# Automatic Guitar Tuner

An Arduino program that tunes a guitar automatically using DC motors attached directly to the tuning knobs of a guitar.

# Demonstration (video)

[![Not Found](https://img.youtube.com/vi/g_ZutZl-uOI/0.jpg)](https://www.youtube.com/watch?v=g_ZutZl-uOI)
There is a lot of background noise, but the video consists of a prototype AGT tuning an acoustic guitar.

# About

Completed as part of a course in early 2018. The programming style is a little bit....unruley, but at the time I had barely programmed whatsoever. This project actually helped encourage me to take on more programming challenges. 

# How it works
## Signal Acquisition

An inductive sensor (aka guitarpickup, taken from an electric guitar) is used to convert the movement of the conductive metal strings into a potential difference across the output terminals of the sensor.

<img src="/media/signal.JPG" height="400" width="400"> 

## Analog Amplification and Filtering

A pre-amp stage followed by a low pass filter to eliminate high frequency artefacts.

##  Digital Sampling and Filtering
SIgnal is sampled at xxx Hz and a digital bandpass filter (Butterworth) is applied.

## Frequency Detection
Fast Fourier Transform (FFT) is applied to detect the fundamental frequency of the string.

## Frequency Adjustment
The delta between the actual and desired string frequency is converted to a rotation quantity (degrees) which is applied to the servo motor. 

<img src="/media/servo_attached.JPG" height="400" width="400">

## Other Photos

<img src="/media/led_box.jpg" height="400" width="400">

<img src="/media/servo.JPG" height="400" width="400">




