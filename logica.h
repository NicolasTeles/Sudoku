#include <stdio.h>
#include <stdlib.h>

typedef struct linha{
    int validos[9];
}Linha;

typedef struct coluna{
    int validos[9];
}Coluna;

typedef struct quadrado{
    int validos[9];
}Quadrado;

typedef struct sudoku{
    Linha linhas[9];
    Coluna colunas[9];
    Quadrado quadrados[3][3];
}Sudoku;