#ifndef funciones_H   /* Include guard */
#define funciones_H

#include <stdio.h> //scanf y printf

#include <stdlib.h> //rand()
#include <time.h>

#include <sys/types.h> //fork
#include <unistd.h>


#define NUM_PZ 6 //numero de piezas por mano
#define PZ_TOT 28//numero de total de piezas en un domino

/*
┌─────────────┐
│struct domino│
├─────────────┴─────────────────────────────────────────────────────────────────┐
│parametros:																	│
│izquierda: indica el numero a la izquierda del domino 							│
│derecha:	indica el numero a la derecha del domino 							│
│suma:		indica la suma entre los numeros a la izquierda y derecha del domino│
└───────────────────────────────────────────────────────────────────────────────┘
*/
typedef struct domino{
	int izquierda ;
	int derecha ;
	int suma ;
}Domino;


/*
┌───────────┐
│struct Mano│
├───────────┴───────────────────────────────────────────────────────────────────┐
│parametros:																	│
│dominos:   arreglos que contie a los domino de la mano							│
│suma:		indica la suma entre los numeros a la izquierda y derecha de la mano│
│n_dom:     tiene el numero de dominos en la mano (el largo de dominos)			│
└───────────────────────────────────────────────────────────────────────────────┘
*/
typedef struct mano{
	Domino dominos[NUM_PZ];
	int suma;
	int n_dom;
}Mano;


/*
┌─────────────┐
│struct estado│
├─────────────┴─────────────────────────────────────────────────────────────────┐
│parametros:																	│
│izquierda: indica el numero a la izquierda del domino 							│
│derecha:	indica el numero a la derecha del domino 							│
│suma:		indica la suma entre los numeros a la izquierda y derecha del domino│
└───────────────────────────────────────────────────────────────────────────────┘
*/
typedef struct estado{
	Domino tablero[PZ_TOT*2];
	int izq;
	int der;
	int estadojuego[4];
	int nadiegano; 
	int algunopudojugar;
}Estado;

/*
┏━━━━━━━━━━━━━━━━━━┓
┃funcion print_tab1┃
┣━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃imprime el tablero para cuando los domino son con numeros    ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃tablero: arreglo con las piezas para imprimir 				  ┃
┃izq: entero que contiene la posicion donde empieza el tablero┃
┃der: entero que contiene la posicion donde termina el tablero┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void print_tab1(Domino tablero[], int izq, int der);
/*
┏━━━━━━━━━━━━━━━━━━━┓
┃funcion print_mano1┃
┣━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃imprime la mano para cuando los domino son con numeros       ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃manin es la mano sobre la cual se itera para imprimir		  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void print_mano1(Mano manin);
/*
┏━━━━━━━━━━━━━━━━━━┓
┃funcion print_tab2┃
┣━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃imprime el tablero para cuando los domino son con dibujos    ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃tablero: arreglo con las piezas para imprimir 				  ┃
┃izq: entero que contiene la posicion donde empieza el tablero┃
┃der: entero que contiene la posicion donde termina el tablero┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void print_tab2(Domino tablero[], int izq, int der);
/*
┏━━━━━━━━━━━━━━━━━━━┓
┃funcion print_mano2┃
┣━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃imprime la mano para cuando los domino son con dibujos       ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃manin: manin es la mano sobre la cual se itera para imprimir ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void print_mano2(Mano manin);
/*
┏━━━━━━━━━━━━━━━━━━━━━━━┓
┃funcion actualizar mano┃
┣━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃revisa si la mano tiene un -1 y lo elimina de la mano        ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃manin: manin es la mano sobre la cual se itera para revisar  ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃retornos:  												  ┃
┃manin: retorna la mano actualizada (sin los elementos con -1)┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
Mano actualizar_mano(Mano manin);
/*
┏━━━━━━━━━━━━━━━━━━━━━━┓
┃funcion verificar mano┃
┣━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃verifica si una mano tiene un domino para jugar en el tablero┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												  ┃
┃manin:   manin es la mano que revisa si se puede jugar 	  ┃
┃tablero: conjunto de dominos que se revisa para saber si la  ┃
┃         mano puede jugar	     							  ┃
┃izq:     apunta a la posicion de la izquierda en el tablero  ┃
┃izq:     apunta a la posicion de la derecha en el tablero    ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃retornos:  												  ┃
┃flag: toma el valor de la posicion del domino que se puede   ┃
┃      jugar y si no se puede jugar ninguno toma -1 como valor┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
int verificar_mano(Mano manin, Domino tablero[],int izq, int der);
/*
┏━━━━━━━━━━━━━━━━━━━━━┓
┃funcion elem_in_array┃
┣━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃revisa si un elemento esta en un array, se usa para generar ┃
┃los dominos y que no se repitan 		                     ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												 ┃
┃elem:   elemento que se revisa si esta en el array          ┃
┃array : array que se revisa 								 ┃
┃n:      tamanno del array 									 ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃retornos:  												 ┃
┃flag: toma valor 0 si el elemento no esta y 1 si es que esta┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
int elem_in_array(int elem[2], int array[][2], int n);
/*
┏━━━━━━━━━━━━━━━━━━━━━━━━┓
┃funcion printestadojuego┃
┣━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃printea si cada uno de los jugadores jugo, aun no, o si paso┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃Paramametros:												 ┃      
┃array : array que indica si cada jugador jugo, aun no, o si ┃      
┃		 si paso 											 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void print_estadojuego(int array[]);



#endif