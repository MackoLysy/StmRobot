/*
 * Sonar.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: macko
 */

#include "Sonar.h"

Sonar::Sonar() {
	HAL_TIM_Base_Start(&htim1);
	distance = 0.0;
}

Sonar::~Sonar() {
	// TODO Auto-generated destructor stub
}

void Sonar::mesureDistance() {
	htim1.Instance->CNT = 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	msDelay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	uint32_t time = getTime();
	distance = ((time * 34) / 1000);
	asm("NOP");
}
void Sonar::msDelay(uint32_t val) {
	htim1.Instance->CNT = 0;
	while (1) {
		if (htim1.Instance->CNT >= val) {
			break;
		}
	}
}

uint32_t Sonar::getTime() {
	uint32_t time = 0;
	htim1.Instance->CNT = 0;
	while (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
		if(htim1.Instance->CNT > 5000)
		{
			return 0;
		}
	}
		;
	htim1.Instance->CNT = 0;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) {
		time++;
		msDelay(1);
	}
	return time;
}


