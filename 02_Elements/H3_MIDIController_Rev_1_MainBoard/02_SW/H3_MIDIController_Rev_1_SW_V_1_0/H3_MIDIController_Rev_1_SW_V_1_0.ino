// Name: H3_HMI_TestBoard_Rev_1_SW_1_0
// Programmer: Pablo dMM (Pablodmm.isp@gmail.com)
// Date: May 2017
// Description:
// Test Code for H3_HMI_TestBoard_Rev_1 Board. Part of the Henar 3 project in which Autofabricantes collaborates.

// Library Import
#include <Adafruit_NeoPixel.h>
#include <MIDIUSB.h>

// MIDI MSSG VALUES

// First Byte
#define NOTE_ON     0x90
#define NOTE_OFF    0x80
#define CONTROL     0xB0

// Second Byte
#define MODULATION  1
#define VOLUME      7
#define Note_C           48
#define Note_Cs          49
#define Note_D           50
#define Note_Ds          51
#define Note_E           52
#define Note_F           53
#define Note_Fs          54
#define Note_G           55
#define Note_Gs          56
#define Note_A           57
#define Note_As          58
#define Note_B           59
#define Note_C2          60



// Pin Definition
#define LED     2
#define MUX_A   3
#define MUX_B   4
#define MUX_C   5
#define MUX_D   6
#define LED_R   7
#define LED_G   8
#define LED_B   9
#define SWT_0   10
#define SWT_1   11
#define MUX_OUT 0
#define POT_0   1
#define POT_1   2

// Constants Definition
#define SW_Q  5     // Switch Quantity
#define PZ_Q  6     // Piezo Quantity

#define PZ_THR_0  10 // Piezo Sensor Threshold for PZ 7 (Wood)
#define PZ_THR_1  10 // Piezo Sensor Threshold for PZ 8 (Plastic)
#define PZ_THR_2  10 // Piezo Sensor Threshold for PZ 9 (Metal)
#define PZ_THR_3  1025 // Piezo Sensor Threshold for PZ 10 (Wood #2)
#define PZ_THR_4  10 // Piezo Sensor Threshold for PZ 11 (Pad EVA #1)
#define PZ_THR_5  10 // Piezo Sensor Threshold for PZ 12 (Pad EVA #2)


#define PZ_RLX    5 // Piezo Relax Time

#define SW_THR  512 // Switch Threshold
#define MIDI_CHANNEL 0   //Default MIDI channel. FOr user is +1

// SW RGB LED color Definition
#define OFF_R  200  // OFF PAD Color Red    [0:255]
#define OFF_G  200    // OFF PAD Color Green  [0:255]
#define OFF_B  200  // OFF PAD Color Blue   [0:255]
                                                                        
#define ON_R   255  // ON PAD Color Red     [0:255]
#define ON_G   0  // ON PAD Color Green   [0:255]
#define ON_B   255  // ON PAD Color Blue    [0:255]

// PZ RGB LED color Definition
#define PZ_OFF_R  150  // OFF PAD Color Red    [0:255]
#define PZ_OFF_G  150    // OFF PAD Color Green  [0:255]
#define PZ_OFF_B  150  // OFF PAD Color Blue   [0:255]
                                                                        
#define PZ_ON_R   255  // ON PAD Color Red     [0:255]
#define PZ_ON_G   0  // ON PAD Color Green   [0:255]
#define PZ_ON_B   255  // ON PAD Color Blue    [0:255]

// Global Variables
Adafruit_NeoPixel ledPadStripe = Adafruit_NeoPixel((SW_Q*4), LED, NEO_RGB + NEO_KHZ800);

int muxSel[4] = {MUX_D,MUX_C,MUX_B,MUX_A}; // MUX Selector Pins

// Control Arrays for SW PAD
byte SW_MIDI_BYTE_1[SW_Q][2] = {{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF}};     // MIDI Values 1 Byte
byte SW_MIDI_BYTE_2[SW_Q] = {Note_C, Note_Cs, Note_D, Note_Ds, Note_As};             // MIDI Values 2 Byte (Note)
byte SW_MIDI_BYTE_3[SW_Q] = {100,100,100,100,100};     // MIDI Values 3 Byte (Velocity)
int SW_LED[(SW_Q*4)][3] = {{OFF_R}};     // LED PAD RGB Color Values
int SW_CTRL[SW_Q] = {1,1,1,1,1};     // PAD Results

