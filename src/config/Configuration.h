/*
*	High-level wrapper to include correct environment config
*
*	Author: Josh Perry <josh.perry245@gmail.com>
*	Created: 09/20/2019
*   Copyright 2019
*/

#pragma once 

// Hardware pinout allocation
#define PWM_LED_INDICATOR 5
#define PWM_RF_OUT 4
#define SWITCH_LED_INDICATOR 14
#define SWITCH_INPUT 12

#define BAUD_RATE 115200

// Logging framework
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_RELEASE 1

#define LOG_LEVEL LOG_LEVEL_DEBUG 

#if LOG_LEVEL == LOG_LEVEL_DEBUG 
    #define LOG_DEBUG(x) Serial.print(x);
#endif

#include <hardwareSerial.h>
#define LOG_RELEASE(x) Serial.print(x);

// RF Config
#define RF_SIGNAL_REPEAT_COUNT 5