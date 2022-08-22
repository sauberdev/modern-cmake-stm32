//
// Created by sauber on 12.04.20.
//

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

#include <stm32f4xx_hal.h>

/**
 * @brief Override weak implementation provided by BSP.
 * @note This method uses functionality provided by FreeRTOS. So all HAL modules using delays needs to be initialized
 * after FreeRTOS.
 */
extern "C" void HAL_Delay(__IO uint32_t Delay) { vTaskDelay(Delay); }