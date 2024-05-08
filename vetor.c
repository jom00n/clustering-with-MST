#include "vetor.h"


struct Vetor {
  double *coordenadas;
  char *identificador;
};

int vetor_compara(const void *v1, const void *v2){
  const Vetor *const *vetor1 = v1;
  const Vetor *const *vetor2 = v2;
  
  return strcmp((*vetor1)->identificador, (*vetor2)->identificador);
}

Vetor *cria_vetor(double *coordenadas, char *id) {
  Vetor *v = (Vetor *)malloc(sizeof(Vetor));
  v->coordenadas = coordenadas;
  v->identificador = id;
  return v;
}

Vetor **cria_vetores(int qtd_vetores) {
  return (Vetor **)malloc(qtd_vetores * sizeof(Vetor *));
}

Vetor **separa_mais_espaco_vetores(Vetor **vetores, int qtd_vetores) {
  return (Vetor **)realloc(vetores, qtd_vetores * sizeof(Vetor *));
}

void printa_coordenadas(Vetor* v, int qtd_coordenadas){
  for(int i = 0; i < qtd_coordenadas; i++){
    printf("%lf ", v->coordenadas[i]);
  }
}

double vetor_calcula_distancia(Vetor *v1, Vetor *v2, int qtd_coordenadas){
  double dist = 0, soma = 0;

  for(int i = 0; i < qtd_coordenadas; i++){
    soma += pow(v1->coordenadas[i] - v2->coordenadas[i], 2);
  }
  dist = sqrt(soma);
  return dist;
}


void printa_vetor(Vetor *v, FILE *saida) {
  fprintf(saida, "%s", v->identificador);
}

void liberar_vetor(Vetor *v) {
  free(v->coordenadas);
  free(v->identificador);
  free(v);
}