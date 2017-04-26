


.PHONY: test clean
all: color test


test:
	make -C lib
	make -C test main
	chmod u+x memprof 
	sh memprof test/main test/main.c

	
color: color.c
	gcc -o $@ $<	
	
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(LIBPAPY)
	
	
clean:
	rm -f *.o commands
	
	
