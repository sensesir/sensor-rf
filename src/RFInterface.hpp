/*
*	Class to handle all interactions with RF 
*   hardware and the HCS301 Keeloq chip
*
*	Author: Josh Perry <josh.perry245@gmail.com> 
*	Copyright 2019
*/

#pragma once

#include <Arduino.h>
#include <RCSwitch.h>
#include <string>
#include "./config/Configuration.h"

class RFInterface {
private:
    const int pwm_indicator_led;
    const int pwm_rf_out;
    RCSwitch rf_interface = RCSwitch();

    void InitRFSwitch();
    void LedFlashOnInit(const int&) const;
public:
    RFInterface(const int led_indicator_pin, const int rf_out_pin);
    void sendGenericPulse();
};
