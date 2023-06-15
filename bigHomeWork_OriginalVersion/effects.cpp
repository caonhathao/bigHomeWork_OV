#include<iostream>
#include"effects.h"
#include"control_console.h"

using std::cout;

void printAndFill(int posX, int posY, string colorCode, string str) {
	gotoXY(posX, posY);
	setTextColor(colorCode);
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
	};
	cout << '\n';
}
