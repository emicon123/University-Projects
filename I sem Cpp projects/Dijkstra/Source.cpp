#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <regex>

#include <stdlib.h>	//sprawdzanie wyciekow pamieci
#include <crtdbg.h>
#define _DEBUG 
#define _CRTDBG_MAP_ALLOC
const double NIESKONCZONOSC = std::numeric_limits<double>::max();
using namespace std;


struct droga;

struct miasto
{
	string nazwa;
	droga * pDrogi; // glowa listy drog z tego miasta
	double dbMinimalnaOdleglosc;
	miasto * pPoprzednik; // poprzednie miasto w najkrotszej trasie
	bool bPrzeanalizowane; // jezeli true, to znaczy ze znamy minimalna odleglosc dla tego miasta
						   //--------------
	miasto * pNext; // nastepne miasto w liscie miast
};

struct droga
{
	double dlugosc; // dlugosc drogi :-)
	miasto * pDokad; // miasto docelowe
					 //--------------   
	droga * pNext; // nastepna droga z miasta 
};
void buduj_graf(miasto * & pHead, const string & poczatkowe, const string & koncowe, double odleglosc);
miasto *znajdz_adres_miasta_poczatkowego(miasto *&pMiasto, const string &poczatkowe);
miasto *znajdz_adres_miasta_koncowego(miasto *&pMiasto, const string &koncowe);
void dodaj_droge(miasto *&pMiastoP, miasto *&pMiastoK, double odleglosc);
void wypisz_trase(miasto *&pHead, miasto *&poczatek, ofstream &plikWyznacz);

void buduj_graf(miasto * & pHead, const string & poczatkowe, const string & koncowe, double odleglosc)
{
	miasto *pom = pHead;
	if (!pHead)
	{

		pHead = new miasto{ poczatkowe, 0, NIESKONCZONOSC, 0, false, 0 };		// jesli nie ma glowy to dodajemy miasto poczatkowe i koncowe
		pHead->pNext = new miasto{ koncowe, 0, NIESKONCZONOSC, 0, false, 0 };
		pHead->pDrogi = new droga{ odleglosc, pHead->pNext, 0 };				// laczymy je droga

	}
	else
	{
		miasto *pMP = znajdz_adres_miasta_poczatkowego(pom, poczatkowe);		// jesli glowa istnieje znajdujemy adres maista poczatkowego i koncowego
		pom = pHead;																		// jesli miast jeszcze nie ma funkcja znajdz_adres utworzy miasta
		miasto *pMK = znajdz_adres_miasta_koncowego(pom, koncowe);
		dodaj_droge(pMP, pMK, odleglosc);										// dodajemy droge
	}

}
miasto *znajdz_adres_miasta_poczatkowego(miasto *&pMiasto, const string &poczatkowe)
{
	while (pMiasto)
	{
		if (pMiasto->nazwa == poczatkowe)
		{
			return pMiasto;
		}
		else
		{
			if (!pMiasto->pNext)
			{
				pMiasto->pNext = new miasto{ poczatkowe, 0, NIESKONCZONOSC, 0, false, 0 };
				return pMiasto->pNext;
			}
		}
		pMiasto = pMiasto->pNext;
	}
}
miasto *znajdz_adres_miasta_koncowego(miasto *&pMiasto, const string &koncowe)
{
	while (pMiasto)
	{
		if (pMiasto->nazwa == koncowe)
		{
			return pMiasto;
		}
		else
		{
			if (!pMiasto->pNext)
			{
				pMiasto->pNext = new miasto{ koncowe, 0, NIESKONCZONOSC, 0, false, 0 };
				return pMiasto->pNext;
			}
		}
		pMiasto = pMiasto->pNext;
	}
}
void dodaj_droge(miasto *&pMiastoP, miasto *&pMiastoK, double odleglosc)
{
	droga *pom = pMiastoP->pDrogi;
	if (!pMiastoP->pDrogi)
	{
		pMiastoP->pDrogi = new droga{ odleglosc, pMiastoK, 0 };
	}
	else
	{
		while (pom)
		{
			if (!pom->pNext)
			{
				pom->pNext = new droga{ odleglosc, pMiastoK, 0 };
				break;
			}
			pom = pom->pNext;
		}
	}
}



