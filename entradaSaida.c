#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "logica.h"

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, int* n){
    int opt;
    while((opt = getopt(argc, argv, "e:s:n:")) != -1){
        switch (opt)
        {
        case 'e':
            *arquivoEntrada = optarg;
            break;
        
        case 's':
            *arquivoSaida = optarg;
            break;

        case 'n':
            *n = atoi(optarg);
            break;

        default:
            printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
            exit(1);
        }
    }
}

void validaValor(Sudoku* s, int i, int j, int valor, int boolean){
    s->colunas[j].validos[valor-1] = boolean;
    s->linhas[i].validos[valor-1] = boolean;
    s->grids[i][j].validos[valor-1] = boolean;
}

void preencheValidos(Sudoku* s){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            for(int k = 0; k < 9; k++){
                s->colunas[3*i+j].validos[k] = 1;
                s->linhas[3*i+j].validos[k] = 1;
                s->grids[i][j].validos[k] = 1;
            }
        }
    }
}

Sudoku* geraSudoku(char* arquivoEntrada){
    int valor;
    FILE* fp = fopen(arquivoEntrada, "r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
    Sudoku* sudoku = (Sudoku*)malloc(sizeof(Sudoku));
    sudoku->matrizSudoku = (int**)calloc(9, sizeof(int*));
    for(int i = 0; i < 9; i++)
        sudoku->matrizSudoku[i] = (int*)calloc(9, sizeof(int));
    preencheValidos(sudoku);
    
    char string[20];
    int i = 0;
    while(!feof(fp)){
        fgets(string, 20, fp);
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        // printf("%s\n", token);
        for(int j = 0; j < 9; j++){
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
        i++;
    }
    fclose(fp);
    return sudoku;
}

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    int n = 1;
    obterNomeArquivos(argc, argv, &entrada, &saida, &n);
    Sudoku* s = geraSudoku(entrada);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            printf("%d ", s->matrizSudoku[i][j]);
        printf("\n");
    }
    for(int i = 0; i < 9; i++)
        free(s->matrizSudoku[i]);
    free(s->matrizSudoku);
    free(s);
    return 0;
}