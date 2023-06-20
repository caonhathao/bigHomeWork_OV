#pragma once
#ifndef _VALGLOBAL_H_
#include<iostream>

using std::string;

#pragma region colorCode
const string RESET_COLOR = "\033[0m";

const string RED_COLOR = "\033[31;1m";
const string GREEN_COLOR = "\033[32;1m";
const string BLUE_COLOR = "\033[34;1m";
const string YELLOW_COLOR = "\033[33;1m";
const string MAGENTA_COLOR = "\033[35;1m";
const string CYAN_COLOR = "\033[36;1m";

const string BRIGHT_RED = "\033[31;2m";
const string BRIGHT_GREEN = "\033[32;2m";
const string BRIGHT_YELLOW = "\033[33;2m";
const string BRIGHT_BLUE = "\033[34;2m";
const string BRIGHT_MAGENTA = "\033[35;2m";
const string BRIGHT_CYAN = "\033[36;2m";
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

	int sumTotal = 0;
};
#endif // !_VALGLOBAL_H_

