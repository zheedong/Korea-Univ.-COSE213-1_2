#include "stack_array.h"
#pragma warning (disable : 4996)

void printMenu() {
		 printf("\n-------------------------------\n");
		 printf("             MENU\n");
		 printf("1. Push\n");
		 printf("2. Pop\n");
		 printf("3. Top\n");
		 printf("4. Exit\n");
		 printf("-------------------------------\n");
}

 int main() {
	 int size;
	 int buffer;

	 printf("How many Element do you want to save in stack? (Element : int)\n");
	 scanf("%d", &size);
	Stack *pStack = createStack(size);
	 printf("Enter the elements\n");
	 for (int i = size; i > 0; i--) {
		 scanf("%d", &buffer);
		 Push(pStack, buffer);
	}

	 while (1) {
		 printMenu();
		 do {
			 scanf("%d", &buffer);
			 if (buffer < 1 || buffer > 4)
				 printf("Try again. Enter between 1 to 4\n");
		 } while (buffer < 1 || buffer > 4);
		 switch (buffer) {
		 case 1:
			 printf("Enter the push element\n");
			 scanf("%d", &buffer);
			 Push(pStack, buffer);
			 printf("Current stack size : %d\n", pStack->top + 1);
			 break;
		 case 2:
			 printf("Pop stack : %d\n", Pop(pStack));
			 printf("Current stack size : %d\n", pStack->top + 1);
			 break;
		 case 3:
			 printf("Top stack : %d\n", Top(pStack));
			 printf("Current stack size : %d\n", pStack->top + 1);
			 break;
		 case 4:
			 DestroyStack(pStack);
			 return 0;
		 default:
			 printf("Fatal ERROR\n");
			 exit(1);
		 }

	 }
 } 