#include <Arduino.h>
#define FASTLED_INTERNAL 1
#include <FastLED.h>

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{

    static float colorNumber;

    CRGBPalette256 palette = { CRGB::Red, CRGB::Red, CRGB::Red,
                               CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, 
                               CRGB::Green, CRGB::Green, CRGB::Green, 
                               CRGB::Blue, CRGB::Blue, CRGB::Blue, 
                               CRGB::Purple, CRGB::Purple, CRGB::Purple,
                               CRGB(CRGB::Red).lerp16(CRGB::Purple, 16386)
                             };

    EVERY_N_MILLIS(10)
    {
        colorNumber = fmod(colorNumber += .05, 256);
        CRGB thisColor = ColorFromPalette(palette, colorNumber);
        CRGB nextColor = ColorFromPalette(palette, colorNumber + 1);

        float frac = colorNumber - (int) colorNumber;
        CRGB c = thisColor.lerp16(nextColor, frac * 65535);
        
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        analogWrite(3, c.r * 9 / 12);
        analogWrite(5, c.g * 11 / 12);
        analogWrite(6, c.b * 12 / 12);
    }
}