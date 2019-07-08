#include "Pliki.h"

FILE *funkcja_plikT(char **plikTrasyNazwa)
{
	FILE *plikTrasy;		//otwieramy plik z zapisanymi trasami
	plikTrasy = fopen(plikTrasyNazwa, "r");
	if (plikTrasy==NULL)
	{
		printf_s("Blad otwierania pliku z trasasmi.\n");
		return 0;
	}
	return plikTrasy;
}

FILE *funkcja_plikW(char **plikWyznaczNazwa)
{
	FILE *plikWyznacz;	//otwieramy plik z w ktorym zapisane beda wyznaczone trasy
	plikWyznacz = fopen(plikWyznaczNazwa, "w");
	if (plikWyznacz==NULL)
	{
		printf_s("Blad otwierania pliku z trasasmi do wyznaczenia.\n");
		return 0;
	}
	return plikWyznacz;
}

FILE *funkcja_plikD(char **plikDrogiNazwa)
{
	FILE *plikDrogi;	//otwieramy plik z drogami
	plikDrogi = fopen(*plikDrogiNazwa, "r");
	if (plikDrogi == NULL)
	{
		printf_s("Blad otwierania pliku z drogami.\n");
		exit(1);
	}
	return plikDrogi;
}