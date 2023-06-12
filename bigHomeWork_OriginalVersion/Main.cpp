/*thuat toan tim kiem o lon nhat cho buoc di ke tiep
* doc, ghi du lieu
* thuat toan voi 2 rot bot o hai vi tri khac nhau
* toa do robot: hoi nguoi dung
*/


#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<conio.h>
#include<Windows.h>

#include"valGobal.cpp"
#include"control_console.h"

using std::cout;
using std::cin;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;

struct posRobot {
	int curPosX = 0;
	int curPosY = 0;
	bool stop = false;
	int amountCell = 1;
};

posRobot robot;
posElement infoStep[4] = { 0 };
int sizeMatrix[2] = {}; //[0]=row and [1]=cloumn

#pragma region funcsEvent
int playerChoice();//giao dien lua chon

void existAndPush(posRobot robot, int** arrFlag, posElement** arr, int& step);
void drawMatrix(posElement** arr, int row, int col, int maxLen, int posX, int posY);
void markCell(int posX, int posY, int colorCode, int num);
posElement** makeNewMap(int& row, int& col,int &maxlen);

bool isElementExist(int i, int j);
bool isStop(posRobot robot[], int& size);

posElement nextStep(posElement a[4], int size);
#pragma endregion

#pragma region funcsDeclare
void existAndPush(posRobot robot, int** arrFlag, posElement** arr, int& step) {
	if (isElementExist(robot.curPosY - 1, robot.curPosX)) //up
	{
		if (arrFlag[robot.curPosY - 1][robot.curPosX] == 0)
		{
			infoStep[step] = arr[robot.curPosY - 1][robot.curPosX];
			step++;
		}
	}
	if (isElementExist(robot.curPosY + 1, robot.curPosX)) //down
	{
		if (arrFlag[robot.curPosY + 1][robot.curPosX] == 0)
		{
			infoStep[step] = arr[robot.curPosY + 1][robot.curPosX];
			step++;
		};
	};

	if (isElementExist(robot.curPosY, robot.curPosX - 1)) //left
	{
		if (arrFlag[robot.curPosY][robot.curPosX - 1] == 0)
		{
			infoStep[step] = arr[robot.curPosY][robot.curPosX - 1];
			step++;
		}
	}
	if (isElementExist(robot.curPosY, robot.curPosX + 1)) //right
	{
		if (arrFlag[robot.curPosY][robot.curPosX + 1] == 0)
		{
			infoStep[step] = arr[robot.curPosY][robot.curPosX + 1];
			step++;
		}
	}
};
bool isElementExist(int posY, int posX) {
	if (posY == -1 || posY == sizeMatrix[0])
	{
		return false;
	}
	else if (posX == -1 || posX == sizeMatrix[1])
	{
		return false;
	}
	return true;
};
bool isStop(posRobot robot[], int& size) {
	int countUp = 0;
	for (int i = 0; i < size; i++)
	{
		if (robot[i].stop == true) {
			countUp++;
		}
		else
		{
			break;
		}
	}
	if (countUp == size)
	{
		return true;
	};
	return false;
}
posElement nextStep(posElement a[4], int size) {
	posElement max = { 0,0,0 };
	for (int i = 0; i < size; i++)
	{
		if (max.value <= a[i].value)
		{
			max = a[i];
		}
	};

	return max;
}

