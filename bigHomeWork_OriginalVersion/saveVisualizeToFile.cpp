#include<iostream>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<fcntl.h>
#include<io.h>
#include"valGlobal.h"

using std::cout;
using std::ofstream;
using std::setw;
using std::ios;

string createLine(string c, int maxLen, int compesation1,int compesation2) {
	string temp;

	temp = temp + " | ";
	int count = 0;
	if (c == u8"\u2190" || c == u8"\u2192")
		count = 3;
	else if (c == u8"\u2191" || c == u8"\u2193")
		count = 1;
	else if (c == ".")
		count = 0;
	else 
		count = 2;

	for (int i = 0; i < maxLen-count; i++)
		temp = temp + " ";

	if (count == 1)
		if (compesation1 > 1) {
			temp = temp + c; int f = 0;
			if (compesation2 > 2 && compesation2 <= 5)
			{
				f = 1;
			}
			else if (compesation2 > 5)
			{
				f = 0;
			}
			else f = 2;
			for (int i = 0; i < f; i++)
			{
				temp = temp + " ";
			}
		}
		else temp = temp + c + " ";
	else if (count == 2)
		temp = temp + c + "  ";
	else
		if (compesation1 > 1) {
			temp = temp + c;
			int f = 0;
			if (compesation2 > 3 && compesation2 <= 5)
			{
				f = 1;
			}
			else if (compesation2 > 5)
			{
				f = 0;
			}
			else f = 2;
			for (int i = 0; i < f; i++)
			{
				temp = temp + " ";
			}
		}
		else temp = temp + c + " ";
	return temp;
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
			int countUp = 0;
			for (int z = 0; z < col; z++)
			{
				if (arr[k][z].marked == index)
					fileOutput << createLine(arr[k][z].character, maxLen, z, z - countUp);
				else
					fileOutput << createLine(".", maxLen, z, z - countUp);
				countUp++;
			};
			fileOutput << " |" << '\n';
			k++;
		}
	};
	fileOutput.close();
}