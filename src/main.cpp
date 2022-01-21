//+--------------------------------------------------------------------------
//
// File:        main.cpp
//
// Chieftain - (c) 2018 Plummer's Software LLC.  All Rights Reserved.  
//
// This file is part of the Chieftain software project.
//
//    Chieftain is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//   
//    Chieftain is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//   
//    You should have received a copy of the GNU General Public License
//    along with Chieftain.  It is normally found in copying.txt
//    If not, see <https://www.gnu.org/licenses/>.
//
// Description:
//
//    Chieftain is PWM control of a single RGB LED.  It runs on the 
//    Arduino Nano 328P.  The goal is to smoothly color cycle a 
//    palette effect on a single large, 10-50W LED.  To control the
//    LED, I am using a triplet of 13005N NPN transistors.  PWN pins
//    3, 5, 6 each control a transistor which is in turn connected to
//    the R, G, and B legs, respectively, of this large common anode
//    LED.
//
//    Remember, as always, not suitability for any purpose is implied.
//
// History:     Jan-12-2022         Davepl      Created
//
//---------------------------------------------------------------------------
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
    static const CRGB colorAmber = CRGB(255, 48, 0);

    CRGBPalette256 palette = { CRGB::White, CRGB::White, CRGB::White,
                               colorAmber, colorAmber, colorAmber,
                               CRGB::Red, CRGB::Red, CRGB::Red,
                               CRGB::Blue, CRGB::Blue, CRGB::Blue, 
                               CRGB::Purple, CRGB::Purple, CRGB::Purple,
                               CRGB::Black
                             };

    EVERY_N_MILLIS(10)
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

        const uint8_t brightness = 255;

        colorNumber = fmod(colorNumber += .05, 256);
        CRGB thisColor = ColorFromPalette(palette, colorNumber, brightness);
        CRGB nextColor = ColorFromPalette(palette, colorNumber + 1, brightness);

        float frac = colorNumber - (int) colorNumber;
        CRGB c = thisColor.lerp16(nextColor, frac * 65535);

        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

        analogWrite(3, c.r * 9 / 12 * 4 / 5);
        analogWrite(5, c.g * 11 / 12 * 4 / 5);
        analogWrite(6, c.b * 12 / 12 * 4 / 5);
    }
}