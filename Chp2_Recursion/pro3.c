#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int stringLength(int *count, char arr[]) { //recursive
	if (*arr == '\0')
		return *count; //count should start by 0.
	else {
		(*count)++;
		return stringLength(count, arr + 1);
	}
}

int palindrome(int i, int j, char arr[]) { //recursive
	//return 0 : palindrome
	//return 1 : not palindrome
	if (i >= j)
		return 0;
	
	if (arr[i] == arr[j]) {
		return palindrome(++i, --j, arr);
	}
	else {
		return 1;
	}
	return 0;
}

int main() {
	int i = 0;
	do {
		char arr[30];
		int count = 0;
		scanf("%s", &arr);
		stringLength(&count, arr);
		printf("The string is%spalindorme\n", palindrome(0, count - 1, arr) ? " not " : " ");
		i++;
	} while (i < 5);

	return 0;
}