#include "Screen.h"

Screen::Screen(String WavelengthSMD[], String lightColor[]) : EFX()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->WavelengthSMD[i] = WavelengthSMD[i];
        this->lightColor[i] = lightColor[i];
    }
}

Screen::~Screen()
{
}

void Screen::printDig(byte value)
{
    if (value < 10)
    {
        print("0");
    }

    print(value);
}

void Screen::printTime(byte hh, byte mm)
{
    printDig(hh);

    print(":");

    printDig(mm);
}

void Screen::printWatch(byte hh, byte mm, byte ss)
{
    printDig(hh);

    print(":");

    printDig(mm);

    print(":");

    printDig(ss);
}

void Screen::printDate(byte day, byte month, int year)
{
    printDig(day);

    print("/");

    printDig(month);

    print("/");

    print(year);
}

void Screen::printSpecTime(Watch &watch, byte id)
{
    printTime(watch.startHour[id], watch.startMinute[id]);

    print("-");

    printTime(watch.finishHour[id], watch.finishMinute[id]);
}

void Screen::iGorLogo()
{
    firstPage();
    do
    {
        setHeight(u8g2_font_crox4h_tf);
        textAlign("Smart Garden", PosX::center, PosY::up);
        textAlign("iGor_2019", PosX::center, PosY::center);

    } while (nextPage());
}

void Screen::brightInfo(Pot &pot, Key &key, Timer &timer)
{
    setHeight(u8g2_font_courB08_tn);

    digAlign(pot.bright[key.id], PosX::rightHalf, PosY::downSpace);
}

void Screen::brightInfo(Bright &bright, Key &key, Timer &timer)
{
    setHeight(u8g2_font_pressstart2p_8f);

    digAlign(bright.bright[key.id], PosX::rightHalf, PosY::downSpace);
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot)
{
    if (watch.skip[key.id] && key.screen != key.manual)
    {
        setHeight(u8g2_font_crox4h_tf);

        moveString("SKIP", PosX::center, PosY::downSpace, timer, 2);
    }

    else if (key.screen == key.manual)
    {
        setHeight(u8g2_font_HelvetiPixelOutline_tr);
        textAlign("MANUAL", PosX::leftHalf, PosY::downSpace);

        brightInfo(pot, key, timer);
    }

    else
    {
        setHeight(u8g2_font_courB08_tn);
        setPosition("00:00-00:00", PosX::leftSpace, PosY::downSpace);

        printSpecTime(watch, key.id);
        brightInfo(pot, key, timer);
    }
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright)
{
    if (watch.skip[key.id] && key.screen != key.manual)
    {
        setHeight(u8g2_font_crox4h_tf);

        moveString("SKIP", PosX::center, PosY::downSpace, timer, 3);
    }

    else if (key.screen == key.manual)
    {
        setHeight(u8g2_font_crox4h_tf);

        textAlign("MANUAL", PosX::leftSpace, PosY::downSpace);
        brightInfo(bright, key, timer);
    }

    else
    {
        setHeight(u8g2_font_courB08_tn);
        setPosition("00:00-00:00", PosX::leftSpace, PosY::downSpace);

        printSpecTime(watch, key.id);
        brightInfo(bright, key, timer);
    }
}

void Screen::lampInfo(Watch &watch, Key &key, Timer &timer)
{
    setHeight(u8g2_font_courB08_tf);

    char string[12];
    String(WavelengthSMD[key.id]).toCharArray(string, 12);

    moveString(string, PosX::center, PosY::upHalf, timer, 0);

    setHeight(u8g2_font_crox5tb_tf);

    stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

    stringAlign(state[watch.autoSwitch[key.id] || key.buttonSwitch[key.id]], 4, PosX::rightHalf, PosY::center);
}

void Screen::headerTime(Watch &watch)
{
    setHeight(u8g2_font_courB08_tn);

    setPosition("00:00:00", PosX::rightSpace, PosY::upSpace);

    Time now = watch.time();

    printWatch(now.hour(), now.minute(), now.second());
}

void Screen::headerDate(Watch &watch)
{
    setHeight(u8g2_font_courB08_tf);

    setPosition("00/00/0000", PosX::leftHalf, PosY::upSpace);

    Date now = watch.date();

    printDate(now.day(), now.month(), now.year());

    // setY = 16;
    textAlign(daysOfTheWeek[now.dayOfTheWeek()], PosX::leftHalf, PosY::upHalf);
}

