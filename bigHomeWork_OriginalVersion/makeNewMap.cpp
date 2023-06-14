//#include<iostream>
//#include<fstream>
//#include<string>
//
//#include"valGobal.cpp"
//using std::cout;
//using std::cin;
//using std::to_string;
//
//posElement** makeNewMap(int& row, int& col, int& maxLen) {
//	system("cls");
//	cout << "Nhap kich thuoc moi cua map (hang, cot): ";
//	cin >> col >> row;
//
//	int temp = 0;
//	maxLen = 0;
//
//	static posElement** arr = new posElement * [row];
//	for (int i = 0; i < row; i++)
//	{
//		arr[i] = new posElement[col];
//		for (int j = 0; j < col; j++)
//		{
//			arr[i][j].value = 0;
//			arr[i][j].posX = j;
//			arr[i][j].posY = i;
//			temp = to_string(arr[i][j].value).size();
//			if (temp >= maxLen)
//			{
//				maxLen = temp;
//			};
//		}
//	};
//	return arr;
//};