#include <Arduino.h>
#include <Keypad.h>
#include <FastLED.h>
#include <Wire.h>
#include <analogWrite.h>
#include <LiquidCrystal.h>


#define LED_PIN     15
#define NUM_LEDS    54
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define MAX_DIGITS 9

CRGB leds[NUM_LEDS];
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
const byte COLS = 4;
const byte ROWS = 3; 
const byte backLightpin = 33; 
const byte contrast_pin = 32;
char key;
int currentLightColorTopLeft = 0;
int currentLightColorTopCenter = 0;
int currentLightColorTopRight = 0;
int currentLightColorCenterLeft = 0;
int currentLightColorCenter = 0;
int currentLightColorCenterRight = 0;
int currentLightColorBottomLeft = 0;
int currentLightColorBottomCenter = 0;
int currentLightColorBottomRight = 0;
int randNumber;
int response;
int level = 1;
int difficulty[10];
bool proceedToNextLevel;

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

// //Button locations
// //  topLeft     topCenter       topRight        ButtonState
// //  C1R1{1}      C2R1{2}         C3R1{3}          C4R1{A}
// //  centerLeft  center          CenterRight     ButtonReset
// //  C1R2{4}      C2R2{5}         C3R2{6}          C4R2{B}
// //  bottomLeft  bottomCenter    bottomRight     ButtonPlay
// //  C1R3{7}      C2R3{8}         C3R3{9}          C4R3{C}

char Keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'}
};

byte rowPins[ROWS] = {4, 16, 17}; 
byte colPins[COLS] = {5, 18, 19, 21}; 
Keypad keypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS ); 


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

