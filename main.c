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
    int N = 1;
    
    obterNomeArquivos(argc, argv, &entrada, &saida, &N);
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
    //comeca loop, passar abertura de arquivo pra main
    while(!feof(fe)){
        Sudoku* s = geraSudoku(fe);
        if(s == NULL){
            fprintf(fs, "Entrada de sudoku invalido!\n\n");
            continue;
        }
        printaMatriz(s->matrizSudoku, s->tamanho);
        preencheHeap(s); //quando colocar o if de qual modo usar
        int resultado = heuristica(s, fs);
        //int resultado = backtracking(s, 0, 0, fs);
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
    //termina loop
    
    return 0;
}