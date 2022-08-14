/*
  Author: Tobias Grundtvig
*/

#ifndef SwitchListener_h
#define SwitchListener_h

#include <Arduino.h>


class SwitchListener
{
public:
    virtual void onStateChange(uint8_t newState) = 0;
};

#endif