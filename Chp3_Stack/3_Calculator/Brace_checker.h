#include "StackADT_char.h"
#define LEFT -1
#define RIGHT 1


int Brace_checker(Stack * pStack) { //return 0 == NO, return 1 == YES
	char checker = 0;
	if (Top(pStack) == -1) {
		return 1;
	}

	for (int i = 0; i < pStack->size; i++) {
		checker += Pop(pStack);
		if (checker < 0)
			return 0;
	}
	if (checker != 0)
		return 0;

	return 1;
}

int Checking(char buffer[]) { //1 yes , //0 no
	Stack* spSmall_Brace = createStack(50);
	Stack* spMiddle_Brace = createStack(50);
	Stack* spBig_Brace = createStack(50);

	int i = 0;

	while (buffer[i] != '\0') {
		if (buffer[i] == '(')
			Push(spSmall_Brace, LEFT);
		else if (buffer[i] == ')')
			Push(spSmall_Brace, RIGHT);
		else if (buffer[i] == '{')
			Push(spMiddle_Brace, LEFT);
		else if (buffer[i] == '}')
			Push(spMiddle_Brace, RIGHT);
		else if (buffer[i] == '[')
			Push(spBig_Brace, LEFT);
		else if (buffer[i] == ']')
			Push(spBig_Brace, RIGHT);

		i++;
	}

	if (Brace_checker(spSmall_Brace) && Brace_checker(spMiddle_Brace) && Brace_checker(spBig_Brace))
		return 1;

	return 0;
}