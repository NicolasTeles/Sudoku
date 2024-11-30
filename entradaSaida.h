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

void preencheValidos(Sudoku* s);

Sudoku* geraSudoku(char* arquivoEntrada);

int testaValores(Sudoku* s, int i, int j);

bool backtracking(Sudoku * sudoku, int n, int m);

#endif