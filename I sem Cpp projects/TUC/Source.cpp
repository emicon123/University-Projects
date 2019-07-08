#include <iostream>
#include <fstream>
#include <string>


#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
//#include <stdlib.h>	//sprawdzanie wyciekow pamieci
//#include <crtdbg.h>
//#define _DEBUG 
//#define _CRTDBG_MAP_ALLOC
using namespace std;


struct wejscia;
/*
Struktura bramka przechowuje dane o rodzaju (nazwie) bramki i
danych jej wyjscia - wezla wychodzacego.
Kazda bramka (oprocz NEG) ma 2 wskazniki na wejscia - lewe i prawe.
W przypadku NEG wskaznik ustawiony jest tylko na wejscie lewe*/
struct bramka
{
	string nazwa;
	int wyjscie;
	bool wartosc;
	wejscia *pLeft;
	wejscia *pRight;
	bramka *pNext;
	
};

/*
Struktura wejscia przechowuje dane o wejsciu do bramki*/
struct wejscia
{
	int wejscie;
	bool wartosc;
};


/*
Funkcja help wyswietla sie, gdy podano zle argumenty lub przelacznik -h i
wyswietla jak poprawnie powinien zostac uruchomiony program*/
void help()
{
	cout << endl << "To jest program sluzacy do symulacji ukladow bramek logicznych.\n"
		"Aby program zadzialal nalezy wpisac nastepujace dane:\n"
		"'-u' - przelacznik do pliku z z ukladem bramek\n"
		"Po nim wpisz nazwe pliku z ukladem bramek z odpowiednim rozszerzeniem pliku.\n"
		"'-i' - przelacznik do pliku ze stanem wejsc\n"
		"Po nim wpisz nazwe pliku ze stanami wejsc ukladu.\n"
		"'-o' - przelacznik do pliku wyjsciowego ze stanami wyjsc.\n"
		"Po nim wpisz nazwe pliku wyjsciowego. \n";
}

