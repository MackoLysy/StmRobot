/*
 * EspHandler.h
 *
 *  Created on: 05.03.2019
 *      Author: Macko
 */

#ifndef ESPHANDLER_H_
#define ESPHANDLER_H_

#include "../Inc/usart.h"
#include "utils.h"
#include <string>
#include <cstring>

using namespace std;
class EspHandler {
public:
	EspHandler();
	virtual ~EspHandler();
	void startReading();
	void reset();
	void getIP();
	void setIPInfo();
	void ok();
	void clear();
	void setUDPServer(string& ip);
	void sendUDPData(string& data, string& ip, string& port);
private:
	void sendCmd(string data);
	void sendData(string data);
};

#endif /* ESPHANDLER_H_ */
