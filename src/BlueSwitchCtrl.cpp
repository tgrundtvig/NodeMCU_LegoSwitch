/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>
#include "BlueSwitchCtrl.h"

#define SWITCH_STEPPER_MOVE_RANGE 500
#define STATE_CALIBRATE_1 101
#define STATE_CALIBRATE_2 102
#define STATE_CALIBRATE_3 103
#define STATE_CALIBRATE_4 104


BlueSwitchCtrl::BlueSwitchCtrl( uint8_t motorPin1,
                                uint8_t motorPin2,
                                uint8_t motorPin3,
                                uint8_t motorPin4) :
                                _stepper(   8,
                                            motorPin1,
                                            motorPin3,
                                            motorPin2,
                                            motorPin4)
{
    _stepper.setMaxSpeed(800.0);
    _stepper.setAcceleration(800.0);
    _stepper.setSpeed(400);
    _state = STATE_CALIBRATE_1;
}

void BlueSwitchCtrl::calibrate()
{
    _stepper.run();
    switch(_state)
    {
        case STATE_CALIBRATE_1:
            _stepper.moveTo(-SWITCH_STEPPER_MOVE_RANGE);
            _state = STATE_CALIBRATE_2;
            return;
        case STATE_CALIBRATE_2:
            if(_stepper.distanceToGo() == 0)
            {
                _stepper.moveTo(SWITCH_STEPPER_MOVE_RANGE);
                _state = STATE_CALIBRATE_3;
            }
            return;
        case STATE_CALIBRATE_3:
            if(_stepper.distanceToGo() == 0)
            {
                _stepper.moveTo(-SWITCH_STEPPER_MOVE_RANGE);
                _state = STATE_CALIBRATE_4;
            }
            return;
        case STATE_CALIBRATE_4:
            if(_stepper.distanceToGo() == 0)
            {
                _state = STATE_LEFT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return;
    }
}

void BlueSwitchCtrl::update(unsigned long curTime)
{
    if(_state >= STATE_CALIBRATE_1)
    {
        calibrate();
        return;
    }
    
    _stepper.run();
    switch(_state)
    {
        case STATE_SWITCHING_LEFT:
            if(_stepper.distanceToGo() == 0)
            {
                _state = STATE_LEFT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
                _lastStateSend = curTime;
            }
            return;
        case STATE_SWITCHING_RIGHT:
            if(_stepper.distanceToGo() == 0)
            {
                _state = STATE_RIGHT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
                _lastStateSend = curTime;
            }
            return;
        case STATE_LEFT:
        case STATE_RIGHT:
            if(curTime - _lastStateSend > 5000)
            {
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
                _lastStateSend = curTime;
            }
            return;
    }
}

void BlueSwitchCtrl::switchTo(uint8_t side)
{
    switch(side)
    {
        case LEFT:
            if(_state != STATE_LEFT && _state != STATE_SWITCHING_LEFT)
            {
                _stepper.moveTo(-SWITCH_STEPPER_MOVE_RANGE);
                _state = STATE_SWITCHING_LEFT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return;
        case RIGHT:
            if(_state != STATE_RIGHT && _state != STATE_SWITCHING_RIGHT)
            {
                _stepper.moveTo(SWITCH_STEPPER_MOVE_RANGE);
                _state = STATE_SWITCHING_RIGHT;
                if(_pListener != 0)
                {
                    _pListener->onStateChange(_state);
                }
            }
            return; 
    }
}
