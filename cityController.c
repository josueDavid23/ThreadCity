//Josue Rodriguez
//Kevin Rodriguez
//Jose Daniel Rodriguez
//Instituto Tecnologico de Costa Rica
//Curso: Sistemas Operativos

#include "cityController.h"
#include "my_mutex.h"
#include "my_threads.h"
#include "scheduler.h"
#include <math.h>

//Colores
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define IN 99
#define N 42

//Variables
my_mutex fieldLock;
char* matriz[6][7];
int semaforo =0;
int bandera=0;
int cronometro =0;

//cityController
//Funcion que se encarga de controlar el hilo de la ciudad
//Inicia los hilos de los carros,ambulancias,planta nuclear y los barcos
//Dentro de un while infinito que va estar actualizando la matriz segun la accion de los distintos hilos
void *cityController(){
	//Random
	srand(time(NULL));
	iniciarMatriz(); //Inicia la matriz
    my_mutex_init(&fieldLock); //Inicia el mutex
    startCars(); //Inicia los hilos de los carros
    startNuclear(); //Inicia el hilo de la planta nuclear
    startAmbulance(); //Inicia los hilos de las ambulancias
    startShip(); //Inicia los hilos de los barcos
    //While infinito
    while (1) {
		//Si la planta nuclear no ha explotado
    	if (bandera == 0){
	    	printf("\n--------------------------------------------------\n\n");
		    matrizImpresion(); //Imprime la matruz
		    cronometro++; //Suma al cronometro de la planta nuclear
		    printf("\n\t                         TIEMPO: %d\n", cronometro);
		    //  printMatriz();
		    usleep(2500000000); //Sleep
	        system("clear");
	    }
	    else{
	    	bandera=0; //Vuelve a iniciar la planta nuclear
			cronometro=0;
			printf("			                        . . .  \n");
			printf("                         |||                    \n");
			printf("                       `--+--'                       \n");
			printf("                         |||                          \n");
			printf("                        ' | '                         \n");
			printf("                          |                           \n");
			printf("                          |                           \n");
			printf("                      ,--'#`--.                       \n");
			printf("                      |#######|                       \n");
			printf("                   _.-'#######`-._                    \n");
			printf("                ,-'###############`-.                 \n");
			printf("              ,'#####################`,               \n");
			printf("             /#########################|              \n");
			printf("            |###########################|             \n");
			printf("           |#############################|            \n");
			printf("           |#############################|            \n");
			printf("           |#############################|            \n");
			printf("           |#############################|            \n");
			printf("            |###########################|             \n");
			printf("             |#########################/              \n");
			printf("              `.#####################,'               \n");
			printf("                `._###############_,'                 \n");
			printf("                   `--..#####..--'      \n");
			printf(ANSI_COLOR_RESET"\n\n \t\t -> LA PLANTA NUCLEAR HA EXPLOTADO BOOOOOOOOOOOOOOOOOOOOOOOOOOM!\n\n");
			sleep(1000000000000);
			usleep(250000000000); //Sleep
			
			system("clear");

	    }
    }
}

