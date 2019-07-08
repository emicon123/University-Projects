#ifndef SOURCE_H
#define SOURCE_H
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true } bool;
static const double NIESKONCZONOSC = INFINITY;

typedef struct droga;
typedef struct miasto
{
	char *nazwa;
	struct droga * pDrogi; // glowa listy drog z tego miasta
	double dbMinimalnaOdleglosc; // minimalna dotychczas wyznaczona odleglosc do miasta (na poczatku nieskonczonosc)
	struct miasto * pPoprzednik; // poprzednie miasto w najkrotszej trasie
	bool bPrzeanalizowane; // jezeli true, to znaczy ze znamy minimalna odleglosc dla tego miasta
	struct miasto * pNext; // nastepne miasto w liscie miast
} miasto;

typedef struct droga
{
	char *nazwa;
	double dlugosc; // dlugosc drogi :-)
	struct miasto * pDokad; // miasto docelowe  
	struct droga * pNext; // nastepna droga z miasta
} droga;

void buduj_graf(struct miasto ** pHead);
miasto *znajdz_adres_miasta_poczatkowego(miasto **pHead, char poczatkowe[]);
miasto *znajdz_adres_miasta_koncowego(miasto **pHead, char koncowe[]);
void dodaj_droge(miasto **pHeadMP, miasto **pHeadMK, double odleglosc);

#endif
