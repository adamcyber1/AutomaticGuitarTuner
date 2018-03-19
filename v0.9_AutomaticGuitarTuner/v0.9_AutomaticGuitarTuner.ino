
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////                                        ///////////////////////////
////////////////////////                                       ///////////////////////////
////////////////////////       AUTOMATIC GUITAR TUNER          ///////////////////////////
////////////////////////       ELEC 3907 WINTER 2018            ///////////////////////////
////////////////////////                                       ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*
 * Authors
 * 
 *Adam Fillion
 *Michael de Grasse
 *Zhang'Ado' Qinyao
 *Ashen
 *Kaya 
 *Vladimir .
 */



 ////////////////////////////////////PROJECT SUMMARY//////////////////////////////////////////
 /*
  * The enlosed project is the firmware for the Automatic Guitar Tuner (AGT)
  * 
  * The purpose of the AGT is to provide rapid and accurate tuning to the user of an accoustic guitar. 
  * This is accomplished through the following steps:
  * 
  * 1) SIGNAL AQUISITION
  * 
  * The accoustic signal is detected and recorded using a standard guitar pickup. This signal is sampled at a rate of 8900Hz and 
  * stored in a buffer to await processing.
  * 
  * 2) STRING SELECTION 
  * 
  * The LED interface is used to select the desired string to tune.
  *
  * 3) DIGITAL FILTERING
  * 
  * A 2nd order digital butterworth bandpass filter is used to filter out harmonics.
  * 
  * 4) FAST FOURIER TRANSFORM AND PEAK DETECTION
  * 
  * An FFT is performed on the filtered data and the spectrum's maximum is extracted -this is the pitch of the string.
  * 
  * 5) SERVO MOTOR CONTROL 
  * 
  * The guitar string is loosened or tightened depending on the pitch of the string.
  * 
  * 
  * */



/////////////////////////////////////////Libraries////////////////////////////////////////////  


#include "AGT_FFT.h" 
#include "AGT_butterworth.h" 


///////////////////////////////////////// END Libraries////////////////////////////////////////////  




///////////////////////CONFIGURATION AND SETUP/////////////////////////////
arduinoFFT FFT = arduinoFFT(); /* Create FFT object from arduinoFFT library */

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

//settings
const uint16_t samples = 512; //Must be power of two. Defines the size of the buffer that will be operated on (FFT).
const double samplingFrequency = 8940; //Sampling rate of the arduino MEGA

//buffers and results
int buffersize = samples; //Initializes bufferSize
double vReal[samples]; //real component of signal data
double vImag[samples]; //imaginary component of signal data (set to 0)
double fundamentalFrequency; //maximum value of signal spectrum
double frequencyCandidate[3]; 
double error; //difference between target frequency and detected frequency

//counters//
int indexCounter = 0;
int count = 0;

//PINS//
//LED CONTROL//
int set_pin = 13;
int LED_OUTPUT_STRING_A2 = 5;
int LED_OUTPUT_STRING_D3 = 6;
int LED_OUTPUT_STRING_G3 = 7;
int LED_OUTPUT_STRING_B2 = 8;
int LED_OUTPUT_STRING_E2 = 9;
int LED_OUTPUT_STRING_E4 = 4;
int currentLed = 0;
//SENSORS//
int sensorPin = A0; //Defines the analog pin for the pickup signal
int sensorValue = 0; //Intializes Sensor Value

//FLAGS//
bool no_Signal = 1;
bool valid_Frequency = 0;
bool is_Tuned = 0;
bool error_flag = 0;

//STRING PARAMETERS//
//CONSIDER SHRINKING THIS ONTO ONE LINE IE. struct strings E2, AA2, D3, G3 etc...
struct strings  {
  double targetFrequency;
  double tighten_rate; //the frequency shift for a quarter rotation of the adjustment knob
  double loosen_rate;
};
struct strings E2;
struct strings AA2; 
struct strings D3;    
struct strings G3;
struct strings B3;
struct strings E4;
struct strings tuneString;

