#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f4xx_hal_tim.h"

/*
extern TIM_HandleTypeDef timerInit;

void initDelay(void);

void Delay_us(uint32_t microseconds);
*/

void TIM2_IRQHandler(void);

extern uint32_t ticks;

extern TIM_HandleTypeDef htim2;
void delay_us(uint32_t microseconds);