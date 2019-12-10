#include <stdio.h>
#include <stdlib.h>
#define	N	10

void printArr(int arr[], const size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void merge(int arr[], int low, int mid, int high)
{
	int i = low, j = mid + 1, k = low;
	int tmp[N]; // »õ ¹è¿­
	while (i <= mid && j <= high) {
		if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while (i <= mid) 
		tmp[k++] = arr[i++];
	while (j <= high)
		tmp[k++] = arr[j++];
	for (int a = low; a <= high; a++)
		arr[a] = tmp[a];
}

void mergeSort(int arr[], int low, int high)
{
	// merge sort body
	int mid = (low + high) / 2;
	if (low < high)
	{
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

int main()
{
	int values[N] = { 1,0,6,7,3, 9,6,6,2,8 };

	printArr(values, N);

	mergeSort(values, 0, N - 1);

	printArr(values, N);

	return 0;
}
