compile: clean logica.o entradaSaida.o main.c
	gcc entradaSaida.o logica.o main.c -o main -fsanitize=address -static-libasan -g -lm

logica.o: logica.h logica.c
	gcc -c logica.c -fsanitize=address -g

entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -c entradaSaida.c -fsanitize=address -g
 

clean: 
	rm -rf *.o main