void setup()
{
  Serial.begin(115200); //Initialize Serial Port to 115200BAUD
  Serial.println("Welcome to the AGT"); 
 
///////////////DEFINE STRING PARAMETERS /////////////////////////////////
  E2.targetFrequency = 82.4; //desired 'in tune' pitch
  E2.loosen_rate= 0.083; //how fast the adjustment knob reduces the frequency in Hz/degree of rotation (loosen)
  E2.tighten_rate= 0.055;
  AA2.targetFrequency = 110;
  AA2.loosen_rate= 0.0511;  
  AA2.tighten_rate = 0.0844;
  D3.targetFrequency = 146.8;
  D3.loosen_rate= 0.05;  
  D3.tighten_rate = 0.0722;
  G3.targetFrequency = 196;
  G3.loosen_rate = 0.07; 
  G3.tighten_rate = 0.03666;
  B3.targetFrequency = 247;
  B3.loosen_rate = 0.094;
  B3.tighten_rate = 0.128;
  E4.targetFrequency = 329.6;
  E4.loosen_rate = 0.08888;  
  E4.tighten_rate= 0.084;
  tuneString.targetFrequency = 100;
  tuneString.loosen_rate = 100;
  tuneString.tighten_rate = 100;

  //USER INTERFACE LEDS//
  pinMode(set_pin, INPUT);
  pinMode(LED_OUTPUT_STRING_E4, OUTPUT);
  pinMode(LED_OUTPUT_STRING_A2, OUTPUT);
  pinMode(LED_OUTPUT_STRING_D3, OUTPUT);
  pinMode(LED_OUTPUT_STRING_G3, OUTPUT);
  pinMode(LED_OUTPUT_STRING_B2, OUTPUT);
  pinMode(LED_OUTPUT_STRING_E2, OUTPUT);

}
///////////////////////END CONFIGURATION AND SETUP/////////////////////////

/////////////////////////////MAIN LOOP ////////////////////////////////////////
void loop() {
// Serial.println("===================================================== NEW LOOP ===========================================");
//***************SIGNAL AQUISITION****************//
  for ( int c = 0; c < buffersize; c++) {
     vReal[c] = (double) analogRead(sensorPin);
     //Serial.print(vReal[c]);
     //Serial.print("  ");
     vImag[c] = 0.0;
    // Serial.println(vReal[c]);
    }

 //******************STRING SELECTION*************************//
if(digitalRead(set_pin)==HIGH && count == 0){
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, HIGH);   
      delay(300);    
      count++; 
  }
  if(digitalRead(set_pin)==HIGH && count == 1){
    digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, HIGH);  
      delay(300);    
      count++;
  }
   if(digitalRead(set_pin)==HIGH && count == 2){
        digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, HIGH);
    delay(300);    
    count++;
   }
    if(digitalRead(set_pin)==HIGH && count == 3){
        digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, HIGH);
    delay(300);    
    count++;
   }
    if(digitalRead(set_pin)==HIGH && count == 4){
        digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, HIGH);
    delay(300);    
    count++;
   }
   if(digitalRead(set_pin)==HIGH && count == 5){
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);  
    digitalWrite(LED_OUTPUT_STRING_E4, HIGH);    
    delay(300); 
    count++;
  }  
  if (count==6) {
    count = 0;
  }

//*********************Check For Sufficient Signal**************************//
//If a string has not been plucked, then there is no need to perform an FFT//
if (averageArray(vReal)>9) {
   no_Signal = 0;   //Serial.println(averageArray(vReal));
} else {
  no_Signal = 1;
  //Serial.println("Insufficient Signal");
 // Serial.println(averageArray(vReal));
}

//*****************Enter Algorithm********************//
//If a signal has bee registered, perform the frequency detection algorithm//
if (no_Signal==0) {
  complete_algorithm(vReal, vImag, samples);
  no_Signal=1; //reset signal flag
}
} // loop

///////////////////////////// END MAIN LOOP ////////////////////////////////////////


void complete_algorithm(double* vReal, double* vImag, uint16_t samples ){

//**************DIGITAL FILTERING and Configuration****************//
//SELECT DIGITAL FILTER and Parameters BASED ON THE SELECTED STRING//
if (digitalRead(LED_OUTPUT_STRING_E2) == HIGH){
   tuneString.targetFrequency = E2.targetFrequency;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E2(vReal[c]);
    }
}else if  (digitalRead(LED_OUTPUT_STRING_A2) == HIGH){
  tuneString.targetFrequency = AA2.targetFrequency;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_A2(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_D3) == HIGH){
  tuneString.targetFrequency = D3.targetFrequency;;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_D3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_G3) == HIGH){
  tuneString.targetFrequency = G3.targetFrequency;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_G3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_B2) == HIGH){
  tuneString.targetFrequency = B3.targetFrequency;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_B2(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_E4) == HIGH){
  tuneString.targetFrequency = E4.targetFrequency;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E4(vReal[c]);
   }
}
   

  //***************FAST FOURIER TRANSFORM AND PEAK DETECTION****************//
