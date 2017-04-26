
include .config

CFLAGS= -fPIC  -c
LDFLAFS = -lpapi
LIBPAPY = $(PATH_TO_PSAR)/papi-5.5.1/src/

.PHONY: test clean
all: main  color test


test: main main.c color libinject.so
	chmod u+x memprof 
	sh memprof $^ 
	
libinject.so :  libinject.o 
	gcc -shared -o $@ $^ 
	
main: main.c
	gcc -g -o $@ $<
	
color: color.c
	gcc -o $@ $<	

	
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(LIBPAPY)
	
	
clean:
	rm -f *.o main main_papi
	
	
