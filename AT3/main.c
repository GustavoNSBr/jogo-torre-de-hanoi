#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "guest.h"

int main(void) {
	configEnviroment();

	FILE* file = fopen(FILE_PATH, "r");

	if(file == NULL) {
		printf("N�o foi poss�vel abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		Room* room = (Room*) malloc(ROOMS * sizeof(Room));

		if(room == NULL) {
			printf("N�o foi poss�vel alocar a mem�ria. Encerrando o programa...\n");
			exit(1);
		} else {
			int num = 0;
			// Lendo o arquivo e salvando as informa��es na struct Room;
			readFile(file, room, &num);

			// TODO: criar um menu interativo;

			// Exibindo os dados da struct;
			showRooms(room, num);
		}

		// Liberando mem�ria alocada;
		free(room);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(file);
	printf("Programa encerrado com sucesso!\n");

	system("pause");
	return 0;
}

static void readFile(FILE* file, Room* room, int* num) {
	while(fscanf(file, "%d;%[^;\n]", &room[*num].number, room[*num].status) != EOF) {
		room[*num].guestSize = 0;

		while(fscanf(file, ";%[^;\n]\n", room[*num].guest[room[*num].guestSize].name) == 1) {
			room[*num].guestSize++;

			if(room[*num].guestSize >= 4) break;
		}

		(*num)++;
	}
}

static void saveFile(FILE* file, Room* room) {
	file = fopen(FILE_PATH, "w");

	if(file == NULL) {
		printf("Erro ao abrir o arquivo. Encerrando o programa...\n");
		exit(1);
	} else {
		// TODO: criar l�gica para salvar as modifica��es da struct Room no arquivo;
	}
}

// Exibe informa��es da struct;
static void showRooms(Room* room, int num) {
	for(int i = 0; i < num; i++) {
		printf("Quarto N�: %d\n", room[i].number);
		printf("Status: %s\n", room[i].status);
		printf("N� de h�spedes: %d\n", room[i].guestSize);

		if(room[i].guestSize > 0) {
			printf("\nH�spedes:\n");
			for(int j = 0; j < room[i].guestSize; j++) {
				printf(" - %s\n", room[i].guest[j].name);
			}
		}

		printf("\n====================\n\n");
	}
}

static void clearScreen() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

static void configEnviroment() {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Gerenciamento de Hotel");
}