frequencyCandidate[indexCounter] =  FFT_complete_function(vReal, vImag, samples);
Serial.print("Detected Frequency:");
Serial.print(frequencyCandidate[indexCounter]);
Serial.print("\n");
//Serial.print("Index Counter:");
//Serial.print(indexCounter);
//Serial.print("\n");

//*****************************Outlier Rejection***************************//
/* Description:
This algorithm only accepts a detected frequency if 3 consecutive frequencies are within a certain spread (+/-4Hz), 
at which point it takes the average of these values and accepts them as a valid frequency.
example: The detected frequencies: [100, 99, 92, 100, 98, 101, 102, 85, 104]
         would yield the following:[100, 99, 92, (100, 98, 101), 102, 85, 104]
So only one set here would be accepted, and (100+98+101) / 3 would be the output frequency.
*/
if (indexCounter>=1) {
  if(abs(frequencyCandidate[indexCounter]-frequencyCandidate[indexCounter-1])<3){
    if (indexCounter == 2){
      valid_Frequency = 1; //allows entry into the motor control block
      indexCounter = 1;
    }else{
      indexCounter++;
    } 
  }else {
    frequencyCandidate[0] = frequencyCandidate[indexCounter];
    indexCounter = 1;
  }
}else {
  indexCounter++;
}

//***********************Check Frequency**********************************//
/* Description:
Depending on the detected pitch of the string, it will be loosened or tightened or, in the event that it is 
properly tuned, the LED's will blink.

In the event that the detected frequency is radically different than the expected pitch, an error will be assumed and no
action will be taken to avoid accidentally overtightening the string
*/
if (valid_Frequency == 1){
//Serial.print("Valid Frequency Flag:");
//Serial.print(valid_Frequency);
//Serial.print("\n");
//Serial.println("VALID FREQUENCY FOUND AND IS:"); 
//Serial.println(frequencyCandidate[0]); 
valid_Frequency = 0; //reset flag to wait for next valid frequency
error = abs(averageArray(frequencyCandidate) - tuneString.targetFrequency);
Serial.print("Average frequency detected: ");
Serial.print(averageArray(frequencyCandidate));
Serial.print("\n");
Serial.print("Target Frequency: ");
Serial.print(tuneString.targetFrequency);
Serial.print("\n");
Serial.print("Error: ");
Serial.print(error);
Serial.print("\n");
frequencyCandidate[0]=0;
frequencyCandidate[1]=0;
frequencyCandidate[2]=0;
if (error<1.5){
  is_Tuned = 1;
  Serial.println("Guitar is tuned.");
  //flash LEDs
  for (int flash = 0; flash<10; flash++) {
      digitalWrite(LED_OUTPUT_STRING_E2, !digitalRead(LED_OUTPUT_STRING_E2));
      digitalWrite(LED_OUTPUT_STRING_A2, !digitalRead(LED_OUTPUT_STRING_A2));
      digitalWrite(LED_OUTPUT_STRING_D3, !digitalRead(LED_OUTPUT_STRING_D3));
      digitalWrite(LED_OUTPUT_STRING_G3, !digitalRead(LED_OUTPUT_STRING_G3));
      digitalWrite(LED_OUTPUT_STRING_B2, !digitalRead(LED_OUTPUT_STRING_B2));
      digitalWrite(LED_OUTPUT_STRING_E4, !digitalRead(LED_OUTPUT_STRING_E4));
       delay(100);
    }
   

    
} else if (error>=1.5 && error<35) {
  is_Tuned = 0;
  Serial.println("Guitar NOT TUNED");
  //motor control
}else {
  is_Tuned = 0;
  error_flag = 1;
  Serial.println("ERROR: FREQUENCY DETECTION NOT ACCURATE");
}
}

}

///////Average function/////////
double averageArray(double* vReal){
double sum = 0;
  for (int i = 0; i<sizeof(vReal);i++){
    sum += vReal[i];   
  }
  return (sum/sizeof(vReal));
}

void adjustString(double error) {
  
}











