#include <Servo.h>
Servo esc;
int val = 100;
const int potentiometre=0;
const int filtre = 3;
float Tension;
float j;
float val1;
 
void setup() {
   esc.attach(9);
   delay(15);
   Serial.begin(9600);
   esc.write(0);
   delay(1000);
   esc.write(180);
   delay(1000);
   esc.write(0);
   pinMode(filtre,OUTPUT);
   }
 
void loop() {
    val1=analogRead(potentiometre);
    Tension = val1/204.8;   //204.8*51
    j=Tension*51;
    analogWrite(filtre,j);
    esc.write(j);
    delay(100);
      }

      
