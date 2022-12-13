all: orden.o visualizacion.o

orden.o: orden.c
	gcc orden.c -Wall -o o1

visualizacion.o: visualizacion.c
	gcc visualizacion.c -Wall -o o2

orden:
	clear;./o1

visualizacion:
	clear;./o2

clean:
	rm -f o1 o2;find CWD -type f -exec cp {} archivos \;;rm -r CWD
