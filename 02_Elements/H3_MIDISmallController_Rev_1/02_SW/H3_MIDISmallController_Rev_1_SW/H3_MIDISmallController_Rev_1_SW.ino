// Name: H3_MIDISmallController_Rev_1_SW
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: Novemeber 2017
// Description: Test Code for H3_MIDISmallController_Rev_31 Board. Part of the Henar#3 project in which Autofabricantes collaborates.

// Library Import
#include <Adafruit_NeoPixel.h>
#include <MIDIUSB.h>

// MIDI MSSG VALUES

// First Byte
const byte NOTE_ON        = 144;
const byte NOTE_OFF       = 128;
const byte CONTROL        = 176;

// SECOND BYTE GENERAL 
const byte CTRL_VOL       =   7;
const byte CTRL_MOD       =   1;
const byte CTRL_EFCT1     =  12;
const byte CTRL_EFCT2     =  13;
const byte CTRL_NOTEOFF   = 123;

// SECOND BYTE NOTE VALUES ------------------------------------------------------------------------------------------------------------------------------------
// OCTAVE 00              || OCTAVE 01               || OCTAVE 02               || OCTAVE 03              || OCTAVE 04               || OCTAVE 05
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
const byte NOTE_C0  =  0  ;const byte NOTE_C1  = 12  ;const byte NOTE_C2  = 24  ;const byte NOTE_C3  = 36  ;const byte NOTE_C4  = 48  ;const byte NOTE_C5  = 60;
const byte NOTE_C0s =  1  ;const byte NOTE_C1s = 13  ;const byte NOTE_C2s = 25  ;const byte NOTE_C3s = 37  ;const byte NOTE_C4s = 49  ;const byte NOTE_C5s = 61;
const byte NOTE_D0  =  2  ;const byte NOTE_D1  = 14  ;const byte NOTE_D2  = 26  ;const byte NOTE_D3  = 38  ;const byte NOTE_D4  = 50  ;const byte NOTE_D5  = 62;
const byte NOTE_D0s =  3  ;const byte NOTE_D1s = 15  ;const byte NOTE_D2s = 27  ;const byte NOTE_D3s = 39  ;const byte NOTE_D4s = 51  ;const byte NOTE_D5s = 63;
const byte NOTE_E0  =  4  ;const byte NOTE_E1  = 16  ;const byte NOTE_E2  = 28  ;const byte NOTE_E3  = 40  ;const byte NOTE_E4  = 52  ;const byte NOTE_E5  = 64;
const byte NOTE_F0  =  5  ;const byte NOTE_F1  = 17  ;const byte NOTE_F2  = 29  ;const byte NOTE_F3  = 41  ;const byte NOTE_F4  = 53  ;const byte NOTE_F5  = 65;
const byte NOTE_F0s =  6  ;const byte NOTE_F1s = 18  ;const byte NOTE_F2s = 30  ;const byte NOTE_F3s = 42  ;const byte NOTE_F4s = 54  ;const byte NOTE_F5s = 66;
const byte NOTE_G0  =  7  ;const byte NOTE_G1  = 19  ;const byte NOTE_G2  = 31  ;const byte NOTE_G3  = 43  ;const byte NOTE_G4  = 55  ;const byte NOTE_G5  = 67;
const byte NOTE_G0s =  8  ;const byte NOTE_G1s = 20  ;const byte NOTE_G2s = 32  ;const byte NOTE_G3s = 44  ;const byte NOTE_G4s = 56  ;const byte NOTE_G5s = 68;
const byte NOTE_A0  =  9  ;const byte NOTE_A1  = 21  ;const byte NOTE_A2  = 33  ;const byte NOTE_A3  = 45  ;const byte NOTE_A4  = 57  ;const byte NOTE_A5  = 69;
const byte NOTE_A0s = 10  ;const byte NOTE_A1s = 22  ;const byte NOTE_A2s = 34  ;const byte NOTE_A3s = 46  ;const byte NOTE_A4s = 58  ;const byte NOTE_A5s = 70;
const byte NOTE_B0  = 11  ;const byte NOTE_B1  = 23  ;const byte NOTE_B2  = 35  ;const byte NOTE_B3  = 47  ;const byte NOTE_B4  = 59  ;const byte NOTE_B5  = 71;

