//
// Created by sauber on 03.04.20.
//

#pragma once

namespace nice_bsp {
namespace gpio {

class GPIO {
public:
    /**
     * @brief Deleted constructor of class GPIO as this class supposed to be static.
     */
    GPIO() = delete;

    /**
     * @brief Initializes all GPIOs which are configured as I/O ports without an alternate function.
     * @note Should be called once after startup.
     */
    static void init();
};
} // namespace gpio
} // namespace nice_bsp
