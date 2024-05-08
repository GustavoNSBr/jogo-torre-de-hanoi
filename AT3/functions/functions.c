#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

#include "../include/types.h"
#include "../include/functions.h"

// L� o arquivo e salva as informa��es na struct Quarto;
void lerArquivo(FILE* arquivo, Quarto* quarto, int* qtdQuartos) {
	while(fscanf(arquivo, "%d;%[^;\n];", &quarto[*qtdQuartos].num, quarto[*qtdQuartos].status) != EOF) {
		quarto[*qtdQuartos].qtdHospede = 0;

		while(fscanf(arquivo, "%[^;\n];", quarto[*qtdQuartos].hospede[quarto[*qtdQuartos].qtdHospede].nome) == 1) {
			quarto[*qtdQuartos].qtdHospede++;

			if(quarto[*qtdQuartos].qtdHospede >= (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) break;
		}

		(*qtdQuartos)++;
	}
}

// Pega as informa��es da struct Quarto e salva no arquivo;
void salvarArquivo(FILE* arquivo, Quarto* quarto, int qtdQuartos) {
	arquivo = fopen(CAMINHO_ARQUIVO, "w");

	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < qtdQuartos; i++) {
			if(quarto[i].num != 0) {
				fprintf(arquivo, "%d;%s", quarto[i].num, quarto[i].status);

				for(int j = 0; j < quarto[i].qtdHospede; j++) {
					fprintf(arquivo, ";%s", quarto[i].hospede[j].nome);
				}

				fprintf(arquivo, "\n");
			}
		}

		fclose(arquivo);

		printf("Arquivo salvo com sucesso!\n");
	}
}

void exibirQuartosDisponiveis(Quarto* quarto, int qtdQuartos) {
	printf("Quartos dispon�veis:\n");
	for(int i = 0; i < qtdQuartos; i++) {
		if(strcmp(quarto[i].status, "Disponivel") == 0) {
			printf(" %d |", quarto[i].num);
		}
	}
	printf("\n\n");
}

void adicionarHospede(Quarto* quarto, int qtdQuartos) {
   // Exibindo quartos dispon�veis;
	exibirQuartosDisponiveis(quarto, qtdQuartos);

	int numQuarto = 0;

	printf("Insira o n�mero do quarto: ");
	while(scanf("%d", &numQuarto) != 1 || numQuarto < 1 || numQuarto > QTD_MAX_QUARTOS) {
		printf("N�mero inv�lido. Insira um n�mero v�lido: ");
		while(getchar() != '\n');
	}

	// Verificando se o quarto est� dispon�vel;
	if(strcmp(quarto[numQuarto - 1].status, "Disponivel") == 0) {
		Hospede* hospede = (Hospede*) malloc(sizeof(Hospede));

		if(hospede == NULL) {
			printf("Erro ao alocar mem�ria. Encerrando o programa...");
			exit(1);
		} else {
			printf("Digite o nome do hospede: ");
			while(scanf(" %[^\n]", hospede->nome) != 1) {
				printf("Erro ao ler o nome do h�spede, tente novamente: ");
				while(getchar() != '\n');
			};

			// Adicionando h�spede ao quarto e incrementando a quantidade total de h�spedes do quarto;
			quarto[numQuarto - 1].hospede[quarto[numQuarto - 1].qtdHospede] = *hospede;
			quarto[numQuarto - 1].qtdHospede++;

			// Alterando o status do quarto para ocupado;
			if(quarto[numQuarto - 1].qtdHospede == (QTD_MAX_HOSPEDE / QTD_MAX_QUARTOS)) strcpy(quarto[numQuarto - 1].status, "Ocupado");
		}

		// Liberando a mem�ria do hospede;
		free(hospede);
	} else {
		printf("Quarto n�o dispon�vel, tente novamente.\n");
	}
}

void trocarValores(Hospede* a, Hospede* b) {
	Hospede temp = *a;
	*a = *b;
	*b = temp;
}

int particionarVetor(Hospede* hospede, int left, int right) {
	Hospede pivot = hospede[right];
	int i = left - 1;

	for(int j = left; j < right; j++) {
		Hospede* A = &hospede[j];
		Hospede* B = &pivot;

		if(strcmp(A->nome, B->nome) <= 0) {
			i++;
			trocarValores(&hospede[i], &hospede[j]);
		}
	}

	trocarValores(&hospede[i + 1], &hospede[right]);
	return i + 1;
}

void quickSort(Hospede* hospede, int left, int right) {
	if(left < right) {
		int p = particionarVetor(hospede, left, right);

		quickSort(hospede, left, p - 1);
		quickSort(hospede, p + 1, right);
	}
}

