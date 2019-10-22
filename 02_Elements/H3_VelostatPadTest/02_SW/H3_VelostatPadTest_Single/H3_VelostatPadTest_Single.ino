/*
 * @author Pablo dMM (Pablodmm.isp@gmail.com)
 * @brief This code controls a single Velostat Pad to be tested
 * @date 2019_10_21
 */
 
// Library Import
#include <Streaming.h>
#include <MIDIUSB.h>
//#include <tone.h>


#ifdef __AVR__
  #include <avr/power.h>
#endif

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------System Pin Definition-----------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Pin Definition
const int PAD_PIN         = A0;
const int POT_PIN         = A3;
const int LED_R           = 6;
const int LED_G           = 8;
const int LED_Y           = 7;
const int BUZZ            = 9;

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Control and Configuration values Definition-------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Constant Value Definition
const int LEDn                  = 3;
const int LEDBoometer[LEDn]     = {LED_G, LED_Y, LED_R};

const int Buzzn                 = 5;
const int BuzzBoometer[Buzzn]   = {33, 65, 131, 262, 523};

const int OFF                   = 0;
const int ON                    = 1;
const int NOTEDURATION          = 200;
const int nMEASURES             = 15;

// FIRST BYTE GENERAL
const byte NOTE_ON              = 144;
const byte NOTE_OFF             = 128;
const byte CONTROL              = 176;

// SECOND BYTE GENERAL 
const byte CTRL_VOL             =   7;
const byte CTRL_MOD             =   1;
const byte CTRL_EFCT1           =  12;
const byte CTRL_EFCT2           =  13;
const byte CTRL_NOTEOFF         = 123;

// MIDI NOTES
const byte NOTE_C6              = 72;


// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Custom Configuration Structs----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Global Variables----------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
int lastMeasures[nMEASURES];
int modeTrigger = OFF;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  for(int i= 0; i < LEDn; i++){
    pinMode(LEDBoometer[i], OUTPUT);
  }
  pinMode(PAD_PIN, INPUT);
  // Adequation
  for(int h = 0; h < 2*nMEASURES; h++){
    updateMeasureArray(analogRead(PAD_PIN));
    delay(10);
  }
  //tone(BUZZ, BuzzBoometer[0], 200);
  //tone(BUZZ, BuzzBoometer[2], 200);
  tone(BUZZ, BuzzBoometer[4], 500);
}

void loop() {
  int newRead = analogRead(PAD_PIN);
  int thr = map(analogRead(POT_PIN), 0, 1024, 0, 500);
  int avgLevel = calculateMeasureArray();
  //Serial <<"NEW: " << newRead << " AVG:" << avgLevel << " DIFF: " << (newRead - avgLevel) << "/" << thr << endl;
  
  switch(modeTrigger){
    case ON:
      boometerLed(map(newRead, (avgLevel + thr), 1024, 1, LEDn));
      if((newRead - avgLevel) < thr){
        //Serial <<"OFF----------------------------------------------------------------------" << endl;
        modeTrigger = OFF;
        MIDI_TX(0, NOTE_OFF, NOTE_C6, 0);
        playBuzzer(1, NOTEDURATION, BuzzBoometer[4]);
      }
      break;
    default: // off
      boometerLed(0);
      updateMeasureArray(newRead);
      if((newRead - calculateMeasureArray()) > thr){
        //Serial <<"ON----------------------------------------------------------------------" << endl;
        modeTrigger = ON;
        MIDI_TX(0, NOTE_ON, NOTE_C6, map(newRead, (avgLevel + thr), 1024, 0, 127));
        playBuzzer(1, NOTEDURATION, BuzzBoometer[0]);
      }
      break;
  }
  delay(10);
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

void playBuzzer(bool enable, int duration, int note){
  if(enable){
    tone(BUZZ, note, duration);
  }else{
    digitalWrite(BUZZ, LOW);
  }
}

void boometerLed(int level){
  if(level > 2){
    level = LEDn - 1;
  }
  for(int i = 0; i < LEDn; i++){
    digitalWrite(LEDBoometer[i], LOW);
  }
  for(int h = 0; h <= level; h++){
    digitalWrite(LEDBoometer[h], HIGH);
  }
}

void MIDI_TX(byte MIDICHANNEL, byte MESSAGE, byte PITCH, byte VELOCITY) {
  //byte status1 = MESSAGE + MIDICHANNEL;
  //Serial.write(MESSAGE + MIDICHANNEL);
  //Serial.write(PITCH);
  //Serial.write(VELOCITY);
  midiEventPacket_t event = {(byte)(MESSAGE >> 4), (byte)(MESSAGE | (MIDICHANNEL)), PITCH, VELOCITY};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void MIDIOFF_FIX(byte CHANNEL, int INIT_NOTE, int END_NOTE){ // This is a very rude and nasty sustitution to a General Note Off CMD
  for(int i= INIT_NOTE; i <= END_NOTE; i++){
    MIDI_TX(CHANNEL, NOTE_OFF, i, 0);
    delay(10);
  }
}
