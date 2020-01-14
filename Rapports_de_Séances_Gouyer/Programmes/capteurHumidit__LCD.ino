#include <SimpleDHT.h>
#include <SPI.h>
#include <SD.h>

const int pinDHT11 = 8; //Entrée capteur DHT11
SimpleDHT11 dht11;
const int xPin = 0;                   // x de l'accelerometer
const int yPin = 1;                   // y de l'accelerometer
const int zPin = 2;                   // z de l'accelerometer      
const int led_droite = 3;  
const int led_gauche = 2;
int val=0;

const byte pinSD= 10;

void setup() {
  Serial.begin(9600);
  
  //carte sd
  pinMode(10,OUTPUT);
  Serial.print(F("Init SD card... "));
  
  if (!SD.begin(pinSD)) {
    Serial.println(F("FAIL"));
    for(;;);
  }

  Serial.println(F("OK"));
  SD.begin(10);
  SD.remove("Arduino");
  if (SD.exists("Arduino")==false){
    SD.mkdir("Arduino");
  }
  
  pinMode(led_droite,OUTPUT);
  pinMode(led_gauche,OUTPUT);
}

void loop() {
  File fichier= SD.open("Arduino",FILE_WRITE);
  if(!fichier) {
  // Erreur d'ouverture du fichier
    Serial.println(F("Impossible d'ouvrir le fichier"));
    for(;;); // Attend appui sur bouton RESET
  }

  byte x=0;
  byte y=0;
  byte z=0;
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    return;
  }
  fichier.print((int)temperature);
  fichier.println("degret");
  fichier.print((int)humidity);
  fichier.println("%");
  
  x = analogRead(xPin);
  fichier.print("x=");
  fichier.print(x, DEC);
  
  fichier.print("\t y=");
  y = analogRead(yPin);
  fichier.print(y);
  
  fichier.print("\t z=");
  z = analogRead(zPin);
  fichier.println(z);

  int valeur = analogRead(3);                 // pour la luminosité
  float lux = valeur*3.750;//*20000.0/1023.0;
  fichier.println(valeur);
  fichier.println(lux);

  if (val==1){
      digitalWrite(led_droite,HIGH);
      digitalWrite(led_gauche,LOW);
      Serial.println("led droite allumer");
      val=0;
    }
   else{
      digitalWrite(led_droite,LOW);
      digitalWrite(led_gauche,HIGH);
      fichier.println("led gauche allumer");
      val=1;
    }
     delay(1000);
} 
