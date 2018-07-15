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

  SW_LED_Initialization_Start();
  PZ_PAD_Autocalibration();
  SW_LED_Initialization_End();
}

void loop() {
    if(ITER == 3){
      ITER = 0;
      SW_MODE.ctrlVal = readSW_ROW(SW_ROW_D, SW_MODE, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_INSTR.ctrlVal = readSW_ROW(SW_ROW_C, SW_INSTR, INSTR_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_OCTV.ctrlVal = readSW_ROW(SW_ROW_B, SW_OCTV, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_SCALE.ctrlVal = readSW_ROW(SW_ROW_A, SW_SCALE, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
    }
    ITER++;
    PZ_PAD_Read();
}

int readSW_ROW(SWPAD SW_ROW[], SWCTRL SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){
  int prevON = SW_CTRL.ctrlVal;
  for(int i = 0; i < 5; i++){ // TODO use some kind of sizeof()
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (analogRead(SW_ROW[i].muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated
          SW_CTRL.ctrlVal = i;                      // Set SW_MODE to that value
          SW_LED_ColumnFade(SW_ROW, SW_CTRL, prevON, COL_ON, COL_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
          //SW_Action(SW_CTRL);
#ifdef SERIAL_DEBUG 
          Serial << "CTRL: " << SW_CTRL.ctrlID << " MUX: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
#endif
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
       }
     }
  }
   return SW_CTRL.ctrlVal;
}

void SW_Action(SWCTRL SW_CTRL, int SW_VAR){
  /*switch(SW_CTRL.ctrlID){
    case(SW_MODE_ACT): // Play Note with New configuration
      MIDI_TX(SW_INSTR, PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_VAR+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_VAR+(12*SW_OCTV)),0);
    break;
    case(SW_INSTR_ACT): // Play Note with New configuration
      MIDI_TX(SW_VAR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_VAR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)),0);
    break;
    case(SW_SCALE_ACT): //case(SW_SCALE_ACT): // Play Note with New configuration
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_VAR][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_VAR][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)),0);
    break;
    case(SW_OCTV_ACT): //case(SW_MODU_ACT): // Configure and Play Note with New configuration
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_VAR)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_VAR)),0);
    break;
    case(SW_EFCT_ACT): //case(SW_MODU_ACT): // Configure and Play Note with New configuration
      MIDI_TX(SW_INSTR, CONTROL, CTRL_EFCT1, map(SW_VAR, 0, 5, 0, 127));
      delay(50);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)),0);
    break;
      case(SW_MODU_ACT): //case(SW_MODU_ACT): // Configure and Play Note with New configuration
      MIDI_TX(SW_INSTR, CONTROL, CTRL_MOD, map(SW_VAR, 0, 5, 0, 127));
      delay(50);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)),0);
    break;
      case(SW_VOL_ACT): //case(SW_VOL_ACT): // Configure and Play Note with New configuration
      MIDI_TX(SW_INSTR, CONTROL, CTRL_VOL, map(SW_VAR, 0, 5, 0, 127));
      delay(50);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      delay(500);
      MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)]+SW_MODE+(12*SW_OCTV)),0);
    break;
    case(SW_SEQ_ACT): //case(SW_SEQ_ACT): // Configure and Play Note with New configuration
      MIDI_TX(7, NOTE_ON, SW_SEQ, 127); //TODO
      delay(500);
      MIDI_TX(7, NOTE_OFF, SW_SEQ, 0); //TODO
      //delay(500);
    break;
  }*/
}

/*
void SW_MENU_Read(int INIT_SW, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(INIT_SW);
  if (analogRead(MUX_1) < SW_THR) {    // If SW Pad activated
    if (!SW_CTRL[INIT_SW]) {            // if SW Pad not previously activated
      SW_LED_FadeSingle(INIT_SW, R_ON, G_ON, B_ON, R_OFF, G_OFF, B_OFF, fadeSteps, fadeDelay);
      //SW_LED_ColumnTransition(SW_MODE_LED_INIT, SW_MODE, i, MODE_R_ON, MODE_G_ON, MODE_B_ON, MODE_R_OFF, MODE_G_OFF, MODE_B_OFF, 6, 10); // Update LED Stripe
      if(!SW_MENU){
        SW_MENU = 1;

        //SW_LED_ColumnFade(SW_MODE_INIT, SW_MODE_Q, SW_MODE, 0, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_EFCT_INIT, SW_EFCT_Q, 0, SW_EFCT, EFCT_R_ON, EFCT_G_ON, EFCT_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        //SW_LED_ColumnFade(SW_SEQ_INIT, SW_SEQ_Q, SW_SEQ, 0, SEQ_R_ON, SEQ_G_ON, SEQ_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_MODU_INIT, SW_MODU_Q, 0, SW_MODU, MODU_R_ON, MODU_G_ON, MODU_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe

        //SW_LED_ColumnFade(SW_INSTR_INIT, SW_INSTR_Q, SW_INSTR, 0, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_OCTV_INIT, SW_OCTV_Q, 0, SW_OCTV, OCTV_R_ON, OCTV_G_ON, OCTV_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe

        //SW_LED_ColumnFade(SW_SCALE_INIT, SW_SCALE_Q, SW_SCALE, 0, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_VOL_INIT, SW_VOL_Q, 0, SW_VOL, VOL_R_ON, VOL_G_ON, VOL_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
      }
      else{
        SW_MENU = 0;
        
        //SW_LED_ColumnFade(SW_EFCT_INIT, SW_EFCT_Q, SW_EFCT, 0, EFCT_R_ON, EFCT_G_ON, EFCT_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_MODU_INIT, SW_MODU_Q, SW_MODU, 0, MODU_R_ON, MODU_G_ON, MODU_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_SEQ_INIT, SW_SEQ_Q, SW_SEQ, 0, SEQ_R_ON, SEQ_G_ON, SEQ_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_MODE_INIT, SW_MODE_Q, 0, SW_MODE, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        
        //SW_LED_ColumnFade(SW_OCTV_INIT, SW_OCTV_Q, SW_OCTV, 0, OCTV_R_ON, OCTV_G_ON, OCTV_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_INSTR_INIT, SW_INSTR_Q, 0, SW_INSTR, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        
        //SW_LED_ColumnFade(SW_VOL_INIT, SW_VOL_Q, SW_VOL, 0,  VOL_R_ON, VOL_G_ON, VOL_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        //SW_LED_ColumnFade(SW_SCALE_INIT, SW_SCALE_Q, 0, SW_SCALE, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
      }
      
    }
  }else{if(SW_CTRL[INIT_SW]){SW_CTRL[INIT_SW]=OFF;}}    // Set SW_Pad as OFF
}*/

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


/*   
    SET_MUXGATE(PZ_ROW[i].muxPos);
    delay(MUX_SETUP_DELAY);
    PZRead = analogRead(PZ_ROW[i].muxID);
#ifdef SERIAL_DEBUG_PZ_FULL 
    Serial.print("PAD Read: "); Serial.print(i); Serial.print(" Analog Read: "); Serial.println(PZRead);
#endif
    if (PZRead > PZ_ROW[i].pzThr) {
      if (!PZ_ROW[i].pzAct) { // If PZ not activated
        PZ_ROW[i].pzAct = ON;
#ifdef SERIAL_DEBUG 
        Serial.print("PAD Pressed: "); Serial.print(i); Serial.print(" Analog Read: "); Serial.println(PZRead);
#else // MIDI USB MSSG
        MIDI_TX(SW_INSTR.ctrlVal,NOTE_ON,(PZ_MIDI_BYTE_2[SW_SCALE.ctrlVal][(PZ_Q-1)-i]+SW_MODE.ctrlVal+(12*SW_OCTV.ctrlVal)), PZRead);
#endif
        
      }
    }else{
      if (PZ_ROW[i].pzAct) { // If PZ activated
        PZ_ROW[i].pzAct = OFF;
#ifdef SERIAL_DEBUG_PZ
        Serial.print("PAD Unpressed: "); Serial.print(i); Serial.print(" Analog Read: "); Serial.println(PZRead);
#else // MIDI USB MSSG
        MIDI_TX(SW_INSTR.ctrlVal,NOTE_OFF,(PZ_MIDI_BYTE_2[SW_SCALE.ctrlVal][(PZ_Q-1)-i]+SW_MODE.ctrlVal+(12*SW_OCTV.ctrlVal)), 0);
#endif
      }
    }
  }
}*/


void PZ_PAD_Read(){
    for (int i = 0; i < PZ_Q; i++){
      PZ_ROW[i] = PZ_PAD_Read_Single(PZ_ROW[i]);  
      PZ_ROW[i].pzLastMax = PZ_PAD_Trigger(PZ_ROW[i], PZ_PAD_Calculate_RMS(PZ_ROW[i]));
    }
}

PZPAD PZ_PAD_Read_Single(PZPAD PZ_Pad){
  SET_MUXGATE(PZ_Pad.muxPos);
  delay(MUX_SETUP_DELAY);
  for (int i = 0; i < PZ_MEASURE_CYCLE; i++){
    PZ_Pad.pzVal[i] = analogRead(PZ_Pad.muxID);  
    delay(1);
  }
  /*for (int i = 0; i < PZ_MEASURE_CYCLE; i++){
      PZ_Pad.pzLastMax = PZ_PAD_Trigger(PZ_Pad, PZ_Pad.pzVal[i]);
    delay(1);
  }*/
  return PZ_Pad;
}

int PZ_PAD_Calculate_RMS(PZPAD PZ_Pad){
  int PZ_RMS = 0;
  for (int i = 0; i < PZ_MEASURE_CYCLE; i++){
    PZ_RMS = PZ_RMS + PZ_Pad.pzVal[i]^2;
  }
  return sqrt((double)(PZ_RMS / PZ_MEASURE_CYCLE));
}

int PZ_PAD_Trigger(PZPAD PZ_Pad, int newVal){
  if((abs(newVal - PZ_Pad.pzLastMax)) > PZ_Pad.pzThr){
#ifdef SERIAL_DEBUG 
    //Serial.print(PZ_Pad.pzID);  Serial.print(" PZ Trigger with value; "); Serial.print((newVal - PZ_Pad.pzLastMax)); Serial.print(" THR: "); Serial.println(PZ_Pad.pzThr);
    Serial << "PZ_PAD ID: " << PZ_Pad.pzID << " PZ Trigger with value; " << (newVal - PZ_Pad.pzLastMax) << " THR: " << PZ_Pad.pzThr << endl;
#else
    MIDI_TX(CONFIG[INSTR].Val, NOTE_ON, (PZ_MIDI_BYTE_2[CONFIG[SCALE].Val][(PZ_Q-1)-i]+CONFIG[MODE].Val+(12*CONFIG[OCTV].Val)), PZRead);
#endif
  }    
  return newVal;
}

void PZ_PAD_Autocalibration(){
  int PZ_PAD_Cal[PZ_Q][PZ_AUTOCAL_CYCLES];
  for (int h = 0; h < PZ_AUTOCAL_CYCLES; h++){
    for (int i = 0; i < PZ_Q; i++){
      PZ_ROW[i] = PZ_PAD_Read_Single(PZ_ROW[i]);  
      PZ_PAD_Cal[i][h] = (abs(PZ_ROW[i].pzVal[i] - PZ_ROW[i].pzLastMax));    
      PZ_ROW[i].pzLastMax = PZ_ROW[i].pzVal[i];
    }
  }

  for (int i = 0; i < PZ_Q; i++){
    int PZ_AVG = 0;
    for (int h = 0; h < PZ_AUTOCAL_CYCLES; h++){
      PZ_AVG += PZ_PAD_Cal[i][h];
    }
    PZ_ROW[i].pzThr = (PZ_AVG/PZ_AUTOCAL_CYCLES) + PZ_GEN_THR;
  } 
}

void SW_LED_ColumnFade(SWPAD SW_ROW[], SWCTRL SW_CTRL, int prevON, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){
  if(prevON >= SW_CTRL.ctrlVal){
    int i = 0; //Start of the Sequence
    for(int i = 0; i < (prevON - SW_CTRL.ctrlVal); i++){
      for(int h = 0; h <= FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[prevON-i].ledPos, (COL_OFF.green - (((COL_OFF.green-COL_ON.green)/FS)*(FS-h))), (COL_OFF.red - (((COL_OFF.red-COL_ON.red)/FS)*(FS-h))), (COL_OFF.blue - (((COL_OFF.blue-COL_ON.blue)/FS)*(FS-h))));
        ledPadStripe.setPixelColor(SW_ROW[prevON-i-1].ledPos, (COL_OFF.green - (((COL_OFF.green-COL_ON.green)/FS)*(h))), (COL_OFF.red - (((COL_OFF.red-COL_ON.red)/FS)*(h))), (COL_OFF.blue - (((COL_OFF.blue-COL_ON.blue)/FS)*(h))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
  }else{
    for(int i = prevON; i <= SW_CTRL.ctrlVal; i++){
      for(int h = 0; h < FS; h++){
        ledPadStripe.setPixelColor(SW_ROW[i].ledPos, (COL_OFF.green - (((COL_OFF.green-COL_ON.green)/FS)*(h+1))), (COL_OFF.red - (((COL_OFF.red-COL_ON.red)/FS)*(h+1))), (COL_OFF.blue - (((COL_OFF.blue-COL_ON.blue)/FS)*(h+1))));
        ledPadStripe.show(); // Update LEDs
        delay(FD);
      }
    }
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

  SW_LED_ColumnFade(SW_ROW_D, SW_MODE, 0, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
  SW_LED_ColumnFade(SW_ROW_C, SW_INSTR, 0,INSTR_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
  SW_LED_ColumnFade(SW_ROW_B, SW_OCTV, 0,OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
  SW_LED_ColumnFade(SW_ROW_A, SW_SCALE, 0,SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);

}

void  SW_LED_Initialization_Start(void){

  for (int h = 0; h < 5; h++){
    for (int i = 0; i < 120; i++){
      ledPadStripe.setPixelColor(SW_ROW_A[4-h].ledPos, (i*2), 0, 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[4-h].ledPos, (i*2), 0, 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[4-h].ledPos, (i*2), 0, 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[4-h].ledPos, (i*2), 0, 0); // Heavy Stuff
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

  for (int h = 0; h < 5; h++){
    for (int i = 0; i < 120; i++){
      ledPadStripe.setPixelColor(SW_ROW_A[4-h].ledPos, 0, (i*2), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[4-h].ledPos, 0, (i*2), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[4-h].ledPos, 0, (i*2), 0); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[4-h].ledPos, 0, (i*2), 0); // Heavy Stuff
      ledPadStripe.show(); // Update LEDs
      delay(1);
    }
  }

  for (int i = 0; i < 120; i++){    // Canvas SW OFF
    ledPadStripe.setPixelColor(SWE.ledPos, 0, (i*2), 0); // Heavy Stuffç
    ledPadStripe.setPixelColor(SWF.ledPos, 0, (i*2), 0); // Heavy Stuffç
    ledPadStripe.show(); // Update LEDs
    delay(5);
  }
  
  for (int h = 0; h < 5; h++){
    for (int i = 0; i < 120; i++){
      ledPadStripe.setPixelColor(SW_ROW_A[4-h].ledPos, 0, 0, (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_B[4-h].ledPos, 0, 0, (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_C[4-h].ledPos, 0, 0, (i*2)); // Heavy Stuff
      ledPadStripe.setPixelColor(SW_ROW_D[4-h].ledPos, 0, 0, (i*2)); // Heavy Stuff
      ledPadStripe.show(); // Update LEDs
      delay(1);
    }
  }

  for (int i = 0; i < 120; i++){    // Canvas SW OFF
    ledPadStripe.setPixelColor(SWE.ledPos, 0, 0, (i*2)); // Heavy Stuffç
    ledPadStripe.setPixelColor(SWF.ledPos, 0, 0, (i*2)); // Heavy Stuffç
    ledPadStripe.show(); // Update LEDs
    delay(5);
  }

  
  for (int i = 0; i < 120; i++){    // Canvas SW OFF
    ledPadStripe.setPixelColor(SWE.ledPos, (i*2), (i*2), (i*2)); // Heavy Stuffç
    ledPadStripe.setPixelColor(SWF.ledPos, (i*2), (i*2), (i*2)); // Heavy Stuffç
    ledPadStripe.show(); // Update LEDs
    delay(10);
  }

}

void SW_LED_FadeSingle(int INIT_LED, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
    for(int h = 0; h < (fadeSteps+1); h++){ // Fade to ON
      ledPadStripe.setPixelColor(INIT_LED, ((G_ON/fadeSteps)*h), ((R_ON/fadeSteps)*h), ((B_ON/fadeSteps)*h)); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }
    for(int h = 0; h < (fadeSteps+1); h++){ // Fade to 0
      ledPadStripe.setPixelColor(INIT_LED, (G_ON - ((G_ON/fadeSteps)*h)),(R_ON - ((R_ON/fadeSteps)*h)), (B_ON -((B_ON/fadeSteps)*h))); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }
    for(int h = 0; h < (fadeSteps+1); h++){ // Fade to OFF
      ledPadStripe.setPixelColor(INIT_LED, ((G_OFF/fadeSteps)*h), ((R_OFF/fadeSteps)*h), ((B_OFF/fadeSteps)*h)); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
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

void SET_MUXGATE(int GATENUM){
  for (int h = 0; h < 4; h++) {
      digitalWrite(muxSel[h], ((GATENUM >> (3 - h)) & 0x01)); //MUX Setup pin for each MUX Pin
  }
  delay(10); // Delay por MUX Setup
}

