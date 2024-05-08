#include <stdio.h>
#include <malloc.h>

#include "./include/types.h"
#include "./include/functions.h"

// TODO: Criar fun��o para buscar h�spede pelo nome (possuir retorno pois ser� utilizado na fun��o para editar um h�spede);
// TODO: Criar um README.md com as instru��es de como compilar e executar o programa;
// TODO: Criar uma fun��o para editar determinado h�spede;
// TODO: Criar fun��o para exibir os quartos vazios;

// Fun��o principal;
int main(void) {
	// Configurando o ambiente de execu��o;
	configurarAmbiente();

	FILE* arquivo = fopen(CAMINHO_ARQUIVO, "r");

	if(arquivo == NULL) {
		printf("N�o foi poss�vel abrir o arquivo. Encerrando o programa...\n");
		return 1;
	} else {
		Quarto* quarto = (Quarto*) malloc(QTD_MAX_QUARTOS * sizeof(Quarto));

		if(quarto == NULL) {
			printf("N�o foi poss�vel alocar a mem�ria. Encerrando o programa...\n");
			exit(1);
		} else {
			int qtdQuartos = 0;

			// Lendo o arquivo e salvando as informa��es na struct Quarto;
			lerArquivo(arquivo, quarto, &qtdQuartos);

			// Exibindo o menu principal;
			exibirMenu(arquivo, quarto, &qtdQuartos);
		}

		// Liberando mem�ria alocada;
		free(quarto);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");
	return 0;
}