#include <Servo.h>
 //moteur première version
Servo esc;
 
int val = 0; 
 
void setup() {
   esc.attach(9);
   delay(15);
   Serial.begin(9600);
   esc.write(0);
   delay(1000);
   esc.write(180);
   delay(1000);
   esc.write(0);
   Serial.println("allumage");
   }
 
void loop() {
   if (Serial.available() > 0) {
      val = Serial.parseInt();  
      Serial.println(val);
      esc.write(val);          
      delay(15);
      }
   }