/// <summary>Lightup the led for the location</summary>
void ledToLightUp(int arr[], int color)
{
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

/// <summary>Start a free game play that lights up the led by clicking on the buttons.</summary>
void freePlayMode()
{
    switch (key)
    {
    case '1':
        ledToLightUp(TopLeft, LightColors[currentLightColorTopLeft]);
        currentLightColorTopLeft++;
        currentLightColorTopLeft = currentLightColorTopLeft % 8;
        break;
    case '2':
        ledToLightUp(TopCenter, LightColors[currentLightColorTopCenter]);
        currentLightColorTopCenter++;
        currentLightColorTopCenter = currentLightColorTopCenter % 8;
        break;
    case '3':
        ledToLightUp(TopRight, LightColors[currentLightColorTopRight]);
        currentLightColorTopRight++;
        currentLightColorTopRight = currentLightColorTopRight % 8;
        break;
    case '4':
        ledToLightUp(CenterLeft, LightColors[currentLightColorCenterLeft]);
        currentLightColorCenterLeft++;
        currentLightColorCenterLeft = currentLightColorCenterLeft % 8;
        break;
    case '5':
        ledToLightUp(Center, LightColors[currentLightColorCenter]);
        currentLightColorCenter++;
        currentLightColorCenter = currentLightColorCenter % 8;
        break;
    case '6':
        ledToLightUp(CenterRight, LightColors[currentLightColorCenterRight]);
        currentLightColorCenterRight++;
        currentLightColorCenterRight = currentLightColorCenterRight % 8;
      
        break;
    case '7':
        ledToLightUp(BottomLeft, LightColors[currentLightColorBottomLeft]);
        currentLightColorBottomLeft++;
        currentLightColorBottomLeft = currentLightColorBottomLeft % 8;
        
        break;
    case '8':
        ledToLightUp(BottomCenter, LightColors[currentLightColorBottomCenter]);
        currentLightColorBottomCenter++;
        currentLightColorBottomCenter = currentLightColorBottomCenter % 8;

        break;
    case '9':
        ledToLightUp(BottomRight, LightColors[currentLightColorBottomRight]);
        currentLightColorBottomRight++;
        currentLightColorBottomRight = currentLightColorBottomRight % 8;

        break;
    }
}

/// <summary>Light up the leds that is randomize by the sequence</summary>
void lightSequence(int sequence)
{
    switch (sequence)
    {
        case 1:      
            ledToLightUp(TopLeft, LightColors[6]);
        break;

        case 2:      
            ledToLightUp(TopCenter, LightColors[6]);
        break;

        case 3:      
            ledToLightUp(TopRight, LightColors[6]);
        break;

        case 4:      
            ledToLightUp(CenterLeft, LightColors[6]);
        break;

        case 5:      
            ledToLightUp(Center, LightColors[6]);
        break;

        case 6:      
            ledToLightUp(CenterRight, LightColors[6]);
        break;

        case 7:      
            ledToLightUp(BottomLeft, LightColors[6]);
        break;

        case 8:      
            ledToLightUp(BottomCenter, LightColors[6]);
        break;

        case 9:      
            ledToLightUp(BottomRight, LightColors[6]);
        break;
    }
}

/// <summary>Red colour for wrong answer</summary>
void wrongAnswer()
{
    ledToLightUp(TopLeft, LightColors[3]);
    ledToLightUp(TopCenter, LightColors[3]);
    ledToLightUp(TopRight, LightColors[3]);
    ledToLightUp(CenterLeft, LightColors[3]);
    ledToLightUp(Center, LightColors[3]);
    ledToLightUp(CenterRight, LightColors[3]);
    ledToLightUp(BottomLeft, LightColors[3]);
    ledToLightUp(BottomCenter, LightColors[3]);
    ledToLightUp(BottomRight, LightColors[3]);
}

/// <summary>Turn off all leds</summary>
void turnOffAll()
{
    ledToLightUp(TopLeft, LightColors[7]);
    ledToLightUp(TopCenter, LightColors[7]);
    ledToLightUp(TopRight, LightColors[7]);
    ledToLightUp(CenterLeft, LightColors[7]);
    ledToLightUp(Center, LightColors[7]);
    ledToLightUp(CenterRight, LightColors[7]);
    ledToLightUp(BottomLeft, LightColors[7]);
    ledToLightUp(BottomCenter, LightColors[7]);
    ledToLightUp(BottomRight, LightColors[7]);
}

/// <summary>Game Settings</summary>
void gameSettings()
{
    switch (key)
    {
    case 'A':
        
        break;
    case 'B':

        break;
    case 'C':

        break;
    }
}

/// <summary>Randomize the sequence for the memory game.</summary>
void getSequence()
{
    for (int i = (level - 1); i < level; i++)
    {
        difficulty[i] = random(1, 9);
        Serial.print("Random Number ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(difficulty[i]);
    }
    for (int i = 0; i < level; i++)
    {
        delay(1000);
        lightSequence(difficulty[i]);
        delay(1000);
        turnOffAll();
    }
}

/// <summary>Starts the memory game</summary>
void startMemoryGame()
{
    proceedToNextLevel = false;
    Serial.print("Starting Level ");
    Serial.println(level);

    getSequence();


    for (int i = 0; i < level; i++)
    {
        
        Serial.print("For loop currently at : ");
        Serial.println(i);
        Serial.println("key in button");
        key = keypad.waitForKey();
        // key = keypad.getKey();
        
        if (key)
        {
            Serial.print("Key pressed: ");
            Serial.println(key);
            response = key - '0';
            if (response == difficulty[i])
            {
                lightSequence(difficulty[i]);
                delay(500);
                turnOffAll();
                Serial.print("Level currently at: ");
                Serial.println(level - 1);
                Serial.print("For loop currently at : ");
                Serial.println(i);
                
                if (i == (level - 1))
                {
                    Serial.println("Level UP!");
                    proceedToNextLevel = true;
                }
                else if (level == 10)
                {
                    Serial.println("Congratulation u Win");
                    Serial.println("Restarting Game");
                    level = 1;
                    return;
                }
                
                
            }
            else if (key == 'A' || key == 'B' || key == 'C')
            {
                level = 1;
                return;
            }
            
            else
            {
                Serial.println("You Guessed Wrong");
                Serial.println("Dropping back to Level 1");
                wrongAnswer();
                delay(2000);
                turnOffAll();
                proceedToNextLevel = false;
                break;
            }
            
        }
        
    }

    if (proceedToNextLevel)
    {
        
        level++;
    }
    else
    {
        level = 1;
    }
    

}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

int contrast = 0;

void setup() {

    Serial.begin(115200);
    Serial.println("Starting");
    My_LCD.begin(16, 2); // Initialize The LCD. Parameters: [ Columns, Rows ]
    My_LCD.clear(); // Clears The LCD Display
    pinMode(backLightpin, OUTPUT);
    analogWrite(backLightpin, 210);
    pinMode(contrast_pin, OUTPUT);
    analogWrite(contrast_pin, contrast);
    My_LCD.print("Powering UP");
    My_LCD.setCursor(5, 1);
    My_LCD.print("GG izi");
    
    
    delay( 3000 ); // power-up safety delay
    // currentPalette = RainbowColors_p;
    FastLED.addLeds<LED_TYPE, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
    // My_LCD.clear();
}


void loop()
{
    //turnOffAll();
    //delay(2000);
    // currentPalette = RainbowColors_p;
    // static uint8_t startIndex = 0;
    // startIndex = startIndex + 1; /* motion speed */
    // FillLEDsFromPaletteColors( startIndex);
    // key = keypad.getKey();

    // freePlayMode();

    //startMemoryGame();

}