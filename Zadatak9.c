#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 128
#define MAX_LINE 1024
#define Down_l 10
#define Up_l 90

struct _cvor;
typedef struct _cvor* Position;
typedef struct _cvor
{
	int number;
	Position left;
	Position right;
}cvor;

struct _Stack;
typedef struct _Stack* PositionStack;
typedef struct _Stack
{
	int element;
	PositionStack next;

}stack;

Position Insert(Position curr, Position new);
Position CreateNewElement(int num, Position curr);
int PrintInorder(Position curr);
int Replace(Position curr);
int Delete(Position curr);
int PopStack(PositionStack head);
int PushStack(PositionStack head, int element);
int AddOnStack(PositionStack head, Position curr);
int AddOnFile(PositionStack head, Position root, char* name);

int main()
{
	Position root = NULL;
	srand((unsigned)time(NULL));
	int i = 0, n;
	stack head = { .element = 0, .next = NULL };
	char name[MAX] = { 0 };

	printf("Enter file name: ");
	scanf(" %s", name);

	int niz[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	for (i = 0; i < 10; i++)
	{
		root = CreateNewElement(niz[i], root);
	}

	PrintInOrder(root);
	printf("\n");

	AddOnStack(&head, root);
	AddOnFile(&head, root, name);

	Replace(root);

	PrintInOrder(root);
	printf("\n");

	AddOnStack(&head, root);
	AddOnFile(&head, root, name);

	Delete(root);

	root = NULL;
	printf("\nBroj clanova: ");
	scanf(" %d", &n);

	for (i = 0; i < n; i++)
	{
		root = CreateNewElement((rand() % (Up_l - Down_l - 1) + Down_l + 1), root);
	}

	PrintInOrder(root);

	return 0;
}
Position Insert(Position curr, Position new)
{
	if (NULL == curr)
	{
		return new;
	}
	else if (new->number < curr->number)
	{
		curr->right = Insert(curr->right, new);
	}
	else
	{
		curr->left = Insert(curr->left, new);
	}

	return curr;
}
Position CreateNewElement(int num, Position curr)
{
	Position new = NULL;

	new = (Position)malloc(sizeof(cvor));

	if (!new)
	{
		printf("Error!");
		return NULL;
	}

	new->number = num;
	new->left = NULL;
	new->right = NULL;

	new = Insert(curr, new);

	return new;
}
int PrintInOrder(Position curr)
{
	if (!curr)
	{
		return 0;
	}

	PrintInOrder(curr->left);
	printf("%d ", curr->number);
	PrintInOrder(curr->right);

	return 0;
}
int Replace(Position curr)
{
	int sum = 0;
	int temp = 0;

	if (NULL != curr)
	{
		sum = Replace(curr->left);
		sum += Replace(curr->right);

		temp = curr->number;
		curr->number = sum;
		sum += temp;
	}
	return sum;

}
int Delete(Position curr)
{
	if (curr == NULL)
	{
		return 0;
	}

	Delete(curr->left);
	Delete(curr->right);

	free(curr);

	return 0;
}
int PopStack(PositionStack head)
{
	if (!head->next)
	{
		return 0;
	}

	PositionStack toDelete = head->next;
	head->next = toDelete->next;

	free(toDelete);

	return 0;
}
int PushStack(PositionStack head, int element)
{
	PositionStack new = NULL;

	new = (PositionStack)malloc(sizeof(stack));

	if (!new)
	{
		perror("Error!\n");
		return -1;
	}

	new->element = element;
	new->next = head->next;
	head->next = new;

	return 0;
}
int AddOnStack(PositionStack head, Position curr)
{
	if (curr==NULL)

	{
		return 0;
	}

	AddOnStack(head, curr->right);

	PushStack(head, curr->number);

	AddOnStack(head, curr->left);


	return 0;
}
int AddOnFile(PositionStack head, Position root, char* ime)
{
	FILE* fp = NULL;

	fp = fopen(ime, "imedat");

	if (!fp)
	{
		perror("Can not open file!\n");
		return -1;
	}

	while (head->next)
	{
		fprintf(fp, "%d ", head->next->element);
		PopStack(head);
	}

	fprintf(fp, "\n");

	fclose(fp);

	return 0;
}