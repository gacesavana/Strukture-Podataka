#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position first,char* surname);
int DeleteAfter(Position head, char* surname);

int main() {
	
	
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position temp = NULL;
	Position p = &Head;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = {0};
	int birthYear=0;



	printf("Unesite informacije o osobi koju želite unijeti na početak liste");
	scanf(" %s %s %d",name, surname, birthYear);
	PrependList(&Head, name, surname, birthYear);


	printf("Unesite informacije o osobi koju želite unijeti na kraj liste");
	scanf(" %s %s %d", name, surname, birthYear);
	AppendList(&Head, name, surname, birthYear);

	printf("Unesite prezime studenta kojeg zelite pronaci");
	scanf("%s",surname);
	temp = FindBySurname(&Head, surname);
	if (temp) {
		printf(" %s %s %d", temp->name, temp->surname, temp->birthYear);
	}

	else {
		printf("Osoba koju trazite ne postoji u listi");
	}
	printf("Unesite prezime osobe koju zelite obrisati");
	scanf("%s",surname);
	DeleteAfter(&Head, surname);


	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear) {

	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp) {
		printf("Name: %s, surname: %s, birthyear: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}

int FindBySurname(Position first, char* surname)
{
	Position temp = first;
	while (temp) {
		if (strcmp(temp->surname, surname) == 0) {
			return temp;
		}
	}
	return NULL;
}

Position FindBefore(Position first, char* surname)
{
	Position temp = first;

	while (temp!=NULL && temp->surname!=surname)
	{
		temp = temp->next;

	}
	if (temp == NULL) {
		return NULL;
	}
	else {
		return temp;
	}
	


}
int DeleteAfter(Position head, char* surname)
{

	Position temp = head;
	
	while (temp != NULL && temp->surname != surname)
	{
		temp = temp->next;
	}
	if (temp->surname = surname)
	{
		temp = temp->next;
		free(temp);
	}

	return 0;


}