// Control Arrays for PZ PAD
byte PZ_MIDI_BYTE_1[PZ_Q][2] = {{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF},{NOTE_ON,NOTE_OFF}};     // MIDI Values 1 Byte
byte PZ_MIDI_BYTE_2[PZ_Q] = {Note_E, Note_F, Note_Fs, Note_G, Note_Gs, Note_A};             // MIDI Values 2 Byte (Note)
int PZ_CTRL[PZ_Q] = {1,1,1,1,1,1};     // PAD Results
int PZ_THR[PZ_Q] = {PZ_THR_0, PZ_THR_1, PZ_THR_2, PZ_THR_3, PZ_THR_4, PZ_THR_5};

// Control Arrays for Potentiometers
int POT_PIN[2]={POT_0, POT_1};
int POT_MIDI[2][2]={{}};      // Pot MIDI Function and Value
int POT_TOL[2]= {5, 5};       // Variation Tolerance for Potentiometers

int ON_RGB[3]  = {ON_R, ON_G, ON_B};    // ON LED SW PAD Color
int OFF_RGB[3] = {OFF_R, OFF_G, OFF_B}; // OFF LED SW PAD Color

int PZ_ON_RGB[3]  = {PZ_ON_R, PZ_ON_G, PZ_ON_B};    // ON LED SW PAD Color
int PZ_OFF_RGB[3] = {PZ_OFF_R, PZ_OFF_G, PZ_OFF_B}; // OFF LED SW PAD Color

int MAX_MIDI_VEL = 0;
int SW_ITE = 0;
int SW_ITE_MAX = 3;

void setup() {
  Serial.begin(115200);   // Baudrate Set
  ledPadStripe.begin();
  ledPadStripe.show();

  // Set Pin Modes
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_D, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(SWT_0, INPUT);
  pinMode(SWT_1, INPUT);

}

void loop() {
  // SW Handle
  /*if(SW_ITE > SW_ITE_MAX){   // Iterator for Piezo Performance
    SW_PAD_read();
    SW_ITE = 0;
  }else{
    SW_ITE++;
  }*/

  // PZ Handle
  PZ_PAD_Read();
  //delay(10);
}

void SW_PAD_read(){
  for (int i=0; i < SW_Q; i++){
    for(int h=0; h<4; h++){
     digitalWrite(muxSel[h], ((i>>(3-h)) & 0x01)); //MUX Setup pin for each MUX Pin
    }
    delay(10); // Delay por MUX Setup
    if (analogRead(MUX_OUT) < SW_THR){  // If SW Pad activated
      if (!SW_CTRL[i]){                 // if SW Pad not previously activated
        SW_CTRL[i] = 1;                 // Mark Pad as Activated
        // SW LED Control
        for(int h=0; h<4; h++){
          for(int n=0; n<3; n++){ // LED PAD ON Color
               SW_LED[((i*4)+h)][n] = ON_RGB[n];
            }
        }
        SW_LED_update();
        // MIDI USB MSSG
        MIDI_TX(SW_MIDI_BYTE_1[i][0], SW_MIDI_BYTE_2[i], SW_MIDI_BYTE_3[i]);
      }
    }else{
      if (SW_CTRL[i]){ // if SW Pad not previously activated
        SW_CTRL[i] = 0; // Mark Pad as not ctivated
        // SW LED Control
        for(int h=0; h<4; h++){
          for(int n=0; n<3; n++){ // LED PAD ON Color
               SW_LED[((i*4)+h)][n] = OFF_RGB[n];
            }
        }
        SW_LED_update();
        // MIDI USB MSSG
        MIDI_TX(SW_MIDI_BYTE_1[i][1], SW_MIDI_BYTE_2[i], SW_MIDI_BYTE_3[i]);
      }
    }
  }
}