/*
Funkcja sprawdzajaca poprawnosc wpisanych argumentow wejsciowych*/
bool sprawdzanie_argumentow(int argc, char **argv, string plikiNazwy[])
{
	if (argc > 1)
	{
		if (!strcmp(argv[1], "-h") || argc == 1)										// jesli zostal podany przelacznik -h to wyswietl pomoc i przerwij program
		{
			help();
			return false;
		}
		if (argc < 7)
		{
			cout << "Podano zbyt malo argumentow" << endl;
			help();
			return false;
		}

		for (int i = 0; i < argc; i++)								// petla dodajaca argumenty wpisane w konsoli
		{
			if (!strcmp(argv[i], "-u"))
			{
				plikiNazwy[0] = argv[i + 1];						// jesli zostal podany przelacznik -u to nastepnym argumentem musi byæ plik w ukladem wejsciowym
			}
			else if (!strcmp(argv[i], "-i"))
			{
				plikiNazwy[1] = argv[i + 1];						// jesli zostal podany przelacznik -i to nastepnym argumentem musi byæ plik z wejsciami
			}				
			else if (!strcmp(argv[i], "-o"))
			{
				plikiNazwy[2] = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-h"))					// jesli zostal podany przelacznik -h to wyswietl pomoc i przerwij program
			{
				help();
				return false;
			}		
		}
	}
	return true;
}

/*
Funkcja buduje graf (strukture), w ktorym przechowane beda elementy ukladu*/
void budujGraf(bramka *&pBramka, const string &nazwaBramki, const int &wejscie1,
	const int &wejscie2, const int &wyjscie)
{
	bramka *tmp = pBramka;
	if (!pBramka)	//jesli glowa jest pusta to znaczy, ze dodajemy pierwszy element do listy
	{
		pBramka = new bramka{ nazwaBramki, wyjscie, false, false, 0, 0 };
		if (nazwaBramki == "NEG")
		{
			pBramka->pLeft = new wejscia{ wejscie1, false };
		}
		else
		{
			pBramka->pLeft = new wejscia{ wejscie1, false };
			pBramka->pRight = new wejscia{ wejscie2, false };
		}
		tmp = pBramka;
	}
	else	//jesli nie, to przechodzimy przez liste i dodajemy nowy element na jej koniec
	{
		while (tmp)
		{
			if (!tmp->pNext)
			{
				if (nazwaBramki == "NEG")
				{
					tmp->pNext = new bramka{ nazwaBramki, wyjscie, false, false, 0, 0 };
					tmp->pNext->pLeft = new wejscia{ wejscie1, false };
					break;	//break, aby uniknac zapetlenia, bo dodajemy element tmp->pNext, a petla przesuwa liste o tmp->pNext
				}
				else
				{
					tmp->pNext = new bramka{ nazwaBramki, wyjscie, false, false, 0, 0 };
					tmp->pNext->pLeft = new wejscia{ wejscie1, false };
					tmp->pNext->pRight = new wejscia{ wejscie2, false };
					break;	//jw.
				}
			}
			tmp = tmp->pNext;
		}
	}
}

/*
Funkcja ustawia wartosci wejscia bramki*/
void ustawBramke(wejscia *&pWejscie, const string &wartoscWejscia)	
{
	if (wartoscWejscia == "0")
	{
		pWejscie->wartosc = false;
	}
	else
	{
		pWejscie->wartosc = true;
	}
}

/*
Funkcja ustala stan poczatkowy ukladu - chodzi o to, zeby dobrze wstawic wezly wejsciowe ukladu, by potem moc prawidlowo go rozwiazac*/
void ustawStanPoczatkowy(bramka *& pBramka, const string &wartoscWejscia1, const string &wartoscWejscia2, const int &wejscieUkladu1, const int &wejscieUkladu2)
{
	bramka *tmp = pBramka;
	while (tmp)	//szukamy bramki/bramek, do ktorych wchodza wezly poczatkowe
	{
		
		if (tmp->pLeft->wejscie == wejscieUkladu1)	// jesli znalezlismy bramke, do ktorej wchodzi pierwsze wejscie ukladu...
		{
			ustawBramke(tmp->pLeft, wartoscWejscia1);	//ustawiamy wartosc wezla
			if (tmp->pRight && (tmp->pLeft->wejscie == tmp->pRight->wejscie))	//sprawdzamy, czy bramka nie jest typu NEG i czy nie wchodzi do niej to samo rozgalezione wejscie
			{
				ustawBramke(tmp->pRight, wartoscWejscia1);
			}
		}
		else if (tmp->pRight)	//sprawdzamy, czy bramka nie jest typu NEG
		{
			if (tmp->pRight->wejscie == wejscieUkladu1)	// ustawiamy prawy wezel
			{
				ustawBramke(tmp->pRight, wartoscWejscia1);
			}
		}
			

		if (tmp->pLeft->wejscie == wejscieUkladu2)	//to samo dla drugiego wejscia ukladu
		{
			ustawBramke(tmp->pLeft, wartoscWejscia2);
			if (tmp->pRight && (tmp->pLeft->wejscie == tmp->pRight->wejscie))
			{
				ustawBramke(tmp->pRight, wartoscWejscia1);
			}
		}
		else if (tmp->pRight)
		{
			if (tmp->pRight->wejscie == wejscieUkladu2)
			{
				ustawBramke(tmp->pRight, wartoscWejscia2);
			}
			
		}
		tmp = tmp->pNext;
	}
}

/*
Funkcje odpowiadajace za zachowania bramek - opisana tylko bramka AND - reszta analogicznie*/
bool andGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)	// sprawdzamy wartosc lewego wezla
	{
	case 0:	//jesli false
		switch (pBramka->pRight->wartosc)	//sprawdzamy wartosc prawego wezla
		{
		case 0:	//jesli false
			pBramka->wartosc = false;	//zgodnie z tablica prawdy do bramki AND ustawiamy wezel na false
			return false;	//zwracamy false
		case 1:	//jesli true
			pBramka->wartosc = false;	//zgodnie z tablica prawdy do bramki AND ustawiamy wezel na false
			return false;	//zwracamy false
		default:
			break;
		}
	case 1:	//jesli true
		switch (pBramka->pRight->wartosc)	//sprawdzamy wartosc prawego wezla
		{
		case 0:
			pBramka->wartosc = false;	//zgodnie z tablica prawdy do bramki AND ustawiamy wezel na false
			return false;	//zwracamy false
		case 1:
			pBramka->wartosc = true;	//zgodnie z tablica prawdy do bramki AND ustawiamy wezel na true
			return true;	//zwracamy true
		default:
			break;
		}
	default:
		break;
	}
}
bool nandGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = true;
			return true;
		default:
			break;
		}
	case 1:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = false;
			return false;
		default:
			break;
		}
	default:
		break;
	}
}
bool orGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = false;
			return false;
		case 1:
			pBramka->wartosc = true;
			return true;
		default:
			break;
		}
	case 1:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = true;
			return true;
		default:
			break;
		}
	default:
		break;
	}
}
bool norGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = false;
			return false;
		default:
			break;
		}
	case 1:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = false;
			return false;
		case 1:
			pBramka->wartosc = false;
			return false;
		default:
			break;
		}
	default:
		break;
	}
}
bool xorGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = false;
			return false;
		case 1:
			pBramka->wartosc = true;
			return true;
		default:
			break;
		}
	case 1:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = false;
			return false;
		default:
			break;
		}
	default:
		break;
	}
}
bool xnorGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = true;
			return true;
		case 1:
			pBramka->wartosc = false;
			return false;
		default:
			break;
		}
	case 1:
		switch (pBramka->pRight->wartosc)
		{
		case 0:
			pBramka->wartosc = false;
			return false;
		case 1:
			pBramka->wartosc = true;
			return true;
		default:
			break;
		}
	default:
		break;
	}
}
bool negGate(bramka *&pBramka)
{
	switch (pBramka->pLeft->wartosc)
	{
	case 0:
		pBramka->wartosc = true;
		return true;
	case 1:
		pBramka->wartosc = false;
		return false;
	default:
		break;
	}
}