// SECOND BYTE NOTE VALUES -----------------------------------------------------------------------------------------------------------
// OCTAVE 06              || OCTAVE 07               || OCTAVE 08               || OCTAVE 09               || OCTAVE 10           
//------------------------------------------------------------------------------------------------------------------------------------
const byte NOTE_C6  = 72  ;const byte NOTE_C7  = 84  ;const byte NOTE_C8  = 96  ;const byte NOTE_C9  =108  ;const byte NOTE_C10  =120;
const byte NOTE_C6s = 73  ;const byte NOTE_C7s = 85  ;const byte NOTE_C8s = 97  ;const byte NOTE_C9s =109  ;const byte NOTE_C10s =121;
const byte NOTE_D6  = 74  ;const byte NOTE_D7  = 86  ;const byte NOTE_D8  = 98  ;const byte NOTE_D9  =110  ;const byte NOTE_D10  =122;
const byte NOTE_D6s = 75  ;const byte NOTE_D7s = 87  ;const byte NOTE_D8s = 99  ;const byte NOTE_D9s =111  ;const byte NOTE_D10s =123;
const byte NOTE_E6  = 76  ;const byte NOTE_E7  = 88  ;const byte NOTE_E8  =100  ;const byte NOTE_E9  =112  ;const byte NOTE_E10  =124;
const byte NOTE_F6  = 77  ;const byte NOTE_F7  = 89  ;const byte NOTE_F8  =101  ;const byte NOTE_F9  =113  ;const byte NOTE_F10  =125;
const byte NOTE_F6s = 78  ;const byte NOTE_F7s = 90  ;const byte NOTE_F8s =102  ;const byte NOTE_F9s =114  ;const byte NOTE_F10s =126;
const byte NOTE_G6  = 79  ;const byte NOTE_G7  = 91  ;const byte NOTE_G8  =103  ;const byte NOTE_G9  =115;
const byte NOTE_G6s = 80  ;const byte NOTE_G7s = 92  ;const byte NOTE_G8s =104  ;const byte NOTE_G9s =116;
const byte NOTE_A6  = 81  ;const byte NOTE_A7  = 93  ;const byte NOTE_A8  =105  ;const byte NOTE_A9  =117;
const byte NOTE_A6s = 82  ;const byte NOTE_A7s = 94  ;const byte NOTE_A8s =106  ;const byte NOTE_A9s =118;
const byte NOTE_B6  = 83  ;const byte NOTE_B7  = 95  ;const byte NOTE_B8  =107  ;const byte NOTE_B9  =119;
                                                            
// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for SW PAD-----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// SW Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
const int  SW_Q         =   4;      // SW_Q Number of present SW Pad (Big or Small)
int  SW_CTRL[SW_Q];                 // SW_Pad Global Control Array (Initialized to OFF in Setup)
const int SW_THR        = 512;      // Switch Threshold (Fake Digital)
int   MENU_MODE         =   0;      // Menu Mode Flag (Values 0, 1)
const int FADESTEPS_Q   =   2;      // GENERAL FadeSteps
const int FADEDELAY_Q   =   5;      // GENERAL FadeDelay

// Control Arrays for SW_Pad
//------------------------------------------------------------------------------------------------------------------------------------------
// SW_Q                || SW_ACT                  || SW_VAR         || SW_INIT                                         || Comments
//------------------------------------------------------------------------------------------------------------------------------------------
const int SW_00_Q = 1  ;const int SW_00_ACT = 0   ;int SW_00  = 0   ;int SW_00_INIT  = 0;                      
const int SW_01_Q = 1  ;const int SW_01_ACT = 1   ;int SW_01  = 0   ;int SW_01_INIT  = SW_00_Q;               
const int SW_02_Q = 1  ;const int SW_02_ACT = 2   ;int SW_02  = 0   ;int SW_02_INIT  = (SW_00_Q + SW_01_Q);
const int SW_03_Q = 1  ;const int SW_03_ACT = 3   ;int SW_03  = 0   ;int SW_03_INIT  = (SW_00_Q + SW_01_Q + SW_02_Q);


