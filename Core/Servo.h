/*
 * Servo.h
 *
 *  Created on: Mar 29, 2019
 *      Author: macko
 */

#ifndef SERVO_H_
#define SERVO_H_
#include "../Inc/tim.h"

class Servo {
public:
	Servo();
	virtual ~Servo();
	void move(int angle);
private:

};

#endif /* SERVO_H_ */
