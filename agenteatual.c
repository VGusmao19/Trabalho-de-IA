/******************************************************************************
O objetivo do agente A é capturar todos os . e os * da tela no menor tempo possivel.
Os * são mais atrativos para o agente que os .
1 - Escreva a função do agente seguindo o modelo reativo simples.
2 - Escreva a função do agente seguindo o modelo reativo baseado em modelos.
3 - Escreva a função do agente seguindo o modelo reativo baseado em objetivos.
4 - Escreva a função do agente seguindo o modelo reativo baseado na utilidade.
Depois compare o tempo que cada abordagem demorou para atingir o objetivo.
O agente capta com seus sensores o conteudo das 4 casas ao seu redor (esquerda, direita, cima, baixo)
O agente tem como acoes movimentar-se para esquerda (0), direita (1), cima (2), baixo (3)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
#define LIXO 7
#define INCINERADOR 8
#define AGENTB 9

int posAgenteX = 1;
int posAgenteY = 1;
int ambiente[SIZE][SIZE];
int mochila = 0;
int count = 0;
int testeCount = 0;

int posAgenteBX = 1;
int posAgenteBY = 18;

////////////////----------- GERENCIAMENTO DO AMBIENTE -------------/////////////////
void delay(int tempo)
{
    for(int i=0; i<tempo; i++);
}

void construirAmbiente()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if(i == 0 || i == SIZE-1)
            {
                if(j == 0 || j == SIZE-1)
                    ambiente[i][j] = CORNER;
                else
                    ambiente[i][j] = FLOOR;
            }
            else if(j == 0 || j == SIZE-1)
                ambiente[i][j] = WALL;
            else
                ambiente[i][j] = rand()%3;
        }
    }
    /*criando as lixeiras*/
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if(i == 12 && j == 1)
            {
                ambiente[i][j] = LIXO;
            }
            if(i == 12 && j == 18)
            {
                ambiente[i][j] = INCINERADOR;
            }
        }
    }
    /*criando o agente B*/
    /*ambiente[1][18] = 9;*/
}

void ambienteTeste()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if(i == 0 || i == SIZE-1)
            {
                if(j == 0 || j == SIZE-1)
                    ambiente[i][j] = CORNER;
                else
                    ambiente[i][j] = FLOOR;
            }
            else if(j == 0 || j == SIZE-1)
                ambiente[i][j] = WALL;

        }
    }
    
    ambiente[12][1] = LIXO;
    ambiente[12][18] = INCINERADOR;
    ambiente[10][10] = DOT;

}

int mostrarAmbiente(int count, int mochila, int testeCount)
{
    system("cls");
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if (ambiente[i][j] == BLANK)
                printf(" ");
            else if (ambiente[i][j] == DOT)
            {
                count++;
                printf(".");
                
            }
            else if (ambiente[i][j] == STAR)
            {
                count++;
                printf("*");
            }
            else if (ambiente[i][j] == CORNER)
                printf("+");
            else if (ambiente[i][j] == FLOOR)
                printf("-");
            else if (ambiente[i][j] == WALL)
                printf("|");
            else if (ambiente[i][j] == AGENT)
                printf("A");
            else if (ambiente[i][j] == LIXO)
                printf("X");
            else if (ambiente[i][j] == INCINERADOR)
                printf("Y");
            else if (ambiente[i][j] == AGENTB)
                printf("B");
        }
        printf("\n");
    }
    printf("Faltam %d objetos. testeCount: %d mochila: %d\n", count, testeCount, mochila);
    return count;
}

bool verificarSucesso()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if (ambiente[i][j] == DOT || ambiente[i][j] == STAR)
                return false;
        }
    }
    return true;
}

////////////////----------- AGENTE REATIVO SIMPLES -------------/////////////////
void atuadores(int acao)
{
    ambiente[posAgenteX][posAgenteY] = BLANK;
    if (acao == LEFT && ambiente[posAgenteX][posAgenteY-1] < CORNER)
        posAgenteY -= 1;
    else if (acao == RIGHT && ambiente[posAgenteX][posAgenteY+1] < CORNER)
        posAgenteY += 1;
    else if (acao == UP && ambiente[posAgenteX-1][posAgenteY] < CORNER)
        posAgenteX -= 1;
    else if (acao == DOWN && ambiente[posAgenteX+1][posAgenteY] < CORNER)
        posAgenteX += 1;
    ambiente[posAgenteX][posAgenteY] = AGENT;
}

