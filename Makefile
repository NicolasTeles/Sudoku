compile: clean logica.o entradaSaida.o main.c
	gcc entradaSaida.o logica.o main.c -o main -lm

logica.o: logica.h logica.c
	gcc -c logica.c

entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -c entradaSaida.c
 

clean: 
	rm -rf *.o main