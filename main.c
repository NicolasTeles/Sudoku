#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"
#include "minHeap.h"

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
    if(fe == NULL){
        printf("Erro na abertura do arquivo de saida!\n");
        return 0;
    }
    //comeca loop, passar abertura de arquivo pra main
    while(!feof(fe)){
        Sudoku* s = geraSudoku(fe);
        if(s == NULL){
            fprintf(fs, "Entrada de sudoku invalido!\n");
            return 0;
        }
        for(int i = 0; i < s->tamanho; i++){
            for(int j = 0; j < s->tamanho; j++)
                printf("%d ", s->matrizSudoku[i][j]);
            printf("\n");
        }
        int resultado = resolveSudoku(s);
        printf("\n\n%d\n\n", resultado);
        if(resultado){
            printaResultado(s, fs);
            fprintf(fs, "\n");
        }
        destroiSudoku(s);
    }
    fclose(fe);
    fclose(fs);
    //termina loop 
    
    return 0;
}