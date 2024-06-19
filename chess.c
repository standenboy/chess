#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct peice {
	char type;
	size_t x;
	size_t y;
} peice;

peice *makePeice(char type, int x, int y){
	peice *new = malloc(sizeof(peice));
	new->type = type;
	new->x= x;
	new->y= y;
	return new;
}

peice **getBoard(char *fen){
	peice **peices = malloc(sizeof(peice)*32);

	int i = 0, j= 0;
	int currentRow = 0, currentColumn = 0;
	int currentPeice = 0;
	while (fen[i] != ' ' && fen[i] != '\0'){
		if (fen[i] == '/') {
			currentRow++;
			currentColumn = 0;
		}

		char current[2] = {fen[i], '\0'};
	
		if (fen[i] >= 'b' && fen[i] <= 'r' || fen[i] >= 'B' && fen[i] <= 'R'){
			peices[currentPeice] = makePeice(fen[i], currentColumn, currentRow);
			currentPeice++;

			currentColumn++;
		}

		if (atoi(current) != 0){
			currentColumn += atoi(current);
		}
		i++;
	}
	return peices;
}

void printBoard(peice **peices){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			bool printed = false;
			for (int x = 0; x < 32; x++){
				if (peices[x]->y == i && peices[x]->x == j){
					printf("%c", peices[x]->type);
					printed = true;
					break;
				}
			}
			if (!printed) printf("-");
		}
		printf("\n");
	}
}

int main(){
	char fen[512];
	fgets(fen, 512, stdin);
	peice **peices = getBoard(fen);

	printBoard(peices);

	for (int i = 0; i < 32; i++){
		free(peices[i]);
	}
	free(peices);
}
