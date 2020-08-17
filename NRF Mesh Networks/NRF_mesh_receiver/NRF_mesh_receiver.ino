/*
:NRF mesh Transmitter
:Author: Lukas Johnny
:Email: Lukasjohnny2328@gmail.
:Mesh v1.0
:Date: 18/08/2020
:Revision: v1.0
:License: TechMon
*/

//Include Necessary Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//Declare nRF pin and const address
RF24 radio(2, 7); // CE, CSN
const byte address[][6] =  {"00001", "00002"};//Setting the two addresses. One for transmitting and one for receiving

struct Received_data {
  byte ch1;
};

Received_data received_data;

int ch1_value = 0;
int ch2_value = 0;
int count = 0;
int marks = 0;
int piezoPin = 8;
String sp1 = " : ";

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.openReadingPipe(1, address[0]); //Set the address at which the data will be send
}

unsigned long last_Time =0;

void receive_the_data()
{
  if(radio.available()> 0)
  {
    radio.read(&received_data, sizeof(Received_data));
    last_Time = millis();
  }
}

void loop() {
  radio.startListening();
  lcd.setCursor(3,0);
  lcd.print("Hits Count");
  receive_the_data();
  ch1_value = received_data.ch1;

  if(ch1_value == 0) {
    lcd.setCursor(7,1);
    lcd.print(" "); 
    lcd.setCursor(8,1);
    lcd.print(" "); 
  }
  //ch2_value = received_data.ch2;
  //Serial.println(ch1_value + sp1 + ch2_value);

   lcd.setCursor(7,1);
   lcd.print(ch1_value);
   String sp1 = "Hits Count ";

  Serial.println(sp1 + ch1_value);
  
}
