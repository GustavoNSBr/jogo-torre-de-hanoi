#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Função para imprimir o estado das torres
void imprimir(Pilha *torres, int qtd_blocos) {
    int i, j;

    for (i = qtd_blocos - 1; i >= 0; i--) {
        for (j = 0; j < 3; j++) {
            // Pilha j
            if (tamanho(&torres[j]) > i) {
                printf("|%d|", torres[j].itens[i]);
            } else {
                printf("|*|");
            }

            printf("\t");
        }
        printf("\n");
    }

    printf("|A|\t|B|\t|C|\n\n");
}


// Função para mover os blocos
void mover_blocos(Pilha *torres, int qtd_blocos) {
    int opcao, destino;

    while (1) {
        // Imprimir o estado das torres
        limpar_tela();
        imprimir(torres, qtd_blocos);

        // Menu de opções
        printf("Qual torre escolher?\n");
        for (int i = 0; i < 3; i++) {
            printf("%d: Torre %c\n", i + 1, 'A' + i);
        }
        printf("4: Voltar ao menu inicial\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 4) {
            break;
        }

        if (!validar_opcao(opcao, 3)) {
            printf("Escolha invalida, tente novamente:\n");
            limpar_tela();
            continue;
        }

        printf("Mover para qual torre?\n");
        for (int i = 0; i < 3; i++) {
            if (i + 1 != opcao) {
                printf("%d: Torre %c\n", i + 1, 'A' + i);
            }
        }
        printf("Opcao: ");
        scanf("%d", &destino);

        if (!validar_opcao(destino, 3) || destino == opcao) {
            printf("Escolha invalida, tente novamente:\n");
            limpar_tela();
            continue;
        }

        // Movimentar bloco
        if (tamanho(&torres[opcao - 1]) == 0) {
            printf("Movimento invalido! Torre de origem vazia.\n");
        } else if (tamanho(&torres[destino - 1]) == 0 || topo(&torres[opcao - 1]) < topo(&torres[destino - 1])) {
            empilhar(&torres[destino - 1], desempilhar(&torres[opcao - 1]));
        } else {
            printf("Movimento invalido! Bloco maior na torre de destino.\n");
        }

        limpar_tela();
    }
}

// Função principal
int main() {
    int opcao, qtd_blocos;

    while (1) {
        // Menu de opções inicial
        limpar_tela();
        printf("Escolha uma opcao:\n");
        printf("1: Jogar\n");
        printf("2: Regras do Jogo\n");
        printf("3: Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                break;

            case 2:
                exibir_regras();
                continue;

            case 3:
                printf("Saindo do jogo.\n");
                return 0;

            default:
                printf("Opcao invalida. Saindo do jogo.\n");
                return 0;
        }

        // Escolher a quantidade de blocos
        limpar_tela();
        printf("Escolha a quantidade de blocos para o jogo (de 4 a 7):\n");
        printf("4: Besta (4 blocos)\n");
        printf("5: Facil (5 blocos)\n");
        printf("6: Medio (6 blocos)\n");
        printf("7: Dificil (7 blocos)\n");
        printf("Opcao: ");
        scanf("%d", &qtd_blocos);

        while (qtd_blocos < 4 || qtd_blocos > 7) {
            printf("Escolha invalida, tente novamente:\n");
            limpar_tela();
            printf("Opcao: ");
            scanf("%d", &qtd_blocos);
        }

        Pilha torres[3];

        for (int i = 0; i < 3; i++) {
            torres[i] = criar();
        }

        // Inicialização da primeira torre com os blocos
        for (int bloco = qtd_blocos; bloco >= 1; bloco--) {
            empilhar(&torres[0], bloco);
        }

        // Jogar o jogo
        mover_blocos(torres, qtd_blocos);
    }

    return 0;
}
