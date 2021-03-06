#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define BLANK 0
#define DOT 1
#define STAR 2
#define CORNER 3
#define FLOOR 4
#define WALL 5
#define AGENT 6
int main(){
    int ambiente[SIZE][SIZE];
    void construirAmbiente(){
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(i == 0 || i == SIZE-1){
                    if(j == 0 || j == SIZE-1) ambiente[i][j] = CORNER;
                    else ambiente[i][j] = FLOOR;
                }
                else if(j == 0 || j == SIZE-1) ambiente[i][j] = WALL;
                else ambiente[i][j] = rand()%3;
            }
        }
    }


    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
			if(i == 0 || i == SIZE-1){
				if(j == 0 || j == SIZE-1) ambiente[i][j] = CORNER;
				else ambiente[i][j] = FLOOR;
			}
			else if(j == 0 || j == SIZE-1) ambiente[i][j] = WALL;
			else ambiente[i][j] = rand()%3;
		}
	}
	void mostrarAmbiente(){
        system("clear");
        int count = 0;
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if (ambiente[i][j] == BLANK) printf(" ");
                else if (ambiente[i][j] == DOT) { count++; printf(".");}
                else if (ambiente[i][j] == STAR) { count++; printf("*");}
                else if (ambiente[i][j] == CORNER) printf("+");
                else if (ambiente[i][j] == FLOOR) printf("-");
                else if (ambiente[i][j] == WALL) printf("|");
                else if (ambiente[i][j] == AGENT) printf("A");
            }
            printf("\n");
        }
        printf("Faltam %d objetos.\n", count);
    }
    
    
    
    
    construirAmbiente();
	mostrarAmbiente();
}
