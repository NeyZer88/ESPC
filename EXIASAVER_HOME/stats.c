#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stats.h"
#ifndef WIN32
    #include <sys/types.h>
#endif

int main()
{
    system("clear");
    int choix;


    printf("Bienvenue dans l'espace dédié aux stats.\n");
    
    printf("Vous pouvez consulter différentes stats :\n\n\"");
    printf("1. Les stats sur la date\n\n\"") ;
    printf(" 2. Les stats sur le termSaver exécuté\n\n\"") ;
    printf(" 3. Les stats sur l'image chargé pour le type statique\n\n\"") ;
    printf(" 4. Les stats sur la taille utilisé pour le mode dynamique\n\n\"") ;
    printf(" Merci de faire votre choix :\n") ;

        


   
    

    scanf("%d", &choix);
    system("clear");

        printf("\nSuccès pour l'ouverture de l'historique\n");

        //STATS SUR LA DATE
        if(choix == 1)
        {



        }

        //STATS SUR LE TYPE DE FICHIER EXECUTE
        else if(choix == 2)
        {
            Input newInput[100] = {0};
            ReadStats(newInput);     //Lance la fonction ReadSats
            nbtype(newInput); 
            return 0;
        }

      //STATS SUR L'IMAGE CHARGEE POUR LE TYPE STATISTIQUE
        else if(choix == 3)
        {
            Image_tS1_lu();

        }

        //STATS SUR LA TAILLE UTILISE POUR LE MODE DYNAMIQUE
        else if(choix == 4)
        {
            printf("J'ai rien développé :'( \n");


        }
}

int nombreLignes(void)
{
	int c;
	int nb_lignes = 0;

	FILE* fhistorique = NULL; //initialise le pointeur à NULL
	fhistorique = fopen("historique.txt", "r+"); //OUVRE LE FICHIER historique.c

    while ((c = getc(fhistorique)) != EOF)
    {
        if (c == '\n')
        ++nb_lignes;
    }
    nb_lignes = nb_lignes-5;

	return nb_lignes;
}

//FONCTION POUR LIRE ET STOCKER TOUTES LES VALEURS DANS L'HISTORIQUE
void ReadStats(Input input[])
{
    FILE *fichier = NULL;
    fichier = fopen("historique.txt", "r");
    if (fichier != NULL) {
        char log[50] = "";
        int i = 0;
        while (fgets(log, 50, fichier) != NULL) {
            strcpy(input[i].date, strtok(log, " "));
            strcpy(input[i].heure, strtok(NULL, ";"));
            strcpy(input[i].type, strtok(NULL, ";"));
            strcpy(input[i].parametre, strtok(NULL, "  "));
            i++;
        }
    }
    fclose(fichier);
}

//FONCTION POUR TRIER LA DATE DANS L'ORDRE CHRONOLOGIQUE
void triDate(Input input[])
{
    int i = 0, tri = 0;
    while (tri == 0)
    {
        tri = 1;
        for (i = 0; i < 100; i++)
        {
            if (strcmp(input[i].date, input[i + 1].date) > 0)
            {
                char echangeDate[11];
                strcpy(echangeDate, input[i].date);
                strcpy(input[i].date, input[i + 1].date);
                strcpy(input[i + 1].date, echangeDate);

                char echangeHeure[11];
                strcpy(echangeHeure, input[i].heure);
                strcpy(input[i].heure, input[i + 1].heure);
                strcpy(input[i + 1].heure, echangeHeure);

                char echangeType[6];
                strcpy(echangeType, input[i].type);
                strcpy(input[i].type, input[i + 1].type);
                strcpy(input[i + 1].type, echangeType);

                char echangeParametre[20];
                strcpy(echangeParametre, input[i].parametre);
                strcpy(input[i].parametre, input[i + 1].parametre);
                strcpy(input[i + 1].parametre, echangeParametre);
                tri = 0;
            }
        }
    }
    printStats(input);
}

//FONCTION POUR TRIER L'HEURE DANS L'ORDRE CHRONOLOGIQUE

