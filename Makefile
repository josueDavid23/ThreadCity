THREADHEADERS = my_threads.h cityController.h my_mutex.h scheduler.h
THREADFILES = main.c my_threads.c cityController.c my_mutex.c scheduler.c

EXE = main

all: 
	gcc $(THREADHEADERS) $(THREADFILES) -o $(EXE)

run_default_main:
	./$(EXE) 

clean:
	rm $(EXE)

