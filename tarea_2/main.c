#include "funciones.h"

int main(){
	srand(time(NULL)); // para el random

	//***************************************************************** variables *****************************************************************

	//pipes
	int PEHL[4][2];//padre escribe, hijo lee
	int PLHE[4][2];//hijo escribe, padre lee
	
	//variables de comunicacion entre pipes
	Domino actual;
	Estado estado;
	Estado estadonulo;
	int mensaje =-1;//mensaje usado para pasar un valor por defecto entre hijos y padre
	
	//creacion de jugadores
	int pid;
	int contador=0;
	int primer_jugador=-1;
	int jugador_actual;

	//creacion de manos para cada jugador
	Mano manitas[4];
	int piezas_usadas = 0;
	int usados[PZ_TOT][2];
	int domino_normal[2];
	int domino_alreves[2];

	//tablero del juego
	Domino tablero[PZ_TOT*2];
	int tableroptizq = PZ_TOT-1;
	int tableroptder = PZ_TOT+1; 

	//variables para el while del juego y menu inicial
	int tipodeprint = 1; //1 para el con dibujito
	char menu;
	char izqder = ' ';
	char weon ;
	int int_menu;
	int flag;
	int puedo_jugar;
	int no_pudo_jugar;
	int c_err = 0; // contador para que en el peor de los casos si no funciona no quede en un bucle infinito


	//***************************************************************** Inicio de juego, primer menu y seleccion de print
	printf("bienvenidx a domino, seleccione por favor el tipo de pieza a usar en el juego (de no seleccionar ninguna se asignara la pieza 1):\n");
	printf("(1): pieza dibujada con ascii (mas bonito, solo aguanta hasta 8 por tablero)\n");
	printf("(2): pieza marcada por un numero (se escribe todo el tablero en un solo print)\n\n");

	printf("ejemplo tipo de pieza 1:                        ejemplo tipo de pieza 2:\n"); 
	printf("  .------..------.					\n");
	printf("  |()()()||()()()|					\n");
	printf("  |      ||      |					(6|6)\n");
	printf("  |()()()||()()()|					\n");
	printf("  '------''------'					\n");
	scanf("%c%c", &menu, &weon);

	if(menu == '2'){
		tipodeprint=2;
	}

	menu = ' ';
	//***************************************************************** Creacion de pipes, manos y jugadores *****************************************************************
	
	//inicializacion de las pipes
	for (int i = 0; i<4 ;i++){
		if (pipe(PEHL[i]) == -1) {
			fprintf(stderr, "Falló hacer el pipe");
		}
		if (pipe(PLHE[i]) == -1) {
			fprintf(stderr, "Falló hacer el pipe");
		}
	}

	//inicializacion de las manos para cada jugador
	
	for(int i = 0; i < 4; i++){
		manitas[i].suma =0;
		manitas[i].n_dom= NUM_PZ;
	}

	for (int j =0; j<4; j++){
		for(int i = 0; i < NUM_PZ; i++){
			domino_normal[0] = rand() %7;// se generan números aleatorios para cada lado del domino
			domino_normal[1] = rand() %7;
			domino_alreves[0] = domino_normal[1];
			domino_alreves[1] = domino_normal[0];

			if ((elem_in_array(domino_normal, usados,piezas_usadas) == 0) && //verificamos que no existan piezas repetidas
				 (elem_in_array(domino_alreves, usados,piezas_usadas) == 0)){// ni la pieza al reves
				usados[piezas_usadas][0] = domino_normal[0];
				usados[piezas_usadas][1] = domino_normal[1];
				manitas[j].dominos[i].derecha = domino_normal[0];
				manitas[j].dominos[i].izquierda = domino_normal[1];
				manitas[j].dominos[i].suma = domino_normal[1]+domino_normal[0];
				manitas[j].suma += manitas[j].dominos[i].suma;
				piezas_usadas++;	
			}
			else{
				i--;
			}
		}
	}

	//creacion de jugadores mediante forks
	for(int i = 0 ; i < 4 ; i++){
		pid = fork();
		contador ++; // esto hace que cada hijo tenga un valor distinto para contador
		if(pid == 0){
			break;
		}
	}

	//***************************************************************** Primera ronda *****************************************************************
	if (pid != 0){ //el padre decide quien es el primer jugador
		//cerramos los extremos que no se utilizaran de cada pipe
		for (int i =0; i<4 ; i++){
			close(PEHL[i][0]);
			close(PLHE[i][1]);
		}

		contador = 0; // el valor 0 de contador queda reservado para el padre
		//se escoge un jugador al azar para que comience el juego	
		primer_jugador =1 + rand() %4;
		jugador_actual = primer_jugador;
		printf("El primer jugador es el jugador numero: %d\n", primer_jugador);
		
		for(int i = 0; i<4; i++){
			if (i == primer_jugador-1){
				write(PEHL[i][1], &primer_jugador, sizeof(int));
			}
			else{
				write(PEHL[i][1], &mensaje, sizeof(int));			
			}

		}
	}
	else{//el primer jugador (o nodo hijo) debe colocar la pieza mas alta que tenga
		for (int i =0; i<4 ; i++){
			close(PEHL[i][1]);
			close(PLHE[i][0]);
		}
		switch(contador){ //el primer jugador recibe el valor real mientraas que el resto recibe un -1
			case 1: read(PEHL[0][0], &primer_jugador, sizeof(int));break;
			case 2: read(PEHL[1][0], &primer_jugador, sizeof(int));break;
			case 3: read(PEHL[2][0], &primer_jugador, sizeof(int));break;
			case 4 :read(PEHL[3][0], &primer_jugador, sizeof(int));break;
		}
		if(contador == primer_jugador){
			int max = -1;
			int pos = -1;
			for(int i = 0; i < NUM_PZ; i++){ // se coloca la pieza mas alta
				if (max < manitas[contador-1].dominos[i].suma){
					max = manitas[contador-1].dominos[i].suma;
					pos = i;
				}
			}
			//se coloca la pieza mas alta en la posicion central del tablero
			tablero[PZ_TOT].izquierda = manitas[contador-1].dominos[pos].izquierda;
			tablero[PZ_TOT].derecha = manitas[contador-1].dominos[pos].derecha;
			tablero[PZ_TOT].suma = manitas[contador-1].dominos[pos].suma;
			// se borra de la mano la pieza
			manitas[contador-1].dominos[pos].izquierda = -1;
			manitas[contador-1].suma = manitas[contador-1].suma - manitas[contador-1].dominos[pos].suma;
			manitas[contador-1] = actualizar_mano(manitas[contador-1]);

			// se imprime mano y tablero a primer jugador
			if(tipodeprint ==1){
				print_mano1(manitas[contador-1]);
				print_tab1(tablero,tableroptizq, tableroptder);
			}else{
				print_mano2(manitas[contador-1]);
				print_tab2(tablero,tableroptizq, tableroptder);
			}
			//se envia la pieza central al padre
			write(PLHE[contador-1][1], &tablero[PZ_TOT] ,sizeof(Domino));
		}
		else{
			write(PLHE[contador-1][1], &contador ,sizeof(int));
		}

	}
	if (pid != 0){// el padre hace el seteo inicial de las flags que se van a ir pasando entre jugador activo y el mismo y el tablero
		for(int i = 0; i<4; i++){
			if (i == jugador_actual-1){
				read(PLHE[i][0], &actual, sizeof(Domino));
			}
			else{
				read(PLHE[i][0], &mensaje, sizeof(int));
			}
		}
		// asigna el turno siguiente
		if(jugador_actual == 4){
			jugador_actual =1;
		}
		else{
			jugador_actual++;
		}

		// esto se revisara despues en menu para saber si jugar o no
		estadonulo.nadiegano = 0;



		estado.nadiegano = 1;
		estado.algunopudojugar = 1;
		estado.izq = tableroptizq;
		estado.der = tableroptder;

		//setea la pieza inicial
		estado.tablero[PZ_TOT].izquierda = actual.izquierda;
		estado.tablero[PZ_TOT].derecha = actual.derecha;
		estado.tablero[PZ_TOT].suma = actual.suma;
		
		for(int i = 0; i<4; i ++){
			estado.estadojuego[i] =2;
		} //seteo inicial del estado de juego

		for(int i = 0; i<4; i++){ // manda el estado correcto al padre y el nulo a los hijos
			if (i == jugador_actual-1){
				write(PEHL[i][1], &estado, sizeof(Estado));
			}else{
				write(PEHL[i][1], &estadonulo, sizeof(Estado));
			}
		}
	}

	//*****************************************************************juego principal *****************************************************************
	while((menu != 'q')&&(c_err < 1000)){
		c_err++;//por temas de debug y en caso de que llegase a fallar para que no quede iterando por siempre, en un juego normal no se deberia alcanzar ese numero
		if (pid != 0){ // padre
			for(int i = 0; i<4; i++){// recibe el estado del jugador que correspondo
				if (i == jugador_actual-1){
					read(PLHE[i][0], &estado, sizeof(Estado));
				}
			}
			//verifica las flags de termino de juego
			if (estado.nadiegano == 0){
				printf("ha ganado el jugador numero: %d\n", jugador_actual);
				estadonulo.nadiegano=2;
				estado.nadiegano = 2;
	
			}
			estadonulo.nadiegano =0;
			if (estado.algunopudojugar == 0){
				int minimo = 31;
				int ind;
				for(int i = 0; i < 4; i++){
					if(minimo < manitas[i].suma){
						minimo = manitas[i].suma;
						ind = i;
					}//busca el minimo de piezas
				}
				printf("ninguno de los jugadores puede colocar mas piezas, el ganador es: %d\n", (ind+1));
				estadonulo.nadiegano=2;//para que terminen los hijos
				estado.nadiegano =2;//para que terminen los hijos
			}

			//indica el jugador siguiente
			if(jugador_actual == 4){
				jugador_actual =1;
			}
			else{
				jugador_actual++;
			}

			//envia estados correspondientes a cada jugador
			for(int i = 0; i<4; i++){
				if (i == jugador_actual-1){
					write(PEHL[i][1], &estado, sizeof(Estado));
				}
				else{
					write(PEHL[i][1], &estadonulo, sizeof(Estado));
				}
			}

			if (estado.nadiegano== 2){
				exit(0);
			} // despues de mandar si alguno gano termina el programa
		}
		else{//hijos
			no_pudo_jugar = 0;
			switch(contador){
				case 1: read(PEHL[0][0], &estado, sizeof(Estado));break;
				case 2: read(PEHL[1][0], &estado, sizeof(Estado));break;
				case 3: read(PEHL[2][0], &estado, sizeof(Estado));break;
				case 4 :read(PEHL[3][0], &estado, sizeof(Estado));break;
			}
			if (estado.nadiegano ==2){//si alguno gano ya sale
				exit(0);
			}
			if(estado.nadiegano*estado.algunopudojugar != 0){// revisa si alguno gano, o si nadie pudo jugar
				printf("/-----------------------------------------------------------------------------------------------/ \n");
				printf("turno del jugador %d\n", contador);
				if (tipodeprint == 1){				// imprime mano y tablero
					print_tab1(estado.tablero,estado.izq, estado.der);
					print_mano1(manitas[contador-1]);
				}
				else{
					print_tab2(estado.tablero,estado.izq, estado.der);
					print_mano2(manitas[contador-1]);	
				}
				puedo_jugar = verificar_mano(manitas[contador-1], estado.tablero, estado.izq,estado.der);
				if (puedo_jugar != -1){
					print_estadojuego(estado.estadojuego);//imprime si se pudo jugar el estado del juego
					printf(" Seleccione (1-%d) para añadir una pieza al tablero o bien (q) para salir: \n", manitas[contador-1].n_dom);
					if (contador == 1){// caso jugador real
						scanf("%c%c", &menu, &weon);
					}
					else {//caso de que sea un bot
						int_menu = puedo_jugar;
						printf("%d\n", int_menu+1);
						if((estado.tablero[estado.izq+1].izquierda == manitas[contador-1].dominos[int_menu].derecha) ||
							(estado.tablero[estado.izq+1].izquierda == manitas[contador-1].dominos[int_menu].izquierda)){
							izqder =  'i';
						}
						else{
							izqder = 'd';
						}
					}

					if (menu != 'q'){
						if (contador == 1){
							int_menu = (int)(menu) - '1';
						}
						if ((0<=int_menu) && (int_menu<manitas[contador-1].n_dom)){
							printf("Seleccione si la pieza se colocara en la izquierda (i) o deredcha (d): \n");
							if(contador ==1){//caso real
								scanf("%c%c", &izqder,&weon);
							}else{//caso bot
								printf("%c\n", izqder);
							}

							flag = 1;
							if (izqder == 'i'){//verifica si se puede jugar, y si se puede juega
								if(estado.tablero[estado.izq+1].izquierda == manitas[contador-1].dominos[int_menu].derecha){
									flag =0;
									estado.tablero[estado.izq].izquierda = manitas[contador-1].dominos[int_menu].izquierda;
									estado.tablero[estado.izq].derecha = manitas[contador-1].dominos[int_menu].derecha;
									estado.tablero[estado.izq].suma = manitas[contador-1].dominos[int_menu].suma;
									estado.izq --;
								}
								else if(estado.tablero[estado.izq+1].izquierda == manitas[contador-1].dominos[int_menu].izquierda){
									flag =0;
									estado.tablero[estado.izq].izquierda = manitas[contador-1].dominos[int_menu].derecha;
									estado.tablero[estado.izq].derecha = manitas[contador-1].dominos[int_menu].izquierda;
									estado.tablero[estado.izq].suma = manitas[contador-1].dominos[int_menu].suma;
									estado.izq --;
								}
							}
							else if(izqder == 'd'){
								if(estado.tablero[estado.der-1].derecha == manitas[contador-1].dominos[int_menu].izquierda){
									flag =0;
									estado.tablero[estado.der].izquierda = manitas[contador-1].dominos[int_menu].izquierda;
									estado.tablero[estado.der].derecha = manitas[contador-1].dominos[int_menu].derecha;
									estado.tablero[estado.der].suma = manitas[contador-1].dominos[int_menu].suma;
									estado.der++;
								}
								else if(estado.tablero[estado.der-1].derecha == manitas[contador-1].dominos[int_menu].derecha){
									flag =0;
									estado.tablero[estado.der].izquierda = manitas[contador-1].dominos[int_menu].derecha;
									estado.tablero[estado.der].derecha = manitas[contador-1].dominos[int_menu].izquierda;
									estado.tablero[estado.der].suma = manitas[contador-1].dominos[int_menu].suma;
									estado.der++;
								}
							}

							if (flag ==1){// si no se pudo arroja un error y continua con el siguiente turno
								printf("Error al colocar la pieza: posicion invalida\n");
								no_pudo_jugar = 1;
							}
							else{
								manitas[contador-1].dominos[int_menu].izquierda = -1;
								manitas[contador-1].suma = manitas[contador-1].suma - manitas[contador-1].dominos[int_menu].suma;
								manitas[contador-1] =actualizar_mano(manitas[contador-1]);
								estado.estadojuego[contador-1] = 1;
								if (manitas[contador-1].n_dom == 0){
									estado.nadiegano =0;//si se queda sin piezas alguien gano
								}
							}	
						}
						else{
							printf("Error al colocar la pieza: indice %d invalido\n", int_menu);
							no_pudo_jugar = 1;
						}
					}
					else{
						printf("saltando turno \n");
						no_pudo_jugar = 1;
					}
				}
				else{
					printf("No se puede colocar ninguna pieza, saltando turno ... \n");
					no_pudo_jugar = 1;
				}
				if (no_pudo_jugar == 1){
					estado.estadojuego[contador-1] = 0;
					estado.algunopudojugar = 0;
					for(int i = 0; i<4; i++){
						if(estado.estadojuego[i] != 0){
							estado.algunopudojugar  = 1;
						} 
					}
				}
				switch(contador){//envia el estado del juego al padre
					case 1: write(PLHE[0][1], &estado, sizeof(Estado)); break;
					case 2: write(PLHE[1][1], &estado, sizeof(Estado));break;
					case 3: write(PLHE[2][1], &estado, sizeof(Estado));break;
					case 4 :write(PLHE[3][1], &estado, sizeof(Estado));break;
				}
			}
		}

	}
	return 0;
}