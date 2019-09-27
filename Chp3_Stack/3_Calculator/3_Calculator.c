#include "StackADT_char.h"
#include "Linked_list_stackADT_double.h"
#include "Brace_checker.h"

int isItOPERATOR(char ch) { //return 1 yes
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
		return 1;
	}
	else
		return 0;
}

int isItPAREN(char ch) { //return 1 yes
	if (ch == '(' || ch == ')') {
		return 1;
	}
	else
		return 0;
}

int Priority_checker(Element top, Element new_one) { //1 means higher priority, 0 means lower or same priority.
	// (,) >>> *,/ >>>> +,-
	if (((top == '+') || (top == '-')) && ((new_one == '*') || (new_one == '/'))) {
		return 1;
	}
	else {
		return 0;
	}
}

void In_to_Post(char* Infix, char* Postfix, int Infix_size) {
	Stack* Operator_Stack = createStack(Infix_size);
	int Postfix_index = 0;

	for (int i = 0; i < Infix_size; i++) {
		if (isItOPERATOR(Infix[i]) == 0) { //Number
			Postfix[Postfix_index] = Infix[i];
			Postfix_index++;
		}
		else if(Infix[i] == '(') {
			Push(Operator_Stack, '(');
		}
		else if (Infix[i] == ')') {
			while (Top(Operator_Stack) != '(') {
				Postfix[Postfix_index] = Pop(Operator_Stack);
				Postfix_index++;
			}
			Pop(Operator_Stack); //remove '('
		}
		else if (Infix[i] == '+' || Infix[i] == '-') {
			if (isEmpty(Operator_Stack) == 1) { //Operator_Stack is empty.
				Push(Operator_Stack, Infix[i]);
			}
			else {
				if (Top(Operator_Stack) == '(') {
					Push(Operator_Stack, Infix[i]); //Just Push
				}
				else {
					char temp = Pop(Operator_Stack);
					Push(Operator_Stack, Infix[i]);
					Postfix[Postfix_index] = temp;
					Postfix_index++;
				}
			}
		}
		else if (Infix[i] == '*' || Infix[i] == '/') {
			if (Priority_checker(Top(Operator_Stack), Infix[i]) == 1) { //Input higher priority.
				Push(Operator_Stack, Infix[i]);
			}
			else {
				if (isEmpty(Operator_Stack) == 1) { //Operator_Stack is empty.
					Push(Operator_Stack, Infix[i]);
				}
				else {
					if (Top(Operator_Stack) == '(') { //Just Push
						Push(Operator_Stack, Infix[i]);
					}
					else {
						char temp = Pop(Operator_Stack);
						Push(Operator_Stack, Infix[i]);
						Postfix[Postfix_index] = temp;
						Postfix_index++;
					}
				}
			}
		}
		else {
			printf("INVALID_FORMULA (ERROR CODE : 3)\n");
			exit(1);
		}
	}
	while (isEmpty(Operator_Stack) == 0) {
		char temp = Pop(Operator_Stack);
		Postfix[Postfix_index] = temp;
		Postfix_index++;
	}
}

double operating(char* Postfix) {
	StackNode* stackPtr = NULL;
	int index = 0;
	while (Postfix[index] != '\0') {
		if (isItOPERATOR(Postfix[index]) == 0) { //Number
			push_double(&stackPtr, Postfix[index] - '0'); //Change to real number.
		}
		else { //Operator
			if (Postfix[index] == '/') { //Check Divide by 0.
				if (top_double(&stackPtr) == 0) {
					printf("DIVIDED_BY_ZERO\n");
					exit(1);
				}
				else {
					double temp = pop_double(&stackPtr);
					double top = pop_double(&stackPtr);
					top /= temp;
					push_double(&stackPtr, top);
				}
			}
			else if(Postfix[index] == '+') {
				double temp = pop_double(&stackPtr);
				double top = pop_double(&stackPtr);
				top += temp;
				push_double(&stackPtr, top);
			}
			else if (Postfix[index] == '-') {
				double temp = pop_double(&stackPtr);
				double top = pop_double(&stackPtr);
				top -= temp;
				push_double(&stackPtr, top);
			}
			else if (Postfix[index] == '*') {
				double temp = pop_double(&stackPtr);
				double top = pop_double(&stackPtr);
				top *= temp;
				push_double(&stackPtr, top);
			}
		}
		index++;
	}
	return pop_double(&stackPtr);
}

int main() {
	char buffer[100] = { '\0', }; //Input Formula.
	int index = 0;
	gets(buffer);

	if (Checking(buffer) == 0) {
		printf("INVALID_FORMULA (ERROR CODE : 0)\n"); //Invalid because of the ()
		return 0;
	}

	while(buffer[index + 1] != '\0') {
		if (isItOPERATOR(buffer[index]) && isItOPERATOR(buffer[index + 1])) {
			if (isItPAREN(buffer[index]) || isItPAREN(buffer[index + 1])) {
				index++;
				continue;
			}
			else {
				printf("INVALID_FORMULA (ERROR CODE : 1)\n"); //Operator and operator
				return 0;
			}
		}
		else if (!isItOPERATOR(buffer[index]) && !isItOPERATOR(buffer[index + 1])) {
			printf("INVALID_FORMULA (ERROR CODE : 2)\n"); //Operand and operand
			return 0;
		}
		index++;
	}
	int formula_size = ++index;

	char Postfix[100] = {'\0', };
	In_to_Post(buffer, Postfix, formula_size); //Call by reference.
	printf("%f\n", operating(Postfix));
	return 0;
}