//------------------------------------------------------------------------------------------------------------------------------------------
// COLOR RED [0:255]          || COLOR GREEN [0:255]         || COLOR BLUE [0:255]           || Comments
//------------------------------------------------------------------------------------------------------------------------------------------
const byte GEN_R_OFF   =  40  ;const byte GEN_G_OFF   =  40  ;const byte GEN_B_OFF  =   40;   // SW_GENERAL OFF LED COLOR
const byte GEN_R_ON    =  40  ;const byte GEN_G_ON    =  40  ;const byte GEN_B_ON   =  255;   // SW_GENERAL OFF LED COLOR
const byte SW_00_R_ON  =   0  ;const byte SW_00_G_ON  = 100  ;const byte SW_00_B_ON  = 100;  // SW_GENERAL OFF LED COLOR
const byte SW_01_R_ON  = 100  ;const byte SW_01_G_ON  = 100  ;const byte SW_01_B_ON  =   0;  // SW_SCALE ON LED COLOR
const byte SW_02_R_ON  = 100  ;const byte SW_02_G_ON  =   0  ;const byte SW_02_B_ON  = 100;  // SW_MODE ON LED COLOR
const byte SW_03_R_ON  =   0  ;const byte SW_03_G_ON  = 100  ;const byte SW_03_B_ON  = 255;  // SW_MODE ON LED COLOR

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for PZ PAD-----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// PZ Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
const int PZ_Q          =   7;   // Piezo Quantity
const int PZ_RLX        =   5;   // Piezo Relax Time (ms)
const int PZ_THR_G      = 400;   // Piezo Sensor Threshold for PZ 7 (General)

// PZ Control Matrix            |PZ_PAD_0  |PZ_PAD_1  |PZ_PAD_2  |PZ_PAD_3  |PZ_PAD_4  |PZ_PAD_5  |PZ_PAD_6    || Comments
//------------------------------------------------------------------------------------------------------------------------------------------
byte PZ_MIDI_BYTE_1[2][PZ_Q] = {{NOTE_ON,  NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON  },   // MIDI First BYTE NOTE_ON
                                {NOTE_OFF, NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF }
};  // MIDI First BYTE NOTE_OFF
//------------------------------------------------------------------------------------------------------------------------------------------
byte PZ_MIDI_BYTE_2[6][PZ_Q] = {{NOTE_C1,  NOTE_D1,   NOTE_E1,   NOTE_F1,   NOTE_G1,   NOTE_A1,   NOTE_B1  },   // Escala Mayor             I-II-III-IV-V-VI-VII
                                {NOTE_C1,  NOTE_D1,   NOTE_D1s,  NOTE_F1,   NOTE_G1,   NOTE_A1,   NOTE_A1s },   // Escala Menor Natural     I-II-IIIb-IV-V-VI-VIIb
                                {NOTE_C1,  NOTE_E1,   NOTE_G1,   NOTE_B1,   NOTE_C2,   NOTE_E2,   NOTE_G2  },   // Escala Arpegio Maj7      I-III-V-VII-I'-III'-V'
                                {NOTE_C1,  NOTE_D1s,  NOTE_G1,   NOTE_A1s,  NOTE_C2,   NOTE_D2s,  NOTE_G2  },   // Escala Arpegio Men7      I-IIb-V-VIIb-I'-IIIb'-V'
                                {NOTE_C1,  NOTE_D1,   NOTE_E1,   NOTE_G1,   NOTE_A1,   NOTE_C2,   NOTE_D2  },   // Escala Pentatonico Mayor I-II-III-V-VI-I'-II'
                                {NOTE_D1s, NOTE_F1,   NOTE_F1,   NOTE_G1,   NOTE_A1s,  NOTE_C2,   NOTE_D2s }
};  // Escala Pentatonico Menor I-IIIb-IV-VIIb-I'-IIIb'
//------------------------------------------------------------------------------------------------------------------------------------------
int PZ_THR[PZ_Q]  =             {PZ_THR_G, PZ_THR_G,  PZ_THR_G,  PZ_THR_G,  PZ_THR_G,  PZ_THR_G,  PZ_THR_G };   // PZ_Pad Threhold Values (Stablishes the minimum value fr trigger)
int PZ_CTRL[PZ_Q] =             {0,        0,         0,         0,         0,         0,         0        };   // PZ_Pad Recorded Velocity (Initialized to 0 just for fun)

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for POT PAD----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

