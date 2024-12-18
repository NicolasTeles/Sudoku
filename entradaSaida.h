#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "logica.h"

void printaMatriz(int** matriz, int tamanho);

void substituiBarraR(char* string);

void substituiQuebraDeLinha(char* string);

void proximoSudoku(FILE* fp);

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, char* modo);

Sudoku* geraSudoku(FILE* fp);

void printaResultado(Sudoku *s, FILE* fs);

#endif