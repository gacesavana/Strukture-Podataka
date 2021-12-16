#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int br;
	Position left;
	Position right;

}tree;

Position InsertNewElement(int element, Position root);
Position CreateNewElement(int element);
int PrintInOrder(Position root);
int PrintPreOrder(Position root);
int PrintPostOrder(Position root);
int PrintLevelOrder(Position root);
int PrintCurrentLevel(Position root, int level);
int TreeDepth(Position current);
Position FindEl(int element, Position root);
Position FindMin(Position root);
Position DeleteEl(int element, Position root);



int main(int argc, char** argv)
{

	Position root = NULL;
	Position temp = NULL;

	int choice = 0;
	int element = 0;

	
	printf("Pick a number \n");
	printf("  1 - Insert Element\n");
	printf("  2 - Print In Order\n");
	printf("  3 - Print Pre Order\n");
	printf("  4 - Print Post Order\n");
        printf("  5 - Print Level Order\n");
	printf("  6 - Find Element\n");
	printf("  7 - Delete Element\n");
	printf("  0 - Exit\n");




	scanf("%d", &choice);

	while (choice != 0) {

		switch (choice)
		{
		case 1:
			printf("Which element do you want to insert: ");
			scanf("%d", &element);
			root = InsertNewElement(element, root);
			break;
		case 2:
			PrintInOrder(root);
			break;
		case 3:
			PrintPreOrder(root);
			break;
		case 4:
			PrintPostOrder(root);
			break;
                case 5:
                        PrintOrderLevel(root);
                        break;
          
		case 6:
			printf("Which element you want to find: ");
			scanf("%d", &element);
			temp = FindEl(element, root);
			if (!temp) {
				printf("Element not found!\n");
			}
			else {
				printf("Element found!\n");
			}
			break;
		case 7:
			printf("Which element you want to delete: ");
			scanf("%d", &element);

			root = DeleteEl(element, root);
		case 0:
			break;
		default:
			printf("Wrong input!\n");
		}


		printf("Pick a number \n");
		printf("  1 - Insert Element\n");
		printf("  2 - Print In Order\n");
		printf("  3 - Print Pre Order\n");
		printf("  4 - Print Post Order\n");
                printf("  5 - Print Level Order\n");
		printf("  6 - Find Element\n");
		printf("  7 - Delete Element\n");
		printf("  0 - Exit\n");



		scanf("%d", &choice);

	}





	return EXIT_SUCCESS;
}


Position InsertNewElement(int element, Position root)

{
	Position current = NULL;
	current = root;
	Position newEl = NULL;

	if (current == NULL)
	{
		newEl = CreateNewElement(element);
		return newEl;
	}
	else if (element < current->br)
		current->left = InsertNewElement(element, current->left);
	else if (element > current->br)
		current->right = InsertNewElement(element, current->right);
	else
		free(newEl);

	return current;


}

Position CreateNewElement(int element)
{
	Position  newEl = NULL;
	newEl = (Position)malloc(sizeof(tree));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newEl->br = element;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;

}

int PrintInOrder(Position  root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		printf("%d ", current->br);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}

int PrintPreOrder(Position root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		printf("%d ", current->br);
		PrintInOrder(current->left);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}




int PrintPostOrder(Position root)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		PrintInOrder(current->right);
		printf("%d ", current->br);
	}

	return EXIT_SUCCESS;
}

int PrintLevelOrder(Position root)
{
	int h = TreeDepth(root);
	int i = 1;
	while (i <= h)
	{
		PrintCurrentLevel(root, i);
		i++;
	}

	return EXIT_SUCCESS;
}


int PrintCurrentLevel(Position root, int level)
{
	Position current = NULL;
	current = root;

	if (root == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", root->br);
	else if (level > 1) {
		PrintCurrentLevel(root->left, level - 1);
		PrintCurrentLevel(root->right, level - 1);
	}
}

int TreeDepth(Position current)
{
	int LeftH = 0;
	int RightH = 0;

	if (current == NULL)
		return 0;
	else {
		LeftH = TreeDepth(current->left);
		RightH = LeftH = TreeDepth(current->left);
		(current->right);

		if (LeftH > RightH)
			return (LeftH + 1);
		else
			return (RightH + 1);
	}

	return EXIT_SUCCESS;
}
Position FindEl(int element, Position root)
{
	Position current = NULL;
	current = root;

	if (current == NULL)
	{
		return NULL;
	}
	else if (element < current->br)
		return FindEl(element, current->left);

	else if (element > current->br)
		return FindEl(element, current->right);
	else
		return current;

}
Position FindMin(Position root)
{

	Position current = NULL;
	current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

Position DeleteEl(int element, Position root)
{
	Position temp = NULL;
	Position current = NULL;
	current = root;

	if (current == NULL)
		printf("There is no such element in the tree!\n");

	else if (current->br > element)
		current->left = DeleteEl(element, current->left);

	else if (current->br < element)
		current->right = DeleteEl(element, current->right);

	else if (current->left != NULL && current->right != NULL) {

		temp = FindMin(current->right);
		current->br = temp->br;
		current->right = DeleteEl(current->br, current->right);
	}

	else {

		temp = current;

		if (current->left == NULL)
			current = current->right;

		else
			current = current->left;

		free(temp);
	}

	return current;
}
