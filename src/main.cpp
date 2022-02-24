#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 15
#define NUM_LEDS    54
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void topLeft(int color){
    leds[6] = color;
    leds[7] = color;
    leds[8] = color;
    leds[9] = color;
    leds[10] = color;
    leds[11] = color;
    FastLED.show();
}
void topCenter(int color){
    leds[3] = color;
    leds[4] = color;
    leds[5] = color;
    leds[12] = color;
    leds[13] = color;
    leds[14] = color;
    FastLED.show();
}
void topRight(int color){
    leds[0] = color;
    leds[1] = color;
    leds[2] = color;
    leds[15] = color;
    leds[16] = color;
    leds[17] = color;
    FastLED.show();
}
void centerRight(int color){
    leds[18] = color;
    leds[19] = color;
    leds[20] = color;
    leds[30] = color;
    leds[31] = color;
    leds[32] = color;
    FastLED.show();
}
void center(int color){
    leds[21] = color;
    leds[22] = color;
    leds[23] = color;
    leds[33] = color;
    leds[34] = color;
    leds[35] = color;
    FastLED.show();
}
void centerLeft(int color){
    leds[24] = color;
    leds[25] = color;
    leds[26] = color;
    leds[27] = color;
    leds[28] = color;
    leds[29] = color;
    FastLED.show();
}
void bottomRight(int color){
    leds[36] = color;
    leds[37] = color;
    leds[38] = color;
    leds[51] = color;
    leds[52] = color;
    leds[53] = color;
    FastLED.show();
}
void bottomCenter(int color){
    leds[39] = color;
    leds[40] = color;
    leds[41] = color;
    leds[48] = color;
    leds[49] = color;
    leds[50] = color;
    FastLED.show();
}
void bottomLeft(int color){
    leds[42] = color;
    leds[43] = color;
    leds[44] = color;
    leds[45] = color;
    leds[46] = color;
    leds[47] = color;
    FastLED.show();
}

enum LightState{
    On = 0x4682B4,
    Off = 0x000000
};

void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
}

void loop() {
//    for( int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed += 1 ) {
//       // Turn our current led on to white, then show the leds
//       leds[whiteLed] = CRGB::Black;
      
//       // Show the leds (only one of which is set to white, from above)
//       FastLED.show();

//       // Wait a little bit
//       delay(100);
//       // Turn our current led back to black for the next loop around
//       leds[whiteLed] = CRGB::WhiteSmoke;
//       }
    topLeft(0x4682B4);
    topCenter(0xD2B48C);
    topRight(0x008080);
    centerRight(0xD8BFD8);
    center(0xFF6347);
    centerLeft(0x40E0D0);
    bottomRight(0xEE82EE);
    bottomLeft(0xF5DEB3);
    bottomCenter(0xFFFF00);
    delay(100);
}



