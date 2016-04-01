#include <iostream>
#include <vector>
using namespace std;

vector<int*>M;

void show(int rows, int col)
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			cout << M[i][j] << " \t";
		}
		cout << endl;
	}
}

void solve(int start, int startX, int startY, int endX, int endY)
{
	if (endX < startX || endY < startY)
		return;
	int rows = endX - startX + 1;
	int col = endY - startY + 1;
	int point[4];
	point[0] = rows - 1;
	point[1] = rows + col - 2;
	point[2] = point[1] + (col>1)*(rows - 1);
	point[3] = point[2] + (rows>1)*(col - 2);
//	cout << "Point:";
//	for (int i = 0; i < 4; i++)
//		cout << point[i] << ",";
//	cout << endl;
	for (int i = 0;; i++)
	{
		if (i <= point[0])
			M[startY][startX + i] = start + i;
		else if (i <= point[1])
			M[startY + i - point[0]][endX] = start + i;
		else if (i <= point[2])
			M[endY][endX - (i - point[1])] = start + i;
		else if (i <= point[3])
			M[endY - (i - point[2])][startX] = start + i;
		else
			break;
	}
	solve(start + point[3] + 1, startX + 1, startY + 1, endX - 1, endY - 1);
}

int main()
{
	int rows, col;
	cin >> col >> rows;
	for (int i = 0; i < col; i++)
	{
		M.push_back(new int[rows]);
	}
	solve(1, 0, 0, rows - 1, col - 1);
	cout << endl;
	show(rows, col);
	system("pause");
	return 0;
}