// Control Arrays for POT_Pad
//------------------------------------------------------------------------------------------------------------------------------------------
// POT_ID               || POT MIN READ VALUE         || POT_MAX READ VALUE      || Comments
//------------------------------------------------------------------------------------------------------------------------------------------
const int POT_00_ID = 0  ;const int POT_00_MIN =   0  ;int POT_00_MAX = 1024;    // Default Values for potentiometer, change for sensors         
const int POT_01_ID = 1  ;const int POT_01_MIN =   0  ;int POT_01_MAX = 1024;    // Default Values for potentiometer, change for sensors  
const int POT_02_ID = 2  ;const int POT_02_MIN =   0  ;int POT_02_MAX = 1024;    // Default Values for potentiometer, change for sensors
const int POT_03_ID = 3  ;const int POT_03_MIN =   0  ;int POT_03_MAX = 1024;    // Default Values for potentiometer, change for sensors

// SW Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
const int  POT_Q       =     2;      // POT_Q Number of present SW Pad (Big or Small)
int  POT_CTRL[POT_Q];                // POT_Pad Global Control Array (Initialized to OFF in Setup)
const int  GEN_POT_THR =   100;    // GEN_POT_THR Threshold for Potentiometer No Action

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for JOY PAD----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// SW Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
const int  JOY_Q       =     1;      // POT_Q Number of present SW Pad (Big or Small)
int  JOY_CTRL[2];                // POT_Pad Global Control Array (Initialized to OFF in Setup)

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Control Arrays for MISCELLANIA--------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Pin Definition
const int LED          =   2;
const int MUX_A        =   3;
const int MUX_B        =   4;
const int MUX_C        =   5;
const int MUX_D        =   6;
const int MUX_0        =   0;
const int JOY_SW       =   7;
const int JOY_X        =   2;
const int JOY_Y        =   1;
// Constant Values Definition
const bool ON          =   1;         // General ON value
const bool OFF         =   0;         // General OFF value
int        muxSel[4] = {MUX_D, MUX_C, MUX_B, MUX_A}; // MUX Selector Pins
const int  MAX_MIDI_VEL = 127;
// MIDI Global Variables
int       GEN_OCT = 3;     // Global OCTAVE (Make sure initial value is within MIN and MAX)
const int OCT_MIN = 0;    // OCTAVE Min Value
const int OCT_MAX = 6;    // OCTAVE Max Value
int       GEN_SCL = 0;    // Global SCALE (Make sure initial value is within MIN and MAX)
const int SCL_MIN = 0;    // SCALE Min Value
const int SCL_MAX = 5;    // SCALE Max Value
int       GEN_CHN = 0;    // Global CHANNEL (Make sure initial value is within MIN and MAX)
const int CHN_MIN = 0;    // CHANNEL Min Value
const int CHN_MAX = 5;    // CHANNEL Max Value

Adafruit_NeoPixel ledPadStripe = Adafruit_NeoPixel((SW_Q+1), LED, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);   // Baudrate Set
  ledPadStripe.begin();
  ledPadStripe.show();

  // Set Pin Modes
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_D, OUTPUT);
  pinMode(JOY_SW, INPUT);

  // Control Arrays Initialization
  for(int i = 0; i < SW_Q; i++){SW_CTRL[i] = 0;}
  for(int i = 0; i < POT_Q; i++){POT_CTRL[i] = 0;}
  for(int i = 0; i < 1; i++){JOY_CTRL[i] = 0;}
  
  //SW_LED_Initialization();
}

