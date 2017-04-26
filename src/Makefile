


.PHONY: test clean
all: color

color: color.c
	gcc -o $@ $<	

test: color
	make -C lib
	make -C test main
	chmod u+x memprof 
	sh memprof test/main test/main.c

	

	
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(LIBPAPY)
	
	
clean:
	rm -f *.o color commands
	
	
