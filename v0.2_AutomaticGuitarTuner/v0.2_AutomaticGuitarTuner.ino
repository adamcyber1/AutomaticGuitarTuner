
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


void setup()
{
  Serial.begin(115200); //Initialize Serial Port to 115200BAUD
  Serial.println("Ready"); 
}

///////////////////////END CONFIGURATION AND SETUP/////////////////////////























/////////////////////////////MAIN LOOP ////////////////////////////////////////



void loop() {

  //***************SIGNAL AQUISITION****************//
  for ( int c = 0; c < buffersize; c++) {
     vReal[c] = (double) analogRead(sensorPin);
     vImag[c] = 0.0;
    }

//**************DIGITAL FILTERING****************//
//SELECT DIGITAL FILTER BASED ON THE SELECTED STRING//
if (digitalRead(LED_OUTPUT_STRING_E4) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E4(vReal[c]);
    }
}else if  (digitalRead(LED_OUTPUT_STRING_A3) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_A3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_D3) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_D3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_G3) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_G3(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_B2) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_B2(vReal[c]);
   }
} else if  (digitalRead(LED_OUTPUT_STRING_E2) == HIGH){
   for (int c = 0; c<samples; c++) {
      vReal[c] = butterWorth_E2(vReal[c]);
   }
}
   

//***************FAST FOURIER TRANSFORM AND PEAK DETECTION****************//
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  double x = FFT.MajorPeak(vReal, samples, samplingFrequency);

//**********************SERVO MOTOR CONTROL*********************************//


  //**********************Output Results********************//
  Serial.print(x);
  Serial.println("");
}

///////////////////////////// END MAIN LOOP ////////////////////////////////////////









