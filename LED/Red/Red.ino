/* This example shows how to display a moving rainbow pattern on
   an APA102-based LED strip. */

/* By default, the APA102 library uses pinMode and digitalWrite
   to write to the LEDs, which works on all Arduino-compatible
   boards but might be slow.  If you have a board supported by
   the FastGPIO library and want faster LED updates, then install
   the FastGPIO library and uncomment the next two lines: */
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

#include <APA102.h>

// Define which pins to use.
const uint8_t dataPin = 11;
const uint8_t clockPin = 12;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Set the number of LEDs to control.
const uint16_t ledCount = 38;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

// Set the brightness to use (the maximum is 31).
const uint8_t brightness = 1;

void setup()
{
  Serial.begin(9600);
}

/* Converts a color from HSV to RGB.
   h is hue, as a number between 0 and 360.
   s is the saturation, as a number between 0 and 255.
   v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return rgb_color(r, g, b);
}

void loop()
{
  if (Serial.available()) {
    char Byte = Serial.read();
    // RESET
    if (Byte == '0') {
      for (uint16_t i = 0; i < 60; i++)
      {
        colors[i] = hsvToRgb(0, 0, 0);
      }
      ledStrip.write(colors, 60, 0);
    }
    // White circle
    if (Byte == '1') {
      uint8_t time = millis() >> 4;
      for (uint16_t f = 0; f < 15; f++)
      {

        for (uint16_t i = 0; i <= ledCount; i++)
        {
          colors[i] = hsvToRgb(0, 0, 0);
        }
        ledStrip.write(colors, ledCount, 31);

        for (uint16_t j = 0; j <= ledCount; j++)
        {
          for (uint16_t k = 0; k < j; k++)
          {
            colors[k] = hsvToRgb(255, 0, 255);
          }
          ledStrip.write(colors, ledCount, 31);
        }
        delay(1);
      }
    }
    // YELLOW
    if (Byte == '2') {

      uint8_t time = millis() >> 4;
      for (uint16_t f = 0; f <= 0; f++)
      {

        for (uint16_t i = 0; i < 255; i++)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(60, 255,  i);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        delay(10);
        for (uint16_t i = 255; i > 0; i--)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(60, 255, i );
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        ledStrip.write(colors, ledCount, 0);
        delay(10);

      }

    }

    //ERROR
    if (Byte == '3') {
      uint8_t time = millis() >> 4;

      for (uint16_t f = 0; f < 5; f++)
      {


        for (uint16_t i = 0; i < 30; i++)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(0, 255, 8 * i);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }

        for (uint16_t i = 30; i > 0; i--)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(0, 255, i * 8);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        ledStrip.write(colors, ledCount, 0);
        delay(100);

      }
    }


    //BLUE
    if (Byte == '4') {
      uint8_t time = millis() >> 4;
      for (uint16_t f = 0; f <= 0; f++)
      {

        for (uint16_t i = 0; i < 255; i++)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(240, 255,  i);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        delay(10);
        for (uint16_t i = 255; i > 0; i--)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(240, 255, i );
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        ledStrip.write(colors, ledCount, 0);
        delay(10);

      }
    }

    //GREEN
    if (Byte == '5') {
      uint8_t time = millis() >> 4;
      for (uint16_t f = 0; f <= 0; f++)
      {

        for (uint16_t i = 0; i < 255; i++)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(120, 255,  i);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        delay(10);
        for (uint16_t i = 255; i > 0; i--)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(120, 255, i );
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        ledStrip.write(colors, ledCount, 0);
        delay(10);

      }
    }

    //BROWN
    if (Byte == '6') {
      uint8_t time = millis() >> 4;
      for (uint16_t f = 0; f <= 0; f++)
      {

        for (uint16_t i = 0; i < 255; i++)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(25, 220,  i);
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        delay(10);
        for (uint16_t i = 255; i > 0; i--)
        {
          for (uint16_t j = 0; j < ledCount; j++)
          {
            colors[j] = hsvToRgb(25, 220, i );
          }
          ledStrip.write(colors, ledCount, 31);
          delay(1);
        }
        ledStrip.write(colors, ledCount, 0);
        delay(10);

      }
    }
  }
}
