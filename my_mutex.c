//Josue Rodriguez
//Kevin Rodriguez
//Jose Daniel Rodriguez
//Instituto Tecnologico de Costa Rica
//Curso: Sistemas Operativos

#include "my_mutex.h"

//my_mutex_init
//Funcion que inicializa el mutex
void my_mutex_init(my_mutex *lock){
	lock = 0;
}

//atomic_xchg
//xchg que permite hacer la operacion y la asignacion atomica
int atomic_xchg(my_mutex * lock){
    unsigned int  tmp = 1;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
    return tmp;
}

//test_and_set
//Funcion que hace el test and set para el lock
int test_and_set(my_mutex *lock){
    return atomic_xchg(lock);
}

//my_mutex_destroy
//Funcion que libera o destruye el mutex
void my_mutex_destroy(my_mutex *lock){
    //free(lock);
}

//my_mutex_lock
//Funcion que hace el lock del mutex
void my_mutex_lock(my_mutex *lock){
    while (*lock){
        sleep(1);
    }
    test_and_set(lock);
}

//my_mutex_trylock
//Funcion para try-lock del mutex
void my_mutex_trylock(my_mutex *lock){
    while (*lock){
        usleep(1000);
    }
    test_and_set(lock);
}

//my_mutex_unlock
//Metodo que desbloquea el mutex
void my_mutex_unlock(my_mutex *lock){
    unsigned int  tmp = 0;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
}
