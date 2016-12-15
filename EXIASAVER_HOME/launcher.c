#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //Inclure la bibliothèque qui contient entre autre la fonction execl

/*Bibliothèque contenant les fonctions pour le parcours de dossiers*/
#include <dirent.h>

/* Si le système n'est pas windows, alors inclure sys/types.h*/
#ifndef WIN32
    #include <sys/types.h>
#endif

/*On inclut les prototypes des fonctions du launcher*/
#include "launcher.h"
#define img1 "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img1.pbm"
#define img2 "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img2.pbm"
#define img3 "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img3.pbm"
#define img4 "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img4.pbm"
#define img5 "/home/pthn/EXIASAVER_HOME/EXIASAVER1/EXIASAVER1_PBM/img5.pbm"




//FONCTION NOMBRE RANDOM

int nb_rand(void)
	{
	    return (rand());
	}


//FONCTION POUR EXPORTER DANS L'HISTORIQUE

void saveDate(int type, int nombrePicture)
{
	FILE* fhistorique = NULL; //initialise le pointeur à NULL
	fhistorique = fopen("historique.txt", "r+"); //OUVRE LE FICHIER historique.c

	if (fhistorique != NULL) //Vérifie si le fichier est bien ouvert, car si fichier=NULL signifie qu'il y a une erreur
	{
		printf("\nSuccès pour l'ouverture de l'historique\n");

		//RECUPERER L'HEURE ET LA DATE
		//Lire l'heure courante
		time_t HeureDate;
		HeureDate = time(NULL);

		//Convertir l'heure en heure locale
		struct tm tm_HeureDate = *localtime (&HeureDate);

		//Crée une chapine JJ/MM/AAAA HH:MM:SS
		char s_HeureDate[sizeof "JJ/MM/AAAA HH:MM:SS"];

		strftime (s_HeureDate, sizeof s_HeureDate, "%d/%m/%Y %H:%M:%S", &tm_HeureDate);


		fseek(fhistorique, 0, SEEK_END); //Place le curseur à la fin du fichier


		//ECRITURE DE TOUTES LES DONNEES (SAUF PARAMETRE) DANS L'HISTORIQUE
		fseek(fhistorique, 0, SEEK_END); //Place le curseur à la fin du fichier

		//Ecrit la date
		fseek(fhistorique, 0, SEEK_END);
		fprintf(fhistorique,"%s", s_HeureDate);
		fprintf(fhistorique,";");

		//Ecrit le type lancé
		fseek(fhistorique, 0, SEEK_END);
		fprintf(fhistorique, "%d", type);
		fseek(fhistorique, 0, SEEK_END);
		fprintf(fhistorique,";");

		//ECRITURE DES PARAMETRES ASSOCIES AU TERMSAVER CHOISI
		if(type == 1)
		{
			//Ecrit l'image utilisé pour le type statique
			switch (nombrePicture)
			{
				case 1:
					fseek(fhistorique, 0, SEEK_END);
					fprintf(fhistorique,"img1\n");
				break;
				case 2:
					fseek(fhistorique, 0, SEEK_END);
					fprintf(fhistorique,"img2\n");
				break;
				case 3:
					fseek(fhistorique, 0, SEEK_END);
					fprintf(fhistorique,"img3\n");
				break;
				case 4:
					fseek(fhistorique, 0, SEEK_END);
					fprintf(fhistorique,"img4\n");
                break;
                case 5:
                    fseek(fhistorique, 0, SEEK_END);
					fprintf(fhistorique,"img5\n");
				break;
			}
		}
		else if (type == 2)
		{
			fseek(fhistorique, 0, SEEK_END);
			fprintf(fhistorique,"\n");
		}
		else if (type == 3)
		{
			fseek(fhistorique, 0, SEEK_END);
			fprintf(fhistorique,"\n");
		}
		fclose(fhistorique);//FERME LE FICHIER
		printf("Ecriture dans l'historique réussie\n\n");

	}
	else
	{
		printf("\nImpossible d'ouvrir le fichier historique...");
	}
}

//FONCTION POUR CONNAITRE LE NOMBRE D'IMAGE

