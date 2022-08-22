#pragma once

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

#ifdef STM32F401xC
#include <stm32f4xx_hal.h>
#elif defined(STM32F100xB)
#include <stm32f1xx_hal.h>
#else
#error "This device family not supported yet"
#endif