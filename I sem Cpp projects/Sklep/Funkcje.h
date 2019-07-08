#pragma once
#include <string>
#include <iostream>

using namespace std;

struct produkt
{
	string nazwa;
	int liczba;
	float cena;
	produkt *pNext;
};


bool sprawdzanie_argumentow(int argc, char **argv, string &plikProduktyNazwa, string &plikZakupyNazwa,
	string &plikRaportNazwa, string &plikRachunekNazwa, string &nazwaProduktuDoUsuniecia);

void dodajProdukty(produkt *&pHead, const string &plikProduktyNazwa);

void dodajProdukt(produkt *& pHead, const string &nazwa, const int &liczba, const float &cena);

void budujListe(produkt *&pHead, const string &nazwa, const int &liczba, const float &cena);

void zakupy(produkt *&pHead, ifstream &plikListaZakupow, ofstream &plikRachunek, ofstream &plikRaport, const string nazwaProduktuDoUsuniecia);

produkt *znajdzProdukt(produkt *&pHead, const string &nazwa);

void sortujProduktyWedlugLiczby(produkt *&pHead, produkt *&tmp);

void wypiszRaport(produkt *&pHead, ofstream &plikRaport);

void usunProdukt(produkt *&pHead, const string &nazwaProduktuDoUsuniecia);

void usunListe(produkt *&pHead);
