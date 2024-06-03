#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f4xx_hal_tim.h"


extern TIM_HandleTypeDef delayNewInit;

void newDelay(void);

void Delay_us(uint16_t us);

void TIM2_IRQHandler(void);