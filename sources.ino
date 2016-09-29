#include <Wire.h>
#include "rgb_lcd.h"

// LCD CONSTANTS BEGIN
rgb_lcd lcd;

const int colorR = 30;
const int colorG = 30;
const int colorB = 100;

// BUTTON VAR BEGIN
const int buttonPin = 3;
int actualButtonState = 0;
int lastButtonState = 0;

// SENSOR VAR BEGIN
const int sensorPin = 4;

//BUZZER VAR
const int buzzerPin = 2;
int actualBuzzerState = 0;
int lastBuzzerState = 0;

// TEMPORAL VAR BEGIN
int itterationDelay = 500; 

int numberOfitteration = 0;
int numberOfElapsedSecondsSinceLastReset = 0;
int lastScoredSecond = 0;
int reamainingSeconds = 0;

int moneyTimeBegin = 15;
int secondsOfARound = 60;

//ROUND VAR
int score = 0;
boolean roundIsRunning = false;

void setup() {
  lcd.begin(32, 2);  
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Lancer la partie");
}

void loop() {
  if(roundIsRunning){
    if( (secondsOfARound - numberOfElapsedSecondsSinceLastReset) <= 0){
      endRound();
    }else{
      itterateRound();
    }
  }else{
    if(digitalRead(buttonPin) == HIGH){
      resetVars();
      lcd.clear();
      lcd.print("Get ready !");
      delay(1500);
      roundIsRunning = true;
    }
  }
  
  delay(itterationDelay);
}

void itterateRound(){
  countSeconds();
  readSensorState();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temps restant:");
  lcd.setCursor(14, 0);
  lcd.print(reamainingSeconds);

  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(7, 1);
  lcd.print(score);

  if(reamainingSeconds - moneyTimeBegin <= 0){
    lcd.setRGB(200, colorG, colorB);
    bipbip();
  }
  
  numberOfitteration++;
}

void endRound(){
  stopBuzzer();
  lcd.setRGB(colorR, 150, colorB);
  lcd.clear();
  lcd.print("Score final:");
  lcd.setCursor(13, 1);
  lcd.print(score);

  lcd.setCursor(0, 1);
  lcd.print("Rejouer");
  
  roundIsRunning = false;
}

void readSensorState(){
   actualButtonState = digitalRead(sensorPin);
   //lastScoredSecond;
   //numberOfElapsedSecondsSinceLastReset
   if (actualButtonState == HIGH ) {
    if( (numberOfElapsedSecondsSinceLastReset - lastScoredSecond) > 3){
      lastScoredSecond = numberOfElapsedSecondsSinceLastReset;
      score++;
    }
   }
}

void bipbip(){
   actualBuzzerState = digitalRead(buzzerPin);
    
   if (actualBuzzerState == HIGH) {
    stopBuzzer();
   }else{
    digitalWrite(buzzerPin, HIGH);
   }
}

void stopBuzzer(){
  digitalWrite(buzzerPin, LOW);
}

void resetVars(){
  numberOfElapsedSecondsSinceLastReset = 0;
  reamainingSeconds = 0;
  numberOfitteration = 0;
  lastScoredSecond = 0;
  score = 0;
  roundIsRunning = false;
  lcd.setRGB(colorR, colorG, colorB);
}

void countSeconds() {
    reamainingSeconds = secondsOfARound - numberOfElapsedSecondsSinceLastReset;
    numberOfElapsedSecondsSinceLastReset = numberOfitteration / (1000 / itterationDelay);
}



