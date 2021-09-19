#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Data.h>

class Timer
{
    friend class Pot;
    friend class Bright;
    friend class Screen;
    friend class Key;
    friend class EFX;

private:
    unsigned long prewCounterMillis;
    unsigned long secMillis = 1000;

    unsigned long prewScreenMillis;
    unsigned long displayMillis = 3000;

    unsigned long prewCursorMillis;

    unsigned long prewBlinkMillis;
    unsigned long blinkMillis = 500;

    unsigned long prewBrightMillis[lampAmount];

    unsigned long riseMillis = 100;

    unsigned long prewMoveMillis;

    const byte maxEscapeCounter = 5;
    byte escapeCounter = maxEscapeCounter;

    byte maxCounter = 5;

    byte unfrizeCounter = maxCounter;

    boolean escBar;
    boolean blink;
    boolean move;

public:
    Timer();
    ~Timer();

    void minusCounter(byte &counter);
    boolean wait(unsigned long &prewMillis, unsigned long setMillis);
    boolean blinkReady();
    boolean unfrize();
    void resetCounter();
    boolean moveReady();
};

#endif