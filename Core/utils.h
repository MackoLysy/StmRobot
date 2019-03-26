/*
 * utils.h
 *
 *  Created on: 06.03.2019
 *      Author: Macko
 */

#ifndef UTILS_H_
#define UTILS_H_

#define MAX_SIZE 200
#define PORT "1234"
#include <string>
#include <vector>

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens);
#endif /* UTILS_H_ */
