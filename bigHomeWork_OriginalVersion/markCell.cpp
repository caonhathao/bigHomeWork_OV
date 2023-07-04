/* danh dau cac o da di vao bang cac mau sac khac nhau
tuy vao so luong nguoi choi se cho mau khac nhau
*/

#include<iostream>
#include<string>
#include<fcntl.h>
#include<io.h>
#include"control_console.h"
#include"valGlobal.h"

using std::wcout;
using std::to_string;

void markCell(int posX, int posY, string colorCode, int num, Activities ac) {
	gotoXY(posX, posY);
	setTextColor(colorCode);
	cout << num;

	SetConsoleOutputCP(CP_UTF8);

	if (ac == Activities::left)
	{
		gotoXY(posX - 1, posY);
		cout << '<';
	}
	else if (ac == Activities::right)
	{
		gotoXY(posX + to_string(num).size()+1, posY);
		cout << '>';
	}
	else if (ac == Activities::up)
	{
		gotoXY(posX + to_string(num).size() / 2, posY - 1);
		printf(u8"\u2227");
	}
	else if (ac == Activities::down) {
		gotoXY(posX + to_string(num).size() / 2, posY + 1);
		printf(u8"\u2228");
	};
};