
CFLAGS= -fPIC  -c
LDFLAFS = -lpapi


.PHONY: test clean
all: main  test


test: main libinject.so
	chmod u+x memprof 
	sh memprof $^ 
	
libinject.so :  libinject.o 
	gcc -shared -o $@ $^ 
	
main: main.c
	gcc -g -o $@ $<
	
	

	
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(HOME)/psar/papi-5.5.1/src/
	
	
clean:
	rm -f *.o main main_papi
	
	
