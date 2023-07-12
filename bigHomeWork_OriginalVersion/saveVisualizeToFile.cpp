#include<iostream>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include"valGlobal.h"

using std::cout;
using std::ofstream;
using std::setw;
using std::ios;

/*
* When write date from program to file .txt:
*	- With the number from 0 to 9 and the character from 'A' to 'Z': the length is 1.5 spaces
*		=> 2 spaces.
*	- With the character from 'a' to 'z': the length is 1 spaces.
*/

string createContentCell(string c, int maxLen) {
	string temp = " | ";
	int sizeCharacter = 0;
	if (c.size() == 1)
	{
		if (c[0] >= '2' && c[0] <= '9' || c[0] == '0')
		{
			for (int i = 0; i < (maxLen * 2) - 2; i++)
			{
				temp = temp + " ";
			};
			temp = temp + c + " ";
			return temp;
		}
		else if (c[0] == '1')
		{
			for (int i = 0; i < ((maxLen - 2) * 2); i++)
			{
				temp = temp + " ";
			};
			temp = temp + c + " ";
			return temp;
		}
		else if (c[0] == 'S' || c[0] == 'E')
		{
			for (int i = 0; i < (maxLen - 1) * 2; i++)
			{
				temp = temp + " ";
			}
			temp = temp + c + " ";
			return temp;
		}
		else
		{
			for (int i = 0; i < ((maxLen - 1) * 2); i++)
			{
				temp = temp + " ";
			};
			temp = temp + c;
			return temp;
		}
	}
	else
	{
		int sizeCharacter = 0;
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == '1')
			{
				sizeCharacter++;
			}
			else sizeCharacter += 2;
		};
		for (int i = 0; i < (maxLen * 2) - sizeCharacter - 1; i++)
		{
			temp = temp + " ";
		};
		temp = temp + c + " ";
		return temp;
	};
}
void saveVisualizeToFile(string pathFile, markVisuallize** arr,int row,int col, int maxLen,int index) {
	int k = 0;
	SetConsoleOutputCP(CP_UTF8);
	ofstream fileOutput(pathFile,ios::app);
	for (int i = 0; i < 2 * row + 1; i++)
	{
		fileOutput << '\t';
		if (i % 2 == 0)
		{
			for (int j = 0; j < ((maxLen + 3) * col) + 1; j++)
			{
				if (j % (3 + maxLen) == 0)
				{
					fileOutput << '+';
				}
				else
				{
					fileOutput << '-';
				}
			};
			fileOutput << '\n';
		}
		else
		{
			for (int z = 0; z < col; z++)
			{
				if (arr[k][z].marked == index)
				{
					fileOutput << createContentCell(arr[k][z].character, maxLen);
				}
				else
				{
					fileOutput << createContentCell(" ", maxLen);
				}
			};
			fileOutput << " |" << '\n';
			k++;
		}
	};
	fileOutput.close();
}