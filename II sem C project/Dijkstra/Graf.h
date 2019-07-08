#ifndef GRAF_H
#define GRAF_H
#include"Source.h"

void buduj_graf(struct miasto ** pHead);
miasto *znajdz_adres_miasta_poczatkowego(struct miasto **pHead, char poczatkowe[]);
miasto *znajdz_adres_miasta_koncowego(struct miasto **pHead, char koncowe[]);
void dodaj_droge(struct miasto **pHeadMP, struct miasto **pHeadMK, double odleglosc);

#endif