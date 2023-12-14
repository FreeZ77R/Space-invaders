#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define NBV 5
#define NBVITA 3

/*---------------------------------------------------------------------------*/
/* GESTION DU TERMINAL */
/*---------------------------------------------------------------------------*/
void gotoxy(int x, int y);
void color(int cT,int cF);
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* GESTION DU JEU */
/*---------------------------------------------------------------------------*/
/*Fct qui affiche la page d'accueil*/
void accueil(void);
/*Fct qui affiche un cadre autour du menu*/
void cadre_menu(void);
/*Fct qui g�re le menu*/
int menu(void);
/*Fct qui affiche les regles pour jouer*/
void regle(void);
/*Fct qui demande de choisir la difficult�e*/
int difficult(void);
/*Fct qui d�limite la mise en page du jeu*/
void mise_en_page_jeu(void);
/*Fct qui g�re affiche du secteur droit quand on joue*/
void affichage_droit_jeu(int vie, int score, int elim_vaisseaux, int elim_boss);
/*Fct qui s'occupe d'effacer le tir pr�c�dent*/
void effacer_tir(int x_tir);
/*Fct qui affiche les vqisseaux ennemis*/
int affichage_vaisseaux(int tabxA[NBV], int tabyA[NBV], int dif);
/*Fct qui g�re la latence dans le jeu*/
void latence(int dif);


