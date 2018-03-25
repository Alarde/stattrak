#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
int counter = 0;
boolean screenOff=false;
const int btnKill = 2;
unsigned long tiempo,tiempo2,tiempo3,tiempo4;
int estadoboton1;
boolean btnPressed=false;
void setup() {
  Serial.begin(9600);
  u8g2.begin();
  pinMode(btnKill, INPUT);
}

void loop(){
  if(digitalRead(btnKill) == HIGH) {
    checkUsuario();
  }
}

void checkUsuario(){
  tiempo=millis();
  Serial.print("Tiempo de milis: ");
  Serial.println(tiempo);
  while(digitalRead(btnKill) == HIGH) { 
    tiempo2=millis();
  }
  Serial.print("Tiempo de milis2: ");
  Serial.println(tiempo2);
  tiempo3=tiempo2-tiempo;
  if(tiempo3<1000 ){
    Serial.println("Entro por tiempo 4");
    tiempo4=millis()+100;
    while(millis()<tiempo4){
      if(digitalRead(btnKill) == HIGH) {
        printKill();
        btnPressed=true;
        delay(1500);
        turnOffScreen();
      }
    }
    if(!btnPressed){
      incorrectUser();
    }
    btnPressed=false;
  }else{
    //printKill();
    Serial.print("Tiempo de pulsado: ");
    Serial.println(tiempo3);
    checkIfSecondPressed();
  }
}

void checkIfSecondPressed() {
  printKill();
  Serial.println("in checkIfSecondPressed");
  tiempo=millis()+4000; //4 segundos de inactividad
  while(millis()<tiempo){
  //while(millis()-tiempo>4000){
    if (digitalRead(btnKill) == HIGH) {
      tiempo = millis ();
      addKill();
    }
  }
  turnOffScreen();
}

void addKill(){
  Serial.println("in addKill");
  counter++;
  printKill();
  checkIfSecondPressed();
}

void printKill(){
  Serial.println("in printKill");
  turnOnScreen();
  char killCount[7];
  //char *test="9999999";
  sprintf(killCount, "%0.7d", counter);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso28_tr);
  u8g2.drawStr(0, 32, killCount);
  u8g2.sendBuffer();
  delay(130);
  //counter++;
}

void turnOffScreen() {
  Serial.println("in turnOffScreen");
  u8g2.setPowerSave(1); //This will turn off the screen
  screenOff=true;
}

void turnOnScreen(){
  Serial.println("in turnOnScreen");
  u8g2.setPowerSave(0); //This will turn on the screen
  screenOff=false;
}

void incorrectUser(){
  Serial.println("in incorrectUser");
  turnOnScreen();
  char *errorUser;
  int times=0;
  while(times<2){
    errorUser="ERROR!";
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0, 32, errorUser);
    u8g2.sendBuffer();
    delay(1000);
    errorUser="USER";
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0, 32, errorUser);
    u8g2.sendBuffer();
    delay(1000);
    errorUser="UNKNWN";
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0, 32, errorUser);
    u8g2.sendBuffer();
    delay(1000);
    printKill();
    delay(1500);
    times++;
  }
  turnOffScreen();
}

