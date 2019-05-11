/*
 * Sonar.h
 *
 *  Created on: Apr 10, 2019
 *      Author: macko
 */

#ifndef SONAR_H_
#define SONAR_H_

#include "../Inc/gpio.h"
#include "../Inc/tim.h"

class Sonar {
public:
	Sonar();
	void mesureDistance();
	virtual ~Sonar();
	uint32_t getDistance() const {
		return distance;
	}
private:
	void msDelay(uint32_t val);
	void waitFinishMesure();
	uint32_t getTime();
	uint32_t distance;
};

#endif /* SONAR_H_ */
