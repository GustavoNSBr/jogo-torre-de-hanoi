#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

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

// Função para limpar a tela
void limpar_tela() {
    #ifdef _WIN32
        system("pause");
        system("cls");
    #else
        system("read -n1 -r -p 'Pressione qualquer tecla para continuar...' key");
        system("clear");
    #endif
}

// Função para validar a entrada do usuário
int validar_opcao(int opcao, int max_opcao) {
    return opcao >= 1 && opcao <= max_opcao;
}

// Função para exibir as regras do jogo
void exibir_regras() {
    limpar_tela();
    printf("\nRegras do Jogo:\n");
    printf("1. Apenas um disco pode ser movido por vez.\n");
    printf("2. Um disco maior nao pode ficar em cima de um disco menor.\n");
    printf("3. Todos os discos devem ser movidos da torre A para a torre C.\n\n");
    printf("Pressione qualquer tecla para voltar ao menu inicial.\n");
    getchar();  // Captura o caractere extra do buffer
}

// Função para mover os blocos
void mover_blocos(Pilha *torres, int qtd_blocos) {
    int opcao, destino;

    while (1) {
        // Imprimir o estado das torres
        limpar_tela();
        imprimir(torres, qtd_blocos);

        // Menu de opções
        printf("Qual torre origem?\n");
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
        printf("4: Noob (4 blocos)\n");
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
