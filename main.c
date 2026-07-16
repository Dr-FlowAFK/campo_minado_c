#include <cstddef>
#include <istream>
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

/*
 * funçao que diz se um par de coordenadas é valido ou nao
 */
int coordenada_valida(int l, int c) {
  if (l >= 0 && l < tam && c >= 0 && c < tam) {
    return 1;
  } else {
    return 0;
  }
}

/*
 * funçao que retorna a quantidade de bombas na vizinhança de l c
 */
int qtd_bombas_na_vizinhanca(int l, int c) {
  int qtd = 0;
  if (coordenada_valida(l - 1, c) && jogo[l - 1][c].eh_bomba) {
    qtd++;
  } else if (coordenada_valida(l + 1, c) && jogo[l + 1][c].eh_bomba) {
    qtd++;
  } else if (coordenada_valida(l, c + 1) && jogo[l][c + 1].eh_bomba) {
    qtd++;
  } else if (coordenada_valida(l, c - 1) && jogo[l][c - 1].eh_bomba) {
    qtd++;
  }
  return qtd;
}

// procedimento para contar as bombas vizinhas
void contar_bombas() {
  for (l = 0; l < tam; l++) {
    for (c = 0; c < tam; c++) {
      jogo[l][c].vizinhos = qtd_bombas_na_vizinhanca(l, c);
    }
  }
};

int main(void) {
  printf("Hello, World!\n");
  inicializar_jogo();
  sortear_bombas(10);
  contar_bombas();
  return 0;
}
