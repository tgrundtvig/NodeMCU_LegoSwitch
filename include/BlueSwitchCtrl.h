/*
  Author: Tobias Grundtvig
*/

#ifndef BlueSwitchCtrl_h
#define BlueSwitchCtrl_h

#include <Arduino.h>
#include <AccelStepper.h>
#include <SwitchCtrl.h>
#include <SwitchListener.h>

class BlueSwitchCtrl : public SwitchCtrl
{
public:
    BlueSwitchCtrl( uint8_t motorPin1,
                    uint8_t motorPin2,
                    uint8_t motorPin3,
                    uint8_t motorPin4 );
    void setListener(SwitchListener* pListener) {_pListener = pListener;}
    void update(unsigned long curTime);
    void switchTo(uint8_t side);
    uint8_t getState() {return _state;}
private:
    void calibrate();
    SwitchListener* _pListener;
    AccelStepper _stepper;
    uint8_t _state;
    unsigned long _lastStateSend;
};

#endif