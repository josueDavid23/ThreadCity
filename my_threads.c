//Josue Rodriguez
//Kevin Rodriguez
//Jose Daniel Rodriguez
//Instituto Tecnologico de Costa Rica
//Curso: Sistemas Operativos

#include "scheduler.h"
#include "my_threads.h"
#include "my_mutex.h"

//executeExitContext
//Funcion que se ejecuta cuando un hilo termina
static void executeExitContext(){
    //printf("Hilo %d terminando\n", curcontext);
    deadThreads[curcontext] =1;
    total_tickets-=tickets[curcontext];
    active_threads_aux--;
    timer_interrupt(); //Selecciona el scheduler
}

//setExitContext
//Funcion que crea contexto para ejecutarse cuando un hilo termina
static void setExitContext(){
    static int exitContextCreated;
    if(!exitContextCreated){
        getcontext(&exitContext);
        exitContext.uc_link = 0;
        exitContext.uc_stack.ss_sp = malloc(STACKSIZE);
        exitContext.uc_stack.ss_size = STACKSIZE;
        exitContext.uc_stack.ss_flags= 0;
        makecontext(&exitContext, (void (*) (void))&executeExitContext, 0);
        exitContextCreated = 1;
    }
}

//setup
//Funcion que setea los hilos en caso de no haberse creado
void setup(){
	int i;
    for( i = 0;i <NUMTHREADS ;i++){
		deadThreads[i] = 0;
	}

	setExitContext();
    struct itimerval it;
    signal_stack = malloc(STACKSIZE);
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = INTERVAL * 1000;
    it.it_value = it.it_interval;
    setitimer(ITIMER_REAL, &it, NULL);
    struct sigaction act;
    act.sa_sigaction = timer_interrupt; //Selecciona el scheduler 
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigaction(SIGALRM, &act, NULL);

}

//my_thread_create
//Funcion que se encarga de crear los hilos
void my_thread_create(void *function, void *args, int tickets_sched, int priority_sched){
	//Si no se ha creado ningun hilo, primero setea todo
    if(!init){
        setup(); //Setea el hilos
    }
    void *stack;
    //Crea el contexto del hilo
    ucontext_t *uc = &threads[active_threads];
    getcontext(uc); //Inicializa el context
    stack = malloc(STACKSIZE);
    uc->uc_stack.ss_sp = stack;
    uc->uc_stack.ss_size = STACKSIZE;
    uc->uc_stack.ss_flags = 0;
    uc->uc_link = &exitContext; //Se reinicia antes de volver hacer el context
    sigemptyset(&uc->uc_sigmask);
    printf("%s", uc);
    makecontext(uc, function, 1, args);
    //Setea los datos para los schedulers
    tickets[active_threads] = tickets_sched; //Tickets del scheduler
    priority[active_threads] = priority_sched; //Prioridad del scheduler
    total_tickets+=tickets_sched;
    active_threads++;
    active_threads_aux++;
  //  printf("Se creo un hilo de manera correcta");
}

//my_thread_end
//Funcion que termina el hilo
void my_thread_end(){
    deadThreads[curcontext] =1;
    total_tickets-=tickets[curcontext];
    active_threads_aux--;
    timer_interrupt();//Selecciona el scheduler
}

//my_thread_yield
//Funcion que cesde el procesador
void my_thread_yield(){
    timer_interrupt();//Selecciona el scheduler
}

//run_threads
//Funcion que pone a correr los hilos
void run_threads(){
    current_thread = &threads[0];
    setcontext(&threads[0]);
}
