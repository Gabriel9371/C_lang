#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define ALTURA 20
#define LARGURA 30

#define TAMANHO_INIT_COBRA 3

typedef struct {
  int linha;
  int coluna;
} Parte;

Parte cobra[TAMANHO_INIT_COBRA];

void init_cobra() {

  int linha_base = ALTURA / 2;
  int coluna_base = LARGURA / 2;

  cobra[0].linha = linha_base;
  cobra[0].coluna = coluna_base;

  cobra[1].linha = linha_base;
  cobra[1].coluna = coluna_base - 1;

  cobra[2].linha = linha_base;
  cobra[2].coluna = coluna_base - 2;
}

void mapa() {

  char mapa[ALTURA][LARGURA];
  for (int i = 0; i < ALTURA; i++) {
    for (int j = 0; j < LARGURA; j++) {
      if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1) {
        mapa[i][j] = '#';
      } else {

        mapa[i][j] = ' ';
      }
    }
  }

  for (int i = TAMANHO_INIT_COBRA - 1; i > 0; i--) {
    cobra[i] = cobra[i - 1];
  }
  cobra[0].coluna += 1;

  for (int i = 0; i < TAMANHO_INIT_COBRA; i++) {
    mapa[cobra[i].linha][cobra[i].coluna] = '@';
  }

  for (int i = 0; i < ALTURA; i++) {
    for (int j = 0; j < LARGURA; j++) {
      printf("%c", mapa[i][j]);
    }
    printf("\n");
  }
}
int main() {
  init_cobra();

  while (1) {
    system("clear");
    mapa();
    usleep(200000);
  }
}
