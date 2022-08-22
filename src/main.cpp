//
// Created by sauber on 24.03.20.
//
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

#include <stm32f4xx_hal.h>

#include "ClockManager.h"
#include <nice-bsp/error/SystemErrorHandler.h>
#include <nice-bsp/gpio/GPIO.h>
#include <nice-bsp/led/LedManager.h>

using namespace nice_bsp;

void vDummyTask(void* pvParameters);

int main()
{
    // Init HAL
    HAL_Init();

    // Init peripherals
    ClockManager::init();
    gpio::GPIO::init();

    // Initialize FreeRTOS
    xTaskCreate(vDummyTask, "Example", configMINIMAL_STACK_SIZE + 80, NULL, tskIDLE_PRIORITY + 4, NULL);

    vTaskStartScheduler();

    return 0;
}

void vDummyTask(void* pvParameters)
{
    int state = 0;
    while (1) {

        state = state == 0 ? 1 : 0;

        if (state)
        {
            LedOn(LED_RED);
            LedOn(LED_GREEN);
            LedOff(LED_BLUE);
            LedOff(LED_ORANGE);
        }
        else
        {
            LedOff(LED_RED);
            LedOff(LED_GREEN);
            LedOn(LED_BLUE);
            LedOn(LED_ORANGE);
        }

        vTaskDelay(1000);
    }
}