void loop() {
  //GEN_SCL = SW_Read_Iterator(SW_01_INIT, GEN_SCL, SCL_MIN, SCL_MAX, GEN_CHN, SW_01_R_ON, SW_01_G_ON, SW_01_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_Q, FADEDELAY_Q);
  //GEN_CHN = SW_Read_Iterator(SW_00_INIT, GEN_CHN, OCT_MIN, OCT_MAX, GEN_CHN, SW_00_R_ON, SW_00_G_ON, SW_00_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_Q, FADEDELAY_Q);
  POT_Read_Scale(POT_03_ID, GEN_CHN, GEN_OCT, GEN_SCL, 480, 580, 0);
  //POT_Read_Control(POT_01_ID, GEN_CHN, CTRL_MOD, 0, 1024, GEN_POT_THR);
  //PZ_PAD_Read(GEN_CHN, GEN_OCT, GEN_SCL);
  //JOYSTICK_Read_Scale(GEN_CHN, GEN_SCL, GEN_OCT, GEN_CHN+1, GEN_SCL, GEN_OCT);
}

void PZ_PAD_Read(int CHANNEL, int OCTAVE, int SCALE){
  for (int i = 0; i < PZ_Q; i++) {
    SET_MUXGATE(7-i);
    if (analogRead(MUX_0) > PZ_THR) {
      if (!PZ_CTRL[i]) { // If PZ not activated
        PZ_CTRL[i] = ON;
        // MIDI USB MSSG
        MIDI_TX(CHANNEL,PZ_MIDI_BYTE_1[0][i],(PZ_MIDI_BYTE_2[SCALE][i]+(OCTAVE*12)), map(analogRead(MUX_0),PZ_THR,1024,80,127));
        delay(50);
      }
    }else{
      if (PZ_CTRL[i]) { // If PZ activated
        PZ_CTRL[i] = OFF;
        // MIDI USB MSSG
        MIDI_TX(CHANNEL,PZ_MIDI_BYTE_1[1][i], (PZ_MIDI_BYTE_2[SCALE][i]+(OCTAVE*12)), 0);
      }
    }
  }
}

void SW_Read_Note(int SW_ID, int CHANNEL, byte MIDI_NOTE, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(3-SW_ID);
  if (analogRead(MUX_0) < SW_THR){      // If SW Pad activated
    if (!SW_CTRL[SW_ID]){                   // if SW Pad not previously activated
      SW_CTRL[SW_ID] = ON;                   // Set SW_Pad as ON
      MIDI_TX(CHANNEL, NOTE_ON, MIDI_NOTE, 127);
      SW_LED_FadeSingleLoop((SW_ID+1), R_OFF, G_OFF, B_OFF, R_ON, G_ON, B_ON, fadeSteps, fadeDelay);
    }
  }else{
    if(SW_CTRL[SW_ID]){
      SW_CTRL[SW_ID] = OFF;
      MIDI_TX(CHANNEL, NOTE_ON, MIDI_NOTE, 0);
      SW_LED_FadeSingleLoop((SW_ID+1), R_ON, G_ON, B_ON, R_OFF, G_OFF, B_OFF, fadeSteps, fadeDelay);     
   }
  }    // Set SW_Pad as OFF
}

int SW_Read_Iterator(int SW_ID, int ITE, int ITE_MIN, int ITE_MAX, int CHANNEL, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(3-SW_ID);
  if (analogRead(MUX_0) < SW_THR){        // If SW Pad activated
    if (!SW_CTRL[SW_ID]){                 // if SW Pad not previously activated
      SW_CTRL[SW_ID] = ON;                // Set SW_Pad as ON
      if (ITE < ITE_MAX){ITE++;}          // Variable Iteration
      else{ITE = ITE_MIN;}
      SW_LED_FadeSingleLoop((SW_ID+1), R_OFF, G_OFF, B_OFF, R_ON, G_ON, B_ON, fadeSteps, fadeDelay);
      MIDIOFF_FIX(CHANNEL, 0, 127);
      delay(200);
    }     
  }else{
    if (SW_CTRL[SW_ID]){
      SW_CTRL[SW_ID] = OFF;                // Set SW_Pad as OFF
      delay(100);
      SW_LED_FadeSingleLoop((SW_ID+1), R_ON, G_ON, B_ON, R_OFF, G_OFF, B_OFF, fadeSteps, fadeDelay);  
    }
  }
  return ITE;
}

