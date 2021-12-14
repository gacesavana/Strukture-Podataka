#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	

	struct _StackElements;
	typedef struct _StackElement* Position;
	typedef struct _StackElement {
		double number;
		Position next;
	}StackElement;

	Position CreateElement(double number);
	int InsertAfter(Position position, Position newElement);
	int Push(Position head, double number);
	int DeleteAfter(Position position);
	int Pop(double* result, Position head);
	int PerformOperation(Position head, char operation);
	int CalculatePostfixFromFile(double* result, char* filename);

	int main() {

		double result = 0;

		CalculatePostfixFromFile(&result, "postfix.txt");

		printf("Result is: %0.1lf\n", result);

		return EXIT_SUCCESS;
	}

	Position CreateElement(double number) {

		Position newElement = NULL;

		newElement = (Position)malloc(sizeof(StackElement));

		if (!newElement) {
			perror("Can't allocate memory!\n");
			return NULL;
		}

		newElement->number = number;
		newElement->next = NULL;

		return newElement;
	}

	int InsertAfter(Position position, Position newElement) {
		newElement->next = position->next;
		position->next = newElement;

		return EXIT_SUCCESS;
	}

	int Push(Position head, double number) {

		Position newElement = NULL;

		newElement = CreateElement(number);
		if (!newElement) {
			return -1;
		}

		InsertAfter(head, newElement);

		return EXIT_SUCCESS;
	}

	int DeleteAfter(Position position) {

		Position temp = position->next;

		if (!temp) {
			return EXIT_SUCCESS;
		}

		position->next = temp->next;
		free(temp);

		return EXIT_SUCCESS;
	}

	int Pop(double* result, Position head) {

		Position first = head->next;
		if (!first) {
			perror("Postfix not valid! Please check your file!\n");
			return -1;
		}

		*result = first->number;

		DeleteAfter(head);

		return EXIT_SUCCESS;
	}

	int PerformOperation(Position head, char operation) {

		double operand1 = 0;
		double operand2 = 0;
		int status1 = EXIT_SUCCESS;
		int status2 = EXIT_SUCCESS;
		double result = 0;

		status2 = Pop(&operand2, head);

		if (status2 != EXIT_SUCCESS) {
			return -1;
		}

		status1 = Pop(&operand1, head);

		if (status1 != EXIT_SUCCESS) {
			return -2;
		}

		switch (operation) {
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand1 - operand2;
			break;
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			if (operand2 == 0) {
				printf("Can't divide with 0!\n");
				return -3;
			}
			result = operand1 / operand2;
			break;

		default:
			printf("ne valja");
			return -4;
		}

		Push(head, result);

		return EXIT_SUCCESS;
	}

	int CalculatePostfixFromFile(double* result, char* filename) {
		FILE* fp = NULL;
		int fpLength = 0;
		char* buffer = NULL;
		char* currentBuffer = NULL;
		char operation = '0';
		int status = 0;
		double number = 0;
		StackElement head = { .next = NULL, .number = 0 };
		int numBytes = 0;

		fp = fopen(filename, "rb");

		if (!fp) {
			perror("Can't open file!\n");
			return -1;
		}

		fseek(fp, 0, SEEK_END);
		fpLength = ftell(fp);
		
		buffer = (char*)calloc(fpLength + 1, sizeof(char));

		if (!buffer) {
			perror("Can't allocate memory!\n");
			return -1;
		}

		rewind(fp);
		fread(buffer, sizeof(char), fpLength, fp);
		printf("|%s|\n", buffer);
		fclose(fp);

		currentBuffer = buffer;

		while (strlen(currentBuffer) > 0) {
			status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
			if (status == 1) {
				Push(&head, number);
				currentBuffer += numBytes;
			}
			else {
				sscanf(currentBuffer, " %c %n", &operation, &numBytes);
				status = PerformOperation(&head, operation);

				if (status != EXIT_SUCCESS) {

					free(buffer);

					while (head.next != NULL) {
						DeleteAfter(&head);
					}

					return -2;
				}

				currentBuffer += numBytes;

			}
		}

		free(buffer);

		status = Pop(result, &head);

		if (status != EXIT_SUCCESS) {
			while (head.next != NULL) {
				return -3;
			}
		}
		if (head.next != NULL) {
			printf("Neispravan postfix! Provjerite datoteku!\n");
			return -4;
		}

		return EXIT_SUCCESS;
	}