int sensores(int lado)
{
    if (lado == LEFT)
        return ambiente[posAgenteX][posAgenteY-1];
    if (lado == RIGHT)
        return ambiente[posAgenteX][posAgenteY+1];
    if (lado == UP)
        return ambiente[posAgenteX-1][posAgenteY];
    if (lado == DOWN)
        return ambiente[posAgenteX+1][posAgenteY];
    return 0;
}

int funcaoAgenteR1(int left, int right, int up, int down)
{
    //delay(100);
    if(up == STAR || up == DOT)
    {
        return UP;
    }
    if(right == STAR || right == DOT)
    {
        return RIGHT;
    }
    if(left == STAR || left == DOT)
    {
        return LEFT;
    }
    if(down == STAR || down == DOT)
    {
        return DOWN;
    }
    return rand()%4;
}

void localizaAgente()
{
    printf("X: %d\n", posAgenteX);
    printf("Y: %d\n", posAgenteY);
}

/*movimentação do agente B*/
void atuadoresB()
{
    int guardaObjeto = ambiente[posAgenteBX+1][posAgenteBY];
    if(ambiente[posAgenteBX+1][posAgenteBY] != 7 && ambiente[posAgenteBX+1][posAgenteBY] != 8)
    {
        int guardaObjeto = ambiente[posAgenteBX+1][posAgenteBY];
    }
    if(posAgenteBX < 12)
    {
        posAgenteBX = posAgenteBX+1;
    }
    ambiente[posAgenteBX-1][posAgenteBY] = guardaObjeto;
    ambiente[posAgenteBX][posAgenteBY] = AGENTB;
}

//A voltando pra lixeira X
void voltarLixeiraX()
{
	    ambiente[posAgenteX][posAgenteY] = BLANK;
            if(posAgenteX==12 && posAgenteY==1)
            {
                mochila=0;
            }
            if(posAgenteX<12)
            {
                posAgenteX=posAgenteX+1;
            }
            if(posAgenteX>12)
            {
                posAgenteX=posAgenteX-1;
            }
            if(posAgenteY>1)
            {
                posAgenteY=posAgenteY-1;
            }
            ambiente[posAgenteX][posAgenteY] = AGENT;
            ambiente[12][1] = LIXO;
}

//A voltando pra lixeira Y
void voltarLixeiraY()
{
	    ambiente[posAgenteX][posAgenteY] = BLANK;
            if(posAgenteX==12 && posAgenteY==18)
            {
                mochila=0;
            }
            if(posAgenteX<12)
            {
                posAgenteX=posAgenteX+1;
            }
            if(posAgenteX>12)
            {
                posAgenteX=posAgenteX-1;
            }
            if(posAgenteY<18)
            {
                posAgenteY=posAgenteY+1;
            }
            ambiente[posAgenteX][posAgenteY] = AGENT;
            ambiente[12][18] = INCINERADOR;
}





////////////////----------- FUNCAO PRINCIPAL -------------/////////////////
int main()
{

    struct timespec start, finish;     //contadores de tempo
    double elapsed;
    construirAmbiente();
    int inicioLixos = mostrarAmbiente(count, mochila, testeCount);/*guarda o numero de lixos q tem no começo*/

    clock_gettime(CLOCK_MONOTONIC, &start);
    while(!verificarSucesso())
    {
        testeCount = mostrarAmbiente(count, mochila, testeCount);
        localizaAgente();
        system("cls");
        if(mochila==0)
        {
            int acao = funcaoAgenteR1(sensores(LEFT), sensores(RIGHT), sensores(UP), sensores(DOWN));
            atuadores(acao);
            atuadoresB();
            ambiente[12][1] = LIXO;
            ambiente[12][18] = INCINERADOR;
            if(inicioLixos > testeCount)
            {
                mochila++;
                inicioLixos--;
            }
        }
        else
        {
           	voltarLixeiraY();
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Tempo gasto: %.3f s.", elapsed);
    return 0;
}
