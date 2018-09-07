//Josue Rodriguez
//Kevin Rodriguez
//Jose Daniel Rodriguez
//Instituto Tecnologico de Costa Rica
//Curso: Sistemas Operativos

#include "my_threads.h"
#include "scheduler.h"

//my_thread_csched
//Funcion que recibe un char del tipo de scheduler
//Asigna a la variable active_sched el valor segun el scheduler enviado
void my_thread_chsched(char *sched){
    if(!strcmp(sched,"RoundRobin")){
        active_sched = 0; 
    }
    if(!strcmp(sched,"Sorteo")){
        active_sched = 1;
    }
    if(!strcmp(sched,"Real")){
        active_sched = 2;
    }
}

//scheduler
//Funcion que activa los hilos con el algoritmo de RoundRobin
void scheduler(){
    if(active_threads_aux > 0){
        curcontext = (curcontext + 1);
        if(deadThreads[curcontext% active_threads]){
            while(deadThreads[curcontext% active_threads]){
                curcontext+=1;
            }
        }
        curcontext = curcontext % active_threads;
        current_thread = &threads[curcontext];
        setcontext(current_thread); //Activa el nuevo hilo 
    }
}

//sched_sorteo
//Funcion que activa los hilos con el algoritmo de Sorteo
void sched_sorteo(){
    srand(time(NULL));
    int aux;
    if(active_threads_aux > 0){
        int winner = rand()%(total_tickets+1);//Ganador del sorteo
        aux = winner;
        int i;
        for (i = 0; i < active_threads; i++) {//Revisa el ganador
            aux -= tickets[i];
            if(aux<=0){
                if(deadThreads[i% active_threads]){
                    while(deadThreads[i% active_threads]){
                        i+=1;
                    }
                }
                curcontext = i;
                current_thread = &threads[curcontext];
                break;
            }else{
                tickets[i]++;
                total_tickets++;
            }
        }
        setcontext(current_thread);//Activa el nuevo hilo
    }
}

//sched_real
//Funcion que activa los hilos con el algoritmo de Tiempo Real
void sched_real(){
    int aux = -1;
    if(active_threads_aux > 0){
    	int i;
        for (i = 0; i < active_threads; i++) {//Busca el hilo de mayor prioridad que aun no haya finalizado
            if(aux<priority[i]&&!deadThreads[i] && !priority_aux[i]){
                curcontext = i;
                aux = priority[i];
            }
        }
        if(aux == -1){
            for (i = 0; i < active_threads; i++) {
                priority_aux[i] = 0;
            }
            sched_real();
        }else{
            priority_aux[curcontext] = 1;//Hilo ya ejecutado
            current_thread = &threads[curcontext];
            setcontext(current_thread); //Activa el nuevo hilo
        }
    }
}
//timer_interrupt
//Crea el context segun el tipo de scheduler
void timer_interrupt(){
    getcontext(&signal_context);
    signal_context.uc_stack.ss_sp = signal_stack;
    signal_context.uc_stack.ss_size = STACKSIZE;
    signal_context.uc_stack.ss_flags = 0;
    sigemptyset(&signal_context.uc_sigmask);
    //Si es de round robin
    if(active_sched == 0){
		makecontext(&signal_context, scheduler, 1);
	}
	//Si es de sorteo
    if(active_sched == 1){
		makecontext(&signal_context, sched_sorteo, 1);
	}
	//Si es de tiempo real
    if(active_sched == 2){
		makecontext(&signal_context, sched_real, 1);
	}
	//Cambia el context
    swapcontext(current_thread,&signal_context);
}
