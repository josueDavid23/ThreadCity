//Josue Rodriguez
//Kevin Rodriguez
//Jose Daniel Rodriguez
//Instituto Tecnologico de Costa Rica
//Curso: Sistemas Operativos

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cityController.h"
#include "my_mutex.h"
#include "my_threads.h"
#include "scheduler.h"

//Main
//Crea el hilo que va controlar la ciudad
//Se cambia el scheduler para que funcione con el scheduler especificado
//Real = Scheduler Tiempo Real
//RoundRobin = Scheduler Round Robin
//Sorteo = Scheduler Sorteo
//Al final pone a correr los distintos hilos con run_threads
int main(int argc, char *argv[]){
	
    my_thread_create(cityController,NULL,5,5); //Crea el hilo que manejara la ciudad
    my_thread_chsched("RoundRobin"); //Tipo de scheduler (Para cambiar el scheduler)
    run_threads(); //Pone a correr los hilos
    
    return 0;
}
