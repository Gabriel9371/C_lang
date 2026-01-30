#include "stdio.h"

#define ALTURA 20
#define LARGURA 30

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

  for (int i = 0; i < ALTURA; i++) {
    for (int j = 0; j < LARGURA; j++) {
      printf("%c", mapa[i][j]);
    }
    printf("\n");
  }
}
int main() {

  /// não quebre a porra da minha linha neovim
  mapa();
}