void PZ_PAD_Read(){
  for (int i=0; i<PZ_Q; i++){
    for(int h=0; h<4; h++){
     digitalWrite(muxSel[h], (((i+8)>>(3-h)) & 0x01)); //MUX Setup pin for each MUX Pin
    }
    delay(10); // Delay por MUX Setup
    Serial.print("Channel: ");
    Serial.println(i);
    Serial.print("Read: ");
    Serial.println(analogRead(MUX_OUT));
    /*if (analogRead(MUX_OUT) > PZ_THR[i]){
      if(!PZ_CTRL[i]){   // If PZ not activated
        PZ_CTRL[i] = 1;
        RGB_LED_Control(PZ_ON_RGB[0], PZ_ON_RGB[1], PZ_ON_RGB[2]);
        // MIDI USB MSSG
        //MIDI_TX(PZ_MIDI_BYTE_1[i][0], PZ_MIDI_BYTE_2[i], map(analogRead(MUX_OUT),PZ_THR[i],1024,60,127));
        
      }
    }else{
      if(PZ_CTRL[i]){   // If PZ activated
        PZ_CTRL[i] = 0;
        RGB_LED_Control(PZ_OFF_RGB[0], PZ_OFF_RGB[1], PZ_OFF_RGB[2]);
        // MIDI USB MSSG
        //MIDI_TX(PZ_MIDI_BYTE_1[i][1], PZ_MIDI_BYTE_2[i], 0);
        //delay(PZ_RLX); // Relax time for the Piezo
      }
    }*/
  }
}



/*void LED_SW_Control(int SW_Num, int R, int G, int B){
  for(int i=0; i<LEDPAD_NUM; i++){ // PAD Button Iterator
        ledPadStripe.setPixelColor((i+(j*LEDPAD_NUM)),ledPad[j][i][0],ledPad[j][i][1],ledPad[j][i][2]); // Heavy Stuff
      }
    }
   ledPadStripe.show(); // Update LEDs
}*/

void RGB_LED_Control(int R, int G, int B){
  analogWrite(LED_R, 255- R);
  analogWrite(LED_G, 255- G);
  analogWrite(LED_B, 255- B);
}

/*
 * Function: noteOn()
 * Description: Sends a noteOn MIDI message.
 * Input:
 *  -Channel: MIDI Channel. Recommended 0.
 *  -Pith: Note value, from 0 to 255
 *  -Velocity: Note intensity, form 0 to 255
 * Output:
 *  -Void.
 */
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, uint8_t(0x90 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

/*
 * Function: noteOff()
 * Description: Sends a noteOff MIDI message.
 * Input:
 *  -Channel: MIDI Channel. Recommended 0.
 *  -Pith: Note value, from 0 to 255
 *  -Velocity: Note intensity, form 0 to 255
 * Output:
 *  -Void.
 */
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, uint8_t(0x80 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

/*
 * Function: updateLEDs()
 * Description: Light up each LED with the corresponding value
 * Input:
 *  -None
 * Output:
 *  -Void.
 */
void SW_LED_update(){
  for(int i=0; i < (SW_Q*4); i++){ // PAD Button Iterator
    ledPadStripe.setPixelColor(i,SW_LED[i][1],SW_LED[i][0],SW_LED[i][2]); // Heavy Stuff
  }
  delay(1);
  ledPadStripe.show(); // Update LEDs
}


void POT_Read(){
  for(int i=0; i<2; i++){
    int potRead = map(analogRead(POT_PIN[i]),0,1024,0,127);
    if((potRead <(POT_MIDI[i][1]-POT_TOL[i])) || (potRead <(POT_MIDI[i][1]+POT_TOL[i]))){
      POT_MIDI[i][1] = potRead;
      // Send MIDI Message
    }
  }
}

void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY) 
{
  //byte status1 = MESSAGE + MIDI_CHANNEL;
  //Serial.write(MESSAGE + MIDI_CHANNEL);
  //Serial.write(PITCH);
  //Serial.write(VELOCITY);
  midiEventPacket_t event = {(byte)(MESSAGE >> 4), (byte)(MESSAGE | MIDI_CHANNEL), PITCH, VELOCITY};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

