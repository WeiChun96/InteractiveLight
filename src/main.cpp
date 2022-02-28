#include <Arduino.h>
#include <Keypad.h>
#include <FastLED.h>

#define LED_PIN     15
#define NUM_LEDS    54
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// //Led light locations
// // topLeft      topCenter       topRight
// // 8 7 6        5 4 3           2 1 0
// // 9 10 11      12 13 14        15 16 17
// // centerLeft   center          centerRight
// // 26 25 24     23 22 21        20 19 18
// // 27 28 29     30 31 32        33 34 35
// // bottomLeft   bottomCenter    bottomRight
// // 44 43 42     41 40 39        38 37 36
// // 45 46 47     48 49 50        51 52 53
int TopLeft[] = {6, 7, 8, 9, 10, 11};
int TopCenter[] = {3, 4, 5, 12, 13, 14};
int TopRight[] = {0, 1, 2, 15, 16, 17};
int CenterLeft[] = {24, 25, 26, 27, 28, 29};
int Center[] = {21, 22, 23, 30, 31, 32};
int CenterRight[] = {18, 19, 20, 33, 34, 35};
int BottomLeft[] = {42, 43, 44, 45, 46, 47};
int BottomCenter[] = {39, 40, 41, 48, 49, 50};
int BottomRight[] = {36, 37, 38, 51, 52, 53};


int LightColors[] = {
    CRGB::Crimson,
    CRGB::Coral,
    CRGB::Yellow,
    CRGB::ForestGreen,
    CRGB::Blue,
    CRGB::Indigo,
    CRGB::BlueViolet,
    CRGB::Black
};

void ledToLightUp(int arr[6], int color){
    for (int i = 0; i < 6; i++)
    {
        leds[arr[i]] = color;
        
    }
    FastLED.show();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
// //Button locations
// //  topLeft     topCenter       topRight        ButtonState
// //  C1R1        C2R1            C3R1            C4R1
// //  centerLeft  center          CenterRight     ButtonReset
// //  C1R2        C2R2            C3R2            C4R2
// //  bottomLeft  bottomCenter    bottomRight     ButtonPlay
// //  C1R3        C2R3            C3R3            C4R3


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void setup() {
    delay( 3000 ); // power-up safety delay
    
    // currentPalette = RainbowColors_p;
    FastLED.addLeds<LED_TYPE, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );

}


void loop()
{
    ledToLightUp(TopRight, LightColors[0]);
    ledToLightUp(TopCenter, LightColors[1]);
    ledToLightUp(TopLeft, LightColors[2]);
    ledToLightUp(CenterRight, LightColors[3]);
    ledToLightUp(Center, LightColors[4]);
    ledToLightUp(CenterLeft, LightColors[5]);
    ledToLightUp(BottomRight, LightColors[6]);
    ledToLightUp(BottomCenter, LightColors[7]);
    ledToLightUp(BottomLeft, LightColors[0]);
    // currentPalette = RainbowColors_p;
    // static uint8_t startIndex = 0;
    // startIndex = startIndex + 1; /* motion speed */
    // FillLEDsFromPaletteColors( startIndex);
    
    

    FastLED.delay(1000);
}