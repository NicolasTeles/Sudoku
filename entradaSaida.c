#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "logica.h"
#include "entradaSaida.h"

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
        switch (opt)
        {
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

void validaValor(Sudoku* s, int i, int j, int valor, int boolean){
    s->colunas[j].validos[valor-1] = boolean;
    s->linhas[i].validos[valor-1] = boolean;
    s->grids[i/3][j/3].validos[valor-1] = boolean;
}

void preencheValidos(Sudoku* s){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
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

int testaValores(Sudoku* s, int i, int j){
    if(s->matrizSudoku[i][j] != 0)
        return -1;
    bool limite;
    for(int k = 1; k <= 9; k++){
        if(s->colunas[j].validos[k-1] == 0)
            continue;
        if(s->linhas[i].validos[k-1] == 0)
            continue;
        if(s->grids[i/3][j/3].validos[k-1] == 0)
            continue;
        
        s->matrizSudoku[i][j] = k;
        validaValor(s, i, j, k, 0);
        limite = (j+1 >= 9);
        if(backtracking(s, (limite ? i+1 : i), (limite ? 0 : j+1) ) == true)
            return 1;
        else{
            s->matrizSudoku[i][j] = 0;
            validaValor(s, i, j, k, 1);
        }
    }
    return 0;
}

bool backtracking(Sudoku* sudoku, int n, int m){
    if(sudoku == NULL)
        return false;
    int retorno;
    for(int i = n; i < 9; i++){
        for(int j = (i==n ? m : 0); j < 9; j++){
            retorno = testaValores(sudoku, i, j);
            if(retorno == -1)
                continue;
            if(retorno == 0)
                return false;
            if(retorno == 1)
                return true;
        }
    }
    return true;
}

bool resolveSudoku(Sudoku* sudoku){
    return backtracking(sudoku, 0, 0);
}

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    int N = 1;
    obterNomeArquivos(argc, argv, &entrada, &saida, &N);
    Sudoku* s = geraSudoku(entrada);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            printf("%d ", s->matrizSudoku[i][j]);
        printf("\n");
    }
    int resultado = resolveSudoku(s);
    printf("\n\n%d\n\n", resultado);
    if(resultado)
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