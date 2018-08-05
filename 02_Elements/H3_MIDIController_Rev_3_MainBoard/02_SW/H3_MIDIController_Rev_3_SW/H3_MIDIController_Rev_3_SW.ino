// Name: H3_MIDIController_Rev_3_SW
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: July 2018
// Description: Test Code for H3_MIDIController_Rev_3 Board. Part of the Henar 3 project in which Autofabricantes collaborates.

// Library Import
#include <Adafruit_NeoPixel.h>
#include <MIDIUSB.h>
#include <Streaming.h>
#include <EEPROM.h>
// Header Custom Files
#include "H3_Configuration.h"
#include "EEPROMAnything.h"

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

  // Param Initialization

  // LED Start Routine
  SW_LED_Initialization_Start();
  SW_INSTR = readSW_ROW_INSTR(SWPZ_ROW, PZ_Q, SW_INSTR, INSTR_COL, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
  EEPROM_readConfig(SW_INSTR);

/*EEPROM_saveConfigFS(0);
EEPROM_saveConfigFS(1);
EEPROM_saveConfigFS(2);
EEPROM_saveConfigFS(3);
EEPROM_saveConfigFS(4);
EEPROM_saveConfigFS(5);
EEPROM_saveConfigFS(6);*/

  
  SW_LED_Initialization_End();
  
  // Param Initialization
  Velocity = map(SW_VEL, 0, 4, 10, 127);
  
  fadeIN_SW_MENU0();
}

