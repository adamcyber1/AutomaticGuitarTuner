# Automatic Guitar Tuner

An Arduino program that tunes a guitar automatically using DC motors attached directly to the tuning knobs of a guitar.

# Demonstration (video)

[![Not Found](https://img.youtube.com/vi/g_ZutZl-uOI/0.jpg)](https://www.youtube.com/watch?v=g_ZutZl-uOI)
There is a lot of background noise, but the video consists of a prototype AGT tuning an acoustic guitar.

# How it works
## Signal Acquisition



## Analog Amplification and Filtering

A pre-amp stage followed by a low pass filter to eliminate high frequency artefacts.

##  Digital Sampling and Filtering
SIgnal is sampled at xxx Hz and a digital bandpass filter (Butterworth) is applied.

## Frequency Detection
Fast Fourier Transform (FFT) is applied to detect the fundamental frequency of the string.

## Frequency Adjustment
The delta between the actual and desired string frequency is converted to a rotation quantity (degrees) which is applied to the servo motor. 

## Photos

<img src="/media/signal.JPG" height="400" width="400"> 
<img src="/media/led_box.jpg" height="400" width="400">
<img src="/media/servo_attached.JPG" height="400" width="400">
<img src="/media/servo.JPG" height="400" width="400">




