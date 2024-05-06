#include <stdio.h>
#include <stdlib.h>

#include "../headers/types.h"
#include "../headers/functions.h"

void exibirMenu(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	int opcao = 0;

	do {
		limparTela();
		printf("---------- Gerenciador de H�spede ----------\n\n");
		printf("1. Inserir h�spedes em um quarto vazio\n2. Listar h�spedes por ordem alfab�tica\n3. Buscar h�spede\n");
		printf("4. Editar h�spede\n5. Liberar um quarto\n6. Mostrar os n�meros dos quartos vazios\n7. Salvar lista de h�spedes com respectivos quartos em arquivo.\n\n");
		printf("Pressione 0 para sair do programa\n");
		printf("Digite o numero da opcao desejada: ");

		while(scanf("%d", &opcao) != 1) {
			printf("Op��o inv�lida. Digite novamente: ");
			while(getchar() != '\n');
		}

		switch(opcao) {
			case 1:
			{
				limparTela();
				adicionarHospede(quarto, *qtdQuartos);

				system("pause");
				break;
			}
			case 2:
			{
				limparTela();
				int qtdTotalHospedes = 0;
				Hospede* hospede = guardarHospedes(quarto, *qtdQuartos, &qtdTotalHospedes);

				quickSort(hospede, 0, qtdTotalHospedes - 1);
				listarHospedes(hospede, qtdTotalHospedes);

				system("pause");
				break;
			}
			case 3:
			{
				limparTela();
				system("pause");
				break;
			}
			case 4:
			{
				printf("xxx\n");
				// funcionalidade aqui;
				system("pause");
				break;
			}
			case 5:
			{
				printf("xxx\n");
				// funcionalidade aqui;
				system("pause");
				break;
			}
			case 6:
			{
				limparTela();
				exibirQuartosDisponiveis(quarto, *qtdQuartos);

				system("pause");
				break;
			}
			case 7:
				limparTela();
				salvarArquivo(arquivo, quarto, *qtdQuartos);
				system("pause");
				break;

			default:
				break;
		}
	} while(opcao != 0);
}