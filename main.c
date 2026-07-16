#include <stdio.h>

typedef struct {
  int eh_bomba;
  int esta_aberta;
  int vizinhos;
} Celula;

// variaveis globais
Celula jogo[10][10];
int l, c, tam = 10;

// procedimento para inicializar a matriz do jogo
void inicializar_jogo() {
  for (l = 0; l < tam; l++) {
    for (c = 0; c < tam; c++) {
      jogo[l][c].eh_bomba = 0;
      jogo[l][c].esta_aberta = 0;
      jogo[l][c].vizinhos = 0;
    }
  }
}

int main(void) {
  printf("Hello, World!\n");
  return 0;
}
