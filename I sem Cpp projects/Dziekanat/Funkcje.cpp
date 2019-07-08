#include <iostream>
#include <string>
#include <fstream>
#include <regex>	//biblioteka dodana sprawdzenia poprawnosci danych wejsciowych
#include "Funkcje.h"

using namespace std;




void budujGraf(student *& pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu, const string &dataWpisu,
	const string &nazwaPrzedmiotu, const string &prowadzacy, const float &ocena);
student * znajdzLubDodajStudenta(student *&pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu);
void dodajPrzedmiot(przedmiot *&pPrzedmiot, const string &nazwaPrzedmiotu, const string &prowadzacy, const string &dataWpisu, const float &ocena);


/*Funckja sprawdzajaca poprawnosc podanych argumentow w konsoli oraz
odczytujaca nazwy plikow z protokolami*/
bool sprawdzanie_argumentow(int argc, char **argv, string plikiProtokolowNazwy[])
{
	if (argc > 1)
	{
		//funkcja strcmp() zwraca wartoœæ zero, gdy str1 jest takie same jak str2, mniejsz¹ od zero gdy str1 < str2 oraz wiêksz¹ od zero gdy str1 > str2.
		if (!strcmp(argv[1], "-i"))	//sprawdzamy, czy podano prawidlowy przelacznik
		{
			for (int i = 0; i < argc - 2; i++)	//pierwszy i drugi argument tablicy argv to DziekanatPPK.exe i przelacznik "-i:"
			{
				plikiProtokolowNazwy[i] = argv[i + 2];	//dodajemy do tablicy dynamicznej odczytane nazwy plikow protokolow
			}
		}
		else
		{
			cout << "Podano zly przelacznik" << endl;
			return false;
		}
	}
	else
	{
		cout << "Podano zbyt malo argumentow" << endl;
		return false;
	}

	return true;
}

/*Funckja odczytuje dane z pliku i wysyla je do funckji budujGraf,
ktora tworzy z nich liste list*/
bool czytajDane(string nazwaPliku, student *& pStudent)
{
	ifstream plikProtokolu;
	plikProtokolu.open(nazwaPliku);
	if (plikProtokolu.is_open() && plikProtokolu.good());
	else
	{
		cout << "Nie udalo sie otworzyc pliku protokolu: " << nazwaPliku << endl;
		return false;
	}

	string imieStudenta;
	string nazwiskoStudenta;
	int nrAlbumu;
	float ocena;
	string dataWpisu;
	string nazwaPrzedmiotu;
	string prowadzacy;

	getline(plikProtokolu, nazwaPrzedmiotu);	//Pobranie pierwszej linii pliku - nazwy przedmiotu
	getline(plikProtokolu, prowadzacy);			//Pobranie drugiej linii pliku - prowadzacego


	/*
	Po poprzednich getline'ach "wskaznik lini" w pliku jest ustawiony na 3 linii
	dlatego od teraz mozna pobierac dane w prostszy sposob - strumieniowo

	Z wczytanych danych budujemy graf - liste list
	*/
	if ((nazwaPrzedmiotu.length() != 0) && (prowadzacy.length() != 0))
	{
		while (plikProtokolu >> imieStudenta >> nazwiskoStudenta >> nrAlbumu >> ocena >> dataWpisu)
		{
			budujGraf(pStudent, imieStudenta, nazwiskoStudenta, nrAlbumu, dataWpisu, nazwaPrzedmiotu, prowadzacy, ocena);
		}
	}



	plikProtokolu.close();
	return true;
}



/*Funckja odpowiada za budowe grafu - listy list*/
void budujGraf(student *& pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu, const string &dataWpisu,
	const string &nazwaPrzedmiotu, const string &prowadzacy, const float &ocena)
{
	student *tmp = pStudent;

	//jesli nie ma jeszcze zadnego studenta w liscie, to dodajemy nowego wraz z przedmiotem
	if (!pStudent)
	{
		pStudent = new student{ imie, nazwisko, nrAlbumu, nullptr, nullptr };
		pStudent->pPrzedmiot = new przedmiot{ nazwaPrzedmiotu, prowadzacy, dataWpisu, ocena, nullptr };

	}
	/*w innym wypadku nalezy sprawdzic, czy odczytywany student juz istnieje. Jesli tak - znajdujemy go i dodajemy przedmiot do jego podlisty
	jesli nie - tworzymy nowego studenta i dodajemy przedmiot do jego podlisty*/
	else
	{
		student *tmpStudent = znajdzLubDodajStudenta(tmp, imie, nazwisko, nrAlbumu);
		dodajPrzedmiot(tmpStudent->pPrzedmiot, nazwaPrzedmiotu, prowadzacy, dataWpisu, ocena);
	}

}