bool dijkstra(miasto *& pMiasto, const string &poczatkowe, const string koncowe, ofstream &plikWyznacz)
{

	miasto *pom = pMiasto;

	miasto *pMP = znajdz_adres_miasta_poczatkowego(pMiasto, poczatkowe);	// znajdujemy adres miasta poczatkowego (jest ono od razu miastem poprzednim
	miasto *przekazPoczatek = pMP;										// dodatkowa zmienna zawsze przyjmuje adres miasta poczatkowego
	pMP->dbMinimalnaOdleglosc = 0;
	pMP->bPrzeanalizowane = true;
	pMiasto = pom;

	miasto *pMK = znajdz_adres_miasta_koncowego(pMiasto, koncowe);		// znajdujemy adres miasta koncowego
	pMiasto = pom;
	if (!pMP->pDrogi)													// jesli nie ma drog to na pewno nie da sie odnalezc trasy
	{
		plikWyznacz << "Nie udalo sie wyznaczyc trasy." << endl;
		plikWyznacz << "Miasto poczatkowe nie jest polaczone z zadnym innym miastem." << endl;
		plikWyznacz << endl;
		return false;
	}


	miasto *p = pMiasto;
	miasto *najblizsze = 0;

	while (pMiasto)
	{

		double min = NIESKONCZONOSC;

		if (pMiasto == pMP)
		{



			if (pMP->pDrogi)
			{
				droga *pD = pMP->pDrogi;
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


				wypisz_trase(najblizsze, przekazPoczatek, plikWyznacz);
				pMiasto = pom;
				while (pMiasto)	// przygotowanie do wyznaczenia kolejnej trasy
				{

					/*if (pHead->pPoprzednik != 0)
					{
						miasto *poprzednik = pHead->pPoprzednik;
						pHead->pPoprzednik = 0;
						delete poprzednik;
					}*/
					pMiasto->bPrzeanalizowane = false;
					pMiasto->dbMinimalnaOdleglosc = NIESKONCZONOSC;
					pMiasto->pPoprzednik = 0;
					pMiasto = pMiasto->pNext;
				}
				pMiasto = pom;
				return true;
			}


			pMP = najblizsze;
			if (pMP == pMiasto && pMP != pom)		// jesli dane miasto nie ma polaczen, a Minimalna Odleglosc reszty miast jest rowna nieskonczonosci
			{									// to nie mozliwe jest wyznaczenie trasy
				break;
			}
			pMiasto = pom;
			if (pMP == pom)						// while() przesuwa glowe, wiec jesli najblizszym miastem jest pierwsze miasto w liscie
			{									// to nie mozna przesunac glowy, poniewaz, najblizsze miasto nie zostanie znalezione
				continue;
			}
		}


		pMiasto = pMiasto->pNext;
	}
	pMiasto = pom;

	while (pMiasto)	// przygotowanie do wyznaczenia kolejnej trasy
	{

		pMiasto->bPrzeanalizowane = false;
		pMiasto->dbMinimalnaOdleglosc = NIESKONCZONOSC;
		pMiasto->pPoprzednik = 0;
		pMiasto = pMiasto->pNext;
	}
	pMiasto = pom;

	if (najblizsze != pMK)		// jesli po analizie miasto z najmniejsza odlegloscia minimalna nie jest miastem koncowym to nie znalezlismy trasy
	{
		plikWyznacz << "Trasa niemozliwa do wyznaczenia" << endl;
		plikWyznacz << endl;
		return false;
	}
}

void wypisz_trase(miasto *&pMiasto, miasto *&pMiastoPoczatkowe, ofstream &plikWyznacz)
{
	miasto *p = pMiasto;
	miasto *pom = 0;



	plikWyznacz << "Trasa: " << pMiastoPoczatkowe->nazwa << " ---> " << p->nazwa << " (" << p->dbMinimalnaOdleglosc << " km):" << endl << endl;
	while (p && p->pPoprzednik != pMiastoPoczatkowe)
	{
		if (p->pPoprzednik && p->pPoprzednik != pMiastoPoczatkowe)		// odzyskujemy poprzednikow w trasie
		{
			pom = p->pPoprzednik;
			plikWyznacz << pom->nazwa << " " << pom->dbMinimalnaOdleglosc << " km" << endl;

		}
		p = pom;
	}

	plikWyznacz << endl;
}

void usun(miasto *&pHead)
{
	while (pHead)
	{

		while (pHead->pDrogi)
		{
			droga *p = pHead->pDrogi;
			pHead->pDrogi = pHead->pDrogi->pNext;
			delete p;
		}
		miasto *p = pHead;

		pHead = pHead->pNext;
		delete p;
	}
}

void help()
{
	cout << endl << "To jest program sluzacy do wyznaczania tras poamiedzy miastami.\n"
		"Aby program zadzialal nalezy wpisac nastepujace dane:\n"
		"'-d' - przelacznik do pliku z drogami\n"
		"Po nim wpisz nazwe pliku z drogami z odpowiednim rozszerzeniem pliku.\n"
		"'-t' - przelacznik do pliku z trasami do wyznaczenia\n"
		"Po nim wpisz nazwe pliku z trasami do wyznaczenia z odpowiednim rozszerzeniem pliku.\n"
		"W plikach wejsciowych powinny znajdowac sie tylko poprawnie wpisane dane.\n"
		"<Miasto poczatkowe> <Miasto koncowe> <odleglosc> dla pliku z drogami. \n"
		"<Miasto poczatkowe> <Miasto koncowe> dla pliku z trasami do wyznaczenia. \n"
		"'-o' - przelacznik do pliku wyjsciowego.\n"
		"Po nim wpisz nazwe pliku wyjsciowego. \n";
}

