/*
 * utils.h
 *
 *  Created on: 06.03.2019
 *      Author: Macko
 */

#ifndef UTILS_H_
#define UTILS_H_

#define MAX_SIZE 200
#define M_PORT "1234"
#include "../stm32f1xx_hal.h"
#include <string>
#include <vector>
#include<stdio.h>
#include<math.h>

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens);
void bigDelay(uint32_t milliseconds);
void ftoa(float n, char *res, int afterpoint);
int intToStr(int x, char str[], int d);
void reverse(char *str, int len);
#endif /* UTILS_H_ */