void showMap(int* arr, int m, int n) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i * n + j] << ' ';
		}
		cout << '\n';
	}
};
int main() {
	ifstream fileInput("C:/Users/Lenovo/Desktop/input.txt");

	int i = 0, j = 0;

	for (int i = 0; i < 2; i++)
	{
		int num = 0;
		if (fileInput >> num)
		{
			sizeMatrix[i] = num;
		}
	}

	posElement** arr = new posElement * [sizeMatrix[0]];
	int* maxLen = new int(0);
	for (int i = 0; i < sizeMatrix[0]; i++)
	{
		arr[i] = new posElement[sizeMatrix[1]];
	};

	for (int i = 0; i < sizeMatrix[0]; i++)
	{
		for (int j = 0; j < sizeMatrix[1]; j++)
		{
			int num;
			if (fileInput >> num)
			{
				arr[i][j].value = num;
				arr[i][j].posX = j;
				arr[i][j].posY = i;

				int temp = to_string(arr[i][j].value).size();
				if (temp > *maxLen)
				{
					*maxLen = temp;
				};
			}
		}
	}

	ofstream fileOutput("C:/Users/Lenovo/Desktop/output.txt");
	if (fileOutput.fail())
	{
		cout << "Can not open this file";
	}

	bool virtualMode = false;
	bool createMap = false;

	int drawX = 0;
	int drawY = 0;

	while(true){
		system("cls");

		int** arrFlag = new int* [sizeMatrix[0]]; 
		for (int i = 0; i < sizeMatrix[0]; i++)
		{
			arrFlag[i] = new int[sizeMatrix[1]];
			for (int j = 0; j < sizeMatrix[1]; j++)
			{
				arrFlag[i][j] = 0;
			}
		};

		if (createMap==true)
		{
			/*create new map*/
			createMap = false;
		}
		switch (playerChoice())
		{
		case 1: {
			system("cls");
			cout << "Xac nhan so nguoi choi:";
			int amount;
			cin >> amount;

			posRobot* robotP = new posRobot[amount]{};
			vector<int>* store = new vector<int>[amount] {};

			int* val = new int(0);
			for (int i = 0; i < amount; i++)
			{
				gotoXY(0, i + 1);
				
				cout << "Nhap toa do cua robot [" << i << "] :";
				cin >> robotP[i].curPosX >> robotP[i].curPosY;

				*val = arr[robotP[i].curPosY][robotP[i].curPosX].value;
				arrFlag[robotP[i].curPosY][robotP[i].curPosX] = i + 1;

				store[i].push_back(*val);
			};
			delete val;

			drawMatrix(arr, sizeMatrix[0], sizeMatrix[1], *maxLen, 20, 3 + amount);

			if (virtualMode == true) {
				for (int i = 0; i < amount; i++)
				{
					/*
					(*maxLen * 2)*curCol: length of cell
					20: position of matrix
					1 + to_sttring(num).size(): set positino of text pointer
					*/
					drawX = (*maxLen + 3) * (robotP[i].curPosX + 1) + 20 - (1 + to_string(store[i][0]).size());
					drawY = 2 * robotP[i].curPosY + 1 + 3 + amount;
					markCell(drawX,drawY, i + 1, store[i][0]);
				}
			};

			while (true)
			{
				bool signal = isStop(robotP, amount);
				for (int i = 0; i < amount; i++)
				{
					if (robotP[i].stop != true)
					{
						int step = 0;
						existAndPush(robotP[i], arrFlag, arr, step);

						posElement temp = nextStep(infoStep, step);
						if (temp.value != 0)
						{
							robotP[i].curPosX = temp.posX;
							robotP[i].curPosY = temp.posY;

							robotP[i].amountCell++;

							store[i].push_back(arr[temp.posY][temp.posX].value);
							arrFlag[robotP[i].curPosY][robotP[i].curPosX] = i + 1;

							if (virtualMode == true)
							{
								drawX = (*maxLen + 3) * (robotP[i].curPosX + 1) + 20 - (1 + to_string(temp.value).size());
								drawY = 2 * robotP[i].curPosY + 1 + 3 + amount;
								markCell(drawX, drawY, i + 1, temp.value);
							};
						}
						else
						{
							robotP[i].stop = true;
						};
					}
				}
				if (signal == true)
				{
					break;
				}
				if (virtualMode == true)
				{
					Sleep(200);
				};
			};

			for (int i = 0; i < amount; i++)
			{
				fileOutput << robotP[i].amountCell << '\n';
				for (int j = 0; j < store[i].size(); j++)
				{
					fileOutput << store[i][j] << ' ';
				};
				fileOutput << '\n';
			};
			fileOutput.close();

			cout << '\n';
			gotoXY(0, 2 * sizeMatrix[0] + 1 + 3 + amount);
			cout << "Ban co muon choi lai khong (y/n): ";
			char c = ' ';
			cin >> c;
			c = tolower(c);
			if (c == 'y')
			{
				delete[]robotP;
				delete[]store;

				for (int i = 0; i < sizeMatrix[0]; i++)
				{
					delete[] arrFlag[i];
				}
				delete[] arrFlag;
				break;
			}
			else
			{
				goto exit;
			};
		}
		case 2: {
			system("cls");
			cout << "Che do mo phong:" << virtualMode << '\n';
			char c = ' ';
			if (!virtualMode)
			{
				cout << "Bat mo phong ?(y/n): ";
			}
			else cout << " Tat mo phong ?(y/n): ";
			cin >> c;
			c = tolower(c);
			if (c == 'y')
			{
				virtualMode = !virtualMode;
			};
			break;
		}
		case 3: {
			system("cls");
			drawMatrix(arr, sizeMatrix[0], sizeMatrix[1], *maxLen, 20, 3);
			cout << '\n';
			cout << "press 'b' to back!";
			char* c = new char(' ');
			while (_kbhit()) {
				*c = _getch();
				*c = tolower(*c);

				if (*c == 'b')
				{
					delete c;
					break;
				}
				else
				{
					delete c;
					goto exit;
				}
			};
		}
		case 4: {
			for (int i = 0; i < sizeMatrix[0]; i++)
			{
				delete[] arrFlag[i];
			};
			delete[] arrFlag;

			for (int i = 0; i < sizeMatrix[0]; i++)
			{
				delete[]  arr[i];
			};
			delete[] arr;
			
			createMap = true;
			break;
		}
		default:
			break;
		}
	};
	exit:
	return 0;
}