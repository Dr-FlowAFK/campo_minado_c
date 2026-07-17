

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
// procedimento para imprimir o jogo
void imprimir() {
  printf("\n\n\t   ");
  for (l = 0; l < tam; l++) {
    printf("  %d   ", l); // indices das colunas
  }
  printf("\n\t  -------------------------------------------------------------\n");
  for (l = 0; l < tam; l++) {
    printf("\t%d | ", l);
    for (c = 0; c < tam; c++) {
      if (jogo[l][c].esta_aberta) {
        if (jogo[l][c].eh_bomba) {
          printf(" * ");
        } else {
          printf(" %d ", jogo[l][c].vizinhos);
        }
      } else {
        printf("   ");
      }
      printf(" | ");
    }
    printf("\n\t  -------------------------------------------------------------\n");
  }
}
// procedimento para abrir a coordenada digitada pelo usuario
void abrir_celula(int linha, int coluna) {
  if (coordenada_valida(linha, coluna) && !jogo[linha][coluna].esta_aberta) {
    jogo[linha][coluna].esta_aberta = 1;
    if (jogo[linha][coluna].vizinhos == 0) {
      /*
       * l-1 e c cima
       * l+1 e c abaixo
       * l e c+1 direita
       * l e c-1 esquerda
       */
      abrir_celula(linha - 1, coluna);
      abrir_celula(linha + 1, coluna);
      abrir_celula(linha, coluna + 1);
      abrir_celula(linha, coluna - 1);
    }
  }
}
/*
 * funçao para verificar vitoria
 */
int ganhou() {
  int qtd = 0;
  for (l = 0; l < tam; l++) {
    for (c = 0; c < tam; c++) {
      if (!jogo[l][c].esta_aberta && !jogo[l][c].eh_bomba) {
        qtd++;
      }
    }
  }
  return qtd;
}
// procedimento jogar que faz a leitura das coordenadas
void jogar() {
  int linha , coluna;
  do {
    imprimir();
    do {
      printf("\n Digite as coordenadas de linha e coluna: ");
      scanf("%d%d", &linha, &coluna);
      if (!coordenada_valida(linha, coluna)) {
        printf("\n Coordenada invalida!");
      }
    }while (!coordenada_valida(linha, coluna) || jogo[linha][coluna].esta_aberta);
    abrir_celula(linha, coluna);
  }while (ganhou() != 0 && jogo[linha][coluna].eh_bomba == 0);
  imprimir();
  if (jogo[linha][coluna].eh_bomba == 1) {
    printf("\t Que pena! Voce perdeu!!!\n");
  }else {
    printf("\t PARABENS VOCE GANHOU!!!\n");
  }
}
int main(void) {
  int opcao;
  do {
    inicializar_jogo();
    sortear_bombas(10);
    contar_bombas();
    printf("\n\t\t\t\tCAMPO MINADO");
    jogar();
    printf("\n Digite 1 para jogar novamente: ");
    scanf("%d", &opcao);
  }while (opcao == 1);
  return 0;
}