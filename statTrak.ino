#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
int counter = 0;
const int BOTON = 2;
int val = 0; //val se emplea para almacenar el estado del boton
int state = 0; // 0 LED apagado, mientras que 1 encendido
int old_val = 0; // almacena el antiguo valor de val



void setup() {
  u8g2.begin();
  pinMode(BOTON, INPUT);
}

void loop() {

  val = digitalRead(BOTON); // lee el estado del Boton
  if (val == HIGH) {
    tiempo = millis ();
    addKill();
    delay(150);
  }
  
}

void addKill(){
  counter++;
  printKill();
}

void printKill(){
  char str[7];
  sprintf(str, "%0.7d", counter);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso28_tr);
  u8g2.drawStr(1, 33, str);
  u8g2.sendBuffer();
  delay(130);
  //counter++;
}

void turnOffPowerSaver() {
  u8g2.setPowerSave(0); //This will turn on the screen
}

void turnOnPowerSaver(){
  u8g2.setPowerSave(1); //This will turn off the screen
}

