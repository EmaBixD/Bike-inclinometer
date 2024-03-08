/*
PIN CONFIGURAION in C:\Users\name\Documents\Arduino\libraries\TFT_eSPI\**User_Setup.h**; make sure to uncomment or edit following lines:

#define GC9A01_DRIVER

#define TFT_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 18
#define TFT_CS   22  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST  4  // Reset pin (could connect to Arduino RESET pin)
*/

// GC9A01
#include <TFT_eSPI.h>
// MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
// IMAGES
#include "erossa.h"
#include "sfondo.h"
#include "moto.h"
#include "motoback.h"
// BUTTON
#define BUTTON_PIN 5 // GPIO5 pin connected to button

// VARIABILI
//unsigned long lastSwitchTime = 0;
//bool interfaceState = false; //VECCHIA VERSIONE, senza pulsante
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
bool schermata = true; // Variabile per tenere traccia dello stato attivo dello sprite

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite spriteBack = TFT_eSprite(&tft);
TFT_eSprite txt = TFT_eSprite(&tft);
TFT_eSprite txTemp = TFT_eSprite(&tft);

Adafruit_MPU6050 mpu;

void setup() {
  // INIZIALIZZAZIONE
  Serial.begin(115200);
  Wire.begin(21, 19); // SCL and SDA pins
  mpu.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  tft.init();
  tft.setRotation(1); // gira il display di 90° per raddrizzarlo

  // LOADING SCREEN
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,240,240,logo);
  for (int i = 0; i < 11; i++) {
    drawProgressBar(70, 210, 100, 10, i * 10); // PROGRESSBAR (x, y, larghezza, altezza, ...)
    delay(100);
  }
  
  background.setColorDepth(8);
  background.createSprite(240,240); // Crea l'oggetto con (x, y) dimensioni
  sprite.setColorDepth(8);
  sprite.createSprite(120,120);
  sprite.pushImage(0,0,120,120,bike); // Assegna l'immagine all'oggetto
  spriteBack.setColorDepth(8);
  spriteBack.createSprite(120,120);
  spriteBack.pushImage(0,0,120,120,bikeBack);
  txt.createSprite(40,40);
  txt.setTextColor(TFT_SILVER,TFT_BLACK); // Color of text and background
  txTemp.createSprite(60,40);
  txTemp.setTextColor(TFT_RED,TFT_BLACK);
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int angleX = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
  int angleY = atan2(a.acceleration.x, a.acceleration.z) * 180.0 / PI;

  background.pushImage(0,0,240,240,back); // cancella tutto quello su schermo e metti lo sfondo

  /* CAMBIA SCHERMATA OGNI 5 SECONDI, versione senza pulsante
  if (millis() - lastSwitchTime >= 5000) {
    interfaceState = !interfaceState;
    lastSwitchTime = millis();
  }

  if (interfaceState == false) {
    showInterface1(angleX);
  } else {
    showInterface2(angleY);
  }
  */

  currentState = digitalRead(BUTTON_PIN);

  if (lastState == HIGH && currentState == LOW) {
    if (schermata)
      schermata = false;
    else
      schermata = true;
    //for (int y = 0; y < tft.height(); y++) {
      //tft.drawFastHLine(0, y, tft.width(), TFT_BLACK);
      //delay(2);
    }
    //delay(200);
  //}
  lastState = currentState;

  if (schermata)
    showInterface1(angleX);
  else
    showInterface2(angleY);

  // parti finali in comune dei 2 loop
  txt.pushToSprite(&background,105,20,TFT_BLACK); // Posizione (x, y)

  txTemp.fillSprite(TFT_BLACK);
  txTemp.drawString(String(int(temp.temperature)) + " C", 0, 0, 2);
  txTemp.pushToSprite(&background,105,200,TFT_BLACK);

  background.pushSprite(0,0); // Stampa lo sfondo e i suoi insiemi
}

void showInterface1(int angleX) {
  sprite.pushRotated(&background,angleX,TFT_BLACK);
  txt.fillSprite(TFT_BLACK);
  txt.drawString(String(-angleX),0,0,4);
}

void showInterface2(int angleY) {
  spriteBack.pushRotated(&background,angleY,TFT_BLACK);
  txt.fillSprite(TFT_BLACK);
  txt.drawString(String(angleY),0,0,4);
}

void drawProgressBar(int x, int y, int width, int height, int progress) {
  int barWidth = (width - 2) * progress / 100;
  tft.drawRect(x, y, width, height, TFT_RED);
  tft.fillRect(x + 1, y + 1, barWidth, height - 2, TFT_WHITE);
}
