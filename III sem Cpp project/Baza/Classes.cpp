#include "stdafx.h"
#include "Classes.h"
#include <iostream>
#include <string>
using namespace std;
//konstruktory+destruktory
Pozycja::Pozycja()
{
	etykieta = "NONE";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
}

Pozycja::~Pozycja()
{
}

P造ty::P造ty()
{
	etykieta = "NONE";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
}
P造ty::~P造ty()
{
}

Kasety::Kasety()
{
	etykieta = "NONE";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
}
Kasety::~Kasety()
{
}

audio::audio()
{
	etykieta = "kaseta audio";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
	opinia_audio = "0";
}
audio::~audio()
{
}
wideo::wideo()
{
	etykieta = "kaseta wideo";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
	opinia_wideo = "0";
}
wideo::~wideo()
{
}

CD::CD()
{
	etykieta = "plyta audio";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
	opinia_CD = "0";
}
CD::~CD()
{
}
DVD::DVD()
{
	etykieta = "plyta wideo";
	nazwa = "NONE";
	autor = "NONE";
	rok_wydania = "0000";
	pNext = nullptr;
	gatunek = "NONE";
	opinia_DVD = "0";
}
DVD::~DVD()
{
}

//edycja element闚
void audio::edytuj()
{
	string nowyautor;
	string nowanazwa;
	int nowyrok;
	string nowygatunek;
	int nowaopinia;
	int wybor;
	cout << "Ktora dana chcesz zmienic?" << endl;
	cout << " 1.autor 2.nazwa 3. rok_wydania 4. gatunek 5. opinie" << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		cout << "Podaj nowa nazwe autora: " << endl;
		cin>> nowyautor;
		autor = nowyautor;
		break;
	case 2:
		cout << "Podaj nowa nazwe: " << endl;
		cin >> nowanazwa;
		nazwa = nowanazwa;
		break;
	case 3:
		cout << "Podaj nowy rok wydania: " << endl;
		cin >> nowyrok;
		rok_wydania = nowyrok;
		break;
	case 4:
		cout << "Podaj nowy gatunek: " << endl;
		cin >> nowygatunek;
		gatunek = nowygatunek;
		break;
	case 5:
		cout << "Podaj nowa opinie: " << endl;
		cin >> nowaopinia;
		opinia_audio = nowaopinia;
		break;
	default:
		cout << "Zly numer przy wyborze" << endl;
		break;
	}

}
void wideo::edytuj()
{
	string nowyautor;
	string nowanazwa;
	int nowyrok;
	string nowygatunek;
	int nowaopinia;
	int wybor;
	cout << "Ktora dana chcesz zmienic?" << endl;
	cout << " 1.autor 2.nazwa 3. rok_wydania 4. gatunek 5. opinie" << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		cout << "Podaj nowa nazwe autora: " << endl;
		cin >> nowyautor;
		autor = nowyautor;
		break;
	case 2:
		cout << "Podaj nowa nazwe: " << endl;
		cin >> nowanazwa;
		nazwa = nowanazwa;
		break;
	case 3:
		cout << "Podaj nowy rok wydania: " << endl;
		cin >> nowyrok;
		rok_wydania = nowyrok;
		break;
	case 4:
		cout << "Podaj nowy gatunek: " << endl;
		cin >> nowygatunek;
		gatunek = nowygatunek;
		break;
	case 5:
		cout << "Podaj nowa opinie: " << endl;
		cin >> nowaopinia;
		opinia_wideo = nowaopinia;
		break;
	default:
		cout << "Zly numer przy wyborze" << endl;
		break;
	}


}
void CD::edytuj()
{
	string nowyautor;
	string nowanazwa;
	int nowyrok;
	string nowygatunek;
	int nowaopinia;
	int wybor;
	cout << "Ktora dana chcesz zmienic?" << endl;
	cout << " 1.autor 2.nazwa 3. rok_wydania 4. gatunek 5. opinie" << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		cout << "Podaj nowa nazwe autora: " << endl;
		cin >> nowyautor;
		autor = nowyautor;
		break;
	case 2:
		cout << "Podaj nowa nazwe: " << endl;
		cin >> nowanazwa;
		nazwa = nowanazwa;
		break;
	case 3:
		cout << "Podaj nowy rok wydania: " << endl;
		cin >> nowyrok;
		rok_wydania = nowyrok;
		break;
	case 4:
		cout << "Podaj nowy gatunek: " << endl;
		cin >> nowygatunek;
		gatunek = nowygatunek;
		break;
	case 5:
		cout << "Podaj nowa opinie: " << endl;
		cin >> nowaopinia;
		opinia_CD = nowaopinia;
		break;
	default:
		cout << "Zly numer przy wyborze" << endl;
		break;
	}


}
void DVD::edytuj()
{
	string nowyautor;
	string nowanazwa;
	int nowyrok;
	string nowygatunek;
	int nowaopinia;
	int wybor;
	cout << "Ktora dana chcesz zmienic?" << endl;
	cout << " 1.autor 2.nazwa 3. rok_wydania 4. gatunek 5. opinie" << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		cout << "Podaj nowa nazwe autora: " << endl;
		cin >> nowyautor;
		autor = nowyautor;
		break;
	case 2:
		cout << "Podaj nowa nazwe: " << endl;
		cin >> nowanazwa;
		nazwa = nowanazwa;
		break;
	case 3:
		cout << "Podaj nowy rok wydania: " << endl;
		cin >> nowyrok;
		rok_wydania = nowyrok;
		break;
	case 4:
		cout << "Podaj nowy gatunek: " << endl;
		cin >> nowygatunek;
		gatunek = nowygatunek;
		break;
	case 5:
		cout << "Podaj nowa opinie: " << endl;
		cin >> nowaopinia;
		opinia_DVD = nowaopinia;
		break;
	default:
		cout << "Zly numer przy wyborze" << endl;
		break;
	}


}

void Lista::dodajdolisty(Pozycja *nowy)
{
	Pozycja *pomocniczy = pHead;
	if (!pHead)
	{
		pHead = nowy;
		ile_elementow++;
		return;
	}
	else while (pomocniczy->pNext)
	{
		pomocniczy = pomocniczy->pNext;
	}
	pomocniczy->pNext = nowy;
	ile_elementow++;

}
void Lista::usun_element(string autorr)
{
	Pozycja *Pomocniczy = pHead;
	if (pHead->autor == autorr)
	{
		Pomocniczy = pHead->pNext;
		delete pHead;
		pHead = Pomocniczy;
	}
	while (Pomocniczy->pNext)
	{
		if (Pomocniczy->pNext->autor == autorr)
		{
			Pozycja *Pomocniczy2;
			Pomocniczy2 = Pomocniczy->pNext->pNext;
			delete Pomocniczy->pNext;
			Pomocniczy->pNext =Pomocniczy2;
			return;
		}
		Pomocniczy = Pomocniczy->pNext;
	}
	cout << "W bazie nie ma takiego autora" << endl;
	system("pause");
	return;
}

Lista::Lista()
{
}

Lista::~Lista()
{
	while (pHead)
	{
		Pozycja*Pomocniczy = pHead->pNext;
		delete pHead;
		pHead = Pomocniczy;
	}
}