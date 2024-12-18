#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    char modo;
    
    obterNomeArquivos(argc, argv, &entrada, &saida, &modo);
    FILE* fe = fopen(entrada, "r");
    if(fe == NULL){
        printf("Erro na abertura do arquivo de entrada!\n");
        return 0;
    }
    FILE* fs = fopen(saida, "w");
    if(fs == NULL){
        printf("Erro na abertura do arquivo de saida!\n");
        return 0;
    }
    while(!feof(fe)){
        Sudoku* s = geraSudoku(fe);
        if(s == NULL){
            fprintf(fs, "Entrada de sudoku invalido!\n\n");
            continue;
        }
        printaMatriz(s->matrizSudoku, s->tamanho);
        int resultado = resolveSudoku(s, modo);
        printf("\n\n%d\n\n", resultado);
        if(resultado){
            printaResultado(s, fs);
            fprintf(fs, "\n");
        }else
            fprintf(fs, "Sudoku Impossível\n\n");
        destroiSudoku(s);
    }
    fclose(fe);
    fclose(fs);
    
    return 0;
}