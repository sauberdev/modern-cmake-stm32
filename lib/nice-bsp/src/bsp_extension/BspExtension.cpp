//
// Created by sauber on 12.04.20.
//

#include "nice-bsp/common/nice_bsp.h"

/**
 * @brief Override weak implementation provided by BSP.
 * @note This method uses functionality provided by FreeRTOS. So all HAL modules using delays needs to be initialized
 * after FreeRTOS.
 */
extern "C" void HAL_Delay(__IO uint32_t Delay) { vTaskDelay(Delay); }