void Screen::setScreen(Bright &brigth, Key &key, Timer &timer)
{
    if (key.screen == key.setBright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Set Set", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(brigth.setBright[key.id], PosX::rightHalf, PosY::center);

            blinkFrame(brigth.setBright[key.id], false, PosX::rightHalf, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::riseScreen(Bright &brigth, Key &key, Timer &timer)
{
    if (key.screen == key.riseBright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Set Rise", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(brigth.riseBright[key.id], PosX::rightHalf, PosY::center);

            blinkFrame(brigth.riseBright[key.id], false, PosX::rightHalf, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::brightScreen(Pot &pot, Key &key, Timer &timer)
{

    if (key.screen == key.maxBright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Set MaxBright", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(pot.maxBright[key.id], PosX::rightHalf, PosY::center);

            blinkFrame(pot.maxBright[key.id], false, PosX::rightHalf, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::maxBrightScreen(Bright &bright, Key &key, Timer &timer)
{
    if (key.screen == key.maxBright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Set MaxBright", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(bright.maxBright[key.id], PosX::rightHalf, PosY::center);

            blinkFrame(bright.maxBright[key.id], false, PosX::rightHalf, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::brightScreen(Bright &bright, Key &key, Timer &timer)
{
    maxBrightScreen(bright, key, timer);

    riseScreen(bright, key, timer);

    setScreen(bright, key, timer);
}

void Screen::timerScreen(Watch &watch, Timer &timer, Key &key)
{
    if (key.screen == key.duration)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_ncenB18_tf);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            setHeight(u8g2_font_profont22_tn);

            setPosition("00:00", PosX::rightHalf, PosY::upHalf);
            printTime(watch.startHour[key.id], watch.startMinute[key.id]);

            setPosition("00:00", PosX::rightHalf, PosY::downHalf);
            printTime(watch.finishHour[key.id], watch.finishMinute[key.id]);

            switch (watch.cursorSpectrum)
            {
            case 0:
                blinkFrame("00:00", 2, PosX::rightHalf, PosY::upFrameHalf, timer, key.valChange());
                break;

            case 1:
                blinkFrame("00:00", 2, PosX::rightFrameHalfSide, PosY::upFrameHalf, timer, key.valChange());
                break;

            case 2:
                blinkFrame("00:00", 2, PosX::rightHalf, PosY::downFrameHalf, timer, key.valChange());
                break;

            case 3:
                blinkFrame("00:00", 2, PosX::rightFrameHalfSide, PosY::downFrameHalf, timer, key.valChange());
                break;

            default:
                break;
            }

        } while (nextPage());
    }
}

void Screen::lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    if (key.screen == key.lamp || key.screen == key.manual)
    {
        firstPage();
        do
        {
            headerTime(watch);
            lampInfo(watch, key, timer);
            bottomLine(watch, timer, key, pot);
        } while (nextPage());
    }
}

void Screen::lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    if (key.screen == key.lamp || key.screen == key.manual)
    {
        firstPage();
        do
        {
            headerTime(watch);
            lampInfo(watch, key, timer);
            bottomLine(watch, timer, key, bright);
        } while (nextPage());
    }
}

void Screen::blinkTime(Key &key, Watch &watch, Timer &timer)
{
    setHeight(u8g2_font_pressstart2p_8f);

    setPosition("00:00:00", PosX::center, PosY::downHalf);

    printWatch(watch.hour, watch.min, watch.sec);

    switch (watch.cursorDateTime)
    {
    case 3:
        blinkFrame("00:00:00", 2, PosX::center, PosY::downFrameHalf, timer, key.valChange());
        break;

    case 4:
        blinkFrame("00:00:00", 2, PosX::centerFrame, PosY::downFrameHalf, timer, key.valChange());
        break;

    case 5:
        blinkFrame("00:00:00", 2, PosX::rightFrameSide, PosY::downFrameHalf, timer, key.valChange());
        break;

    default:
        break;
    }
}

void Screen::blinkDate(Key &key, Watch &watch, Timer &timer)
{
    setHeight(u8g2_font_pressstart2p_8f);

    setPosition("00/00/0000", PosX::center, PosY::upHalf);

    printDate(watch.day, watch.month, watch.year);

    // textAlign(daysOfTheWeek[now.dayOfTheWeek()], PosX::center, PosY::center);

    switch (watch.cursorDateTime)
    {
    case 0:
        blinkFrame("00/00/0000", 2, PosX::center, PosY::upFrameHalf, timer, key.valChange());
        break;

    case 1:
        blinkFrame("00/00/0000", 2, PosX::centerFrame, PosY::upFrameHalf, timer, key.valChange());
        break;

    case 2:
        blinkFrame("00/00/0000", 4, PosX::rightFrameSide, PosY::upFrameHalf, timer, key.valChange());
        break;

    default:
        break;
    }
}

void Screen::setWatchScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.watch)
    {
        firstPage();
        do
        {
            blinkDate(key, watch, timer);
            blinkTime(key, watch, timer);

        } while (nextPage());

        // if (timer.unfrize())
        // {
        //     key.setDateTime = true;
        //     key.screen = key.lamp;
        //     key.autoMove = true;
        // }
    }
}

void Screen::showSunTime(Watch &watch)
{
    setHeight(u8g2_font_9x18_tn);

    setPosition("00:00", PosX::rightSpace, PosY::center);
    printTime(watch.RiseHour, watch.RiseMin);

    setPosition("00:00", PosX::rightSpace, PosY::downSpace);
    printTime(watch.SetHour, watch.SetMin);
}

void Screen::blinkSunTime(Key &key, Timer &timer, Watch &watch)
{
    setHeight(u8g2_font_profont22_tn);

    setPosition("00:00", PosX::center, PosY::center);
    printTime(watch.RiseHour, watch.RiseMin);

    setPosition("00:00", PosX::center, PosY::downSpace);
    printTime(watch.SetHour, watch.SetMin);

    switch (watch.cursorDay)
    {
    case 0:
        blinkFrame("00:00", 2, PosX::center, PosY::centerFrame, timer, key.valChange());
        break;

    case 1:
        blinkFrame("00:00", 2, PosX::rightFrameSide, PosY::centerFrame, timer, key.valChange());
        break;

    case 2:
        blinkFrame("00:00", 2, PosX::center, PosY::downFrameSpace, timer, key.valChange());
        break;

    case 3:
        blinkFrame("00:00", 2, PosX::rightFrameSide, PosY::downFrameSpace, timer, key.valChange());
        break;

    default:
        break;
    }
}

void Screen::intervalScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.interval)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Interval", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            digStringAlign(watch.interval, " m", PosX::center, PosY::center);

            blinkFrame(watch.interval, false, PosX::customFrame, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::riseSpeedScreen(Key &key, Timer &timer)
{
    if (key.screen == key.speed)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Sun Speed", PosX::center, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            digStringAlign(timer.riseMil, " bp", PosX::center, PosY::center);

            blinkFrame(timer.riseMil, false, PosX::customFrame, PosY::centerFrame, timer, key.valChange());

        } while (nextPage());
    }
}

void Screen::sunTimeScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.dayDuration)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("Set SunTime", PosX::center, PosY::upSpace, timer, 1);
            blinkSunTime(key, timer, watch);
        } while (nextPage());

        // if (timer.unfrize())
        // {
        //     key.writeDay = true;
        //     key.correctDay = true;
        //     key.screen = key.lamp;
        //     key.autoMove = true;
        // }
    }
}

