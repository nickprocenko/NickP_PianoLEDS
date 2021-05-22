 //String myColours[12] = {F00000,0xFF6F77,0xFFBBC1,0xFFDEE3,0xFF8896,0xFF8896,0xFFDEE3,0xFFBBC1,0xFF6F77,0xFF3334,0xC00000};
byte y;

 
#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    144
CRGB leds[NUM_LEDS];

#define NUM_KEYS    61
#include <MIDI.h>  // Add Midi Library



//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
 
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

   
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
 MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 

 
   leds [50] = CRGB :: Red;
FastLED.show();
  
}

void loop() { // Main loop

  MIDI.read(); // Continuously check if Midi data has been received.
  fadeToBlackBy(leds,NUM_LEDS,20);
  FastLED.show();
   
}

 


// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  if ( 26 <= pitch && pitch <= 99){
  byte y = map (pitch, 26, 99, 144,0);
 byte lightPitch = pitch % 12;
  lightPitch = map (lightPitch, 0, 11, 0,255);
 // lightPitch = 30*sin(lightPitch/1.9)+220;
 leds[y] =  CHSV  (lightPitch,150,255);
 leds[y-1] = CHSV  (lightPitch,150,255);

  
   

  }
    FastLED.show();
  }


// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  if ( 26 <= pitch && pitch <= 99){
  byte y = map (pitch, 26, 99, 144,0); 
//leds[y] = CRGB::Black;
//leds[y-1] = CRGB :: Black;
 // FastLED.show();
 
  }
}
