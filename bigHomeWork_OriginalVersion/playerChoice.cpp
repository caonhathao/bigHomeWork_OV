#include<iostream>
#include"control_console.h"
#include"valGlobal.h"

#pragma region namespaceVersion
using std::cout;
using std::cin;
using std::string;
#pragma endregion

void drawBoard() {
	for (int i = 1; i < 100; i++)
	{
		gotoXY(i + 38, 3);
		if (i % 2 == 0) setTextColor(RED_COLOR);
		else setTextColor(YELLOW_COLOR);
		cout << '_';
		Sleep(5);
	};
	for (int i = 1; i < 16; i++)
	{
		gotoXY(38, i + 3);
		if (i % 2 == 0) setTextColor(RED_COLOR);
		else setTextColor(YELLOW_COLOR);
		cout << 'T';

		if (i % 2 == 0) setTextColor(RED_COLOR);
		else setTextColor(YELLOW_COLOR);
		gotoXY(138, i + 3);
		cout << 'T';

		Sleep(5);
	}
	for (int i = 1; i < 100; i++)
	{
		gotoXY(i + 38, 18);
		if (i % 2 == 0) setTextColor(RED_COLOR);
		else setTextColor(YELLOW_COLOR);
		cout << '_';

		Sleep(5);
	}
}
int playerChoice() {
	gotoXY(80, 1);
	setTextColor(RESET_COLOR);
	
	cout << "_GREEDY_ROBOT_S";

	drawBoard();

	gotoXY(42, 5);
	cout << "Ban muon choi theo kieu nao?";
	gotoXY(44, 7);
	cout << "1. Mot (nhieu) nguoi choi.";
	gotoXY(44, 9);
	cout << "2. Bat mo phong.";
	gotoXY(44, 11);
	cout << "3. Xem map.";
	gotoXY(44, 13);
	cout << "4. Cai dat map moi.";
	gotoXY(44, 15);
	cout << "5. Huong dan choi.";

	gotoXY(44, 17);
	cout << ">> ";

	int choice = 0;
	cin >> choice;
	
	return choice;
}