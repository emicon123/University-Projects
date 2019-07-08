#include "Graf.h"

void buduj_graf(struct miasto ** pHead, char **plikDrogiNazwa)
{
	struct miasto *current = pHead;	//zmienna pomocnicza
	char miastoPoczatkowe[30];
	char miastoKoncowe[30];
	char odleglosc[30];

	FILE *plikDrogi = funkcja_plikD(plikDrogiNazwa); //otwieranie pliku z drogami

	while (true) //petla skanujaca plik i budujaca graf miast oraz drog
	{
		if (feof(plikDrogi) != 0)
			break;

		fscanf(plikDrogi, "%s", &miastoPoczatkowe);
		fscanf(plikDrogi, "%s", &miastoKoncowe);
		fscanf(plikDrogi, "%s", odleglosc);
		double dlugosc = atof(odleglosc);

		if (current->nazwa == NULL)	//jesli nie ma jeszcze zadnego miasta w liscie, dodajemy nowe
		{

			struct miasto * current = (struct miasto*)malloc(sizeof(miasto));
			if (current == NULL)
			{
				fprintf(stderr, "Malloc error");
			}


			current->bPrzeanalizowane = false;	//ustawiamy parametry
			current->dbMinimalnaOdleglosc = NIESKONCZONOSC;
			current->nazwa = (char*)malloc(sizeof(char) * strlen(miastoPoczatkowe) + 1);
			if (current->nazwa == NULL)
			{
				fprintf(stderr, "Malloc error");
			}
			strcpy(current->nazwa, miastoPoczatkowe);
			current->pDrogi = 0;
			current->pNext = NULL;
			current->pPoprzednik = NULL;
			*pHead = current;	//mamy pierwsze miasto w liscie miast

			current->pNext = malloc(sizeof(miasto));	//przy pierwszym "przebiegu" petli mozna od razu utworzyc drugie miasto i droge do niego
			if (current->pNext == NULL) {
				fprintf(stderr, "Malloc error");
			}
			current->pNext->bPrzeanalizowane = false;
			current->pNext->dbMinimalnaOdleglosc = NIESKONCZONOSC;
			current->pNext->nazwa = (char*)malloc(sizeof(char) * strlen(miastoKoncowe) + 1);
			if (current->pNext->nazwa == NULL)
			{
				fprintf(stderr, "Malloc error");
			}
			strcpy(current->pNext->nazwa, miastoKoncowe);
			current->pNext->pDrogi = 0;
			current->pNext->pNext = NULL;
			current->pNext->pPoprzednik = NULL;
			(*pHead)->pNext = current->pNext;	//miasto docelowe zostalo dodane do listy miast

			current->pDrogi = malloc(sizeof(struct droga));	//teraz nalezy dodac droge wskazujaca na miasto koncowe do listy drog miasta poczatkowego
			current->pDrogi->dlugosc = dlugosc;
			current->pDrogi->pDokad = current->pNext;

			current->pDrogi->nazwa = "AAAAA";

			current->pDrogi->pNext = NULL;
			(*pHead)->pDrogi = current->pDrogi;	//pierwsza droga zostala dodana
		}
		else	//przy kolejnych przejsciach petli i czytaniu danych z pliku nalezy sprawdzic czy danego miasta (poczatkowego/koncowego) nie ma juz w liscie miast 
		{

			miasto *pMP = znajdz_adres_miasta_poczatkowego(*pHead, miastoPoczatkowe);	//funkcja sprawdzajaca czy miasto poczatkowe juz istnieje na liscie (jesli nie, dodaje ona nowe miasto)
			pHead = current;
			miasto *pMK = znajdz_adres_miasta_koncowego(*pHead, miastoKoncowe);	//funkcja sprawdzajaca czy miasto koncowe juz istnieje na liscie (jesli nie, dodaje ona nowe miasto)
			pHead = current;

			dodaj_droge(&pMP, &pMK, dlugosc);	//skoro miasta zostaly znalezione/dodane mozna polaczyc je droga (z miasta poczatkowego do miasta koncowego)


		}

	}
	fclose(plikDrogi);
}

miasto *znajdz_adres_miasta_poczatkowego(struct miasto *pHead, char poczatkowe[])
{
	while (pHead)
	{
		if (strcmp(pHead->nazwa, poczatkowe) == NULL)	//jesli strcmp znajdzie miasto o tej samej nazwie, to znaczy, ze jest ono juz na liscie miast
		{
			return pHead;
		}
		else //jesli nie, nalezy dodac nowe miasto
		{
			if (pHead->pNext == NULL)
			{
				pHead->pNext = malloc(sizeof(struct miasto));
				pHead->pNext->bPrzeanalizowane = false;
				pHead->pNext->dbMinimalnaOdleglosc = NIESKONCZONOSC;
				pHead->pNext->nazwa = (char*)malloc(sizeof(char) * strlen(poczatkowe) + 1);
				if (pHead->pNext->nazwa == NULL)
				{
					fprintf(stderr, "Malloc error");
				}
				strcpy(pHead->pNext->nazwa, poczatkowe);
				pHead->pNext->pDrogi = 0;
				pHead->pNext->pNext = NULL;
				pHead->pNext->pPoprzednik = 0;
				return pHead->pNext;

			}
		}
		pHead = pHead->pNext;
	}
}

miasto *znajdz_adres_miasta_koncowego(struct miasto *pHead, char koncowe[])	//funkcja analogiczna do powyzszej
{
	while (pHead)
	{
		if (strcmp(pHead->nazwa, koncowe) == NULL)
		{
			return pHead;
		}
		else
		{
			if (!pHead->pNext)
			{
				pHead->pNext = malloc(sizeof(struct miasto));
				pHead->pNext->bPrzeanalizowane = false;
				pHead->pNext->dbMinimalnaOdleglosc = NIESKONCZONOSC;
				pHead->pNext->nazwa = (char*)malloc(sizeof(char) * strlen(koncowe) + 1);
				if (pHead->pNext->nazwa == NULL)
				{
					fprintf(stderr, "Malloc error");
				}
				strcpy(pHead->pNext->nazwa, koncowe);
				pHead->pNext->pDrogi = 0;
				pHead->pNext->pNext = NULL;
				pHead->pNext->pPoprzednik = 0;
				return pHead->pNext;
			}
		}
		pHead = pHead->pNext;
	}
}

void dodaj_droge(struct miasto **pHeadMP, struct miasto **pHeadMK, double odleglosc)
{
	//droga *current = calloc(1, sizeof(*current));
	//current = (*pHeadMP)->pDrogi;
	struct droga *current = (*pHeadMP)->pDrogi;

	if (current == NULL)	//jesli w liscie drog z miasta poczatkowego nie ma jeszcze drogi nalezy dodac nowa
	{
		current = malloc(sizeof(droga));
		current->dlugosc = odleglosc;
		current->pDokad = *pHeadMK;

		current->nazwa = "AAAAA";

		current->pNext = NULL;
		(*pHeadMP)->pDrogi = current;
	}
	else	//w innym przypadku szukamy konca listy drog i dodajemy nowa
	{
		while (current)
		{
			if (current->pNext == NULL)
			{
				current->pNext = malloc(sizeof(droga));
				current->pNext->dlugosc = odleglosc;
				current->pNext->pDokad = *pHeadMK;

				current->nazwa = "AAAAAA";

				current->pNext->pNext = NULL;
				break;
			}
			current = current->pNext;
		}

	}
}