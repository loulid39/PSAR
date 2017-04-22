#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "debug.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>


int NB_EVENTS=2;

int * events;
long long * values; 
int quant_total;
int prem = 1;

FILE* fd;

	
void initpapi()
{
	quant_total = 0;
	fd=fopen("./papi_log.txt", "w+");
	if(!fd)
	{
		perror("echec creation du fichier");
		exit(1);
	
	}
	events = malloc(sizeof(int)*NB_EVENTS);
	values = malloc(sizeof(long long)*NB_EVENTS);
	
	events[0]=PAPI_L3_TCM;
	events[1]=PAPI_TOT_CYC;

	
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



void readpapi(int l, int bool)
{     
	PAPI_read_counters(values, NB_EVENTS);
	quant_total +=values[0]/16384; 
	if(prem){
		fprintf(fd,"                    \n");
		fflush(fd);
		prem = 0;
	}
	if(bool)
	{
		fprintf(fd,"%d %lld %f\n", l,(values[0]/16384),(pow(10,-9)*values[1]));
		fflush(fd);
	}
}



void stoppapi()
{
	
	if(PAPI_stop_counters(values,NB_EVENTS)!=PAPI_OK)
	{
		perror("stop counters");
		exit(1);
	}
		
	fseek(fd,0,SEEK_SET);	
	fprintf(fd,"%d",quant_total);
	fflush(fd);
	printf(DEBUG"l3 cache miss %lld %f\n", values[0],(pow(10,-9)*values[1]));
	fclose(fd);
}
