#include "stdio.h"
#include "stdlib.h"
#include "time.h"
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
#define TAM_MAX 100

typedef struct {
  int linha;
  int coluna;
} Parte;

typedef struct {
  int linha;
  int coluna;
} Comida;

Comida comida;

void gen_comida() {

  // -2 e +1 pra não aparecer comida na borda
  comida.linha = rand() % (ALTURA - 2) + 1;
  comida.coluna = rand() % (LARGURA - 2) + 1;
}

Parte cobra[TAM_MAX];
int tamanho_Cobra = 3;

int comeu() {
  return cobra[0].linha == comida.linha && cobra[0].coluna == comida.coluna;
}

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

  for (int i = tamanho_Cobra - 1; i > 0; i--) {
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

  for (int i = 0; i < tamanho_Cobra; i++) {
    mapa[cobra[i].linha][cobra[i].coluna] = '@';
  }

  mapa[comida.linha][comida.coluna] = '*';

  for (int i = 0; i < ALTURA; i++) {
    for (int j = 0; j < LARGURA; j++) {
      printf("%c", mapa[i][j]);
    }
    printf("\n");
  }
}

int bateu_na_parede() {
  if (cobra[0].linha <= 0)
    return 1;
  if (cobra[0].linha >= ALTURA - 1)
    return 1;
  if (cobra[0].coluna <= 0)
    return 1;
  if (cobra[0].coluna >= LARGURA - 1)
    return 1;

  return 0;
}

int direcao_oposta(Direcao atual, Direcao nova) {
  if (atual == CIMA && nova == BAIXO)
    return 1;
  if (atual == BAIXO && nova == CIMA)
    return 1;
  if (atual == ESQUERDA && nova == DIREITA)
    return 1;
  if (atual == DIREITA && nova == ESQUERDA)
    return 1;

  return 0;
}

int main() {
  init_cobra();

  direcao = ESQUERDA;
  Direcao nova;

  srand(time(NULL));
  gen_comida();

  conf_terminal();
  while (1) {
    char tecla;

    if (read(STDIN_FILENO, &tecla, 1) > 0) {
      if (tecla == 'w')
        nova = CIMA;
      if (tecla == 'a')
        nova = ESQUERDA;
      if (tecla == 's')
        nova = BAIXO;
      if (tecla == 'd')
        nova = DIREITA;

      if (!direcao_oposta(direcao, nova)) {
        direcao = nova;
      }
    }
    if (comeu()) {
      cobra[tamanho_Cobra] = cobra[tamanho_Cobra - 1];
      tamanho_Cobra++;
      gen_comida();
    }
    system("clear");
    mapa();

    if (bateu_na_parede()) {
      printf("GAME OVER\n");
      break;
    }

    usleep(100000);
  }
}
