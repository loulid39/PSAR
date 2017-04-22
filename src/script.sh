#!/bin/bash


echo "break main" > commands
echo -e "command 1\n call initpapi()\n continue \nend" >>commands



c=1
for addr in `objdump -d -j .text $1 | awk -vRS=  '/<main>/' | grep callq | awk '{ print $1}' | sed 's/://g'`;
do
	echo "addr is 0x$addr"
	line=`addr2line -a 0x$addr -e main | tail -n1`
	echo "line is $line"
	number=`echo $line | grep -o -e [0-9]*$`
	
	echo "break $number"			>>commands
	echo "break `expr $number + 1`"		>>commands
	
	c=`expr $c + 1`
	echo -e "command $c \n call readpapi($number,0) \n continue \nend" 	>>commands
	
	c=`expr $c + 1`
	echo -e "command $c \n call readpapi($number,1)\n continue \nend" 	>>commands
	
done

c=`expr $c + 1`
last_line=`objdump -d -j .text $1 | awk -vRS=  '/<main>/'  | grep retq | awk '{ print $1}' | sed 's/://g'`
echo "b *0x$last_line">>commands
echo -e "command $c\n call stoppapi()\n continue \n end" >>commands




echo -e "set logging file gdb.txt\nset logging on\nset pagination off" >> commands

echo "set env LD_PRELOAD=$HOME/psar/src/libinject.so:$HOME/psar/papi-5.5.1/src/libpapi.so:$HOME/psar/papi-5.5.1/src/libpfm4/lib/libpfm.so" >>commands

echo "run" >> commands
