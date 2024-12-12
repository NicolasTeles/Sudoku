#ifndef LOGICA_H
#define LOGICA_H

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
    int tamHeap;
    Celula* heap;
}Sudoku;

typedef struct celula{
    int linha;
    int coluna;
    int num_possiveis;
} Celula;

void validaValor(Sudoku* s, int i, int j, int valor, int boolean);

bool quadradoPerfeito(Sudoku* s);

void criaSudoku(Sudoku* s);

void criaVetoresValidos(Sudoku* s);

void preencheValidos(Sudoku* s);

int testaValores(Sudoku* s, int i, int j);

bool backtracking(Sudoku * sudoku, int n, int m);

bool obterTamanhoSudoku(Sudoku* s, FILE* f);

void destroiValidos(Sudoku* s);

void destroiSudoku(Sudoku* s);

void destroiMatriz(Sudoku* s);

#endif