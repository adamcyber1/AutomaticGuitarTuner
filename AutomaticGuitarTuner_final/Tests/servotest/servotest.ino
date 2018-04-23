#include <Servo.h>


Servo servoTune;

void setup() {
  // put your setup code here, to run once:

servoTune.attach(2);
Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  leftRotate(90, servoTune);
  delay(1000);
 rightRotate(90, servoTune);
 //servoTune.write(10);
// delay(500);
// Serial.print("loop");

}

//LEFT ROTATE
//Left rotate
double leftRotate(double angle, Servo servo){
  uint32_t timeAngle;
  double value = 0.0000606; // Don't change
  timeAngle = (angle*value)* 60000L;
  Serial.println("1");

   for( uint32_t tStart = millis();  (millis()-tStart) < timeAngle;  ){
   servo.writeMicroseconds(1700);
   Serial.println("loop");
 
  }
  Serial.println(" exit loop");
  for( uint32_t tStart = millis();  (millis()-tStart) < timeAngle;  ){
    servo.writeMicroseconds(1500);
Serial.println("second loop");
  }
}

///SERVO ROTATE RIGHT////
//Right rotate
double rightRotate(double angle, Servo servo){
  uint32_t timeAngle;
  double value = 0.0000606; //Don't change
  timeAngle = (angle*value)* 60000L;

   for( uint32_t tStart = millis();  (millis()-tStart) < timeAngle;  ){
   servo.writeMicroseconds(1300);
  
  }
  for( uint32_t tStart = millis();  (millis()-tStart) < timeAngle;  ){
    servo.writeMicroseconds(1500);

  }
  
}
