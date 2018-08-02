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


# define SERIAL_DEBUG

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
  SW_LED_Initialization_Start();
  SW_INSTR.Val = readSW_ROW_INSTR(SWPZ_ROW, PZ_Q, SW_INSTR, INSTR_COL, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
  SW_LED_Initialization_End();
}

void loop() {
   SW_MODE.Val = readSW_ROW(SW_ROW_CD, (sizeof(SW_ROW_CD)/sizeof(SWPAD)), SW_MODE, MODE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_OCTV.Val = readSW_ROW(SW_ROW_B, (sizeof(SW_ROW_B)/sizeof(SWPAD)), SW_OCTV, OCTV_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SW_SCALE.Val = readSW_ROW(SW_ROW_A, (sizeof(SW_ROW_A)/sizeof(SWPAD)), SW_SCALE, SCALE_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SWE = readSW_Single(SWE, GEN_OFF, INSTR_COL[SW_INSTR.Val], FADESTEPS_C, FADEDELAY_C);
   SWF = readSW_PANIC(SWF, RESET_ON, GEN_OFF, FADESTEPS_C, FADEDELAY_C);
   SWPZ_Read(SWPZ_ROW, PZ_Q, INSTR_COL[SW_INSTR.Val], GEN_OFF, FADESTEPS_C, FADEDELAY_C);
}

int readSW_ROW(SWPAD SW_ROW[], int arraySize, SWCTRL SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){ // Should Remove arraySize somehow
  int prevON = SW_CTRL.Val;
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (!digitalRead(SW_ROW[i].muxID)){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated
          SW_CTRL.Val = i;                      // Set SW_MODE to that value
          SW_LED_ColumnFade(SW_ROW, SW_CTRL, prevON, COL_ON, COL_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
          Serial << "SWPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
          Serial << "CTRL: " << SW_CTRL.ID << " Val: " << SW_CTRL.Val << endl;
#else
          MIDI_TX(SW_INSTR.Val, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE.Val][0] + SW_MODE.Val+(12*SW_OCTV.Val)), 127);
          delay(NOTE_DURATION);
          MIDI_TX(SW_INSTR.Val, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE.Val]][0] + SW_MODE.Val+(12*SW_OCTV.Val)), 0);
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

SWPAD readSW_Single(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
#endif
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

int readSW_ROW_INSTR(SWPAD SW_ROW[], int arraySize, SWCTRL SW_CTRL, LEDCOL COL_ON[], LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  int prevON = SW_CTRL.Val;
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
       SW_CTRL.Val = i;                      // Set SW_MODE to that value
        }
     }
  }

  for(int i = 0; i < arraySize; i++){ 
    ledPadStripe.setPixelColor(SW_ROW[i].ledPos, COL_ON[SW_CTRL.Val].green, COL_ON[SW_CTRL.Val].red, COL_ON[SW_CTRL.Val].blue);
    ledPadStripe.show(); // Update LEDs
  }

  delay(FD*FS);

  for(int i = 0; i < arraySize; i++){ 
    ledPadStripe.setPixelColor(SW_ROW[i].ledPos, COL_OFF.green, COL_OFF.red, COL_OFF.blue);
    ledPadStripe.show(); // Update LEDs
  }
  
  return SW_CTRL.Val;
}

void SW_MENU_Transition(){
  if(Menu == 0){ // Transiopn from MENU MAX_MENU to MENU 0
    // Fade Out of MENU MAX_MENU


    // Fade In of MENU 0
  }
}

SWPAD readSW_PANIC(SWPAD SW_Pad, LEDCOL COL_ON, LEDCOL COL_OFF, int FS, int FD){ // Should Remove arraySize somehow
  SET_MUXGATE(SW_Pad.muxPos);
  if (!digitalRead(SW_Pad.muxID)){    // If SW Pad activated // TODO Change to digitalRead()
   if (!SW_Pad.swAct){                      // if SW Pad not previously activated
      SW_Pad.swAct = ON;                   // Set SW_Pad as ON
      SW_Time_Start = millis();
      SW_LED_FadeSingle_UP(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
#ifdef SERIAL_DEBUG 
      Serial << "SWPAD ON: " << SW_Pad.swID << " MUX GATE: " << SW_Pad.muxPos << " LED: " << SW_Pad.ledPos << endl;
      Serial << "Initiate MUTE and RESET sequence" << endl;
#endif
      
    }
  }else{
   if (SW_Pad.swAct){                      // if SW Pad previously activated
     SW_Pad.swAct = OFF;                   // Set SW_Pad as ON
     SW_Time_Current = millis();
     if((SW_Time_Current - SW_Time_Start) > TIME_PANIC_MS){
        muteChannel(SW_INSTR.Val, FD);
        SW_LED_ShutDown();
        resetMachine();
     }
     SW_LED_FadeSingle_DW(SW_Pad, COL_ON, COL_OFF,  FS, FD); // Update LED Stripe
   }
  }
   return SW_Pad;
}

void SWPZ_Read(SWPAD SW_ROW[], int arraySize, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){
  for(int i = 0; i < arraySize; i++){ 
     SET_MUXGATE(SW_ROW[i].muxPos);
     //if (analogRead(SW_ROW[i].muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
     if (!digitalRead(SW_ROW[i].muxID)){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated       
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
          Serial << "SWPZPAD ON: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
#else
          MIDI_TX(SW_INSTR.Val, NOTE_ON, (PZ_MIDI_BYTE_2[SW_SCALE.Val][i]+SW_MODE.Val+(12*SW_OCTV.Val)), 127);
#endif    
          SW_LED_FadeSingle_UP(SW_ROW[i], COL_ON, COL_OFF,  fadeSteps, fadeDelay); // Update LED 
        }
     }else{
       if (SW_ROW[i].swAct){                      // if SW Pad previously activated
         SW_ROW[i].swAct = OFF;                   // Set SW_Pad as ON
#ifdef SERIAL_DEBUG 
          Serial << "SWPZPAD OFF: " << SW_ROW[i].swID << " MUX GATE: " << SW_ROW[i].muxPos << " LED: " << SW_ROW[i].ledPos << " PAD: " << i << endl;
#else

          MIDI_TX(SW_INSTR.Val, NOTE_OFF, (PZ_MIDI_BYTE_2[SW_SCALE.Val][i]+SW_MODE.Val+(12*SW_OCTV.Val)), 0);
#endif  
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
  SW_LED_FadeSingle_UP(SWE, INSTR_COL[SW_INSTR.Val], GEN_OFF,  FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
  
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

