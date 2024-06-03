#include "newDelay.h"


TIM_HandleTypeDef delayNewInit;

void newDelay(void) {

    __HAL_RCC_TIM2_CLK_ENABLE();

    delayNewInit.Instance = TIM2;
		delayNewInit.Init.Prescaler = 13;
	
	
    //delayNewInit.Init.Prescaler = 1;
		//delayNewInit.Init.Prescaler = 13;
    delayNewInit.Init.CounterMode = TIM_COUNTERMODE_UP;
    //delayNewInit.Init.Period = 12;
		//delayNewInit.Init.Period = 0xffff-1;
	
		//delayNewInit.Init.Period = 0xffff-1;
		delayNewInit.Init.Period = 65535;

    HAL_TIM_Base_Init(&delayNewInit);

    //HAL_NVIC_EnableIRQ(TIM2_IRQn);

   HAL_TIM_Base_Start(&delayNewInit);
	
}

void Delay_us(uint16_t us) {
	if (us == 0)
		return;
	if (us > 0){
		us--;
		__HAL_TIM_SET_COUNTER(&delayNewInit, 0);
		
		while (__HAL_TIM_GET_COUNTER(&delayNewInit) < us);
		
	}
	
}
/*
void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&delayNewInit);
}
*/
