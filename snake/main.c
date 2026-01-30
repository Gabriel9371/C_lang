#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

//-=-=fis isso usando chatGPT pois não sei como fazer :) -=-=
#include <fcntl.h>
#include <termios.h>
void conf_terminal() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);

  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

  /*
    Pelo que intendi isso faz com que
    o terminal não espere eu dar enter
    pra poder executar algo, e o ECHO
    impede que os comndos pra mover a cobra
    como W,A,S,D não fiquem aparecendo
  */
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define ALTURA 20
#define LARGURA 30

#define TAMANHO_INIT_COBRA 3

typedef struct {
  int linha;
  int coluna;
} Parte;

Parte cobra[TAMANHO_INIT_COBRA];

typedef enum {

  CIMA,
  BAIXO,
  ESQUERDA,
  DIREITA

} Direcao;

Direcao direcao;

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
  if (direcao == DIREITA)
    cobra[0].coluna++;
  if (direcao == ESQUERDA)
    cobra[0].coluna--;
  if (direcao == CIMA)
    cobra[0].linha--;
  if (direcao == BAIXO)
    cobra[0].linha++;

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

  direcao = ESQUERDA;

  conf_terminal();
  while (1) {
    char tecla;
    if (read(STDIN_FILENO, &tecla, 1) > 0) {
      if (tecla == 'w')
        direcao = CIMA;
      if (tecla == 'a')
        direcao = ESQUERDA;
      if (tecla == 's')
        direcao = BAIXO;
      if (tecla == 'd')
        direcao = DIREITA;
    }
    system("clear");
    mapa();
    usleep(200000);
  }
}
