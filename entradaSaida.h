#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "logica.h"
#include "entradaSaida.h"

void substituiQuebraDeLinha(char* string);

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, int* n);

void validaValor(Sudoku* s, int i, int j, int valor, int boolean);

bool quadradoPerfeito(Sudoku* s);

void criaSudoku(Sudoku* s);

void criaVetoresValidos(Sudoku* s);

void preencheValidos(Sudoku* s);

Sudoku* geraSudoku(char* arquivoEntrada);

int testaValores(Sudoku* s, int i, int j);

bool backtracking(Sudoku * sudoku, int n, int m);

bool obterTamanhoSudoku(Sudoku* s, FILE* f);

void destroiValidos(Sudoku* s);

void destroiSudoku(Sudoku* s);

void destroiMatriz(Sudoku* s);

#endif