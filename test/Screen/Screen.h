#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Watch.h>
#include <Switchers.h>
#include <Timer.h>
#include <Key.h>
#include <Pot.h>
#include <Bright.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

class Screen : public Adafruit_SSD1306
{
private:
    String WavelengthSMD[lampAmount];
    String lightColor[lampAmount];

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

public:
    Screen(String *WavelengthSMD, String *lightColor);
    ~Screen();

    void begin();
    void iGorLogo();

    void showDig(byte value);

    void headerTime(Watch &watch);
    void headerDate(Watch &watch);
    void headerScreen(Watch &watch);

    void showBlink(byte x, byte y, Timer &timer, byte val);
    void showBlinkBig(byte x, byte y, Timer &timer);
    void showBlinkYear(byte x, byte y, Timer &timer);
    void showBlinkSpectrumTime(Watch &watch, Timer &timer, Key &key);

    void showStringTime(byte hh, byte mm);
    void showStringWatch(byte hh, byte mm, byte ss);
    void showSpectrumTime(Watch &watch, byte id);

    void showAlert();

    void brightInfo(Pot &pot, Key &key, Timer &timer);
    void brightInfo(Bright &bright, Key &key, Timer &timer);

    void bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot);
    void bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright);

    void lampInfo(Watch &watch, Key &key);

    void showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);

    void showStartScreen(Watch &watch, Key &key, Timer &timer);

    void blinkHeaderDate(Key &key, Watch &watch, Timer &timer);
    void blinkHeaderTime(Key &key, Watch &watch, Timer &timer);

    void showBlinkSunRise(Key &key, Timer &timer, Watch &watch, byte hh, byte mm);
    void showBlinkSunSet(Key &key, Timer &timer, Watch &watch, byte hh, byte mm);
};

#endif