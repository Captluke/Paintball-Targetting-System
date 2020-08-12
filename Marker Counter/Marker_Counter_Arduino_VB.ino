/*
:Arduino VB Interface
:Author: Lukas Johnny
:Email: Lukasjohnny2328@gmail.
:Maker Counter v1.0
:Date: 13/08/2020
:Revision: v1.0
:License: TechMon
*/


void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    Serial.println(i);
    delay(2000);
  }

}
