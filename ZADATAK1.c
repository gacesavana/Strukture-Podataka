#include<stdio.h>
#include<stdlib.h>
#define VELICINA 128
#define MAX_LINE 1024
#define MAX_BOD 100

typedef struct {
	char IME[VELICINA];
	char PREZIME[VELICINA];
	int bodovi;
}student;

int  BrojStudenataUnutarDatoteke(char* datoteka);
student* AlocirajMemorijuProcitajStudente(int brojStudenata, char* datoteka);
double MaksimalanBrojBodova(student* studenti, int brojStudenata);
void IspisStudenata(int brojStudenata, student* studenti,double max);


int main()
{
	int brojStudenata = 0;
	student* studenti;
	int max=0;
	char izabranadatoteka[VELICINA];
	char* datoteka = NULL;


	printf("Upišite koju datoteku želite otvoriti: ");
	scanf("%s",izabranadatoteka);

	datoteka = izabranadatoteka;

	brojStudenata=BrojStudenataUnutarDatoteke(datoteka);

	if (brojStudenata == 0)
	{
		printf("U datoteci nema upisanih studenata.");
		return -1;
	}

	studenti=AlocirajMemorijuProcitajStudente(brojStudenata,datoteka);
	max=MaksimalanBrojBodova(studenti, brojStudenata);
	IspisStudenata(brojStudenata, studenti,max);

	return 0;

}
int  BrojStudenataUnutarDatoteke(char* datoteka)
{
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (!fp) {
		printf("Datoteka ne postoji");
		return -1;
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);
		brojac++;
	}

	fclose(fp);
	return brojac;

}

student* AlocirajMemorijuProcitajStudente(int brojStudenata, char*datoteka)
{
	int brojac = 0;
	FILE* fp = NULL;
	student* studenti;

	studenti = (student*)malloc(brojStudenata*sizeof(student));
	fp = fopen(datoteka, "r");
	if (!fp)
	{
		printf("Neuspjesna alokacija memorije\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(" %s %s %lf", studenti[brojac].IME, studenti[brojac].PREZIME,  &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(fp);
	return studenti;
}

double maksimalanbrojbodova(student* studenti, int brojStudenata)
{
	int i=0;
	double max = 0;
	max = studenti[0].bodovi;

	for (i = 0;i < brojStudenata;i++)
	{
		if (studenti[i].bodovi > max)
		{
			max = studenti[i].bodovi;
		}
	}

	return max;
}

void IspisStudenata(int brojStudenata, student* studenti,double max)
{
	int i = 0;
	for (i = 0;i < brojStudenata;i++)
	{
		float relativanbrojbod = studenti[i].bodovi / max * 100;
		printf(" ime: %s prezime: %s bodovi(apsolutni): %lf bodovi(relativni): %lf\n", studenti[i].IME, studenti[i].PREZIME, studenti[i].bodovi / MAX_BOD* 100, relativanbrojbod);
		relativanbrojbod = 0;
	}
}