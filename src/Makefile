
CFLAGS= -fPIC  -c
LDFLAFS = -lpapi


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
	gcc -g $(CFLAGS) $< -I $(HOME)/psar/papi-5.5.1/src/
	
	
clean:
	rm -f *.o main main_papi
	
	
