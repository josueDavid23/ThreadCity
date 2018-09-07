#ifndef scheduler_h
#define scheduler_h
#include <time.h>
#include <string.h>

void my_thread_chsched(char *sched); //Cambia el scheduler

void run_threads(); //Corre los hilos 

void scheduler(); //Scheduler de Round Robin

void sched_sorteo(); //Scheduler de Sorteo

void sched_real(); //Scheduler de Tiempo real

void timer_interrupt(); //Crea el context segun el tipo de scheduler

#endif
