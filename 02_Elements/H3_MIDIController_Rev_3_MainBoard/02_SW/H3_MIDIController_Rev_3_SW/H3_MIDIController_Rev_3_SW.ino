

// Name: H3_MIDIController_Rev_3_SW
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: Novemeber 2017
// Description: Test Code for H3_MIDIController_Rev_3 Board. Part of the Henar 3 project in which Autofabricantes collaborates.

// Library Import
#include <Adafruit_NeoPixel.h>
#include <MIDIUSB.h>
#include <Streaming.h>

//# define SERIAL_DEBUG
//# define SERIAL_DEBUG_PZ
//# define SERIAL_DEBUG_PZ_FULL

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
const int MAX_MIDI_VEL        = 127;
const int SW_ITE              =   0;
const int SW_ITE_MAX          =   5;
const int SW_Q                =  22;
const int SW_THR              = 512; // Switch Threshold (Fake Digital)
int   MENU_MODE               =   0; // Menu Mode Flag (Values 0, 1)
const int FADESTEPS_C         =   6; // GENERAL FadeSteps
const int FADEDELAY_C         =  10; // GENERAL FadeDelay
const int MUX_SETUP_DELAY     =   7; // Mux Delay for PZPad
const int PZ_MEASURE_CYCLE    =   3;
const int PZ_AUTOCAL_CYCLES   =  30;
const int PZ_GEN_THR          =   2;

// Generated Structures (struct)
struct SWPAD{
  int   muxPos;
  int   ledPos;
  bool  swAct;
  int   muxID;
};

struct PZPAD{
  int   pzID;
  int   muxPos;
  int   pzThr;
  bool  pzAct;
  int   muxID;
  int   pzVal[PZ_MEASURE_CYCLE];
  int   pzLastMax;
};


struct LEDCOL{
  int red;
  int green;
  int blue;
};

struct SWCTRL{
  int    ctrlID;
  int    ctrlVal;
};

PZPAD PZA = {0, 4, 15, 0, MUX_2};
PZPAD PZB = {1, 5, 5, 0, MUX_2};
PZPAD PZC = {2, 6, 5, 0, MUX_2};
PZPAD PZD = {3, 3, 5, 0, MUX_2};
PZPAD PZE = {4, 2, 5, 0, MUX_2};
PZPAD PZF = {5, 1, 5, 0, MUX_2};
PZPAD PZG = {6, 0, 5, 0, MUX_2};

SWPAD SWA0 = {5,17,0,MUX_1};
SWPAD SWA1 = {10,18,0,MUX_1};
SWPAD SWA2 = {12,20,0,MUX_1};
SWPAD SWA3 = {0,12,0,MUX_1};
SWPAD SWA4 = {3,15,0,MUX_1};

SWPAD SWB0 = {4,16,0,MUX_1};
SWPAD SWB1 = {13,21,0,MUX_1};
SWPAD SWB2 = {11,19,0,MUX_1};
SWPAD SWB3 = {1,13,0,MUX_1};
SWPAD SWB4 = {2,14,0,MUX_1};

SWPAD SWC0 = {8,8,0,MUX_0};
SWPAD SWC1 = {4,4,0,MUX_0};
SWPAD SWC2 = {7,7,0,MUX_0};
SWPAD SWC3 = {0,0,0,MUX_0};
SWPAD SWC4 = {3,3,0,MUX_0};

SWPAD SWD0 = {9,9,0,MUX_0};
SWPAD SWD1 = {5,5,0,MUX_0};
SWPAD SWD2 = {6,6,0,MUX_0};
SWPAD SWD3 = {2,1,0,MUX_0};
SWPAD SWD4 = {1,2,0,MUX_0};

SWPAD SWE  = {11,11,0,MUX_0};
SWPAD SWF  = {10,10,0,MUX_0};

// Gamma Correction LUT from Adafruit
const int GC[256] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

// Control Arrays for SW_Pad LEDS
// -----------------------------------------------------------------------------------------------------------------------------------------
// COLOR RED [0:255]          || COLOR GREEN [0:255]          || COLOR BLUE [0:255]         || Comments
//----------------------------------------------------------------------------------------------------------------------
LEDCOL GEN_OFF   = {GC[255],GC[255], GC[255]};  // SW_GENERAL OFF LED COLOR
LEDCOL BIG_ON    = {GC[255],GC[255], GC[255]};  // SW_GENERAL OFF LED COLOR
LEDCOL SCALE_ON  = {GC[255],GC[0], GC[102]};    // SW_SCALE ON LED COLOR
LEDCOL MODE_ON   = {GC[51],  GC[204], GC[255]};  // SW_MODE ON LED COLOR
LEDCOL INSTR_ON  = {GC[51],GC[204],   GC[51]}; // SW_INSTR ON LED COLOR
LEDCOL VOL_ON    = {GC[100],GC[0],   GC[40]};  // SW_VOL ON LED COLOR
LEDCOL OCTV_ON   = {GC[255],  GC[153], GC[51]};   // SW_OCTV ON LED COLOR
LEDCOL MODU_ON   = {GC[100],GC[0],   GC[100]}; // SW_MODU ON LED COLOR
LEDCOL EFCT_ON   = {GC[0],  GC[100], GC[0]};   // SW_EFCT ON LED COLOR
LEDCOL MENU_ON   = {GC[0],  GC[255], GC[255]}; // SW_MENU ON LED COLOR
LEDCOL PANIC_ON  = {GC[255],GC[0],   GC[0]};   // SW_MENU ON LED COLOR
LEDCOL NUSE_ON   = {GC[0],  GC[255], GC[0]};   // SW_MENU ON LED COLOR
LEDCOL SEQ_ON    = {GC[0],  GC[255], GC[100]}; // SW_SEQ ON LED COLOR

