#include <stdio.h>
#include <stdlib.h>

int fibLoop(int fiboCount) {
	if (fiboCount <= 1) {
		return -1;
	}
	else {
		int f1 = 0;
		int f2 = 1;
		int sum = 0;
		
		for (int i = 0; i < fiboCount; i++) {
			printf("	%d : %d\n", i, f1);
			sum = f1 + f2;
			f1 = f2;
			f2 = sum;
		}
		return 0;
	}
}

int fib(int i, int fibo1, int fibo2) {
	if (i == 10) {
		return 0;
	}
	int fibo3 = fibo1 + fibo2;
	printf("	%d : %d\n", i, fibo1);
	return fib(++i, fibo2, fibo3);
}

int main() {
	int fibo1 = 0;
	int fibo2 = 1;
	int i = 0;

	printf("Loop:\n");
	fibLoop(10);
	printf("--------------------\n");
	printf("Recursion:\n");
	fib(i, fibo1, fibo2);

	return 0;
}