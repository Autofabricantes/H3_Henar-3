// Name: H3_MIDIController_Rev_3_SW
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: Novemeber 2017
// Description: Test Code for H3_MIDIController_Rev_3 Board. Part of the Henar 3 project in which Autofabricantes collaborates.

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
const int  SW_Q               = 27;  // SW_Q Number of present SW Pad (Big or Small)
int  SW_CTRL[SW_Q];                  // SW_Pad Global Control Array (Initialized to OFF in Setup)
const int SW_THR              = 512; // Switch Threshold (Fake Digital)
int   MENU_MODE               =   0; // Menu Mode Flag (Values 0, 1)
const int FADESTEPS_C         =   6; // GENERAL FadeSteps
const int FADEDELAY_C         =  10; // GENERAL FadeDelay

// Control Arrays for SW_Pad LEDS
// -----------------------------------------------------------------------------------------------------------------------------------------
// COLOR RED [0:255]          || COLOR GREEN [0:255]          || COLOR BLUE [0:255]         || Comments
//----------------------------------------------------------------------------------------------------------------------
const byte GEN_R_OFF   =  20  ;const byte GEN_G_OFF   =  20   ;const byte GEN_B_OFF  =  20;  // SW_GENERAL OFF LED COLOR
const byte BIG_R       =  100 ;const byte BIG_G       = 100   ;const byte BIG_B      = 100;  // SW_GENERAL OFF LED COLOR
const byte SCALE_R_ON  = 100  ;const byte SCALE_G_ON  = 100   ;const byte SCALE_B_ON =   0;  // SW_SCALE ON LED COLOR
const byte MODE_R_ON   =   0  ;const byte MODE_G_ON   = 100   ;const byte MODE_B_ON  = 100;  // SW_MODE ON LED COLOR
const byte INSTR_R_ON  = 100  ;const byte INSTR_G_ON  =   0   ;const byte INSTR_B_ON = 100;  // SW_INSTR ON LED COLOR
const byte VOL_R_ON    = 100  ;const byte VOL_G_ON    =   0   ;const byte VOL_B_ON   =  40;  // SW_VOL ON LED COLOR
const byte OCTV_R_ON   =   0  ;const byte OCTV_G_ON   =   0   ;const byte OCTV_B_ON  = 100;  // SW_OCTV ON LED COLOR
const byte MODU_R_ON   = 100  ;const byte MODU_G_ON   =   0   ;const byte MODU_B_ON  = 100;  // SW_MODU ON LED COLOR
const byte EFCT_R_ON   =   0  ;const byte EFCT_G_ON   = 100   ;const byte EFCT_B_ON  =   0;  // SW_EFCT ON LED COLOR
const byte MENU_R_ON   =   0  ;const byte MENU_G_ON   = 255   ;const byte MENU_B_ON  = 255;  // SW_MENU ON LED COLOR
const byte PANIC_R_ON  = 255  ;const byte PANIC_G_ON  =   0   ;const byte PANIC_B_ON =   0;  // SW_MENU ON LED COLOR
const byte NUSE_R_ON   =   0  ;const byte NUSE_G_ON   = 255   ;const byte NUSE_B_ON  =   0;  // SW_MENU ON LED COLOR

