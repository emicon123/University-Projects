#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

class Pozycja {
public:
	string etykieta;
	string nazwa;
	string autor;
	string rok_wydania;
	Pozycja *pNext;
	virtual void dodaj_pozycje() = 0;
	virtual void wyswietl() = 0;
	virtual void wyswietl_do_pliku(ofstream &plik) = 0;
	virtual void edytuj() = 0;
	Pozycja();
	~Pozycja();
};

class P造ty :public Pozycja {
public:
	string gatunek;
	virtual void dodaj_pozycje() = 0;
	virtual void wyswietl() = 0;
	virtual void wyswietl_do_pliku(ofstream &plik) = 0;
	virtual void edytuj() = 0;
	P造ty();
	~P造ty();
};

class Kasety :public Pozycja {
public:
	string gatunek;
	virtual void dodaj_pozycje() = 0;
	virtual void wyswietl() = 0;
	virtual void wyswietl_do_pliku(ofstream &plik) = 0;
	virtual void edytuj() = 0;
	Kasety();
	~Kasety();
};

class audio :public Kasety {
public:
	string opinia_audio;
	void dodaj_pozycje()
	{
		int x = 0;
		cout << "Podaj autora: " << endl;
		cin >> autor;
		cout << "Podaj nazwe: " << endl;
		cin >> nazwa;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj rok wydania: " << endl;

			cin >> rok_wydania;

			x++;
		} while (!(regex_match(rok_wydania, regex("[0-9]+"))));
		cout << "Podaj gatunek: " << endl;
		cin >> gatunek;
		x = 0;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj opinie 1-5: " << endl;

			cin >> opinia_audio;

			x++;
		} while (!(regex_match(opinia_audio, regex("[1-5]+"))));
		x = 0;
	}
	void wyswietl()
	{
		cout << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_audio<<endl;
	}
	void wyswietl_do_pliku(ofstream &plik)
	{
		plik << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_audio << endl;
	}
	void edytuj();
	
	audio();
	~audio();
};
class wideo :public Kasety {
public:
	string opinia_wideo;
	void dodaj_pozycje()
	{
		int x = 0;
		cout << "Podaj autora: " << endl;
		cin >> autor;
		cout << "Podaj nazwe: " << endl;
		cin >> nazwa;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj rok wydania: " << endl;

			cin >> rok_wydania;
			
			x++;
		} while (!(regex_match(rok_wydania, regex("[0-9]+"))));
		x = 0;
		cout << "Podaj gatunek: " << endl;
		cin >> gatunek;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj opinie 1-5: " << endl;

			cin >> opinia_wideo;


		} while (!(regex_match(opinia_wideo, regex("[1-5]+"))));
		x = 0;
	}
	void wyswietl()
	{
		cout << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_wideo<<endl;
	}
	void wyswietl_do_pliku(ofstream &plik)
	{
		plik << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_wideo << endl;
	}
	
	void edytuj();
	wideo();
	~wideo();
};
class CD :public P造ty {
public:
	string opinia_CD;
	void dodaj_pozycje()
	{
		int x = 0;
		cout << "Podaj autora: " << endl;
		cin >> autor;
		cout << "Podaj nazwe: " << endl;
		cin >> nazwa;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj rok wydania: " << endl;

			cin >> rok_wydania;


		} while (!(regex_match(rok_wydania, regex("[0-9]+"))));
		cout << "Podaj gatunek: " << endl;
		cin >> gatunek;
		x = 0;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj opinie 1-5: " << endl;

			cin >> opinia_CD;

			x++;
		} while (!(regex_match(opinia_CD, regex("[1-5]+"))));
		x = 0;
	}
	void wyswietl()
	{
		cout << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_CD<<endl;
	}
	void wyswietl_do_pliku(ofstream &plik)
	{
		plik << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_CD << endl;
	}
	
	void edytuj();
	CD();
	~CD();

};
class DVD :public P造ty {
public:
	string opinia_DVD;
	void dodaj_pozycje()
	{
		int x = 0;
		cout << "Podaj autora: " << endl;
		cin >> autor;
		cout << "Podaj nazwe: " << endl;
		cin >> nazwa;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj rok wydania: " << endl;

			cin >> rok_wydania;


		} while (!(regex_match(rok_wydania, regex("[0-9]+"))));
		cout << "Podaj gatunek: " << endl;
		cin >> gatunek;
		x = 0;
		do
		{
			if (x > 0)
				cout << "Podano zly format" << endl;

			cout << "Podaj opinie 1-5: " << endl;

			cin >> opinia_DVD;

			x++;
		} while (!(regex_match(opinia_DVD, regex("[1-5]+"))));
		x = 0;
	}
	void wyswietl()
	{
		cout << etykieta << ": "<< autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_DVD<<endl;
	}
	void wyswietl_do_pliku(ofstream &plik)
	{
		plik << etykieta << ": " << autor << " " << nazwa << " " << rok_wydania << " " << gatunek << " " << opinia_DVD << endl;
	}
	void edytuj();
	DVD();
	~DVD();
};

class Lista
{
public:
	int ile_elementow = 0;
	Pozycja *pHead = nullptr;

	void dodajdolisty(Pozycja *Nowa);
	void usun_element(string autorr);
	

	Lista();
	~Lista();
};