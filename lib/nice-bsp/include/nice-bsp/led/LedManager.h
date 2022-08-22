//
// Created by sauber on 03.04.20.
//

#pragma once

// Inlcude main.h from generated sources as it contains user defines for LEDs
#include <main.h>

#define LedOnHelper(ledName, port, pin, state) HAL_GPIO_WritePin(ledName##port, ledName##pin, state);
#define LedOn(ledName) LedOnHelper(ledName, _GPIO_Port, _Pin, GPIO_PIN_SET)
#define LedOff(ledName) LedOnHelper(ledName, _GPIO_Port, _Pin, GPIO_PIN_RESET)
