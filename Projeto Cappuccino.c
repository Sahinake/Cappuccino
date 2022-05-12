#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#define COR1 1
#define COR2 2
#define COR3 4
#define COR4 6
#define COR5 13
#define CORPADRAO 15

struct Pino{
	int azul;
	int verde;
	int vermelho;
	int amarelo;
};

struct Contagem{
	int azul;
	int verde;
	int vermelho;
	int amarelo;
};

void placar (int *lugar, int *pontuacao) {
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese");
    
    SetConsoleTextAttribute(hConsole, COR5);
    printf("\t\t  FIM DE JOGO!\n");
	SetConsoleTextAttribute(hConsole, CORPADRAO);
	
	for (int i = 0; i < 4; i++) {
		printf("+-------------------------------------------------+\n");
		switch(i) {
			case 0:
				SetConsoleTextAttribute(hConsole, COR5);
				printf("  Primeiro Lugar:  ");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				break;
			case 1:
				SetConsoleTextAttribute(hConsole, COR5);
				printf("  Segundo Lugar:   ");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				break;
			case 2:
				SetConsoleTextAttribute(hConsole, COR5);
				printf("  Terceiro Lugar:  ");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				break;
			case 3:
				SetConsoleTextAttribute(hConsole, COR5);
				printf("  Quarto Lugar:    ");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				break; 
				
		}
		switch(lugar[i]) {
			case 0: 
			SetConsoleTextAttribute(hConsole, COR1);
			printf("Jogador 1 com %d pontos        ", pontuacao[0]);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			break;
			case 1:
			SetConsoleTextAttribute(hConsole, COR2);
			printf("Jogador 2 com %d pontos        ", pontuacao[1]);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			break;
			case 2:
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Jogador 3 com %d pontos        ", pontuacao[2]);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			break;
			case 3:
			SetConsoleTextAttribute(hConsole, COR4);
			printf("Jogador 4 com %d pontos        ", pontuacao[3]);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			break;
		}
		printf("\n+-------------------------------------------------+\n");
	}
	printf("+==============================================================================================================+\n");	
	free(pontuacao);
	free(lugar);
}

void calculo (int **tab, int *pecas) {
	
	int *pontuacao = (int*)malloc(4*sizeof(int)), *lugar = (int*)malloc(4*sizeof(int)), primeiro = 0, quarto = 10, x = 0, y = 0, n = 0;
	
	for(int i = 0; i < 4; i++) {
		pontuacao[i] = 0;
	}
	
	for (int j = 1; j < 6; j++) {
		for(int k = 1; k < 6; k++) {
			switch(pecas[n]) {
				case '\0':
				n++;
				break;
				case 1:
				pontuacao[0] = (pontuacao[0] + tab[j][k]);
				n++;
				break;
				case 2:
				pontuacao[1] = (pontuacao[1] + tab[j][k]);
				n++;
				break;
				case 3:
				pontuacao[2] = (pontuacao[2] + tab[j][k]);
				n++;
				break;
				case 4:
				pontuacao[3] = (pontuacao[3] + tab[j][k]);
				n++;
				break;
			}
		}
	}
	
	for(int j = 3; j >= 0; ) {
		if(pontuacao[j] >= primeiro) {
			primeiro = pontuacao[j];
			lugar[0] = j;
			j--;
		}
		else{
			j--;
		}
	}
	
	for(int j = 3; j >= 0; ) {
		if(pontuacao[j] <= quarto) {
			quarto = pontuacao[j];
			lugar[3] = j;
			j--;
		}
		else{
			j--;
		}
	}	
	
	for(int j = 3; j >= 0; ) {
		if((j != lugar[0]) && (j != lugar[3])) {
			x = pontuacao[j];
			y = j;
		}
		j--;
	}
	
	for(int j = 3; j >= 0; ) {
		if((j != lugar[0]) && (j != lugar[3]) && (j != y)) {
			if(pontuacao[j] > x) {
				lugar[1] = j;
				lugar[2] = y;
			}
			else {
				lugar[1] = y;
				lugar[2] = j;	
			}
		}
		j--;
	}
	placar(lugar, pontuacao);
	free(pecas);
}

