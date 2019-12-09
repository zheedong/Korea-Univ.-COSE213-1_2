#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning (disable : 4996)
#define SIZE 10 

int distance(int SP[][SIZE], int destination) //Find distance from [0][0] to [row][col]
{
	int one_before = 0;
	for (one_before = 0; one_before < SIZE; ++one_before)
	{
		if (SP[one_before][destination] != 0)
			break;
	}

	if (one_before == 0)
		return 0;

	return distance(SP, one_before) + SP[one_before][destination];
}

int main()
{
	int cost[SIZE][SIZE] = {
	{0, 6, 3, 0, 9,   0, 0, 0, 0, 0},
	{6, 0, 4, 2, 0,   0, 0, 9, 0, 0},
	{3, 4, 0, 2, 9,   9, 0, 0, 0, 0},
	{0, 2, 2, 0, 0,   8, 0, 9, 0, 0},
	{9, 0, 9, 0, 0,   8, 0, 0, 0, 18},
	{0, 0, 9, 8, 8,   0, 9, 7, 0, 10},
	{0, 0, 0, 0, 0,   9, 0, 5, 1, 3},
	{0, 9, 0, 9, 0,   7, 5, 0, 4, 0},
	{0, 0, 0, 0, 0,   0, 1, 4, 0, 4},
	{0, 0, 0, 0, 18, 10, 3, 0, 4, 0}
	};
	
	bool visited[SIZE] = { false, };
	visited[0] = true;
	int Shortest_Path[SIZE][SIZE] = { { 0, }, };

	int min = 999;
	int row = 0;
	int col = 0;
	int min_col = 0;
	for (col = 0; col < SIZE; ++col) //Initialization
	{
		if (cost[0][col] != 0 && cost[0][col] < min)
		{
			min = cost[0][col];
			min_col = col;
		}
	}
	visited[min_col] = true;
	Shortest_Path[row][min_col] = min;
	Shortest_Path[min_col][row] = min;

	for (int i = 2; i < SIZE; ++i)
	{
		int min = 999;
		int min_row = 0;
		int min_col = 0;
		for (row = 0; row < SIZE; ++row) {
			if (visited[row]) {
				for (col = 0; col < SIZE; ++col) {
					if (!visited[col] && cost[row][col] != 0) {
						int dist = distance(Shortest_Path, row) + cost[row][col];
						if (dist < min)
						{
							min = cost[row][col];
							min_row = row;
							min_col = col;
						}
					}
				}
			}
		}
		visited[min_col] = true;
		Shortest_Path[min_row][min_col] = min;
		Shortest_Path[min_col][min_row] = min;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
			printf("%2d, ", Shortest_Path[i][j]);
		printf("\n");
	}

	return 0;
}
