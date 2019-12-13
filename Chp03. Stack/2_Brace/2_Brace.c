#include "StackADT_char.h"
#include "Brace_checker.h"
#define LEFT -1
#define RIGHT 1

int main() {
	char buffer[100] = { '\0', };
	gets(buffer);

	if (Checking(buffer) == 1)
		printf("yes\n");
	else
		printf("no\n");

	return 0;
}