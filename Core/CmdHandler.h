/*
 * CmdHandler.h
 *
 *  Created on: Apr 18, 2019
 *      Author: macko
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

#include <string>
#include <string.h>
#include "utils.h"
#include "Servo.h"
#include "Sonar.h"

using namespace std;

class CmdHandler {
public:
	CmdHandler();
	virtual ~CmdHandler();
	string handleCmd(string& data);
private:
	string handleDistance(string& data);
	void handleMove(string& data);
	Servo m_servo;
	Sonar m_sonar;
};

#endif /* CMDHANDLER_H_ */