// Aloca todos os h�spedes em uma struct Hospede;
Hospede* guardarHospedes(Quarto* quarto, int qtdQuartos, int* qtdTotalHospedes) {
	Hospede* hospede = (Hospede*) malloc(QTD_MAX_HOSPEDE * sizeof(Hospede));

	if(hospede == NULL) {
		printf("Erro ao alocar mem�ria. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < qtdQuartos; i++) {
			for(int j = 0; j < quarto[i].qtdHospede; j++) {
				hospede[*qtdTotalHospedes] = quarto[i].hospede[j];

				(*qtdTotalHospedes)++;
			}
		}
	}

	return hospede;
}

void listarHospedes(Hospede* hospede, int qtdHospedes) {
	printf("H�spedes:\n\n");

	for(int i = 0; i < qtdHospedes; i++) {
		printf("%d� - %s\n", i + 1, hospede[i].nome);
	}

	printf("\n");
}


// TODO: Arrumar o retorno da fun��o e excluir printf() dela;
char* buscarHospedePorNome(Quarto* quarto, int qtdQuartos) {
	char nome[MAX_CHAR], nomeNovo[MAX_CHAR];
	int encontrado = 0;

	printf("Digite o nome do hospede a ser buscado: ");
	scanf(" %[^\n]", nome);

	for(int i = 0; i < qtdQuartos; i++) {
		for(int j = 0; j < quarto[i].qtdHospede; j++) {
			if(strcmp(quarto[i].hospede[j].nome, nome) == 0) {
				strcpy(nomeNovo, quarto[i].hospede[j].nome);
				printf("H�spede encontrado:\n");
				printf("Quarto: %d\n", quarto[i].num);
				printf("Nome: %s\n", quarto[i].hospede[j].nome);
				encontrado = 1;
				break;
			}
		}
		if(encontrado) break;
	}

	if(!encontrado) {
		printf("H�spede n�o encontrado.\n");
	}
	return nomeNovo;
}

void quartoVazio(Quarto* quarto, int qtdHospede) {
  for (int i = 0; i < QTD_MAX_QUARTOS; i++) {
    if (quarto[i].qtdHospede == 0) {
      printf("%d\n", quarto[i].num);

    } else {
      continue;
    }
  }
}

//--------------------------------------- FUN��ES PARA FINS DE DESENVOLVIMENTO ---------------------------------------//

// Alocar quartos no arquivo (Aloca todos os quartos como dispon�vel e deleta os h�spedes);
void alocarQuartos(FILE* arquivo) {
	arquivo = fopen(CAMINHO_ARQUIVO, "w");

	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		for(int i = 0; i < QTD_MAX_QUARTOS; i++) {
			fprintf(arquivo, "%d;Disponivel\n", i + 1);
		}
	}

	fclose(arquivo);
}

// Exibe informa��es da struct Quarto;
void exibirQuartos(Quarto* quarto, int qtdQuartos) {
	for(int i = 0; i < qtdQuartos; i++) {
		printf("N� do quarto: %d\n", quarto[i].num);
		printf("Status: %s\n", quarto[i].status);
		printf("N� de h�spedes: %d\n", quarto[i].qtdHospede);

		if(quarto[i].qtdHospede > 0) {
			printf("H�spedes:\n");
			for(int j = 0; j < quarto[i].qtdHospede; j++) {
				printf(" - %s\n", quarto[i].hospede[j].nome);
			}
		}

		printf("\n====================\n\n");
	}
}

//-------------------------------------------------------------------------------------------------------------------//

// Limpa a tela do console;
void limparTela() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

// Pausa a tela do console;
void pausarTela() {
	printf("Pressione ENTER para continuar...\n");
	while(getchar() != '\n');
	getchar();
}

// Configura o ambiente de execu��o;
void configurarAmbiente() {
	#ifdef _WIN32
	system("color 0A");
	system("title Gerenciamento de Hotel");
	#endif

	char* local = setlocale(LC_ALL, NULL);

	printf("Configurando a localidade:\n\n");
	printf("Localidade padr�o do sistema: %s\n", local);

	if(local != NULL && strcmp(local, "Portuguese_Brazil.1252") == 0) {
		printf("Localidade j� est� configurada!\n\n");
	} else {
		#ifdef _WIN32
		printf("Configurando a localidade para Portugu�s do Brasil...\n");
		printf("Localidade configurada para %s com sucesso!\n\n", setlocale(LC_ALL, "Portuguese"));
		#elif __linux__
		printf("Configurando a localidade para Portugu�s do Brasil...\n");
		printf("Localidade configurada para %s com sucesso!\n\n", setlocale(LC_ALL, "pt_BR.UTF-8"));
		#endif
	}

	pausarTela();
}

//-------------------------------------------------------------------------------------------------------------------//