/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* FONCTION PRINCIPALE */
/*---------------------------------------------------------------------------*/
int main()
{
/*--------------DECLARATION DES VARIABLES------------------------------------*/
    time_t start_t,end_t;/*d�but et fin du timer*/
    double temps,min,s;/*affect� � la diff�rence de temps �coul�, les minutes et les secondes*/


    int choix=0,ite=0,i;/*ite:nb d'it�rations / choix:choix du menu*/
    int tabxA[NBV];/*tableau des positions en x des vaisseaux ennemis*/
    int tabyA[NBV]= {1,6,9,12,15};/*tableau des positions en Y des vaisseaux ennemis*/
    int tabxV[NBVITA];/*tableau des positions en x des vitamines*/
    int tabyV[NBVITA]= {1,1,1}; /*tableau des positions en Y des vitamines*/
    int vie=5;/*nombre de vies*/
    int dif;/*difficult�*/
    int y_base=23,y_tir;/*position en Y de la base et du tir*/
    int x_base=40,x_tir;/*position en X de la base et du tir*/
    int x_boss;/*position en X du BOSS*/
    int y_boss=1;/*position en Y du boss*/
    char touche;/*touche s�lectionner sur le clavier*/
    int fin;/*variable qui lorsqu'elle vaut 0 indique la fin du jeu*/
    int score=0;/*score*/
    int secu=0;/*blindage*/
    int compteur_tir=0;/*compte les tirs que se prend le BOSS*/
    int fin_boss=1;/*est une condition de fin du jeu*/
    int modeboss=0;/*conditionne l'affichage du boss*/
    int mode_vit=0;/*conditionne l'affichage des vitamines*/
    int compteur_vit=0;/*compte les d�placements en Y des vitamines*/
    int elim_vaisseaux=0;/*compte les �liminations de vaisseaux*/
    int elim_boss=0;/*compte les �liminations de BOSS*/
/*--------------------------------------------------------------------------*/

    /*Fixe la taille de l'�cran*/
    system("mode con lines=50 cols=150");
    srand(time(NULL));
    /*Appel de la fct accueil*/
    accueil();

/*------------------MENU PRINCIPAL----------------------*/
    while(choix!=4)
    {
        fin=1;//initialisation
        touche='e';//initialisation
        /*Appel de la fonction cadre_menu*/
        cadre_menu();

        /*Appel de la fct menu*/
        choix=menu();

        /*choix difficultee*/
        if(choix==1)
        {
            secu=1;
            dif=difficult();
            getchar();
            system("cls");
        }
        /*arr�t du programme*/
        else if(choix==4)
        {
            return 0;
        }
        /*affichage r�gles*/
        else if(choix==3)
        {
            regle();

            getchar();
            getchar();
            system("cls");
        }

        /*lancement du jeu*/
        else if(choix==2)
        {
            if(secu==0)
            {
                printf("Vous devez d'abord choisir votre difficultee !\n\n\nAppuyez sur une touche pour recommencer...");
                getchar();
                getchar();
                system("cls");
            }
            else
            {
                getchar();
                system("cls");

                mise_en_page_jeu();
/*-------------------------------------------------------------------------*/

/*--------------INITIALISATION DES COORDONN�ES en X des vaisseaux, vitamines et BOSS------------*/
                for(i=0; i<NBV; i++)
                {
                    tabxA[i]=rand()%79 + 1;
                }
                for(i=0; i<NBVITA; i++)
                {
                    tabxV[i]=rand()%79 + 1;
                }
                x_boss=rand()%79 + 1;
                y_boss=1;
/*----------------------------------------------------------------------------------------------*/

/*______________LANCEMENT DU JEU_______________________________________________________*/
                while(fin!=0)//condition d'arr�t du jeu
                {
                    time(&start_t);//d�but du timer
                    ite=ite+1;
                    score=score+1;

/*------------------AFFICHAGE SECTEUR DROIT du jeu---------------------------*/

                    affichage_droit_jeu(vie,score,elim_vaisseaux,elim_boss);

/*---------------------------------------------------------------------------*/


/*------------------EFFACEMENT DU TIR pr�c�dent-----------------*/

                    effacer_tir(x_tir);

/*--------------------------------------------------------------*/


/*------------------AFFICHAGE DES VAISSEAUX--------------------*/

                    affichage_vaisseaux(tabxA,tabyA,dif);

/*------------------------------------------------------------*/

/*------------------BOSS--------------------------------------*/
                    if(ite%100==0)
                    {
                        modeboss=1;
                    }
                    if (modeboss==1)
                    {
                        gotoxy(x_boss,y_boss);
                        printf("       ");

                        if (ite%10==0)
                            y_boss=y_boss+1;


                        gotoxy(x_boss,y_boss);
                        color(12,0);
                        printf("|-----|");
                        color(15,0);
                        if(y_boss>23)
                        {
                            fin_boss=0;
                        }
                    }
/*----------------------------------------------------------*/

/*-------------------VITAMINES------------------------------*/
                    if(ite>100)//Condition d'affichage pour vitamines
                    {
                        /*Affichage vitamines*/
                        for(i=0; i<NBVITA; i++)
                        {
                            gotoxy(tabxV[i],tabyV[i]);
                            printf("   ");
                            /*La difficult�e va jouer sur l'incr�mentation en Y des vaisseaux*/
                            if(dif==1)
                            {
                                tabyV[i]=tabyV[i]+1;
                            }
                            else if(dif==2)
                            {
                                tabyV[i]=tabyV[i]+2;
                            }
                            else
                            {
                                tabyV[i]=tabyV[i]+2;
                            }
                            gotoxy(tabxV[i],tabyV[i]);
                            color(2,0);
                            printf("xxx");
                            color(15,0);

                            if(tabyV[i]>23)
                            {
                                gotoxy(tabxV[i],tabyV[i]);
                                printf("   ");
                                tabyV[i]=1;

                                tabxV[i]=rand()%79 + 1;
                            }
                        }
                    }
/*----------------------------------------------------*/

/*__________________D�PLACEMENT, ACTIONS ET AFFICHAGE DE LA BASE______________________________________________*/
                    gotoxy(x_base,y_base);
                    printf(" ");

                    //if(kbhit()==1)
                    //{
                    touche = getchar();

/*----------------------SI ON APPUIE SUR LA TOUCHE A:------------------------------*/
                        if(touche=='a')
                        {
                            if(x_base>1)//saturation du bord gauche
                            {
                                x_base= x_base-1;//d�placement vers la gauche
                            }
                        }
/*---------------------------------------------------------------------------------*/

/*----------------------SI ON APPUIE SUR l'ESPACE = D�TECTION DE TIR:--------------*/
                        if(touche==32)
                        {
                            x_tir=x_base;
                            y_tir=22;
                            while(y_tir>2)
                            {
                                y_tir--;//dessiner le tir � la bonne position

                                gotoxy(x_tir,y_tir);
                                color(11,0);
                                printf("|");
                                color(15,0);
/*---------------------------------------------------------------------------------*/

/*------------------------------VAISSEAU TOUCHER = DISPARITION---------------------*/
                                for(i=0; i<NBV; i++)
                                {
                                    if((x_tir==tabxA[i] || x_tir==tabxA[i]+1 || x_tir==tabxA[i]+2) && y_tir==tabyA[i])
                                    {
                                        gotoxy(tabxA[i],tabyA[i]);
                                        printf("   ");

                                        tabyA[i]=1;
                                        tabxA[i]=rand()%79 + 1;

                                        score=score+20;
                                        elim_vaisseaux++;
                                    }
                                }
/*---------------------------------------------------------------------------------*/
/*------------------------------BOSS TOUCHER 5 FOIS = DISPARITION------------------*/
                                if((x_tir==x_boss || x_tir==x_boss+1 || x_tir==x_boss+2 || x_tir==x_boss+3 || x_tir==x_boss+4 || x_tir==x_boss+5 || x_tir==x_boss+6) && y_tir==y_boss)
                                {
                                    compteur_tir++;
                                    if(compteur_tir>=5)
                                    {
                                        gotoxy(x_boss,y_boss);
                                        printf("       ");
                                        modeboss= 0;
                                        y_boss=1;
                                        x_boss=rand()%79 + 1;
                                        compteur_tir=0;
                                        score=score+50;
                                        elim_boss++;
                                    }
                                }
                            }
                        //}
/*---------------------------------------------------------------------------------*/
/*__________________________________________________________________________________________________________*/

/*----------------------Si on appuie sur la touche Z:------------------------------*/
                        if(touche=='z')
                        {
                            if(x_base<85)//saturation sur le bord droit !
                            {
                                x_base= x_base+1;//d�placement � droite
                            }

                        }
                    }
/*----------------------------------------------------------------------------------*/

/*------------------DESSINER LE PERSSONAGE (BASE) A LA BONNE POSITION---------------*/
                    gotoxy(x_base,y_base);
                    printf("*");
/*----------------------------------------------------------------------------------*/

/*------------------Fluctuation des vies---------------------------------*/
                    for(i=0; i<NBV; i++)
                    {
                        /*Si la base touche un vaisseau alors vie=vie-1*/
                        if( (x_base==tabxA[i] || x_base==tabxA[i]+1 || x_base==tabxA[i]+2) && y_base==tabyA[i])
                        {
                            vie=vie-1;
                        }
                        /*Si la base touche un vaisseau alors vie=vie+1*/
                        if( (x_base==tabxV[i] || x_base==tabxV[i]+1 || x_base==tabxV[i]+2) && y_base==tabyV[i])
                        {
                            vie=vie+1;
                        }
                    }
/*-----------------------------------------------------------------------*/

/*------------------TEMPS DE LATENCE AVANT LE RELANCEMENT DE LA BOUCLE---*/

                    latence(dif);

/*-----------------------------------------------------------------------*/

/*-------------------TOUTES LES CONDITIONS DE FIN DE JEU-----------------*/
                    if(fin_boss==0)
                    {
                        vie=0;
                    }
                    if(vie<=0)
                    {

                        fin=0;
                        system("cls");
                        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\tVOUS AVEZ PERDU !");
                        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t   Score: %d",score);

                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour continuer...");
                        getchar();
                        system("cls");
                    }
                    if(touche==27)// = appuyez sur la touche ECHAP
                    {

                        fin=0;
                        system("cls");
                        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\tVOUS AVEZ PERDU !");
                        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t   Score: %d",score);

                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour continuer...");
                        getchar();
                        system("cls");
                    }
/*------------------------------------------------------------------------*/

/*------------------TIMER: CALCUL ET AFFICHAGE----------------------------*/
                    time(&end_t);
                    temps = difftime(end_t, start_t);
                    if(temps>=1)
                    {
                        s=s+1;
                        if(s>=60)
                        {
                            min=min+1;
                            s=0;
                        }
                    }
                    gotoxy(90,24);
                    printf("temps: %2.lf min %2.lf s",min,s);
                    if(fin==0)
                    {
                        system("cls");
                    }
/*-------------------------------------------------------------------------*/
                }
/*--------------RESET n�c�ssaires des variables si l'utilisateur souhaite faire une nouvelle partie*/
                ite=0;
                vie=5;
                score=0;
                fin_boss=1;
                modeboss=0;
                min=0;
                s=0;
/*--------------------------------------------------------------------------*/
            }
        }
    }
}
void accueil(void)
{
    color(14,0);

    printf("\t\t******************************************************************************************\n"
           "\t\t*                                                                                        *\n"
           "\t\t*                                                                                        *\n"
           "\t\t*                  ,adPPYba, 8b,dPPYba,  ,adPPYYba,  ,adPPYba,  ,adPPYba,                *\n"
           "\t\t*                  I8[    '' 88P'    8a          Y8  a8'        8P_____88                *\n"
           "\t\t*                   `Y8ba,   88       d8 ,adPPPPP88  8b         8PP''''''                *\n"
           "\t\t*                  aa    ]8I 88b,   ,a8  88,    ,88  8a,   ,aa  8b,   ,aa                *\n"
           "\t\t*                  `'YbbdP   88`YbbdPD   `'8bbdP'Y8  `'Ybbd8D   `'Ybbd8''                *\n"
           "\t\t*                            88                                                          *\n"
           "\t\t*                            88                                                          *\n"
           "\t\t*                                                                                        *\n"
           "\t\t*                                                  88                                    *\n"
           "\t\t*    88                                            88                                    *\n"
           "\t\t*                                                  88                                    *\n"
           "\t\t*    88 8b,dPPYba, 8b       d8 ,adPPYYba,  ,adPPYb,88  ,adPPYba, 8b,dPPYba, ,adPPYba,    *\n"
           "\t\t*    88 88P'    8a `8b     d8'        `Y8 a8    ` Y88 a8P_____88 88P'    Y8 I8[    ''    *\n"
           "\t\t*    88 88      88  `8b   d8'  ,adPPPPP88 8b       88 8PP''''''' 88          `'Y8ba,     *\n"
           "\t\t*    88 88      88   `8b,d8'   88,    ,88 '8a,   ,d88 '8b,   ,aa 88         aa    ]8I    *\n"
           "\t\t*    88 88      88     '8'     `'8bbdP'Y8  `'8bbdP'Y8  `'Ybbd8'  88         `'YbbdP''    *\n"
           "\t\t*                                                                                        *\n"
           "\t\t*                                                                                        *\n"
           "\t\t******************************************************************************************");
    color(15,0);

    printf("\n\nAppuyez sur une touche pour continuer...");
    getchar();
    system("cls");
}

