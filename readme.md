# Sudoku

Resolvedor de Sudoku em C, com dois algoritmos: **backtracking** e uma **heurística** baseada em heap mínima. Aceita tabuleiros de qualquer tamanho quadrado perfeito (1x1, 4x4, 9x9, 16x16, 25x25...) e resolve vários tabuleiros de um mesmo arquivo.

Trabalho Prático II da disciplina de **Projeto e Análise de Algoritmos** (UFSJ, dezembro de 2024), desenvolvido em dupla.

## Autores

- Miguel de Assis Viveiros
- Nicolas Rafael Mendonça Teles

## Como funciona

**Estruturas auxiliares (nos dois modos).** Para cada linha, coluna e subgrade (grid), o programa guarda quais valores ainda podem ser usados. Assim, não é preciso percorrer o tabuleiro a cada tentativa para saber se um valor é válido.

**Backtracking (`-m b`, modo padrão).** Percorre as células vazias e testa, em cada uma, os valores ainda válidos. Quando chega a uma célula sem nenhum valor possível, volta às células anteriores e tenta o próximo valor.

**Heurística (`-m h`).** Imita o raciocínio de quem joga: preenche primeiro as células com menos possibilidades. Para isso, as células vazias entram em uma **heap mínima**, ordenada pelo número de valores possíveis. Esse número é calculado uma única vez, ao montar a heap, e não é atualizado durante a resolução. A decisão foi tomada porque recalcular a cada jogada exigiria percorrer linha, coluna e grid, o que custaria mais do que o ganho. Os valores válidos de cada linha, coluna e grid continuam sendo atualizados normalmente.

## Compilar e executar

Requisitos: `gcc` e `make`, em Linux. O `Makefile` compila com AddressSanitizer (`-fsanitize=address`) e usa `sys/resource.h` para medir tempo e memória, então não é compatível com Windows.

```
make compile
./main -e entrada.txt -s saida.txt -m b
```

| Opção | Significado |
|---|---|
| `-e` | arquivo de entrada |
| `-s` | arquivo de saída |
| `-m` | modo: `b` (backtracking, padrão) ou `h` (heurística) |

Durante a execução, o programa mostra no terminal cada tabuleiro lido e, ao fim de cada um, o tempo de processador, o tempo real e a memória máxima usada.

## Formato de entrada

- Cada linha do tabuleiro tem os valores separados por espaço.
- Células vazias são escritas com `v`.
- O tamanho do tabuleiro é definido pela quantidade de valores da primeira linha, e precisa ser um quadrado perfeito.
- Tabuleiros diferentes no mesmo arquivo são separados por **duas linhas em branco**.
- Não deixe linhas em branco no final do arquivo.

Exemplo (um 9x9 e um 4x4 vazio):

```
5 3 v v 7 v v v v
6 v v 1 9 5 v v v
v 9 8 v v v v 6 v
8 v v v 6 v v v 3
4 v v 8 v 3 v v 1
7 v v v 2 v v v 6
v 6 v v v v 2 8 v
v v v 4 1 9 v v 5
v v v v 8 v v 7 9


v v v v
v v v v
v v v v
v v v v
```

## Formato de saída

Para cada tabuleiro, o arquivo de saída traz a grade resolvida, com os grids separados por espaços e linhas em branco. Se o tabuleiro não tem solução, aparece `Sudoku Impossível`. Se a entrada está mal formada (linhas de tamanhos diferentes, tamanho que não é quadrado perfeito), aparece `Entrada de sudoku invalido!`.

## Organização

| Arquivo | Conteúdo |
|---|---|
| `main.c` | Leitura dos argumentos, laço principal e medição de tempo |
| `logica.c` / `logica.h` | Estruturas do Sudoku, backtracking, heurística e heap mínima |
| `entradaSaida.c` / `entradaSaida.h` | Leitura do arquivo, validação da entrada e impressão |
| `TP2_Documentação.pdf` | Documentação completa: rotinas, estruturas de dados, complexidade e resultados |

## Resultados

Os testes usaram tabuleiros vazios (pior caso) de tamanhos 1x1, 4x4, 9x9 e 16x16. O 16x16 foi resolvido em menos de 1 segundo, mas o 25x25 ficou mais de 11 horas sem terminar. Isso é coerente com a complexidade exponencial do problema, analisada na documentação. A heurística não se mostrou melhor que o backtracking puro no pior caso, porque com todas as células vazias todas têm o número máximo de possibilidades.

## Limitações conhecidas

- O programa pode falhar (erro de memória) se o arquivo de entrada terminar com linhas em branco extras.
- Tabuleiros grandes (a partir de 25x25) não terminam em tempo razoável.