void POT_Read_Control(int POT_ID, byte CONTROL_ID, int CHANNEL, int POT_MAX, int POT_MIN, int POT_THR){
  SET_MUXGATE((7-POT_ID));                                                     // POT Positions are mappe in MUX Positions 7 to 4
  if (analogRead(MUX_0) > POT_THR){
    int MUX_READ = map(analogRead(MUX_0),(POT_MIN+POT_THR),POT_MAX,0,127); // Map the value in the MIDI Range [0:127]
    if(MUX_READ != POT_CTRL[POT_ID]){                                            // Do not resend a MIDI if value has not change
      POT_CTRL[POT_ID] = MUX_READ;                                               // State new value in the POT_CTRL
      MIDI_TX(CHANNEL, CONTROL, CONTROL_ID, MUX_READ);                                   // MIDI Control MESSAGE Send
    }
  }
}

void POT_Read_Scale(int POT_ID, int CHANNEL, int OCTAVE, int SCALE, int POT_MAX, int POT_MIN, int POT_THR){
  SET_MUXGATE((7-POT_ID));                                                     // POT Positions are mappe in MUX Positions 7 to 4
  if (analogRead(MUX_0) > POT_THR){
    int MUX_READ = map(analogRead(MUX_0),(POT_MIN+POT_THR),POT_MAX,0,6); // Map the value in the MIDI Range [0:127]
    if(MUX_READ != POT_CTRL[POT_ID]){                                            // Do not resend a MIDI if value has not change
      MIDI_TX(CHANNEL,NOTE_OFF, (PZ_MIDI_BYTE_2[SCALE][POT_CTRL[POT_ID]]+(OCTAVE*12)), 0); // Turn OFF Previous Note
      POT_CTRL[POT_ID] = MUX_READ;                                               // State new value in the POT_CTRL
      MIDI_TX(CHANNEL,NOTE_ON,(PZ_MIDI_BYTE_2[SCALE][POT_CTRL[POT_ID]]+(OCTAVE*12)), 127); // Play New Note
    }
  }else{ // TODO Bad Temporal FIX
    if(POT_CTRL[POT_ID] != 7){
      MIDI_TX(CHANNEL,NOTE_OFF, (PZ_MIDI_BYTE_2[SCALE][POT_CTRL[POT_ID]]+(OCTAVE*12)), 0); // Turn OFF Previous Note
      POT_CTRL[POT_ID] = 7;
    }
  }
}

void JOYSTICK_Read_Scale(int CHANNEL_X, int SCALE_X, int OCTAVE_X, int CHANNEL_Y, int SCALE_Y, int OCTAVE_Y){
  if(digitalRead(JOY_SW)){ // If Joystick pressed
    int READ_X = map(analogRead(JOY_X),0,1024,0,6); // Map the value in the MIDI Range [0:127]
    if(READ_X != JOY_CTRL[0]){                                            // Do not resend a MIDI if value has not change
      MIDI_TX(CHANNEL_X,NOTE_OFF, (PZ_MIDI_BYTE_2[SCALE_X][JOY_CTRL[0]]+(OCTAVE_X*12)), 0); // Turn OFF Previous Note
      JOY_CTRL[0] = READ_X;                                               // State new value in the POT_CTRL
      MIDI_TX(CHANNEL_X,NOTE_ON,(PZ_MIDI_BYTE_2[SCALE_X][JOY_CTRL[0]]+(OCTAVE_X*12)), 127); // Play New Note
    }
    int READ_Y = map(analogRead(JOY_Y),0,1024,0,6); // Map the value in the MIDI Range [0:127]
    if(READ_Y != JOY_CTRL[1]){                                            // Do not resend a MIDI if value has not change
      MIDI_TX(CHANNEL_Y,NOTE_OFF, (PZ_MIDI_BYTE_2[SCALE_Y][JOY_CTRL[1]]+(OCTAVE_Y*12)), 0); // Turn OFF Previous Note
      JOY_CTRL[1] = READ_Y;                                               // State new value in the POT_CTRL
      MIDI_TX(CHANNEL_Y,NOTE_ON,(PZ_MIDI_BYTE_2[SCALE_Y][JOY_CTRL[1]]+(OCTAVE_Y*12)), 127); // Play New Note
    }
  }else{
    if(JOY_CTRL[0] != 7){
      MIDIOFF_FIX(CHANNEL_X, (PZ_MIDI_BYTE_2[SCALE_X][0]+(OCTAVE_X*12)), (PZ_MIDI_BYTE_2[SCALE_X][6]+(OCTAVE_X*12)));
      JOY_CTRL[0] = 7;
    }
    if(JOY_CTRL[1] != 7){
      MIDIOFF_FIX(CHANNEL_Y, (PZ_MIDI_BYTE_2[SCALE_Y][0]+(OCTAVE_Y*12)), (PZ_MIDI_BYTE_2[SCALE_Y][6]+(OCTAVE_Y*12)));
      JOY_CTRL[1] = 7;
    }
    
  }
}

