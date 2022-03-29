#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

struct Config {
  String sid;
  String password;
};

const char *configFile = "/conf.json";
Config wifiConfig;

void loadConfiguration(const char *filename, Config &config) {
  File file = SPIFFS.open(filename);

  StaticJsonDocument<512> doc;

  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println(F("Failed to read file, using default configuration"));
  }
  config.sid = doc[0].as<String>();
  config.password = doc[1].as<String>();
  file.close();
}

void saveConfiguration(const char *filename, const Config &config) {
  SPIFFS.remove(filename);

  File file = SPIFFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<512> doc;

  doc[0] = config.sid;
  doc[1] = config.password;

  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS initialisation failed. Please reboot.");
    while (1) yield();
  }

  wifiConfig.sid = "this_is_my_sid";
  wifiConfig.password = "this_is_my_pwd";
  saveConfiguration(configFile, wifiConfig);

  loadConfiguration(configFile, wifiConfig);

  Serial.println(" ");
  Serial.println("=============================");
  Serial.println(wifiConfig.sid);
  Serial.println(wifiConfig.password);
  Serial.println("=============================");
}

void loop() {}