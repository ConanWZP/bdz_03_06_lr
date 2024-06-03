#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
//#include "keyboard.h"
#include "termoresistor.h"
#include "adcTermo.h"
#include "leds.h"
#include "initTim4.h"
#include "initShim.h"
#include "pwmSetPulse.h"

#include "newDelay.h"
//#include "timerForDisplay.h"
#include "initPinsDisplay.h"
#include "WH1602B.h"

//#include "button.h"

#include "initKeys.h"

#include <stdio.h>
#include <math.h>





void SystemClock_Config(void);
void SysTick_Handler(void);

void changeUnit(uint16_t unit, double* currentArray, double* displayValue);
void changeAccuracy(uint16_t accuracy, double* currentArray, double* initialArray, uint16_t unit, double* displayValue);

int main (void) {
	
	HAL_Init();
	SystemClock_Config();
	
	//allLedsHalInit();
	//initKeyboard();
	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	
	//buttonInitExti();
	

	//initKeys();
	
	//initAdc();
	
	
	
	// init gpio_pin_14 (diod) like alterate func
	//initShim();
	
	// init timer 4
	//initTim4();
	
	
	// dlya display
	PINS_DISPLAY_Init();
	//display_init();
	
	
	//dlya display
	//initDelay();
	newDelay();
	
	LCD_Init8();
	LCD_CharCmd('f');
	
	while(1)
 {}
		
}
	/*
	// initialTemperature - ispolzuetsya dlya vichislenya tekyshei temperatyri posle smeni tochnosti ili smeni edinitsi izmereniya
	// {celcia, farengeit, kelvin}
	double initialTemperatureArray[3] = {25.6, 78.1, 298.6};
	
	
	// currentTemperature ispolzyetsya dlya vivoda na ekran i imenno v ety peremennyiy zapisivaytsya perevodov tochnosti i smnei ediniz izmereniya
	// {celcia, farengeit, kelvin}
	double currentTemperatureArray[3] = {25.6, 78.1, 298.6};
	
	
	double displayValue = 25.6;
	
	
	uint16_t wasStart = 0;
	
	uint16_t wasMesured = 0;
	
	// 0 - bez zapyatoy, 1 - s zapyatoy
	uint16_t currentAccuracy = 1;
	uint16_t accuracyArray[2] = {0, 1};
	
	// 0 - celci; 1 - farengeit; 2 - kelvin;
	uint16_t currentUnit = 0;
	uint16_t unitOfMeasurement[3] = {0, 1, 2};
	
	uint16_t varFlag = 0;
	uint16_t cnt = 0;

	
	//HAL_ADC_Start(&adcStruct);
	
	
	while(1){
		
		if (stateStart == 1) {
			wasStart = 1;
			wasMesured = 0;
			stateStart = 0;
		}
		
		
		if (wasStart) {
			
			LinearSearch();

			displayValue = result;
			// result - v celciax s zapyatoy
			initialTemperatureArray[0] = result;
			currentTemperatureArray[0] = result;
			
			initialTemperatureArray[1] = (result * 9 / 5) + 32 + 3;
			currentTemperatureArray[1] = (result * 9 / 5) + 32 + 3;
			
			initialTemperatureArray[2] = result + 273;
			currentTemperatureArray[2] = result + 273;
			
			wasStart = 0;
			wasMesured = 1;
			
		}
		
		
		if (stateAccuracy == 1) {
			currentAccuracy = (currentAccuracy + 1) % 2; // 2 - razmer massiva
		
			changeAccuracy(accuracyArray[currentAccuracy], currentTemperatureArray, initialTemperatureArray, currentUnit, &displayValue);
			stateAccuracy = 0;
		}
		
		
		if (stateUnit == 1) {
			currentUnit = (currentUnit + 1) % 3; // // 3 - razmer massiva
			
			changeUnit(unitOfMeasurement[currentUnit], currentTemperatureArray, &displayValue);
			stateUnit = 0;
		}
		
		if (wasMesured) {
			//char firstString[20] = "Temperature:";
			char* firstString = "Temperature:"; 
			
			char secondString[20];
			
			// 0 - celci; 1 - farengeit; 2 - kelvin;
			switch (currentUnit) {
				case 0:
				sprintf(secondString, "%.1lf degrees_c", displayValue);
				break;
				case 1:
				sprintf(secondString, "%.1lf degrees_f", displayValue);
				break;
				case 2:
				sprintf(secondString, "%.1lf kelvin", displayValue);
				break;
			}
			
			//LCD_SelectedString(firstString, 1);
			
			//LCD_SelectedString(secondString, 2);
		}
		
		
		if (wasMesured) {
			if (varFlag) {
				pwmSetPulse(cnt, timerFour);
			} else {
					pwmSetPulse(1000-cnt, timerFour);
			}
			
			cnt++;
			
			if (cnt == 1000) {
				varFlag = varFlag ? 0 : 1;
				cnt = 0;
			}
			HAL_Delay(1);
		}
		
	}
	*/
//}

void changeUnit(uint16_t unit, double* currentArray, double* displayValue) {
	*displayValue = currentArray[unit];
	
}

// dolgno rabotat'
void changeAccuracy(uint16_t accuracy, double* currentArray, double* initialArray, uint16_t unit, double* displayValue) {
	if (accuracy) {
		
		currentArray[0] = initialArray[0];
		currentArray[1] = initialArray[1];
		currentArray[2] = initialArray[2];
		
	} else {
		
		currentArray[0] = rint(currentArray[0]);
		currentArray[1] = rint(currentArray[1]);
		currentArray[2] = rint(currentArray[2]);
	}

	*displayValue = currentArray[unit];
}

void SystemClock_Config(void)
{
		RCC_OscInitTypeDef RCC_OscInitStruct = {0};
		RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

		/** Configure the main internal regulator output voltage 
		*/
		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

		/** Initializes the CPU, AHB and APB busses clocks 
		*/
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		RCC_OscInitStruct.PLL.PLLM = 8;
		RCC_OscInitStruct.PLL.PLLN = 50;
		RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
		RCC_OscInitStruct.PLL.PLLQ = 7;
		HAL_RCC_OscConfig(&RCC_OscInitStruct);

		/** Initializes the CPU, AHB and APB busses clocks 
		*/
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
		HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);		
}

void SysTick_Handler(void) {	
    HAL_IncTick();
}
