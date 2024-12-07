#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "logica.h"
#include "entradaSaida.h"

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, int* N){
    int opt;
    while((opt = getopt(argc, argv, "e:s:n:")) != -1){
        switch (opt){
            case 'e':
                *arquivoEntrada = optarg;
                break;
            
            case 's':
                *arquivoSaida = optarg;
                break;

            case 'n':
                *N = atoi(optarg);
                break;

            default:
                printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
                exit(1);
        }
    }
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

Sudoku* geraSudoku(char* arquivoEntrada){
    int valor;
    FILE* fp = fopen(arquivoEntrada, "r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
    Sudoku* sudoku = (Sudoku*)malloc(sizeof(Sudoku));
    
    char string[500];
    int i = 0;
    if(obterTamanhoSudoku(sudoku, fp) == false || !quadradoPerfeito(sudoku)){
        destroiSudoku(sudoku);
        fclose(fp);
        return NULL;
    }

    criaSudoku(sudoku);
    // printf("tamanho: %d\n", sudoku->tamanho);

    while(!feof(fp)){
        if(i >= sudoku->tamanho){
            destroiSudoku(sudoku);
            fclose(fp);
            return NULL;
        }
        fgets(string, 500, fp);
        if(string[0] == '\n' || strcmp(string, "\r\n") == 0)
            continue;
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        // printf("%s\n", token);
        int j;
        for(j = 0; ; j++){
            if(token == NULL)
                break;
            if(j >= sudoku->tamanho){
                destroiSudoku(sudoku);
                fclose(fp);
                return NULL;
            }

            if(token[0] == 'v'){
                sudoku->matrizSudoku[i][j] = 0;
                token = strtok(NULL, " ");
                continue;
            }
            sudoku->matrizSudoku[i][j] = valor = atoi(token);
            validaValor(sudoku, i, j, valor, 0);
            
            token = strtok(NULL, " ");
            // printf("%d %d %d\n", i, j, matriz[i][j]);
        }
        if(j != sudoku->tamanho){
            destroiSudoku(sudoku);
            fclose(fp);
            return NULL;
        }
        i++;
    }
    if(i < sudoku->tamanho){
        destroiSudoku(sudoku);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    return sudoku;
}

int testaValores(Sudoku* s, int i, int j){
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
        if(backtracking(s, (limite ? i+1 : i), (limite ? 0 : j+1) ) == true)
            return 1;
        else{
            s->matrizSudoku[i][j] = 0;
            validaValor(s, i, j, k, 1);
        }
    }
    return 0;
}

bool backtracking(Sudoku* sudoku, int n, int m){
    if(sudoku == NULL)
        return false;
    int retorno;
    for(int i = n; i < sudoku->tamanho; i++){
        for(int j = (i==n ? m : 0); j < sudoku->tamanho; j++){
            retorno = testaValores(sudoku, i, j);
            if(retorno == -1)
                continue;
            if(retorno == 0)
                return false;
            if(retorno == 1)
                return true;
        }
    }
    return true;
}

// bool heuristica(Sudoku* sudoku, int n, int m){}

bool resolveSudoku(Sudoku* sudoku){
    return backtracking(sudoku, 0, 0);
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
    free(s);
}

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    int N = 1;
    obterNomeArquivos(argc, argv, &entrada, &saida, &N);
    //comeca loop, passar abertura de arquivo pra main
    Sudoku* s = geraSudoku(entrada);
    if(s == NULL){
        printf("Entrada de sudoku invalido\n");
        return 0;
    }
    for(int i = 0; i < s->tamanho; i++){
        for(int j = 0; j < s->tamanho; j++)
            printf("%d ", s->matrizSudoku[i][j]);
        printf("\n");
    }
    int resultado = resolveSudoku(s);
    printf("\n\n%d\n\n", resultado);
    if(resultado)
        for(int i = 0; i < s->tamanho; i++){
            for(int j = 0; j < s->tamanho; j++){
                printf("%d ", s->matrizSudoku[i][j]);
                if((j+1) % s->raizTamanho == 0)
                    printf(" ");
            }
            if((i+1) % s->raizTamanho == 0)
                printf("\n");
            printf("\n");
        }
    destroiSudoku(s);
    //termina loop 
    
    return 0;
}