void cadre_menu(void)
{
    color(3,0);
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t**********************************************\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t*                                            *\n"
           "\t\t\t\t\t\t**********************************************\n");
    color(15,0);
}

int menu(void)
{
    int c;

    gotoxy(64,11);
    printf("SPACE INVADERS\n\n\n\t\t\t\t\t\t\t1-)Choisisser la difficultee:\n\t\t\t\t\t\t\t2-)Jouer\n\t\t\t\t\t\t\t3-)Regles\n\t\t\t\t\t\t\t4-)Quitter\n\n\t\t\t\t\t\t\tChoix:");
    scanf("%d",&c);

    while(c<1 || c>4)
    {
        printf("Saisissez un choix du menu possible ! Recommencez :");
        printf("Appuyez sur une touche pour recommencer !");

        getchar();
        getchar();
        system("cls");

        printf("\n\n\n\n\n\n\t\t\t\t\t\t SPACE INVADERS\n\n\n\n\t\t\t\t\t1-)Choisissez la difficultee:\n\t\t\t\t\t2-)Jouer\n\t\t\t\t\t3-)Quitter\n\n\t\t\t\t\tChoix:");
        scanf("%d",&c);
    }
    return c;
}

void regle(void)
{

    printf("\n\n\nComment jouer:\n\n\t1-Deplacer votre base avec les touches 'A'(gauche), 'Z'(droite) afin d'eviter les vaisseaux ennemis '___'.");
    printf("\n\n\t2-Attention a votre vie ! Initialement a 5, elle diminue si vous percutez des vaisseaux ennemis.");
    printf("\n\t  Pour gagner a nouveau des vies percutez des vitamines 'xxx'.");
    printf("\n\n\t3-Defendez votre base pour faire durer la partie !");
    printf("\n\t  Avec la touche 'ESPACE', vous envoyez des lasers, si le laser touche le vaisseau ennemis,");
    printf("\n\t  alors le vaisseau disparait.");
    printf("\n\nAppuyez sur une touche pour continuer...");
}

