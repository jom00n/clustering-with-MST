#ifndef VETOR_H
#define VETOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Vetor Vetor;

int vetor_compara(const void *v1, const void *v2);
Vetor *cria_vetor(double *coordenadas, char *id);
void liberar_vetor(Vetor *v);
Vetor **cria_vetores(int qtd_vetores);
void printa_coordenadas(Vetor* v, int qtd_coordenadas);
Vetor **separa_mais_espaco_vetores(Vetor **vetores, int qtd_vetores);
double vetor_calcula_distancia(Vetor *v1, Vetor *v2, int qtd_coordenadas);
void printa_vetor(Vetor *v, FILE *saida);
#endif