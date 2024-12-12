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

Sudoku* geraSudoku(FILE* fp);

void printaResultado(Sudoku *s, FILE* fs);

#endif