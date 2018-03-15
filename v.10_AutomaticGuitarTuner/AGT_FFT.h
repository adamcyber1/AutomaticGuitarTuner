#ifndef AGT_FFT_H
#define AGT_FFT_H
#include <Arduino.h>
#include "arduinoFFT.h"

//The following library was used:
//https://github.com/kosme/arduinoFFT

/* Description:

This condenses the calling of the Fast Fourier Transform and allows for customizable calling.
The amount of samples being used can be changed in the function call to speed up or slow down execution.

*/

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

#endif
