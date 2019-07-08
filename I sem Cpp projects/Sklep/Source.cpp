#include <iostream>
#include <fstream>
#include "Funkcje.h"

#include <stdlib.h>	//sprawdzanie wyciekow pamieci
#include <crtdbg.h>
#define _DEBUG 
#define _CRTDBG_MAP_ALLOC

using namespace std;

int main(const int argc, char **argv)
{
	
	string plikProduktyNazwa, plikZakupyNazwa, plikRaportNazwa, plikRachunekNazwa, nazwaProduktuDoUsuniecia = "";

	
	if (!sprawdzanie_argumentow(argc, argv, plikProduktyNazwa, plikZakupyNazwa, plikRaportNazwa, plikRachunekNazwa, nazwaProduktuDoUsuniecia))
	{
		cout << "Nie udalo sie poprawnie odczytac argumentow." << endl << endl;
		return 0;
	}
	
	ifstream plikListaZakupow;
	plikListaZakupow.open(plikZakupyNazwa);
	if (plikListaZakupow.is_open() && plikListaZakupow.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z lista zakupow: " << plikZakupyNazwa << endl;
		return 0;
	}
	ofstream plikRachunek;
	plikRachunek.open(plikRachunekNazwa);
	if (plikRachunek.is_open() && plikRachunek.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z rachunkiem: " << plikRachunekNazwa << endl;
		return 0;
	}
	ofstream plikRaport;
	plikRaport.open(plikRaportNazwa);
	if (plikRaport.is_open() && plikRaport.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z rachunkiem: " << plikRachunekNazwa << endl;
		return 0;
	}

	produkt *pHead = nullptr;

	dodajProdukty(pHead, plikProduktyNazwa);

	produkt *tmp = pHead;
	zakupy(tmp, plikListaZakupow, plikRachunek, plikRaport, nazwaProduktuDoUsuniecia);

	usunListe(pHead);
	cout << "Program wykonany pomyslnie - sprawdz wyniki!" << endl;
	_CrtDumpMemoryLeaks();	//detekcja wyciekow pamieci
	return 0;
}