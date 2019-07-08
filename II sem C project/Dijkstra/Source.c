#include "Source.h"
#define _DEBUG 
#define _CRTDBG_MAP_ALLOC 
void usun(struct miasto **pHead);
//void wypisz(struct miasto **pHead);



int main(int argc, char*argv)
{
	
	char *plikDrogiNazwa;
	char *plikTrasyNazwa;
	char *plikWyznaczNazwa;

	if (sprawdzanie_argumentow(argc, argv, &plikDrogiNazwa, &plikTrasyNazwa, &plikWyznaczNazwa)==false) //funckja odpowiadajaca za sprawdzanie poprawnosci wpisywania przelacznikow w konsoli CMD
	{
		printf("Nie udalo sie poprawnie odczytac argumentow.\n");
		return 0;
	}

	
	struct miasto *pGlowa = NULL;	 // inicjalizacja glowy listy miast
	buduj_graf(&pGlowa, &plikDrogiNazwa);	//funckja budujaca liste (miast) list (i dolaczonych do nich drog)
	//wypisz(&pGlowa);

	FILE *plikTrasy = funkcja_plikT(plikTrasyNazwa);	//funckja otwierajaca plik z trasami
	FILE *plikWyznacz = funkcja_plikW(plikWyznaczNazwa);	//funkcja otwierajaca plik z trasami do wyznaczenia

	char poczatkowe[30];
	char koncowe[30];

	while (true)
	{
		if (feof(plikTrasy) != 0)	//Algorytm Dijkstry wykona sie tyle razy ile jest podanych linijek w pliku z trasami
			break;
		fscanf(plikTrasy, "%s", &poczatkowe);
		fscanf(plikTrasy, "%s", &koncowe);

		dijkstra(&pGlowa, plikWyznacz, poczatkowe, koncowe);	//algorytm Dijkstry
	}

	
	usun(&pGlowa);	//usuwanie listy list
	printf("\nGotowe! Sprawdz wynik w pliku z wyznaczonymi trasami.\n");
	fclose(plikTrasy);
	fclose(plikWyznacz);
	_CrtDumpMemoryLeaks();
	return 0;
}

void usun(struct miasto **pHead)
{
	struct droga * droga = (*pHead)->pDrogi;
	struct droga * drogaNext;
	struct miasto * miasto = *pHead;
	struct miasto * miastoNext;
	while (miasto != NULL)
	{

		while (droga != NULL)
		{

			drogaNext = droga->pNext;

			free(droga);
			droga = drogaNext;
		}

		miastoNext = miasto->pNext;
		free(miasto);

		miasto = miastoNext;
	}
	*pHead = NULL;
}

//void wypisz(struct miasto **pHead)
//{
//	struct miasto *pom = *pHead;
//	struct droga *p = (*pHead)->pDrogi;
//	while (*pHead)
//	{
//		printf("%s\n", (*pHead)->nazwa);
//		while ((*pHead)->pDrogi)
//		{
//			printf("%s ",(*pHead)->pDrogi->pDokad->nazwa);
//			(*pHead)->pDrogi = (*pHead)->pDrogi->pNext;
//		}
//		printf("\n");
//		*pHead = (*pHead)->pNext;
//	}
//	*pHead = pom;	
//}