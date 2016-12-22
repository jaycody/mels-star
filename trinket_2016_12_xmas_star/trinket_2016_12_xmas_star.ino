/* jstephens 2016_12
    Trinket Pro & 2 NeoPixel 16-LED Ring
    Christmas Tree Star
*/

// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define PIN 0
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

int delayval = 200; // delay for half a second

void setup() {
  /////////////////////////////////
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  /////////////////////////////////
  // initialize neopixel library
  pixels.begin();
  // set brightness
  pixels.setBrightness(85); // 1/3 brightness
  // set initial time
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  //uint32_t t;
  switch (mode) {

    case 0: // Random sparks - just one LED on at a time!
      randomGreenReds(200);
      break;

    case 1: // Spinny wheels (8 LEDs on at a time)
      spinnyWheels(200);
      break;

    case 2:
      spinGreenRed(200);
      break;
  }
  modeSwitchClock();
}

/////////////////////////////////
// case 0
void randomGreenReds(uint8_t delayBy) {
  uint8_t  r;
  uint8_t  g;
  uint8_t  off;
  uint8_t  off2;
  r = random(NUMPIXELS);
  g = random(NUMPIXELS);
  pixels.setPixelColor(r, pixels.Color(255, 0, 0));
  pixels.setPixelColor(g, pixels.Color(0, 255, 0));
  pixels.show();
  delay(delayBy);

  off = random(NUMPIXELS);
  off2 = random(NUMPIXELS);
  pixels.setPixelColor(off, 0);
  pixels.show();
  delay(delayBy);
}
// end case 0
/////////////////////////////////


/////////////////////////////////
// case 1
void spinnyWheels(uint8_t delayBy) {
  for (int i = 0; i < 16; i++) {
    uint32_t c = 0;
    if (((offset + i) & 7) < 2) c = color; // 4 pixels on...
    pixels.setPixelColor(   i, c); // First eye
    pixels.setPixelColor(NUMPIXELS - i, c); // Second eye (flipped)
  }
  pixels.show();
  offset++;
  delay(delayBy);
}
// end case 1
/////////////////////////////////


/////////////////////////////////
// case 2
void spinGreenRed(uint8_t delayBy) {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Moderately bright green color.
    pixels.setPixelColor(i + 1, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayBy); // Delay for a period of time (in milliseconds).
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(i + 1, pixels.Color(0, 255, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayBy); // Delay for a period of time (in milliseconds).
  }
}
// end case 2
/////////////////////////////////


/////////////////////////////////
// mode switcher
void modeSwitchClock() {
  uint32_t t;
  t = millis();
  if ((t - prevTime) > 8000) {     // Every 8 seconds...
    mode++;                        // Next mode
    if (mode > 2) {                // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                  // Next color R->G->B
      if (!color) color = 0xFF0000; // Reset to red
    }
    for (int i = 0; i < 32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}
