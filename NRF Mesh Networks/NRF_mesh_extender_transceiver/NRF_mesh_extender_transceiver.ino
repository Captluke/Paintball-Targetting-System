/*
:NRF mesh extender receiver
:Author: Lukas Johnny
:Email: Lukasjohnny2328@gmail.
:Mesh v1.0
:Date: 17/08/2020
:Revision: v1.0
:License: TechMon
*/

//Include Necessary Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declare nRF pin and const address
RF24 radio(2, 7); // CE, CSN
const byte address[][6] =  {"00001", "00002"};//Setting the two addresses. One for transmitting and one for receiving

//Create a struct that do not exceed 32 bytes (I prefer this method)
struct Received_data {
  byte ch1;
};

int ch1_value = 0;

Received_data received_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN); 
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.openWritingPipe(address[0]); //Set the address at which the data will be send
  radio.openReadingPipe(1,address[1]); // Set the address at which the data will be received
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
  receive_the_data();
  ch1_value = received_data.ch1;
  Serial.println(ch1_value);
  delay(5);

  radio.stopListening();
  radio.write(&received_data, sizeof(Received_data));
}
