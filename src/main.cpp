#include <Arduino.h>
#include "accesspoint.h"

#define DEBUG true

void setup() {
  Serial.begin(115200);
 //initialize Access POint
 accessPointInit(DEBUG);
 //SERVE HTML File
 serveHTML(DEBUG);
}

void loop() {

}
