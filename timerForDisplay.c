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

// ������� �������������� ��������
void delay_us(uint32_t us) {
  // ������������� ������� TIM2
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 125 - 1; // ������� APB1 = 12.5 ���, �������� �� 125 ��� 1 ������������
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999; // ������ 10000 ������ (10000 �����������)
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
 

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 

  // ��������� ���������� �� ������������
  HAL_TIM_Base_Start_IT(&htim2); // ��������� ������ � ������ ����������

  // ���� ������������ ������� (us)
  ticks = us;
  while (ticks) {
    // �������� ������������ �������
    // � ����������� ���������� (TIM2_IRQHandler) 
    // ������� ticks ����������� �� 1
  }

  // ��������� �������
  HAL_TIM_Base_Stop_IT(&htim2);
}

// ���������� ���������� ������� TIM2
void TIM2_IRQHandler(void) {
  // �������� ����� ���������� �� ������������
  if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE)) {
    // ����� ����� ���������� 
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE); 

    // ��������� ������� ticks 
    ticks--; 
  }
}
