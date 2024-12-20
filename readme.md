Primeiro compila-se o programa pelo makefile por meio do comando "make compile"
Após isso, o executável do programa será gerado. Para rodar o programa em si deve-se seguir a seguinte estrutura:
    ./main -e [nome_do_arquivo_de_entrada].txt -s [nome_do_arquivo_de_saída].txt -m [modo de rodar o programa](b para backtracking ou h para heurística)
Caso o usuário não informe o modo que deseja que o programa seja rodado, o programa irá resolver de sua maneira padrão, que é o backtracking