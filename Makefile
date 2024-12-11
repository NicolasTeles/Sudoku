compile: clean entradaSaida.o minHeap.o logica.o main.c
	gcc entradaSaida.o minHeap.o logica.o main.c -o main

entradaSaida.o:entradaSaida.h entradaSaida.c
	gcc entradaSaida.c -c
 
minHeap.o: minHeap.h minHeap.c
	gcc -c minHeap.c


logica.o: logica.g logica.c
	gcc -c logica.c

clean: 
	rm -rf *.o main