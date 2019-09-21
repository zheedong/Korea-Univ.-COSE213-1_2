#include <stdio.h>
#include <stdlib.h>

long long int fibtail(int count,  long long int fibo1, long long int fibo2) {
	if (count == 0) {
		return fibo1;
	}
	else {
		return fibtail(--count, fibo2, fibo1 + fibo2);
	}
}

int main() {
	int count = 49;
	long long int fibo1 = 0;
	long long int fibo2 = 1;
	while (count < 59) {
		printf("%d : %lld\n", count + 1, fibtail(count, fibo1, fibo2));
		count++;
	}
	return 0;
}