/* danh dau cac o da di vao bang cac mau sac khac nhau
tuy vao so luong nguoi choi se cho mau khac nhau
*/

#include<iostream>
#include"control_console.h"

void markCell(int posX, int posY, string colorCode, int num) {
	gotoXY(posX, posY);
	setTextColor(colorCode);
	cout << num;
}