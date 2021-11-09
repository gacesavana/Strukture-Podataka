
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024
#define MAX 50

struct _Polinom;
typedef struct _Polinom* Position;
typedef struct _Polinom {

	int k;
	int p;
	Position next;

}Polinom;

ReadFromFile(char* datoteka,Position head1,Position head2);
Position CreateNewElement(int k, int p);
int ParseStringIntoList(Position head, char buffer);
int InsertSorted(Position head, Position NewElement);
int InsertAfter(Position temp, Position NewElement);
int DeleteAfter(Position temp);
int AddPolinom(Position head1, Position head2, Position newhead);
int MultiplyPolinom(Position head1, Position head2, Position newhead);
int ClearMemory(Position newhead);

int main(int argc,char** argv)
{
	Polinom head1 = { .k = 0,.p = 0,.next = NULL };
	Polinom head2 = { .k = 0,.p = 0,.next = NULL };
	Polinom newhead = { .k = 0,.p = 0,.next = NULL };
	
	char imedatoteke[MAX] = { 0 };
	printf("Unesite ime datoteke koju zelite otvoriti");
	scanf("%s", imedatoteke);


	ReadFromFile(imedatoteke, &head1, &head2);
	AddPolinom(&head1, &head2, &newhead);
	MultiplyPolinom(&head1, &head2, &newhead);

	return EXIT_SUCCESS;
}

int ReadFromFile(datoteka, head1, head2)
{
	char buffer[MAX_LINE] = { 0 };
	Position NewElement = NULL;
	
	FILE* fp = NULL;
	fp = fopen(datoteka,"r");
	if (!fp)
	{
		return - 1;
	}

	fgets(buffer, MAX_LINE, fp);
	ParseStringIntoList(head1, buffer);

	fgets(buffer, MAX_LINE, fp);
	ParseStringIntoList(head2, buffer);
	

	fclose(fp);
	return 0;
}
Position CreateNewElement(int k, int p)
{
	Position NewElement = NULL;
	NewElement = (Position)malloc(sizeof(Polinom));
	if (!NewElement)
	{
		perror("Cant allocate memory!\n");
		return NULL;
	}
	NewElement->k = k;
	NewElement->p = p;
	NewElement->next = NULL;

	return NewElement;

}

int ParseStringIntoList(Position head,char* buffer)
{
	int k = 0;
	int p = 0;
	int n = 0;
	char* newbuffer = buffer;
	Position NewElement = NULL;
	int provjera = 0;


	provjera=sscanf(newbuffer, " %d %d %n", &k, &p, &n);
	if (provjera != 2)
	{
		printf("Greška, datoteka nije dobro napisana");
	}
	
	NewElement = CreateNewElement(k, p);
	if (!NewElement)
	{
		return NULL;
	}
	InsertSorted(head, NewElement);
	
	newbuffer += n;
	
	
	return 0;
}
int InsertSorted(Position head, Position NewElement)
{
	Position temp = head;
	int result = 0;
	while (temp->next != NULL && temp->next->p > NewElement->p)
	{
		temp = temp->next;
	}
	if (temp->next != NULL && temp->next->p == NewElement-> p)
	{
		result=temp->next->k + NewElement->k;
		if (result == 0)
		{
			DeleteAfter(temp);
		}
		else
		{
			temp->next->k = result;
		}
		free(NewElement);
		
	}

	else
	{
		InsertAfter(temp, NewElement);
	}

	return 0;
}

int InsertAfter(Position temp, Position NewElement)
{
	NewElement->next = temp->next;
	temp->next = NewElement;

	return 0;
}
int DeleteAfter(Position temp)
{
	Position toDelete = NULL;

	toDelete = temp->next;
	temp->next = toDelete->next;
	free(toDelete);

	return 0;
}

int AddPolinom(Position head1, Position head2, Position newhead)
{
	
	Position i = head1->next;
	Position j = head2->next;
	Position NewElement = NULL;
	Position temp = newhead;
	Position pomocna = NULL;
	
	int sum = 0;

	while (i != NULL && j != NULL)
	{
		if (i->p == j->p)
		{
			sum = i->k + j->k;
			if (sum == 0)
			{
				DeleteAfter(temp);
			}
			NewElement=CreateNewElement(sum, i->p);
			InsertAfter(temp, NewElement);
			i = i->next;
			j = j->next;
			temp = temp->next;
		}
		else if (i->p > j->p)
		{
			NewElement = CreateNewElement(i->k, i->p);
			InsertAfter(temp,NewElement);
			i = i->next;
			temp = temp->next;
		}
		else
		{
			NewElement = CreateNewElement(j->k, j->p);
			InsertAfter(temp, NewElement);
			j = j->next;
			temp = temp->next;
		}
	}
	if (i == NULL)
	{
		pomocna = j;
	}
	else if (j == NULL)
	{
		pomocna = i;
	}
	while (pomocna != NULL)
	{
		NewElement = CreateNewElement(pomocna->k, pomocna->p, temp);
		InsertAfter(temp, NewElement);
		pomocna = pomocna -> next;
	}
	ClearMemory(temp);
	
	return 0;
}


int MultiplyPolinom(Position head1,Position head2,Position newhead)
{
	Position NewElement = NULL;
	Position i = head1->next;
	Position j = head2->next;

	while (i != NULL);
	{
		j = j->next;
		while (j != NULL)
		{
			NewElement = CreateNewElement(i->k * j->k, i->p + j->p);
			InsertSorted(newhead, NewElement);
			j = j->next;
		}
		i = i->next;
	}
	ClearMemory(newhead);
	
	return 0;
}

int ClearMemory(Position newhead)
{
	Position temp = newhead;
	Position toFree = NULL;

	while (temp->next != NULL) {
		if (!temp->next->k) {
			toFree = temp->next;
			temp->next = temp->next->next;
			free(toFree);
		}
		temp = temp->next;
	}

	return 0;
}