// Control Arrays for SW_Pad
//------------------------------------------------------------------------------------------------------------------------------------------
// SW_Q                    || SW_ACT                     || SW_VAR           || SW_INIT                                     || Comments
//-----------------------------------------------------------------------------------------------------------------------------------------
const int SW_MODE_Q  = 12  ;const int SW_MODE_ACT  = 0   ;int SW_MODE  = 0   ;int SW_MODE_INIT   = 0;                       // SW_MODE
const int SW_INSTR_Q =  6  ;const int SW_INSTR_ACT = 1   ;int SW_INSTR = 0   ;int SW_INSTR_INIT  = SW_MODE_Q;               // SW_INSTR
const int SW_SCALE_Q =  6  ;const int SW_SCALE_ACT = 2   ;int SW_SCALE = 0   ;int SW_SCALE_INIT  = (SW_SCALE_Q + SW_MODE_Q);// SW_SCALE
const int SW_EFCT_Q  =  6  ;const int SW_EFCT_ACT  = 3   ;int SW_EFCT  = 0   ;int SW_EFCT_INIT   = 0;
const int SW_MODU_Q  =  6  ;const int SW_MODU_ACT  = 4   ;int SW_MODU  = 0   ;int SW_MODU_INIT   = SW_EFCT_Q;
const int SW_OCTV_Q  =  6  ;const int SW_OCTV_ACT  = 5   ;int SW_OCTV  = 2   ;int SW_OCTV_INIT   = (SW_EFCT_Q + SW_MODU_Q);
const int SW_VOL_Q   =  6  ;const int SW_VOL_ACT   = 6   ;int SW_VOL   = 5   ;int SW_VOL_INIT    = (SW_EFCT_Q + SW_MODU_Q + SW_OCTV_Q);
const int SW_PANIC_Q =  1  ;const int SW_PANIC_ACT = 7   ;int SW_PANIC = 0   ;int SW_PANIC_INIT  = (SW_EFCT_Q + SW_MODU_Q + SW_OCTV_Q + SW_VOL_Q);
const int SW_MENU_Q  =  1  ;const int SW_MENU_ACT = 8    ;int SW_MENU  = 0   ;int SW_MENU_INIT   = (SW_EFCT_Q + SW_MODU_Q + SW_OCTV_Q + SW_VOL_Q + SW_PANIC_Q);

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for PZ PAD-----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// PZ Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
// General Parameters:
#define PZ_Q      7     // Piezo Quantity
#define PZ_RLX    5     // Piezo Relax Time (ms)
// Threshold Parameters:
#define PZ_THR    200   // Piezo Sensor Threshold for PZ 7 (General)
// PZ RGB LED Color Definition:
#define PZ_OFF_R  0   // OFF PAD Color Red    [0:255]
#define PZ_OFF_G  0   // OFF PAD Color Green  [0:255]
#define PZ_OFF_B  0   // OFF PAD Color Blue   [0:255]                                                                    
#define PZ_ON_R   255   // ON PAD Color Red     [0:255]
#define PZ_ON_G   0     // ON PAD Color Green   [0:255]
#define PZ_ON_B   255   // ON PAD Color Blue    [0:255] 

int PZ_ON_RGB[3]  = {PZ_ON_R, PZ_ON_G, PZ_ON_B};    // ON LED SW PAD Color
int PZ_OFF_RGB[3] = {PZ_OFF_R, PZ_OFF_G, PZ_OFF_B}; // OFF LED SW PAD Color


int PZ_CTRL[PZ_Q] =             {0,        0,         0,         0,         0,         0,         0        };   // PZ_Pad Recorded Velocity (Initialized to 0 just for fun)
// PZ Control Matrix            |PZ_PAD_0  |PZ_PAD_1  |PZ_PAD_2  |PZ_PAD_3  |PZ_PAD_4  |PZ_PAD_5  |PZ_PAD_6    || Comments
//------------------------------------------------------------------------------------------------------------------------------------------
byte PZ_MIDI_BYTE_1[2][PZ_Q] = {{NOTE_ON,  NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON,   NOTE_ON  },   // MIDI First BYTE NOTE_ON
                                {NOTE_OFF, NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF,  NOTE_OFF }};  
