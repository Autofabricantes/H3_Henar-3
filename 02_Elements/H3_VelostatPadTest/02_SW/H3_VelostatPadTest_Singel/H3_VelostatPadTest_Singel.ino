/*
 * @author Pablo dMM (Pablodmm.isp@gmail.com)
 * @brief This code controls a Winged LED Suit for LATE Lab
 */
 
// Library Import
#include <Adafruit_NeoPixel.h>
#include <Streaming.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------System Pin Definition-----------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Pin Definition

const int SW_00_PIN       = 4;
const int MIC             = A4;
const int LEDCore_PIN     = 2;
const int LEDWings_PIN    = 3;

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Control and Configuration values Definition-------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Constant Value Definition

const int LEDCore_Q       = 20;
const int LEDWings_Q      = 144;

const int OFF             = 0;
const int ON              = 1;

const int nMODES          = 4;

const int MODE_FULLON     = 0;
const int MODE_FULLOFF    = 1;
const int MODE_FLASH      = 2;
const int MODE_GLOW       = 3;

const int FLASH_STEP_MS   = 200;  // Steps for Flash Delay

const int GLOW_STEP_MS   = 50;  // Steps for Flash Delay
// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Custom Configuration Structs----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Generated Structures (struct)
struct SWctrl{
  int   swPin;
  bool  swLastValue;
};

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Global Variables----------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Generated Structures (struct)

// Switch Controller Inizialization
SWctrl SW_00 = {SW_00_PIN, OFF};

int MIC_THR = 20;
const int nMEASURES = 15;

int programMode = MODE_FULLON;
int iterator              = 0;
long iterTime             = 0;
int lastMeasures[nMEASURES];

// LED Stripes
Adafruit_NeoPixel LEDCore = Adafruit_NeoPixel(LEDCore_Q, LEDCore_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel LEDWings = Adafruit_NeoPixel(LEDWings_Q, LEDWings_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(SW_00_PIN, INPUT);
  LEDCore.begin(); // This initializes the NeoPixel library.
  LEDWings.begin(); // This initializes the NeoPixel library.
}

void loop() {
  switch(programMode){
    case(MODE_FULLON):
      //actionLED_SetColor(&LEDWings, 255, 255, 255);
      actionLED_SetColor(&LEDCore, 255, 255, 255);
      
      break;

    case (MODE_FULLOFF):
      //actionLED_SetColor(&LEDWings, 0, 0, 0);
      actionLED_SetColor(&LEDCore, 0, 0, 0);
      break;

    case(MODE_FLASH):
      //actionLED_SetColor(&LEDWings, 255, 255, 255);
      actionLED_SetColor(&LEDCore, 255, 255, 255);
      delay(100);
      //actionLED_SetColor(&LEDWings, 0, 0, 0);
      actionLED_SetColor(&LEDCore, 0, 0, 0);
      break;
    case(MODE_GLOW):
      if((millis() - iterTime) >= GLOW_STEP_MS){
        iterTime = millis();
        if(iterator < LEDWings.numPixels()){
          iterator = iterator + 2;
        }else{
          iterator = 0;
        }
        actionLED_Glow(&LEDWings, 255, 255, 255, iterator, 20);
      }
        
      break;

    default:
      break;
  }
  
  int newMicRead = analogRead(MIC);
  int oldMicAverage = calculateMeasureArray();
  updateMeasureArray(newMicRead);
  
  //Serial << "[OLD] " << oldMicAverage  << " [NEW] " << newMicRead << endl;
  Serial.println(oldMicAverage - newMicRead);

  if(((newMicRead < (oldMicAverage - MIC_THR)) || (newMicRead > (oldMicAverage + MIC_THR))) && (programMode == MODE_FULLOFF)){
    programMode = MODE_FULLON;
    
    //MIC_THR = 30;
  }else if (programMode == MODE_FULLON){
    delay(200);
    programMode = MODE_FULLOFF;
  }

  
}


int actionLED_SetColor(Adafruit_NeoPixel *LED, int R, int G, int B){
  //Serial << "[actionLED_SetColor] << endl;
  for(int i=0; i< LED->numPixels(); i++) {
    LED->setPixelColor(i, R, G, B);  
  }
  LED->show();
}

int actionLED_Flash(Adafruit_NeoPixel *LED, int R, int G, int B, int iter){
  //Serial << "[actionLED_Flash] Recieved: Iter:" << iter << endl;
  if(iter){
    actionLED_SetColor(LED, 0, 0, 0);
  }else{
    actionLED_SetColor(LED, R, G, B);
  }
}

int actionLED_Glow(Adafruit_NeoPixel *LED, int R, int G, int B, int iter, int range){
  //Serial << "[actionLED_Flash] Recieved: Iter:" << iter << endl;
  actionLED_SetColor(LED, 0, 0, 0);

  for(int i = 0; i < range; i++){
    LED->setPixelColor(iter - i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter + i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter, R, G, B);
  }

  for(int i = (range*3); i < ((range*3) + range); i = i+2){
    LED->setPixelColor(iter - i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter + i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter, R, G, B);
  }

  for(int i = (range*6); i < ((range*6) + range); i = i+2){
    LED->setPixelColor(iter - i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter + i, ((R/range) * (range - i)), ((R/range) * (range - i)), ((R/range) * (range - i)));
    LED->setPixelColor(iter, R, G, B);
  }
  LED->show();
}

bool readSW(SWctrl *SW){
  bool newValue = digitalRead(SW->swPin);
  bool funcResponse = OFF;
  if(newValue != SW->swLastValue){
    SW->swLastValue = newValue;
    if(newValue == ON){
      Serial.println("The button was pressed!");
      funcResponse = ON;
    }
  }
  return funcResponse;
}

int updateMeasureArray(int newValue){
  //lastMeasures[0] = newValue;
  for(int i = 0; i < nMEASURES; i++){
    lastMeasures[i + 1] = lastMeasures[i];
  }
  lastMeasures[0] = newValue;
}

int calculateMeasureArray(){
  int averageValue = 0;
  for(int i = 0; i < nMEASURES; i++){
    averageValue = (averageValue + lastMeasures[i]);
  }
  return (averageValue / nMEASURES);
}
