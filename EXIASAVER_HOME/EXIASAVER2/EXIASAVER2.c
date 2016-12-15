#include <stdlib.h>		
#include <stdio.h>		
#include <ncurses.h>		//Bibliothèque pour quitter le processus sur commande de touches
#include <string.h>
#include <time.h>           //contient la structure por recuperer l'heure.
#include <sys/types.h>
#include <unistd.h>

#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
#define TAILLE_MAX 1000					//Taille maximum du fichier
#define LARGEUR_CONSOLE 80

int InitTime()
{
	time_t secondes;
	struct tm instant;         //structure qui recupere l'heure actuelle
	time(&secondes);
	instant=*localtime(&secondes);


	int TimeS1 = (instant.tm_sec)/10;  
	int TimeS2 = (instant.tm_sec)-(TimeS1*10); //on effectue ce calcul afin de pouvoir recuperer les unitées de l'heure
	int TimeM1 = (instant.tm_min)/10;
	int TimeM2 = (instant.tm_min)-(TimeM1*10);
	int TimeH1 = (instant.tm_hour)/10;
	int TimeH2 = (instant.tm_hour)-(TimeH1*10);

	
	int tab[8];						//tableau contenant les caracteres
	tab[0]=TimeH1;
	tab[1]=TimeH2;			
	tab[2]=20;
	tab[3]=TimeM1;
	tab[4]=TimeM2;
	tab[5]=20;
	tab[6]=TimeS1;
	tab[7]=TimeS2;

	int z = 0; 						//nombre de caractere affiché
	int tailleFich = 1;

	int y=12, x=9;
	FILE* fichier1 = NULL;     		//Pointeur initialisé à NULL
	char chaine[TAILLE_MAX];        
	int chaine2[2];
        int i=0, j=0;				//Déclaration des deux variables pour les boucles
        int r,e;	

	for (z=0;z<8;z++)
	{
		switch (tab[z])																				//Va chercher les images dans le dossier 
		{
			case 0:
				fichier1 = fopen("EXIASAVER2_PBM/0.pbm", "r");
				break;
			case 1:
				fichier1 = fopen("EXIASAVER2_PBM/1.pbm", "r");
				break;
			case 2:
				fichier1 = fopen("EXIASAVER2_PBM/2.pbm", "r");
				break;
			case 3:
				fichier1 = fopen("EXIASAVER2_PBM/3.pbm", "r");
				break;
			case 4:
				fichier1 = fopen("EXIASAVER2_PBM/4.pbm", "r");
				break;
			case 5:
				fichier1 = fopen("EXIASAVER2_PBM/5.pbm", "r");
				break;
			case 6:
				fichier1 = fopen("EXIASAVER2_PBM/6.pbm", "r");
				break;
			case 7:
				fichier1 = fopen("EXIASAVER2_PBM/7.pbm", "r");
				break;
			case 8:
				fichier1 = fopen("EXIASAVER2_PBM/8.pbm", "r");
				break;
			case 9:
				fichier1 = fopen("EXIASAVER2_PBM/9.pbm", "r");
				break;
			case 20:
				fichier1 = fopen("EXIASAVER2_PBM/doublpoint.pbm", "r");
				break;
		}
		

       
		 if (fichier1 != NULL) 							//On peut lire le fichier            //AFFICHAGE DE L'IMAGE
        	    {
        	        fseek(fichier1, 3, SEEK_SET);            // //fgets permet de deplacer un poiteur dans un fichier                 
        	        fscanf(fichier1, "%d %d", &chaine2[0], &chaine2[1]);
        	        r = chaine2[0];
        	        e = chaine2[1];
        	        r = (r*2)-1;
        		
			fseek(fichier1, 1, SEEK_CUR); 
        	      	for(i=0; i<e; i++)                   			//Boucle qui va parcourir les lignes
        	            {
				gotoxy(x,y);        	                
				fgets(chaine, TAILLE_MAX, fichier1);		//récupération de la ligne
        	                for(j=0; j<r; j++)               		//boucle qui parcours la ligne
        	                    {
					gotoxy(x,y);        	                    	
					if (chaine[j] == '0')
        	                            chaine[j] = ' ';        		//Affiche les caractères correspondants en ' '
        	       			else if (chaine[j] == '1')
        	                            	chaine[j] = 220;      
        	                    }
				x=x+1;								//permet de parcourir toutes les lignes
				printf("%s", chaine);				//Afficher l'image ligne par ligne
        	            }
				fclose(fichier1);   				//On ferme le fichier ouvert
				fichier1 = NULL;	
        	    }
		x=x-5;
		y=y+7;
	}
			
}

int main()
{

	int RefreshT = 10;				//Temps en seconde avant actualisation
	int ctrlc = 0;
	int k;
	int a = 20,b = 13,c = 20,d = 30;		//Encrage de l'horloge et de la phrase
	system("clear");				//Nettoiement de la console
	while (ctrlc != 1)				//tant que l'on appuie pas sur ctrlc 
	{
		int y = 60;
		gotoxy(c,d);
		InitTime();
		gotoxy(a,b);
		printf("Cet ecran sera actualise dans quelques secondes");
		printf ("\n\n\n");

		for (k=0; k<RefreshT; k++)
		{
			sleep(1);
			gotoxy(a,y);
			printf(".\n");
			y++;
		}
		y=y-RefreshT;
		gotoxy(a,y);
		printf("                            ");
	}
	return 0;
}