// MIDI First BYTE NOTE_OFF
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
byte PZ_MIDI_BYTE_2[6][PZ_Q] = {{NOTE_C1,  NOTE_D1,   NOTE_E1,   NOTE_F1,   NOTE_G1,   NOTE_A1,   NOTE_B1  },   // Escala Mayor             I-II-III-IV-V-VI-VII
                                {NOTE_C1,  NOTE_D1,   NOTE_D1s,  NOTE_F1,   NOTE_G1,   NOTE_A1,   NOTE_A1s },   // Escala Menor Natural     I-II-IIIb-IV-V-VI-VIIb
                                {NOTE_C1,  NOTE_E1,   NOTE_G1,   NOTE_B1,   NOTE_C2,   NOTE_E2,   NOTE_G2  },   // Escala Arpegio Maj7      I-III-V-VII-I'-III'-V'
                                {NOTE_C1,  NOTE_D1s,  NOTE_G1,   NOTE_A1s,  NOTE_C2,   NOTE_D2s,  NOTE_G2  },   // Escala Arpegio Men7      I-IIb-V-VIIb-I'-IIIb'-V'
                                {NOTE_C1,  NOTE_D1,   NOTE_E1,   NOTE_G1,   NOTE_A1,   NOTE_C2,   NOTE_D2  },   // Escala Pentatonico Mayor I-II-III-V-VI-I'-II'
                                {NOTE_D1s, NOTE_F1,   NOTE_F1,   NOTE_G1,   NOTE_A1s,  NOTE_C2,   NOTE_D2s }};  // Escala Pentatonico Menor I-IIIb-IV-VIIb-I'-IIIb'

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
const int MUX_1        =   1;
const int MUX_2        =   2;
// Constant Values Definition
const bool ON          =   1;         // General ON value
const bool OFF         =   0;         // General OFF value
int muxSel[4] = {MUX_D, MUX_C, MUX_B, MUX_A}; // MUX Selector Pins
const int MAX_MIDI_VEL = 127;
const int SW_ITE = 0;
const int SW_ITE_MAX = 5;

Adafruit_NeoPixel ledPadStripe = Adafruit_NeoPixel(SW_Q, LED, NEO_RGB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);   // Baudrate Set
  ledPadStripe.begin();
  ledPadStripe.show();

  // Set Pin Modes
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_D, OUTPUT);

  for(int i = 0; i < SW_Q; i++){
    SW_CTRL[i] = 0;
  }
  SW_LED_Initialization();
}