/*Funkcja odpowiada za znajdywanie studenta w liscie lub w przypadku, gdy go nie ma - dodaje nowego studenta do listy studentow*/
student * znajdzLubDodajStudenta(student *&pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu)
{
	while (pStudent)	//dopoki istnieja elementy listy studenci
	{
		//jesli nr albumu studenta ktory jest obecnie odczytywany z pliku pokrywa sie z nr albumu ktoregos elementu listy studentow, znaczy to, ze mamy juz tego studenta w naszej liscie
		if (pStudent->nrAlbumu == nrAlbumu)
		{
			return pStudent;
		}
		// jesli nie to dodajemy nowego studenta do listy
		else
		{
			if (!pStudent->pNext)	//przechodzimy na koniec listy studentow
			{
				pStudent->pNext = new student{ imie, nazwisko, nrAlbumu, nullptr, nullptr };	//dodajemy studenta
				return pStudent->pNext;
			}
		}
		pStudent = pStudent->pNext;
	}
}

/*Funkcja rekurencyjna odpowiada za dodanie przedmiotu do podlisty przedmiotow danego studenta.
Funckja wstawia przedmioty posortowane, zeby pozniej bylo latwiej wypisac je do pliku wyjsciowego*/
void dodajPrzedmiot(przedmiot *&pPrzedmiot, const string &nazwaPrzedmiotu, const string &prowadzacy, const string &dataWpisu, const float &ocena)
{

	if (!pPrzedmiot)	//jesli student nie ma zadnego przedmiotu w podliscie, to dodajemy nowy przedmiot
	{
		pPrzedmiot = new przedmiot{ nazwaPrzedmiotu, prowadzacy, dataWpisu, ocena, nullptr };
	}
	else if (pPrzedmiot->nazwa > nazwaPrzedmiotu)	//jesli aktualnie dodawana nazwa przedmiotu jest wieksza od tej, ktora istnieje w aktualnie przegladanym elemencie listy, 
	{
		pPrzedmiot = new przedmiot{ nazwaPrzedmiotu, prowadzacy, dataWpisu, ocena, pPrzedmiot };
	}
	else
	{
		dodajPrzedmiot(pPrzedmiot->pNext, nazwaPrzedmiotu, prowadzacy, dataWpisu, ocena);
	}
}


/*Funckja odpowiada za wypisanie danych z listy list do pliku wyjsciowego*/
bool wypiszDoPliku(student *&pStudent)
{
	string nrAlbumuString = to_string(pStudent->nrAlbumu) + ".txt";	//wyciagmy nr albumu studenta, aby moc utworzyc plik wynikowy o nazwie takiej samej jak numer albumu

	ofstream plikWynikowy;
	plikWynikowy.open(nrAlbumuString);
	if (plikWynikowy.is_open() && plikWynikowy.good());
	else
	{
		cout << "Blad podczas otwierania pliku wynikowego studenta o numerze albumu: " << pStudent->nrAlbumu << endl;
		return false;
	}


	plikWynikowy << pStudent->imie << " " << pStudent->nazwisko << endl;
	plikWynikowy << "Nr albumu: " << pStudent->nrAlbumu << endl << endl;

	przedmiot *tmpP = pStudent->pPrzedmiot;

	while (tmpP)
	{
		plikWynikowy << "- " << tmpP->prowadzacy << "\t - " << tmpP->nazwa
			<< "\t - " << tmpP->ocena << "\t - " << tmpP->dataWpisu << endl;

		tmpP = tmpP->pNext;
	}

	plikWynikowy.close();
	return true;
}



/*Funckja odpowada za usuniecie grafu - listy list*/
void usun(student *&pStudent)
{
	while (pStudent)
	{

		while (pStudent->pPrzedmiot)
		{
			przedmiot *tmp = pStudent->pPrzedmiot;
			pStudent->pPrzedmiot = pStudent->pPrzedmiot->pNext;
			delete tmp;
		}
		student *tmp = pStudent;

		pStudent = pStudent->pNext;
		delete tmp;
	}
}

