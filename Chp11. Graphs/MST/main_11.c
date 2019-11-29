#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning (disable : 4996)

#define MAX_SIZE 10

struct _Minimun_Spanning_Tree {
	bool Selected_Vertex[MAX_SIZE];
	int MinimumSpanningTree[MAX_SIZE][MAX_SIZE];
};

struct _Minimum {
	int from;
	int to;
	int weight;
};

typedef struct _Minimun_Spanning_Tree MST;
typedef struct _Minimum Mini;

int main() {
	bool SpanningTree[10] = { false, };
	SpanningTree[0] = true;
	MST mst;
	Mini Cur_mini;

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			mst.MinimumSpanningTree[i][j] = 0;
		}
		mst.Selected_Vertex[i] = false;
	}
	mst.Selected_Vertex[0] = true;

	int graphMatrix[MAX_SIZE][MAX_SIZE] = {
	{0, 6, 3, 0, 9, 0, 0, 0, 0, 0},
	{6, 0, 4, 2, 0, 0, 0, 9, 0, 0},
	{3, 4, 0, 2, 9, 9, 0, 0, 0, 0},
	{0, 2, 2, 0, 0, 8, 0, 9, 0, 0},
	{9, 0, 9, 0, 0, 8, 0, 0, 0, 18},
	{0, 0, 9, 8, 8, 0, 9, 7, 1, 10},
	{0, 0, 0, 0, 0, 9, 0, 5, 4, 3},
	{0, 9, 0, 9, 0, 7, 5, 0, 4, 0},
	{0, 0, 0, 0, 0, 1, 4, 4, 0, 4},
	{0, 0, 0, 0, 18, 10, 3, 0, 4, 0}
	};

	for (int mst_size = 0; mst_size < MAX_SIZE - 1; ++mst_size)
	{
		Cur_mini.from = 0;
		Cur_mini.to = 0;
		Cur_mini.weight = 20;

		for (int row = 0; row < MAX_SIZE; ++row)
		{
			if (mst.Selected_Vertex[row] == true)
			{
				for (int col = 0; col < MAX_SIZE; ++col)
				{
					if (mst.Selected_Vertex[col] == false)
					{
						if (graphMatrix[row][col] != 0 && graphMatrix[row][col] < Cur_mini.weight)
						{
							Cur_mini.from = row;
							Cur_mini.to = col;
							Cur_mini.weight = graphMatrix[row][col];
						}
					}
				}
			}
		}

		mst.Selected_Vertex[Cur_mini.to] = true;
		mst.MinimumSpanningTree[Cur_mini.from][Cur_mini.to] = Cur_mini.weight;
		mst.MinimumSpanningTree[Cur_mini.to][Cur_mini.from] = Cur_mini.weight;
	}

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
			printf("%2d, ", mst.MinimumSpanningTree[i][j]);
		printf("\n");
	}

	return 0;
}
