#ifndef AGT_FFT_H
#define AGT_FFT_H

#include <Arduino.h>
#include "arduinoFFT.h"

arduinoFFT FFT2 = arduinoFFT();
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02


double FFT_complete_function(double* vReal, double* vImag, uint16_t samples) {
    FFT2.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
    FFT2.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
    FFT2.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
    return (FFT2.MajorPeak(vReal, samples, 8940));
}

/*
for(int a=0; a<20; a++){
   
  for (int i=0; i<3; i++){
    fundamentalFrequencyCandidates[i] = FFT_complete_function(vReal, vImag, samples);
   }
   
   if(fundamentalFrequencyCandidates[0]<fundamentalFrequencyCandidates[1]+0.2&&fundamentalFrequencyCandidates[0]<fundamentalFrequencyCandidates[1]+0.2){
     
     if(fundamentalFrequencyCandidates[0]<fundamentalFrequencyCandidates[2]+0.2&&fundamentalFrequencyCandidates[0]<fundamentalFrequencyCandidates[2]+0.2){
        
        if(fundamentalFrequencyCandidates[1]<fundamentalFrequencyCandidates[2]+0.2 && fundamentalFrequencyCandidates[1]<fundamentalFrequencyCandidates[2]+0.2){ 
          fundamentalFrequency = (fundamentalFrequencyCandidates[0]+fundamentalFrequencyCandidates[1]+fundamentalFrequencyCandidates[2])/3;
          break;
      }
    }
   }
   
}
*/



#endif
