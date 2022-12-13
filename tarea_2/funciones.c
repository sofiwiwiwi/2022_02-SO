#include "funciones.h"
/*
┌────────────────┐
│arreglos dominos│
├────────────────┴──────────────────────────────────────────────────────────────────┐
│no es una funcion o un struct pero corresponden a las partes para los print bonitos│
│estan ordenados de arriba a abajo y midd es para imprimir la mano 					│
└───────────────────────────────────────────────────────────────────────────────────┘
*/

char top[7][9] = 		{".------.",".------.",".------.",".------.",".------.",".------.",".------."};
char nomedio1[7][9] =	{"|      |","|      |","|()    |","|()    |","|()  ()|","|()  ()|","|()()()|"};
char medio[7][9] =		{"|      |","|  ()  |","|      |","|  ()  |","|      |","|  ()  |","|      |"};
char nomedio2[7][9] =	{"|      |","|      |","|    ()|","|    ()|","|()  ()|","|()  ()|","|()()()|"};
char bot[7][9] = 		{"'------'","'------'","'------'","'------'","'------'","'------'","'------'"};
char midd[7][9] = 		{"|------|","|------|","|------|","|------|","|------|","|------|","|------|"};


void print_tab1(Domino tablero[], int izq, int der){
	printf("Este es el estado actual del tablero: \n");
	
	for(int i = izq+1; i<der; i++){
		if(i<izq+5 || i>der -5){
			printf(" %s%s ",top[1], top[1]);
		}
		else if(i==izq+5 || i==der -5){
			printf("|");
		}
	};
	printf("\n");
	for(int i = izq+1; i<der; i++){
		if(i<izq+5 || i>der -5){
			printf(" %s%s ",nomedio1[tablero[i].izquierda], nomedio1[tablero[i].derecha]);
		}
		else if(i==izq+5 || i==der -5){
			printf("|");
		}
	};
	printf("\n");
	for(int i = izq+1; i<der; i++){
		if(i<izq+5 || i>der -5){
			printf(" %s%s ", medio[tablero[i].izquierda], medio[tablero[i].derecha]);
		}
		else if(i==izq+5 || i==der -5){
			printf("|");
		}
	};
	printf("\n");
	for(int i = izq+1; i<der; i++){
		if(i<izq+5 || i>der -5){
			printf(" %s%s ",nomedio2[tablero[i].izquierda], nomedio2[tablero[i].derecha]);
		}
		else if(i==izq+5 || i==der -5){
			printf("|");
		}
	};
	printf("\n");
	for(int i = izq+1; i<der; i++){
		if(i<izq+5 || i>der -5){
			printf(" %s%s ",bot[1], bot[1]);
		}
		else if(i==izq+5 || i==der -5){
			printf("|");
		}
	};
	printf("\n");
}

void print_mano1(Mano manin){
	printf("Esta es tu mano: \n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("(%d):      ",i+1);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",top[manin.dominos[i].izquierda]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",nomedio1[manin.dominos[i].izquierda]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",medio[manin.dominos[i].izquierda]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",nomedio2[manin.dominos[i].izquierda]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",midd[manin.dominos[i].izquierda]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",nomedio1[manin.dominos[i].derecha]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",medio[manin.dominos[i].derecha]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",nomedio2[manin.dominos[i].derecha]);
	};
	printf("\n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("%s  ",bot[manin.dominos[i].derecha]);
	};
	printf("\n");
}


void print_tab2(Domino tablero[], int izq, int der){
	printf("Este es el estado actual del tablero: \n");
	for(int i = izq+1; i<der; i++){
		printf("(%d|%d)",tablero[i].izquierda, tablero[i].derecha);
	};
	printf("\n");
}

void print_mano2(Mano manin){
	printf("Esta es tu mano: \n");
	for(int i = 0; i<manin.n_dom; i++){
		printf("(%d|%d)",manin.dominos[i].izquierda, manin.dominos[i].derecha);
	};
	printf("\n");
}

Mano actualizar_mano(Mano manin){
	for(int i =0; i < manin.n_dom; i++){
		if(manin.dominos[i].izquierda==-1){
			for(int j =i; j < manin.n_dom-1; j++){
				manin.dominos[j] = manin.dominos[j+1];
			}
			manin.n_dom--;
			break;
		}	
	}
	return manin;
}

int verificar_mano(Mano manin, Domino tablero[],int izq, int der){
	int flag =-1;
	for(int i =0; i < manin.n_dom; i++){
		if(tablero[izq+1].izquierda == manin.dominos[i].derecha){
			flag=i;
			break;
		}
		if(tablero[izq+1].izquierda == manin.dominos[i].izquierda){
			flag=i;
			break;
		}
		if(tablero[der-1].derecha == manin.dominos[i].izquierda){
			flag=i;
			break;
		}	
		if(tablero[der-1].derecha == manin.dominos[i].derecha){
			flag=i;
			break;
		}
	}
	return flag;
}

int elem_in_array(int elem[2], int array[][2], int n){
	int flag = 0;
	for(int i = 0; i<n; i++){
		if((elem[1] == array[i][1])&&(elem[0] == array[i][0])){
			flag = 1;
		};
	};
	return flag;
}

void print_estadojuego(int array[]){
	for(int i = 0; i<4; i++){
		if(array[i] == 0){
			printf("El jugador número %d saltó su turno\n", i+1);
		}else if(array[i] == 2){
			printf("El jugador número %d aun no juega\n", i+1);
		}
		else{	
			printf("El jugador número %d jugó su turno correctamente\n", i+1);
		}
	}
}