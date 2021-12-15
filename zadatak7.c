#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

struct _Directory;
typedef struct _Directory* Position;
typedef struct _Directory {
	char name[MAX];
	Position sibling;
	Position child;
}Directory;

struct _Stack;
typedef struct _Stack* StackPosition;
typedef struct _Stack {
	Position directory;
	StackPosition next;
}Stack;


Position insertDirectory(Position current, Position newElement);
Position CreateDirectory(char* name);
StackPosition CreateStackElement(Position directory);
int PushStack(StackPosition head, StackPosition newStackElement);
Position PopStack(StackPosition head, Position current);
int PrintDirectory(Position current);
Position Move(Position current, char* destinationName, StackPosition stack);
int Free(Position root);


int main()
{
	Directory Root = { .name = "root", .sibling = NULL, .child = NULL };
	Position root = &Root;
	Position current = root;

	Stack Head = { .directory = NULL, .next = NULL };
	StackPosition head = &Head;

	int choice = 0;
	char directoryName[MAX] = { 0 };

	printf("Enter your choice: \n");

	printf("1 - Make directory \n");
	printf("2 - Change position to an another directory \n");
	printf("3 - Move to parent directory \n");
	printf("4 - Print the content of the directory\n");
	printf("5 - exit \n");

	printf("Witch choice do you want");
	scanf("%d", &choice);


	while (choice != 5)
	{

		switch (choice)
		{
		case 1:
		{
			printf("Enter the name of the new directory: ");
			scanf(" %s", directoryName);
			Position newDirectory = CreateDirectory(directoryName);
			current->child = insertDirectory(current->child, newDirectory);
			break;
		}

		case 2:
		{
			printf("Enter the name of the destination directory: ");
			scanf(" %s", directoryName);
			current = Move(current, directoryName, head);
			break;
		}
		case 3:
		{
			current = PopStack(head, current);
			break;
		}
		case 4:
		{
			printf("/%s: \n", current->name);
			PrintDirectory(current);
			break;
		}
		default:
		{
			if (choice != 5)
			{
				printf("Wrong input, please try again.\n\n");
				break;
			}
		}
		}
		puts("\n");

		printf("1 - Make directory\n");
		printf("2 - Change position to an another directory \n");
		printf("3 - Move to parent directory \n");
		printf("4 - Print the content of the directory\n");
		printf("5 - exit \n");

		printf("Witch choice do you want");
		scanf("%d", &choice);

	}

	Free(root->child);

	return EXIT_SUCCESS;
}

Position insertDirectory(Position current, Position newEl)
{
	if (!current)
		return newEl;

	if (strcmp(current->name, newEl->name) < 0)
		current->sibling = insertDirectory(current->sibling, newEl);

	else if (strcmp(current->name, newEl->name) > 0)
	{
		newEl->sibling = current;
		return newEl;
	}
	return current;
}

Position CreateDirectory(char* name)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(Directory));

	if (!newEl)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, name);
	newEl->sibling = NULL;
	newEl->child = NULL;

	return newEl;
}

StackPosition CreateStackElement(Position current)
{
	StackPosition newEl = NULL;
	newEl = (StackPosition)malloc(sizeof(Stack));

	if (!newEl)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	newEl->directory = current;
	newEl->next = NULL;

	return newEl;
}


int PushStack(StackPosition head, StackPosition newEl)
{
	newEl->next = head->next;
	head->next = newEl;

	return EXIT_SUCCESS;
}

Position PopStack(StackPosition head, Position current)
{
	StackPosition first = NULL;
	first = head->next;

	Position temp = NULL;

	if (!first)
	{
		printf("This directory does not have a parent");
		return current;
	}
	temp = first->directory;

	head->next = first->next;
	free(first);

	return temp;
}

int PrintDirectory(Position current)
{
	Position temp = current->child;

	while (temp)
	{
		printf(" -%s \n", temp->name);
		temp = temp->sibling;
	}

	return EXIT_SUCCESS;
}

Position Move(Position current, char* name, StackPosition stack)
{
	Position temp = current->child;
	while (temp && strcmp(temp->name, name))
		temp = temp->sibling;

	if (temp == NULL)
	{
		printf("There is no subdirectory with name: %s ", name);
		return current;
	}
	else
	{
		StackPosition newEl = CreateStackElement(current);
		PushStack(stack, newEl);
		return temp;
	}
	return temp;
}

int Free(Position current)
{
	if (current && current->sibling)
		Free(current->sibling);

	if (current && current->child)
		Free(current->child);

	free(current);

	return EXIT_SUCCESS;
}