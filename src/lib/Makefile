
include ../.config

CFLAGS= -fPIC  -c
LDFLAFS = -lpapi
LIBPAPY = $(PATH_TO_PSAR)/papi-5.5.1/src/

.PHONY: clean distclean


	
libinject.so :  libinject.o 
	gcc -shared -o $@ $^ 
	
	
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(LIBPAPY)
	
	
clean:
	rm -f *.o

distclean:
	rm -f *.so *.so
	
	
