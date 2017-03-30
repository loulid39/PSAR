#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

#define SIZE 26214400
int *data;
/*int *ares;
int *ares_r;
int *ares;
int *ares_r;*/

void init_tab(){
	printf("Debut init_tab\n");
	int i;
	data = (int*)(malloc(SIZE * sizeof(int)));
	/*ares = (int*)(malloc(SIZE * sizeof(int)));
	ares_r = (int*)(malloc(SIZE * sizeof(int)));
	ares = (int*)(malloc(SIZE * sizeof(int)));
	ares_r = (int*)(malloc(SIZE * sizeof(int)));*/
	
	for(i=0;i<SIZE;i++){
		data[i] = rand() % SIZE;
	}
	printf("Fin init_tab\n");
}

void random_access_r(){
	printf("Debut random_access_r\n");
	int i;int y;
	for(i=0;i<SIZE;i++){
		y = data[data[data[data[i]]]];
	}
	printf("Fin random_access_r\n");
}

void random_access_w(){
	printf("Debut random_access_w\n");
	int i;
	for(i=0;i<SIZE;i++){
		 data[i] = data[data[data[data[i]]]];
	}
	printf("Fin random_access_w\n");
}

void random_access_rw(){
	printf("Debut random_access_rw\n");
	int i, y, m = 0;
	for(i=0;i<SIZE;i++){
		if(m == 0){//Lecture
			y = data[data[data[data[i]]]];
			m = 1;
		} else {//ecriture
			data[i] = data[data[data[data[i]]]];
			m = 0;
		}
	}
	printf("Fin random_access_rw\n");
}

void seq_acess_r(){
	printf("Debut seq_acess_r\n");
	int i,y,z,m;
	for(i=0;i<SIZE;i++){
		if(i < (SIZE - 2)){
			y = i + 1;
			z = i + 2;
		}
		m = data[i] + data[y] + data[z];
	}
	printf("Fin	seq_acess_r\n");
}

void seq_acess_w(){
	printf("Debut seq_acess_w\n");
	int i,y,z,m;
	for(i=0;i<SIZE;i++){
		if(i < (SIZE - 2)){
			y = i + 1;
			z = i + 2;
		}
		data[i] = (data[i] + data[y] + data[z]) % SIZE;
	}
	printf("Fin	seq_acess_w\n");
}

void seq_acess_rw(){
	printf("Debut seq_acess_rw\n");
	int i, y, z, j, m = 0;
	for(i=0;i<SIZE;i++){
		if(i < (SIZE - 2)){
			y = i + 1;
			z = i + 2;
		}
		if(m == 0){//Lecture
			j = data[i] + data[y] + data[z];
			m = 1;
		} else {//ecriture
			data[i] = (data[i] + data[y] + data[z]) % SIZE;
			m = 0;
		}
	}
	printf("Fin	seq_acess_rw\n");
}

void main(void){
srand (time (NULL));
/* init table */
init_tab();
/* access aleatoire */

/* lecture */
random_access_r();
/* ecrire */
random_access_w();
/* hybride */
random_access_rw();
/*Fin*/
/* access sequentiel */
/* lecture */
seq_acess_r();
/* ecrire */
seq_acess_w();
/* hybride */
seq_acess_rw();
/* Fin */
}
