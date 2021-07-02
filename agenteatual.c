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
#define LIXO1 7
#define LIXO2 8
#define AGENTB 9
#define INCINERADOR 10
#define RECICLADORA 11

int posAgenteX = 1;
int posAgenteY = 1;
int ambiente[SIZE][SIZE];
int mochila = 0;/*false*/
int count = 0;
int testeCount = 0;

int posAgenteBX = 1;
int posAgenteBY = 18;

int countPonto = 0;
int countStar = 0;

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
                ambiente[i][j] = LIXO1;
            }
            if(i == 12 && j == 18)
            {
                ambiente[i][j] = LIXO2;
            }
            if(i == 18 && j == 1)
            {
                ambiente[i][j] = INCINERADOR;
            }
            if(i == 18 && j == 18)
            {
                ambiente[i][j] = RECICLADORA;
            }
            if(i == 1 && j == 18)
            {
                ambiente[i][j] = AGENTB;
            }
        }
    }
}

int mostrarAmbiente(int countPonto, int countStar, int mochila, int testeCount)
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
                countPonto++;
                printf(".");
            }
            else if (ambiente[i][j] == STAR)
            {
                countStar++;
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
            else if (ambiente[i][j] == LIXO1)
                printf("X");
            else if (ambiente[i][j] == LIXO2)
                printf("Y");
            else if (ambiente[i][j] == AGENTB)
                printf("B");
            else if (ambiente[i][j] == INCINERADOR)
                printf("I");
            else if (ambiente[i][j] == RECICLADORA)
                printf("R");
        }
        printf("\n");
    }
    printf("Faltam %d estrelas e Faltam %d pontos. testeCount: %d mochila: %d\n", countStar, countPonto, testeCount, mochila);
    return countStar+countPonto;
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
    ambiente[12][1] = LIXO1;
}


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
        ambiente[12][18] = LIXO2;
}

void voltarIncinerador()
{
    	ambiente[posAgenteBX][posAgenteBY] = BLANK;
        if(posAgenteBX==20 && posAgenteBY==1)
        {
            mochila=0;
        }
        if(posAgenteBX<20)
        {
            posAgenteBX=posAgenteBX+1;
        }
        if(posAgenteBY>1)
        {
            posAgenteBY=posAgenteBY-1;
        }
        ambiente[posAgenteBX][posAgenteBY] = AGENTB;
        ambiente[20][1] = INCINERADOR;
}

void voltarRecicladora()
{
    	ambiente[posAgenteBX][posAgenteBY] = BLANK;
        if(posAgenteBX==20 && posAgenteBY==18)
        {
            mochila=0;
        }
        if(posAgenteBX<20)
        {
            posAgenteBX=posAgenteBX+1;
        }
        if(posAgenteBY<18)
        {
            posAgenteBY=posAgenteBY+1;
        }
        ambiente[posAgenteBX][posAgenteBY] = AGENTB;
        ambiente[20][1] = RECICLADORA;
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






////////////////----------- FUNCAO PRINCIPAL -------------/////////////////
int main()
{

    struct timespec start, finish;     //contadores de tempo
    double elapsed;
    construirAmbiente();
    int inicioLixos = mostrarAmbiente(countPonto, countStar, mochila, testeCount);/*guarda o numero de lixos q tem no começo*/

    clock_gettime(CLOCK_MONOTONIC, &start);
    while(!verificarSucesso())
    {
        delay(99999);
        testeCount = mostrarAmbiente(countPonto, countStar, mochila, testeCount);
        localizaAgente();
        system("cls");
        if(mochila==0)
        {
            int acao = funcaoAgenteR1(sensores(LEFT), sensores(RIGHT), sensores(UP), sensores(DOWN));
            atuadores(acao);
            testeCount = mostrarAmbiente(countPonto, countStar, mochila, testeCount);//tem que ficar aqui pra não comer mais de um lixo antes de ir pra lixeira!
            atuadoresB();
            ambiente[12][1] = LIXO1;
            if(inicioLixos > testeCount)
            {
                mochila++;
                inicioLixos--;
            }
        }
        else
        {
            /*if(posAgenteY <= 10)
                voltarLixeiraX();
            else
                voltarLixeiraY();
            */
            voltarIncinerador();
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Tempo gasto: %.3f s.", elapsed);
    return 0;
}
