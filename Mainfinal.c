/* Projet Algorithmie :
Fichier : Mainfinal.c
Auteur : Duval Jacques && de Font-Reaulx Pol
groupe Da
Date : Avril 2015
*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++CONSTANTES && librairies+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//Librairies
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

//Constantes permettant d'afficher le donjon avec les codes ASCII
#define COLONNES 20
#define LIGNES 10
#define SOL_NU 32
#define MUR_EXT 35
#define MUR_INT 43
#define PORTE_FER 64
#define PORTE_OU 32
#define ROCS 42
#define OR 71
#define ARMURE 234
#define PERSO 127
#define MONSTRE1 82
#define BOSS 225
#define PIEGE 32
#define PIEGE_UTILISE 81
#define EPEE 33
#define POTION 148


#define MaliceP 8  //malice du piège

//Constante pour le mininum et le maximum des caractéristiques
#define MIN_CARAC 1 //minimum pour une caracteristique
#define MAX_CARAC 10 //maximum pour une caracteristique

//Constantes pour les touches de deplacement avec les codes ASCII
#define ENTER 13
#define ECHAP 27
#define TOUCHEDROITE 77
#define TOUCHEGAUCHE 75
#define TOUCHEHAUT 72
#define TOUCHEBAS 80

//Constantes reliés aux fichiers des cartes
#define niveau1 "carte1.txt"
#define niveau2 "carte2.txt"
#define niveau3 "carte3.txt"
#define niveau4 "carte4.txt"
#define niveau5 "carte5.txt"
#define sauvegarde "save.txt"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++Structures de données++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

struct caseDonjon //contient les données pour le donjon
{
    int typeCase; //0: sol nu, 1: mur exterieur, 2: cloison interieure, 3: porte fermee, 4: porteouverte, 5: rochers, 6: Or, 7: armure, 8: epee, 9: piege, 10:piege utilise, 11:potion
    int statutCase; // 0: vide, 1: occupee par le personnage, 2: occupe par un monstre, 3: occupe par le Boss
};
typedef struct caseDonjon sCaseDonjon;

struct personnage //contient les données du personnage
{
    char nom[20];
    int classe; //0: mage, 1:chevalier
    int corps, intellect, esprit, endurance, habilete, malice;
};
typedef struct personnage sPerso;

struct monstre //contient les données du monstre
{
    char nom[50];
    int endurance,habilete;
};
typedef struct monstre sMonstre1;

struct boss //contient les données du Boss
{
    char nom[50];
    int endurance,habilete;
};
typedef struct boss BigBoss;



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++Déclaration fonctions++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void DemanderNom(sPerso * monPersonnage);
void DemanderClasse(sPerso * monPersonnage);
void AfficherPerso(sPerso * monPersonnage);
void chargement(sPerso* monPersonnage,int* compteurScore,int* compteurNiveau,sMonstre1* monstre,BigBoss* Boss,int* x,int* y,int* xr,int* yr,sCaseDonjon donjon[LIGNES][COLONNES]);
void AfficherCarte(sCaseDonjon donjon[LIGNES][COLONNES],sPerso * monPersonnage, int compteurScore, int compteurNiveau);
void Deplacement(int* IsRunning,sCaseDonjon donjon[LIGNES][COLONNES],sPerso *monPersonnage,int *compteurScore,int *compteurNiveau,int *x,int *y,int *xr,int *yr,sMonstre1* monstre,BigBoss *Boss);
void DeplacementMonstre(sCaseDonjon donjon[LIGNES][COLONNES],int* xr, int* yr,sMonstre1 * monstre);
void combatD(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int* y);
void combatG(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int* y);
void combatH(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int* y);
void combatB(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int* y);
void combatBoss(sPerso * monPersonnage,BigBoss *Boss,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y);
void Testcase (sCaseDonjon donjon[LIGNES][COLONNES],sPerso *monPersonnage,int *compteurScore,int* x,int* y);
void potions(sPerso * monPersonnage);
void changerCarte(sCaseDonjon donjon[LIGNES][COLONNES],FILE* fichier,sMonstre1 *monstre);
void choixDeCarte(int* compteurNiveau,sCaseDonjon donjon[LIGNES][COLONNES],sMonstre1 *monstre,int* x,int* y,int* xr,int* yr);
void bouclejeu(sPerso* monPersonnage,int* compteurScore,int* compteurNiveau,sMonstre1* monstre,BigBoss* Boss,int* x,int* y,int* xr,int* yr,sCaseDonjon donjon[LIGNES][COLONNES]);
int Caracteristique(char * NomCarac,int ValeurMin,int ValeurMax);


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++Fonction principal+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int main()
{
    sPerso monPersonnage; //Création du tableau qui contiendra les infos sur le personnage
    sCaseDonjon donjon[LIGNES][COLONNES]; //Création du tableau qui contiendra la carte
    sMonstre1 monstre;
    BigBoss Boss;

    int compteurNiveau; //initialisation du compteur pour passer de niveaux en niveaux
    int compteurScore; //initialisation de la variable gérant le score

    int x,y;// Position initiale du personnage dans un niveau
    int xr,yr; //position initiale du monstre dans un niveau

    int menu;

    while(menu<1 || menu>4) //pour que le joueur rentre bien un nombre entre 1 et 4
    {
        printf("\n\tJEU DE STYLE ROGUE DE POL ET JACK\n\n\n");
        printf("Le but du jeu est de traverser les differents niveau et de vaincre le Boss!\n\n");
        printf("Tapez le chiffre correspondant a votre souhait!\n\n");
        printf("1: Commencer une nouvelle partie\n");
        printf("2: Charger une partie\n");
        printf("3: Quitter le jeu\n\n");

        menu=getch(); //fonction de conio.h permet d'envoyer directement la valeur de la touche pressé sans avoir a appuyer sur entrée. De plus, la valeur n'apparait pas à l'écran.
        switch(menu)
        {
        case 49: //Touche 1, on lance une nouvelle partie et le jeu en lui meme commence.

            printf("\n");

            DemanderNom(&monPersonnage); //fonction qui demande le nom du personnage

            DemanderClasse(&monPersonnage); //fonction qui demande la classe et les caractéristiques du personnage

            AfficherPerso(&monPersonnage); //fonction qui récapitule tout au joueur

            monstre.endurance=5,monstre.habilete=5; //initialisation des valeurs de l endurance et de l'habileté du monstre
            Boss.endurance=15,Boss.habilete=10; //initialisation des valeurs de l endurance et de l'habileté du boss

            srand (time(NULL));

            compteurNiveau=1; //on est au premier niveau
            compteurScore=0; //pas encore de score

            x=5; //position initiale dans le niveau 1
            y=1;

            xr=8,yr=4; //Position de départ du monstre au niveau 1

            FILE *fichier1;

            if((fichier1=fopen(niveau1,"r")) == NULL) //on ouvre le fichier comportant la carte du niveau 1 en mettant en message d'erreur si ca ne fonctionne pas
            {
                fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau1); //message d'erreur
                return(EXIT_FAILURE); //on quitte s'il n'arrive pas à ouvrir le fichier
            }

            changerCarte(donjon,fichier1,&monstre); //fonction qui attribue le fichier au tableau donjon

            bouclejeu(&monPersonnage,&compteurScore,&compteurNiveau,&monstre,&Boss,&x,&y,&xr,&yr,donjon); //fonction contenant la boucle principale du jeu

            break;

        case 50: //correspond a la touche 2

            chargement(&monPersonnage,&compteurScore,&compteurNiveau,&monstre,&Boss,&x,&y,&xr,&yr,donjon); //fonction qui lance le chargement d'une ancienne partie sauvegardée

            break;

        case 51: //correspond a la touche 3

            printf("\n\n BYE BYE\n\n");

            return 0; //on quitte le jeu

            break;
        }

    }

    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++Définitions des  fonctions+++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// On demande le nom du personnage
void DemanderNom(sPerso * p)
{
    printf("Entrez le nom de votre personnage. \n");
    scanf("%s",(*p).nom); //on entre le nom du joueur
    printf("\nVous vous appelez: %s. \n \n",(*p).nom);
}

// On demande la classe du personnage
void DemanderClasse(sPerso * p)
{
    printf("Choisissez votre classe. \nTapez: \n 0 pour devenir un mage.\n 1 pour devenir un chevalier: \n");
    scanf("%d",&(*p).classe);
    while(((*p).classe<0)||((*p).classe>1)) //message d'erreur pour qu'il choississe bien entre les classes proposées
    {
        printf("Veuillez choisir 0 pour le mage ou 1 pour le chevalier: \n");
        scanf("%d",&((*p).classe));
    }
    printf("\n");
    (*p).corps=Caracteristique("Corps",MIN_CARAC,MAX_CARAC); //il entre le corps
    (*p).esprit=Caracteristique("Esprit",MIN_CARAC,MAX_CARAC); //il entre l esprit
    (*p).intellect=Caracteristique("Intellect",MIN_CARAC,MAX_CARAC); //il entre l intellect
    (*p).endurance=(((*p).corps)*2)+((*p).esprit); //on calcule l'endurance avec les caracteristiques secondaires
    (*p).habilete=((((*p).corps)*2+(*p).intellect+(*p).esprit)/4); //on calcule l'habileté avec les caracteristiques secondaires
    (*p).malice=((((*p).intellect)*2+(*p).esprit)/2); //on calcule la malice avec les caracteristiques secondaires
    printf("\n \n");
}

//initialisation des caractéristiques
int Caracteristique(char * carac, int min, int max)
{
    int a;
    printf(" Entrez la valeur de votre caracteristique %s: \t", carac);
    scanf("%d",&a);
    while((a<min)||(a>max)) //message d'erreur pour que la valeur soit bien comprise dans la tranche voulue
    {
        printf(" Votre %s doit etre compris entre %d et %d : \n", carac, min, max);
        scanf("%d", &a);
    }
    return a; //on retourne la valeur de la caracteristique
}

//on fait un rappel sur tout le personnage
void AfficherPerso(sPerso * p)
{
    if((*p).classe==1)
    {
        printf("Voici le vaillant chevalier %s. \n",(*p).nom);
    }

    else
    {
        printf("Voici le puissant sorcier %s. \n",(*p).nom);
    }
    printf("Son endurance est de %d. \nSon habilete est de %d. \nSa malice est de %d. \n",(*p).endurance,(*p).habilete, (*p).malice);
    system("PAUSE");
}

//chargement de la sauvegarde
void chargement(sPerso* monPersonnage,int* compteurScore,int* compteurNiveau,sMonstre1* monstre,BigBoss* Boss,int* x,int* y,int* xr,int* yr,sCaseDonjon donjon[LIGNES][COLONNES])
{
    FILE *charge;

    if((charge=fopen(sauvegarde,"r")) == NULL) //on ouvre le fichier de sauvegarde qui contient la sauvegardenà charger
    {
        fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", sauvegarde); //message d'erreur
        exit(EXIT_FAILURE);
    }

    fscanf(charge,"%s %d  %d %d  %d %d %d ",(*monPersonnage).nom,&(*monPersonnage).classe,&(*compteurScore),&(*compteurNiveau),&(*monPersonnage).endurance,&(*monPersonnage).habilete,&(*monPersonnage).malice); //on attribut toutes les valeurs du fichier à celles du jeu
    system("cls");
    printf("\n\n\t\tChargement reussi de la partie de %s \n\n",(*monPersonnage).nom); //message de réussite
    system("pause");


    (*monstre).endurance=5,(*monstre).habilete=5; //on initialise les données du monstre
    (*Boss).endurance=15,(*Boss).habilete=10; //on initialise les données du boss


    choixDeCarte(&(*compteurNiveau),donjon,&(*monstre),&(*x),&(*y),&(*xr),&(*yr));
    bouclejeu(&(*monPersonnage),&(*compteurScore),&(*compteurNiveau),&(*monstre),&(*Boss),&(*x),&(*y),&(*xr),&(*yr),donjon);


}

// Affichage de la carte
void AfficherCarte(sCaseDonjon donjon[LIGNES][COLONNES],sPerso * m, int compteurScore, int compteurNiveau)
{
    int i,j;
    printf("\n");
    for(i=0; i<LIGNES; i++)
    {
        printf("\t");
        for(j=0; j<COLONNES; j++)
        {
            if (donjon[i][j].statutCase == 0)
            {
                switch(donjon[i][j].typeCase) //switch qui affiche les caractères selon les typeCase contenues dans le tableau donjon
                {
                case 0:
                    printf("%c ", SOL_NU);
                    break;

                case 1:
                    printf("%c ", MUR_EXT);
                    break;

                case 2:
                    printf("%c ", MUR_INT);

                    break;

                case 3:
                    printf("%c ", PORTE_FER);
                    break;

                case 4:
                    printf("%c ", PORTE_OU);
                    break;

                case 5:
                    printf("%c ", ROCS);
                    break;

                case 6:
                    printf("%c ", OR);
                    break;

                case 7:
                    printf("%c ", ARMURE);
                    break;

                case 8:
                    printf("%c ",EPEE);
                    break;

                case 9:
                    printf("%c ", PIEGE);
                    break;

                case 10:
                    printf("%c ",PIEGE_UTILISE);
                    break;

                case 11:
                    printf("%c ",POTION);
                    break;

                default:
                    printf("X "); //cas où il ne reconnait pas la valeur
                    break;

                }
            }

            else
            {
                switch(donjon[i][j].statutCase) //affiche les caractères selon les statutCase contenues dans la tableau
                {

                case 1:
                    printf("%c ", PERSO);
                    break;
                case 2:
                    printf("%c ", MONSTRE1);
                    break;
                case 3:
                    printf("%c ",BOSS);
                    break;
                default:
                    printf("Y "); //cas où il ne reconnait pas la valeur
                    break;
                }
            }
        }

        printf(" \n ");

    }
    printf("\tScore: %d\t\t Niveau: %d\n\n",compteurScore,compteurNiveau);
    printf("\tEndurance: %d\t\tHabilete: %d\t\tMalice: %d\n\n",(*m).endurance,(*m).habilete, (*m).malice);
    printf("Pour vous deplacer, appuyer sur les fleches directionnelle\n\n");
    printf("\t\n Legende : \n ");
    printf("\t%c: mur exterieur\t %c: Or\n ", MUR_EXT,OR);
    printf("\t%c: mur interieur\t %c: Armure\n ", MUR_INT,ARMURE);
    printf("\t%c: porte fermee\t\t %c: Piege utilise \n ", PORTE_FER,PIEGE_UTILISE);
    printf("\t%c: roc \t\t\t %c: Epee\n", ROCS,EPEE);
    printf("\t%c: %s \t\t %c: Potion\n\n ", PERSO,(*m).nom,POTION);
    printf("\nPour quitter le jeu et sauvegarder appuyer sur ECHAP\n\n");

}

void Deplacement(int* IsRunning,sCaseDonjon donjon[LIGNES][COLONNES],sPerso *monPersonnage,int *compteurScore,int *compteurNiveau,int* x,int* y,int* xr,int* yr,sMonstre1* monstre,BigBoss *Boss)
{
    int touche;

    touche=getch();


    switch(touche)
    {
    case ECHAP://pour sortir de la boucle principale a tout instant

        (*IsRunning)=0;
        break;


    case TOUCHEDROITE:

        if (donjon[*x][(*y)+1].typeCase==1 || donjon[*x][(*y)+1].typeCase==2 || donjon[*x][(*y)+1].typeCase==3 || donjon[*x][(*y)+1].typeCase==5 )
        {
            printf("Deplacement impossible\n\n");
            system("pause");
            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)+1].statutCase=0;

            break;

        }
        else if(donjon[*x][(*y)+1].typeCase==4)
        {
            (*compteurNiveau)++; //on incrémente le compteur de niveau pour pouvoir choisir la carte suivante après
            choixDeCarte(&(*compteurNiveau),donjon,&(*monstre),&(*x),&(*y),&(*xr),&(*yr)); //fonction qui choisit la carte selon le niveau dans lequel le joueur se situe

            break;
        }

        else if(donjon[*x][(*y)+1].typeCase==9) //cas où il y a un piège sur la case vers laquelle on se déplace
        {
            printf("Mince un piege!!!\n\n");
            system("pause");

            srand (time(NULL));

            int MalicePerso, MalicePiege;

            MalicePerso = (rand() % (*monPersonnage).malice+1);//tirage d'un nombre aléatoire dépendant de la malice du personnage
            MalicePiege = (rand() % ( MaliceP+1));

            //On effectue le test de comparaison
            if(MalicePerso>MalicePiege)
            {
                printf("Bravo vous avez reussi a eviter ce piege!\n\n");
                system("pause");

                donjon[*x][*y].statutCase=1;
                donjon[*x][(*y)+1].typeCase=10;

                break;
            }

            else if(MalicePiege==0 ||MalicePerso==0)
            {
                printf("ERREUR 000s...\n\n");
                system("pause");

                donjon[*x][*y].statutCase=1;
                donjon[*x][*y].typeCase=10;

            }

            else if(MalicePiege>MalicePerso)
            {
                printf("Malheureusement ce piege est trop fourbe pour vous...\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-10;

                (*y)++;

                donjon[*x][(*y)-1].statutCase=0;
                donjon[*x][(*y)].statutCase=1;
                donjon[*x][(*y)].typeCase=10;

                break;
            }

            else
            {
                printf("Arghh vous y avez presque echappe!\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-5;



                donjon[*x][(*y)].statutCase=1;
                donjon[*x][(*y)+1].typeCase=10;

                break;
            }
        }

        else if(donjon[*x][(*y)+1].statutCase==2) //cas où il y a un monstre sur la case vers laquelle on se déplace --> on engage le combat
        {
            combatD(&(*monPersonnage),&(*monstre),&(*compteurScore),donjon,&(*x),&(*y)); //fonction pour le combat en venant de la droite

            break;
        }
        else if(donjon[*x][(*y)+1].statutCase==3) //cas où il y a un monstre sur la case vers laquelle on se déplace --> on engage le combat
        {
            combatBoss(&(*monPersonnage),&(*Boss),&(*compteurScore),donjon,&(*x),&(*y)); //fonction pour combattre le boss

            break;
        }

        else
        {
            (*y)++;

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)-1].statutCase=0;

            break;
        }



    case TOUCHEGAUCHE:

        if (donjon[*x][(*y)-1].typeCase==1 || donjon[*x][(*y)-1].typeCase==2 || donjon[*x][(*y)-1].typeCase==3 || donjon[*x][(*y)-1].typeCase==5 )
        {


            printf("Deplacement impossible\n\n");
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)-1].statutCase=0;

            break;
        }

        else if(donjon[*x][(*y)-1].typeCase==9)
        {
            printf("Mince un piege!!!\n\n");
            system("pause");

            srand (time(NULL));

            int MalicePerso, MalicePiege;

            MalicePerso = (rand() % (*monPersonnage).malice+1);
            MalicePiege = (rand() % ( MaliceP+1));

            if(MalicePerso>MalicePiege)
            {
                printf("Bravo vous avez reussi a eviter ce piege!\n\n");
                system("pause");

                donjon[*x][*y].statutCase=1;
                donjon[*x][(*y)-1].typeCase=10;

                break;
            }

            else if(MalicePiege>MalicePerso)
            {
                printf("Malheureusement ce piege est trop fourbe pour vous...\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-10;

                (*y)--;

                donjon[*x][(*y)+1].statutCase=0;
                donjon[*x][(*y)].statutCase=1;
                donjon[*x][(*y)].typeCase=10;

                break;
            }

            else
            {
                printf("Arghh vous y avez presque echappe!\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-5;

                donjon[*x][*y].statutCase=1;
                donjon[*x][(*y)-1].typeCase=10;

                break;
            }
        }

        else if(donjon[*x][(*y)-1].statutCase==2)
        {
            combatG(&(*monPersonnage),&(*monstre),&(*compteurScore),donjon,&(*x),&(*y)); //combat en venant de la gauche

            break;
        }


        else
        {
            (*y)--;

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)+1].statutCase=0;

            break;
        }


    case TOUCHEHAUT:

        if (donjon[(*x)-1][*y].typeCase==1 || donjon[(*x)-1][*y].typeCase==2 || donjon[(*x)-1][*y].typeCase==3 || donjon[(*x)-1][*y].typeCase==5 )
        {
            printf("Deplacement impossible\n\n");
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[(*x)-1][*y].statutCase=0;

            break;
        }

        else if(donjon[(*x)-1][*y].typeCase==9)
        {
            printf("Mince un piege!!!\n\n");
            system("pause");

            srand (time(NULL));

            int MalicePerso, MalicePiege;

            MalicePerso = (rand() % (*monPersonnage).malice+1);
            MalicePiege = (rand() % ( MaliceP+1));

            if(MalicePerso>MalicePiege)
            {
                printf("Bravo vous avez reussi a eviter ce piege!\n\n");
                system("pause");

                donjon[*x][*y].statutCase=1;
                donjon[(*x)-1][*y].typeCase=10;

                break;
            }

            else if(MalicePiege>MalicePerso)
            {
                printf("Malheureusement ce piege est trop fourbe pour vous...\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-10;

                (*x)--;

                donjon[(*x)+1][*y].statutCase=0;
                donjon[(*x)][*y].statutCase=1;
                donjon[(*x)][*y].typeCase=10;

                break;
            }

            else
            {
                printf("Arghh vous y avez presque echappe!\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-5;

                donjon[*x][*y].statutCase=1;
                donjon[(*x)-1][*y].typeCase=10;

                break;
            }
        }

        else if(donjon[(*x)-1][*y].statutCase==2)
        {
            combatH(&(*monPersonnage),&(*monstre),&(*compteurScore),donjon,&(*x),&(*y)); //combat en allant vers le haut

            break;
        }

        else
        {
            (*x)--;

            donjon[*x][*y].statutCase=1;
            donjon[(*x)+1][*y].statutCase=0;

            break;
        }


    case TOUCHEBAS:

        if (donjon[(*x)+1][*y].typeCase==1 || donjon[(*x)+1][*y].typeCase==2 || donjon[(*x)+1][*y].typeCase==3 || donjon[(*x)+1][*y].typeCase==5 )
        {

            printf("Deplacement impossible\n\n");
            system("pause");

            donjon[(*x)+1][*y].statutCase=1;
            donjon[(*x)+1][*y].statutCase=0;

            break;
        }

        else if(donjon[(*x)+1][*y].typeCase==9)
        {
            printf("Mince un piege!!!\n\n");
            system("pause");

            srand (time(NULL));

            int MalicePerso, MalicePiege;

            MalicePerso = (rand() % (*monPersonnage).malice+1);
            MalicePiege = (rand() % ( MaliceP+1));

            if(MalicePerso>MalicePiege)
            {
                printf("Bravo vous avez reussi a eviter ce piege!\n\n");
                system("pause");

                donjon[*x][*y].statutCase=1;
                donjon[(*x)+1][*y].typeCase=10;

                break;
            }

            else if(MalicePiege>MalicePerso)
            {
                printf("Malheureusement ce piege est trop fourbe pour vous...\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-10;

                (*x)++;

                donjon[(*x)-1][*y].statutCase=0;
                donjon[(*x)][*y].statutCase=1;
                donjon[(*x)][*y].typeCase=10;

                break;
            }

            else
            {
                printf("Arghh vous y avez presque echappe!\n\n");
                system("pause");
                (*monPersonnage).endurance=(*monPersonnage).endurance-5;

                donjon[*x][*y].statutCase=1;
                donjon[(*x)+1][*y].typeCase=10;

                break;
            }
        }

        else if(donjon[(*x)+1][*y].statutCase==2)
        {
            combatB(&(*monPersonnage),&(*monstre),&(*compteurScore),donjon,&(*x),&(*y)); //combat en allant vers le bas

            break;
        }

        else
        {
            (*x)++;

            donjon[*x][*y].statutCase=1;
            donjon[(*x)-1][*y].statutCase=0;
        }

        break;
    }

//apres le deplacement du joueur, on fait bouger le monstre.
    DeplacementMonstre(donjon,&(*xr),&(*yr),&(*monstre));
}

//Deplacement du monstre
void DeplacementMonstre(sCaseDonjon donjon[LIGNES][COLONNES],int* xr, int* yr,sMonstre1* monstre)
{

    if((*monstre).endurance!=0)
    {
        int deplacementMonstre;

        deplacementMonstre=rand() % ((4)+1);// On effetcue un tirage d'un nombre aléatoire entre 1 et 4 pour attribuer un sens de déplacement au monstre

        if(donjon[*xr][(*yr)+1].statutCase==1 || donjon[*xr][(*yr)-1].statutCase==1 || donjon[(*xr)+1][*yr].statutCase==1 || donjon[(*xr)-1][*yr].statutCase==1)
        {
            donjon[*xr][*yr].statutCase=2;
        }

        else if(deplacementMonstre==1)
        {
            if(donjon[*xr][(*yr)+1].typeCase==0)
            {
                (*yr)++;

                donjon[*xr][*yr].statutCase=2;
                donjon[*xr][(*yr)-1].statutCase=0;
            }

            else
            {
                donjon[*xr][*yr].statutCase=2;
            }

        }

        else if(deplacementMonstre==2)
        {
            if(donjon[*xr][(*yr)-1].typeCase==0)
            {
                (*yr)--;

                donjon[*xr][*yr].statutCase=2;
                donjon[*xr][(*yr)+1].statutCase=0;
            }

            else
            {
                donjon[*xr][*yr].statutCase=2;
            }
        }

        else if(deplacementMonstre==3)
        {
            if(donjon[(*xr)-1][*yr].typeCase==0)
            {
                (*xr)--;

                donjon[*xr][*yr].statutCase=2;
                donjon[(*xr)+1][*yr].statutCase=0;
            }

            else
            {
                donjon[*xr][*yr].statutCase=2;
            }

        }

        else if(deplacementMonstre==4)
        {
            if(donjon[(*xr)+1][*yr].typeCase==0)
            {
                (*xr)++;

                donjon[*xr][*yr].statutCase=2;
                donjon[(*xr)-1][*yr].statutCase=0;
            }

            else
            {
                donjon[*xr][*yr].statutCase=2;
            }
        }
    }
}

//focntion générant l'attaque du monstre et du joueur et la comparaison
void combatD(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y)
{
    printf("Oh un Monstre 'R'!\n\n");
    system("pause");

    srand (time(NULL));

    int Attackjoueur,AttackR;

//Tirage au sort de l'attaque des adversaires
    Attackjoueur = (rand() % ((*monPersonnage).habilete)+1);
    AttackR = (rand() % ( ((*monstre).habilete)+1));

    if (Attackjoueur>AttackR)
    {
        printf("\n\n%s blesse le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        ((*monstre).endurance)--;

        printf("\n\nIl reste %d points de vie au monstre\n\n",(*monstre).endurance);
        system("pause");

        if((*monstre).endurance==0)
        {
            printf("\n\n%s a vaincu le monstre!\n\n",(*monPersonnage).nom);
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)+1].statutCase=0;

            (*compteurScore)++; //on incrémente le score
        }
    }

    else if (Attackjoueur<AttackR)
    {
        printf("\n\n%s est blesse par le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        (*monPersonnage).endurance--;
    }

    else
    {
        printf("\n\nAucun n'est blesse\n\n");
        system("pause");
    }
}

void combatG(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y)
{
    printf("Oh un Monstre 'R'!\n\n");
    system("pause");

    srand (time(NULL));

    int Attackjoueur,AttackR;

    Attackjoueur = (rand() % ((*monPersonnage).habilete)+1);
    AttackR = (rand() % ( ((*monstre).habilete)+1));

    if (Attackjoueur>AttackR)
    {
        printf("\n\n%s blesse le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        ((*monstre).endurance)--;

        printf("\n\nIl reste %d points de vie au monstre\n\n",(*monstre).endurance);
        system("pause");

        if((*monstre).endurance==0)
        {
            printf("\n\n%s a vaincu le monstre!\n\n",(*monPersonnage).nom);
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)-1].statutCase=0;

            (*compteurScore)++; //on incrémente le score
        }
    }

    else if (Attackjoueur<AttackR)
    {
        printf("\n\n%s est blesse par le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        (*monPersonnage).endurance--;
    }

    else
    {
        printf("\n\nAucun n'est blesse\n\n");
        system("pause");
    }
}

void combatH(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y)
{
    printf("Oh un Monstre 'R'!\n\n");
    system("pause");

    srand (time(NULL));

    int Attackjoueur,AttackR;

    Attackjoueur = (rand() % ((*monPersonnage).habilete)+1);
    AttackR = (rand() % ( ((*monstre).habilete)+1));

    if (Attackjoueur>AttackR)
    {
        printf("\n\n%s blesse le monstre\n\n",(*monPersonnage).nom);
        ((*monstre).endurance)--;

        printf("\n\nIl reste %d points de vie au monstre\n\n",(*monstre).endurance);
        system("pause");

        if((*monstre).endurance==0)
        {
            printf("\n\n%s a vaincu le monstre!\n\n",(*monPersonnage).nom);
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[(*x)-1][*y].statutCase=0;

            (*compteurScore)++; //on incrémente le score
        }
    }

    else if (Attackjoueur<AttackR)
    {
        printf("\n\n%s est blesse par le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        (*monPersonnage).endurance--;
    }

    else
    {
        printf("\n\nAucun n'est blesse\n\n");
        system("pause");
    }
}

void combatB(sPerso * monPersonnage,sMonstre1* monstre,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y)
{
    printf("Oh un Monstre 'R'!\n\n");
    system("pause");

    srand (time(NULL));

    int Attackjoueur,AttackR;

    Attackjoueur = (rand() % ((*monPersonnage).habilete)+1);
    AttackR = (rand() % ( ((*monstre).habilete)+1));

    if (Attackjoueur>AttackR)
    {
        printf("\n\n%s blesse le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        ((*monstre).endurance)--;

        printf("\n\nIl reste %d points de vie au monstre\n\n",(*monstre).endurance);
        system("pause");

        if((*monstre).endurance==0)
        {
            printf("\n\n%s a vaincu le monstre!\n\n",(*monPersonnage).nom);
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[(*x)+1][*y].statutCase=0;

            (*compteurScore)++; //on incrémente le score
        }
    }

    else if (Attackjoueur<AttackR)
    {
        printf("\n\n%s est blesse par le monstre\n\n",(*monPersonnage).nom);
        system("pause");
        (*monPersonnage).endurance--;
    }

    else
    {
        printf("\n\nAucun n'est blesse\n\n");
        system("pause");
    }
}

void combatBoss(sPerso * monPersonnage,BigBoss *Boss,int* compteurScore,sCaseDonjon donjon[LIGNES][COLONNES],int* x,int *y)
{
    printf("Oh Voici le BIG BOSS!\n\n");
    system("pause");

    srand (time(NULL));

    int Attackjoueur,AttackBoss;

    Attackjoueur = (rand() % ((*monPersonnage).habilete)+1);
    AttackBoss = (rand() % ( ((*Boss).habilete)+1));

    if (Attackjoueur>AttackBoss)
    {
        printf("\n\n%s blesse le Boss\n\n",(*monPersonnage).nom);
        system("pause");
        ((*Boss).endurance)--;

        printf("\n\nIl reste %d points de vie au Boss\n\n",(*Boss).endurance);
        system("pause");

        if((*Boss).endurance==0)
        {
            printf("\n\n%s a vaincu le Boss du Donjon!\n\n",(*monPersonnage).nom);
            system("pause");

            donjon[*x][*y].statutCase=1;
            donjon[*x][(*y)+1].statutCase=0;

            (*compteurScore)++; //on incrémente le score
        }
    }

    else if (Attackjoueur<AttackBoss)
    {
        printf("\n\n%s est blesse par le Boss\n\n",(*monPersonnage).nom);
        system("pause");

        int CoupCritique;

        CoupCritique = (rand() % ((2))+1);//on rend possible un coup critique de la part du monstre grâce à une fonction random


        if (CoupCritique==0)
        {
            printf("ERREUR ATTAQUE BOSS\n\n");
            system("pause");
        }

        else if (CoupCritique==1)
        {
            (*monPersonnage).endurance--;
        }

        else if (CoupCritique==2)
        {
            (*monPersonnage).endurance=(*monPersonnage).endurance-2;
            printf("\nMalheuresement pour %s, il inflige plus de degats\n\n",(*monPersonnage).nom);
            system("pause");
        }
    }

    else
    {
        printf("\n\nAucun n'est blesse\n\n");
        system("pause");
    }
}

 //tirage pour définir l'effet de la potion
void potions(sPerso * monPersonnage)
{
    printf("Oh une potion\n\n");
    system("pause");

    int typePotion;
    typePotion=rand() % (3)+1;

    if(typePotion==1)
    {
        printf("Rien ne se passe\n\n");
        system("pause");
    }

    else if(typePotion==2)
    {
        printf("Arghhh, quel gout atroce!!\n\n");
        system("pause");
        (*monPersonnage).endurance=(*monPersonnage).endurance-5;
    }

    else if(typePotion==3)
    {
        printf("HUM!!\n\n");
        system("pause");
        (*monPersonnage).endurance=(*monPersonnage).endurance+5;
    }

    else if(typePotion==0)
    {
        printf("0 PAS POSSIBLE\n\n");
        system("pause");
    }

    else
    {
        printf("ERREUR\n\n");
        system("pause");
    }
}

//On test la valeur de la case sur laquelle on se trouve, et on agit un fonction.
void Testcase (sCaseDonjon donjon[LIGNES][COLONNES],sPerso *monPersonnage,int *compteurScore,int* x,int* y)
{

    if(donjon[*x][*y].typeCase==6)
    {
        printf("Chouette de l'or!\n\n"); //cas où il y a de l'or sur la case voulue
        (*compteurScore)++;
        system("pause");

        donjon[*x][*y].statutCase=1;
        donjon[*x][*y].typeCase=0;

    }

    else if(donjon[*x][*y].typeCase==7) //cas où il y a une armure sur la case voulue
    {
        printf("Chouette une armure!\n\n");
        (*monPersonnage).endurance=(*monPersonnage).endurance+6;

        system("pause");

        donjon[*x][*y].statutCase=1;
        donjon[*x][*y].typeCase=0;
    }

    else if(donjon[*x][*y].typeCase==8) //cas où il y a une épée sur la case voulue
    {
        printf("Oh une epee\n\n");
        ((*monPersonnage).habilete)=((*monPersonnage).habilete)+10;
        system("pause");

        donjon[*x][*y].statutCase=1;
        donjon[*x][*y].typeCase=0;
    }

    else if (donjon[*x][*y].typeCase==10)
    {
        donjon[*x][*y].statutCase=1;
    }

    else if(donjon[*x][*y].typeCase==11) //cas où il y a une potion sur la case voulue
    {
        potions(&(*monPersonnage));

        donjon[*x][*y].statutCase=1;
        donjon[*x][*y].typeCase=0;
    }

    else
    {
        donjon[*x][*y].statutCase=1;
    }
}

//on donne les valeurs du fichier au tableau qui contient les données sur la carte
void changerCarte(sCaseDonjon donjon[LIGNES][COLONNES],FILE* fichier,sMonstre1 *monstre)
{
    int i,j;
    for(i=0; i<LIGNES; i++)
    {
        for(j=0; j<COLONNES; j++)
        {
            fscanf(fichier,"%d",&donjon[i][j].typeCase);
            fscanf(fichier,"%d",&donjon[i][j].statutCase);
        }
    }

    fclose(fichier);
    system("cls");

    (*monstre).endurance=5; //on remet la vie du monstre a son état initial
}

void choixDeCarte(int* compteurNiveau,sCaseDonjon donjon[LIGNES][COLONNES],sMonstre1 *monstre,int* x,int* y,int* xr,int* yr)
{
    FILE *fichier1; //fichiers qui seront reliés a la carte du niveau correspondant
    FILE *fichier2;
    FILE *fichier3;
    FILE *fichier4;
    FILE *fichier5;

    if((*compteurNiveau)==1)
    {
        if((fichier1=fopen(niveau1,"r")) == NULL) //on ouvre le fichier 1 qui contient le 1er niveau
        {
            fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau1); //message d'erreur
            exit(EXIT_FAILURE);
        }

        changerCarte(donjon,fichier1,&(*monstre));
        *x=5,*y=1; //on met la position du personnage au depart du niveau 1
        *xr=8,*yr=4; //on met la position du monstre au depart du niveau 1
    }
    else if((*compteurNiveau)==2)
    {
        if((fichier2=fopen(niveau2,"r")) == NULL) //on ouvre le fichier 2 qui contient le 2eme niveau
        {
            fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau2); //message d'erreur
            exit(EXIT_FAILURE);
        }

        changerCarte(donjon,fichier2,&(*monstre));
        *x=1,*y=0; //on met la position du personnage au depart du niveau 2
        *xr=5,*yr=7; //on met la position du monstre au depart du niveau 2
    }
    else if((*compteurNiveau)==3)
    {
        if((fichier3=fopen(niveau3,"r")) == NULL) //on ouvre le fichier 3 qui contient le 3eme niveau
        {
            compteurNiveau++;
            fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau3); //message d'erreur
            exit(EXIT_FAILURE);
        }

        changerCarte(donjon,fichier3,&(*monstre));
        *x=7,*y=0; //on met la position du personnage au depart du niveau 3
        *xr=4,*yr=9; //on met la position du monstre au depart du niveau 3
    }
    else if((*compteurNiveau)==4)
    {
        if((fichier4=fopen(niveau4,"r")) == NULL) //on ouvre le fichier 4 qui contient le 4eme niveau
        {
            fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau4); //message d'erreur
            exit(EXIT_FAILURE);
        }

        changerCarte(donjon,fichier4,&(*monstre));
        *x=1,*y=0; //on met la position du personnage au depart du niveau 4
        *xr=4,*yr=5; //on met la position du monstre au depart du niveau 4
    }
    else if((*compteurNiveau)==5)
    {
        if((fichier5=fopen(niveau5,"r")) == NULL) //on ouvre le fichier 5 qui contient le 5eme niveau
        {
            fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", niveau5); //message d'erreur
            exit(EXIT_FAILURE);
        }

        changerCarte(donjon,fichier5,&(*monstre));
        *x=1,*y=0; //on met la position du personnage au depart du niveau 5
        *xr=5,*yr=7; //on met la position du monstre au depart du niveau 5
    }
}
//Fonction contenant la boucle principale du jeu
void bouclejeu(sPerso* monPersonnage,int* compteurScore,int* compteurNiveau,sMonstre1* monstre,BigBoss* Boss,int* x,int* y,int* xr,int* yr,sCaseDonjon donjon[LIGNES][COLONNES])
{
    int IsRunning=1;

    FILE *save;

    while ((*monPersonnage).endurance>0 && IsRunning!=0 && (*Boss).endurance>0)//boucle principale du jeu
    {
        AfficherCarte(donjon,&(*monPersonnage),*compteurScore,*compteurNiveau); //on affiche la carte

        Deplacement(&IsRunning,donjon,&(*monPersonnage),&(*compteurScore),&(*compteurNiveau),&(*x),&(*y),&(*xr),&(*yr),&(*monstre),&(*Boss)); //le personnage se deplace

        Testcase (donjon,&(*monPersonnage),&(*compteurScore),&(*x),&(*y)); //on regarde si la carte contient un objet

        system("CLS");//effacer la carte et la réafficher.
    }

    //Voici les 3 diférents cas pour sortir de la boucle de jeu principal

    if((*monPersonnage).endurance<=0) //Le personnage meurt
    {
        printf("%s a ete tue\n\n",(*monPersonnage).nom);

        int continuerjeu;
        while(continuerjeu<1 || continuerjeu>2) //on propose de refaire une partie
        {
            printf("\nVoulez vous refaire une partie?\n1: OUI\t2: NON\n");
            scanf("%d",&continuerjeu);
        }

        if (continuerjeu==2)
        {
            printf("Merci d'avoir joue a notre jeu");
            exit(0);
        }

    }

    else if(IsRunning==0)// Quitte la partie en jeu et permet la sauvegarde
    {
        printf("Merci d'avoir joue\n\n");
        int sauvegarder;

        while (sauvegarder<1 || sauvegarder>2) //on propose la sauvegarde
        {
            printf("Voulez vous sauvegarder votre avancee?\n");

            printf("1: OUI\t2: NON\n");

            scanf("%d",&sauvegarder);
        }

        if (sauvegarder==1)
        {


            if((save=fopen(sauvegarde,"w+")) == NULL) //on ouvre le fichier qui va contenir la sauvegarde en effacant l ancienne
            {
                fprintf(stderr, " \n Impossible d ouvrir le fichier %s \n", sauvegarde); //message d'erreur
                exit(EXIT_FAILURE);
            }

            else
            {
                fprintf(save,"%s %d \n %d %d \n %d %d %d \n",(*monPersonnage).nom,(*monPersonnage).classe,*compteurScore,*compteurNiveau,(*monPersonnage).endurance,(*monPersonnage).habilete,(*monPersonnage).malice); //on met toutes ces informations dans le fichier
                fclose(save);
                printf("Vous avez bien sauvegarde!! A plus tard %s\n\n",(*monPersonnage).nom); //message de confirmation
                system("PAUSE");
                exit(0); //on quitte le jeu
            }
        }

        else
        {
            printf("Au revoir");
            exit(0); //on quitte le jeu
        }
    }

    else if((*Boss).endurance==0) // On tue le Boss
    {
        printf("BRAVO VOUS AVEZ VAINCU LE BOSS DU DONJON\n\n");

        printf("Votre score est de %d, felecitation!!\n\n",*compteurScore);

        system("PAUSE");

        int continuerjeu;
        while(continuerjeu<1 || continuerjeu>2) //on propose de continuer le jeu
        {
            printf("Voulez vous refaire une partie?\n1: OUI\t2: NON\n");

            scanf("%d",&continuerjeu);
        }
        if (continuerjeu==2)
        {
            printf("Merci d'avoir joue a notre jeu");
            exit(0); //on quitte
        }

    }
}