//matrizImpresion
//Funcion que imprime la matriz representativa
void matrizImpresion(){
	char* matrizImpresion[11][7]={{"*_____","*_____","*_____","*_____","*_____","*_____","*\n"},{"|     ","|     ","|     ","      ","|     ","|     ","|\n"},{"*_____","*_____","*_____","©_____","*_____","*_____","*\n\n"},
									{"░░░░░░","██░░░░","░░░░░░","█░░░░░","░░░░░░","█░░░░░","░"},{"*_____","*_____","*     ","*     ","*     ","*     ","*\n"},{"      ","|     ","      ","|     ","|     ","|     ","|\n"},
									{"*_____","*_____","*_____","*_____","*_____","*_____","*\n"},{"|     ","      ","|     ","|     ","      ","|     ","|\n"},{"*_____","*_____","*_____","*_____","*_____","*_____","*\n"},
									{"|     ","      ","|     ","|     ","      ","|     ","|\n"},{"*_____","*_____","*_____","*_____","*_____","*_____","*\n"}};
	int i,j;
	int contador =0;
	//For para imprimir la matriz representativa
	printf(ANSI_COLOR_YELLOW"\t|_xxxxxx_ |_xxxxxx_ |_xxxxxx_ |_xxxxxx_\n");    
 	printf(ANSI_COLOR_YELLOW"\t| ╔════╗  | ╔════╗  | ╔════╗  | ╔════╗ \n"); 
 	printf(ANSI_COLOR_YELLOW"\t| ║ CO ║  | ║ ME ║  | ║ RC ║  | ║ IO ║ |\n"); 
 	printf(ANSI_COLOR_YELLOW"\t| ╚════╝  | ╚════╝  | ╚════╝  | ╚════╝ |\n");
 	printf(ANSI_COLOR_YELLOW"\t|_ ░▓░ _   _ ░▓░ _   _ ░▓░ _   _ ░▓░ _ |\n\n"ANSI_COLOR_RESET);

	for(i=0;i<11;i++){
		if(i%2 == 0){
			printf("\t");
			for (j=0;j<7;j++){
				//printf("entro en %d",i);
				if(matriz[contador][j]== "C     "){
					printf(ANSI_COLOR_GREEN "%s",matriz[contador][j]);
				}
				else if(matriz[contador][j]== "A     "){
					printf(ANSI_COLOR_RED "%s",matriz[contador][j]);
				}

				else{
					printf(ANSI_COLOR_CYAN "%s",matriz[contador][j]);
				}
			}
			//Imprime los rios
			if(i == 4){
				printf(ANSI_COLOR_BLUE "\n\t░░░░░░██░░░░░░░░░░█░░░░░░░░░░░█░░░░░░");
				if (semaforo == 0) { // verde
					printf(ANSI_COLOR_GREEN "  ©" ANSI_COLOR_YELLOW "©" ANSI_COLOR_RED "©" ANSI_COLOR_RESET " SEMAFORO:" ANSI_COLOR_GREEN"  █\n");
				}
				else{
					printf(ANSI_COLOR_GREEN "  ©" ANSI_COLOR_YELLOW "©" ANSI_COLOR_RED "©" ANSI_COLOR_RESET " SEMAFORO:" ANSI_COLOR_RED"  █\n");

				}

			}
			contador++;
			printf("\n");
		}
		printf("\t");

		//Imprime los rios
		for( j =0; j<7;j++){
			if(i ==3){
				printf(ANSI_COLOR_BLUE "%s",matrizImpresion[i][j]);


			}
			else{
				printf(ANSI_COLOR_RESET "%s",matrizImpresion[i][j]);

			}

		}
		//Imprime los semaforos
		if(i==3){
			if (semaforo == 0) { // verde
					printf(ANSI_COLOR_GREEN "  ©" ANSI_COLOR_YELLOW "©" ANSI_COLOR_RED "©" ANSI_COLOR_RESET " SEMAFORO:" ANSI_COLOR_GREEN"  █\n");
				}

			else{
				printf(ANSI_COLOR_GREEN "  ©" ANSI_COLOR_YELLOW "©" ANSI_COLOR_RED "©" ANSI_COLOR_RESET " SEMAFORO:" ANSI_COLOR_RED"  █\n");


			}
		}

	}
	//Imprime la planta nuclear
	printf("	           _"ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET"_░▓░_"ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET"_\n");
	printf("	          | ╔════╗  |\n");
	printf("	          "ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET" ║ PN ║  "ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET"\n");
    printf("                  "ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET" ╚════╝  "ANSI_COLOR_YELLOW"x"ANSI_COLOR_RESET"\n");
    printf("                  |_"ANSI_COLOR_YELLOW"xxxxxxx"ANSI_COLOR_RESET"_|\n");


}


//printMatriz
//Print de la matriz
void printMatriz(){
	int i,j;
	for(i=0;i < 6; i++){
		printf("\t");
		for(j=0;j < 7; j++){
			//matriz[i][j]='c';
			printf("%s",matriz[i][j]);

		}
		printf("\n");
	}
	printf("\n\n");
}

//nuclearPlantController
//Controller de la planta nuclear
//While infinito para controlar la planta si ha explotado o no
void *nuclearPlantController(){
	while(1){
		if(cronometro >= 100){
			bandera=1;

		}
		// verificar tiempo e impresion
	}
}

