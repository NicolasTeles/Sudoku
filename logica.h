#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct linha{
    int *validos;
}Linha;

typedef struct coluna{
    int *validos;
}Coluna;

typedef struct grid{
    int *validos;
}Grid;

typedef struct celula{
    int linha;
    int coluna;
    int num_possiveis;
} Celula;

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

void validaValor(Sudoku* s, int i, int j, int valor, int boolean);

bool quadradoPerfeito(Sudoku* s);

void criaSudoku(Sudoku* s);

void criaVetoresValidos(Sudoku* s);

void preencheValidos(Sudoku* s);

void preencheHeap(Sudoku* s);

int testaValores(Sudoku* s, int i, int j, FILE* fs);

bool backtracking(Sudoku * sudoku, int n, int m, FILE*fs);

bool resolveSudoku(Sudoku* sudoku, FILE* fs);

bool obterTamanhoSudoku(Sudoku* s, FILE* f);

void destroiValidos(Sudoku* s);

void destroiSudoku(Sudoku* s);

void destroiMatriz(Sudoku* s);

bool heuristica(Sudoku* sudoku);

void troca(Celula* a, Celula* b);

int esquerda(int i);

int direita(int i);

int pai(int i);

void heapify(Sudoku* sudoku, int i);

bool insere(Sudoku* sudoku, Celula elemento);

Celula removeMin(Sudoku* sudoku);

#endif