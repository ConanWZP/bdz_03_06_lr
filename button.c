#include "button.h"

uint16_t stateTest = 0;
/*
void buttonInitExti(void) {

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef buttonForExti;

	buttonForExti.Pin = GPIO_PIN_0;
	//buttonForExti.Mode = GPIO_MODE_IT_RISING;
	buttonForExti.Mode = GPIO_MODE_IT_RISING_FALLING; /// ???
	buttonForExti.Pull = GPIO_NOPULL;
	buttonForExti.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &buttonForExti);

	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/
void EXTI0_IRQHandler(void) {
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) {
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); // Ñáğàñûâàåì ôëàã ïğåğûâàíèÿ
		stateTest = stateTest + 1; // Èçìåíÿåì ñîñòîÿíèå ïåğåìåííîé state
		if (stateTest > 5){
			stateTest = 1;
		}
	}
}
*/