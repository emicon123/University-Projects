#include "Interfejs.h"



void help()
{
	printf("\n");
	printf("To jest program sluzacy do wyznaczania tras poamiedzy miastami.\n");
	printf("Aby program zadzialal nalezy wpisac nastepujace dane:\n");
	printf("'-d' - przelacznik do pliku z drogami\n");
	printf("Po nim wpisz sciezke do pliku z odpowiednim rozszerzeniem pliku. \n");
	printf("Np. D:/Dane/Program/plikDrogi.txt \n");
	printf("'-t' - przelacznik do pliku z trasami do wyznaczenia\n");
	printf("Po nim wpisz sciezke do pliku z trasami z odpowiednim rozszerzeniem pliku.\n");
	printf("Np. D:/Dane/Program/plikTrasy.txt \n");
	printf("W plikach wejsciowych powinny znajdowac sie tylko poprawnie wpisane dane.\n");
	printf("<Miasto poczatkowe> <Miasto koncowe> <odleglosc> dla pliku z drogami. \n");
	printf("<Miasto poczatkowe> <Miasto koncowe> dla pliku z trasami do wyznaczenia. \n");
	printf("'-o' - przelacznik do pliku wyjsciowego.\n");
	printf("Po nim wpisz sciezke do pliku wyjsciowego. \n");
	printf("Np. D:/Dane/Program/plikWyznacz.txt \n");
}

bool sprawdzanie_argumentow(int argc, char **argv, char **plikDrogiNazwa, char **plikTrasyNazwa, char **plikWyznaczNazwa)
{
	if (argc>1)
		if (!strcmp(argv[1], "-h"))										// jesli zostal podany przelacznik -h to wyswietl pomoc i przerwij program
		{
			help();
			return 0;
		}
		else {
			for (int i = 0; i < argc; i++)								// petla dodajaca argumenty wpisane w konsoli
			{
				if (!strcmp(argv[i], "-d"))
				{
					*plikDrogiNazwa = argv[i + 1];						// jesli zostal podany przelacznik -d to nastepnym argumentem musi byæ nazwa pliku z drogami
				}
				else if (!strcmp(argv[i], "-t"))
				{
					*plikTrasyNazwa = argv[i + 1];						// jesli zostal podany przelacznik -t to nastepnym argumentem musi byæ nazwa pliku z trasami
				}
				else if (!strcmp(argv[i], "-o"))
				{
					*plikWyznaczNazwa = argv[i + 1];						// jesli zostal podany przelacznik -o to nastepnym argumentem musi byæ nazwa pliku wyjsciowego
					if (plikTrasyNazwa == plikDrogiNazwa || plikWyznaczNazwa == plikDrogiNazwa || plikTrasyNazwa == plikWyznaczNazwa)
					{
						printf("Dwa te same pliki nie moga byc podane jako rozne argumenty\n");
						help();
						return false;
					}

					else if (!strcmp(argv[i], "-h"))					// jesli zostal podany przelacznik -h to wyswietl pomoc i przerwij program
					{
						help();
						return 0;
					}
				}

			}
			if (argc < 6)
			{
				printf("Podano zbyt malo argumentow\n");
				return false;
			}
		}
		return true;
}