// Control Arrays for SW_Pad Mapping
//------------------------------------------------------------------------------------------------------------------------------------------
//                                                    || Comments
//-----------------------------------------------------------------------------------------------------------------------------------------
SWPAD SW_ROW_A[5] = {SWA0, SWA1, SWA2, SWA3, SWA4};
SWPAD SW_ROW_B[5] = {SWB0, SWB1, SWB2, SWB3, SWB4};
SWPAD SW_ROW_C[5] = {SWC0, SWC1, SWC2, SWC3, SWC4};
SWPAD SW_ROW_D[5] = {SWD0, SWD1, SWD2, SWD3, SWD4};
SWPAD SW_ROW_CD[10] = {SWC0, SWC1, SWC2, SWC3, SWC4, SWD0, SWD1, SWD2, SWD3, SWD4}; 
SWPAD SW_ROW_E[1]  = {SWE};
SWPAD SW_ROW_F[1]  = {SWF};

PZPAD PZ_ROW[7] = {PZA, PZB, PZC, PZD, PZE, PZF, PZG};

// Control Arrays for SW_Pad
//------------------------------------------------------------------------------------------------------------------------------------------
// SW_ACT                    || SW_VAR           || Comments
//-----------------------------------------------------------------------------------------------------------------------------------------
SWCTRL SW_MODE  = {0, 0};  
SWCTRL SW_INSTR = {1, 1};  
SWCTRL SW_SCALE = {2, 0};  
SWCTRL SW_SEQ   = {9, 0};  
SWCTRL SW_EFCT  = {3, 0};
SWCTRL SW_MODU  = {4, 0};
SWCTRL SW_OCTV  = {5, 2};
SWCTRL SW_VOL   = {6, 4};
SWCTRL SW_PANIC = {7, 0};
SWCTRL SW_MENU  = {8, 0};



// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for PZ PAD-----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// PZ Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
// General Parameters:
#define PZ_Q      7     // Piezo Quantity
#define PZ_RLX    5     // Piezo Relax Time (ms)
// Threshold Parameters:
#define PZ_THR    40   // Piezo Sensor Threshold for PZ 7 (General)
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
    /*for (int i = 0; i < PZ_MEASURE_CYCLE; i++){
      Serial.println(PZ_ROW[0].pzVal[i]); //TOREMOVE
      delay(1);
    }*/
    //Serial.println(PZ_PAD_Calculate_RMS(PZ_ROW[0]));
    //Serial.println(PZ_PAD_Read_Single(PZA, 0));

}

int readSW_ROW(SWPAD SW_ROW[], SWCTRL SW_CTRL, LEDCOL COL_ON, LEDCOL COL_OFF, int fadeSteps, int fadeDelay){
  int prevON = SW_CTRL.ctrlVal;
  for(int i = 0; i < 5; i++){
     SET_MUXGATE(SW_ROW[i].muxPos);
     if (analogRead(SW_ROW[i].muxID) < SW_THR){    // If SW Pad activated // TODO Change to digitalRead()
       if (!SW_ROW[i].swAct){                      // if SW Pad not previously activated
          SW_CTRL.ctrlVal = i;                      // Set SW_MODE to that value
          SW_LED_ColumnFade(SW_ROW, SW_CTRL, prevON, COL_ON, COL_OFF, FADESTEPS_C, FADEDELAY_C); // Update LED Stripe
          SW_ROW[i].swAct = ON;                   // Set SW_Pad as ON
          //SW_Action(SW_CTRL);
#ifdef SERIAL_DEBUG 
          
          Serial.print("CTRL: "); Serial.print(SW_CTRL.ctrlID); Serial.print(" MUX: "); Serial.print(SW_ROW[i].muxPos); Serial.print("LED: "); Serial.print(SW_ROW[i].ledPos); Serial.print(" Button: "); Serial.println(i);
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

void SW_Action(int SW_ACTION, int SW_VAR){ }
/*  switch(SW_ACTION){
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
  }
}*/

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
    Serial.print(PZ_Pad.pzID);  Serial.print(" PZ Trigger with value; "); Serial.print((newVal - PZ_Pad.pzLastMax)); Serial.print(" THR: "); Serial.println(PZ_Pad.pzThr);
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

void  SW_LED_Initialization_End(void){
  /*for (int i = 0; i < 120; i++){    // Canvas SW OFF
    ledPadStripe.setPixelColor(SWE.ledPos, (i*2), (i*2), (i*2)); // Heavy Stuffç
    ledPadStripe.setPixelColor(SWF.ledPos, (i*2), (i*2), (i*2)); // Heavy Stuffç
    ledPadStripe.show(); // Update LEDs
    delay(10);
  }*/
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

