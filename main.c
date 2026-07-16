#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// procedimento para sortear n bombas
void sortear_bombas(int n) {
  int i;
  srand(time(NULL));
  for (i = 0; i <= n; i++) {
    l = rand() % tam;
    c = rand() % tam;
    if (jogo[l][c].eh_bomba == 0) {
      jogo[l][c].eh_bomba = 1;
    } else {
      i--;
    };
  }
}

int main(void) {
  printf("Hello, World!\n");
  inicializar_jogo();
  sortear_bombas(10);
  return 0;
}