/*
Funkcja ustawia wejscia kolejnych bramek w ukladzie (innych niz te, do ktorych wchodza wezly poczatkowe)*/
void ustawWejscia(bramka *&pBramka, const bool &out)
{
	bramka *tmp = pBramka;
	bramka *doZnalezienia = pBramka;	//nalezy znalezc bramke/bramki o tych samych wezlach wejsciowych, co wezel wyjsciowy analizowanej w funkcji 'symulujUklad' bramki

	while (doZnalezienia)
	{
		if (tmp->wyjscie == doZnalezienia->pLeft->wejscie)	//jesli wyjscie bramki to ten sam wezel, co lewe wejscie bramki do znalezienia, to przypisujemy mu wartosc tego wyjscia
		{
			doZnalezienia->pLeft->wartosc = out;
		}
		else if (doZnalezienia->pRight)	//jesli bramka nie jest typu NEG
		{
			if (tmp->wyjscie == doZnalezienia->pRight->wejscie)	// analogicznie dla prawego wejscia
			{
				doZnalezienia->pRight->wartosc = out;
			}
		}
		doZnalezienia = doZnalezienia->pNext;
	}
}
/*
Fukncja odpowiada za symulacje ukladu*/
bool symulujUklad(bramka *& pBramka)
{
	bramka *tmp = pBramka;
	bramka *tmp2 = pBramka;
	bool out;

	while (tmp)	//sprawdzamy jaka bramke aktualnie nalezy sprawdzic
	{
		if (tmp->nazwa == "AND")
		{
			out = andGate(tmp);
			ustawWejscia(tmp2, out);			
		}
		else if (tmp->nazwa == "NAND")
		{
			out = nandGate(tmp);
			ustawWejscia(tmp, out);
		}
		else if (tmp->nazwa == "OR")
		{
			out = orGate(tmp);
			ustawWejscia(tmp2, out);
		}
		else if (tmp->nazwa == "NOR")
		{
			out = norGate(tmp);
			ustawWejscia(tmp2, out);
		}
		else if (tmp->nazwa == "XOR")
		{
			out = xorGate(tmp);
			ustawWejscia(tmp2, out);
		}
		else if (tmp->nazwa == "XNOR")
		{
			out = xnorGate(tmp);
			ustawWejscia(tmp2, out);
		}
		else if (tmp->nazwa == "NEG")
		{
			out = negGate(tmp);
			ustawWejscia(tmp2, out);
		}

		if (!tmp->pNext)	//jesli jestesmy przy ostatniej bramce, to znaczy, ze wartosc jej wyjscia jest wartoscia koncowa ukladu
		{
			return tmp->wartosc;
		}
		else //jesli nie, to przerabiamy kolejne bramki ukladu
		{
			tmp = tmp->pNext;
		}	
	}
}
/*
Funkcja usuwa graf*/
void usun(bramka *&pBramka)
{
	bramka *tmp;
	while (pBramka)
	{
		delete pBramka->pLeft;
		if (pBramka->pRight)	//jesli bramka nie jest typu NEG
		{
			delete pBramka->pRight;
		}

		tmp = pBramka;
		pBramka = pBramka->pNext;
		delete tmp;
	}
}

