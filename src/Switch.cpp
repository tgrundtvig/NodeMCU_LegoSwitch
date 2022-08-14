/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>
#include "Switch.h"

Switch::Switch( SwitchCtrl* pSwitchCtrl,
                uint8_t ledPin,
                bool ledOn,
                const char* deviceType,
                uint16_t deviceVersion) :
                DeviceUDPClient(ESP.getChipId(), deviceType, deviceVersion),
                _led(ledPin, ledOn)
{
    _pSwitchCtrl = pSwitchCtrl;
}

void Switch::update(unsigned long curTime)
{
    _curTime = curTime;
    DeviceUDPClient::update(curTime);
    _pSwitchCtrl->update(curTime);
    _led.update(curTime);
    if(curTime - _ledStarted > 5000)
    {
        _led.stop();
    }
}

uint16_t Switch::onPacketReceived(uint16_t command, uint16_t arg1, uint16_t arg2, uint8_t* pData, uint16_t size)
{
    Serial.println("Packet received!");
    switch(command)
    {
        case CMD_IDENTIFY:
            Serial.println("Identify received!");
            _led.setBlinksPattern(3, 100, 200, 400);
            _led.start();
            _ledStarted = _curTime;
            return 0;
        case CMD_SWITCH_LEFT:
            _pSwitchCtrl->switchTo(LEFT);
            return 0;
        case CMD_SWITCH_RIGHT:
            _pSwitchCtrl->switchTo(RIGHT);
            return 0;
        case CMD_GET_STATE:
            sendPacketToServer(CMD_ON_STATE_CHANGE, _pSwitchCtrl->getState(), 0, true, true);
            return 0;
        default:
            Serial.print("Unknown command: ");
            Serial.println(command);
            return 404;
    }
}

void Switch::onStateChange(uint8_t newState)
{
    sendPacketToServer(CMD_ON_STATE_CHANGE, newState, 0, true, true);
}