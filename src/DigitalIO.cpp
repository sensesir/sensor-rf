/*
*	Interface for digital IO for the ESP8266 NodeMCU board
*
*	Author: Josh Perry <josh.perry245@gmail.com>
*	Created: 09/20/2019
*   Copyright 2019
*/

#include "DigitalIO.hpp"

DigitalIO& DigitalIO::GetInstance() {
    static DigitalIO instance;
    if (!(instance.initialized)) instance.initPins();
    return instance;
}

DigitalIO::DigitalIO() {}

void DigitalIO::initPins() {
    pinMode(this->switch_input, INPUT);
    pinMode(this->switch_led, OUTPUT);
    digitalWrite(this->switch_led, LOW);
    
    LOG_DEBUG("DIGITAL IO: Initialized pins\n");
    this->initialized = true;
}

void DigitalIO::updateSwitchLED() {
    const int previous_state = digitalRead(this->switch_led);
    const int switch_state = digitalRead(this->switch_input);
    
    // Switch is pulled up to HIGH, if pressed, goes LOW
    // LED should mimick switch state (active/passive)
    if (previous_state == switch_state) digitalWrite(this->switch_led, !switch_state);          
    
    // If LED was off, and switch is now low, then this is a new press
    if (previous_state == LOW && switch_state == LOW) {
        LOG_DEBUG("DIGITAL IO: Button press detected\n");
        this->button_callback();
    }
}

void DigitalIO::set_button_callback(ButtonCallback callback){
    this->button_callback = callback;
}