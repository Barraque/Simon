	#include "../lib/libgraphique.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

/****************************************************************************/
/*							DEFINE		    */
/****************************************************************************/

#define T_CARRE 100 //Taille des carrés
#define T_ECRANX 800 //Taille de l'écran en X
#define T_ECRANY 600 //Taille de l'écran en Y
#define DECA 4 //Permet de faire clignoter les carrés
#define MAXTOUR 200 //Nombre max de tour avant la victoire
#define SEC 500 //Temps de clignotement

/****************************************************************************/
/*						   STRUCTURE	            */
/****************************************************************************/

typedef struct simon{
    int tab_couleur[MAXTOUR];
    int nbr_couleurs;
    }Simon;

/****************************************************************************/
/*		  	PROTOTYPE DES FONCTIONS                             */
/****************************************************************************/

void lecture_tab(Simon s,int diffi); //Lit le tableau et "grossis les carres" en fonction des valeurs du tableaux et modifie la vitesse d apparition en fonction de la difficultée

void ecran_noir(void); //Met un rectangle noir sur tous l ecran

void mini_ecran_noir(void); // Met un carre noir uniquement sur le plateau au centre pour pouvoir afficher du texte en continue

void ecran_noir_en_haut(void);//Meme fonction que la precedente mais seulement sur le bandeau du haut

void creation_fond(void); //Affiche les carre de base non selectionné

void a_toi_de_jouer(void); //Affiche sur l'écran quand le joueur doit jouer

void tour_ordinateur(void); //Affiche sur l'écran quand l'ordi prépare la série

Simon ajout_couleur(Simon s); //Ajoute une couleur à la strutcture

int joueur_a_bien_clique(Simon s,int diffi); //Vérifie si chaque clic correspond à la sequence et si il y a une faute lance la fonction perdu 

int a_clique_en_dehors(Simon s); //Indique si un clic est en dehors de la zone de jeu

void affiche_score(void);//Affiche dans le terminal les scores des dernieres parties dans score.txt

void renvoi_score(int score);//demande le nom du joueur puis ecris dans le fichier score.txt son nom et son meilleur score

int menu(void);//affiche le menu et attends que le joueur choisisse une difficultée

int perdu(Couleur check, int score);//affiche en "fond d'ecran" la couleur manquée par le joueur puis demande au joueur si il veut quitter ou recommencer

void bonne_sequence(void);//affiche à l'ecran Bonne sequence

void affiche_score_fenetre(int score);//affiche sur la fenetre le score actuel

void affiche_nb_tour(int nbr_tour);//affiche sur la fenetre le numero du tour actuel

void affiche_dfficulte (int diff);//affiche sur la fenetre le niveau de dificultée

void ecran_defaite(void);//affiche a l'ecran un message de remerciement pour avoir jouer

void lancement_jeu(void);//affiche que le joueur doit cliquer quand il est pret à jouer

Simon reini_struct(Simon s,int nbr_tour);//remet la variable de position dans le tableau a 0

void indique_clic(Point clic);//indique si le joueur a cliqué en grossissant le carre ou il a cliqué