void SW_LED_ColumnFade(int START_LED, int Q_LED, int INIT_LED, int END_LED, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
   for (int i = 0; i <= INIT_LED; i++){    // Canvas SW ON
    ledPadStripe.setPixelColor((START_LED + i), G_ON, R_ON, B_ON); // Heavy Stuff
   }
   for (int i = INIT_LED + 1; i < Q_LED; i++){    // Canvas SW ON
    ledPadStripe.setPixelColor((START_LED + i), G_OFF, R_OFF, B_OFF); // Heavy Stuff
   }
   if(INIT_LED > END_LED){
    int i = 0; //Start of the Sequence
    for(int h = 0; h < (fadeSteps+1); h++){
      ledPadStripe.setPixelColor((START_LED + INIT_LED - i), G_ON - ((G_ON/fadeSteps)*h), R_ON - ((R_ON/fadeSteps)*h), B_ON - ((B_ON/fadeSteps)*h)); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }
    for(int i = 1; i < (INIT_LED-END_LED); i++){
      for(int h = 0; h < (fadeSteps+1); h++){
        ledPadStripe.setPixelColor((START_LED + INIT_LED - i), G_ON - ((G_ON/fadeSteps)*h), R_ON - ((R_ON/fadeSteps)*h), B_ON - ((B_ON/fadeSteps)*h)); // Heavy Stuff
        ledPadStripe.setPixelColor((START_LED + INIT_LED - i + 1), ((G_OFF/fadeSteps)*h), ((R_OFF/fadeSteps)*h), ((B_OFF/fadeSteps)*h)); // Heavy Stuff
        delay(fadeDelay);
        ledPadStripe.show(); // Update LEDs
      }
    }
    for(int h = 0; h < (fadeSteps+1); h++){         // End of sequence BUG LAZY SOLUTION
      ledPadStripe.setPixelColor((START_LED + END_LED + 1), (G_OFF/fadeSteps)*h, (R_OFF/fadeSteps)*h, (B_OFF/fadeSteps)*h); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }
   }else if(INIT_LED == (END_LED - 1)){              // Consecutive BUG LAZY SOLUTION
      for(int h = 0; h < (fadeSteps+1); h++){
        ledPadStripe.setPixelColor((START_LED + END_LED), ((G_ON/fadeSteps)*h), ((R_ON/fadeSteps)*h), ((B_ON/fadeSteps)*h)); // Heavy Stuff
        delay(fadeDelay);
        ledPadStripe.show(); // Update LEDs
      }
   }else if(INIT_LED < END_LED){
      ledPadStripe.setPixelColor(START_LED, G_ON, R_ON, B_ON); // EXTREMELY LAZY SOLUTION TO BUG (TODO)
      for(int i = 1; i <= (END_LED-INIT_LED); i++){ // THIS CAUSES A BAD BLINK :'(
        for(int h = 0; h < (fadeSteps+1); h++){
          ledPadStripe.setPixelColor((START_LED + INIT_LED + i), ((G_ON/fadeSteps)*h), ((R_ON/fadeSteps)*h), ((B_ON/fadeSteps)*h)); // Heavy Stuff
          delay(fadeDelay);
          ledPadStripe.show(); // Update LEDs
        }
      } 
   }
}