//carController
//Funcion que controla los hilos de los carros
//Controla los semaforos, el paso de los puentes (prioridad) y el ceda
void *carController(){
	//While infinito para sacar los random donde se va mover los carros(pos inicial y final)
	while(1){
		//pthread_mutex_lock(&mutex);
		int ruta[N];
		//my_mutex_lock(&fieldLock);
		int r = rand() % 41;
		int r2 = rand() % 41;
		while(r==r2 || (r>=14 && r<=20) || (r2>=14 && r2<=20)){
			r2 = rand() % 41;
			r = rand() % 41;
		}
		//printf("hilo: %i-%i",r,r2);
		int len=dijsktra(r,r2,ruta);
		int x=0,y=0,z;

		int posAnterior=-1;
		//For para recorrer la ruta que retorno el dijkstra
		for(z=0;z<len+1;z++){
			//printf("%d /n",ruta[z]);
			usleep(250000);
			int pos =ruta[z];
			x = pos/7;
			y = pos%7;
			//Si hay una ambulancia en el nodo del puente y el carro se encuentra en alguno de los extremos, se debera de esperar hasta que dicha ambulancia
			//pase por el puente por eso el !=A
			if(x ==2 && y ==1 ){ //PRIORIDAD PUENTE1 Y SEMAFORO
					while(1){
						if(semaforo == 0 && matriz[2][1] != "A     " &&  matriz[3][1] != "A     "&& matriz[1][1] != "A     "){// esta en verde
							break;
						}
						usleep(10000);
					}

			}
			else if(x ==2 && y ==3 ){ //PRIORIDAD PUENTE2
					while(1){
						if(matriz[2][3] != "A     " && matriz[3][3] != "A     "  && matriz[1][3] != "A     "){// esta en verde
					
							break;
						}
						usleep(10000);

					}

			}
			else if(x ==2 && y ==5){ //PRIORIDAD PUENTE3 Y SEMAFORO
					while(1){
						if(matriz[2][5] != "A     " && matriz[1][5] != "A     " && matriz[3][5] != "A     "){// esta en verde
							
							break;
						}
						usleep(10000);

					}
			}
			
			if(1){
				matriz[posAnterior/7][posAnterior%7]="      ";
			}
			posAnterior=ruta[z];

			matriz[x][y]="C     ";
			if (x == 5 &&  y ==2 || x ==5 && y == 3){
				cronometro=0;
			}
			usleep(250000);
			my_thread_yield();
			//Controla los cedas (matriz[2][3] es el centro del puente)
			while(1){
				if(matriz[2][3] == "C     " || matriz[2][3] == "A     "){
					//matriz[1][2] =="A      "||matriz[1][2]=="C     "&&matriz[1][4]=="A     "||matriz[1][4]=="C     "
					if(pos/7 == 1 && pos%7 == 2 || pos/7 == 1 && pos%7 == 4){
						//printf("x %d \n",pos/7);
						//printf("x %d \n",pos%7);
						printf("\n -> CEDA\n");
						usleep(9990000);
					}
					else{
						break;
					}
				}else{
					break;
				}
			}
		}
		//Pone una x donde termina el recorrido del carro
		matriz[x][y]="x     ";
		usleep(2500000);
		//Luego lo pone vacio de nuevo
		matriz[x][y]="      ";
	}
}

//ambulanceController
//Funcion que controla los hilos de las ambulancias
//Controla los semaforos y el ceda
void *ambulanceController(){
	while(1){
		//pthread_mutex_lock(&mutex);
		int ruta[N];
		//my_mutex_lock(&fieldLock);
		int r = rand() % 41;
		int r2 = rand() % 41;
		while(r==r2 || (r>=14 && r<=20) || (r2>=14 && r2<=20)){
			r2 = rand() % 41;
			r = rand() % 41;
		}
		//printf("hilo: %i-%i",r,r2);
		//Saca ruta mas corta hacia el destino
		int len=dijsktra(r,r2,ruta);
		int x=0,y=0,z;
		
		//For para recorrer la ruta del dijkstra
		int posAnterior=-1;
		for(z=0;z<len+1;z++){
			//printf("%d /n",ruta[z]);
			usleep(250000);
			int pos =ruta[z];
			x = pos/7;
			y = pos%7;
			//Controla los semaforos
			if(x ==2 && y ==1 && semaforo ==1  ){
					while(1){
						if(semaforo == 0){

							break;
						}
						usleep(1000);
					}

			}

			if(1){
				matriz[posAnterior/7][posAnterior%7]="      ";
			}

			posAnterior=ruta[z];
			

			//Pone una A donde se va mover la ambulancia
			matriz[x][y]="A     ";
			usleep(250000);
			//Cede el procesador
			my_thread_yield();
			//Ceda
			while(1){
				if(matriz[2][3] == "C     " || matriz[2][3] == "A     "){
					//matriz[1][2] =="A      "||matriz[1][2]=="C     "&&matriz[1][4]=="A     "||matriz[1][4]=="C     "
					if(pos/7 == 1 && pos%7 == 2 || pos/7 == 1 && pos%7 == 4){
						//printf("x %d \n",pos/7);
						//printf("x %d \n",pos%7);
						printf("\n -> CEDA\n");
						usleep(9990000);
					}
					else{
						break;
					}
				}else{
					break;
				}
			}


		}
		matriz[x][y]="x     "; //Pone una x por donde termino
		usleep(2500000);
		matriz[x][y]="      "; //Pone vacio
	}
	//my_mutex_unlock(&fieldLock);
}

