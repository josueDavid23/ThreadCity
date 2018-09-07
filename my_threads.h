#ifndef my_threads_h
#define my_threads_h

#include <ucontext.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMTHREADS 100
#define STACKSIZE 4096
#define INTERVAL 100

sigset_t set;
//ucontext
ucontext_t signal_context;
ucontext_t threads[NUMTHREADS];
ucontext_t *current_thread;
ucontext_t exitContext;

//Variables
int priority[NUMTHREADS];
int priority_aux[NUMTHREADS];
int tickets[NUMTHREADS];
int deadThreads[NUMTHREADS];
int curcontext;
int init;
int active_threads;
int active_threads_aux;
int total_tickets;
int active_sched;


void my_thread_create(void *function,void *args, int tickets_sched, int priority_sched); //Crea el hilo

void my_thread_end(); //Termina el hilo

void my_thread_yield(); //Cede el procesador

void run_threads(); //Corre los hilos

//static void setExitContext();

void *signal_stack; //Signal stack

static void setExitContext(); //Crea el contexto para ejecutarse cuando un hilo termina

void setup(); //Setea los hilos

#endif
