#include<iostream>
#include<iomanip>
#include"control_console.h"
#include"valGobal.cpp"

using std::cout;
using std::setw;

void drawMatrix(posElement** arr, int row, int col, int maxLen, int posX, int posY) {
	int k = 0;

	for (int i = 0; i < 2 * row + 1; i++)
	{
		gotoXY(posX, posY + i);

		if (i % 2 == 0)
		{
			for (int j = 0; j < ((maxLen * 2) * col) + 1; j++)
			{
				if (j % (3 + maxLen) == 0)
				{
					cout << '+';
				}
				else {
					cout << '-';
				}
			}
			cout << '\n';
		}
		else
		{
			for (int z = 0; z < col; z++)
			{
				cout << "| " << setw(maxLen) << arr[k][z].value << " ";
			}
			cout << '|' << '\n';
			k++;
		}
	}
};