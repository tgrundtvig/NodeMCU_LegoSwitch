/*
  Author: Tobias Grundtvig
*/

#ifndef GreySwitchCtrl_h
#define GreySwitchCtrl_h

#include <Arduino.h>
#include <Servo.h>
#include <SwitchCtrl.h>
#include <SwitchListener.h>

class GreySwitchCtrl : public SwitchCtrl
{
public:
    GreySwitchCtrl( uint8_t pmwPin);
    void setListener(SwitchListener* pListener) {_pListener = pListener;}
    void update(unsigned long curTime);
    bool switchTo(uint8_t side);
    uint8_t getState() {return _state;}
private:
    Servo _servo;
    SwitchListener* _pListener;
    uint8_t _state;
    unsigned long _startTime;
    unsigned long _curTime;
};

#endif