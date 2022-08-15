/*
  Author: Tobias Grundtvig
*/

#ifndef SwitchCtrl_h
#define SwitchCtrl_h

#include "SwitchListener.h"

#define STATE_LEFT 0
#define STATE_RIGHT 1
#define STATE_SWITCHING_LEFT 2
#define STATE_SWITCHING_RIGHT 3
#define LEFT 0
#define RIGHT 1

class SwitchCtrl
{
public:
    virtual void setListener(SwitchListener* pListener) = 0;
    virtual void update(unsigned long curTime) = 0;
    virtual bool switchTo(uint8_t side) = 0;
    virtual uint8_t getState() = 0;
};

#endif