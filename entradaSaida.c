#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"
#include "minHeap.h"

typedef struct sudoku Sudoku;

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, int* N){
    int opt;
    while((opt = getopt(argc, argv, "e:s:n:")) != -1){
        switch (opt){
            case 'e':
                *arquivoEntrada = optarg;
                break;
            
            case 's':
                *arquivoSaida = optarg;
                break;

            case 'n':
                *N = atoi(optarg);
                break;

            default:
                printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
                exit(1);
        }
    }
}



Sudoku* geraSudoku(FILE* fp){
    int valor;
    Sudoku* sudoku = (Sudoku*)malloc(sizeof(Sudoku));
    
    char string[500];
    int i = 0;
    if(obterTamanhoSudoku(sudoku, fp) == false || !quadradoPerfeito(sudoku)){
        destroiSudoku(sudoku);
        //fclose(fp);
        return NULL;
    }

    criaSudoku(sudoku);
    // printf("tamanho: %d\n", sudoku->tamanho);

    bool quebraDeLinha = false;
    while(!feof(fp)){
        fgets(string, 500, fp);
        if(string[0] == '\n' || strcmp(string, "\r\n") == 0){
            //printf("1 quebra de linha\n");
            if(quebraDeLinha){
                //printf("2 quebra de linha\n");
                break;
            }
            quebraDeLinha = true;
            continue;
        }
        quebraDeLinha = false;
        if(i >= sudoku->tamanho){
            destroiSudoku(sudoku);
            //fclose(fp);
            return NULL;
        }

        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        // printf("%s\n", token);
        int j;
        for(j = 0; ; j++){
            if(token == NULL)
                break;
            if(j >= sudoku->tamanho){
                destroiSudoku(sudoku);
                //fclose(fp);
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
            // printf("%d %d %d\n", i, j, matriz[i][j]);
        }
        if(j != sudoku->tamanho){
            destroiSudoku(sudoku);
            //fclose(fp);
            return NULL;
        }
        i++;
    }
    if(i < sudoku->tamanho){
        printf("menor\n");
        destroiSudoku(sudoku);
        //fclose(fp);
        return NULL;
    }
    //fclose(fp);
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

