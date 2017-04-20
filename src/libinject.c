#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "debug.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int NB_EVENTS=1;

int * events;
long long * values; 

FILE* fd;

	
void initpapi()
{
	fd=fopen("./papi_log.txt", "w+");
	if(!fd)
	{
		perror("echec creation du fichier");
		exit(1);
	
	}
	events = malloc(sizeof(int)*NB_EVENTS);
	values = malloc(sizeof(long long)*NB_EVENTS);
	
	events[0]=PAPI_L3_TCM; //PAPI_L2_TCM;

	
	printf(DEBUG"avail counters is %d\n", PAPI_num_counters ());


	const PAPI_hw_info_t *hwinfo = NULL;
        
	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
	  exit(1);


	int retval;
	if( (retval=PAPI_start_counters( events, NB_EVENTS )) != PAPI_OK )
	{
		fprintf(stderr,DEBUG"start counters %d", retval);
         	exit(1);
        }  
        
}



void readpapi(int l)
{     
	PAPI_read_counters(values, NB_EVENTS);
	//printf(DEBUG"l2 cache miss %lld %d\n", values[0]);
	fprintf(fd,"%d, l3 cache miss %lld\n", l,values[0]);
	fflush(fd);
}



void stoppapi()
{
	
	if(PAPI_stop_counters(values,NB_EVENTS)!=PAPI_OK)
	{
		perror("stop counters");
		exit(1);
	}
		
	printf(DEBUG"l3 cache miss %lld\n", values[0]);
	fclose(fd);
}
