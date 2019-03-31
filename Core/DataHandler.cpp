/*
 * DataHandler.cpp
 *
 *  Created on: 21.02.2019
 *      Author: lyson
 */

#include "DataHandler.h"

DataHandler* DataHandler::m_instance = 0;
DataHandler::DataHandler() {
	m_cmdType = RST;
	busy = false;
	m_display.draw();
}

DataHandler::~DataHandler() {

}

DataHandler* DataHandler::getInstace() {
	if (m_instance == 0) {
		m_instance = new DataHandler();
	}
	return m_instance;

}

void DataHandler::resetEsp() {
	m_cmdType = RST;
	m_esp.reset();
}

void DataHandler::testEsp() {
	busy = true;
	m_cmdType = OK;
	m_esp.ok();
	delay();
}

void DataHandler::getIp() {
	busy = true;
	m_cmdType = IP;
	m_esp.getIP();
	delay();
}

void DataHandler::getIpInfo() {
	busy = true;
	m_cmdType = IPINFO;
	m_esp.setIPInfo();
	delay();
}

void DataHandler::createUDPServer() {
	busy = true;
	m_cmdType = SETUDPSERVER;
	m_esp.setUDPServer(m_ip);
	delay();
}
void DataHandler::handleReciveCmd(const char* data) {

	if (m_cmdType == RST) {
		handleRstCmd(data);
	}
	if (m_cmdType == OK) {
		isOk(data);
	}
	if (m_cmdType == IP) {
		handleIpCmd(data);
	}
	if (m_cmdType == IPINFO) {
		isOk(data);
	}
	if (m_cmdType == SETUDPSERVER) {
		isOk(data);

	}

}

void DataHandler::handleReciveData(const char* data) {
	vector<string> tempData;
	split(data, ":", tempData);
	if (tempData.size() > 1) {
		setServerIp(tempData.at(0));
		sendData("Dupa!");
	}

}

void DataHandler::setServerIp(string& data) {
	vector<string> tempData;
	split(data, ",", tempData);
	if (tempData.size() > 3) {
		m_serverIP = tempData.at(2);
		m_serverPort = tempData.at(3);
		m_display.setServerIP(m_serverIP);
		m_display.draw();
	}
}

void DataHandler::sendData(string data) {
	if (m_serverIP.length() > 1 && m_serverPort.length() > 1) {
		m_esp.sendUDPData(data, m_serverIP, m_serverPort);

	}
}

void DataHandler::handleIpCmd(const char* data) {
	if (isContainWord(data, "OK")) {
		setIPAddress(data);
		busy = false;
	}
}

void DataHandler::isOk(const char* data) {
	if (isContainWord(data, "OK")) {
		busy = false;
		if (m_cmdType == SETUDPSERVER) {
			m_cmdType = READY;
		}
		m_esp.clear();
	}
}

void DataHandler::handleRstCmd(const char* data) {
	if (isContainWord(data, "GOT IP")) {
		busy = false;
		m_esp.clear();
	}
}

bool DataHandler::isContainWord(const char* buffer, const char* sentence) {
	uint8_t pos_search = 0;
	uint8_t pos_text = 0;
	uint8_t len_search = strlen(sentence);
	for (pos_text = 0; pos_text < MAX_SIZE - len_search; ++pos_text) {
		if (buffer[pos_text] == sentence[pos_search]) {
			++pos_search;
			if (pos_search == len_search) {
				return true;
			}
		} else {
			pos_text -= pos_search;
			pos_search = 0;
		}
	}
	return false;
}

int DataHandler::getWordPos(const char* buffer, const char* sentence) {
	uint8_t pos_search = 0;
	uint8_t pos_text = 0;
	uint8_t len_search = strlen(sentence);
	for (pos_text = 0; pos_text < MAX_SIZE - len_search; ++pos_text) {
		if (buffer[pos_text] == sentence[pos_search]) {
			++pos_search;
			if (pos_search == len_search) {
				return true;
			}
		} else {
			pos_text -= pos_search;
			pos_search = 0;
		}
	}
	return false;
}

void DataHandler::setIPAddress(const char* data) {
	asm("NOP");
	char* pfound = strstr(data, "STAIP");
	if (pfound != NULL) {
		getValueFromRecivedData(pfound, m_ip);
		m_display.setIP(m_ip);
		m_display.draw();
	}
}

void DataHandler::getValueFromRecivedData(const char* recivedData,
		string& valueToSet) {
	bool push = false;
	for (uint8_t i = 0; i < strlen(recivedData); ++i) {
		if (push) {
			if (recivedData[i] == '"') {
				return;
			}
			valueToSet.push_back(recivedData[i]);

		}
		if (recivedData[i] == '"' && i != 0) {
			push = true;
		}
	}
}

void DataHandler::delay() {
	HAL_Delay(500);
}



