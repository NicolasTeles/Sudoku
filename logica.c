#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"

void troca(Celula* a, Celula* b){
    Celula temp = *a;
    *a = *b;
    *b = temp;
}

int esquerda(int i){
    return 2*i+1;
}

int direita(int i){
    return 2*i+2;
}

int pai(int i){
    return (i-1)/2;
}

void heapify(Sudoku* sudoku, int i){
    int e = esquerda(i);
    int d = direita(i);
    int menor = i;
    if(e < sudoku->tamHeap && sudoku->heap[e].num_possiveis < sudoku->heap[i].num_possiveis)
        menor = e;
    if(d < sudoku->tamHeap && sudoku->heap[d].num_possiveis < sudoku->heap[menor].num_possiveis)
        menor = d;
    if(menor != i){
        troca(&sudoku->heap[menor], &sudoku->heap[i]);
        heapify(sudoku, menor);
    }
}

bool insere(Sudoku* sudoku, Celula elemento){
    sudoku->tamHeap++;
    int i = sudoku->tamHeap-1;
    sudoku->heap[i] = elemento;
    while(i != 0 && sudoku->heap[pai(i)].num_possiveis > sudoku->heap[i].num_possiveis){
        troca(&sudoku->heap[pai(i)], &sudoku->heap[i]);
        i = pai(i);
    }
}

Celula removeMin(Sudoku* sudoku){
    if(sudoku->tamHeap == 1){
        sudoku->tamHeap--;
        return sudoku->heap[0];
    }

    Celula raiz = sudoku->heap[0];
    sudoku->heap[0] = sudoku->heap[sudoku->tamHeap-1];
    sudoku->tamHeap--;
    heapify(sudoku, 0);

    return raiz;
}

void constroiHeapVazio(Sudoku* sudoku, int n){
    sudoku->heap = (Celula*)calloc(n, sizeof(sizeof(int)));
}

void constroiHeap(Sudoku* sudoku, Celula* vetor, int n){
    constroiHeapVazio(sudoku, n);
    for(int i = 0; i < n; i++)
        sudoku->heap[i] = vetor[i];
    for(int i = (sudoku->tamHeap/2)-1; i >= 0; i--)
        heapify(sudoku, i);
}

void validaValor(Sudoku* s, int i, int j, int valor, int boolean){
    s->colunas[j].validos[valor-1] = boolean;
    s->linhas[i].validos[valor-1] = boolean;
    s->grids[i/s->raizTamanho][j/s->raizTamanho].validos[valor-1] = boolean;
}

bool quadradoPerfeito(Sudoku* s){
    return s->raizTamanho*s->raizTamanho == s->tamanho;
}

void preencheValidos(Sudoku* s){
    for(int i = 0; i < s->raizTamanho; i++){
        for(int j = 0; j < s->raizTamanho; j++){
            for(int k = 0; k < s->tamanho; k++){
                s->colunas[s->raizTamanho*i+j].validos[k] = 1;
                s->linhas[s->raizTamanho*i+j].validos[k] = 1;
                s->grids[i][j].validos[k] = 1;
            }
        }
    }
}

void criaVetoresValidos(Sudoku* s){
    for(int i = 0; i < s->raizTamanho; i++){
        for(int j = 0; j < s->raizTamanho; j++){
            s->colunas[s->raizTamanho*i+j].validos = (int*)calloc(s->tamanho, sizeof(int));
            s->linhas[s->raizTamanho*i+j].validos = (int*)calloc(s->tamanho, sizeof(int));
            s->grids[i][j].validos = (int*)calloc(s->tamanho, sizeof(int));
        }
    }
}

void criaSudoku(Sudoku* s){
    s->matrizSudoku = (int**)calloc(s->tamanho, sizeof(int*));
    for(int i = 0; i < s->tamanho; i++)
        s->matrizSudoku[i] = (int*)calloc(s->tamanho, sizeof(int));
    s->colunas = (Coluna*)calloc(s->tamanho, sizeof(Coluna));
    s->linhas = (Linha*)calloc(s->tamanho, sizeof(Linha));
    s->grids = (Grid**)calloc(s->raizTamanho, sizeof(Grid*));
    for(int i = 0; i < s->raizTamanho; i++)
        s->grids[i] = (Grid*)calloc(s->raizTamanho, sizeof(Grid));
    criaVetoresValidos(s);
    preencheValidos(s);
    s->heap = (Celula*)calloc(s->tamanho*s->tamanho, sizeof(Celula*));
    s->tamHeap= 0;
}

