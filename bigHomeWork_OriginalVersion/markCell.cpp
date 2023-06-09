/* danh dau cac o da di vao bang cac mau sac khac nhau
tuy vao so luong nguoi choi se cho mau khac nhau
*/

#include<iostream>
#include"control_console.h"
using std::cout;
void markCell(int posX, int posY, int colorCode, int num) {
	gotoXY(posX, posY);
	setColor(0, colorCode);
	cout << num;
}