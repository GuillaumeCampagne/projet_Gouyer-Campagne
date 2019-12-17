#include <Servo.h>//non fonctionnel
Servo servoD;
Servo servoG;
int val;
char Data;
int X;
int Y;
int vd;
float vg;


void setup() {
  Serial.begin(9600);
  Serial.println("ok");
  servoD.attach(3);
  servoG.attach(5);
  servoD.write(90);// paralleles avec l'aile
  servoG.write(90);
 
  

}

void loop() {
  if (Serial.available()) {
     Data=Serial.read();
     Serial.println(Data);
    if (Data=='X'){
        X=Serial.parseInt();
        Serial.println(X);
      }
    if (Data=='Y'){
        Y=Serial.parseInt();
        Serial.println(Y);
      }
  }
  
  if ((X<255) and (Y==255)){//tourne a gauche
                vg=20.0+(X/255.0)*70.0;//servo moteur posés dans 2 sens différents donc pas besoin de plus de code
                servoD.write(vg);
                servoG.write(vg);
             }
  if ((X>255) and (Y==255)){//tourne a droite
                vg=160-X/511.0*70;
                servoD.write(vg);
                servoG.write(vg);
             }
  if ((X==255) and (Y<255)){//plonge
                vd=160.0-Y/511.0*70;
                vg=20.0+Y/511.0*70;
                servoD.write(vd);
                servoG.write(vg);
             }
   if ((X==255) and (Y>255)){//monte
                vg=160.0-Y/511.0*70;
                vd=20.0+Y/511.0*70;
                servoD.write(vd);
                servoG.write(vg);
             }    
   if ((X==255) and (Y==255)){//vol en ligne droite
    
                servoD.write(90);
                servoG.write(90);
             }    
}
