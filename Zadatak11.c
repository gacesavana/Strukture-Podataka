#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 120
#define hashvel 11

struct _stablo;
typedef struct _stablo* stabloposition;
typedef struct _stablo
{
	char grad[MAX];
	int brGradana;

	stabloposition lijevo;
	stabloposition desno;

}stablo;

struct _lista;
typedef struct _lista* listaposition;
typedef struct _lista
{
	char drzava[MAX];

	stabloposition stablo;
	listaposition next;

}lista;


struct _tablica;
typedef struct _tablica* hash;
typedef struct _tablica
{
	listaposition* hashLista;
}tablica;


int ProcitajDatDrzava(hash HTab, char* dat);
int UnesiSortirano(listaposition p, char* ime_drzave, char* datoteka_drzava);
stabloposition StvoriStablo(stabloposition root, char* grad, int brGradana);
int Ispisi(listaposition p);
int InOrder(stabloposition S);
int InOrderPrintBiggerThan(stabloposition p, int number);
listaposition StvoriListaElement(listaposition p);
listaposition PronadiDrzavu(hash HTab, char* drzava);
stabloposition ProcitajDatGradovi(stabloposition root, char* datoteka_drzava);
listaposition StvoriListaElementAlokacija();
hash InicijalizacijaHashTab();
int DodajUTablicu(char* drzava, char* datoteka_drzava, hash H);
int HashFun(char* drzava);




int main()
{
	listaposition p = NULL;
	hash HTab = NULL;
	char dat[MAX] = "drzave.txt", c = { 0 }, drzava[MAX] = { 0 };
	int number = 0;
	int z = 1;

	HTab = InicijalizacijaHashTab();
	p = StvoriListaElement(p);

	ProcitajDatDrzava(HTab, dat);
	

	printf("\n1) Odaberite državu! \n2) Exit\n");
	while (z)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Odaberite državu : ");
			scanf(" %s", drzava);
			p = PronadiDrzavu(HTab, drzava);
			if (p == NULL)
			{
				printf("Ta država se ne nalazi u datoteci!\n");
				return EXIT_FAILURE;
			}
			printf("\nGradovi s više građana nego što ste unijeli će biti prikazani. Upišite broj: \n");
			scanf("%d", &number);
			InOrderPrintBiggerThan(p->stablo, number);
			break;
		case '2':
			printf("Exit.\n");
			z = 0;
			break;
		}
	}
	return 0;
}



hash InicijalizacijaHashTab()
{
	hash H = NULL;
	int i = 0;

	H = (hash)malloc(sizeof(tablica));
	if (H == NULL)
	{
		printf("Nemoguće inicijalizirati.\n");
		return NULL;
	}

	H->hashLista = (listaposition*)malloc(sizeof(listaposition) * hashvel);
	if (H->hashLista == NULL)
	{
		printf("Nemoguće inicijalizirati.\n");
		return NULL;
	}

	for (i = 0;i < hashvel;i++)
	{ 
		H->hashLista[i] = StvoriListaElementAlokacija();
		}

	return H;
}

int DodajUTablicu(char* drzava, char* datoteka_drzava, hash H)
{
	int index = 0;
	index = HashFun(drzava);

	UnesiSortirano(H->hashLista[index], drzava, datoteka_drzava);

	return 0;
}

int HashFun(char* drzava)
{
	int duljina = 0, pom = 0, sum = 0, i = 0;
	duljina = strlen(drzava);

	for (i = 0; i < duljina || i < 5; i++)
		sum += drzava[i];

	pom = sum % hashvel;

	return pom;
}
listaposition StvoriListaElementAlokacija()
{
	listaposition p = NULL;
	p = (listaposition)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Nemoguće alocirati memoriju!\n");
		return NULL;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;

	return p;
}


listaposition StvoriListaElement(listaposition p)
{
	p = (listaposition)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Nemoguće alocirati memoriju!");
		return -3;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;
}

int ProcitajDatDrzava(hash HTab, char* dat)
{
	FILE* file = NULL;
	char ime_drzave[MAX] = { 0 }, datoteka_drzava[MAX] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Ne moze se otvoriti datoteka!");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", ime_drzave, datoteka_drzava);
		DodajUTablicu(ime_drzave, datoteka_drzava, HTab);
	}

	fclose(file);
	return 0;
}
int UnesiSortirano(listaposition p, char* ime_drzave, char* datoteka_drzava)
{
	listaposition q = NULL;
	char pom[MAX] = { 0 };

	q = (listaposition)malloc(sizeof(lista));
	if (q == NULL)
	{
		printf("Nemoguće alocirati memoriju!");
		return -2;
	}


	strcpy(q->drzava, ime_drzave);
	q->stablo = NULL;
	q->stablo = ProcitajDatGradovi(q->stablo, datoteka_drzava);
	strcpy(pom, ime_drzave);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(pom, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}
	return 0;
}
stabloposition ProcitajDatGradovi(stabloposition root, char* datoteka_drzava)
{
	FILE* file = NULL;
	char grad[MAX] = { 0 };
	int brGradana = 0;

	file = fopen(datoteka_drzava, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", grad, &brGradana);
		root = StvoriStablo(root, grad, brGradana);
	}
	fclose(file);
	return root;
}
stabloposition StvoriStablo(stabloposition S, char* grad, int brGradana)
{
	if (S == NULL)
	{
		S = (stabloposition)malloc(sizeof(stablo));
		if (S == NULL)
		{
			printf("Nemoguće alocirati memoriju!");
			return NULL;
		}
		strcpy(S->grad, grad);
		S->brGradana = brGradana;
		S->lijevo = NULL;
		S->desno = NULL;
	}
	else if (brGradana == S->brGradana)
	{
		if (strcmp(grad, S->grad) < 0)
			S->lijevo = StvoriStablo(S->lijevo, grad, brGradana);
		else if (strcmp(grad, S->grad) > 0)
			S->desno = StvoriStablo(S->desno, grad, brGradana);
	}
	else
	{
		if (brGradana < S->brGradana)
			S->lijevo = StvoriStablo(S->lijevo, grad, brGradana);
		else if (brGradana > S->brGradana)
			S->desno = StvoriStablo(S->desno, grad, brGradana);
	}
	return S;
}
int Ispisi(listaposition p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		InOrder(p->stablo);
		p = p->next;
	}
	return 0;
}
int InOrder(stabloposition S)
{
	if (S == NULL)
		return 0;

	InOrder(S->lijevo);
	printf(" %s-%d ", S->grad, S->brGradana);
	InOrder(S->desno);

	return 0;
}
listaposition PronadiDrzavu(hash HTab, char* drzava)
{
	int index = 0;
	index = HashFun(drzava);
	listaposition p = HTab->hashLista[index];

	while (p->next != NULL)
	{
		if (strcmp(drzava, p->next->drzava) == 0)
			return p->next;
		else
			p = p->next;
	}
	return NULL;
}

int InOrderPrintBiggerThan(stabloposition p, int number)
{
	if (p == NULL)
		return 0;

	InOrderPrintBiggerThan(p->lijevo, number);

	if (number < p->brGradana)
		printf("%s %d\n", p->grad, p->brGradana);

	InOrderPrintBiggerThan(p->desno, number);

	return 0;
}
