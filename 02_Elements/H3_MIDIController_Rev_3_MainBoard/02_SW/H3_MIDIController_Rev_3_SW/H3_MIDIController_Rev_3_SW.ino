// Name: H3_MIDIController_Rev_3_SW
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: July 2018
// Description: Test Code for H3_MIDIController_Rev_3 Board. Part of the Henar 3 project in which Autofabricantes collaborates.

// Library Import
#include <Adafruit_NeoPixel.h>
#include <MIDIUSB.h>
#include <Streaming.h>
// Header Custom Files
#include "H3_Configuration.h"


//# define SERIAL_DEBUG
//# define SERIAL_DEBUG_PZ
//# define SERIAL_DEBUG_PZ_FULL

Adafruit_NeoPixel ledPadStripe = Adafruit_NeoPixel(SW_Q, LED, NEO_RGB + NEO_KHZ800);

int ITER = 0;

void setup() {
  Serial.begin(115200);   // Baudrate Set
  ledPadStripe.begin();
  ledPadStripe.show();

  // Set Pin Modes
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_D, OUTPUT);

  //SW_LED_Initialization_Start(GEN_OFF);
  //PZ_PAD_Autocalibration();
  SW_LED_Initialization_End();

  /*for (int h = 0; h < PZ_Q; h++){
      ledPadStripe.setPixelColor(SWPZ_ROW[h].ledPos,255, 255, 255); // Heavy Stuff
     ledPadStripe.show(); // Update LEDs
      delay(1000);
  }*/
  
}

void loop() {
    if(ITER == 2){
      ITER = 0;
      SW_MODE.Val = readSW_ROW(SW_ROW_CD, (sizeof(SW_ROW_CD)/sizeof(SWPAD)), SW_MODE, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      //SW_INSTR.Val = readSW_ROW(SW_ROW_C, SW_INSTR, INSTR_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_OCTV.Val = readSW_ROW(SW_ROW_B, (sizeof(SW_ROW_B)/sizeof(SWPAD)), SW_OCTV, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_SCALE.Val = readSW_ROW(SW_ROW_A, (sizeof(SW_ROW_A)/sizeof(SWPAD)), SW_SCALE, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SWE = readSW_Single(SWE, PANIC_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SWF = readSW_Single(SWF, MENU_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
    
    }
    ITER++;
    SWPZ_Read(SWPZ_ROW, PZ_Q, INSTR_0, GEN_OFF, FADESTEPS_C, FADEDELAY_C);

    //Serial << (sizeof(SW_ROW_CD)/sizeof(SWPAD)) << endl;
}

int readSW_ROW(SWPAD SW_ROW[], int arraySize, SWCTRL SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){ // Should Remove arraySize somehow
  int prevON = SW_CTRL.Val;
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (analogRead(SW_ROW[i].muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated
          SW_CTRL.Val = i;                      // Set SW_MODE to that value
          SW_LED_ColumnFade(SW_ROW, SW_CTRL, prevON, COL_ON, COL_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
          CONFIG[SW_CTRL.ID].Val = SW_CTRL.Val;
#ifdef SERIAL_DEBUG 
          Serial << "SWPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
          Serial << "CTRL: " << SW_CTRL.ID << " Val: " << CONFIG[SW_CTRL.ID].Val << endl;
#else
          MIDI_TX(CONFIG[INSTR].Val, NOTE_ON, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][0]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 127);
          delay(NOTE_DURATION);
          MIDI_TX(CONFIG[INSTR].Val, NOTE_OFF, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][0]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 0);
#endif
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
       }
     }
  }
   return SW_CTRL.Val;
}

SWPAD readSW_Single(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (analogRead(SW_Pad.muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_LED_FadeSingle_FULL(SW_Pad, COL_ON, COL_OFF,  FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
      Serial << "SWPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
#else
      MIDI_TX(CONFIG[INSTR].Val, NOTE_ON, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][0]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 127);
      delay(NOTE_DURATION);
      MIDI_TX(CONFIG[INSTR].Val, NOTE_OFF, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][0]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 0);
#endif
    }
  }else{
   if (SW_Pad.swAct){                      // if SW Pad previously activated
     SW_Pad.swAct = OFF;                   // Set SW_Pad as ON
   }
  }
   return SW_Pad;
}

SWPAD SW_MENU_Read(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){ // Should Remove arraySize somehow
  SW_Pad = readSW_Single(SW_Pad, COL_ON, COL_OFF, fadeSteps, fadeDelay);
  if(Menu < MAX_MENU){
    Menu ++;
  }else{
    Menu = 0;
  }
  SW_MENU_Transition();
  return SW_Pad;
}

void SW_MENU_Transition(){
  if(Menu == 0){ // Transiopn from MENU MAX_MENU to MENU 0
    // Fade Out of MENU MAX_MENU


    // Fade In of MENU 0
  }
}

