#ifndef PILHA_H
#define PILHA_H

typedef struct Pilha {
    int itens[100];  // Capacidade máxima da pilha
    int topo;        // Índice do topo da pilha
} Pilha;

Pilha criar();
int vazia(Pilha *p);
void empilhar(Pilha *p, int disco);
int desempilhar(Pilha *p);
int topo(Pilha *p);
int tamanho(Pilha *p);

#endif
