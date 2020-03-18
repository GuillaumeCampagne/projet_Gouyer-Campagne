#include <SimpleDHT.h>
#include <SPI.h>
#include <SD.h>

const int pinDHT11 = 8; //Entrée capteur DHT11
SimpleDHT11 dht11;       
const int led_gauche = 2;

int val=0;
File myFile;
const byte pinSD= 4;

void setup() {
  // ouverture communication et attente de réponse:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  //Initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
  //supression de l'ancien fichier
  SD.remove("arduino.txt");
  Serial.println("ancien fichier suppr");
  myFile = SD.open("arduino.txt", FILE_WRITE);

  // essai d'écriture
  if (myFile) {
    Serial.print("Writing to arduino.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening arduino.txt");
  }

  // essai lecture
  myFile = SD.open("arduino.txt");
  if (myFile) {
    Serial.println("arduino.txt:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
  } else {
    Serial.println("error opening arduino.txt");
  }

  //LED
  pinMode(led_gauche,OUTPUT);

  //Fermeture fichier test
  myFile.close();
}

void loop() {
  myFile= SD.open("arduino.txt",FILE_WRITE);
  if(!myFile) {
  // Erreur d'ouverture du fichier
    Serial.println(F("Impossible d'ouvrir le fichier"));
    for(;;); // Attend appui sur bouton RESET
  }
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    return;
  }

  //écriture dans le fichier arduino des données et relevé des valeurs
  myFile.print("température: ");
  myFile.print((int)temperature);
  myFile.print(" degrés ||| ");
  myFile.print("humidité: ");
  myFile.print((int)humidity);
  myFile.print(" % ||| ");


  int valeur = analogRead(3);                 // pour la luminosité
  float lux = valeur*3.750;//*20000.0/1023.0;
  myFile.print(" lux: ");
  
  myFile.print(lux);
  myFile.println(" lx");

  //led permettant à l'utilisateur de s'assurer du bon fonctionnement sans terminal
  if (val==1){
      digitalWrite(led_gauche,LOW);
      val=0;
    }
   else{
      digitalWrite(led_gauche,HIGH);
      val=1;
    }

    //On force l'écriture
    myFile.flush();
    delay(1000);
    myFile.close();
    File myFile=myFile.openNextFile();
    } 