void loop() {
  switch(SW_MENU){
    case (0):
      SW_MODE = SW_Read(SW_MODE_INIT, SW_MODE_Q, SW_MODE, SW_MODE_ACT, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_SCALE = SW_Read(SW_SCALE_INIT, SW_SCALE_Q, SW_SCALE, SW_SCALE_ACT, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_INSTR = SW_Read(SW_INSTR_INIT, SW_INSTR_Q, SW_INSTR, SW_INSTR_ACT, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
    break;
    default:
      SW_EFCT = SW_Read(SW_EFCT_INIT, SW_EFCT_Q, SW_EFCT, SW_EFCT_ACT, EFCT_R_ON, EFCT_G_ON, EFCT_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_MODU = SW_Read(SW_MODU_INIT, SW_MODU_Q, SW_MODU, SW_MODU_ACT, MODU_R_ON, MODU_G_ON, MODU_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_OCTV = SW_Read(SW_OCTV_INIT, SW_OCTV_Q, SW_OCTV, SW_OCTV_ACT, OCTV_R_ON, OCTV_G_ON, OCTV_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
      SW_VOL = SW_Read(SW_VOL_INIT, SW_VOL_Q, SW_VOL, SW_VOL_ACT, VOL_R_ON, VOL_G_ON, VOL_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
    break;
  }
  SW_MENU_Read(SW_MENU_INIT, MENU_R_ON, MENU_G_ON, MENU_B_ON, (GEN_R_OFF + BIG_R), (GEN_G_OFF + BIG_G), (GEN_B_OFF + BIG_B), FADESTEPS_C, (FADEDELAY_C));
  //SW_PANIC_Read(SW_PANIC_INIT, PANIC_R_ON, PANIC_G_ON, PANIC_B_ON, (GEN_R_OFF + BIG_R), (GEN_G_OFF + BIG_G), (GEN_B_OFF + BIG_B), FADESTEPS_C, (FADEDELAY_C));
  PZ_PAD_Read();
}


// MENU MODE 0 SW_Read Functions

int SW_Read(int INIT_SW, int SW_IND_Q, int SW_VAR, int SW_ACTION, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  //int i = INIT_SW;
  for(int i = INIT_SW; i < (INIT_SW + SW_IND_Q); i++){
    // SW_Pad Located in MUX_0
    if(i <= 15){                             // If SW_Pad located in MUX_0
      SET_MUXGATE(i);
      if (analogRead(MUX_0) < SW_THR){      // If SW Pad activated
        if (!SW_CTRL[i]){                   // if SW Pad not previously activated
          SW_LED_ColumnFade(INIT_SW, SW_IND_Q, SW_VAR, (i-INIT_SW), R_ON, G_ON, B_ON, R_OFF, G_OFF,B_OFF, fadeSteps, fadeDelay); // Update LED Stripe
          SW_VAR = (i-INIT_SW);                        // Set SW_MODE to that value
          SW_CTRL[i] = ON;                   // Set SW_Pad as ON
          SW_Action(SW_ACTION, SW_VAR);
        }
      }else{if(SW_CTRL[i]) {SW_CTRL[i] = OFF;}}    // Set SW_Pad as OFF
    // SW_Pad Located in MUX_1
    }else if (i >= 16){
      SET_MUXGATE(i-16);                      // If SW_Pad located in MUX_1
      if (analogRead(MUX_1) < SW_THR){       // If SW Pad activated
        if (!SW_CTRL[i+16]) {                 // if SW Pad not previously activated
          SW_LED_ColumnFade(INIT_SW, SW_IND_Q, SW_VAR, (i-INIT_SW), R_ON, G_ON, B_ON, R_OFF, G_OFF,B_OFF, fadeSteps, fadeDelay); // Update LED Stripe
          SW_VAR = (i-INIT_SW);                      // Set SW_MODE to that value
          SW_CTRL[i+16] = ON;                 // Set SW_Pad as ON
          SW_Action(SW_ACTION, SW_VAR);
        }
      }else{if(SW_CTRL[i+16]) {SW_CTRL[i+16] = OFF;}}    // Set SW_Pad as OFF
    } 
  }
  return SW_VAR;
}

void SW_Action(int SW_ACTION, int SW_VAR){
  switch(SW_ACTION){
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
  }
}

void SW_MENU_Read(int INIT_SW, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(INIT_SW);
  if (analogRead(MUX_1) < SW_THR) {    // If SW Pad activated
    if (!SW_CTRL[INIT_SW]) {            // if SW Pad not previously activated
      SW_LED_FadeSingle(INIT_SW, R_ON, G_ON, B_ON, R_OFF, G_OFF, B_OFF, fadeSteps, fadeDelay);
      //SW_LED_ColumnTransition(SW_MODE_LED_INIT, SW_MODE, i, MODE_R_ON, MODE_G_ON, MODE_B_ON, MODE_R_OFF, MODE_G_OFF, MODE_B_OFF, 6, 10); // Update LED Stripe
      if(!SW_MENU){
        SW_MENU = 1;

        SW_LED_ColumnFade(SW_MODE_INIT, SW_MODE_Q, SW_MODE, 0, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_EFCT_INIT, SW_EFCT_Q, 0, SW_EFCT, EFCT_R_ON, EFCT_G_ON, EFCT_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        SW_LED_ColumnFade(SW_MODU_INIT, SW_MODU_Q, 0, SW_MODU, MODU_R_ON, MODU_G_ON, MODU_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe

        SW_LED_ColumnFade(SW_INSTR_INIT, SW_INSTR_Q, SW_INSTR, 0, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_OCTV_INIT, SW_OCTV_Q, 0, SW_OCTV, OCTV_R_ON, OCTV_G_ON, OCTV_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe

        SW_LED_ColumnFade(SW_SCALE_INIT, SW_SCALE_Q, SW_SCALE, 0, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_VOL_INIT, SW_VOL_Q, 0, SW_VOL, VOL_R_ON, VOL_G_ON, VOL_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
      }
      else{
        SW_MENU = 0;
        
        SW_LED_ColumnFade(SW_EFCT_INIT, SW_EFCT_Q, SW_EFCT, 0, EFCT_R_ON, EFCT_G_ON, EFCT_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_MODU_INIT, SW_MODU_Q, SW_MODU, 0, MODU_R_ON, MODU_G_ON, MODU_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_MODE_INIT, SW_MODE_Q, 0, SW_MODE, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        
        SW_LED_ColumnFade(SW_OCTV_INIT, SW_OCTV_Q, SW_OCTV, 0, OCTV_R_ON, OCTV_G_ON, OCTV_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_INSTR_INIT, SW_INSTR_Q, 0, SW_INSTR, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
        
        SW_LED_ColumnFade(SW_VOL_INIT, SW_VOL_Q, SW_VOL, 0,  VOL_R_ON, VOL_G_ON, VOL_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C);
        SW_LED_ColumnFade(SW_SCALE_INIT, SW_SCALE_Q, 0, SW_SCALE, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
      }
      
    }
  }else{if(SW_CTRL[INIT_SW]){SW_CTRL[INIT_SW]=OFF;}}    // Set SW_Pad as OFF
}

void SW_PANIC_Read(int INIT_SW, int R_ON, int G_ON, int B_ON, int R_OFF, int G_OFF, int B_OFF, int fadeSteps, int fadeDelay){
  SET_MUXGATE(INIT_SW);
  if (analogRead(MUX_1) < SW_THR) {    // If SW Pad activated
    if (!SW_CTRL[INIT_SW]) {            // if SW Pad not previously activated
      SW_CTRL[INIT_SW]=ON;
      ledPadStripe.setPixelColor(SW_PANIC_INIT, PANIC_G_ON, PANIC_R_ON, PANIC_B_ON);   
      ledPadStripe.show(); // Update LEDs
      for(int i = 0; i < 6; i++){
        MIDIOFF_FIX(i, 0, 127);
      }
  }else{
    if(SW_CTRL[INIT_SW]){
      SW_CTRL[INIT_SW]=OFF;
      ledPadStripe.setPixelColor(SW_PANIC_INIT, (GEN_G_OFF+BIG_R), (GEN_R_OFF+BIG_G), (GEN_B_OFF+BIG_B));   
      ledPadStripe.show(); // Update LEDs
     }
   }    // Set SW_Pad as OFF 
  }
}

// PZ_Pad Read Function

void PZ_PAD_Read() {
  for (int i = 0; i < PZ_Q; i++) {
    SET_MUXGATE(i);
    if (analogRead(MUX_2) > PZ_THR) {
      if (!PZ_CTRL[i]) { // If PZ not activated
        PZ_CTRL[i] = ON;
        // MIDI USB MSSG
        MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[0][(PZ_Q-1)-i],(PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)-i]+SW_MODE+(12*SW_OCTV)), map(analogRead(MUX_2),PZ_THR,1024,80,127));
      }
    }else{
      if (PZ_CTRL[i]) { // If PZ activated
        PZ_CTRL[i] = OFF;
        // MIDI USB MSSG
        MIDI_TX(SW_INSTR,PZ_MIDI_BYTE_1[1][(PZ_Q-1)-i], (PZ_MIDI_BYTE_2[SW_SCALE][(PZ_Q-1)-i]+SW_MODE+(12*SW_OCTV)), 0);
      }
    }
  }
}

void POT_Read() {
  for (int i = 1; i < 2; i++) {
    for (int h = 0; h < 4; h++) {
      digitalWrite(muxSel[h], ((i >> (3 - h)) & 0x01)); //MUX Setup pin for each MUX Pin
    }
    delay(100); // Delay for MUX Setup
    Serial.print("POT READ: ");
    Serial.println(analogRead(MUX_2));
  }
}

/*void SW_LED_update() {
  if (ledEvent) {           // Execute only under demand
    ledEvent = 0;
    
    //SW_PAD_MODE control
    for (int i = SW_MODE_LED_INIT; i < (SW_MODE_LED_INIT + SW_MODE_Q); i++) {
      ledPadStripe.setPixelColor(i, SW_MODE_LED[1][1], SW_MODE_LED[1][0], SW_MODE_LED[1][2]);   // Heavy Stuff
    }
    ledPadStripe.setPixelColor(SW_MODE_LED_INIT + SW_MODE, SW_MODE_LED[0][1], SW_MODE_LED[0][0], SW_MODE_LED[0][2]); // Heavy Stuff
    
    //SW_PAD_INSTR control
    for (int i = SW_INSTR_LED_INIT; i < (SW_INSTR_LED_INIT + SW_INSTR_Q); i++) {
      ledPadStripe.setPixelColor(i, SW_INSTR_LED[1][1], SW_INSTR_LED[1][0], SW_INSTR_LED[1][2]);   // Heavy Stuff
    }
    ledPadStripe.setPixelColor((SW_INSTR_LED_INIT + SW_INSTR), SW_INSTR_LED[0][1], SW_INSTR_LED[0][0], SW_INSTR_LED[0][2]); // Heavy Stuff
    
    //SW_PAD_SCALE control
    for (int i = SW_SCALE_LED_INIT; i < (SW_SCALE_LED_INIT + SW_SCALE_Q); i++) {
      ledPadStripe.setPixelColor(i, SW_SCALE_LED[1][1], SW_SCALE_LED[1][0], SW_SCALE_LED[1][2]);   // Heavy Stuff
    }
    ledPadStripe.setPixelColor(SW_SCALE_LED_INIT + SW_SCALE, SW_MODE_LED[0][1], SW_SCALE_LED[0][0], SW_SCALE_LED[0][2]); // Heavy Stuff
    
    //SW_BIG BUTTONS control
    
  }
  delay(1);
  ledPadStripe.show(); // Update LEDs
}*/

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

void SW_LED_Initialization(){
  SW_LED_FadeGlobal(0, 0, 0, 100, 100, 100, FADESTEPS_C, (FADEDELAY_C*10));
  SW_LED_FadeGlobal(100, 100, 100, 10, 10, 10, FADESTEPS_C, (FADEDELAY_C*10));
  SW_LED_FadeGlobal(10, 10, 10, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, (FADEDELAY_C*10));

  SW_LED_ColumnFade(SW_MODE_INIT, SW_MODE_Q, 0, SW_MODE, MODE_R_ON, MODE_G_ON, MODE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
  SW_LED_ColumnFade(SW_INSTR_INIT, SW_INSTR_Q, 0, SW_INSTR, INSTR_R_ON, INSTR_G_ON, INSTR_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
  SW_LED_ColumnFade(SW_SCALE_INIT, SW_SCALE_Q, 0, SW_SCALE, SCALE_R_ON, SCALE_G_ON, SCALE_B_ON, GEN_R_OFF, GEN_G_OFF, GEN_B_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
  SW_LED_FadeSingle(SW_MENU_INIT, MENU_R_ON, MENU_G_ON, MENU_B_ON, (GEN_R_OFF + BIG_R), (GEN_G_OFF + BIG_G), (GEN_B_OFF + BIG_B), FADESTEPS_C, FADEDELAY_C * 5);
  SW_LED_FadeSingle(SW_PANIC_INIT, PANIC_R_ON, PANIC_G_ON, PANIC_B_ON, (GEN_R_OFF + BIG_R), (GEN_G_OFF + BIG_G), (GEN_B_OFF + BIG_B), FADESTEPS_C, FADEDELAY_C * 5);
  SW_LED_FadeSingle(SW_MENU_INIT+1, MENU_R_ON, MENU_G_ON, MENU_B_ON, (GEN_R_OFF + BIG_R), (GEN_G_OFF + BIG_G), (GEN_B_OFF + BIG_B), FADESTEPS_C, FADEDELAY_C * 5);
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
    for(int i = 0; i< (SW_SCALE_Q + SW_MODE_Q + SW_INSTR_Q + 3); i++){
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
  //ledPadStripe.setPixelColor(SW_PANIC_INIT, PANIC_R_ON, PANIC_G_ON, PANIC_B_ON);   
  //ledPadStripe.show(); // Update LEDs
  //delay(100);
  //ledPadStripe.setPixelColor(SW_PANIC_INIT, (GEN_R_OFF+BIG_R), (GEN_G_OFF+BIG_G), (GEN_B_OFF+BIG_B));   
  //ledPadStripe.show(); // Update LEDs
}

void MIDIOFF_FIX(byte CHANNEL, int INIT_NOTE, int END_NOTE){ // This is a very rude and nasty sustitution to a General Note Off CMD
  for(int i= INIT_NOTE; i <= END_NOTE; i++){
    MIDI_TX(CHANNEL, NOTE_OFF, i, 0);
    delay(10);
  }
}
