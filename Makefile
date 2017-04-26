


install:
	cd papi-5.5.1/src;\
	 ./configure
	echo "PATH_TO_PSAR="`pwd`"" > src/.config
	make -j9 -C papi-5.5.1/src shared
	make -C src main libinject.so
	
	
test:
	make -C src test 
	
	
clean:
	make -C papi-5.5.1/src  clean
	make -C src clean
