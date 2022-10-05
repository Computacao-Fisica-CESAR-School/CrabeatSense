#include <Ultrasonic.h>

Ultrasonic volumeSensor(10, 11);
unsigned int volumeValue;

void setup() {
  Serial.begin(9600);

}

void loop() {
  volumeValue = volumeSensor.read()

  Serial.println(volumeValue + ";0;0;0");
}
