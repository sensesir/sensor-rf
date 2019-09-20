/*
*	Class to handle all interactions with RF 
*   hardware and the HCS301 Keeloq chip
*
*	Author: Josh Perry <josh.perry245@gmail.com> 
*	Copyright 2019
*/

#include "RFInterface.hpp"

RFInterface::RFInterface(const int led_indicator_pin, const int rf_out_pin) :pwm_indicator_led(led_indicator_pin), pwm_rf_out(rf_out_pin) {
    LOG_RELEASE("RF INTERFACE: Created new RF interface\n");

    // IO setting
    pinMode(this->pwm_indicator_led, OUTPUT);
    digitalWrite(this->pwm_indicator_led, LOW);
    pinMode(this->pwm_rf_out, OUTPUT);  // Probably not necessary - done in RCSwitch
    digitalWrite(this->pwm_rf_out, LOW);

    // Create RF interface (external lib)
    this->InitRFSwitch();

    // Flash LED
    this->LedFlashOnInit(2);           
}

void RFInterface::InitRFSwitch() {
    this->rf_interface.enableTransmit(this->pwm_rf_out);
    this->rf_interface.setRepeatTransmit(RF_SIGNAL_REPEAT_COUNT);
    // this->rf_interface.setPulseLength();
    // this->rf_interface.setProtocol(1);
}

void RFInterface::LedFlashOnInit(const int& flashes) const {
    for (int i = 0; i < (flashes*2); ++i) {
        int led_state = digitalRead(this->pwm_indicator_led);
        digitalWrite(this->pwm_indicator_led, !led_state);
        delay(100);
    }
}

void RFInterface::sendGenericPulse() {
    LOG_DEBUG("RF INTERFACE: Sending generic pulse\n");
    digitalWrite(this->pwm_indicator_led, HIGH);

    const std::string packet = "10101010101010101010";  // 20 bits
    // const std::string packet = "1010";  // 4 bits
    this->rf_interface.send(packet.c_str());
    delay(1000);
    // this->rf_interface.send(packet.c_str());
    digitalWrite(this->pwm_indicator_led, LOW);
}
