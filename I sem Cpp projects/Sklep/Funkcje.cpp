#include <iostream>
#include <string>
#include <fstream>
#include "Funkcje.h"
using namespace std;

bool sprawdzanie_argumentow(int argc, char **argv, string &plikProduktyNazwa, string &plikZakupyNazwa, string &plikRaportNazwa, 
	string &plikRachunekNazwa, string &nazwaProduktuDoUsuniecia)
{
	bool bledneDane = 0;

	if (argc > 1)
	{
		for (int i = 0; i < argc - 1; i++)								// petla dodajaca argumenty wpisane w konsoli
		{
			if (!strcmp(argv[i], "-p"))
			{
				if (i == argc - 1)									//Jezeli przelacznik jest na ostatnim miejscu tablicy, bledneDane przyjmuja wartosc "true" gdyz przelacznik nie ma przypisanej wartosci
					bledneDane = true;
				else if (argv[i + 1] == "" || i == argc)
					bledneDane = true;								//Je¿eli wartoœæ po prze³¹czniku "-i" jest pusta, bledneDane przyjmie wartosc "true"
				else
					plikProduktyNazwa = argv[i + 1];				//W innym wypadku, wartoœæ po prze³¹czniku jest wpisywana do odpowiedniej zmiennej
			}
			else if (!strcmp(argv[i], "-z"))
			{
				if (i == argc - 1)									//Jezeli przelacznik jest na ostatnim miejscu tablicy, bledneDane przyjmuja wartosc "true" gdyz przelacznik nie ma przypisanej wartosci
					bledneDane = true;
				else if (argv[i + 1] == "" || i == argc)
					bledneDane = true;								//Je¿eli wartoœæ po prze³¹czniku "-i" jest pusta, bledneDane przyjmie wartosc "true"
				else
					plikZakupyNazwa = argv[i + 1];				//W innym wypadku, wartoœæ po prze³¹czniku jest wpisywana do odpowiedniej zmiennej
			}
			else if (!strcmp(argv[i], "-rZ"))
			{
				if (i == argc - 1)									//Jezeli przelacznik jest na ostatnim miejscu tablicy, bledneDane przyjmuja wartosc "true" gdyz przelacznik nie ma przypisanej wartosci
					bledneDane = true;
				else if (argv[i + 1] == "" || i == argc)
					bledneDane = true;								//Je¿eli wartoœæ po prze³¹czniku "-i" jest pusta, bledneDane przyjmie wartosc "true"
				else
					plikRaportNazwa = argv[i + 1];				//W innym wypadku, wartoœæ po prze³¹czniku jest wpisywana do odpowiedniej zmiennej
			}
			else if (!strcmp(argv[i], "-r"))
			{
				if (i == argc - 1)									//Jezeli przelacznik jest na ostatnim miejscu tablicy, bledneDane przyjmuja wartosc "true" gdyz przelacznik nie ma przypisanej wartosci
					bledneDane = true;
				else if (argv[i + 1] == "" || i == argc)
					bledneDane = true;								//Je¿eli wartoœæ po prze³¹czniku "-i" jest pusta, bledneDane przyjmie wartosc "true"
				else
					plikRachunekNazwa = argv[i + 1];				//W innym wypadku, wartoœæ po prze³¹czniku jest wpisywana do odpowiedniej zmiennej
			}
			else if (!strcmp(argv[i], "-ui"))
			{
				if (i == argc - 1)									//Jezeli przelacznik jest na ostatnim miejscu tablicy, bledneDane przyjmuja wartosc "true" gdyz przelacznik nie ma przypisanej wartosci
					bledneDane = true;
				else if (argv[i + 1] == "" || i == argc)
					bledneDane = true;								//Je¿eli wartoœæ po prze³¹czniku "-i" jest pusta, bledneDane przyjmie wartosc "true"
				else
					nazwaProduktuDoUsuniecia = argv[i + 1];				//W innym wypadku, wartoœæ po prze³¹czniku jest wpisywana do odpowiedniej zmiennej
			}			
		}
		if (plikZakupyNazwa == plikProduktyNazwa)
		{
			cout << "Plik z produktami nie moze byc tym samym plikiem co plik z lista zakupow" << endl;
			return false;
		}
	}

	if (argc < 9)
	{
		cout << "Podano zbyt malo argumentow" << endl;
		return false;
	}

	if (bledneDane)
	{
		cout << "Bledne dane!" << endl;
	}
	return true;
}


void dodajProdukty(produkt *&pHead, const string &plikProduktyNazwa)
{
	ifstream plikProdukty;
	plikProdukty.open(plikProduktyNazwa);
	if (plikProdukty.is_open() && plikProdukty.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku z produktami: " << plikProduktyNazwa << endl;
		return;
	}
	produkt *tmp = pHead;
	string nazwaProduktu;
	int liczbaProduktow;
	float cena;

	while (plikProdukty >> nazwaProduktu >> liczbaProduktow >> cena)
	{
		budujListe(pHead, nazwaProduktu, liczbaProduktow, cena);		
	}

	plikProdukty.close();
}