void triHeure(Input input[])
{
    int k = 0, trie = 0;
    while (trie == 0)
    {
        trie = 1;
        for (k = 0; k < 100; k++)
        {
            if (strcmp(input[k].heure, input[k + 1].heure) > 0)
            {
                char echangeDate[11];
                strcpy(echangeDate, input[k].date);
                strcpy(input[k].date, input[k + 1].date);
                strcpy(input[k + 1].date, echangeDate);

                char echangeHeure[11];
                strcpy(echangeHeure, input[k].heure);
                strcpy(input[k].heure, input[k + 1].heure);
                strcpy(input[k + 1].heure, echangeHeure);

                char echangeType[6];
                strcpy(echangeType, input[k].type);
                strcpy(input[k].type, input[k + 1].type);
                strcpy(input[k + 1].type, echangeType);

                char echangeParametre[20];
                strcpy(echangeParametre, input[k].parametre);
                strcpy(input[k].parametre, input[k + 1].parametre);
                strcpy(input[k + 1].parametre, echangeParametre);
                trie = 0;
            }
        }
    }
    printStats(input);
}

//FONCTION POUR AFFICHER LES DIFFERENTES VALEURS DANS L'HISTORIQUE
void printStats(Input input[])
{
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("%d", i);
        printf("%s  ", input[i].date);
        printf("%s  ", input[i].heure);
        printf("%s  ", input[i].type);
        printf("%s  ", input[i].parametre);
        printf("\n  ");
    }
}

//FONCTION POUR COMPTER ET AFFICHER LE NOMBRE DE TYPES TERMSAVER LANCES
void nbtype(Input input[])
{
    int i, type1=0, type2=0, type3=0;

    //On va lire jusqu'à 100 lignes*/
    for (i = 0; i < 100; i++)
    {
        switch ((int)input[i].type[0])
        {
            //Si le type lu est 1, on incrémente le compteur de type1 de 1
            case 49:
                type1++;
                break;

            // Si le type lu est 2, on incrémente le compteur de type2 de 1
            case 50:
                type2++;
                break;

            //Si le type lu est 3, on incrémente le compteur de type3 de 1
            case 51:
                type3++;
                break;
        }
    }
    printf("type 1: %d\ntype 2: %d\ntype 3: %d\n", type1, type2, type3);
}

void Image_tS1_lu(void)
{
    int image1 = 0, image2 = 0, image3 = 0, image4 = 0, image5 = 0; //Déclaration des compteurs pour les images lu

    FILE* fhistorique = NULL; //initialise le pointeur à NULL
	fhistorique = fopen("historique.txt", "r+"); //OUVRE LE FICHIER historique.c

	if (fhistorique != NULL)
	{
		int type_detecte[100];
		int i;

		char image1c[] = "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img1.pbm";
		char image2c[] = "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img2.pbm";
		char image3c[] = "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img3.pbm";
		char image4c[] = "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img4.pbm";
		char image5c[] = "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img5.pbm";
		int verif1 = 0, verif2 = 0, verif3 = 0, verif4 = 0, verif5 = 0;


		fseek(fhistorique, 20,SEEK_SET);

		//Le type lu est-il bien 1 ?

		for (i=0; i < 100; i++)
		{

		fscanf(fhistorique, "%d", &type_detecte[i]);
		printf("%d ", type_detecte[i]);



			if (type_detecte[i] == 1)
			{
				fseek(fhistorique, 1,SEEK_CUR);

				char c[100] = "";
				fgets(c, 100, fhistorique);
				printf("%s\n", c);

				verif1=strcmp(c,image1c);
				verif2=strcmp(c,image2c);
				verif3=strcmp(c,image3c);
				verif4=strcmp(c,image4c);
				verif5=strcmp(c,image5c);

				if (verif1 == 0)
				{
                    image1++;
				}
				else if (verif2 == 0)
				{
                    image2++;
				}
				else if (verif3 == 0)
				{
                    image3++;
				}
				else if (verif4 == 0)
				{
                    image4++;
				}
				else if (verif5 == 0)
				{
                    image5++;
				}

			}
			else
			{
				fseek(fhistorique, 2, SEEK_CUR);
			}
		fseek(fhistorique, 20,SEEK_CUR);
		}

	}
	else
	{
		printf("non\n");
	}
	fclose(fhistorique);
    printf("Image XD: %d\nImage chateau: %d\nImage fusee: %d\nImage maison: %d\nImage sapin: %d\n", image1, image2, image3, image4, image5);
}