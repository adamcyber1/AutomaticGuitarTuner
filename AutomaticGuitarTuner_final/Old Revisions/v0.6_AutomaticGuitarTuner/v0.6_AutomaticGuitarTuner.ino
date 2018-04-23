
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
 *Vlad Mirkadirka
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
  * 2) DIGITAL FILTERING
  * 
  * add content
  * 
  * 3) FAST FOURIER TRANSFORM AND PEAK DETECTION
  * 
  * add content
  * 
  * 4) SERVO MOTOR CONTROL 
  * 
  * add content
  * 
  * 
  * 
  * 
  * 
  * 
  * 
  * 
  * 
  * */



/////////////////////////////////////////Libraries////////////////////////////////////////////  

#include "arduinoFFT.h"
#include "AGT_FFT.h"
#include "AGT_butterworth.h"


///////////////////////////////////////// END Libraries////////////////////////////////////////////  

//https://www-users.cs.york.ac.uk/~fisher/cgi-bin/mkfscript

//https://github.com/kosme/arduinoFFT
arduinoFFT FFT = arduinoFFT(); /* Create FFT object from arduinoFFT library */

///////////////////////CONFIGURATION AND SETUP/////////////////////////////
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

const uint16_t samples = 512; //Must be power of two. Defines the size of the buffer that will be operated on (FFT).
const double samplingFrequency = 8940; //Sampling rate of the arduino MEGA
int sensorPin = A0; //Defines the analog pin for the pickup signal
int sensorValue = 0; //Intializes Sensor Value
int buffersize = samples; //Initializes bufferSize
double bufferStream[samples];
double vReal[samples];
double vImag[samples];
double fundamentalFrequency;
double frequencyCandidate[3];
double error;
int indexCounter = 0;





//LED CONTROL//
int set_pin = 13;
int LED_OUTPUT_STRING_E4 = 4;
int LED_OUTPUT_STRING_A2 = 5;
int LED_OUTPUT_STRING_D3 = 6;
int LED_OUTPUT_STRING_G3 = 7;
int LED_OUTPUT_STRING_B2 = 8;
int LED_OUTPUT_STRING_E2 = 9;

int currentLed = 0;
int count = 0;



//FLAGS//
bool no_Signal = 1;
bool valid_Frequency = 0;
bool is_Tuned = 0;
bool error_flag = 0;

//STRINGS//
struct strings  {
  double targetFrequency;
  double frequencyErrorMax;
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
  Serial.println("Ready"); 
 

///////////////DEFINE STRINGS /////////////////////////////////
  E2.targetFrequency = 82.4;
  E2.frequencyErrorMax = 2;
  AA2.targetFrequency = 110;
  AA2.frequencyErrorMax = 2;
  D3.targetFrequency = 146.8;
  D3.frequencyErrorMax = 2;
  G3.targetFrequency = 196;
  G3.frequencyErrorMax = 2;
  B3.targetFrequency = 247;
  B3.frequencyErrorMax = 2;
  E4.targetFrequency = 329.6;
  E4.frequencyErrorMax = 2;
  tuneString.targetFrequency = 100;
  tuneString.frequencyErrorMax = 2;


  //LED CONTROL//
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

 // Serial.println(E2.targetFrequency);
  //***************SIGNAL AQUISITION****************//
  for ( int c = 0; c < buffersize; c++) {
     vReal[c] = (double) analogRead(sensorPin);
     vImag[c] = 0.0;
    }
   

 //******************CHECK WHICH STRING IS SELECTED**************************//

if(digitalRead(set_pin)==HIGH && count == 0){
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E4, HIGH);   
      delay(1000);    
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
      delay(1000);    
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
    delay(1000);    
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
    delay(1000);    
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
    delay(1000);    
    count++;
   }
  
   if(digitalRead(set_pin)==HIGH && count == 5){
        digitalWrite(LED_OUTPUT_STRING_E4, LOW);
    digitalWrite(LED_OUTPUT_STRING_A2, LOW);
    digitalWrite(LED_OUTPUT_STRING_D3, LOW);
    digitalWrite(LED_OUTPUT_STRING_G3, LOW);
    digitalWrite(LED_OUTPUT_STRING_B2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, LOW);
    digitalWrite(LED_OUTPUT_STRING_E2, HIGH);    
    delay(1000); 
    count++;
  }  
  
  count = 0;


 

 


//*********************Check For Sufficient Signal**************************//
if (averageArray(vReal)>200) {
   no_Signal = 0;
} else {
  Serial.println("Insufficient Signal");
}

//////////Enter Algorithm/////////
if (no_Signal==0) {
  complete_algorithm(vReal, vImag, samples);
}


}

///////////////////////////// END MAIN LOOP ////////////////////////////////////////






/////////////////////////////////NO_SIGNAL==1 EXECUTION STATES//////////////////////////

void complete_algorithm(double* vReal, double* vImag, uint16_t samples ){


//**************DIGITAL FILTERING and Configuration****************//
//SELECT DIGITAL FILTER and Parameters BASED ON THE SELECTED STRING//

if (digitalRead(LED_OUTPUT_STRING_E4) == HIGH){
   tuneString.targetFrequency = E4.targetFrequency;
   tuneString.frequencyErrorMax =  E4.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E4(vReal[c]);
    }
}else if  (digitalRead(LED_OUTPUT_STRING_A2) == HIGH){
  tuneString.targetFrequency = AA2.targetFrequency;
   tuneString.frequencyErrorMax =  AA2.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_A2(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_D3) == HIGH){
  tuneString.targetFrequency = D3.targetFrequency;
   tuneString.frequencyErrorMax =  D3.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_D3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_G3) == HIGH){
  tuneString.targetFrequency = G3.targetFrequency;
   tuneString.frequencyErrorMax =  G3.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_G3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_B2) == HIGH){
  tuneString.targetFrequency = B3.targetFrequency;
   tuneString.frequencyErrorMax =  B3.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_B2(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_E2) == HIGH){
  tuneString.targetFrequency = E2.targetFrequency;
   tuneString.frequencyErrorMax =  E2.frequencyErrorMax;
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E2(vReal[c]);
   }
}
   

  //***************FAST FOURIER TRANSFORM AND PEAK DETECTION****************//

frequencyCandidate[indexCounter] =  FFT_complete_function(vReal, vImag, samples);
if (indexCounter>=1) {
  if(abs(frequencyCandidate[indexCounter]-frequencyCandidate[indexCounter-1])<5){
    if (indexCounter == 2){
      valid_Frequency = 1;
      indexCounter = 0;
    }
    indexCounter++;
  }else {
    frequencyCandidate[0] = frequencyCandidate[indexCounter];
    indexCounter = 1;
  }
}



//***********************Check Frequency**********************************//
if (valid_Frequency == 1){
valid_Frequency = 0; //reset flag
error = abs(averageArray(frequencyCandidate) - 100);
frequencyCandidate[0]=0;
frequencyCandidate[1]=0;
frequencyCandidate[2]=0;
if (error<5){
  is_Tuned = 1;
  //flash LEDs
} else if (error<5 && error<50) {
  is_Tuned = 0;
  //motor control
}else {
  is_Tuned = 0;
  error_flag = 1;
  Serial.println("ERROR: FREQUENCY DETECTION NOT ACCURATE");
}
}

}




//comment






///////Average function/////////
double averageArray(double* vReal){
double sum = 0;
  for (int i = 0; i<sizeof(vReal);i++){
    sum += vReal[i];   
  }
  return (sum/sizeof(vReal));
}