bool obterTamanhoSudoku(Sudoku* s, FILE* f){
    if(s == NULL || f == NULL)
        return false;
    
    char newString[500];
    long posicao_anterior = ftell(f);
    fgets(newString, 500, f);
    char* token = strtok(newString, " ");
    int contador = 0;
    while(token != NULL){
        contador++;
        token = strtok(NULL, " ");
    }

    if(contador == 0)
        return false;
    s->tamanho = contador;
    s->raizTamanho = sqrt(contador);
    fseek(f, posicao_anterior, SEEK_SET);
    return true;
}

int testaValores(Sudoku* s, int i, int j, FILE* fs){
    if(s->matrizSudoku[i][j] != 0)
        return -1;
    bool limite;
    for(int k = 1; k <= s->tamanho; k++){
        if(s->colunas[j].validos[k-1] == 0)
            continue;
        if(s->linhas[i].validos[k-1] == 0)
            continue;
        if(s->grids[i/s->raizTamanho][j/s->raizTamanho].validos[k-1] == 0)
            continue;
        
        s->matrizSudoku[i][j] = k;
        validaValor(s, i, j, k, 0);
        limite = (j+1 >= s->tamanho);
        if(backtracking(s, (limite ? i+1 : i), (limite ? 0 : j+1) , fs) == true)
            return 1;
        else{
            s->matrizSudoku[i][j] = 0;
            validaValor(s, i, j, k, 1);
        }
    }
    return 0;
}

bool backtracking(Sudoku* sudoku, int n, int m, FILE* fs){
    if(sudoku == NULL)
        return false;
    int retorno;
    printaMatrizResultado(sudoku, &fs);
    fprintf(fs, "\n");
    for(int i = n; i < sudoku->tamanho; i++){
        for(int j = (i==n ? m : 0); j < sudoku->tamanho; j++){
            retorno = testaValores(sudoku, i, j, fs);
            if(retorno == -1)
                continue;
            if(retorno == 0){
            printf("oi\n");
                return false;}
            if(retorno == 1)
                return true;
        }
    }
    return true;
}

void preencheHeap(Sudoku* s){
    if(s == NULL){
        printf("Sudoku nulo\n");
        exit(1);
    }
    Celula celula; 
    for(int i =0; i < s->tamanho; i++){
        for(int j = 0; j < s->tamanho; j++){
            if(s->matrizSudoku[i][j] == 0){
                celula.linha = i;
                celula.coluna = j;
                celula.num_possiveis = 0;
                for(int k = 1; k <= s->tamanho; k++)
                    if(s->linhas[i].validos[k] && s->colunas[j].validos[k] && s->grids[i/s->raizTamanho][j/s->raizTamanho].validos[k])
                        celula.num_possiveis++;
                insere(s, celula);
            }
        }
    }
}

bool resolveSudoku(Sudoku* sudoku, FILE* fs){
    return backtracking(sudoku, 0, 0, fs);
}

void destroiValidos(Sudoku* s){
    if(s->colunas == NULL || s->linhas == NULL || s->grids == NULL)
        return;
    for(int i = 0; i < s->raizTamanho; i++){
        for(int j = 0; j < s->raizTamanho; j++){
            free(s->colunas[s->raizTamanho*i+j].validos);
            free(s->linhas[s->raizTamanho*i+j].validos);
            free(s->grids[i][j].validos);
        }
    }
}

void destroiMatriz(Sudoku *s){
    if(s->matrizSudoku == NULL)
        return;
    for(int i = 0; i < s->tamanho; i++)
        free(s->matrizSudoku[i]);
    free(s->matrizSudoku);
}

void destroiSudoku(Sudoku* s){
    if(s == NULL)
        return;
    destroiMatriz(s);
    destroiValidos(s);
    if(s->colunas != NULL && s->linhas != NULL){
        free(s->colunas);
        free(s->linhas);
    }
    if(s->grids != NULL){
        for(int i = 0; i < s->raizTamanho; i++)
            free(s->grids[i]);
        free(s->grids);
    }
    free(s->heap);
    free(s);
}

bool heuristica(Sudoku* sudoku){
    if(sudoku == NULL)
        return false;
    if(sudoku->tamHeap == 0)
        return true;
    Celula celula = removeMin(sudoku);
    for(int k = 1; k <= sudoku->tamanho; k++){
        if(sudoku->colunas[celula.linha].validos[k-1] == 0)
            continue;
        if(sudoku->linhas[celula.coluna].validos[k-1] == 0)
            continue;
        if(sudoku->grids[celula.linha/sudoku->raizTamanho][celula.coluna/sudoku->raizTamanho].validos[k-1] == 0)
            continue;
        
        sudoku->matrizSudoku[celula.linha][celula.coluna] = k;
        validaValor(sudoku, celula.linha, celula.coluna, k, 0);
        bool retorno = heuristica(sudoku);
        if(retorno)
            return true;
        else
            continue;
    }
    return false;
}