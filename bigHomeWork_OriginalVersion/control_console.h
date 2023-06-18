#pragma once
#ifndef _CONTROL_CONSOLE_H

#define _CONTROL_CONSOLE_H // !_CONTROL_CONSOLE_H

#include<Windows.h>
#include<iostream>	

using std::string;
using std::cout;

void gotoXY(SHORT posX, SHORT posY);
void showCursor(bool cursorVisibility);
void setTextColor(const string& color);

void setWindowSize(SHORT width, SHORT height);
void setScreenBufferSize(SHORT width, SHORT height);

//void setColor(int background_color, int text_color);

/*
0 = Black

8 = Gray

1 = Blue

9 = Light Blue

2 = Green

10 = Light Green

3 = Aqua

11 = Light Aqua

4 = Red

12 = Light Red

5 = Purple

13 = Light Purple

6 = Yellow

14 = Light Yellow

7 = White

15 = Bright White
*/
//int random(int minN, int maxN);
#endif
