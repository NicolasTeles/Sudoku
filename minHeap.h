#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "entradaSaida.h"
#include "logica.h"

void troca(Celula* a, Celula* b);

int esquerda(int i);

int direita(int i);

int pai(int i);

void heapify(Sudoku* sudoku, int i);

bool insere(Sudoku* sudoku, Celula elemento);

Celula removeMin(Sudoku* sudoku);

#endif