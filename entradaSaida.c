#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "entradaSaida.h"

void printaMatriz(int** matriz, int tamanho){
    for(int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++)
                printf("%d ", matriz[i][j]);
            printf("\n");
        }
}

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, char *modo){
    int opt;
    while((opt = getopt(argc, argv, "e:s:m:")) != -1){
        switch (opt){
            case 'e':
                *arquivoEntrada = optarg;
                break;
            
            case 's':
                *arquivoSaida = optarg;
                break;

            case 'm':
                if(optarg[0] != 'h' && optarg[0] != 'b'){
                    printf("stting: %s char: %c\n", optarg, optarg[0]);
                    printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
                    exit(1);
                }
                *modo = optarg[0];
                break;

            default:
                printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
                exit(1);
        }
    }
}

void proximoSudoku(FILE* fp){
    bool quebraDeLinha;
    char str[500];
    while(!feof(fp)){
        fgets(str, 500, fp);
        if(str[0] == '\n' || strcmp(str, "\r\n") == 0){
            if(quebraDeLinha){
                return;
            }
            quebraDeLinha = true;
            continue;
        }
        quebraDeLinha = false;
    }
}

Sudoku* geraSudoku(FILE* fp){
    int valor;
    Sudoku* sudoku = (Sudoku*)malloc(sizeof(Sudoku));
    
    char string[500];
    int i = 0;
    if(obterTamanhoSudoku(sudoku, fp) == false || !quadradoPerfeito(sudoku)){
        proximoSudoku(fp);
        destroiSudoku(sudoku);
        return NULL;
    }
    criaSudoku(sudoku);

    bool quebraDeLinha = false;
    while(!feof(fp)){
        fgets(string, 500, fp);
        if(string[0] == '\n' || strcmp(string, "\r\n") == 0){
            if(quebraDeLinha)
                break;
            quebraDeLinha = true;
            continue;
        }
        quebraDeLinha = false;
        if(i >= sudoku->tamanho){
            proximoSudoku(fp);
            destroiSudoku(sudoku);
            return NULL;
        }
        
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        int j;
        for(j = 0; ; j++){
            if(token == NULL)
                break;
            if(token[0] == '\0')
                break;
            if(token[0] == '\n' || strcmp(token, "\r\n") == 0)
                break;
            if(token[0] == ' ')
                break;
                
            if(j >= sudoku->tamanho){
                proximoSudoku(fp);
                destroiSudoku(sudoku);
                return NULL;
            }

            if(token[0] == 'v'){
                sudoku->matrizSudoku[i][j] = 0;
                token = strtok(NULL, " ");
                continue;
            }
            sudoku->matrizSudoku[i][j] = valor = atoi(token);
            validaValor(sudoku, i, j, valor, 0);
            
            token = strtok(NULL, " ");
        }
        if(j != sudoku->tamanho){
            proximoSudoku(fp);
            destroiSudoku(sudoku);
            return NULL;
        }
        i++;
    }
    if(i < sudoku->tamanho){
        printf("menor i=%d tam=%d\n", i, sudoku->tamanho);
        proximoSudoku(fp);
        destroiSudoku(sudoku);
        return NULL;
    }
    return sudoku;
}



void printaResultado(Sudoku *s, FILE* fs){
    for(int i = 0; i < s->tamanho; i++){
        for(int j = 0; j < s->tamanho; j++){
            fprintf(fs, "%d ", s->matrizSudoku[i][j]);
            if((j+1) % s->raizTamanho == 0)
                fprintf(fs, " ");
            }
            if((i+1) % s->raizTamanho == 0)
                fprintf(fs, "\n");
            fprintf(fs, "\n");
            }
}