int difficult(void)
{
    int c;

    printf("\n\n\nVous avez le choix entre 3 difficultees:1-)Facile\n\t\t\t\t\t2-)Moyenne\n\t\t\t\t\t3-)Difficile\n\nChoix :");
    scanf("%d",&c);

    while(c<1 || c>3)
    {
        printf("Saisissez un choix du menu possible ! Recommencez :");
        scanf("%d",&c);
    }

    return c;

}

void mise_en_page_jeu(void)
{
    color(3,0);
    printf("--------------------------------------------------------------------------------------------------------------\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "|                                                                                     |                      |\n"
           "--------------------------------------------------------------------------------------------------------------");
    color(15,0);
}

void affichage_droit_jeu(int vie, int score, int elim_vaisseaux, int elim_boss)
{
    /*Affichage SPACE INVADERS*/
    gotoxy(92,1);
    printf("SPACE INVADERS");

    /*Affichage nb vie*/
    gotoxy(90,4);
    printf("vies:%d",vie);

    /*Affichage score*/
    gotoxy(90,9);
    printf("score:%d",score);

    /*Affichage nb vaisseaux �limin�*/
    gotoxy(90,14);
    printf("X vaisseaux:%d",elim_vaisseaux);

    /*Affichage nb boss �limin�*/
    gotoxy(90,19);
    printf("X boss:%d",elim_boss);
}

