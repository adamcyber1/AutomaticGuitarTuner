int set_pin = 13;
byte ledPin[] = {4,5,6,7,8,9};
int direction = 1;
int currentLed = 0;
int count = 0;
int doneE = 0;
int doneA = 0;
int doneD = 0;
int doneG = 0;
int doneB = 0;
int doneE1 = 0;         
void setup() {
  pinMode(set_pin, INPUT);
  int x = 0;
  for(x=0;x<6;x++){
    pinMode(ledPin[x], OUTPUT);
  }
  Serial.begin(115200);
}
void loop() {
  
  if(digitalRead(set_pin)==HIGH && count == 0){
    digitalWrite(ledPin[count], HIGH);
    while(doneE==0){
      delay(1000);
      doneE = 1;
     }
      count++;
      
  }
  if(digitalRead(set_pin)==HIGH && count == 1){
    digitalWrite(ledPin[count-1], LOW);
    digitalWrite(ledPin[count], HIGH);
    while(doneA==0){
      delay(1000);
      doneA = 1;
     }
      count++;
  }
  
   if(digitalRead(set_pin)==HIGH && count == 2){
    digitalWrite(ledPin[count-1], LOW);
    digitalWrite(ledPin[count], HIGH);
    while(doneD==0){
        delay(1000);
        doneD =1;
     }
      count++;
   }
  
   if(digitalRead(set_pin)==HIGH && count == 3){
    digitalWrite(ledPin[count-1], LOW);
    digitalWrite(ledPin[count], HIGH);
    while(doneG==0){
      delay(1000);
      doneG = 1;
     }
     
      count++;
      digitalWrite(ledPin[count-1], LOW);
  }
  
  if(count==4){
    
    
    doneE = 0;
    doneA = 0;
    doneD = 0;
    doneG = 0;
    doneB = 0;
    doneE1 =0;
   
  
  }
  count = 0;
}

