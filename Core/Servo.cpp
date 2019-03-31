/*
 * Servo.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: macko
 */

#include "Servo.h"

Servo::Servo() {
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	isSet = false;
}

Servo::~Servo() {
	// TODO Auto-generated destructor stub
}

void Servo::move(int angle) {
//	if (!isSet) {
//		isSet = true;
		double value = 0.5;
		uint8_t duty = 35 + (angle * value);
		htim4.Instance->CCR1 = duty;
		HAL_Delay(300);
//
//	}
}

