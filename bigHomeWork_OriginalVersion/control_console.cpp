#include"control_console.h"
void gotoXY(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
};
void showCursor(bool cursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = cursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void setTextColor(const string& color) {
	cout << color;
}
//void setColor(int background_color, int text_color) {
//	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//	int color_code = background_color * 16 + text_color;
//	SetConsoleTextAttribute(hStdout, color_code);
//};	
//int random(int minN, int maxN) {
//	return minN + rand() % (maxN + 1 - minN);
//
//}