int main(const int argc, char **argv)
{
	string * plikiNazwy = new string[argc - 4];	//tablica dynamiczna przechowujaca nazwy plikow.
	//Rozmiar argc - 4 dlatego, ze niektore elementy tablicy to TUC.exe i przelaczniki -i -u -o:"

	if (!sprawdzanie_argumentow(argc, argv, plikiNazwy))
	{
		cout << "Nie udalo sie poprawnie odczytac argumentow." << endl << endl;
		return 0;
	}
	
	ifstream plikUklad;
	plikUklad.open(plikiNazwy[0]);											// otwieranie pliku z ukladem
	if (!(plikUklad.is_open() && plikUklad.good()))
	{
		cout << "Nie udalo sie otworzyc pliku z ukladem." << endl;
		help();
		return 0;
	}

	ifstream plikStanyWejsc;														// otwieranie pliku ze stanem wejsc
	plikStanyWejsc.open(plikiNazwy[1]);
	if (!(plikStanyWejsc.is_open() && plikStanyWejsc.good()))
	{
		cout << "Nie udalo sie otworzyc pliku ze stanami wejsc." << endl;
		help();
		return 0;
	}

	ofstream plikWyjsciowy;													// otwieranie pliku wyjsciowego
	plikWyjsciowy.open(plikiNazwy[2]);
	if (!(plikWyjsciowy.is_open() && plikWyjsciowy.good()))
	{
		cout << "Nie udalo sie otworzyc pliku wyjsciowego." << endl;
		help();
		return 0;
	}

	//deklaracja glowy grafu i konieczne zmienne do odczytu danych z plikow
	bramka *pGlowa = 0;
	string nazwaBramki = "";
	string in = "";
	string out = "";
	int wejscieUkladu1 = 0;
	int wejscieUkladu2 = 0;
	int wyjscieUkladu = 0;
	int wejscie1 = 0;
	int wejscie2 = 0;
	int wyjscie = 0;
	
	

	//pierwsze dwie linie pliku z ukladem roznia sie od reszty pliku, dlatego sa odczytywane osobno
	plikUklad >> in >> wejscieUkladu1 >> wejscieUkladu2;
	plikUklad >> out >> wyjscieUkladu;

	//odczyt reszty pliku
	while (plikUklad >> nazwaBramki)
	{
		if (nazwaBramki == "NEG")	//jesli bramka jest typu NEG, to znaczy, ze ma tylko jedno wejscie - odczyt danych musi sie roznic w stosunku do innych bramek
		{
			plikUklad >> wejscie1 >> wyjscie;
			budujGraf(pGlowa, nazwaBramki, wejscie1, wejscie2, wyjscie);
		}
		else
		{
			plikUklad >> wejscie1 >> wejscie2 >> wyjscie;
			budujGraf(pGlowa, nazwaBramki, wejscie1, wejscie2, wyjscie);
		}
	}

	// zmienne konieczne do odczytu danych z pliku ze stanami wejsc
	bramka *tmp = pGlowa;
	string stanyWejsc1;
	string stanyWejsc2;
	string stan1;
	string stan2;
	bool wynik = false;

	while (plikStanyWejsc >> stanyWejsc1 >> stanyWejsc2)
	{
		stan1 = stanyWejsc1.back();	//stany wejsc podane sa w formie wejsce:wartosc - musimy wyluskac ostatnia litere stringa jaka jest wartosc
		stan2 = stanyWejsc2.back();

		ustawStanPoczatkowy(tmp, stan1, stan2, wejscieUkladu1, wejscieUkladu2);	//ustawiamy stan poczatkowy ukladu wedlug wartosci wejsc
		wynik = symulujUklad(tmp);	// symulujemy uklad i sprawdzamy jaka wartosc zwraca

		if (wynik)	//jesli true, to wypisujemy do pliku wyjsciowego odpowiednie dane i zwracana wartosc - 1
		{
			plikWyjsciowy << "IN: " << wejscieUkladu1 << ":" << stan1 << " " << wejscieUkladu2 << ":" << stan2 << " "
				<< "OUT: " << wyjscieUkladu << ":" << 1 << endl;
		}
		else	//jesli false, wypisujemy wartosc - 0
		{
			plikWyjsciowy << "IN: " << wejscieUkladu1 << ":" << stan1 << " " << wejscieUkladu2 << ":" << stan2 << " "
				<< "OUT: " << wyjscieUkladu << ":" << 0 << endl;
		}
	}



	plikUklad.close();	//zamykamy pliki
	plikStanyWejsc.close();
	plikWyjsciowy.close();

	usun(pGlowa);	//usuwamy liste
	delete[] plikiNazwy;	//usuwamy tablice dynamiczna
	cout << endl << "Program wykonany pomyslnie - sprawdz wyniki!" << endl;
	_CrtDumpMemoryLeaks();	//detekcja wyciekow pamieci
	return 0;
}

