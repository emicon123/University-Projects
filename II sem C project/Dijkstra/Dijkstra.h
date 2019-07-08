#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include"Source.h"

void wypisz_trase(miasto **pHead, miasto **poczatek, FILE * plikWyznacz);
bool dijkstra(struct miasto ** pHead, FILE * plikWyznacz, char poczatkowe[], char koncowe[]);

#endif
