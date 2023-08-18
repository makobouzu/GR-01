#include <M5Stack.h>
#include <ArduinoOSCWiFi.h>
#include "FastLED.h"

const String SSID = "SPWH_L12_bba3d6";
const String PASSWORD = "090a1643b0a54";
const int PORT = 8888;

#define Neopixel_PIN 21
#define NUM_LEDS     36

CRGB leds[NUM_LEDS];

void setup() {
    M5.begin();
    M5.Power.begin();
    M5.Lcd.setTextSize(2);

    WiFi.begin(SSID.c_str(), PASSWORD.c_str());

    M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      M5.Lcd.print(".");
    }
    M5.Lcd.println(" connected.");
    delay(100);
    M5.Lcd.println(WiFi.localIP());

    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(20);
}

void loop() {
  OscWiFi.update();
  OscWiFi.subscribe(PORT, "/toggle", [&](OscMessage& m) {
    if(m.arg<int>(0) == 0){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i].setRGB(0, 0, 0);
        FastLED.show();
      }
    }else if(m.arg<int>(0) == 1){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i].setRGB(0, 255, 0);
        FastLED.show();
      }
    }else if(m.arg<int>(0) == 2){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i].setRGB(238, 120, 0);
        FastLED.show();
      }
    }else if(m.arg<int>(0) == 3){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i].setRGB(0, 0, 255);
        FastLED.show();
      }
    }else if(m.arg<int>(0) == 4){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i].setRGB(255, 0, 0);
        FastLED.show();
      }
    }
  });
}
