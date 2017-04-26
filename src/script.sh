#!/bin/bash

source .config

LIBPAPY=$PATH_TO_PSAR/papi-5.5.1/src
LIBINJECT=$PATH_TO_PSAR/src/lib



echo "break main" > commands
echo -e "command 1\n\tcall initpapi()\n\tcontinue\nend" >>commands



c=1
for addr in `objdump -d -j .text $1 | awk -vRS=  '/<main>/' | grep callq | awk '{ print $1}' | sed 's/://g'`;
do
	echo "addr is 0x$addr"
	line=`addr2line -a 0x$addr -e $1 | tail -n1`
	echo "line is $line"
	number=`echo $line | grep -o -e [0-9]*$`
	
	echo "break $number"			>>commands
	echo "break `expr $number + 1`"		>>commands
	
	c=`expr $c + 1`
	echo -e "command $c\n\tcall readpapi($number,0)\n\tcontinue\nend" 	>>commands
	
	c=`expr $c + 1`
	echo -e "command $c\n\tcall readpapi($number,1)\n\tcontinue\nend" 	>>commands
	
done

c=`expr $c + 1`
last_line=`objdump -d -j .text $1 | awk -vRS=  '/<main>/'  | grep retq`

if  [ -z "$last_line" ]; then
    last_line=`objdump -d -j .text $1 | awk -vRS=  '/<main>/'  | tail -1`
fi;

last_line=`echo $last_line| awk '{ print $1}' | sed 's/://g'`

echo "b *0x$last_line">>commands
echo -e "command $c\n\tcall stoppapi()\n\tcontinue\nend" >>commands




echo -e "set logging file gdb.log\nset logging on\nset pagination off" >> commands
echo "set env LD_PRELOAD=$LIBINJECT/libinject.so:$LIBPAPY/libpapi.so:$LIBPAPY/libpfm4/lib/libpfm.so" >>commands

echo "run" >> commands
