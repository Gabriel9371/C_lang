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

  int linha_base = ALTURA / 2;
  int coluna_base = LARGURA / 2;
  int col_a = (LARGURA / 2) - 1;
  int col_b = (LARGURA / 2) - 2;
  
  coluna_base += 9;
  col_a += 9;
  col_b += 9;

  mapa[linha_base][coluna_base] = '@';
  mapa[linha_base][col_a] = '@';
  mapa[linha_base][col_b] = '@';


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
