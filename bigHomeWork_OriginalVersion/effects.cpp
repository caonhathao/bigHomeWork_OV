#include<iostream>
#include"effects.h"
#include"control_console.h"

using std::cout;

void printAndFill(int posX, int posY, int colorCode, string str) {
	gotoXY(posX, posY);
	setColor(0, colorCode);
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
	};
	cout << '\n';
}
