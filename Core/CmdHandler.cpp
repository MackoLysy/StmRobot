/*
 * CmdHandler.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: macko
 */

#include "CmdHandler.h"

CmdHandler::CmdHandler() {

}

CmdHandler::~CmdHandler() {
	// TODO Auto-generated destructor stub
}

string CmdHandler::handleCmd(string& data) {
	string result = "ok";
	if (data.find("servo") != string::npos) {
		result = handleDistance(data);
	}
	if (data.find("move") != string::npos) {
		handleMove(data);
	}
	return result;
}
string CmdHandler::handleDistance(string& data) {
	vector<string> tempData;
	string distance = "0";
	split(data, "=", tempData);
	if (tempData.size() > 1) {
		uint8_t angle = stoi(tempData.at(1));
		m_servo.move(angle);
		bigDelay(300);
		m_sonar.mesureDistance();
		bigDelay(50);
		int d_distance = m_sonar.getDistance();
		distance = to_string(d_distance);
	}
	return distance;
}
void CmdHandler::handleMove(string& data) {

}

