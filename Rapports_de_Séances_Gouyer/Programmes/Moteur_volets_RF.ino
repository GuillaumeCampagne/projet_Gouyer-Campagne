#include <Servo.h>
Servo servoD;
Servo servoG;
Servo moteurvroom;

float angleG;
float angleD;

float angleGA;
float angleDA;

float SortieFD;
float SortieFG;

int const moteur=11;//sortie 3 rf
int const altitude=6;//sortie 2 rf
int const roulis=9;//sortie 1 rf
float tempsun;
float tempsdeux;
float tempstrois;
float SortieMoteur;
float SortieAltitude;
float SortieRoulis;


void setup() {
  Serial.begin(9600);
  moteurvroom.write(0);
  pinMode(moteur, INPUT);
  pinMode(altitude, INPUT);
  pinMode(roulis, INPUT);
  servoD.attach(3);
  servoG.attach(5);
  moteurvroom.attach(10);
  servoD.write(90);// paralleles avec l'aile
  servoG.write(90);

}

void loop() {
  //RF on relève les valeur télécommande
  tempsun= pulseIn(moteur, HIGH);

  //sécurité en cas de bug moteur
  if (tempsun<1000){
    tempsun=1920.0;
  }

  tempsdeux= pulseIn(altitude, HIGH );
  tempstrois= pulseIn(roulis, HIGH);

  //conversion en PMW
   if (tempstrois>1000 and tempsdeux>1000){
    if (1450>tempsdeux or tempsdeux>1550){
     SortieAltitude=(1-(tempsdeux-1040)/850)*255;
    }
    if ((1400<tempsdeux) and (tempsdeux<1500)){//pas de mouvement
      SortieAltitude=127.5;
    }

    if (1400>tempstrois or tempstrois>1470){
      SortieRoulis=(1-(tempstrois-1070)/831)*255;

    }
    if ((1450<tempstrois) and(tempstrois<1550)){
      SortieRoulis=127.5;
    }

  if (SortieAltitude<=0){
    SortieAltitude=0;
  }
  SortieMoteur=(1-(tempsun-1040)/843)*255;
  if (SortieMoteur<20){//moteur à l'arret
    SortieMoteur=0;
  }
  if (SortieMoteur>240){
     SortieMoteur=255;
 }

  //calcul des angles

  angleG=SortieRoulis/255*180;
  angleD=SortieRoulis/255*180;

  angleDA=180-SortieAltitude/255*180;
  angleGA=SortieAltitude/255*180;

  SortieFD=(angleD+angleDA)/2;
  SortieFG=(angleG+angleGA)/2;

    if ((SortieAltitude>145.0) and (SortieRoulis>145.0)){//haut gauche
    SortieFD=(angleD+angleDA)/2-20;
    SortieFG=(angleG+angleGA)/2;
  }

     if ((SortieAltitude<100.0) and (SortieRoulis>145.0)){//bas gauche
    SortieFD=(angleD+angleDA)/2;
    SortieFG=(angleG+angleGA)/2-20;
  }

       if ((SortieAltitude<100.0) and (SortieRoulis<100.0)){//bas droite
    SortieFD=(angleD+angleDA)/2+20;
    SortieFG=(angleG+angleGA)/2;
  }

       if ((SortieAltitude>145.0) and (SortieRoulis<100.0)){//haut droite
    SortieFD=(angleD+angleDA)/2;
    SortieFG=(angleG+angleGA)/2+20;
  }


  //on bannit les angles trop importants
 if (SortieFD>130){
  SortieFD=130;
 }

 if (SortieFG>130){
  SortieFG=130;
 }

 if (SortieFD<50){
  SortieFD=50;
 }

 if (SortieFG<50){
  SortieFG=50;
  
 }


  //volets final
  servoD.write(SortieFD);//axe altitude
  servoG.write(SortieFG);
   }

  //moteur
  moteurvroom.write(SortieMoteur);

}


  
