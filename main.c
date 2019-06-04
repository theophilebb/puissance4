#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_COLONNES 7
#define NB_LIGNES 6
#define  VIDE ' '
#define CROIX 'x'
#define ROND 'o'
#define TRUE 1
#define FALSE 0


typedef struct

{

    int dg;

    int vert;

    int dd;

    int horz;

}place;


int joueur1(int player, char grille[NB_COLONNES][NB_LIGNES])

{

    int colonne=1;

    printf("JOUEUR 1: %s - quelle colonne voulez-vous jouer?\n" , player == FALSE ? "ROND" : "CROIX");

    scanf("%d", &colonne);

    return colonne;



}

int joueur2(int player, char grille[NB_COLONNES][NB_LIGNES])

{

    int colonne=1;

    printf("JOUEUR 2: %s - quelle colonne voulez-vous jouer?\n" , player == FALSE ? "ROND" : "CROIX");

    scanf("%d", &colonne);

    return colonne;



}

int coupvalide(char grille[NB_COLONNES][NB_LIGNES], int colonne) // numero entre 0 et 6 indiquant la colonne jouée

{

    int y;

    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine



    colonne -=1; // pour passer de 1..NB_COLONNES à 0..NB_COLONNES-1



    if (colonne < 0 || colonne >= NB_COLONNES)

    {

        return FALSE; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide

    }



    for ( y = NB_LIGNES-1; y >=0 ; y--)

    {

        if (grille[colonne][y] == VIDE)

            lignefree = y;

    }



    if (lignefree== -1)

    {

        return FALSE; // si la colonne est pleine, le coup n'est pas valide

    }

    return TRUE;

}


void Init(char grille[NB_COLONNES][NB_LIGNES])

{

    int w, h;

    for(w = 0; w < NB_COLONNES; w++)

    {

        for(h = 0; h < NB_LIGNES; h++)

        {

            grille[w][h]=VIDE; // on initialise la tableau pour qu'il soit vide au debut

        }

    }

}


void AfficheGrille(char tableau[NB_COLONNES][NB_LIGNES])

{

    int w, h;



    printf("|");

    for(w = 0; w < NB_COLONNES; w++)

        printf(" %d ", w+1);  // on affiche le numéro de la colonne

    printf("|\n");



    printf("|");

    for(w = 0; w < NB_COLONNES; w++)

        printf("___", w+1); // un underscore pour dessiner le cadre

    printf("|\n");



    for(h = NB_LIGNES-1 ; h >= 0; h--) // on affiche la ligne du haut en haut et on descend pour avoir l'afficgage dans le bon sens

    {

        printf("|");

        for(w = 0; w< NB_COLONNES; w++)

        {

            printf(" %c ", tableau[w][h]);

        }

        printf("|\n");

    }

    printf("|");

    for(w = 0; w < NB_COLONNES; w++)

        printf("___", w+1); // une ligne 'souligné' pour dessiner le cadre

    printf("|\n");

}


int check(char grille[NB_COLONNES][NB_LIGNES])

/*


Permet d'additioner le contenu de la case adjacente correcte (meme motifs)

 au contenu de la case courante.

 */


