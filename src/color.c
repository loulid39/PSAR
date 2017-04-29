#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ececuter avec ./color fichier.c fichier.txt resul.html


// green	bgcolor=\"#00FF5A\"
// yellow	bgcolor=\"#F3FF3D\"
// orange 	bgcolor=\"#FF9500\"
// red		bgcolor=\"#FF0000\"
typedef struct {
	int num;// numéro de ligne ou commence la fonction
	int prc;// pourcentage d'accès
}DATA;
int main(int argc, char **argv){
	char Tableau[100000];	// utilisé pour généré le .html
	DATA result [40]; 	// les résultats généré par le profileur
	char ligne_[255];
	char ligne[255];	// une ligne du fichier .c	
	char * ligtmp;
	char results [40];
	char numligne[6];
	char nbaccess[10];
	char praccess[5];
	char temps[8];
	char totalaccess[12];
	char *color[5]={"\"#00FF5A\"","\"#F3FF3D\"","\"#FF9500\"","\"#FF0000\"","\"#FFFFFF\""};
	int couleur;
	FILE *codefile;
	FILE *resultat;
	FILE *htmlfile;
	char ** resume;
	int i=0;
	int n=0;

	int nbligne=0;
	int tacces=0;	//total access
	char aligne[6];
	char c='\0';
	
	printf("%s\n",argv[1]);
	if((codefile = fopen(argv[1], "r") )== NULL) // code source en lecture
	{
		perror("Error opening file c");
		return(-1);
	}
	
	if((resultat = fopen("papi_log.txt", "r") )== NULL) // le loge des résultats du profileur en lecture
	{
		perror("Error opening file txt");
		return(-1);
	}
	if((htmlfile = fopen("resultat.html", "w") )== NULL) // le fichier HTML a créé
	{
		perror("Error opening file html");
		return(-1);
	}

	fputs("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n<head><title>Résultat</title></head>\n<body>\n ",htmlfile);

	fputs("<h2 align = center >R&eacute;sultat Du Profilage sur le fichier ",htmlfile);
	fputs(argv[2],htmlfile);
	fputs("</h2>",htmlfile);
	fputs("<table><tr><td width= 40%>",htmlfile);

	fputs("<table frame = \"box\" rules=\"rows\">\n<thead > <tr> <th width=20% ,align=center  > Ligne </th>\n <th width= 20% ,align=center  > Quantity MB </th>\n<th width= 20% ,align=center  > Pourcentage </th>\n \n <th width=20% ,align=center  > Time </th>\n </tr></thead>\n<tbody>",htmlfile);
	memset(results, '\0', sizeof(results));

	if(fgets(results,40,resultat)!=NULL)
	{
	

		tacces=atoi(results);
		memset(results, '\0', sizeof(results));
		while(fgets(results,40,resultat)!=NULL)
		{
			int taille=strlen(results)-strlen(strchr(results,' '));
			memset(numligne, '\0', sizeof(numligne));
			strncpy(numligne,results,taille);			//
			strcpy(results,&results[taille+1]);
			taille=strlen(results)-strlen(strchr(results,' '));
			memset(nbaccess, '\0', sizeof(nbaccess));
			strncpy(nbaccess,results,taille);			//
			memset(temps, '\0', sizeof(temps));
			strcpy(temps,&results[taille+1]);			//
			sprintf(praccess,"%.2f",(atof(nbaccess)*100)/tacces);	//
			couleur= (int)(((atof(nbaccess)*100)/tacces)/25);
			fputs("<tr><td align=center bgcolor = ",htmlfile);
			fputs(color[couleur],htmlfile);	
			fputs(" >",htmlfile);
			fputs(numligne,htmlfile);
			fputs("</td><td align=center bgcolor = ",htmlfile);
			fputs(color[couleur],htmlfile);	
			fputs(" >",htmlfile);
			fputs(nbaccess,htmlfile);
			fputs("</td><td align=center bgcolor = ",htmlfile);
			fputs(color[couleur],htmlfile);	
			fputs(" >",htmlfile);
			fputs(praccess,htmlfile);
			fputs("</td><td align=center bgcolor = ",htmlfile);
			fputs(color[couleur],htmlfile);	
			fputs(" %>",htmlfile);
			fputs(temps,htmlfile);
			fputs("</td></tr>",htmlfile);	
			
		}
	}
	
	fputs("</tbody></table>",htmlfile);
	fputs("</td><td  width= 30%> </td></tr></table>",htmlfile);
	fputs("<p><pre>R&eacute;sum&eacute; des lignes dont un appel de fonction est effectu&eacute;.</pre></p>",htmlfile);
	//ici un while pour le petit tableau	
	
	fputs("<table frame = \"box\" rules=\"cols\">\n<thead > <tr> <th width=10% ,align=center bgcolor =#CFFC95 > Quantity MB </th>\n <th width= 5% ,align=center bgcolor =#CFFC95 > Pourcentage </th>\n<th width= 10% ,align=center bgcolor =#CFFC95 > Time s </th>\n \n <th width=5% ,align=center bgcolor =#CFFC95 > Ligne Number </th><th  ,align=center bgcolor =#CFFC95> Code Source </th></tr>\n </thead>\n<tbody>",htmlfile);
	fclose(resultat);
	if((resultat = fopen("papi_log.txt", "r") )== NULL) // le loge des résultats du profileur en lecture
	{
		perror("Error opening file txt");
		return(-1);
	}
	memset(ligne, '\0', sizeof(ligne));
	memset(results, '\0', sizeof(results));
	int intern;
	// ma 1ere ligne du fichier log contenant des résultats représente le nombre totals d'accès effectués
	if(fgets(results,40,resultat)!=NULL)
	{
		tacces=atoi(results);
		memset(results, '\0', sizeof(results));
		while(fgets(results,40,resultat)!=NULL)
		{
			int taille=strlen(results)-strlen(strchr(results,' '));
			memset(numligne, '\0', sizeof(numligne));
			strncpy(numligne,results,taille);
			//printf("%d : %s ->",taille, numligne);
			strcpy(results,&results[taille+1]);
			taille=strlen(results)-strlen(strchr(results,' '));
			memset(nbaccess, '\0', sizeof(nbaccess));
			strncpy(nbaccess,results,taille);
			//printf("%s -> ", nbaccess);
			memset(temps, '\0', sizeof(temps));
			strcpy(temps,&results[taille+1]);
			//printf("%s \n ", temps);
			intern=1;
			while(intern==1 && fgets(ligne_, 255,codefile)!=NULL)
			{	// lire la ligne

				if((ligtmp=strchr(ligne_,'<'))!=NULL){
					taille= strlen(ligne_)-strlen(ligtmp);
					strncpy(ligne,ligne_, taille);
					strcat(ligne,"&lt;\0");
					strcat(ligne,&ligtmp[1]);
					//strcpy(&ligne_[taille],"&lt;\0");	
				}
				else{
				
					strcpy(ligne,ligne_);
				}

				//printf("%s",ligne);
				couleur=4;
				nbligne++;
				fputs("<tr height=\"10\" ><td align=center bgcolor = ",htmlfile);
				memset(aligne, '\0', sizeof(aligne));
				//printf("%s : %d --> %d\n",numligne,atoi(numligne), nbligne);
				if(atoi(numligne)==nbligne)
				{	
					couleur= (int)(((atof(nbaccess)*100)/tacces)/25);
					fputs(color[couleur],htmlfile);
					fputs(" >",htmlfile);	
					fputs(nbaccess,htmlfile);
					fputs("</td><td align=center bgcolor = ",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs(" >",htmlfile);	
					sprintf(praccess,"%.2f",(atof(nbaccess)*100)/tacces);
					fputs(praccess,htmlfile);
					fputs(" % </td><td align=center bgcolor = ",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs(" >",htmlfile);
					fputs(temps,htmlfile);	
					fputs("</td><td align=center bgcolor = ",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs(" >",htmlfile);	
					intern=0;	// variable utilisé pour quitter cette boucle et lire la prochaine ligne dans log
				}
				else
				{	fputs(color[couleur],htmlfile);
					fputs(" > _ </td><td align = center bgcolor = ",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs("> _ </td><td align=center bgcolor =",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs("> _ </td><td align=center bgcolor =",htmlfile);
					fputs(color[couleur],htmlfile);
					fputs(" >",htmlfile);	
				}

				sprintf(aligne,"%d",nbligne);
				fputs(aligne,htmlfile);
				fputs("</td><td align=left bgcolor = ",htmlfile);
				fputs(color[couleur],htmlfile);
				fputs(" ><pre>",htmlfile);
				ligne[strlen(ligne)-1]='\0';	
				fputs(ligne,htmlfile);
				fputs("</pre></td>\n",htmlfile);
				memset(ligne, '\0', sizeof(ligne));
		
			}
			memset(results, '\0', sizeof(results));
		}
	}
	while(fgets(ligne, 255,codefile)!=NULL)
	{	// lire la ligne
		fputs("<tr><td align=center> _ </td>\n<td  align=center> _ </td>\n<td align=center> _ </td>\n<td  align=center>",htmlfile);
		nbligne++;
		memset(aligne, '\0', sizeof(aligne));
		sprintf(aligne,"%d",nbligne);
		fputs(aligne,htmlfile);
		fputs("</td><td align=left><pre>",htmlfile);
		ligne[strlen(ligne)-1]='\0';	
		fputs(ligne,htmlfile);
		fputs("</pre></td>\n",htmlfile);
		memset(ligne, '\0', sizeof(ligne));
		
	}
	fputs("</tbody>\n</table>\n</body>\n </html>\n",htmlfile);

	fclose(htmlfile);
	fclose(resultat);
	fclose(codefile);

	return 0;
}
