#include "Pot.h"

Pot::Pot(byte amount)
{
    // lampAmount = amount;
    
    // bright = new byte[lampAmount];

    // maxBright = new byte[lampAmount];
    // prewMaxBright = new byte[lampAmount];

    // pot = new DigiPot[lampAmount];
}

Pot::~Pot()
{
}

void Pot::setPot(DigiPot pot[])
{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->pot[i] = pot[i];
    }
}

void Pot::setMinBright(DigiPot &pot, byte &bright)
{
    if (bright < autoMinBright)
    {
        pot.set(autoMinBright);
        bright = pot.get();
    }
}

void Pot::resetBright(DigiPot &pot, byte &bright)
{
    pot.set(minManualBright);
    bright = pot.get();
}

void Pot::autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i)
{
    if (watch.autoSwitch[i] && !watch.skip[i] && !key.reduration[i] && !key.reBright[i])
    {
        if (!watch.brightDown[i])
        {
            setMinBright(pot[i], bright[i]);

            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] < maxBright[i])
            {
                pot[i].increase(1);
                bright[i] = pot[i].get();
            }
        }

        if (watch.brightDown[i])
        {
            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] > autoMinBright)
            {
                pot[i].decrease(1);
                bright[i] = pot[i].get();
            }

            if (bright[i] == autoMinBright)
            {
                watch.autoSwitch[i] = false;
                watch.brightDown[i] = false;
                resetBright(pot[i], bright[i]);
            }
        }
    }
    else if (watch.skip[i] && key.screen != key.manual)
    {
        pot[i].set(minManualBright);
        bright[i] = pot[i].get();
    }
}

void Pot::autoBright(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen != key.manual || key.screen != key.bright)
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            autoChangeBright(watch, key, timer, i);
        }
    }
    if (key.resetManualPot)
    {
        resetAllPots();
        key.resetManualPot = false;
    }
}

void Pot::changeBright(byte &bright, DigiPot &pot, Key &key, Timer &timer)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS && bright > autoMinBright)
        {
            bright--;
            pot.decrease(1);
        }
        else if (key.act == key.PLUS && bright < maxManualBright)
        {
            bright++;
            pot.increase(1);
        }
    }
}

void Pot::manualChangeBright(Key &key, Timer &timer)
{
    if (key.screen == key.manual)
    {
        if (key.buttonSwitch[key.id])
        {
            setMinBright(pot[key.id], bright[key.id]);
            changeBright(bright[key.id], pot[key.id], key, timer);
        }

        else
        {
            pot[key.id].set(minManualBright);
            bright[key.id] = pot[key.id].get();
        }
    }
}

void Pot::resetAllPots()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        pot[i].reset();
        bright[i] = pot[i].get();
    }
}

void Pot::correctBright(boolean brightDown, DigiPot &pot, byte &bright, byte maxBright, byte id)
{
    if (!brightDown)
    {
        pot.set(maxBright);
        bright = pot.get();
    }

    else if (brightDown)
    {
        if (prewMaxBright[id] > maxBright)
        {
            pot.decrease(prewMaxBright[id] - maxBright);
            bright = pot.get();
        }

        else if (prewMaxBright[id] < maxBright)
        {
            pot.increase(maxBright - prewMaxBright[id]);
            bright = pot.get();
        }
    }
}

void Pot::changeMaxBright(Key &key, Watch &watch, Timer &timer)
{
    if (key.changeMaxBright())
    {
        prewMaxBright[key.id] = maxBright[key.id];
        key.reBright[key.id] = true;
    }

    else if (key.screen == key.bright)
    {
        if (key.valChange(timer))
        {
            if (key.act == key.MINUS && maxBright[key.id] > autoMinBright)
            {
                maxBright[key.id]--;
            }

            if (key.act == key.PLUS && maxBright[key.id] < maxManualBright)
            {
                maxBright[key.id]++;
            }
        }
    }

    if (key.correctBright)
    {
        if (watch.autoSwitch[key.id])
        {
            correctBright(watch.brightDown[key.id], pot[key.id], bright[key.id], maxBright[key.id], key.id);
        }

        key.correctBright = false;
        key.reBright[key.id] = false;
    }
}
