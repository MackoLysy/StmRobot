/*
 * EspHandler.cpp
 *
 *  Created on: 05.03.2019
 *      Author: Macko
 */

#include "EspHandler.h"
#include "DataHandler.h"
#include "utils.h"

uint8_t recivedData;
char buffer[MAX_SIZE];
uint8_t rXcounter = 0;

EspHandler::EspHandler() {
	// TODO Auto-generated constructor stub

}

EspHandler::~EspHandler() {
	// TODO Auto-generated destructor stub
}
void EspHandler::startReading() {
	HAL_UART_Receive_DMA(&huart2, &recivedData, 1);
}
void EspHandler::sendCmd(string data) {
	string tmpCmd = data.append("\r\n");
	char cmd[tmpCmd.size() + 1];
	strcpy(cmd, tmpCmd.c_str());
	HAL_UART_Transmit(&huart2, (uint8_t*) (cmd), strlen(cmd), 500);
}

void EspHandler::sendData(string data) {
	char cmd[data.size() + 1];
	strcpy(cmd, data.c_str());
	HAL_UART_Transmit(&huart2, (uint8_t*) (cmd), strlen(cmd), 1000);
}
void EspHandler::reset() {
	sendCmd("AT+RST");
}

void EspHandler::ok() {
	sendCmd("AT");
}

void EspHandler::getIP() {
	sendCmd("AT+CIFSR");
}
void EspHandler::setIPInfo() {
	sendCmd("AT+CIPDINFO=1");
}
void EspHandler::clear() {
	rXcounter = 0;
	memset(buffer, 0, MAX_SIZE);
}

void EspHandler::setUDPServer(string& ip) {
	string cmd = "AT+CIPSTART=\"UDP\",\"" + ip + "\"," + M_PORT + "," + M_PORT
			+ ",2";
	sendCmd(cmd);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	DataHandler* handler = DataHandler::getInstace();
	if (rXcounter > 200) {
		rXcounter = 0;
	}
	buffer[rXcounter] = (char) recivedData;
	rXcounter++;
	if (handler->isReady()) {
		if (recivedData == ';') {
			handler->handleReciveData(buffer);
		}
	} else {
		if (recivedData == '\n') {
			handler->handleReciveCmd(buffer);
		}
	}

	HAL_UART_Receive_DMA(&huart2, &recivedData, 1);

}

void EspHandler::sendUDPData(string& data, string& ip, string& port) {
	clear();
	string s_size = to_string(data.length());
	string query = "AT+CIPSEND=" + s_size + ",\"" + ip + "\"," + port;
	sendCmd(query);
	bigDelay(500);
	sendData(data);
}


