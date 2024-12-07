#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct linha{
    int *validos;
}Linha;

typedef struct coluna{
    int *validos;
}Coluna;

typedef struct grid{
    int *validos;
}Grid;

typedef struct sudoku{
    int tamanho;
    int raizTamanho;
    Linha *linhas;
    Coluna *colunas;
    Grid **grids;
    int** matrizSudoku;
}Sudoku;

#endif