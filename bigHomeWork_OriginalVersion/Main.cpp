/*Greedy Robot
*Find the way which will be next step for robot (player) go.
* Looking for cells around the robot
* If no one went on them, save them and compare them
* when we find a max cell, control robot go to that cell
* continue untill we cannot find any cells may be a next step or no way to go.
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<random>
#include<iomanip>

#include"valGlobal.h"
#include"control_console.h"

#pragma region	namespaceVersion	
using std::cout;
using std::cin;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;
using std::getline;
using std::setw;
using std::setfill;
using std::ios;
#pragma endregion

posRobot robot;
posRobot R;
posElement infoStep[4] = { 0 };
Activities active;
int sizeMatrix[2] = {}; //[0]=row and [1]=cloumn
int* maxLen = new int(0);
int amount = 0;
int step = 0;

#pragma region funcsDeclaration
int playerChoice();//giao dien lua chon

void existAndPush(posRobot robot, markVisuallize** arrFlag, posElement** arr, int& step, vector<Activities>& AC,int index);
void drawMatrix(posElement** arr, int row, int col, int maxLen, int posX, int posY);
void markCell(int posX, int posY, string colorCode, int num, Activities ac);
void drawSortRank(posRobot* arr, int &size, int &numRow);

void saveVisualizeToFile(string pathFile, markVisuallize** arr, int row, int col, int maxLen, int index);
	//posElement** makeNewMap(int& row, int& col,int &maxlen);

bool isElementExist(int i, int j);
bool isStop(_In_ posRobot robot[], int& size);

posElement nextStep(posElement a[4], int size, vector<Activities>ac);

size_t generateRandNum();
void filterNumber(int& posY, int& posX, string str);

string direction(Activities ac);
#pragma endregion

#pragma region funcsFindWayForPlayers
void existAndPush(posRobot robot, markVisuallize** arrFlag, posElement** arr, int& step, vector<Activities>& AC, int index) {//false if run case  3
	step = 0;
	if (isElementExist(robot.curPosY - 1, robot.curPosX)) //up
	{
		if (arrFlag[robot.curPosY - 1][robot.curPosX].marked == 0)
		{
			infoStep[step] = arr[robot.curPosY - 1][robot.curPosX];
			step++;
			active = Activities::up;
			AC.push_back(active);
		};
	}
	if (isElementExist(robot.curPosY + 1, robot.curPosX)) //down
	{
		if (arrFlag[robot.curPosY + 1][robot.curPosX].marked == 0)
		{
			infoStep[step] = arr[robot.curPosY + 1][robot.curPosX];
			step++;
			active = Activities::down;
			AC.push_back(active);
		};
	};

	if (isElementExist(robot.curPosY, robot.curPosX - 1)) //left
	{
		if (arrFlag[robot.curPosY][robot.curPosX - 1].marked == 0)
		{
			infoStep[step] = arr[robot.curPosY][robot.curPosX - 1];
			step++;
			active = Activities::left;
			AC.push_back(active);
		}
	}
	if (isElementExist(robot.curPosY, robot.curPosX + 1)) //right
	{
		if (arrFlag[robot.curPosY][robot.curPosX + 1].marked == 0)
		{
			infoStep[step] = arr[robot.curPosY][robot.curPosX + 1];
			step++;
			active = Activities::right;
			AC.push_back(active);
		}
	}
};
posElement nextStep(posElement a[4], int size,vector<Activities>ac) {
	posElement max = { 0,0,0 };
	for (int i = 0; i < size; i++)
	{
		if (max.value <= a[i].value)
		{
			max = a[i];
			active = ac[i];
		}
	};

	return max;
};
#pragma endregion

#pragma region funsFindWayForOne
void explorePath(posElement** arr, markVisuallize** arrFlag,int x, int y,int step, vector<int> &vc, vector<Activities>&ac,int index) {
	R.curPosX = x;
	R.curPosY = y;
	step = 0;
	ac.clear();
	existAndPush(R, arrFlag, arr, step, ac, index);
	posElement temp = nextStep(infoStep, step,ac);
	if (temp.value == 0)
	{
		int drawX = (*maxLen + 3) * (x + 1) + 20 - (1 + to_string(arr[y][x].value).size());
		int drawY = 2 * y + amount + 5;
		string colorCode = "\033[3" + to_string(index) + ";1m";
		arrFlag[y][x].marked = index;
		active = Activities::stop;
		arrFlag[y][x].character = "E";
		markCell(drawX, drawY, colorCode, arr[y][x].value, active);
		return;
	}
	else {
		int drawX = (*maxLen + 3) * (x + 1) + 20 - (1 + to_string(arr[y][x].value).size());
		int drawY = 2 * y + amount + 5;
		string colorCode = "\033[3" + to_string(index) + ";1m";
		markCell(drawX, drawY, colorCode, arr[y][x].value, active);

		R.amountCell++;
		arrFlag[y][x].marked = index;
		vc.push_back(temp.value);
		R.sumTotal = R.sumTotal + temp.value;
		arrFlag[y][x].character = direction(active);
		Sleep(200);
		explorePath(arr, arrFlag, temp.posX, temp.posY, step, vc, ac,index);
	}
}
#pragma endregion

#pragma region funsCheckEvent
bool isElementExist(int posY, int posX) {
		if (posY <= -1 || posY >= sizeMatrix[0])
		{
			return false;
		}
		else if (posX <= -1 || posX >= sizeMatrix[1])
		{
			return false;
		}
		return true;
	}; 
bool isStop(_In_ posRobot robot[], int& size) {
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
#pragma endregion

#pragma region funsTool
size_t generateRandNum() {
	// Create a seed to send value to engine
	std::random_device rand;
	// Take the seed value as an argument
	std::mt19937 generate(rand()); // Mersenne Twister engine

	const int MAX = 1000;

	std::uniform_int_distribution<> dist(1, MAX);
	return dist(generate);
}
void filterNumber(int& posY, int& posX, string str) {
	str = str + ' ';
	string num = "";
	int index = 0;
	posX = -1;
	posY = -1;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ')
		{
			num = num + str[i];
		}
		else if (num.size() != 0 && str[i] == ' ')
		{
			index = i;
			posY = stoi(num);
			break;
		};
	};

	num = "";
	for (int i = index; i < str.size(); i++)
	{
		if (str[i] != ' ')
		{
			num = num + str[i];
		}
		else if (num.size() != 0 && str[i] == ' ')
		{
			posX = stoi(num);
			break;
		};
	}
}
string direction(Activities ac) {
	if (ac == Activities::left)
	{
		return u8"\u2190";
	}
	else if (ac == Activities::right)
	{
		return u8"\u2192";
	}
	else if (ac == Activities::up)
	{
		return u8"\u2191";
	}
	else return u8"\u2193";
}
#pragma endregion

int main() {
	showCursor(true);
	SetConsoleOutputCP(CP_UTF8);

	bool virtualMode = false;
	bool createMap = false;
	bool defaultMap = true;

	ofstream fileOutput;

	while (true) {
		setTextColor(RESET_COLOR);
		SetConsoleOutputCP(CP_UTF8);

		posElement** arr = NULL;
		int drawX = 0;
		int drawY = 0;
		if (defaultMap == true)
		{
			ifstream fileInput("input.txt");

			int i = 0, j = 0;

			for (int i = 0; i < 2; i++)
			{
				int num = 0;
				if (fileInput >> num)
				{
					sizeMatrix[i] = num;
				}
			}

			arr = new posElement * [sizeMatrix[0]];

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
			fileInput.close();

			if (fileOutput.fail())
			{
				cout << "Can not open this file";
			}
			defaultMap = false;
		}

		createNewMap:
		if (createMap == true)
		{
			system("cls");
			setTextColor(GREEN_COLOR);
			cout << "\tNhap kich thuoc moi cua map (hang, cot): ";
			cin >> sizeMatrix[0] >> sizeMatrix[1];

			int temp = 0;
			*maxLen = 0;

			cout << '\n';
			cout << "\tDang tao moi..." << '\n';
			arr = new posElement * [sizeMatrix[0]];
			for (int i = 0; i < sizeMatrix[0]; i++)
			{
				arr[i] = new posElement[sizeMatrix[1]];
				for (int j = 0; j < sizeMatrix[1]; j++)
				{
					arr[i][j].value = generateRandNum();
					arr[i][j].posX = j;
					arr[i][j].posY = i;
					temp = to_string(arr[i][j].value).size();
					if (temp >= *maxLen)
					{
						*maxLen = temp;
					};
				}
			};
			createMap = false;

			cout << "\tDa tao xong" << '\n';
			cout << '\n';

			setTextColor(RED_COLOR);
			cout << "\tNhan phim 'b' de quay lai!";
			char* c = new char(' ');
			while (true) {
				if (_kbhit())
				{
					*c = _getch();
					*c = tolower(*c);
					if (*c == 'b')
					{
						delete c;
						break;
					}
				};
			};
		};

		while (true) {
			markVisuallize** arrFlag = new markVisuallize* [sizeMatrix[0]];
			for (int i = 0; i < sizeMatrix[0]; i++)
			{
				arrFlag[i] = new markVisuallize[sizeMatrix[1]];
				for (int j = 0; j < sizeMatrix[1]; j++)
				{
					arrFlag[i][j].marked = 0;
				}
			};

			system("cls");
			switch (playerChoice())
			{
			case 1: {
				system("cls");
				setTextColor(YELLOW_COLOR);
				cout << "\tXac nhan so nguoi choi: ";
				cin >> amount;

				posRobot* robotP = new posRobot[amount];
				vector<int>* store = new vector<int>[amount];

				setTextColor(GREEN_COLOR);
				cout << "\tNhap vi tri cua robot theo mau sau: [numRow][ ][numCol]" << '\n';
				cout << "\tnumRow >= numCol >= 1" << '\n';

				setTextColor(RESET_COLOR);
				int* val = new int(0);
				for (int i = 0; i < amount; i++)
				{
					gotoXY(0, i + 3);

					string colorCode = "";
					if (i < 6) colorCode = "\033[3" + to_string(i + 1) + ";1m";
					else colorCode = "\033[3" + to_string(i - 5) + ";2m";

					setTextColor(colorCode);
					string temp = "Nhap toa do cua robot [" + to_string(i + 1) + "](" + to_string(sizeMatrix[0]) + "x" + to_string(sizeMatrix[1]) + ") : ";
					cout << '\t' << temp;

					string str = " ";
					//enter position
					while (!isElementExist(robotP[i].curPosY - 1,robotP[i].curPosX - 1))
					{
						gotoXY(7 + temp.size() + 1, i + 3);
						cout << setfill(' ');
						cout << setw(str.size()) << ' ';

						gotoXY(7 + temp.size() + 1, i + 3);

						getline(cin, str);

						filterNumber(robotP[i].curPosY, robotP[i].curPosX, str);
					}

					robotP[i].curPosX = robotP[i].curPosX - 1;
					robotP[i].curPosY = robotP[i].curPosY - 1;
					
					*val = arr[robotP[i].curPosY][robotP[i].curPosX].value;
					arrFlag[robotP[i].curPosY][robotP[i].curPosX].marked = i + 1;
					arrFlag[robotP[i].curPosY][robotP[i].curPosX].beginPos = true;

					robotP[i].sumTotal = robotP[i].sumTotal + *val;

					store[i].push_back(*val);
					gotoXY(7 + temp.size() + str.size(), i + 3);
					cout << "Cell's Value: " << *val;
				};
				delete val;

				setTextColor(RESET_COLOR);
				drawMatrix(arr, sizeMatrix[0], sizeMatrix[1], *maxLen, 20, 3 + amount + 1);

				//for one player
				if (amount == 1) //for case 2
				{
					fileOutput.open("output.txt");

					vector<Activities>ac = {};
					R.amountCell = 1;
					R.sumTotal = 0;
					explorePath(arr, arrFlag, robotP[0].curPosX, robotP[0].curPosY, step, store[0], ac, 1);
					robotP[0].sumTotal = store[0][0] + R.sumTotal;
					robotP[0].amountCell = R.amountCell;

					cout << "\n";

					fileOutput << "Robot [" << 1 << "]: " << R.amountCell << '\n';
					for (int j = 0; j < store[0].size(); j++)
					{
						fileOutput << store[0][j] << ' ';
					};
					fileOutput << '\n';
					fileOutput << '\n';

					fileOutput.close();

					saveVisualizeToFile("output.txt", arrFlag, sizeMatrix[0], sizeMatrix[1], *maxLen, 1);

					cout << '\n';
					cout << '\n';

					setTextColor(RESET_COLOR);

					drawSortRank(robotP, amount, sizeMatrix[0]);

					setTextColor(MAGENTA_COLOR);
					//gotoXY(0, 2 * sizeMatrix[0] + 1 + 6 + amount);
					cout << "\tNhan phim 'b' de quay lai ";
					char c = ' ';
					while (true) {
						if (_kbhit())
						{
							c = _getch();
							c = tolower(c);
							if (c == 'b')
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
						};
					};
				}
				else {
					active = Activities::stop;

					setTextColor(RESET_COLOR);
					vector<Activities>ac = {};
					while (true)
					{
						bool signal = isStop(robotP, amount);
						for (int i = 0; i < amount; i++)
						{
							ac.clear();
							string colorCode = "";
							setTextColor(RESET_COLOR);
							if (i < 6) colorCode = "\033[3" + to_string(i + 1) + ";1m";
							else colorCode = "\033[3" + to_string(i - 5) + ";2m";

							gotoXY(4, 3 + i);
							setTextColor(colorCode);
							cout << ">>";

							if (robotP[i].stop != true)
							{
								existAndPush(robotP[i], arrFlag, arr, step, ac, 0);

								posElement temp = nextStep(infoStep, step, ac);
								if (temp.value != 0)
								{
									if (virtualMode == true)
									{
										int val = arr[robotP[i].curPosY][robotP[i].curPosX].value;
										drawX = (*maxLen + 3) * ((robotP[i].curPosX) + 1) + 20 - (1 + to_string(val).size());
										drawY = 2 * robotP[i].curPosY + 5 + amount;

										markCell(drawX, drawY, colorCode, store[i][store[i].size() - 1], active);
									};
									arrFlag[robotP[i].curPosY][robotP[i].curPosX].character = direction(active);

									robotP[i].curPosX = temp.posX;
									robotP[i].curPosY = temp.posY;

									robotP[i].amountCell++;
									robotP[i].sumTotal = robotP[i].sumTotal + temp.value;

									store[i].push_back(arr[temp.posY][temp.posX].value);
									arrFlag[robotP[i].curPosY][robotP[i].curPosX].marked = i + 1;
								}
								else
								{
									if (virtualMode == true)
									{
										active = Activities::stop;
										int val = arr[robotP[i].curPosY][robotP[i].curPosX].value;

										drawX = (*maxLen + 3) * ((robotP[i].curPosX) + 1) + 20 - (1 + to_string(val).size());
										drawY = 2 * robotP[i].curPosY + 5 + amount;

										markCell(drawX, drawY, colorCode, store[i][store[i].size() - 1], active);
									};
									robotP[i].stop = true;
									arrFlag[robotP[i].curPosY][robotP[i].curPosX].character = "E";
								};
								if (virtualMode == true)
								{
									Sleep(250);
								};
							}
							gotoXY(4, 3 + i);
							cout << "  ";
						}
						gotoXY(5, 3 + amount - 1);
						cout << ' ';
						if (signal == true)
						{
							break;
						}
					};

					fileOutput.open("output.txt", ios::out);
					fileOutput.close();

					for (int i = 0; i < amount; i++)
					{
						fileOutput.open("output.txt", ios::app);
						fileOutput << "Robot [" << i + 1 << "]: " << robotP[i].amountCell << '\n';
						for (int j = 0; j < store[i].size(); j++)
						{
							fileOutput << store[i][j] << ' ';
						};
						fileOutput << '\n';
						fileOutput << '\n';

						fileOutput.close();
						saveVisualizeToFile("output.txt", arrFlag, sizeMatrix[0], sizeMatrix[1], *maxLen, i + 1);
					};
					
					fileOutput.close();

					cout << '\n';
					cout << '\n';

					setTextColor(RESET_COLOR);

					drawSortRank(robotP, amount, sizeMatrix[0]);

					setTextColor(MAGENTA_COLOR);
					//gotoXY(0, 2 * sizeMatrix[0] + 1 + 6 + amount);
					cout << "\tBan co muon choi lai khong (y/n): ";
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
				};
				break;
			};
			case 2: {
				system("cls");
				setTextColor(RESET_COLOR);

				setTextColor(YELLOW_COLOR);
				cout << "\t[==========][==========]" << '\n';

				setTextColor(GREEN_COLOR);
				if (virtualMode) cout << "\tChe do mo phong: BAT" << '\n';
				else cout << "\tChe do mo phong: TAT" << '\n';

				char c = ' ';
				if (!virtualMode)
				{
					if (virtualMode == false) setTextColor(RED_COLOR);
					cout << "\tBat mo phong ?(y/n): ";
				}
				else {
					if (virtualMode == true) setTextColor(GREEN_COLOR);
					cout << "\tTat mo phong ?(y/n): ";
				}
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
				setTextColor(RESET_COLOR);

				setTextColor(YELLOW_COLOR);
				drawMatrix(arr, sizeMatrix[0], sizeMatrix[1], *maxLen, 20, 3);

				cout << '\n';
				setTextColor(RED_COLOR);
				cout << "\tNhan phim 'b' de quay lai!";
				char* c = new char(' ');
				while (true) {
					if (_kbhit())
					{
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
				};
				break;
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
				defaultMap = false;
				goto createNewMap;
			}
			case 5: {
				system("cls");
				setTextColor(RESET_COLOR);
				
				setTextColor(GREEN_COLOR);
				cout << "\tThiet lap vi tri robot cua ban (x,y) Sau do, chuong trinh se dieu khien con robot cua ban de tim duong di." << '\n';

				cout << '\n';
				cout << "\tDuong di se duoc tim bang cach xem xet vung xung quanh robot va chon ra o co gia tri lon nhat. ";
				cout << "\tCuoc tim kiem se dung lai neu khong the tim ra diem den tiep theo" << '\n';
				cout << '\n';

				cout << "\tSo nguoi choi toi da la 10 nguoi.\n";
				cout << '\n';

				setTextColor(RED_COLOR);
				cout << "\tCHU THICH:" << '\n';
				cout << "\t1. VUNG XUNG QUANH: CAC O TREN, DUOI, TRAI, PHAI" << '\n';
				cout << "\t2. MOT MAU SE DUOC GAN CHO MOI ROBOT (NEU CHE DO VIRTUALMODE DUOC BAT)." << '\n';

				setTextColor(YELLOW_COLOR);
				cout << "\tHE THONG XEP HANG:" << "\n";
				cout << "\t1. SAP XEP THEO TONG SO O DI DUOC [TU LON NHAT DEN BE NHAT]." << "\n";
				cout << "\t2. NEU CO NHIEU HON 2 ROBOT CUNG SO O DI DUOC, TONG SO DIEM KIEM DUOC SE DUOC DEM DI SO SANH." << "\n";

				setTextColor(RED_COLOR);
				cout << '\n';
				cout << "\tNhan phim 'b' de quay lai!";
				char* c = new char(' ');
				while (true) {
					if (_kbhit())
					{
						*c = _getch();
						*c = tolower(*c);
						if (*c == 'b')
						{
							delete c;
							break;
						}
					};
				};
				break;
			}
			default:
				break;
			};
		};
	}
	exit:
	delete maxLen;
	return 0;
};;