


.PHONY: test clean
all: main

main: main.c
	gcc -g -o $@ $<
		
%.o: %.c
	gcc -g $(CFLAGS) $< -I $(LIBPAPY)
	
clean:
	rm -f *.o main
	
	