/*
void SW_PANIC_Read(int INIT_SW, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(INIT_SW);
  if (analogRead(MUX_1) < SW_THR) {    // If SW Pad activated
    if (!SW_CTRL[INIT_SW]) {            // if SW Pad not previously activated
      SW_CTRL[INIT_SW]=ON;
      //ledPadStripe.setPixelColor(SW_PANIC_INIT, PANIC_G_ON, PANIC_R_ON, PANIC_B_ON);   
      ledPadStripe.show(); // Update LEDs
      for(int i = 0; i < 8; i++){
        MIDI_TX(i, CONTROL, CTRL_NOTEOFF, 0);
      }
    }
  }else{
    if(SW_CTRL[INIT_SW]){
      SW_CTRL[INIT_SW]=OFF;
      //ledPadStripe.setPixelColor(SW_PANIC_INIT, (GEN_G_OFF+BIG_R), (GEN_R_OFF+BIG_G), (GEN_B_OFF+BIG_B));   
      ledPadStripe.show(); // Update LEDs
     }
   }    // Set SW_Pad as OFF 
}*/


// PZ_Pad Read Function

void SWPZ_Read(SWPAD SW_ROW[], int arraySize, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (analogRead(SW_ROW[i].muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated       
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
          Serial << "SWPZPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
#else
          MIDI_TX(CONFIG[INSTR].Val, NOTE_ON, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][i]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 127);
#endif    
          SW_LED_FadeSingle_UP(SW_ROW[i], COL_ON, COL_OFF,  fadeSteps, fadeDelay); // Update LED 
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
          Serial << "SWPZPAD OFF: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
#else
         MIDI_TX(CONFIG[INSTR].Val, NOTE_OFF, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][i]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), 0);
#endif  
         SW_LED_FadeSingle_DW(SW_ROW[i], COL_ON, COL_OFF,  fadeSteps, fadeDelay); // Update LED 
       }
     }
  }
  return 0;
}




void SW_LED_ColumnFade(SWPAD SW_ROW[], SWCTRL SW_CTRL, int prevON, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
  int RDiff = (COL_OFF.red-COL_ON.red);
  int GDiff = (COL_OFF.green-COL_ON.green);
  int BDiff = (COL_OFF.blue-COL_ON.blue);
  if(prevON >= SW_CTRL.Val){
    int i = 0; //Start of the Sequence
    for(int i = 0; i < (prevON - SW_CTRL.Val); i++){
      for(int h = 0; h <= FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[prevON-i].ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
        ledPadStripe.setPixelColor(SW_ROW[prevON-i-1].ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
  }else{
    for(int i = prevON; i <= SW_CTRL.Val; i++){
      for(int h = 0; h < FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[i].ledPos, (COL_OFF.green - ((GDiff/FS)*(h+1))), (COL_OFF.red - ((RDiff/FS)*(h+1))), (COL_OFF.blue - ((BDiff/FS)*(h+1))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
  }     
}

void SW_LED_FadeSingle_FULL(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h < (FS); h++){ // Fade to ON
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
    delay(5*FD);
    for(int h = 0; h < (FS); h++){ // Fade to OFF
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void SW_LED_FadeSingle_UP(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h < (FS); h++){ // Fade to ON
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void SW_LED_FadeSingle_DW(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h < (FS); h++){ // Fade to OFF
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void  SW_LED_Initialization_End(void){
  for (int h = 0; h < 5; h++){
    for (int i = 0; i < 120; i++){
      ledPadStripe.setPixelColor(SW_ROW_A[h].ledPos, (i*2), (i*2), (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[h].ledPos, (i*2), (i*2), (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[h].ledPos, (i*2), (i*2), (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[h].ledPos, (i*2), (i*2), (i*2)); // Heavy Stuff
      ledPadStripe.show(); // Update LEDs
      delay(2);
    }
  }

}

void  SW_LED_Initialization_Start(LEDCOL COL_ON){
/*  int FS = 255; // Fade Steps
  int RStep = COL_ON.red;
  int GStep = COL_ON.green;
  int BStep = COL_ON.blue;
  for (int i = 0; i < FS; i++){
    for (int h = 0; h < 5; h++){
      ledPadStripe.setPixelColor(SW_ROW_A[4-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[4-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[4-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[4-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff

      ledPadStripe.setPixelColor(SW_ROW_A[3-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[3-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[3-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[3-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff

      ledPadStripe.setPixelColor(SW_ROW_A[2-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[2-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[2-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[2-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff

      ledPadStripe.setPixelColor(SW_ROW_A[1-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[1-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[1-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[1-h].ledPos, (COL_ON.red/(FS-i)), (COL_ON.red/(FS-i)), 0); // Heavy Stuff

      
      ledPadStripe.show(); // Update LEDs
      delay(1);
    }
  }

  for (int i = 0; i < 120; i++){    // Canvas SW OFF
    ledPadStripe.setPixelColor(SWE.ledPos, (i*2), 0, 0); // Heavy Stuffç
    ledPadStripe.setPixelColor(SWF.ledPos, (i*2), 0, 0); // Heavy Stuffç
    ledPadStripe.show(); // Update LEDs
    delay(5);
  }
*/
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

void SET_MUXGATE(int GATENUM){
  for (int h = 0; h < 4; h++) {
      digitalWrite(muxSel[h], ((GATENUM >> (3 - h)) & 0x01)); //MUX Setup pin for each MUX Pin
  }
  delay(10); // Delay por MUX Setup
}

