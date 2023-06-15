#pragma once
#ifndef _VALGLOBAL_H_
#include<iostream>

using std::string;

#pragma region colorCode
const string RESET_COLOR = "\033[0m";
const string RED_COLOR = "\033[31m";
const string GREEN_COLOR = "\033[32m";
const string BLUE_COLOR = "\033[34m";
const string YELLOW_COLOR = "\033[33m";
#pragma endregion

struct posElement {
	int value = 0;
	int posX = 0;
	int posY = 0;
};
struct posRobot {
	bool stop = false;
	int curPosX = 0;
	int curPosY = 0;
	int amountCell = 1;
};
#endif // !_VALGLOBAL_H_

