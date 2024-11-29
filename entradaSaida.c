#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoEntrada, char** arquivoSaida, int* n){
    int opt;
    while((opt = getopt(argc, argv, "e:s:n:")) != -1){
        switch (opt)
        {
        case 'e':
            *arquivoEntrada = optarg;
            break;
        
        case 's':
            *arquivoSaida = optarg;
            break;

        case 'n':
            *n = atoi(optarg);
            break;

        default:
            printf("Uso correto: %s -e <arquivo de entrada> -s <arquivo de saida>\n", argv[0]);
            exit(1);
        }
    }
}

int** geraMatriz(char* arquivoEntrada){
    FILE* fp = fopen(arquivoEntrada, "r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
    int** matriz = (int**)calloc(9, sizeof(int*));
    for(int i = 0; i < 9; i++)
        matriz[i] = (int*)calloc(9, sizeof(int));

    char string[20];
    int i = 0;
    while(!feof(fp)){
        fgets(string, 20, fp);
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        // printf("%s\n", token);
        for(int j = 0; j < 9; j++){
            if(token[0] == 'v'){
                matriz[i][j] = 0;
                token = strtok(NULL, " ");
                continue;
            }
            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
            // printf("%d %d %d\n", i, j, matriz[i][j]);
        }
        i++;
    }
    fclose(fp);
    return matriz;
}

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    int n = 1;
    obterNomeArquivos(argc, argv, &entrada, &saida, &n);
    int** sudoku = geraMatriz(entrada);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            printf("%d ", sudoku[i][j]);
        printf("\n");
    }
    for(int i = 0; i < 9; i++)
        free(sudoku[i]);
    free(sudoku);
    return 0;
}