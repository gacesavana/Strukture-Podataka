#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (120)

struct _Lista;
typedef struct _Lista* ListaPosition;
typedef struct _Lista
{
	char grad[max];
	int brojGradana;
	ListaPosition next;
}Lista;

struct _stablo;
typedef struct _stablo* stabloPosition;
typedef struct _stablo
{
	char drzava[max];
	ListaPosition List;
	stabloPosition Lijevo;
	stabloPosition Desno;
}stablo;


stabloPosition StvoriElementStabla(stabloPosition S);
stabloPosition ProcitajDatDrzava(stabloPosition p, char* dat);
stabloPosition Unesistablo(stabloPosition S, char* drzava, char* drzava_ime);
stabloPosition PronadiDrzavu(stabloPosition S, char* drzava);
int InOrder(stabloPosition S);
int StvoriListu(ListaPosition p, char* grad, int brojGradana);
ListaPosition ProcitajDatGradovi(ListaPosition p, char* dat);
int IspisiListu(ListaPosition p);
ListaPosition StvoriElementListe(ListaPosition p);
int Ispisi(ListaPosition p, int broj);


int main()
{
	stabloPosition root = NULL, trenutni = NULL;
	char dat[max] = "drzave.txt", drzava[max] = { 0 }, c = { 0 };
	int z = 1, broj = 0;

	root = StvoriElementStabla(root);

	root = ProcitajDatDrzava(root, dat);
	InOrder(root);

	printf("1) Izaberite drzavu! \n 2) Izlaz\n");

	while (z)
	{
		printf("\nIzbor:");
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Izaberite drzavu: \n");
			scanf(" %s", drzava);
			trenutni = PronadiDrzavu(root, drzava);
			if (trenutni == NULL)
			{
				printf("Odabrana država se ne nalazi u datoteci!");
				return 0;
			}
			printf("\nGradovi s većim brojem građana(od unesenog broja) će biti prikazani. Unesite broj: \n");
			scanf("%d", &broj);
			Ispisi(trenutni->List, broj);
			break;
		case '2':
			printf("Izlaz\n");
			z = 0;
			break;
		}
	}

	return 0;
}
ListaPosition StvoriElementListe(ListaPosition p)
{
	p = (ListaPosition)malloc(sizeof(Lista));
	if (p == NULL) {
		printf("Nemoguće alocirati memoriju!\n");
		return NULL;
	}

	strcpy(p->grad, "");
	p->brojGradana = 0;
	p->next = NULL;

	return p;
}

stabloPosition StvoriElementStabla(stabloPosition S)
{
	S = (stabloPosition)malloc(sizeof(stablo));

	if (S == NULL)
	{
		printf("Nemoguće alocirati memoriju!");
		return -1;
	}

	S->Lijevo = NULL;
	S->Desno = NULL;
	S->List = NULL;
	strcpy(S->drzava, "");

	return S;
}
stabloPosition ProcitajDatDrzava(stabloPosition p, char* dat)
{
	FILE* file = NULL;
	char drzava[max] = { 0 }, drzava_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Nemoguće otvoriti datoteku!");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava, drzava_dat);
		p = Unesistablo(p, drzava, drzava_dat);
	}

	fclose(file);
	return p;
}
stabloPosition Unesistablo(stabloPosition S, char* drzava, char* drzava_dat)
{
	if (S == NULL)
	{
		S = StvoriElementStabla(S);
		strcpy(S->drzava, drzava);
		S->List = NULL;
		S->List = ProcitajDatGradovi(S->List, drzava_dat);
	}
	else if (strcmp(S->drzava, drzava) > 0)
		S->Lijevo = Unesistablo(S->Lijevo, drzava, drzava_dat);
	else if (strcmp(S->drzava, drzava) < 0)
		S->Desno = Unesistablo(S->Desno, drzava, drzava_dat);

	return S;
}
ListaPosition ProcitajDatGradovi(ListaPosition p, char* dat)
{
	FILE* file = NULL;
	char grad[max] = { 0 };
	int brojGradana = 0;

	p = StvoriElementListe(p);

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Nemoguće otvoriti datoteku!\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d", grad, &brojGradana);
		StvoriListu(p, grad, brojGradana);
	}

	fclose(file);
	return p;
}
int StvoriListu(ListaPosition p, char* grad, int brojGradana)
{
	ListaPosition q = NULL;
	q = StvoriElementListe(q);

	strcpy(q->grad, grad);
	q->brojGradana = brojGradana;

	while (p->next != NULL)
	{
		if (q->brojGradana < p->next->brojGradana)
			break;
		else if (q->brojGradana == p->next->brojGradana)
		{
			if (strcmp(q->grad, p->next->grad) < 0)
				break;
			else if (strcmp(q->grad, p->next->grad) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;

}

int InOrder(stabloPosition S)
{
	if (S == NULL)
		return 0;
	else
	{
		InOrder(S->Lijevo);
		printf("\n%s:\n", S->drzava);
		IspisiListu(S->List);
		InOrder(S->Desno);
	}
	return 0;
}

int IspisiListu(ListaPosition p)
{
	if (p == NULL)
		return 0;
	else
	{
		p = p->next;
		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->brojGradana);
			p = p->next;
		}
		return 0;
	}
}

stabloPosition PronadiDrzavu(stabloPosition S, char* drzava)
{
	if (S == NULL)
		return NULL;
	else if (strcmp(drzava, S->drzava) == 0)
		return S;
	else if (strcmp(drzava, S->drzava) > 0)
		return PronadiDrzavu(S->Desno, drzava);

	return PronadiDrzavu(S->Lijevo, drzava);
}

int Ispisi(ListaPosition p, int broj)
{
	while (p != NULL)
	{
		if (broj < p->brojGradana)
			printf(" %s-%d", p->grad, p->brojGradana);
		p = p->next;
	}
	return 0;
}