int fimPartida (int i, int **tab, int *pecas) {
	int quantidade = 0, num = 0;
	
	if(i == 1) {
		for(int j = 1; j < 6; j++) {
			for(int k = 1; k < 6; ) {
				if(pecas[num] == 1) {
					if((tab[j+1][k-1] != '\0' && tab[j+1][k-1] <= tab[j][k]) || (tab[j+1][k] != '\0' && tab[j+1][k] <= tab[j][k]) || (tab[j+1][k+1] != '\0' && tab[j+1][k+1] <= tab[j][k]) || (tab[j][k-1] != '\0' && tab[j][k-1] <= tab[j][k]) || (tab[j][k+1] != '\0' && tab[j][k+1] <= tab[j][k]) || (tab[j-1][k-1] != '\0' && tab[j-1][k-1] <= tab[j][k]) || (tab[j-1][k] != '\0' && tab[j-1][k] <= tab[j][k]) || (tab[j-1][k+1] != '\0' && tab[j-1][k+1] <= tab[j][k])) {
						quantidade++;	
						k++;
						num++;
					}
					else {
						k++;
						num++;
					}
				}
				else {
					k++;
					num++;
				}
			}
		}
	}
	else if(i == 2) {
		for(int j = 1; j < 6; j++) {
			for(int k = 1; k < 6; ) {
				if(pecas[num] == 2) {
					if((tab[j+1][k-1] != '\0' && tab[j+1][k-1] <= tab[j][k]) || (tab[j+1][k] != '\0' && tab[j+1][k] <= tab[j][k]) || (tab[j+1][k+1] != '\0' && tab[j+1][k+1] <= tab[j][k]) || (tab[j][k-1] != '\0' && tab[j][k-1] <= tab[j][k]) || (tab[j][k+1] != '\0' && tab[j][k+1] <= tab[j][k]) || (tab[j-1][k-1] != '\0' && tab[j-1][k-1] <= tab[j][k]) || (tab[j-1][k] != '\0' && tab[j-1][k] <= tab[j][k]) || (tab[j-1][k+1] != '\0' && tab[j-1][k+1] <= tab[j][k])) {
						quantidade++;
						k++;
						num++;	
					}
					else {
						k++;
						num++;
					}
				}
				else {
					k++;
					num++;
				}
			}
		}
	}
	else if(i == 3) {
		for(int j = 1; j < 6; j++) {
			for(int k = 1; k < 6; ) {
				if(pecas[num] == 3) {
					if((tab[j+1][k-1] != '\0' && tab[j+1][k-1] <= tab[j][k]) || (tab[j+1][k] != '\0' && tab[j+1][k] <= tab[j][k]) || (tab[j+1][k+1] != '\0' && tab[j+1][k+1] <= tab[j][k]) || (tab[j][k-1] != '\0' && tab[j][k-1] <= tab[j][k]) || (tab[j][k+1] != '\0' && tab[j][k+1] <= tab[j][k]) || (tab[j-1][k-1] != '\0' && tab[j-1][k-1] <= tab[j][k]) || (tab[j-1][k] != '\0' && tab[j-1][k] <= tab[j][k]) || (tab[j-1][k+1] != '\0' && tab[j-1][k+1] <= tab[j][k])) {
						quantidade++;
						k++;
						num++;	
					}
					else {
						k++;
						num++;
					}
				}
				else {
					k++;
					num++;
				}
			}
		}
	}
	else {
		for(int j = 1; j < 6; j++) {
			for(int k = 1; k < 6; ) {
				if(pecas[num] == 4) {
				if((tab[j+1][k-1] != '\0' && tab[j+1][k-1] <= tab[j][k]) || (tab[j+1][k] != '\0' && tab[j+1][k] <= tab[j][k]) || (tab[j+1][k+1] != '\0' && tab[j+1][k+1] <= tab[j][k]) || (tab[j][k-1] != '\0' && tab[j][k-1] <= tab[j][k]) || (tab[j][k+1] != '\0' && tab[j][k+1] <= tab[j][k]) || (tab[j-1][k-1] != '\0' && tab[j-1][k-1] <= tab[j][k]) || (tab[j-1][k] != '\0' && tab[j-1][k] <= tab[j][k]) || (tab[j-1][k+1] != '\0' && tab[j-1][k+1] <= tab[j][k])) {
						quantidade++;	
						k++;
						num++;
					}
					else {
						k++;
						num++;
					}
				}
				else {
					k++;
					num++;
				}
			}
		}
	}
	num = 0;
	if(quantidade == 0) {
		return 1;
	}	
	else{
		quantidade = 0;
		return 0;
	}
}

