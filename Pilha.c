#include "Pilha.h"

Pilha criar() {
    Pilha p;
    p.topo = -1;  // Pilha vazia inicialmente
    return p;
}

int vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int disco) {
    p->topo++;
    p->itens[p->topo] = disco;
}

int desempilhar(Pilha *p) {
    int disco = p->itens[p->topo];
    p->topo--;
    return disco;
}

int topo(Pilha *p) {
    return p->itens[p->topo];
}

int tamanho(Pilha *p) {
    return p->topo + 1;
}
