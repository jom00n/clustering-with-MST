#include "mst.h"

struct Mst {
  int *grupos;
  int tam;
  int *profundidade;
};

Mst *cria_mst(int tam) {
  Mst *mst = (Mst *)malloc(sizeof(Mst));
  mst->grupos = (int *)malloc(tam * sizeof(int));
  mst->profundidade = (int *)malloc(tam * sizeof(int));

  // inicializa profundidade
  for (int i = 0; i < tam; i++) {
    mst->profundidade[i] = 1;
  }
  // inicializa os grupos
  for (int i = 0; i < tam; i++) {
    mst->grupos[i] = i;
  }
  mst->tam = tam;
  return mst;
}

int encontra_pai(Mst *mst, int ponto) {
  while (mst->grupos[ponto] != ponto){
    mst->grupos[ponto] = mst->grupos[mst->grupos[ponto]];
    ponto = mst->grupos[ponto];
  }
  return ponto;
}

int une_grupos(Mst *mst, int p1, int p2) {
  int i = encontra_pai(mst, p1);
  int j = encontra_pai(mst, p2);

  if (i == j) {
    return 0;
  }

  if (mst->profundidade[i] < mst->profundidade[j]) {
    mst->grupos[i] = j;
    mst->profundidade[j] += mst->profundidade[i];
  } else {
    mst->grupos[j] = i;
    mst->profundidade[i] += mst->profundidade[j];
  }
  return 1;
}

int retorna_profundidade(Mst *mst, int ponto){
  return mst->profundidade[encontra_pai(mst, ponto)];
}

void printa_grupos(Mst *mst) {}

void libera_mst(Mst *mst) {
  free(mst->grupos);
  free(mst->profundidade);
  free(mst);
}