int nbIMGStatique(void)
{
    int nombrePic = 0; //initalisation à 0 du nombre d'images

    DIR* repertoireImages = NULL; //déclaration et initialisation à NULL du pointeur repertoireImages

    struct dirent* ent = NULL;

    repertoireImages = opendir("EXIASAVER1_PBM/"); //Ouverture du dossier PBM_statique dans repertoireImages

    while ((ent = readdir(repertoireImages)) != NULL) //Tant que des fichiers sont lus (fichiers déjà tous lu = NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && //Si le fichier lu n'est pas .
            strcmp(ent->d_name, "..") != 0) //Et n'est pas .. non plus
        nombrePic++; //Alors on incrémente le compteur
    }

    closedir(repertoireImages);
    return nombrePic;

}

int main(int argc,char *argv[])
{
	system("clear"); //Nettoie la console
	srand(time(NULL));
	int choixtype=nb_rand()%3+1; //Affecte à la variable choixtype, un nombre au hasard compris entre 1 et 3

	int nbimg; //Variable contenant le nombre d'image statique dans le dossier des images statiques
	nbimg = nbIMGStatique(); //Met dans la variable nbimg le résultat retourné par la fonction nombreImaesStatique. Cette fonction permet de connaitre le nombre d'images statiques

	int choixIMG=nb_rand()%nbimg+1; //Le choix de l'image statique se fera entre la numéro 1 et la numéro n (n correspond au nombre d'images trouvé précédemment)

//VERIFIE SI L'ARGUMENT STAT EST SAISI
	char statarg[] = "-stat"; //On définit une chaine de caractère qui contient "-stat", afin que l'on puisse comparer si l'argument rentré correspond à ça
	int statverif; //Déclaration de la variable statverif (pour connaitre son utilité, voir plus bas

    //Vérifie si un argument est rentré (sinon le programme continue sans que rien ne se passe)

	if(argv[1] != NULL)
	{
		printf("Vous avez rentré un argument...\n");
		statverif=strcmp(argv[1],statarg); //On met dans la variable statverif le numéro du résultat de strcmp : 0 si les deux chaines sont identiques (donc -stat rentré par l'utilisateur) ou un autre chiffre si les deux chaines ne correspondent pas

        //Vérifie si l'argument rentré est -stat (sinon, on indique que l'argument rentré ne correspond à rien)
		if (statverif == 0)
		{
			printf("Bravo, vous avez rentré le paramètre -stat :)\nNous allons procéder à l'ouverture du programme des statistiques, apuuyez simplement sur Entrée :)\n");
			getchar();
			execl("stats","stats", NULL); //Exécute l'exécutable stats pour rentrer dans les stats :)
		}
		else
		{
			printf("Le paramètre que vous avez rentré est inconnu pour nous ;)\nLe programme continue\n");
            		getchar();
		}
	}
//FIN TEST ARGUMENT


	printf("Bonjour et bienvenue dans exiaSaver !\nVeuillez appuyez sur Entrée pour continuer...");
	getchar();
	printf("\nNous allons voir ensemble quel écran de veille nous allons lancer\nVeuillez appuyez sur Entrée pour continuer...\n\n");
	getchar();
	printf("Le nombre random est de : %d\n\n", choixtype);

//SAUVEGARDER DANS L'HISTORIQUE
	saveDate(choixtype,choixIMG);


	//Que faire selon le type d'écran de veille choisi
	if (choixtype ==1)
	{
		printf("Nous allons lancer le type statique !\nVous etes pret ?\n");
        getchar();

		//L'image que l'on va lancer en mode type statique
		switch (choixIMG)
		{
		case 1:
            execl("EXIASAVER1", "EXIASAVER1", "img1", NULL);
		break;
		case 2:
            execl("EXIASAVER1", "EXIASAVER1", "img2", NULL);
		break;
		case 3:
            execl("EXIASAVER1", "EXIASAVER1", "img3", NULL);
		break;
		case 4:
            execl("EXIASAVER1", "EXIASAVER1", "img4",NULL);
		break;
		case 5:
            execl("EXIASAVER1", "EXIASAVER1", "img5", NULL);
		break;
		}
	}
	else if (choixtype ==2)
	{
		printf("Nous allons lancer le type dynamique !\nVous etes pret ?\n");
		getchar();
		execl("EXIASAVER2", "EXIASAVER2", NULL);
	}
	else if (choixtype ==3)
	{
		printf("Nous allons lancer le type interactif !\n");
		getchar();
		execl("EXIASAVER3", "EXIASAVER3", NULL);
	}
}