void budujListe(produkt *&pHead, const string &nazwa, const int &liczba, const float &cena)
{
	produkt *tmp = pHead;
	if (!pHead)
	{
		pHead = new produkt{ nazwa, liczba, cena, nullptr };
	}
	else
	{
		dodajProdukt(tmp, nazwa, liczba, cena);
	}
}

void dodajProdukt(produkt *& pHead, const string &nazwa, const int &liczba, const float &cena)
{
	//jesli nie ma jeszcze zadnego produktu w liscie, to go dodajemy
	if (!pHead)
	{
		pHead = new produkt{ nazwa, liczba, cena, nullptr};
	}
	else
	{
		dodajProdukt(pHead->pNext, nazwa, liczba, cena);	
	}
}


void zakupy(produkt *&pHead, ifstream &plikListaZakupow, ofstream &plikRachunek, ofstream &plikRaport, const string nazwaProduktuDoUsuniecia)
{
	string nazwa;
	int liczba;
	float rachunek = 0;
	int limit = 3;

	produkt *tmp = pHead;

	while (plikListaZakupow >> nazwa >> liczba)
	{
		produkt *znaleziony = znajdzProdukt(tmp, nazwa);
		if (znaleziony)
		{
			if (znaleziony->liczba >= liczba && znaleziony->liczba > 0)
			{
				znaleziony->liczba -= liczba;
				rachunek = rachunek + znaleziony->cena * liczba;
				plikRachunek << nazwa << " " << liczba << " * " << znaleziony->cena << "z³ = " << znaleziony->cena * liczba << "z³" << endl;
			}
			else
			{
				plikRachunek << "Zbyt ma³a liczba produktu " << nazwa << " w sklepie" << endl;
			}
		}
		else
		{
			plikRachunek << "Nie ma w sklepie produktu:" << nazwa << endl;
		}
	}

	plikRachunek << "SUMA: " << rachunek << endl;



	produkt *tmpList = nullptr;
	while (tmp)
	{
		if (tmp->liczba <= limit)
		{
			sortujProduktyWedlugLiczby(tmpList, tmp);
		}
		tmp = tmp->pNext;
	}
	tmp = pHead;


	produkt *tmpList2 = tmpList;
	if (nazwaProduktuDoUsuniecia != "")
	{
		usunProdukt(tmpList2, nazwaProduktuDoUsuniecia);
	}
	
	tmpList2 = tmpList;
	wypiszRaport(tmpList2, plikRaport);
	tmpList = tmpList2;
	usunListe(tmpList);

}

void sortujProduktyWedlugLiczby(produkt *&pHead, produkt *&tmp)
{
	if (!pHead)
	{
		pHead = new produkt{ tmp->nazwa, tmp->liczba, tmp->cena, nullptr };
	}
	else if (pHead->liczba > tmp->liczba)
	{
		pHead = new produkt{ tmp->nazwa, tmp->liczba, tmp->cena, pHead};
	}
	else
	{
		sortujProduktyWedlugLiczby(pHead->pNext, tmp);
	}
}

produkt *znajdzProdukt(produkt *&pHead, const string &nazwa)
{
	if (pHead->nazwa == nazwa)
	{
		return pHead;
	}
	else
	{
		znajdzProdukt(pHead->pNext, nazwa);
	}
}


void wypiszRaport(produkt *&pHead, ofstream &plikRaport)
{
	produkt *tmp = pHead;

	while (tmp)
	{
		if (!pHead->liczba)
		{
			produkt *toDelete = pHead;
			pHead = pHead->pNext;
			tmp = pHead;
			delete toDelete;
			continue;
		}
		if (tmp->pNext && !tmp->pNext->liczba)
		{
			produkt *toDelete = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
			delete toDelete;
			continue;
		}
		plikRaport << tmp->nazwa << " " << tmp->liczba << endl;
		tmp = tmp->pNext;
	}
	
}

void usunProdukt(produkt *&pHead, const string & nazwaProduktuDoUsuniecia)
{
	while (pHead)
	{
		if (pHead->pNext->nazwa == nazwaProduktuDoUsuniecia)
		{
			produkt *tmp = pHead->pNext;
			pHead->pNext = pHead->pNext->pNext;
			delete tmp;
			break;
		}
		pHead = pHead->pNext;
	}
	
}

void usunListe(produkt *&pHead)
{
	produkt *tmp;
	while (pHead)
	{
		tmp = pHead;
		pHead = pHead->pNext;
		delete tmp;
	}
}