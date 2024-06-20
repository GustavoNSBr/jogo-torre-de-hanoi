#include <stdio.h>
#include <stdlib.h>


int main() {

    while (1) {
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
    }

    return 0;
}