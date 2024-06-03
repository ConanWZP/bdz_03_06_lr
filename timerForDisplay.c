#include "timerForDisplay.h"


//TIM_HandleTypeDef timerInit;



/*
void initDelay(void) {

    __HAL_RCC_TIM2_CLK_ENABLE();

    timerInit.Instance = TIM2;
    //timerInit.Init.Prescaler = 1;
		timerInit.Init.Prescaler = 13;
    timerInit.Init.CounterMode = TIM_COUNTERMODE_UP;
    //timerInit.Init.Period = 12;
		timerInit.Init.Period = 0xffff-1;

    HAL_TIM_Base_Init(&timerInit);

    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    HAL_TIM_Base_Start_IT(&timerInit);
	
	
		
	
}
*/
/*
void Delay_us(uint32_t microseconds) {
		/*
    uint32_t startTime = __HAL_TIM_GET_COUNTER(&timerInit);

    while ((__HAL_TIM_GET_COUNTER(&timerInit) - startTime) < microseconds) {
       // gdet ykazannoe chislo microsenods
    }
	  */
	
	/*
  __HAL_TIM_SET_COUNTER(&timerInit, 0);
  __HAL_TIM_CLEAR_FLAG(&timerInit, TIM_FLAG_UPDATE);
	
  while(__HAL_TIM_GET_COUNTER(&timerInit) < microseconds) {
    if (__HAL_TIM_GET_FLAG(&timerInit, TIM_FLAG_UPDATE) != RESET) {
      break;
    }
		
  }
	
	
	//__HAL_TIM_SET_COUNTER(&timerInit,0);  // set the counter value a 0
	//while (__HAL_TIM_GET_COUNTER(&timerInit) < microseconds);  // wait for the counter to reach the us input in the parameter
	
}
*/

/*

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&timerInit);
}

*/



TIM_HandleTypeDef htim2;

uint32_t ticks;

// Функция микросекундной задержки
void delay_us(uint32_t us) {
  // Инициализация таймера TIM2
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 125 - 1; // Частота APB1 = 12.5 МГц, делитель на 125 для 1 микросекунды
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999; // Период 10000 тактов (10000 микросекунд)
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
 

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 

  // Настройка прерывания по переполнению
  HAL_TIM_Base_Start_IT(&htim2); // Запускаем таймер в режиме прерывания

  // Ждем переполнения таймера (us)
  ticks = us;
  while (ticks) {
    // Ожидание переполнения таймера
    // В обработчике прерывания (TIM2_IRQHandler) 
    // счетчик ticks уменьшается на 1
  }

  // Остановка таймера
  HAL_TIM_Base_Stop_IT(&htim2);
}

// Обработчик прерывания таймера TIM2
void TIM2_IRQHandler(void) {
  // Проверка флага прерывания по переполнению
  if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE)) {
    // Сброс флага прерывания 
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE); 

    // Уменьшаем счетчик ticks 
    ticks--; 
  }
}
