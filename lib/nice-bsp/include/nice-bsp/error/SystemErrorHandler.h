//
// Created by sauber on 03.04.20.
//

#pragma once

#include <cstdint>
#include <FreeRTOS.h>
#include <task.h>

extern "C" void vApplicationTickHook( void );
extern "C" void vApplicationMallocFailedHook( void );
extern "C" void vApplicationStackOverflowHook ( TaskHandle_t xTask, char *pcTaskName );

namespace nice_bsp {
namespace error {

/** @brief Describes how many errors can be stored in a memory. */
static constexpr auto MAX_ERROR_COUNT = 20;

enum class ApplicationError : std::uint8_t {
    CLOCK_INITIALIZATION_ERROR = 0x01,
    CAN_INITIALIZATION_FAILED = 0x02,
    CAN_TX_ERROR = 0x03,
    CAN_RX_ERROR = 0x04,
    CAN_WRONG_CLOCK = 0x05
};

enum class RtosError : std::uint8_t {
    MEMORY_LACK = 0x01,
};

/**
 * @brief Reports an application error.
 * @param error Error code to report.
 */
void reportApplicationError(ApplicationError error);

/**
 * @brief Reports an RTOS error.
 * @param error Error code to report.
 */
void reportRTOSError(RtosError error);

/**
 * @brief Returns a count of registered errors.
 * @return Count of registered errors
 */
std::size_t getErrorCount();

} // namespace error
} // namespace nice_bsp