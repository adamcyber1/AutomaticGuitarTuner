#ifndef AGT_butterworth_H
#define AGT_butterworth_H

//Generated using:
//https://www-users.cs.york.ac.uk/~fisher/cgi-bin/mkfscript

#include <Arduino.h>

#define NPOLES 4
#define NZEROS 4
static  double xv[NZEROS+1] = {0}, yv[NPOLES+1] = {0};
double GAIN;



  double butterWorth_E2(double input) {
        GAIN = 2.244496884e+03;
        xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.9412139862 * yv[0]) + (  3.8165033595 * yv[1])
                     + ( -5.8092075713 * yv[2]) + (  3.9339105722 * yv[3]);
        
        return yv[4];
      
  }
  
    double butterWorth_A2(double input) {
        GAIN = 1.275132612e+03;
         xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
         yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.9223969024 * yv[0]) + (  3.7539830519 * yv[1])
                     + ( -5.7403875816 * yv[2]) + (  3.9087739231 * yv[3]);
        
        return yv[4];
      
  }

    double butterWorth_D3(double input) {
        GAIN = 8.242485205e+02;
        xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.9039560414 * yv[0]) + (  3.6881269532 * yv[1])
                     + ( -5.6635056998 * yv[2]) + (  3.8792360344 * yv[3]);
        
        return yv[4];
      
  }

     double butterWorth_G3(double input) {
        GAIN = 3.751924004e+02;
        xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.8594510403 * yv[0]) + (  3.5382470105 * yv[1])
                     + ( -5.4960730947 * yv[2]) + (  3.8170244145 * yv[3]);
        
        return yv[4];
      
  }

double butterWorth_B2(double input) {
 
GAIN = 3.314388598e+02;

        xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.8508165960 * yv[0]) + (  3.4942313340 * yv[1])
                     + ( -5.4327502587 * yv[2]) + (  3.7887084744 * yv[3]);
         return yv[4];
     
  }

  double butterWorth_E4(double input) {
    GAIN = 1.315039092e+02;
    xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
        xv[4] = input / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.7691062651 * yv[0]) + (  3.2001566896 * yv[1])
                     + ( -5.0841016847 * yv[2]) + (  3.6511262072 * yv[3]);
        
        return yv[4];
      
  }



#endif
