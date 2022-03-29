////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////
////// Info, guides and tutorials on:
////// https://ziotester.github.io
//////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <Arduino.h>

#include "SPIFFS.h"

const char *filename = "/test.txt";

void setup() {
  Serial.begin(115200);

  /*

  SPIFFS BEGIN

  */
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  Serial.println("========================================");

  /*

  FILE WRITE

  */
  Serial.printf("Writing file: %s\r\n", filename);  
  File file_write = SPIFFS.open(filename, FILE_WRITE);
  if (!file_write) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file_write.print("Hello world! This text is from spiffs file!")) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file_write.close();
  Serial.println("========================================");

  /*

  FILE READ

  */
  Serial.printf("Reading file: %s\r\n", filename);
  File file = SPIFFS.open(filename);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }
  Serial.println("- read from file:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  Serial.println();
  Serial.println("========================================");
}

void loop() {}