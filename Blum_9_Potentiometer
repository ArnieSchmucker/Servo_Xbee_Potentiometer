#include <SoftwareSerial.h>
SoftwareSerial XBee(2,3);

int potPin = 0;

void setup() {
  Serial.begin(9600);
  XBee.begin(9600);

}

void loop() {
  int val = map(analogRead(potPin), 0, 1023, 0, 179);
  Serial.println(val);
  XBee.print('<');
  XBee.print(val);
  XBee.println('>');
  delay(10);
}
