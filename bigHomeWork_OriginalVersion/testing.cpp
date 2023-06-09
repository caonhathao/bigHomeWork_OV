//#include<iostream>
//#include<string>
//#include<Windows.h>
//#include"control_console.h"
//#include<iomanip>
//using namespace std;
//int main() {
//	int arr[2][5] = { {1,3,45,132,40},{12,32,345,655,1} };
//	int maxLen = 0;
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (to_string(arr[i][j]).size() > maxLen)
//			{
//				maxLen = to_string(arr[i][j]).size();
//			}
//		}
//	};
//
//	int j = 0;
//	for (int i = 0; i < 3*2 - 1; i++)
//	{
//		if (i%2==0)
//		{
//			for (int j = 0; j < (6*5)+1; j++)
//			{
//				if (j % 6 == 0)
//				{
//					cout << '+';
//				}
//				else cout << '-';
//			}
//			cout << endl;
//		}
//		else
//		{
//			for (int k = 0; k < 5; k++)
//			{
//				cout << "| " << setw(maxLen) << arr[j][k] << " ";
//			}
//			cout << '|' << endl;
//			j++;
//		}
//	}
//	
//}