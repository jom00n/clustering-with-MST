#include "mst.h"
#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compara_distancia(const void *d1, const void *d2) {
  const double *dist1 = *(const double **)d1;
  const double *dist2 = *(const double **)d2;
  if (dist1[2] < dist2[2]) {
    return -1;
  }
  if (dist1[2] > dist2[2]) {
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  
  clock_t inicio, fim;
  
  FILE *entrada = fopen(argv[1], "r");
  int qtd_agrupamentos = atoi(argv[2]);
  char *linha = NULL;
  size_t tamanho = 0;
  int qtd_coordenadas = 0, qtd_vetores = 0, qtd_max_vetores = 100,
      qtd_max_coordenadas =2;
  char *reparticoes = NULL;
  double *coordenadas = NULL;

  // leitura de arquivo texto e criaçao de vetores.
  Vetor **vetores = cria_vetores(qtd_max_vetores);
  while (getline(&linha, &tamanho, entrada) != -1) {
    // aumenta espaço para vetores
    if (qtd_vetores >= qtd_max_vetores) {
      qtd_max_vetores *= 2;
      vetores = separa_mais_espaco_vetores(vetores, qtd_max_vetores);
    }

    // lê identificador
    char *id = strtok(linha, ",");
    id = strdup(id);

    if (qtd_coordenadas == 0) {

      reparticoes = strtok(NULL, ",");
      coordenadas = (double *)malloc(qtd_max_coordenadas * sizeof(double));
      coordenadas[qtd_coordenadas] = atof(reparticoes);
      qtd_coordenadas++;

      reparticoes = strtok(NULL, ",");
      while (reparticoes) {
        // separa espaço para as coordenadas
        if (qtd_coordenadas >= qtd_max_coordenadas) {
          qtd_max_coordenadas += 2;
          coordenadas = (double *)realloc(coordenadas, qtd_max_coordenadas * sizeof(double));
        }

        coordenadas[qtd_coordenadas] = atof(reparticoes);
        qtd_coordenadas++;
        reparticoes = strtok(NULL, ",");
      }

    }//apos a primeira, separa o espaço necessario para as coordenadas de uma só vez 
    else {
      coordenadas = (double *)malloc(qtd_coordenadas * sizeof(double));
      for (int i = 0; i < qtd_coordenadas; i++) {
        coordenadas[i] = atof(strtok(NULL, ","));
      }
    }

    vetores[qtd_vetores] = cria_vetor(coordenadas, id);
    qtd_vetores++;
  }
  
  qsort(vetores, qtd_vetores, sizeof(Vetor *), vetor_compara);

  // libera string de leitura
  free(linha);
  fclose(entrada);
  
  // cria matriz para armazenar as distancias,
  int qtd_distancias = qtd_vetores * (qtd_vetores - 1) / 2;
  double **distancias = (double **)malloc(qtd_distancias * sizeof(double *));

  for (int i = 0; i < qtd_distancias; i++) {
    distancias[i] = (double *)malloc(3 * sizeof(double));
  }
  
  // calcula distancias e armazena na matriz
  int k = 0;
  for (int i = 0; i < qtd_vetores; i++) {
    for (int j = 0; j < qtd_vetores; j++) {
      if (j < i) {
        distancias[k][0] = i;
        distancias[k][1] = j;
        distancias[k][2] =
            vetor_calcula_distancia(vetores[i], vetores[j], qtd_coordenadas);
        k++;
      }
    }
  }

  // ordena matriz de distancias

  qsort(distancias, qtd_distancias, sizeof(double *), compara_distancia);

  // cria mst
  Mst *tree = cria_mst(qtd_vetores);

  int arestas = 0;
  // cria arestas
  for (int i = 0; i < qtd_distancias && arestas < (qtd_vetores - qtd_agrupamentos); i++) {
    if (une_grupos(tree, distancias[i][0], distancias[i][1])) {
      arestas++;
    }
  }

  FILE *saida = fopen(argv[3], "w");

  // cria vetor para armazenar todos os grupos a serem visitados, com o intuito de facilitar a identificaçao destes
  int grupos_visitados[qtd_agrupamentos];
  for (int i = 0; i < qtd_agrupamentos; i++) {
    grupos_visitados[i] = -1;
  }
  int conta_grupos = 0;
  grupos_visitados[conta_grupos++] = encontra_pai(tree, 0);
   
  // printa grupos

  for (int i = 0; i < qtd_agrupamentos; i++) {
    int aux = grupos_visitados[i];
    int contador = 0, profundidade = retorna_profundidade(tree, aux);
    for (int j = 0; j < qtd_vetores; j++) {
      if (encontra_pai(tree, j) == aux) {
        printa_vetor(vetores[j], saida);
        contador++;
        if (contador < profundidade)
          fprintf(saida, ",");
      } 
      // armazena os grupos que ainda nao foram visitados
      else {
        if (i == 0) {
          int pai = encontra_pai(tree, j);
          int l = 0;
          while (l < qtd_agrupamentos && grupos_visitados[l] != pai) {
            l++;
          }
          if (l >= qtd_agrupamentos) {
            grupos_visitados[conta_grupos++] = pai;
          }
        }
      }
    }
    if (i < qtd_agrupamentos - 1) {
      fprintf(saida, "\n");
    }
  }
  
  // liberaçao de memoria
  for (int i = 0; i < qtd_vetores; i++) {
    liberar_vetor(vetores[i]);
  }

  for (int i = 0; i < qtd_distancias; i++) {
    free(distancias[i]);
  }
  libera_mst(tree);
  free(distancias);
  free(vetores);
  fclose(saida);
  
  return 0;
}