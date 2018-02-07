

#include "arduinoFFT.h"
#include "AGT_FFT.h"
#include "AGT_butterworth.h"

//https://www-users.cs.york.ac.uk/~fisher/cgi-bin/mkfscript

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
  These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 512; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 8940;
const uint8_t amplitude = 100;
/*
  These are the input and output vectors
  Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];
double bufferStream[samples];
//double vReal2[samples];
//double vImag2[samples];
//double vRealFinal[samples];


#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

//Butterworth Filter
//#define NZEROS 4
//#define NPOLES 4
//#define GAIN   6.847506274e+02
//static  double xv[NZEROS+1] = {0}, yv[NPOLES+1] = {0};


int loopCounter = 0;
int sensorPin = A0;
int sensorValue = 0;
int buffersize = samples;
double correctionFactor = 1.776;
void setup()
{

  Serial.begin(115200);
  Serial.println("Ready");
  //analogReference(INTERNAL);
}

void loop()
{

  //Buffer Stream
  for ( int c = 0; c < buffersize; c++) {
    vReal[c] = (double) analogRead(sensorPin);
    vImag[c] = 0.0;
  }




  // for (int c = 0; c<samples; c++) {
  // vReal[c] = butterWorth_B3(vReal[c]);
  //  }

if(digitalRead(LED_OUTPUT_STRING_E2)==HIGH){
  
}




  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  double x = FFT.MajorPeak(vReal, samples, samplingFrequency);
  Serial.print(x);
  Serial.println("");

}