//shipController
//Funcion que controla los hilos de los barcos
void *shipController(){
	while(1){
		//pthread_mutex_lock(&mutex);
		int ruta[N];
		int r = 14;
		int r2 = 16;
		//printf("hilo: %i-%i",r,r2);
		int len=dijsktra(r,r2,ruta);
		int x=0,y=0,z;
		int posAnterior=-1;
		//For para recorrer ruta
		for(z=0;z<len+1;z++){
			//printf("%d /n",ruta[z]);
			usleep(250000);
			int pos =ruta[z];
			if(posAnterior!=-1 && matriz[pos/7][pos%7]!="B     "){
				matriz[posAnterior/7][posAnterior%7]="      ";
			}
			posAnterior=ruta[z];
			x = pos/7;
			y = pos%7;
			matriz[x][y]="B     ";
			//Setea los semaforos si el barco esta en la posicion 2,1 de la matriz (lo pone en rojo el semaforo del puente)
			if (x== 2 && y == 1){
				semaforo =1;
			}
			else{
				semaforo=0;
			}
			usleep(250000);
			//Cede el procesador
			my_thread_yield();
		}
		matriz[x][y]="x     "; //X donde termino el recorrido
		usleep(2500000);
		matriz[x][y]="      "; //Vuelve a poner en vacio
	}
	//my_mutex_unlock(&fieldLock);
}


//dijkstra
//Funcion que encuentra la ruta mas corta
//Recine el nodo de inicio, final y un arreglo donde guardara los nodos de la ruta
int dijsktra(int source,int target,int ruta[N]){
		//Matriz de adyacencia
		int cost[42][42]=
				//0     //1 //2 //3 //4 //5 //6//7//8 //9 //10 //11//12//13//14//15//16//17//18//19//20//21//22//23//24//25//26//27//28//29//30//31//32//33//34//35//36//37//38//39//40//41
				{{0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99}, //0
				{1,  	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//1
				{99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//2
				{99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//3
				{99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//4
				{99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//5
				{99,	99,	99,	99,	99,	1,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//6
				{1,	    99,	99,	99,	99,	99,	99,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//7
				{99,	    1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//8
				{99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//9
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//10
				{99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//11
				{99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//12
				{99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//13
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//14
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//15
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//16
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//17
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//18
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//19
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//20
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//21
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//22
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//23
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//24
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//25
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99,	99},//26
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	99},//27
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99},//28
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99},//29
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99},//30
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99,	99,	99},//31
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	99,	99,	99},//32
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99,	99,	1,	99},//33
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	99,	99,	99,	99,	99,	99,	1},//34
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	99,	0,	1,	99,	99,	99,	99,	99},//35
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99,	99},//36
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99,	99},//37
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1,	99,	99},//38
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	0,	1,	99},//39
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,	99,	99,	99,	99,	99,	1,	0,	1},//40
				{99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	99,	1,  99,	99,	99,	99,	99,	1,	0}};//41
    
    int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j;
    int path[N]={-1};
    for(i=0;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = IN;
        m = 0;
        for(i=0;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j] = start;
        start = prev[start];
        j++;
    }
    //path[j]='\0';
    //strrev(path);
    int p,q=0;
	for(p=dist[target];p >= 0; p--){
		ruta[q] = path[p];
		//printf("%i->",path[p]);
		q++;
	}
	printf("\n");
    //printf("%s", path);
    //Retorna un arreglo con la ruta
    return dist[target];
}

//iniciaMatriz
//Funcion que inicia la matriz
void iniciarMatriz(){
	int i,j;
	for (i=0;i<6;i++){
		for(j=0;j<7;j++){
			matriz[i][j]="      ";
		}
	}

}

//verificar
//Verifica si el nodo esta en la ruta
int verficar(int ruta[],int numero){
	int i;
	for (i=0;i< sizeof(ruta);i++){
		if(ruta[i]== numero){
			return 1;
		}
	}
	return 0;
}

//startCars
//Crea los hilos de los carros
void startCars(){
    my_thread_create(carController, NULL,5,5);
//	my_thread_create(carController, NULL,5,5);
//	my_thread_create(carController, NULL,5,5);
//	my_thread_create(carController, NULL,5,5);
	
}

//startAmbulance
//Crea los hilos de las ambulancias
void startAmbulance(){
	my_thread_create(ambulanceController, NULL,5,1);
//	my_thread_create(ambulanceController, NULL,5,1);
}

//startShips
//Crea los hilos de los barcos
void startShip(){
	my_thread_create(shipController, NULL,5,1);
}

//startNuclear
//Crea los hilos de la planta nuclear
void startNuclear(){
	my_thread_create(nuclearPlantController, NULL,5,5);
}
