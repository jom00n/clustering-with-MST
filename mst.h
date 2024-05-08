#ifndef MST_H
#define MST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Mst Mst;

Mst *cria_mst(int tam);
int une_grupos(Mst *mst, int p1, int p2);
void libera_mst(Mst *mst);
int retorna_profundidade(Mst *mst, int ponto);
int encontra_pai(Mst *mst, int ponto);

#endif