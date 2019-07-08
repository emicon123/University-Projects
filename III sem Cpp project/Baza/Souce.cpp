#include "stdafx.h"
#include "Classes.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main()
{
	ofstream plik;
	plik.open("Baza.txt");

	string nazwaporownawcza;
	int sw;
	Lista Baza;
	Pozycja*pHead = nullptr;

	while (true)
	{
		cout << "Co chcesz zrobic: " << endl
			<< "1. Dodac kasete audio " << endl
			<< "2. Dodac kasete wideo" << endl
			<< "3. Dodac plyte audio " << endl
			<< "4. Dodac plyte wideo" << endl
			<< "5. Wyswietlic liste" << endl
			<< "6. Wyswietlic kasety audio" << endl
			<< "7. Wyswietlic kasety wideo" << endl
			<< "8. Wyswietlic plyty audio" << endl
			<< "9. Wyswietlic plyty wideo" << endl
			<< "10. Edytowac kasety audio" << endl
			<< "11. Edytowac kasety wideo" << endl
			<< "12. Edytowac plyty audio" << endl
			<< "13. Edytowac plyty wideo" << endl
			<< "14. Zapisac baze w pliku" << endl
			<< "15. Zakonczyc program" << endl;
		cin >> sw;
		switch (sw)
		{
			Pozycja*dodany;
		case 1:
			cout << endl;
			dodany = new audio();
			dodany->dodaj_pozycje();
			Baza.dodajdolisty(dodany);
			Baza.ile_elementow++;
			system("cls");
			cout << "Element pomyslnie dodany do bazy!" << endl << endl;
			break;

		case 2:
			cout << endl;
			dodany = new wideo();
			dodany->dodaj_pozycje();
			Baza.dodajdolisty(dodany);
			Baza.ile_elementow++;
			cout << "Element pomyslnie dodany do bazy!" << endl << endl;
			system("cls");
			break;

		case 3:
			cout << endl;
			dodany = new CD();
			dodany->dodaj_pozycje();
			Baza.dodajdolisty(dodany);
			Baza.ile_elementow++;
			system("cls");
			cout << "Element pomyslnie dodany do bazy!" << endl << endl;
			break;

		case 4:
			cout << endl;
			dodany = new DVD();
			dodany->dodaj_pozycje();
			Baza.dodajdolisty(dodany);
			Baza.ile_elementow++;
			system("cls");
			cout << "Element pomyslnie dodany do bazy!" << endl << endl;
			break;

		case 5:
			cout << endl;
			Pozycja*Pomocniczy;
			Pomocniczy = Baza.pHead;
			while (Pomocniczy)
			{
				Pomocniczy->wyswietl();
				Pomocniczy = Pomocniczy->pNext;
			}
			system("pause");
			cout << endl;
			system("cls");
			break;

		case 6:
			cout << endl;
			Pozycja*Pomocniczy1;
			Pomocniczy1 = Baza.pHead;
			while (Pomocniczy1) {
				if (Pomocniczy1->etykieta == "kaseta audio")
					Pomocniczy1->wyswietl();
				Pomocniczy1 = Pomocniczy1->pNext;
			}
			system("pause");
			cout << endl;
			system("cls");
			break;

		case 7:
			cout << endl;
			Pozycja*Pomocniczy2;
			Pomocniczy2 = Baza.pHead;
			while (Pomocniczy2) {
				if (Pomocniczy2->etykieta == "kaseta wideo")
					Pomocniczy2->wyswietl();
				Pomocniczy2 = Pomocniczy2->pNext;
			}
			system("pause");
			cout << endl;
			system("cls");
			break;

		case 8:
			cout << endl;
			Pozycja*Pomocniczy3;
			Pomocniczy3 = Baza.pHead;
			while (Pomocniczy3) {
				if (Pomocniczy3->etykieta == "plyta audio") 
					Pomocniczy3->wyswietl();
					Pomocniczy3 = Pomocniczy3->pNext;
				}
				system("pause");
				cout << endl;
				system("cls");
				break;

		case 9:
			cout << endl;
			Pozycja*Pomocniczy4;
			Pomocniczy4 = Baza.pHead;
			while (Pomocniczy4) {
				if (Pomocniczy4->etykieta == "plyta wideo")
					Pomocniczy4->wyswietl();
				Pomocniczy4 = Pomocniczy4->pNext;
			}
			system("pause");
			cout << endl;
			system("cls");
			break;

		case 10:
			cout << endl;
			Pozycja*Pomocniczy5;
			Pomocniczy5 = Baza.pHead;
			cout << "Podaj nazwe elementu do edycji: ";
			cin >> nazwaporownawcza;
			while (Pomocniczy5) {
				if (Pomocniczy5->etykieta == "kaseta audio"&&Pomocniczy5->nazwa == nazwaporownawcza)
				{
					Pomocniczy5->edytuj();
				}
				Pomocniczy5 = Pomocniczy5->pNext;
			}
			system("cls");
			cout << "Edycja przebiegla pomyslnie!" << endl;
			cout << endl;
			break;

		case 11:
			cout << endl;
			Pozycja*Pomocniczy6;
			Pomocniczy6 = Baza.pHead;
			cout << "Podaj nazwe elementu do edycji: ";
			cin >> nazwaporownawcza;
			while (Pomocniczy6) {
				if (Pomocniczy6->etykieta == "kaseta wideo"&&Pomocniczy6->nazwa == nazwaporownawcza)
				{
					Pomocniczy6->edytuj();
				}
				Pomocniczy6 = Pomocniczy6->pNext;
			}
			system("cls");
			cout << "Edycja przebiegla pomyslnie!" << endl;
			cout << endl;
			break;

		case 12:
			cout << endl;
			Pozycja*Pomocniczy7;
			Pomocniczy7 = Baza.pHead;
			cout << "Podaj nazwe elementu do edycji: ";
			cin >> nazwaporownawcza;
			while (Pomocniczy7) {
				if (Pomocniczy7->etykieta == "plyta audio"&&Pomocniczy7->nazwa == nazwaporownawcza)
				{
					Pomocniczy7->edytuj();
				}
				Pomocniczy7 = Pomocniczy7->pNext;
			}
			system("cls");
			break;

		case 13:
			cout << endl;
			Pozycja*Pomocniczy8;
			Pomocniczy8 = Baza.pHead;
			cout << "Podaj nazwe elementu do edycji: ";
			cin >> nazwaporownawcza;
			while (Pomocniczy8) {
				if (Pomocniczy8->etykieta == "plyta wideo"&&Pomocniczy8->nazwa == nazwaporownawcza)
				{
					Pomocniczy8->edytuj();
				}
				Pomocniczy8= Pomocniczy8->pNext;
			}
			system("cls");
			cout << "Edycja przebiegla pomyslnie!" << endl;
			cout << endl;
			break;

		case 14:
			cout << endl;
			Pozycja*Pomocniczy9;
			Pomocniczy9 = Baza.pHead;
			while (Pomocniczy9)
			{
				Pomocniczy9->wyswietl_do_pliku(plik);
				Pomocniczy9 = Pomocniczy9->pNext;
			}
			system("cls");
			cout << "Pomyslnie zapisano baze w pliku!" << endl;
			cout << endl;
			break;

		default:
			cout << endl;
			cout << "Podano z³y numer" << endl;
			system("cls");
			break;
			}

			if (sw == 15)
				break;
		}

		plik.close();
    return 0;
}

