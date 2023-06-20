#include<iostream>
#include<vector>
#include"valGlobal.h"
#include"control_console.h"

using std::cout;
using std::cin;
using std::vector;

struct serialPlayer {
	int serial = 0;
	int amountCell = 0;
	int sumTotal = 0;
};
void drawSortRank(posRobot* arr, int &size, int &numRow) {
	serialPlayer* sP = new serialPlayer[size];

	for (int i = 0; i < size; i++)
	{
		sP[i].serial = i;
		sP[i].amountCell = arr[i].amountCell;
		sP[i].sumTotal = arr[i].sumTotal;
	};
		
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (sP[i].amountCell < sP[j].amountCell)
			{
				serialPlayer temp = sP[i];
				sP[i] = sP[j];
				sP[j] = temp;
			}
			else if (sP[i].amountCell == sP[j].amountCell)
			{
				if (sP[i].sumTotal <= sP[j].sumTotal)
				{
					serialPlayer temp = sP[i];
					sP[i] = sP[j];
					sP[j] = temp;
				}
			}
		};
		
		gotoXY(20, 5 + numRow * 2 + 2 + size + i);
		cout << "Robot[" << sP[i].serial << "]: Cells: " << sP[i].amountCell << " Sum: " << sP[i].sumTotal << " Rank " << i + 1 << "\n";
	};

	gotoXY(20, 5 + numRow * 2 + 2 + size * 2 - 1);
	cout << "Robot[" << sP[size - 1].serial << "]: Cells: " << sP[size - 1].amountCell<<" Sum: "<<sP[size-1].sumTotal << " Rank " << size << "\n";
};