void Screen::startScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.start)
    {
        firstPage();
        do
        {
            headerDate(watch);
            headerTime(watch);

            showSunTime(watch);

        } while (nextPage());

        if (timer.unfrize())
        {
            key.screen = key.lamp;
        }
    }
}

void Screen::allBrightScreen(Bright &bright, Key &key, Timer &timer)
{
    if (bright.setAllBrigh(key, timer))
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            moveString("allBright", PosX::leftSpace, PosY::upSpace, timer, 4);

            setHeight(u8g2_font_ncenB18_tf);

            digAlign(bright.allBrigh, PosX::leftHalf, PosY::center);

            blinkFrame(bright.allBrigh, false, PosX::leftHalf, PosY::centerFrame, timer, key.valChange());

            for (byte i = 0; i < lampAmount; i++)
            {
                setHeight(u8g2_font_pressstart2p_8f);

                // convStr(lightColor[i]);
                strDigAlign(convStr(lightColor[i]), bright.maxBright[i], PosX::leftHalf, PosY::custom);
            }

        } while (nextPage());

        if (timer.unfrize() && !key.allBrigh())
        {
            key.setAll = false;
            key.screen = key.lamp;
        }
    }
}

void Screen::screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    lampScreen(watch, switchers, timer, key, pot);
    brightScreen(pot, key, timer);

    startScreen(watch, key, timer);
    setWatchScreen(watch, key, timer);
    sunTimeScreen(watch, key, timer);
    timerScreen(watch, timer, key);
    riseSpeedScreen(key, timer);
    intervalScreen(watch, key, timer);
}

void Screen::screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    lampScreen(watch, switchers, timer, key, bright);
    brightScreen(bright, key, timer);
    allBrightScreen(bright, key, timer);

    startScreen(watch, key, timer);
    setWatchScreen(watch, key, timer);
    sunTimeScreen(watch, key, timer);
    timerScreen(watch, timer, key);
    riseSpeedScreen(key, timer);
    intervalScreen(watch, key, timer);
}
