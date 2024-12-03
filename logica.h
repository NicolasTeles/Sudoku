#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct linha{
    int validos[9];
}Linha;

typedef struct coluna{
    int validos[9];
}Coluna;

typedef struct grid{
    int validos[9];
}Grid;

typedef struct sudoku{
    int tamanho;
    Linha linhas[9];
    Coluna colunas[9];
    Grid grids[3][3];
    int** matrizSudoku;
}Sudoku;

#endif