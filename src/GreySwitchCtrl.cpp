/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>
#include "GreySwitchCtrl.h"

#define SWITCH_SERVO_LEFT 30
#define SWITCH_SERVO_RIGHT 130
#define SWITCHING_TIME 2000

GreySwitchCtrl::GreySwitchCtrl(uint8_t pwmPin)
{
    _servo.attach(pwmPin);
    _servo.write(SWITCH_SERVO_LEFT);
    _state = STATE_SWITCHING_LEFT;
    _startTime = millis();
}

void GreySwitchCtrl::update(unsigned long curTime)
{
    _curTime = curTime;
    switch(_state)
    {
        case STATE_SWITCHING_LEFT:
            if(curTime - _startTime >= SWITCHING_TIME)
            {
                _state = STATE_LEFT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return;
        case STATE_SWITCHING_RIGHT:
            if(curTime - _startTime >= SWITCHING_TIME)
            {
                _state = STATE_RIGHT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return;
    }
}

bool GreySwitchCtrl::switchTo(uint8_t side)
{
    switch(side)
    {
        case LEFT:
            if(_state != STATE_LEFT && _state != STATE_SWITCHING_LEFT)
            {
                _servo.write(SWITCH_SERVO_LEFT);
                _state = STATE_SWITCHING_LEFT;
                _startTime = _curTime;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return true;
        case RIGHT:
            if(_state != STATE_RIGHT && _state != STATE_SWITCHING_RIGHT)
            {
                _servo.write(SWITCH_SERVO_RIGHT);
                _state = STATE_SWITCHING_RIGHT;
                _startTime = _curTime;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return true; 
    }
    Serial.println("ERROR: Unknow side");
    return false;
}
