// Name: H3_Configuration.h
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: July 2018
// Description: Constant, MIDI Messages, Structs and Aux definitions. Part of the Henar 3 project in which Autofabricantes collaborates.

// MIDI MSSG VALUES

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------MIDI MSSG VALUES----------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

// FIRST BYTE GENERAL
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
// ---------------------------------------------------H3 Pin Definition---------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
const int LED                 =   2;
const int MUX_A               =   3;
const int MUX_B               =   4;
const int MUX_C               =   5;
const int MUX_D               =   6;
const int MUX_0               =   0;
const int MUX_1               =   1;
const int MUX_2               =   2;

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Control and Configuration values Definition-------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// Constant Values Definition
const bool ON                 =   1;         // General ON value
const bool OFF                =   0;         // General OFF value
const int muxSel[4]           =   {6, 5, 4, 3}; // MUX Selector Pins MUX_D, MUX_C, MUX_B, MUX_A
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
const int PZ_Q                =   7;     // Piezo Quantity
const int PZ_RLX              =   5;     // Piezo Relax Time (ms)

const int MODE                =   0;  
const int INSTR               =   1;  
const int SCALE               =   2;  
const int SEQ                 =   3;  
const int EFC                 =   4;
const int MODU                =   5;
const int OCTV                =   6;
const int VOL                 =   7;
const int PANIC               =   8;
const int MENU                =   9;

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Custom Configuration Structs----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
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
  int    ID;
  int    Val;
};

// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------LED Gamma Correction LUT--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
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
  
// -----------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------Struct Object Definition--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
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

// Control Arrays for SW_Pad LEDS
// ---------------------------------------------------------------------------------------------------------------------
// [0:255]          RED    || GREEN || BLUE     || Comments
//----------------------------------------------------------------------------------------------------------------------
LEDCOL GEN_OFF   = {GC[255], GC[255],  GC[255]};  // SW_GENERAL OFF LED COLOR
LEDCOL BIG_ON    = {GC[255], GC[255],  GC[255]};  // SW_GENERAL OFF LED COLOR
LEDCOL SCALE_ON  = {GC[255], GC[0],    GC[102]};  // SW_SCALE ON LED COLOR
LEDCOL MODE_ON   = {GC[51],  GC[204],  GC[255]};  // SW_MODE ON LED COLOR
LEDCOL INSTR_ON  = {GC[51],  GC[204],  GC[51]};   // SW_INSTR ON LED COLOR
LEDCOL VOL_ON    = {GC[100], GC[0],    GC[40]};   // SW_VOL ON LED COLOR
LEDCOL OCTV_ON   = {GC[255], GC[153],  GC[51]};   // SW_OCTV ON LED COLOR
LEDCOL MODU_ON   = {GC[100], GC[0],    GC[100]};  // SW_MODU ON LED COLOR
LEDCOL EFCT_ON   = {GC[0],   GC[100],  GC[0]};    // SW_EFCT ON LED COLOR
LEDCOL MENU_ON   = {GC[0],   GC[255],  GC[255]};  // SW_MENU ON LED COLOR
LEDCOL PANIC_ON  = {GC[255], GC[0],    GC[0]};    // SW_MENU ON LED COLOR
LEDCOL NUSE_ON   = {GC[0],   GC[255],  GC[0]};    // SW_MENU ON LED COLOR
LEDCOL SEQ_ON    = {GC[0],   GC[255],  GC[100]};  // SW_SEQ ON LED COLOR

SWCTRL SW_MODE  = {MODE,  0};  
SWCTRL SW_INSTR = {INSTR, 1};  
SWCTRL SW_SCALE = {SCALE, 0};  
SWCTRL SW_SEQ   = {SEQ,   0};  
SWCTRL SW_EFCT  = {EFCT,  0};
SWCTRL SW_MODU  = {MODU,  0};
SWCTRL SW_OCTV  = {OCTV,  2};
SWCTRL SW_VOL   = {VOL,   4};
SWCTRL SW_PANIC = {PANIC, 0};
SWCTRL SW_MENU  = {MENU,  0};

// Control Arrays for SW_Pad Mapping
SWPAD SW_ROW_A[5] = {SWA0, SWA1, SWA2, SWA3, SWA4};
SWPAD SW_ROW_B[5] = {SWB0, SWB1, SWB2, SWB3, SWB4};
SWPAD SW_ROW_C[5] = {SWC0, SWC1, SWC2, SWC3, SWC4};
SWPAD SW_ROW_D[5] = {SWD0, SWD1, SWD2, SWD3, SWD4};
SWPAD SW_ROW_CD[10] = {SWC0, SWC1, SWC2, SWC3, SWC4, SWD0, SWD1, SWD2, SWD3, SWD4}; 
SWPAD SW_ROW_E[1]  = {SWE};
SWPAD SW_ROW_F[1]  = {SWF};
PZPAD PZ_ROW[7] = {PZA, PZB, PZC, PZD, PZE, PZF, PZG};
SWCTRL CONFIG[10] = {SW_MODE, SW_INSTR, SW_SCALE, SW_SEQ, SW_EFCT, SW_MODU, SW_OCTV, SW_VOL, SW_PANIC, SW_MENU}

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------Control Arrays for PZ PAD-----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------
// PZ Control General Parameters
// -----------------------------------------------------------------------------------------------------------------------------------------
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

