/*
 * Display.h
 *
 *  Created on: Mar 31, 2019
 *      Author: macko
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>

#include "../Libs/ssd1306.h"
#include "../Libs/ssd1306_fonts.h"
using namespace std;
class Display {
public:
	Display();
	virtual ~Display();

	void draw();
	void setIP(string& ip) {
		m_ip = ip;
	}
	void setServerIP(string& ip) {
		m_server_ip = ip;
	}
	void setBatteryLvl(string& lvl) {
		m_batt_lvl = "Battery: " + lvl;
	}
private:
	string m_ip = "0.0.0.0";
	string m_server_ip = "0.0.0.0";
	string m_batt_lvl = "Battery: 0%";
};

#endif /* DISPLAY_H_ */
