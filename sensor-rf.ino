/*
 * R&D project to get an ESP MCU to interface with an HCS301 
 * to work with a rolling code RF receiver.
 * 
 * Collaborator(s): Josh Perry <josh.perry245@gmail.com>
 * Created: 09/20/2019
 */

// Global includes
#include <memory>

// Local includes
#include "./src/config/Configuration.h"
#include "./src/RFInterface.hpp"
#include "./src/DigitalIO.hpp"

// Scoped between setup and loop
std::unique_ptr<RFInterface> rf_interface;

void setup() {
  Serial.begin(BAUD_RATE);
  LOG_RELEASE("MAIN: Booting RF code...\n");

  rf_interface = std::unique_ptr<RFInterface>(new RFInterface(PWM_LED_INDICATOR, PWM_RF_OUT));
  void (*callback_ptr)() = []() { rf_interface->sendGenericPulse(); };  // Should check if ptr is non-null
  DigitalIO::GetInstance().set_button_callback(callback_ptr);
}

void loop() {
  DigitalIO::GetInstance().updateSwitchLED();
}