int validaMovimento (char *movimento, int **tab, int l, int c, int num) {
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese");

	switch (movimento[0]){
		case 49:
			if(tab[l+1][c-1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num+4) > 24) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;	
		case 50:
			if(tab[l+1][c] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num+5) > 24) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;	
		case 51:
			if(tab[l+1][c+1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num+6) > 24) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;		
		case 52:
			if(tab[l][c-1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num-1) < 0) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;				
		case 54:
			if(tab[l][c+1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num+1) > 24) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;			
		case 55:
			if(tab[l-1][c-1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num-6) < 0) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;				
			case 56: 
			if(tab[l-1][c] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num-5) < 0) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;
		case 57:
			if(tab[l-1][c+1] == '\0') {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Campo vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
			else {
				if((num-4) < 0) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Movimento fora do Tabuleiro!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					return 1;	
				}
				else {
					return 0;
				}
			}
			break;
	}
}

void movimento (int i, int **tab, int *pecas, int l, int c, int num) {
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese");
	char *movimento = (char*)malloc(2*sizeof(char));
	int tamanho_movimento = 0, invalido = 0;
	
	do {
		do {
			printf("Digite seu movimento!");
			printf("\n");
			scanf("%s", movimento);
				tamanho_movimento = strlen(movimento);
				if((movimento[0] < 49 || movimento[0] > 57) || movimento[0] == 53 || (tamanho_movimento != 1)) {
					SetConsoleTextAttribute(hConsole, COR3);
					printf("Digite um movimento válido!\n");
					SetConsoleTextAttribute(hConsole, CORPADRAO);
				}
		}while((movimento[0] < 49 || movimento[0] > 57) || movimento[0] == 53 || (tamanho_movimento != 1));
				
		switch (movimento[0]){
			case 49:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l+1][c-1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l+1][c-1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num+4] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
			case 50:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l+1][c] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l+1][c] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num+5] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
			case 51:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l+1][c+1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l+1][c+1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num+6] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;	
			case 52:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l][c-1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l][c-1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num-1] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
			case 54:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l][c+1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l][c+1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num+1] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
			case 55:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l-1][c-1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l-1][c-1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num-6] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
			case 56: 
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l-1][c] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l-1][c] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num-5] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;	
			case 57:
			invalido = validaMovimento(movimento, tab, l, c, num);
			if(invalido == 1)
				continue;
			if(tab[l-1][c+1] > tab[l][c]) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Você não pode atacar esta peça!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				invalido = 1;
				continue;
			}
			tab[l-1][c+1] += tab[l][c];
			tab[l][c] = '\0';
			pecas[num-4] = pecas[num];
			pecas[num] = '\0';
			invalido = 0;
			break;
		}
	}while(invalido == 1);

}	