{

    place jeu[NB_COLONNES][NB_LIGNES];

    int ligne, colonne;

    for ( ligne = 0; ligne < NB_LIGNES ; ligne++)

    {

        for ( colonne = 0; colonne < NB_COLONNES; colonne++)

        {

            /*

             Par défaut il y a toujours  1 pion sur 4 aligné

             */

            jeu[colonne][ligne].horz=1;

            jeu[colonne][ligne].vert=1;

            jeu[colonne][ligne].dg=1;

            jeu[colonne][ligne].dd=1;

        }

    }



    // pour le horizontal

    for ( ligne = 0; ligne < NB_LIGNES ; ligne++)

    {

        for ( colonne = 1; colonne < NB_COLONNES; colonne++)

        {

            if ((grille[colonne][ligne]==grille[colonne-1][ligne])&&(grille[colonne][ligne]!=VIDE))

                // meme motif

            {

                jeu[colonne][ligne].horz=jeu[colonne-1][ligne].horz+1;

                if (jeu[colonne][ligne].horz==4)

                    return TRUE;

            }

        }

    }

    // pour le vertical

    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)

    {

        for ( colonne = 0; colonne < NB_COLONNES; colonne++)

        {

            if ((grille[colonne][ligne]==grille[colonne][ligne-1])&&(grille[colonne][ligne]!=VIDE))

                // meme motif

            {

                jeu[colonne][ligne].vert=jeu[colonne][ligne-1].vert+1;

                if (jeu[colonne][ligne].vert==4)

                    return TRUE;

            }

        }

    }

    // pour la diagonale gauche:de bas à gauche vers haut à droite

    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)

    {

        for ( colonne = 0; colonne < NB_COLONNES-1; colonne++)

        {

            if ((grille[colonne][ligne]==grille[colonne+1][ligne-1])&&(grille[colonne][ligne]!=VIDE))

                // meme motif

            {

                jeu[colonne][ligne].dg=jeu[colonne+1][ligne-1].dg+1;

                if (jeu[colonne][ligne].dg==4)

                    return TRUE;

            }

        }

    }

    // pour la diagonale droite:de haut à gauche vers bas à droite

    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)

    {

        for ( colonne = 1; colonne < NB_COLONNES; colonne++)

        {

            if ((grille[colonne][ligne]==grille[colonne-1][ligne-1])&&(grille[colonne][ligne]!=VIDE))

                // meme motif

            {

                jeu[colonne][ligne].dd=jeu[colonne-1][ligne-1].dd+1;

                if (jeu[colonne][ligne].dd==4)

                    return TRUE;

            }

        }

    }

    return FALSE;

}


void joue(int player, char grille[NB_COLONNES][NB_LIGNES], int colonne )

/*

 colonne entre 1 et 7 inclus

 */

{

    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine

    int y;

    colonne -=1;



    if (colonne < 0 || colonne >= NB_COLONNES)  // ne devrait pas arriver à ce stade si coupvalide() a été appelé avant cette fonction

    {

        return ; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide

    }



    for ( y = NB_LIGNES-1; y >=0 ; y--)

    {

        if (grille[colonne][y] == VIDE)

            lignefree = y;

    }

    if (lignefree== -1) // ne devrait pas arriver a ce stade si coupvalide() a été appelé avant cette fonction

    {

        return;

    }



    grille[colonne][lignefree]= (player == FALSE) ? ROND:CROIX;

    printf("%s a joué grille[%d][%d]\n", (player == FALSE) ? "Joueur 2":"Joueur 1", colonne+1, lignefree+1);

}


int demande(int player, char grille[NB_COLONNES][NB_LIGNES])

{

    int col;

    printf("%s - A votre tour...\n" , player == FALSE ? "Joueur 2" : "Joueur 1");

    switch (player)

    {

        case TRUE:

            col = joueur1(player, grille);

            break;

        case FALSE:

            col = joueur2(player, grille);

            break;

    }

    printf("JOUEUR %s a joué la colonne %d\n" , player == FALSE ? "2" : "1", col);

    return col;

}


int main (int argc, char *argv[])

{

    int col;

    int gameover = FALSE;

    int nbcoups = 0;

    char grille[NB_COLONNES][NB_LIGNES];

    int player = TRUE;



    Init(grille);

    AfficheGrille(grille);



    while (!gameover)

    {

        do

        {

            col = demande(player, grille);

        }while(coupvalide(grille, col)==FALSE); // tant qu'il n'est pas possible de jouer là, on redemande

        joue(player, grille, col);

        printf("Joueur %s a joué:\n", player == FALSE ? "2 : ROND" : "1 : CROIX");

        AfficheGrille(grille);

        nbcoups++;

        if (check(grille)==TRUE)

        {

            gameover = TRUE;

            printf("Victoire de %s au %d ieme coups!", player == FALSE ? "JOUEUR 2" : "JOUEUR 1", nbcoups);

        }

        else if (nbcoups == NB_COLONNES*NB_LIGNES)

        {

            gameover = TRUE;

            printf("Match NUL (%d coups)\n", nbcoups);

        }

        player = !player; // au joueur suivant de jouer

    }

    return 0;

}
