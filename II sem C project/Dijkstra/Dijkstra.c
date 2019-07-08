#include "Dijkstra.h"

bool dijkstra(struct miasto ** pHead, FILE * plikWyznacz, char poczatkowe[], char koncowe[])
{
	struct miasto *pom = *pHead;

	miasto *pMP = znajdz_adres_miasta_poczatkowego(*pHead, poczatkowe);	// znajdujemy adres miasta poczatkowego (jest ono od razu miastem poprzednim
	struct miasto *przekazPoczatek = pMP;	// dodatkowa zmienna zawsze przyjmuje adres miasta poczatkowego
	pMP->dbMinimalnaOdleglosc = 0;
	pMP->bPrzeanalizowane = true;
	*pHead = pom;

	miasto *pMK = znajdz_adres_miasta_koncowego(*pHead, koncowe);		// znajdujemy adres miasta koncowego
	*pHead = pom;
	if (!pMP->pDrogi)													// jesli nie ma drog to na pewno nie da sie odnalezc trasy
	{
		fprintf(plikWyznacz, "Nie udalo sie wyznaczyc trasy.\n");
		fprintf(plikWyznacz, "Miasto poczatkowe nie jest polaczone z zadnym innym miastem.\n\n");
		return false;
	}

	struct miasto *p = *pHead;

	struct miasto *najblizsze = 0;
	while (*pHead)
	{

		double min = NIESKONCZONOSC;

		if (*pHead == pMP)
		{



			if (pMP->pDrogi)
			{
				struct droga *pD = pMP->pDrogi;

				while (pMP->pDrogi)		//dopoki miasto posiada drogi
				{

					if (pMP->pDrogi->pDokad->bPrzeanalizowane == false)
					{
						double minimalnaOdl = pMP->pDrogi->pDokad->dbMinimalnaOdleglosc;

						if (minimalnaOdl >= pMP->pDrogi->dlugosc + pMP->dbMinimalnaOdleglosc)		// przypisujemy miasta poprzednika i najmniejsza dotychczas znana Minimalna Odleglosc
						{
							minimalnaOdl = pMP->pDrogi->dlugosc + pMP->dbMinimalnaOdleglosc;
							pMP->pDrogi->pDokad->dbMinimalnaOdleglosc = minimalnaOdl;
							pMP->pDrogi->pDokad->pPoprzednik = pMP;
						}
					}
					pMP->pDrogi = pMP->pDrogi->pNext;
				}	// najblizszym miastom zostaly przypisane wartosci
				pMP->pDrogi = pD;
			}
			else
			{
				pMP->bPrzeanalizowane = true;		// jesli miasto nie ma drog, to jest przeanalizowane

			}

			while (p)														// dopoki glowa to szukamy miasta o najmniejszej Minimalnej Odleglosci
			{

				if (p->dbMinimalnaOdleglosc < min && p->bPrzeanalizowane == false)
				{
					if (p != pMP)	// to miasto nie moze byc aktualnie analizowanym miastem
					{
						min = p->dbMinimalnaOdleglosc;
						najblizsze = p;
					}
					else
					{
						return false;
					}

				}
				p = p->pNext;
			}																//	zostalo znalezione najblizsze miasto
			p = pom;

			najblizsze->bPrzeanalizowane = true;


			if (najblizsze == pMK)		// jesli najblize jest rowne koncowemu dijkstra sie konczy
			{


				wypisz_trase(&najblizsze, &przekazPoczatek, plikWyznacz);
				*pHead = pom;
				while (*pHead)	// przygotowanie do wyznaczenia kolejnej trasy
				{

					(*pHead)->bPrzeanalizowane = false;
					(*pHead)->dbMinimalnaOdleglosc = NIESKONCZONOSC;
					(*pHead)->pPoprzednik = 0;
					(*pHead) = (*pHead)->pNext;
				}
				*pHead = pom;
				return true;
			}


			pMP = najblizsze;
			if (pMP == *pHead && pMP != pom)		// jesli dane miasto nie ma polaczen, a Minimalna Odleglosc reszty miast jest rowna nieskonczonosci
			{									// to nie mozliwe jest wyznaczenie trasy
				break;
			}
			*pHead = pom;
			if (pMP == pom)						// while() przesuwa glowe, wiec jesli najblizszym miastem jest pierwsze miasto w liscie
			{									// to nie mozna przesunac glowy, poniewaz, najblizsze miasto nie zostanie znalezione
				continue;
			}
		}


		*pHead = (*pHead)->pNext;
	}
	*pHead = pom;

	while (*pHead)	// przygotowanie do wyznaczenia kolejnej trasy
	{

		(*pHead)->bPrzeanalizowane = false;
		(*pHead)->dbMinimalnaOdleglosc = NIESKONCZONOSC;
		(*pHead)->pPoprzednik = 0;
		(*pHead) = (*pHead)->pNext;
	}
	*pHead = pom;

	if (najblizsze != pMK)		// jesli po analizie miasto z najmniejsza odlegloscia minimalna nie jest miastem koncowym to nie znalezlismy trasy
	{
		fprintf(plikWyznacz, "Trasa niemozliwa do wyznaczenia.\n\n");
		return false;
	}
}

void wypisz_trase(miasto **pHead, miasto **poczatek, FILE * plikWyznacz)
{
	//miasto *p = calloc(1, sizeof(*p));
	//p = *pHead;
	//miasto *pom = calloc(1, sizeof(*pom));
	//pom = 0;
	struct miasto *p = *pHead;
	struct miasto*pom = 0;
	fprintf(plikWyznacz, "Trasa z: %s do %s wynosi w sumie %f km.\n", (*poczatek)->nazwa, p->nazwa, p->dbMinimalnaOdleglosc);

	while (*pHead && (*pHead)->pPoprzednik != *poczatek)
	{
		if ((*pHead)->pPoprzednik && (*pHead)->pPoprzednik != *poczatek)	//odzyskujemy poprzednikow w trasie
		{
			pom = (*pHead)->pPoprzednik;
			fprintf(plikWyznacz, "Przez ");
			fprintf(plikWyznacz, "%s", pom->nazwa);
			fprintf(plikWyznacz, " ");
			fprintf(plikWyznacz, "%f", pom->dbMinimalnaOdleglosc);
			fprintf(plikWyznacz, " km");
			fprintf(plikWyznacz, "\n");
		}
		*pHead = pom;
	}
	*pHead = p;
	fprintf(plikWyznacz, "\n");
	
}