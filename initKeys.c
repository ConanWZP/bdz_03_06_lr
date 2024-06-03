#include "initKeys.h"

uint16_t newTestState = 0;

uint16_t stateStart = 0;
uint16_t stateAccuracy = 0;
uint16_t stateUnit = 0;

void initKeys(void) {

	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9; // Пины PC6, PC7, PC8, PC9
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; // Установка режима на вход с прерыванием по спаду
	GPIO_InitStruct.Pull = GPIO_PULLUP; // Включение подтягивающего резистора
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0); // Установка приоритета прерывания
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // Разрешение прерывания EXTI9_5_IRQn

	
	
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef buttonPA;

	buttonPA.Pin = GPIO_PIN_0;
	//buttonPA.Mode = GPIO_MODE_IT_RISING;
	buttonPA.Mode = GPIO_MODE_IT_FALLING; /// ???
	buttonPA.Pull = GPIO_NOPULL;
	buttonPA.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &buttonPA);

	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
}

void EXTI9_5_IRQHandler(void) {
	 // не работает
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) { 
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6); 
				newTestState = newTestState + 1;
				if (newTestState > 5){
					newTestState = 1;
				}
			
			
    }
		
		
		// SB1
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
		
				/*
				newTestState = newTestState + 1;
				if (newTestState > 5){
					newTestState = 1;
				}
				*/
			
				stateAccuracy = stateAccuracy + 1; // Изменяем состояние переменной state
				if (stateAccuracy > 1){
					stateAccuracy = 0;
				}
				
			
			
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) { 
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8); 
			
			newTestState = newTestState + 1;
				if (newTestState > 5){
					newTestState = 1;
				}
       
    }
		
		
		// SB3
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) { 
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9); 
        /*
				newTestState = newTestState + 1;
				if (newTestState > 5){
					newTestState = 1;
				}
				*/
			
				stateUnit = stateUnit + 1; // Изменяем состояние переменной state
				if (stateUnit > 1){
					stateUnit = 0;
				}
			
    }
}




void EXTI0_IRQHandler(void) {
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) {
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); // Сбрасываем флаг прерывания
		/*
		newTestState = newTestState + 1; // Изменяем состояние переменной state
		if (newTestState > 5){
			newTestState = 1;
		}
		*/
		
		stateStart = stateStart + 1; // Изменяем состояние переменной state
		if (stateStart > 1){
			stateStart = 0;
		}
	}
}