void loop() {
   switch(SW_MENU){
      case 0:
        readSW_MENU0();
        break;
      case 1:
        readSW_MENU1();
        break;
      default:
        break;
   }
   SWE = readSW_SW_MENU(SWE, GEN_OFF, INSTR_COL[SW_INSTR], FADESTEPS_C, FADEDELAY_C);
   SWF = readSW_PANIC(SWF, RESET_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SWPZ_Read(SWPZ_ROW, PZ_Q, INSTR_COL[SW_INSTR], GEN_OFF, FADESTEPS_C, FADEDELAY_C);
}

void readSW_MENU0(void){
   SW_MODE  = readSW_ROW(SW_ROW_CD2, (sizeof(SW_ROW_CD2)/sizeof(SWPAD)), SW_MODE, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_OCTV  = readSW_ROW(SW_ROW_A, (sizeof(SW_ROW_A)/sizeof(SWPAD)), SW_OCTV, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_SEQ  = readSW_Binary(SWB2, SW_SEQ, SEQ_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_VSWAP = readSW_Binary(SWB3, SW_VSWAP, VSWAP_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_CHORD = readSW_Binary(SWB4, SW_CHORD, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
}

void fadeOUT_SW_MENU0(void){
   if(SW_CHORD){SW_LED_FadeSingle_DW(SWB4, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_VSWAP){SW_LED_FadeSingle_DW(SWB3, VSWAP_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_SEQ){SW_LED_FadeSingle_DW(SWB2, SEQ_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   SW_LED_ColumnFade(SW_ROW_CD2, 0, SW_MODE, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_A, 0, SW_OCTV, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
}

void fadeIN_SW_MENU0(void){
   SW_LED_ColumnFade(SW_ROW_CD2, SW_MODE, 0, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_A, SW_OCTV, 0, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   if(SW_SEQ){SW_LED_FadeSingle_UP(SWB2, SEQ_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_VSWAP){SW_LED_FadeSingle_UP(SWB3, VSWAP_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_CHORD){SW_LED_FadeSingle_UP(SWB4, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
}

void readSW_MENU1(void){
   SW_VEL   = readSW_ROW(SW_ROW_A, (sizeof(SW_ROW_A)/sizeof(SWPAD)), SW_VEL, VEL_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_SCALE = readSW_ROW(SW_ROW_B, (sizeof(SW_ROW_B)/sizeof(SWPAD)), SW_SCALE, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_CHORDTYPE = readSW_ROW(SW_ROW_C, (sizeof(SW_ROW_C)/sizeof(SWPAD)), SW_CHORDTYPE, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_SDBG  = readSW_Binary(SWD4, SW_SDBG, SDBG_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_FRST  = readSW_Binary(SWD3, SW_FRST, FRST_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   Velocity = map(SW_VEL, 0, 4, 10, 127);
}

void fadeOUT_SW_MENU1(void){
   if(SW_SDBG){SW_LED_FadeSingle_DW(SWD4, SDBG_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_FRST){SW_LED_FadeSingle_DW(SWD3, FRST_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   SW_LED_ColumnFade(SW_ROW_A, 0, SW_VEL, VEL_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_B, 0, SW_SCALE, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_C, 0, SW_CHORDTYPE, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
}

void fadeIN_SW_MENU1(void){
   SW_LED_ColumnFade(SW_ROW_C, SW_CHORDTYPE,0, CHORD_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_B, SW_SCALE, 0, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   SW_LED_ColumnFade(SW_ROW_A, SW_VEL, 0, VEL_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   delay(50);
   if(SW_FRST){SW_LED_FadeSingle_UP(SWD3, FRST_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
   if(SW_SDBG){SW_LED_FadeSingle_UP(SWD4, SDBG_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);}
   delay(50);
}

int readSW_ROW(SWPAD SW_ROW[], int arraySize, int SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){ // Should Remove arraySize somehow
  int prevON = SW_CTRL;
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (!digitalRead(SW_ROW[i].muxID)){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated
          SW_CTRL = i;                      // Set SW_MODE to that value
          SW_LED_ColumnFade(SW_ROW, SW_CTRL, prevON, COL_ON, COL_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
if(SW_SDBG){ 
          Serial << "SWPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
}else{
          MIDI_TX(SW_INSTR, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE][0] + SW_MODE+(12*SW_OCTV)), (Velocity-((Velocity/2)*SW_VSWAP)));
          delay(NOTE_DURATION);
          MIDI_TX(SW_INSTR, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE][0] + SW_MODE+(12*SW_OCTV)), 0);
}
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
       }
     }
  }
   return SW_CTRL;
}

SWPAD readSW_Single(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
if(SW_SDBG){ 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
}
      SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
    }
  }else{
   if (SW_Pad.swAct){                      // if SW Pad previously activated
     SW_Pad.swAct = OFF;                   // Set SW_Pad as ON
     SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
   }
  }
   return SW_Pad;
}

int readSW_ROW_INSTR(SWPAD SW_ROW[], int arraySize, int SW_CTRL, LEDCOL COL_ON[], LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  int prevON = SW_CTRL;
  bool instrSel = OFF;
  for(int i = 0; i < arraySize; i++){ 
    ledPadStripe.setPixelColor(SW_ROW[i].ledPos, COL_ON[i].green, COL_ON[i].red, COL_ON[i].blue);
    ledPadStripe.show(); // Update LEDs
    delay(FD);
  }

  while(!instrSel){
   for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (!digitalRead(SW_ROW[i].muxID)){    // If SW Pad activated // TODO Change to digitalRead()
       instrSel = ON;
       SW_CTRL = i;                      // Set SW_MODE to that value
        }
     }
  }

  for(int i = 0; i < arraySize; i++){ 
    ledPadStripe.setPixelColor(SW_ROW[i].ledPos, COL_ON[SW_CTRL].green, COL_ON[SW_CTRL].red, COL_ON[SW_CTRL].blue);
    ledPadStripe.show(); // Update LEDs
  }

  delay(FD*FS);

  for(int i = 0; i < arraySize; i++){ 
    ledPadStripe.setPixelColor(SW_ROW[i].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue);
    ledPadStripe.show(); // Update LEDs
  }
  
  return SW_CTRL;
}

void SW_SW_MENU_Transition(int newSW_MENU){
  if(newSW_MENU == 1){ // Transiopn from SW_MENU MAX_SW_MENU to SW_MENU 0
    fadeOUT_SW_MENU0();
    SW_LED_CleanCanvas(GEN_OFF);
    delay(100);
    fadeIN_SW_MENU1();
  }else if(newSW_MENU == 0){
    fadeOUT_SW_MENU1();
    SW_LED_CleanCanvas(GEN_OFF);
    delay(100);
    fadeIN_SW_MENU0();
  }
}

int readSW_Binary(SWPAD SW_Pad, int SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_CTRL){                      // if SW_CTRL is OFF
      SW_CTRL = ON;                    // Set SW_Pad as ON
      SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
if(SW_SDBG){ 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
      Serial << "Option turned ON" << endl;
}
    }else{
      SW_CTRL = OFF;                    // Set SW_Pad as ON
      SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
if(SW_SDBG){ 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
      Serial << "Option turned OFF" << endl;
}
    
    }
    delay(100);   
  }
   return SW_CTRL;
}

SWPAD readSW_PANIC(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
      SW_Time_Start = millis();
      SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
if(SW_SDBG){ 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
      Serial << "Start Mute and Reset routine" << endl;
}
      
    }
  }else{
   if (SW_Pad.swAct){                      // if SW Pad previously activated
     SW_Pad.swAct = OFF;                   // Set SW_Pad as ON
     SW_Time_Current = millis();
     if((SW_Time_Current - SW_Time_Start) > TIME_PANIC_MS){
        SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
        delay(100);
        SW_LED_FadeSingle_UP(SW_Pad, SAVE_ON, COL_OFF,  FS, FD); // Update LED Stripe
        if(SW_FRST){EEPROM_factoryReset();} // Save Factory Reset Settings for all INSTR Channels
        muteChannel(SW_INSTR, FD);
        SW_LED_FadeSingle_DW(SW_Pad, SAVE_ON, COL_OFF,  FS, FD); // Update LED Stripe
        SW_LED_ShutDown();
        resetMachine();
     }
     SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
   }
  }
   return SW_Pad;
}

SWPAD readSW_SW_MENU(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
      SW_Time_Start = millis();
      SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
if(SW_SDBG){ 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
      Serial << "SW_MENU Change" << endl;
}
      
    }
  }else{
   if (SW_Pad.swAct){                      // if SW Pad previously activated
     SW_Pad.swAct = OFF;                   // Set SW_Pad as ON
     SW_Time_Current = millis();
     if((SW_Time_Current - SW_Time_Start) > TIME_PANIC_MS){
        SW_LED_FadeSingle_DW(SW_Pad, SAVE_ON, COL_OFF,  FS, FD); // Update LED Stripe
        EEPROM_saveConfig(SW_INSTR);
        delay(100);
        SW_LED_FadeSingle_DW(SW_Pad, SAVE_ON, COL_OFF,  FS, FD); // Update LED Stripe
        SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
     }else{
        if (SW_MENU < MENU_Q){
          SW_MENU++;
        }else{
          SW_MENU = 0;
        }
        SW_SW_MENU_Transition(SW_MENU);
     }
     SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
     SW_LED_FadeSingle_DW(SW_Pad, COL_OFF, COL_OFF,  FS, FD); // Update LED Stripe
   }
  }
   return SW_Pad;
}

void SWPZ_Read(SWPAD SW_ROW[], int arraySize, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (!digitalRead(SW_ROW[i].muxID)){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated       
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
          if(SW_SDBG){ 
            Serial << "SWPZPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
          }else{
            if(!SW_CHORD){
              MIDI_TX(SW_INSTR, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)), (Velocity-((Velocity/2)*SW_VSWAP)));
            }else{
              MIDI_TX(SW_INSTR, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][0]), (Velocity-((Velocity/2)*SW_VSWAP)));
              MIDI_TX(SW_INSTR, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][1]), (Velocity-((Velocity/2)*SW_VSWAP)));
              MIDI_TX(SW_INSTR, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][2]), (Velocity-((Velocity/2)*SW_VSWAP)));
            }
          }    
          SW_LED_FadeSingle_UP(SW_ROW[i], COL_ON, COL_OFF,  fadeSteps, fadeDelay); // Update LED 
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
         if(SW_SDBG){ 
          Serial << "SWPZPAD OFF: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;      
         }else{
            if(!SW_CHORD){
              MIDI_TX(SW_INSTR, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)), 0);
            }else{
              MIDI_TX(SW_INSTR, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][0]), 0);
              MIDI_TX(SW_INSTR, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][1]), 0);
              MIDI_TX(SW_INSTR, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE][i]+SW_MODE+(12*SW_OCTV)+CHORDS[SW_CHORDTYPE][2]), 0);
            }
         }  
         SW_LED_FadeSingle_DW(SW_ROW[i], COL_ON, COL_OFF,  fadeSteps, fadeDelay); // Update LED 
       }
     }
  }
  return 0;
}

