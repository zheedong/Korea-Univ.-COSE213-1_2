#include "StackADT_int.h"
#pragma warning (disable : 4996)

void printMenu() {
	printf("\n-------------------------------\n");
	printf("             MENU\n");
	printf("0. Creat Stack\n");
	printf("1. Push\n");
	printf("2. Pop\n");
	printf("3. Top\n");
	printf("4. CatStack\n");
	printf("5. Exit\n");
	printf("-------------------------------\n");
}

int main() {
	int size;
	int buffer;
	int a;

	int stack_instructor_pointer = 0;

	Stack* Stack_array[100] = { '0', };
	int stack_index = 0;

	while (1) {
		printMenu();
		do {
			a = scanf("%d", &buffer);
			if (buffer < 0 || buffer > 5)
				printf("Try again. Enter between 0 to 5\n");
		} while (buffer < 0 || buffer > 5);

		switch (buffer) {
		case 0:
			printf("How many Elements do you want to save in stack? (Element : int)\n");
			a = scanf("%d", &size);
			Stack_array[stack_index] = createStack(size);
			printf("Enter the elements\n");
			for (int i = size; i > 0; i--) {
				a = scanf("%d", &buffer);
				Push(Stack_array[stack_index], buffer);
			}
			printf("This Stack index is %d\n", stack_index);
			stack_index++;
			break;
		case 1:
			printf("Enter the push element and Stack index\n");
			a = scanf("%d %d", &buffer ,&stack_instructor_pointer);

			if (stack_instructor_pointer > stack_index) {
				printf("Invalide Stack index.\n");
				break;
			}

			Push(Stack_array[stack_instructor_pointer], buffer);
			printf("Current stack size of Stack #%d : %d\n", stack_instructor_pointer, Stack_array[stack_instructor_pointer]->top + 1);
			break;

		case 2:
			printf("Enter the Stack index\n");
			a = scanf("%d", &stack_instructor_pointer);
			if (stack_instructor_pointer > stack_index) {
				printf("Invalide Stack index.\n");
				break;
			}
			printf("Pop stack : %d\n", Pop(Stack_array[stack_instructor_pointer]));
			printf("Current stack size of Stack #%d : %d\n", stack_instructor_pointer, Stack_array[stack_instructor_pointer]->top + 1);
			break;
		case 3:
			printf("Enter the Stack index\n");
			a = scanf("%d", &stack_instructor_pointer);
			if (stack_instructor_pointer > stack_index) {
				printf("Invalide Stack index.\n");
				break;
			}
			printf("Top stack : %d\n", Top(Stack_array[stack_instructor_pointer]));
			printf("Current stack size of Stack #%d : %d\n", stack_instructor_pointer, Stack_array[stack_instructor_pointer]->top + 1);
			break;
		case 4:
			printf("Enter the two Stack index\n");
			int i, j;
			a = scanf("%d %d", &i, &j);
			if (i > stack_index || j > stack_index) {
				printf("Invalide Stack index.\n");
				break;
			}
			Stack_array[i] = CatStack(Stack_array[i], Stack_array[j]);
			printf("Current stack size of Stack #%d : %d\n", i, Stack_array[i]->top + 1);
			break;
		case 5:
			for (int i = 0; i < stack_index; i++) {
				DestroyStack(Stack_array[i]);
			}
			return 0;
		default:
			printf("Fatal ERROR\n");
			exit(1);
		}

	}
}