#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 50
#define MAX_LINE 1024

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char name[MAX];
	char surname[MAX];
	int birthyear;
	Position next;
}Person;

Position CreatePerson(char* name, char* surname, int birthyear);
int AddAfter(Position head, char* name, char* surname, int birthyear, char* adafsurname);
int AddBefore(Position head, char* name, char* surname, int birthyear, char* adbefsurname);
int UpisUDatoteku(Position first, char* datoteka);
int IspisListeIzDatoteke(char* datoteka);

int main()
{

	Person head = { .name = {0}, .surname = {0}, .birthyear = 0, .next = NULL };
	Position NewPerson = NULL;
	char adafsurname[MAX] = { 0 };
	char adbefsurname[MAX] = { 0 };
	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int birthyear = 0;
	
	
	
	printf("Unesite podatke o osobi koju želite unijeti u listu");
	scanf("%s %s %d", name, surname, &birthyear);
	printf("Unesite prezime osobe iza koje želite dodati novu osobu");
	scanf("%s", adafsurname);
	AddAfter(&head, name, surname, birthyear, adafsurname);


	printf("Unesite podatke o osobi koju želite unijeti u listu");
	scanf("%s %s %d", name, surname, &birthyear);
	printf("Unesite prezime osobe ispred koje želite dodati novu osobu");
	scanf("%s", adbefsurname);
	AddBefore(&head, name, surname, birthyear, adbefsurname);

	UpisUDatoteku(head->next, "datoteka.txt");

	IspisListeIzDatoteke("datoteka.txt");
	

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthyear)
{
	Position Newperson = NULL;
	Newperson = (Position)malloc(sizeof(Person));
	if (!Newperson)
	{
		perror("Cant allocate memory!\n");
		return NULL;
	}
	strcpy(Newperson->name, name);
	strcpy(Newperson->surname, surname);
	Newperson->birthyear = birthyear;
	Newperson->next = NULL;

	return Newperson;

}


int AddAfter(Position head, char* name, char* surname, int birthyear,char *adafsurname)
{
	Position Newperson = NULL;
	Position temp = head;
	Newperson = CreatePerson(name, surname, birthyear);
	if(!Newperson)
	{
		return -1;
	}
	while (temp != NULL && temp->surname != adafsurname)
	{
		temp = temp->next;

	}
	if (temp!=NULL)
	{
		Newperson->next = temp->next;
		temp->next = Newperson;
	}
	else
	{
		printf("Greška, takvo prezime ne postoji");
	}

	return 0;
}

int AddBefore(Position head, char* name, char* surname, int birthyear, char* adbefsurname)
{
	Position Newperson = NULL;
	Position temp = head;
	Newperson = CreatePerson(name, surname, birthyear);
	if (!Newperson)
	{
		return -1;
	}
	while (temp != NULL && temp->next->surname != adbefsurname)
	{
		temp = temp->next;

	}
	if (temp->next!= NULL)
	{
		Newperson->next = temp->next;
		temp->next = Newperson;
	}
	else
	{
		printf("Greška, takvo prezime ne postoji");
	}
	return 0;

}


int UpisUDatoteku(Position first, char* datoteka)
{
	FILE* lista = NULL;
	Position temp = first;
	lista = fopen(datoteka, "w");

	if (!lista)
	{
		return -1;
	}
	while (temp)
	{
		fprintf(" %s %s %d\n", temp->name, temp->surname, temp->birthyear);
		temp = temp->next;

	}
	fclose(lista);
	return 0;
	
}


int IspisListeIzDatoteke(char* datoteka)
{
	FILE* lista = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int birthyear = 0;

	lista = fopen(datoteka, "r");
	if (!lista)
	{
		return -1;
	}
	
	while (!feof(lista))
	{
		fgets(buffer, MAX_LINE, lista);
		sscanf(buffer, "%s %s %d", name, surname,&birthyear);
		printf("%s %s %d\n", name, surname, birthyear);
	}
	fclose(lista);
	return 0;
}

