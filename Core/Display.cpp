/*
 * Display.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: macko
 */

#include "Display.h"

Display::Display() {
	ssd1306_Init();
}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::draw() {
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString((char*) m_batt_lvl.c_str(), Font_7x10, White);
	ssd1306_SetCursor(2, 16);
	ssd1306_WriteString("My IP", Font_7x10, White);
	ssd1306_SetCursor(2, 27);
	ssd1306_WriteString((char*) m_ip.c_str(), Font_7x10, White);
	ssd1306_SetCursor(2, 42);
	ssd1306_WriteString((char*) m_server_ip.c_str(), Font_7x10, White);
	ssd1306_UpdateScreen();
}

