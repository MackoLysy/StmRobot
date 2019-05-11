/*
 * DataHandler.h
 *
 *  Created on: 21.02.2019
 *      Author: lyson
 */

#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "EspHandler.h"
#include "Display.h"
#include "CmdHandler.h"
#include "utils.h"

using namespace std;
class DataHandler {
public:
	virtual ~DataHandler();
	static DataHandler* getInstace();
	void resetEsp();
	void getIp();
	void testEsp();
	void getIpInfo();
	void createUDPServer();
	void handleReciveCmd(const char* data);
	void handleReciveData(const char* data);
	void setServerIp(string& data);
	void espStart() {
		m_esp.startReading();
	}
	bool isReady() {
		return m_cmdType == READY;
	}
	void sendData(string data);
private:
	static DataHandler* m_instance;
	bool isContainWord(const char* buffer, const char* sentence);
	int getWordPos(const char* buffer, const char* sentence);
	DataHandler();

	enum CMD {
		RST = 0, OK, IP, IPINFO, SETUDPSERVER, READY
	};
	CMD m_cmdType;
	EspHandler m_esp;
	Display m_display;
	CmdHandler m_cmdHandler;
	bool busy;
	string m_ip;
	string m_serverIP = "";
	string m_serverPort = "";
	void isOk(const char* data);
	void handleIpCmd(const char* data);
	void handleRstCmd(const char* data);
	void setIPAddress(const char* data);
	void getValueFromRecivedData(const char* recivedData, string& valueToSet);
	void delay();
};

#endif /* DATAHANDLER_H_ */
