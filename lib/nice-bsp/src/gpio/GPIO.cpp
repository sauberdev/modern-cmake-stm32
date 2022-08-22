//
// Created by sauber on 03.04.20.
//

#include "GPIO.h"
#include "gpio.h"

namespace nice_bsp {
namespace gpio {

void GPIO::init() {
    MX_GPIO_Init();
}

} // namespace gpio
} // namespace nice_bsp