void SW_LED_FadeSingleLoop(int INIT_LED, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
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

void SW_LED_FadeSingle(int INIT_LED, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
    /*for(int h = 0; h < (fadeSteps+1); h++){ // Fade to 0
      ledPadStripe.setPixelColor(INIT_LED, (G_OFF - ((G_OFF/fadeSteps)*h)),(R_OFF - ((R_OFF/fadeSteps)*h)), (B_OFF -((B_OFF/fadeSteps)*h))); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }*/
    for(int h = 1; h < (fadeSteps+1); h++){ // Fade to FINAL
      ledPadStripe.setPixelColor(INIT_LED, ((G_ON/fadeSteps)*h), ((R_ON/fadeSteps)*h), ((B_ON/fadeSteps)*h)); // Heavy Stuff
      delay(fadeDelay);
      ledPadStripe.show(); // Update LEDs
    }
}

void SW_LED_Initialization(){
  SW_LED_FadeGlobal(0, 0, 0, 100, 100, 100, FADESTEPS_Q, (FADEDELAY_Q*10));
  SW_LED_FadeGlobal(100, 100, 100, 10, 10, 10, FADESTEPS_Q, (FADEDELAY_Q*10));
  SW_LED_FadeGlobal(10, 10, 10, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_Q, (FADEDELAY_Q*10));
}

void SET_MUXGATE(int GATENUM){
  for (int h = 0; h < 4; h++) {
      digitalWrite(muxSel[h], ((GATENUM >> (3 - h)) & 0x01)); //MUX Setup pin for each MUX Pin
  }
  delay(5); // Delay por MUX Setup
}

void SW_LED_FadeGlobal(int INIT_R, int INIT_G, int INIT_B, int END_R, int END_G, int END_B, int fadeSteps, int fadeDelay){
  bool dir_R, dir_G, dir_B;
  int  step_R, step_G, step_B;
  int  Red, Grn, Blu;
  if(INIT_R >= END_R){dir_R = 0; step_R = ((INIT_R-END_R)/fadeSteps);}else{dir_R = 1; step_R = ((END_R-INIT_R)/fadeSteps);};
  if(INIT_G >= END_G){dir_G = 0; step_G = ((INIT_G-END_G)/fadeSteps);}else{dir_G = 1; step_G = ((END_G-INIT_G)/fadeSteps);};
  if(INIT_B >= END_B){dir_B = 0; step_R = ((INIT_B-END_B)/fadeSteps);}else{dir_B = 1; step_B = ((END_B-INIT_B)/fadeSteps);};
  for(int h = 0; h < fadeSteps; h++){
    if(dir_R){Red = (INIT_R + (h* step_R));}else{Red = (INIT_R - (h* step_R));};
    if(dir_G){Grn = (INIT_G + (h* step_G));}else{Grn = (INIT_G - (h* step_G));};
    if(dir_B){Blu = (INIT_B + (h* step_B));}else{Blu = (INIT_B - (h* step_B));};
    for(int i = 0; i< (SW_Q+1); i++){
      ledPadStripe.setPixelColor(i, Red, Grn, Blu);   // Heavy Stuff
    }
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
  // MIDI Sent Blink
  ledPadStripe.setPixelColor(0, GEN_R_ON, GEN_G_ON, GEN_B_ON);   
  ledPadStripe.show(); // Update LEDs
  delay(FADEDELAY_Q);
  ledPadStripe.setPixelColor(0, 0, 0, 0);   
  ledPadStripe.show(); // Update LEDs
}

void MIDIOFF_FIX(byte CHANNEL, int INIT_NOTE, int END_NOTE){ // This is a very rude and nasty sustitution to a General Note Off CMD
  for(int i= INIT_NOTE; i <= END_NOTE; i++){
    MIDI_TX(CHANNEL, NOTE_OFF, i, 0);
    delay(30);
  }
}

