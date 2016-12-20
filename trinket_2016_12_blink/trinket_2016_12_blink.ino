/* jstephens 2016_12
 *  Trinket Pro 
 *  Blink Hello World
 */

int led = 1; // blink 'digital' pin 1 - the built-in LED


void setup() {
  // initialize the digital pin as an output
 pinMode(led, OUTPUT);

}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

