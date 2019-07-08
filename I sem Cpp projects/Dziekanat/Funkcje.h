#pragma once
#include <string>
#include <iostream>

using namespace std;

struct przedmiot;

/*Struktura student tworzy liste studwentow. Kazdy element listy studentow posiada wskaznik na
jego liste z ocenami z danych przedmiotow*/
struct student
{
	string imie;
	string nazwisko;
	int nrAlbumu;
	przedmiot *pPrzedmiot;	//wskaznik na podliste
	student *pNext;
};
/*Struktura przedmiot tworzy podliste przedmiotow oraz przechowuje oceny,
ktore zdobyl student
*/
struct przedmiot
{
	string nazwa;
	string prowadzacy;
	string dataWpisu;
	float ocena;
	przedmiot *pNext;
};


/*Funckja odpowiada za budowe grafu - listy list*/
void budujGraf(student *& pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu, const string &dataWpisu,
	const string &nazwaPrzedmiotu, const string &prowadzacy, const float &ocena);


/*Funkcja odpowiada za znajdywanie studenta w liscie lub w przypadku, gdy go nie ma - dodaje nowego studenta do listy studentow*/
student * znajdzLubDodajStudenta(student *&pStudent, const string &imie, const string &nazwisko, const int &nrAlbumu);


/*Funkcja rekurencyjna odpowiada za dodanie przedmiotu do podlisty przedmiotow danego studenta.
Funckja wstawia przedmioty posortowane, zeby pozniej bylo latwiej wypisac je do pliku wyjsciowego*/
void dodajPrzedmiot(przedmiot *&pPrzedmiot, const string &nazwaPrzedmiotu, const string &prowadzacy, const string &dataWpisu, const float &ocena);


/*Funckja sprawdzajaca poprawnosc podanych argumentow w konsoli oraz
odczytujaca nazwy plikow z protokolami*/
bool sprawdzanie_argumentow(int argc, char **argv, string plikiProtokolowNazwy[]);


/*Funckja odczytuje dane z pliku i wysyla je do funckji budujGraf,
ktora tworzy z nich liste list*/
bool czytajDane(string nazwaPliku, student *& pStudent);


/*Funckja odpowiada za wypisanie danych z listy list do pliku wyjsciowego*/
bool wypiszDoPliku(student *&pStudent);


/*Funckja odpowada za usuniecie grafu - listy list*/
void usun(student *&pStudent);
