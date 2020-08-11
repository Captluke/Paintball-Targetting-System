/*
:Marker Counter Transmitter
:Author: Lukas Johnny
:Email: Lukasjohnny2328@gmail.
:Maker Counter v1.0
:Date: 05/08/2020
:Revision: v1.0
:License: TechMon
*/

//Include Necessary Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declare nRF pin and const address
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "000001";

//Declare Sensors and Piezo Pin
int vibr_Pin_A =A1;
int vibr_Pin_B =A2;
int piezoPin = 8;

int count = 0;
int marks = 0;
String sp1 = " : ";
int LED_Pin = 2;

//Create a struct that do not exceed 32 bytes (I prefer this method)
struct Data_to_be_sent {
  byte ch1;
  byte ch2;
};

Data_to_be_sent sent_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();  

  //Default reset channel value
  sent_data.ch1 = 0;
  sent_data.ch2 = 0;
  
  pinMode(vibr_Pin_A, INPUT);
  pinMode(vibr_Pin_B, INPUT);
  pinMode(LED_Pin, OUTPUT);
}

void loop() {

  long measurement_A =TP_init_A();
  long measurement_B =TP_init_B();
  delay(50);

  sent_data.ch1 = measurement_A;
  sent_data.ch2 = measurement_B;
  String sp1 = " : ";
  //Serial.println(measurement_A + sp1 + measurement_B);

  /* if ((measurement_A > 210) && (measurement_B >210)){
   
    digitalWrite(LED_Pin, HIGH);
    marks = ++count; 
    Serial.println(marks);
    tone(piezoPin, 440, 200);
  }
  else{
    digitalWrite(LED_Pin, LOW); 
    noTone(8);
  }
  */
  
  //sent_data.ch1 = marks;
  radio.write(&sent_data, sizeof(Data_to_be_sent));
  //Serial.println(sent_data.ch1);
}

long TP_init_A(){
  delay(10);
  long measurement_A=pulseIn (vibr_Pin_A, HIGH);  //wait for the pin to get HIGH and returns measurement_A
  return measurement_A;
}

long TP_init_B(){
  delay(10);
  long measurement_B=pulseIn (vibr_Pin_B, HIGH);  //wait for the pin to get HIGH and returns measurement_A
  return measurement_B;
}
