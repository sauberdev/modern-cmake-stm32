//
// Created by sauber on 03.04.20.
//

#include "SystemErrorHandler.h"

#include <array>
#include <cstdint>

namespace nice_bsp {
    namespace error {

        enum class ErrorType : std::uint8_t {
            SYSTEM = 0x01, APPLICATION = 0x02, RTOS_ERROR = 0x04
        };

/**
 * @brief Struct describing an error.
 */
        struct Error {
            ErrorType errorType;
            std::uint8_t errorCode;
        };

/**
 * @brief Describes codes of system interrupts.
 */
        enum class SystemInterruptError : std::uint8_t {
            NMI = 0x01,
            HARD_FAULT = 0x02,
            MEM_MANAGE = 0x03,
            BUS_FAULT = 0x04,
            USAGE_FAULT = 0x05,
            DEBUG_MON = 0x06
        };

        std::array<Error, MAX_ERROR_COUNT> mErrors;
        std::size_t mErrorCounter = 0x00;

        void reportError(ErrorType type, std::uint8_t errorCode);

        void reportApplicationError(ApplicationError error) {
            reportError(ErrorType::APPLICATION, static_cast<std::uint8_t>(error));
        }

        void reportRTOSError(RtosError error) { reportError(ErrorType::RTOS_ERROR, static_cast<std::uint8_t>(error)); }

        std::size_t getErrorCount() { return mErrorCounter; }

        void reportError(ErrorType type, std::uint8_t errorCode) {
            if (mErrorCounter < MAX_ERROR_COUNT) {
                mErrors[mErrorCounter++] = {type, errorCode};
            }
        }

/**
 * @brief This function handles Non maskable interrupt.
 */
        extern "C" void NMI_Handler(void) {
            reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::NMI));

            while (1) {
            }
        }

/**
 * @brief This function handles Hard fault interrupt.
 */
        extern "C" void HardFault_Handler(void) {
            reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::HARD_FAULT));

            while (1) {
            }
        }

/**
 * @brief This function handles Memory management fault.
 */
        extern "C" void MemManage_Handler(void) {
            reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::MEM_MANAGE));

            while (1) {
            }
        }

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
        extern "C" void BusFault_Handler(void) {
            reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::BUS_FAULT));

            while (1) {
            }
        }

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
        extern "C" void UsageFault_Handler(void) {
            reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::USAGE_FAULT));

            while (1) {
            }
        }

/**
 * @brief This function handles Debug monitor.
 */
extern "C" void DebugMon_Handler(void) {
    reportError(ErrorType::SYSTEM, static_cast<std::uint8_t>(SystemInterruptError::DEBUG_MON));

    while (1) {
    }
}

} // namespace error
} // namespace nice_bsp

void vApplicationTickHook(void) {
    // TODO: Move logic to user firmware
}

void vApplicationMallocFailedHook(void) {
    // TODO: Report an error
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // TODO: Report an error
}