bool sprawdzanie_argumentow(int argc, char **argv, string &plikDrogiNazwa, string &plikTrasyNazwa, string &plikWyznaczNazwa)
{
	if (argc > 1)
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
					plikDrogiNazwa = argv[i + 1];						// jesli zostal podany przelacznik -d to nastepnym argumentem musi byæ nazwa pliku z drogami
				}
				else if (!strcmp(argv[i], "-t"))
				{
					plikTrasyNazwa = argv[i + 1];						// jesli zostal podany przelacznik -t to nastepnym argumentem musi byæ nazwa pliku z trasami
				}
				else if (!strcmp(argv[i], "-o"))
				{
					plikWyznaczNazwa = argv[i + 1];						// jesli zostal podany przelacznik -o to nastepnym argumentem musi byæ nazwa pliku wyjsciowego
					if (plikTrasyNazwa == plikDrogiNazwa || plikWyznaczNazwa == plikDrogiNazwa || plikTrasyNazwa == plikWyznaczNazwa)
					{
						cout << "Dwa te same pliki nie moga byc podane jako rozne argumenty" << endl;
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
				cout << "Podano zbyt malo argumentow" << endl;
				return false;
			}
		}
	return true;
}

int main(int argc, char **argv)
{

	

	string plikDrogiNazwa, plikTrasyNazwa, plikWyznaczNazwa;

	if (!sprawdzanie_argumentow(argc, argv, plikDrogiNazwa, plikTrasyNazwa, plikWyznaczNazwa))
	{
		cout << "Nie udalo sie poprawnie odczytac argumentow." << endl << endl;
		return 0;

	}
	
	//_CrtDumpMemoryLeaks();
	ifstream plikDrogi;
	plikDrogi.open(plikDrogiNazwa);											// otwieranie pliku drog
	if (plikDrogi.is_open() && plikDrogi.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z drogami." << endl;
		help();
		return 0;
	}

	ifstream plikTrasy;														// otwieranie pliku tras
	plikTrasy.open(plikTrasyNazwa);
	if (plikTrasy.is_open() && plikTrasy.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z trasami." << endl;
		help();
		return 0;
	}

	ofstream plikWyznacz;													// otwieranie pliku wyjsciowego
	plikWyznacz.open(plikWyznaczNazwa);
	if (plikWyznacz.is_open() && plikWyznacz.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku wyjsciowego." << endl;
		help();
		return 0;
	}

	//_CrtDumpMemoryLeaks();

	miasto *pGlowa = 0;	
	int linia = 0;
	string miastoPoczatkowe, miastoKoncowe;
	string odleglosc;
	while (plikDrogi >> miastoPoczatkowe >> miastoKoncowe >> odleglosc)							// odczyt danych z pliku drogi
	{
		linia++;

		if (regex_match(miastoPoczatkowe, regex("[a-zA-Z]+")) &&
			regex_match(miastoKoncowe, regex("[a-zA-Z]+")) &&
			regex_match(odleglosc, regex("[0-9]+")))			// sprawdzanie poprawnosci danych
		{
			double dlugosc = stod(odleglosc);
			buduj_graf(pGlowa, miastoPoczatkowe, miastoKoncowe, dlugosc);
		}
		else
		{
			plikWyznacz << "Blad danych w pliku z drogami w lini " << linia << endl << endl;
		}
	}

	usun(pGlowa);
	linia = 0;
	_CrtDumpMemoryLeaks();
	

	miasto *pom = pGlowa;
	while (plikTrasy >> miastoPoczatkowe >> miastoKoncowe)
	{
		linia++;
		if (regex_match(miastoPoczatkowe, regex("[a-zA-Z]+")) &&
			regex_match(miastoKoncowe, regex("[a-zA-Z]+")))
		{
			dijkstra(pom, miastoPoczatkowe, miastoKoncowe, plikWyznacz);
		}
		else
		{
			plikWyznacz << "Blad danych w pliku z trasami w lini " << linia << endl << endl;
		}
	}

	
	usun(pGlowa);
	plikDrogi.close();
	plikTrasy.close();
	plikWyznacz.close();
	cout << "\nGotowe! Sprawdz wynik w pliku z wyznaczonymi trasami.\n";
	_CrtDumpMemoryLeaks();
	return 0;
}