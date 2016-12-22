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
#define NUMPIXELS 32

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

int delayval = 200; // delay for half a second
int modeInterval = 18000; // in millis

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
  pixels.setBrightness(55); // 1/3 brightness
  // set initial time
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  //uint32_t t;
  switch (mode) {

    case 0: // Random sparks - just one LED on at a time!
      randomGreenReds(400);
      break;

    case 1: // Spinny wheels (8 LEDs on at a time)
      spinnyWheels(500);
      break;

    case 2:
      spinGreenRed(400);
      break;

    case 3:
      fadeGreenToRed(400);
      break;

    case 4:
      fadeBlue(200);
      break;

    case 5:
      randomRedGreenBlue(400);
      break;
  }
  modeSwitchClock();
}

/////////////////////////////////
// case 5
void randomRedGreenBlue(uint8_t delayBy) {
  pixels.setBrightness(50);
  uint8_t  r;
  uint8_t  g;
  uint8_t  b;
  uint8_t  off;
  uint8_t  off2;
  uint8_t  randBright;
  r = random(NUMPIXELS / 2);
  g = random(NUMPIXELS / 2, NUMPIXELS);
  b = random(NUMPIXELS);
  randBright = random(255);
  pixels.setPixelColor(r, pixels.Color(randBright, 0, 0));
  pixels.setPixelColor(g, pixels.Color(0, randBright, 0));
  pixels.setPixelColor(b, pixels.Color(0, 0, randBright));
  pixels.show();
  delay(delayBy);

  off = random(NUMPIXELS);
  off2 = random(NUMPIXELS);
  pixels.setPixelColor(off, 0);
  pixels.setPixelColor(off2, 0);
  pixels.show();
  delay(delayBy);
}
// end case 0
/////////////////////////////////

/////////////////////////////////
// case 4
void fadeBlue(uint8_t delayBy) {
  pixels.setBrightness(50);
  for (int b = 0; b < 255; b++) {
    for (int i = 0; i < NUMPIXELS / 2; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, b));
      pixels.show();  // send updated pixel color to the hardware.
      //delay(delayBy);
    }
    for (int j = 16; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(0, 0, 255 - b));
      pixels.show();  // send updated pixel color to the hardware.
      //delay(delayBy);
    }
  }
  for (int b = 255; b > 0; b--) {
    for (int i = 0; i < NUMPIXELS / 2; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, b));
      pixels.show();  // send updated pixel color to the hardware.
      //delay(delayBy);
    }
    for (int j = 16; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(0, 0, 255 - b));
      pixels.show();  // send updated pixel color to the hardware.
      //delay(delayBy);
    }
  }
}

/////////////////////////////////
// case 3
void fadeGreenToRed(uint8_t delayBy) {
  uint8_t  randBright;
  uint8_t  r;
  uint8_t  g;
  uint8_t  b;
  randBright = random(100);
  r          = random(255);
  g          = random(255);
  b          = random(255);
  //pixels.setBrightness(155 + randBright);
  for (int i = 0; i < NUMPIXELS; i++) {
    uint32_t c = 0;
    //randBright = random(155);
    //pixels.setBrightness(100+randBright); // 1/3 brightness
    if (((offset + i) & 7) < 6) c = color; // 4 pixels on...
    pixels.setPixelColor(   i, c); // First eye
    pixels.setPixelColor(NUMPIXELS - i, c); // Second eye (flipped)
    //pixels.setPixelColor(NUMPIXELS - i -1, pixels.Color(r,g,b)); // Second eye (flipped)
    //pixels.setPixelColor(NUMPIXELS - i -2, pixels.Color(r,g,b)); // Second eye (flipped)
  }
  pixels.show();
  offset++;
  delay(delayBy);
}

/////////////////////////////////
// case 0
void randomGreenReds(uint8_t delayBy) {
  uint8_t  r;
  uint8_t  g;
  uint8_t  off;
  uint8_t  off2;
  uint8_t  randBright;
  r = random(NUMPIXELS);
  g = random(NUMPIXELS);
  randBright = random(155);
  pixels.setPixelColor(r, pixels.Color(255, 0, 0));
  //pixels.setBrightness(100 + randBright);
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
  uint8_t  randBright;
  randBright = random(155);
  //pixels.setBrightness(100 + randBright); // 1/3 brightness
  for (int i = 0; i < NUMPIXELS; i++) {
    uint32_t c = 0;
    if (((offset + i) & 7) < 4) c = color; // 4 pixels on...
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
    pixels.setPixelColor(i + 2, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i + 1, pixels.Color(0, 255, 0)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 255, 255)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 2, pixels.Color(255, 0, 255)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 3, pixels.Color(0, 0, 255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayBy); // Delay for a period of time (in milliseconds).
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.setPixelColor(i + 1, pixels.Color(0, 255, 0)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i, pixels.Color(0, 0, 255)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 255, 255)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 2, pixels.Color(0, 255, 255)); // Moderately bright green color.
    pixels.setPixelColor(NUMPIXELS - i - 3, pixels.Color(0, 0, 255)); // Moderately bright green color.
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
  if ((t - prevTime) > modeInterval) {     // Every 8 seconds...
    mode++;                        // Next mode
    if (mode > 5) {                // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                  // Next color R->G->B
      if (!color) color = 0xFF0000; // Reset to red
    }
    //for (int i = 0; i < 32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}