void effacer_tir(int x_tir)
{
    int y_tir=22;
    while(y_tir>2)
    {
        y_tir--;

        gotoxy(x_tir,y_tir);
        printf(" ");
    }
}

int affichage_vaisseaux(int tabxA[NBV], int tabyA[NBV], int dif)
{
    int i;

    for(i=0; i<NBV; i++)
    {
        gotoxy(tabxA[i],tabyA[i]);
        printf("   ");
        /*La difficult�e va jouer sur l'incr�mentation en Y des vaisseaux*/
        if(dif==1)
        {
            tabyA[i]=tabyA[i]+1;
        }
        else if(dif==2)
        {
            tabyA[i]=tabyA[i]+2;
        }
        else
        {
            tabyA[i]=tabyA[i]+2;
        }

        if(tabyA[i]>24)
        {
            tabyA[i]=1;

            tabxA[i]=rand()%79 + 1;
        }
        gotoxy(tabxA[i],tabyA[i]);
        color(4,0);
        printf("___");
        color(15,0);
    }
}

void latence(int dif)
{
    if(dif==1 || dif==2)
    {
        Sleep(150);
    }
    if(dif==3)//la difficult�e 3 va jouer sur le sleep sinon probl�me
    {
        Sleep(135);
    }
}
/*---------------------------------------------------------------------------*/
/* FONCTIONS DE GESTION D'ECRAN */
/*---------------------------------------------------------------------------*/

/*****************************************/
/*  POSITIONNEMENT DU CURSEUR SUR L'ECRAN
    x est la colonne et y est la ligne   */
/*****************************************/
void gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

/************************************************************/
/*  Choix des couleurs de la police et de la fen�tre CONSOLE
    cT correspond � la couleur du texte
    cF correspond � la couleur de fond
    Codes couleurs :
        0: noir
        1: bleu fonc�
        2: vert
        3: bleu-gris
        4: marron
        5: pourpre
        6: kaki
        7: gris clair
        8: gris
        9: bleu
        10: vert fluo
        11: turquoise
        12: rouge
        13: rose fluo
        14: jaune fluo
        15: blanc               */
/************************************************************/

void color(int cT,int cF)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,cF*16+cT);

}