int validaPeca (int i, int **tab, int l, int c, int *pecas, int num) {
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese");
	
	if(i == 1) {
		if(pecas[num] == '\0') {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Espaço vazio!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else if (pecas[num] != 1) {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Selecione uma peça de sua cor!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else {
			if ((tab[l+1][c-1] != '\0' && tab[l+1][c-1] <= tab[l][c]) || (tab[l+1][c] != '\0' && tab[l+1][c] <= tab[l][c]) || (tab[l+1][c+1] != '\0' && tab[l+1][c+1] <= tab[l][c]) || (tab[l][c-1] != '\0' && tab[l][c-1] <= tab[l][c]) || (tab[l][c+1] != '\0' && tab[l][c+1] <= tab[l][c]) || (tab[l-1][c-1] != '\0' && tab[l-1][c-1] <= tab[l][c]) || (tab[l-1][c] != '\0' && tab[l-1][c] <= tab[l][c]) || (tab[l-1][c+1] != '\0' && tab[l-1][c+1] <= tab[l][c])) {
				return 0;	
			}
			else {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Esta peça não possuí movimentos válidos!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
		}
	}
	
	else if(i == 2) {
		if(pecas[num] == '\0') {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Espaço vazio!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else if (pecas[num] != 2) {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Selecione uma peça de sua cor!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else {
			if ((tab[l+1][c-1] != '\0' && tab[l+1][c-1] <= tab[l][c]) || (tab[l+1][c] != '\0' && tab[l+1][c] <= tab[l][c]) || (tab[l+1][c+1] != '\0' && tab[l+1][c+1] <= tab[l][c]) || (tab[l][c-1] != '\0' && tab[l][c-1] <= tab[l][c]) || (tab[l][c+1] != '\0' && tab[l][c+1] <= tab[l][c]) || (tab[l-1][c-1] != '\0' && tab[l-1][c-1] <= tab[l][c]) || (tab[l-1][c] != '\0' && tab[l-1][c] <= tab[l][c]) || (tab[l-1][c+1] != '\0' && tab[l-1][c+1] <= tab[l][c])) {
				return 0;	
			}
			else {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Esta peça não possuí movimentos válidos!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
		}
	}
	
	else if(i == 3) {
		if(pecas[num] == '\0') {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Espaço vazio!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else if (pecas[num] != 3) {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Selecione uma peça de sua cor!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else {
			if ((tab[l+1][c-1] != '\0' && tab[l+1][c-1] <= tab[l][c]) || (tab[l+1][c] != '\0' && tab[l+1][c] <= tab[l][c]) || (tab[l+1][c+1] != '\0' && tab[l+1][c+1] <= tab[l][c]) || (tab[l][c-1] != '\0' && tab[l][c-1] <= tab[l][c]) || (tab[l][c+1] != '\0' && tab[l][c+1] <= tab[l][c]) || (tab[l-1][c-1] != '\0' && tab[l-1][c-1] <= tab[l][c]) || (tab[l-1][c] != '\0' && tab[l-1][c] <= tab[l][c]) || (tab[l-1][c+1] != '\0' && tab[l-1][c+1] <= tab[l][c])) {
				return 0;	
			}
			else {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Esta peça não possuí movimentos válidos!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
		}
	}
	
	else {
		if(pecas[num] == '\0') {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Espaço vazio!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else if (pecas[num] != 4) {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Selecione uma peça de sua cor!\n");
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			return 1;
		}
		else {
			if ((tab[l+1][c-1] != '\0' && tab[l+1][c-1] <= tab[l][c]) || (tab[l+1][c] != '\0' && tab[l+1][c] <= tab[l][c]) || (tab[l+1][c+1] != '\0' && tab[l+1][c+1] <= tab[l][c]) || (tab[l][c-1] != '\0' && tab[l][c-1] <= tab[l][c]) || (tab[l][c+1] != '\0' && tab[l][c+1] <= tab[l][c]) || (tab[l-1][c-1] != '\0' && tab[l-1][c-1] <= tab[l][c]) || (tab[l-1][c] != '\0' && tab[l-1][c] <= tab[l][c]) || (tab[l-1][c+1] != '\0' && tab[l-1][c+1] <= tab[l][c])) {
				return 0;	
			}
			else {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Esta peça não possuí movimentos válidos!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				return 1;
			}
		}
	}
}

void exibeTabuleiro (int **tab, struct Pino p, int *pecas) {
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese");
    
    int contador = 0;
    system("cls");
    
    char letras[6] = {' ','a','b','c','d','e'};
	
	printf("|  1  |  2  |  3  |  4  |  5  |\n");
	printf("+-----+-----+-----+-----+-----+-----\n");
	for (int i = 1; i < 6; i ++) {
		for (int j = 1; j < 6; j++) {
			printf("|");
			
			switch(pecas[contador]) {
				case '\0':
					printf("     ");
					break;
				case 1:
					SetConsoleTextAttribute(hConsole, COR1);
					printf("  %d  ", tab[i][j]);
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					break;
				case 2:
					SetConsoleTextAttribute(hConsole, COR2);
					printf("  %d  ", tab[i][j]);
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					break;
				case 3:
					SetConsoleTextAttribute(hConsole, COR3);
					printf("  %d  ", tab[i][j]);
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					break;
				case 4:
					SetConsoleTextAttribute(hConsole, COR4);
					printf("  %d  ", tab[i][j]);
					SetConsoleTextAttribute(hConsole, CORPADRAO);
					break;
			}
			contador++;	
		}
		printf("|  %c\n", letras[i]);
		printf("+-----+-----+-----+-----+-----+-----\n");
	}
	printf("\n");
	printf("+==============================================================================================================+\n");
	printf("\n");
}

void posicaoMatriz (int i, int **tab, struct Pino p, int *pecas) {
	
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, "Portuguese");
	
	char *linha = (char*)malloc(2*sizeof(char)), *coluna = (char*)malloc(2*sizeof(char));
	int valida = 0, tamanho_linha = 0, tamanho_coluna = 0, l = 0, c = 0, num = 0;
    
	do {
	    valida = 0;
		do {
			printf("Indique a linha: ");
			scanf("%s", linha);
			tamanho_linha = strlen(linha);
			if((tolower(linha[0]) < 97 || tolower(linha[0]) > 101) || (tamanho_linha != 1)) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Digite uma linha válida!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
			}
		}while((tolower(linha[0]) < 97 || tolower(linha[0]) > 101) || (tamanho_linha != 1));
		
		do {
			printf("Indique a coluna: ");
			scanf("%s", coluna);
			tamanho_coluna = strlen(coluna);
			if((coluna[0] < 49|| coluna[0] > 53) || (tamanho_coluna != 1)) {
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Digite uma coluna válida!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
			}
		}while((coluna[0] < 49 || coluna [0] > 53) || (tamanho_coluna != 1));
			
		linha[0] = tolower(linha[0]);
			
		if(linha[0] == 97) {
			l = 1;
			switch(coluna[0]) {
				case 49:
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Espaço vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				valida = 1;
				break;
				case 50:
				c = 2;
				num = 1;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 51:
				c = 3;
				num = 2;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 52:
				c = 4;
				num = 3;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 53:
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Espaço vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				valida = 1;
				break;
			}
		}
		else if(linha[0] == 98) {
			l = 2;
			switch(coluna[0]) {
				case 49:
				c = 1;
				num = 5;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 50:
				c = 2;
				num = 6;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 51:
				c = 3;
				num = 7;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 52:
				c = 4;
				num = 8;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 53:
				c = 5;
				num = 9;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
			}
		}
		else if(linha[0] == 99) {
			l = 3;
			switch(coluna[0]) {
				case 49:
				c = 1;
				num = 10;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 50:
				c = 2;
				num = 11;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 51:
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Espaço vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				valida = 1;
				break;
				case 52:
				c = 4;
				num = 13;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 53 :
				c = 5;
				num = 14;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;	
			}
		}
		else if(linha[0] == 100) {
			l = 4;
			switch(coluna[0]) {
				case 49:
				c = 1;
				num = 15;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 50:
				c = 2;
				num = 16;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 51:
				c = 3;
				num = 17;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 52:
				c = 4;
				num = 18;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 53:
				c = 5;
				num = 19;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;	
			}
		}
		else {
			l = 5;
			switch(coluna[0]) {
				case 49:
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Espaço vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				valida = 1;
				break;
				case 50:
				c = 2;
				num = 21;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 51:
				c = 3;
				num = 22;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 52:
				c = 4;
				num = 23;
				valida = 0;
				valida = validaPeca(i, tab, l, c, pecas, num);
				break;
				case 53:
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Espaço vazio!\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				valida = 1;
				break;
			}
		}
	}while(valida != 0);
	movimento(i, tab, pecas, l ,c, num);
	
}

void trocaTurno (int **tab, int *pecas, struct Pino p) {
	
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, "Portuguese");
	
	int i = 1, pula_vez[5] = {0,0,0,0,0};
	
	do {
    	for(i = 1; i < 5; i++) {
    		
    		pula_vez[i] = fimPartida(i, tab, pecas);
    		if(pula_vez[i] == 1) {
				continue;
			}
			
			printf("Vez do ");
    		switch(i) {
    			case 1:
				SetConsoleTextAttribute(hConsole, COR1);
				printf("Jogador 1\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO);
				break;
    			case 2: 
				SetConsoleTextAttribute(hConsole, COR2);
				printf("Jogador 2\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO); 
				break;
    			case 3: 
				SetConsoleTextAttribute(hConsole, COR3);
				printf("Jogador 3\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO); 
				break;
    			case 4: 
				SetConsoleTextAttribute(hConsole, COR4);
				printf("Jogador 4\n");
				SetConsoleTextAttribute(hConsole, CORPADRAO); 
				break;
			}
			
			printf("Selecione sua peça!\n");
			posicaoMatriz(i, tab, p, pecas);
			exibeTabuleiro(tab, p, pecas);
		}
		i = 1;
	}while(pula_vez[1] == 0 || pula_vez[2] == 0 || pula_vez[3] == 0 || pula_vez[4] == 0);
	
	calculo(tab, pecas);	
}

void Tabuleiro(int **tab) {
	
	struct Contagem c;
	c.azul = 5;
	c.verde = 5;
	c.vermelho = 5;
	c.amarelo = 5;
	
	struct Pino p;
	p.azul = 1;
	p.verde = 1;
	p.vermelho = 1;
	p.amarelo = 1;
		
	int alerta = 0, jogador, num, qtdJogadores = 4, k = 0, *pecas = (int*)malloc(25*sizeof(int));
	time_t t;
	
	srand((unsigned) time(&t));
	
	
	for(int i = 0; i < 7; i++) {
		for (int j = 0 ; j < 7 ; j++) {
			if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 2) || (i == 0 && j == 3) || (i == 0 && j == 4) || (i == 0 && j == 5) || (i == 0 && j == 6)) {
				tab[i][j] = '\0';
				continue;
			}
			if ((i == 1 && j == 0) || (i == 1 && j == 6) || (i == 2 && j == 0) || (i == 2 && j == 6) || (i == 3 && j == 0) || (i == 3 && j == 6) || (i == 4 && j == 0)) {
				tab[i][j] = '\0';
				continue;
			}
			if ((i == 1 && j == 1) || (i == 1 && j == 5) || (i == 3 && j == 3) || (i == 5 && j == 1) || (i == 5 && j == 5)) {
				tab[i][j] = '\0';
				pecas[k] = '\0';
				k++;
				continue;
			}
			if ((i == 4 && j == 6) || (i == 5 && j == 0) || (i == 5 && j == 6) || (i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 2) || (i == 6 && j == 3) || (i == 6 && j == 4) || (i == 6 && j == 5) || (i == 6 && j == 6)) {
				tab[i][j] = '\0';
				continue;
			}
			
			do {
			jogador = (rand()%qtdJogadores)+1;
			switch (jogador) {
				case 1:
					alerta = 0;
					c.azul--;
					if (c.azul == -1) {
						alerta = 0;
						c.azul++;
						alerta++;
					}
					break;
				case 2:
					alerta = 0;
					c.verde--;
					if (c.verde == -1) {
						alerta = 0;
						c.verde++;
						alerta++;
					}
					break;
				case 3:
					alerta = 0;
					c.vermelho--;
					if (c.vermelho == -1) {
						alerta = 0;
						c.vermelho++;
						alerta++;
					}
					break;
				case 4:
					alerta = 0;
					c.amarelo--;
					if (c.amarelo == -1) {
						alerta = 0;
						c.amarelo++;
						alerta++;
					}
					break;
				}
			}while (alerta == 1);
			
			switch(jogador) {
				case 1:
					pecas[k] = jogador;
					tab[i][j] = p.azul;
					break;
				case 2:
					pecas[k] = jogador;
					tab[i][j] = p.verde;
					break;
				case 3:
					pecas[k] = jogador;
					tab[i][j] = p.vermelho;
					break;
				case 4:
					pecas[k] = jogador;
					tab[i][j] = p.amarelo;
					break;
			}
			k++;
		}
	}
	
	exibeTabuleiro(tab, p, pecas);	
	trocaTurno(tab, pecas, p);
}

void menu (int **tab) {
	setlocale(LC_ALL, "Portuguese");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, COR5);
	VOID WINAPI sleep(_In_ DWORD dwMilliseconds);
	
	char x[0];
	int tamanho_x = 0;
	
	do {
		printf("+==============================================================================================================+\n");
		printf("\t######     ####      #####     #####    ##   #    ######    ######    ###    ##   ###     #### \n");
		printf("\t##  ##    ##  ##    ##   ##   ##   ##   ##   #    ##  ##    ##  ##    ###    ###  ###    ### ##\n");
		printf("\t##        ##  ##    ######    ######    ##   #    ##        ##        ###    #### ###    ##  ##\n");
		printf("\t##  ##    ######    ##        ##        ######    ##  ##    ##  ##    ###    ########    ## ###\n");
		printf("\t######    ##  ##    ##        ##        #####     ######    ######    ###    ##   ###     #### \n");
		printf("+==============================================================================================================+\n");
	
		SetConsoleTextAttribute(hConsole, CORPADRAO);
		tamanho_x = 0;
	
		printf("\t\t\t\t\t##    #                          \n");
		printf("\t\t\t\t\t###  ##    ####    # ###    ##  #\n");
		printf("\t\t\t\t\t## ## #   ##   #   ##  ##   ##  #\n");
		printf("\t\t\t\t\t##    #   #####    ##  ##   ##  #\n");
		printf("\t\t\t\t\t##    #    #####   ##  ##   #### \n");

   		printf("                                                                                     `:.\n");
    	printf("                                                                                       `:.\n");
   		printf("                                                                               .:'     ,::\n");
   		printf("               ++--------------------------------++                           .:'      ;:'\n");
    	printf("               ||                                ||                           ::      ;:'\n");
    	printf("               ||        Novo Jogo [1]           ||                            :    .:'\n");
    	printf("               ||        Carregar Jogo [2]       ||                             `.  :.\n");
    	printf("               ||        Ver Replay [3]          ||                    _________________________\n");
    	printf("               ||                                ||                   : _ _ _ _ _ _ _ _ _ _ _ _ :\n");
    	printf("               ++--------------------------------++               ,---:'.''.'.''.'.''.'.''.'.''.:\n");
    	printf("                                                                 : ,''`::.:.:.:.:.:.:.:.:.:.:.::'\n");
    	printf("                                                                 `.`.  `:-===-===-===-===-===-:'\n");
    	printf("                                                                   `.`-._:                   :\n");
    	printf("                                                                     `-.__`.               ,' \n");
    	printf("                                                                 ,--------`'`-------------'--------.\n");
    	printf("                                                                  `'--.__                   __.--''\n");
    	printf("                                                                         `""-------------""'\n");
    	SetConsoleTextAttribute(hConsole, COR5);
    	printf("+==============================================================================================================+\n");
    	SetConsoleTextAttribute(hConsole, CORPADRAO);
		scanf("%s", &x);
		tamanho_x = strlen(x);
	
		if ((x[0] != 49 && x[0] != 50 && x[0] != 51) || (tamanho_x != 1)) {
			SetConsoleTextAttribute(hConsole, COR3);
			printf("Valor inválido! Insira corretamente!");
			sleep(1);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
		}
		system("cls");
	}while ((x[0] != 49 && x[0] != 50 && x[0] != 51) || (tamanho_x != 1));
	
	system("cls");
	
	if(x[0] == 49){
		
		char y[1], *nome_save = (char*)malloc(10*sizeof(char)); 
		int tamanho_y = 0, erro = 0;
		SetConsoleTextAttribute(hConsole, COR5);
		printf("+==============================================================================================================+\n");
		do{
			SetConsoleTextAttribute(hConsole, COR5);
   			printf("\t\t\t\t\tComo gostaria de salvar o seu jogo? ");
   			SetConsoleTextAttribute(hConsole, CORPADRAO);
   			scanf("%s", nome_save);
   			printf("\n");
   			SetConsoleTextAttribute(hConsole, COR5);
   			printf("\t\t\tSeu jogo será salvo como: ");
   			SetConsoleTextAttribute(hConsole, CORPADRAO);
			printf("%s. ", nome_save);
			SetConsoleTextAttribute(hConsole, COR5);
			printf("Gostaria de modificá-lo?\n", nome_save);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
			do {
				SetConsoleTextAttribute(hConsole, COR5);
   				printf("\t\t\t\t\t\tSim [1] / Não [2] ");
   				SetConsoleTextAttribute(hConsole, CORPADRAO);
   				scanf("%s", &y);
   				tamanho_y = strlen(y);
   				if((y[0] != 49 && y[0] != 50) || tamanho_y != 1) {
   					SetConsoleTextAttribute(hConsole, COR3);
   					printf("\t\t\t\t\tValor inválido! Insira corretamente!\n");
   					erro = 1;
   					SetConsoleTextAttribute(hConsole, CORPADRAO);
				}
				else {
					erro = 0;
				}
			}while(erro == 1);
		} while (y[0] == 49 && tamanho_y == 1);
		
		if (y[0] == 50) {
			SetConsoleTextAttribute(hConsole, COR5);
			printf("\t\t\t\t\t\tIniciando o jogo...\n");
			printf("+==============================================================================================================+\n");
			sleep(1);
			SetConsoleTextAttribute(hConsole, CORPADRAO);
		}
		
		system("cls");
		Tabuleiro(tab);
		free(nome_save);
	}
	else if (x[0] == 50){
		setlocale(LC_ALL, "Portuguese");
		SetConsoleTextAttribute(hConsole, COR5);
		printf("+==============================================================================================================+\n");
		SetConsoleTextAttribute(hConsole, CORPADRAO);
		printf("\t\t\t\t\t\t   INDISPONIVEL! \n");
		printf("\t\t\t\t\t   ESPERE A PROXIMA VERSAO :)\n");
		SetConsoleTextAttribute(hConsole, COR5);
		printf("+==============================================================================================================+\n");
		SetConsoleTextAttribute(hConsole, CORPADRAO);
		sleep(2);
		
		system("cls");
		menu(tab);
	}
	else {
		setlocale(LC_ALL, "Portuguese");
		SetConsoleTextAttribute(hConsole, COR5);
		printf("+==============================================================================================================+\n");
		SetConsoleTextAttribute(hConsole, CORPADRAO);
		printf("\t\t\t\t\t\t   INDISPONIVEL! \n");
		printf("\t\t\t\t\t   ESPERE A PROXIMA VERSAO :)\n");
		SetConsoleTextAttribute(hConsole, COR5);
		printf("+==============================================================================================================+\n");
		SetConsoleTextAttribute(hConsole, CORPADRAO);
		sleep(2);
		
		system("cls");
		menu(tab);
	}

}

int main () {
	setlocale(LC_ALL, "Portuguese");	
	
	int** tab = (int**)malloc(7*sizeof(int*));
	for (int i = 0; i < 7; i++) {
		tab[i] = (int*)malloc(7*sizeof(int));
	}
	menu(tab);
}