void muteChannel(int CHANNEL, int DELAY){
  for(int i = 0; i < 127; i++){      // Manual NOTE_OFF to all the CHANNEL Notes
    MIDI_TX(CHANNEL, NOTE_OFF, i, 0);
    delay(DELAY);
  }
}

void resetMachine(void){
  asm volatile ("  jmp 0"); 
}

void SW_LED_ColumnFade(SWPAD SW_ROW[], int SW_CTRL, int prevON, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
  int RDiff = (COL_OFF.red-COL_ON.red);
  int GDiff = (COL_OFF.green-COL_ON.green);
  int BDiff = (COL_OFF.blue-COL_ON.blue);
  if(prevON >= SW_CTRL){
    int i = 0; //Start of the Sequence
    for(int i = 0; i < (prevON - SW_CTRL); i++){
      for(int h = 0; h <= FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[prevON-i].ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
        ledPadStripe.setPixelColor(SW_ROW[prevON-i-1].ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
  }else{
    for(int i = prevON; i <= SW_CTRL; i++){
      for(int h = 0; h < FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[i].ledPos, (COL_OFF.green - ((GDiff/FS)*(h+1))), (COL_OFF.red - ((RDiff/FS)*(h+1))), (COL_OFF.blue - ((BDiff/FS)*(h+1))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
  }
  if((!prevON) && (!SW_CTRL)){  // Quick Fix, not relatable at all
    SW_LED_FadeSingle_UP(SW_ROW[0], COL_ON, COL_OFF, FS, FD);
  }
}

void SW_LED_FadeSingle_FULL(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h <= (FS); h++){ // Fade to ON
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
    delay(5*FD);
    for(int h = 0; h <= (FS); h++){ // Fade to OFF
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void SW_LED_FadeSingle_UP(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h <= (FS); h++){ // Fade to ON
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(h))), (COL_OFF.red - ((RDiff/FS)*(h))), (COL_OFF.blue - ((BDiff/FS)*(h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void SW_LED_FadeSingle_DW(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
    int RDiff = (COL_OFF.red-COL_ON.red);
    int GDiff = (COL_OFF.green-COL_ON.green);
    int BDiff = (COL_OFF.blue-COL_ON.blue);
    for(int h = 0; h <= (FS); h++){ // Fade to OFF
      ledPadStripe.setPixelColor(SW_Pad.ledPos, (COL_OFF.green - ((GDiff/FS)*(FS-h))), (COL_OFF.red - ((RDiff/FS)*(FS-h))), (COL_OFF.blue - ((BDiff/FS)*(FS-h))));
      ledPadStripe.show(); // Update LEDs
      delay(FD);
    }
}

void SW_LED_CleanCanvas(LEDCOL COL_OFF){
  for (int h = 0; h < 5; h++){
    ledPadStripe.setPixelColor(SW_ROW_A[h].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue); // Heavy Stuff
    ledPadStripe.setPixelColor(SW_ROW_B[h].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue); // Heavy Stuff
    ledPadStripe.setPixelColor(SW_ROW_C[h].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue); // Heavy Stuff
    ledPadStripe.setPixelColor(SW_ROW_D[h].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue); // Heavy Stuff
  }  
  ledPadStripe.show(); // Update LEDs
}

void  SW_LED_Initialization_Start(void){
  ledPadStripe.setPixelColor(SWE.ledPos, 255, 255, 255); // Heavy Stuff
  ledPadStripe.setPixelColor(SWF.ledPos, 255, 255, 255); // Heavy Stuff
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

void  SW_LED_ShutDown(void){
  for (int h = 0; h < 5; h++){
    for (int i = 0; i < 120; i++){
      ledPadStripe.setPixelColor(SW_ROW_A[4-h].ledPos, 255-(i*2), 255-(i*2), 255-(i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[4-h].ledPos, 255-(i*2), 255-(i*2), 255-(i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[4-h].ledPos, 255-(i*2), 255-(i*2), 255-(i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[4-h].ledPos, 255-(i*2), 255-(i*2), 255-(i*2)); // Heavy Stuff
      ledPadStripe.show(); // Update LEDs
      delay(2);
    }
  }
}

void  SW_LED_Initialization_End(void){
  SW_LED_FadeSingle_UP(SWE, INSTR_COL[SW_INSTR], GEN_OFF,  FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
}

void  EEPROM_saveConfig(int INSTR){
  int EEPROMdir = (INSTR_BLOCK*INSTR);
  EEPROM_writeAnything((EEPROMdir), SW_MODE);
  Serial << "write SW_MODE: " << SW_MODE << " EEPROM POS: " << EEPROMdir << endl;      
  EEPROM_writeAnything((EEPROMdir+8), SW_SCALE);
  Serial << "write SW_SCALE: " << SW_SCALE << " EEPROM POS: " << EEPROMdir+8 << endl;      
  EEPROM_writeAnything((EEPROMdir+12), SW_SEQ);
  Serial << "write SW_SEQ: " << SW_SEQ << " EEPROM POS: " << EEPROMdir+12 << endl;      
  EEPROM_writeAnything((EEPROMdir+16), SW_OCTV);
  Serial << "write SW_OCTV: " << SW_OCTV << " EEPROM POS: " << EEPROMdir+16 << endl;      
  EEPROM_writeAnything((EEPROMdir+20), SW_VEL);
  Serial << "write SW_VEL: " << SW_VEL << " EEPROM POS: " << EEPROMdir+20 << endl;      
  EEPROM_writeAnything((EEPROMdir+24), SW_VSWAP);
  Serial << "write SW_VSWAP: " << SW_VSWAP << " EEPROM POS: " << EEPROMdir+24 << endl;      
  EEPROM_writeAnything((EEPROMdir+28), SW_SDBG);
  Serial << "write SW_SDBG: " << SW_SDBG << " EEPROM POS: " << EEPROMdir+28 << endl;      
  EEPROM_writeAnything((EEPROMdir+32), SW_CHORD);
  Serial << "write SW_CHORD: " << SW_CHORD << " EEPROM POS: " << EEPROMdir+32 << endl;      
  EEPROM_writeAnything((EEPROMdir+36), SW_CHORDTYPE); 
  Serial << "write SW_CHORDTYPE: " << SW_CHORDTYPE << " EEPROM POS: " << EEPROMdir+36 << endl;  
}

void  EEPROM_saveConfigFS(int INSTR){
  int EEPROMdir = (INSTR_BLOCK*INSTR);
  EEPROM_writeAnything((EEPROMdir), FRST_MODE);
  Serial << "write FRST_MODE: " << FRST_MODE << " EEPROM POS: " << EEPROMdir << endl;      
  EEPROM_writeAnything((EEPROMdir+8), FRST_SCALE);
  Serial << "write FRST_SCALE: " << FRST_SCALE << " EEPROM POS: " << EEPROMdir+8 << endl;      
  EEPROM_writeAnything((EEPROMdir+12), FRST_SEQ);
  Serial << "write FRST_SEQ: " << FRST_SEQ << " EEPROM POS: " << EEPROMdir+12 << endl;      
  EEPROM_writeAnything((EEPROMdir+16), FRST_OCTV);
  Serial << "write FRST_OCTV: " << FRST_OCTV << " EEPROM POS: " << EEPROMdir+16 << endl;      
  EEPROM_writeAnything((EEPROMdir+20), FRST_VEL);
  Serial << "write FRST_VEL: " << FRST_VEL << " EEPROM POS: " << EEPROMdir+20 << endl;      
  EEPROM_writeAnything((EEPROMdir+24), FRST_VSWAP);
  Serial << "write FRST_VSWAP: " << FRST_VSWAP << " EEPROM POS: " << EEPROMdir+24 << endl;      
  EEPROM_writeAnything((EEPROMdir+28), FRST_SDBG);
  Serial << "write FRST_SDBG: " << FRST_SDBG << " EEPROM POS: " << EEPROMdir+28 << endl;      
  EEPROM_writeAnything((EEPROMdir+32), FRST_CHORD);
  Serial << "write FRST_CHORD: " << FRST_CHORD << " EEPROM POS: " << EEPROMdir+32 << endl;      
  EEPROM_writeAnything((EEPROMdir+36), FRST_CHORDTYPE); 
  Serial << "write FRST_CHORDTYPE: " << FRST_CHORDTYPE << " EEPROM POS: " << EEPROMdir+36 << endl;   
}

void EEPROM_factoryReset(){
  for(int i = 0; i < PZ_Q; i++){
    EEPROM_saveConfigFS(i);
  }
}

void  EEPROM_readConfig(int INSTR){
  int EEPROMdir = (INSTR_BLOCK*INSTR);
  EEPROM_readAnything((EEPROMdir), SW_MODE);
  Serial << "Read SW_MODE: " << SW_MODE << " EEPROM POS: " << EEPROMdir << endl;      
  EEPROM_readAnything((EEPROMdir+8), SW_SCALE);
  Serial << "Read SW_SCALE: " << SW_SCALE << " EEPROM POS: " << EEPROMdir+8 << endl;      
  EEPROM_readAnything((EEPROMdir+12), SW_SEQ);
  Serial << "Read SW_SEQ: " << SW_SEQ << " EEPROM POS: " << EEPROMdir+12 << endl;      
  EEPROM_readAnything((EEPROMdir+16), SW_OCTV);
  Serial << "Read SW_OCTV: " << SW_OCTV << " EEPROM POS: " << EEPROMdir+16 << endl;      
  EEPROM_readAnything((EEPROMdir+20), SW_VEL);
  Serial << "Read SW_VEL: " << SW_VEL << " EEPROM POS: " << EEPROMdir+20 << endl;      
  EEPROM_readAnything((EEPROMdir+24), SW_VSWAP);
  Serial << "Read SW_VSWAP: " << SW_VSWAP << " EEPROM POS: " << EEPROMdir+24 << endl;      
  EEPROM_readAnything((EEPROMdir+28), SW_SDBG);
  Serial << "Read SW_SDBG: " << SW_SDBG << " EEPROM POS: " << EEPROMdir+28 << endl;      
  EEPROM_readAnything((EEPROMdir+32), SW_CHORD);
  Serial << "Read SW_CHORD: " << SW_CHORD << " EEPROM POS: " << EEPROMdir+32 << endl;      
  EEPROM_readAnything((EEPROMdir+36), SW_CHORDTYPE); 
  Serial << "Read SW_CHORDTYPE: " << SW_CHORDTYPE << " EEPROM POS: " << EEPROMdir+36 << endl;      
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

