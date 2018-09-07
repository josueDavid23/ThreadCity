#ifndef my_mutex_h
#define my_mutex_h

#include <stdio.h>
#include <unistd.h>

#define my_mutex int

void my_mutex_init(my_mutex *lock); //Inicializa el mutex

void my_mutex_lock(my_mutex *lock); //Lock del mutex

void my_mutex_trylock(my_mutex *lock); //Try lock del mutex

void my_mutex_unlock(my_mutex *lock); //Unlock del mutex

void my_mutex_destroy(my_mutex *lock); //Destuye el mutex
 

#endif
