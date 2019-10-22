#include "./simon13.h"

/****************************************************************************/
/*		                   FONCTION				    						*/
/****************************************************************************/
int main(int argc,char *argv[])
    {
    ouvrir_fenetre(T_ECRANX,T_ECRANY);
    affiche_score();//affiche le score dans les anciens score sur le terminale
    int nbr_tour=0,dif;
    int score = 0;
    Simon s;
    s.nbr_couleurs = 0;
	for (nbr_tour=0; nbr_tour<MAXTOUR; nbr_tour++)//boucle qui s arreteras pour eviter les boucles infini
		{	
		if(score==0)//si le score est a 0 c est que le joueur a recommencer donc il faut reinitialiser les valeurs
			{
			dif=menu();//on lance la page menu et on stocke la difficultée que le joueur veut
			ecran_noir();
			creation_fond();
			lancement_jeu();
			s=reini_struct(s,nbr_tour);
			nbr_tour=0;
			}
		s = ajout_couleur(s); //on ajoute une couleur a la sequence
		creation_fond();
		affiche_score_fenetre(score);//on affiche le score actuel a l ecran
		affiche_nb_tour(nbr_tour+1);//on affiche le nbr de tour
		affiche_dfficulte (dif);//ainsi que la difficultée
		tour_ordinateur();
		lecture_tab(s,dif);//on affiche la sequence a reproduire par rapport a la difficultée
		ecran_noir_en_haut();
		mini_ecran_noir(); //ecran noir plus petit
		a_toi_de_jouer();
		creation_fond();
		score = joueur_a_bien_clique(s,dif);//le joueur doit reproduire la sequence et si il perds le joueur perd et souhaite recommencer le score seras remis a 0
		}
    return 0;
    }
    
Simon reini_struct(Simon s,int nbr_tour)
	{
	s.nbr_couleurs=0;  //remet l indice de deplacement du tableaux a 0 pour recommencer une sequence
	return s;
	}
void ecran_noir(void)
    {
    Point dark={0,0};
    dessiner_rectangle(dark,T_ECRANX,T_ECRANY,fabrique_couleur(51,51,65));
    }
    
void mini_ecran_noir(void)
    {
    Point dark={T_ECRANX/2 - T_CARRE - DECA * 2, T_ECRANY/2 - T_CARRE - DECA * 2};
    dessiner_rectangle(dark,T_CARRE * 2 + DECA * 4,T_CARRE * 2 + DECA * 4,fabrique_couleur(51,51,65));
    }
    
void ecran_noir_en_haut(void)
	{
	Point dark={200, 25};
    dessiner_rectangle(dark, 500, 80,fabrique_couleur(51,51,65));
	}
    
void creation_fond(void)
    {
    Point carrefond={(T_ECRANX/2)-T_CARRE,T_ECRANY/2};//dessine un carre puis se decale pour creer les autre carrés
    dessiner_rectangle(carrefond,T_CARRE,T_CARRE,rouge);
    carrefond.x += T_CARRE;
    dessiner_rectangle(carrefond,T_CARRE,T_CARRE,blue);
    carrefond.y -= T_CARRE;
    dessiner_rectangle(carrefond,T_CARRE,T_CARRE,vert);
    carrefond.x -= T_CARRE;
    dessiner_rectangle(carrefond,T_CARRE,T_CARRE,jaune);
    actualiser();
    }

Simon ajout_couleur(Simon s)
    {
    s.tab_couleur[s.nbr_couleurs]= entier_aleatoire(4);//prends une valeur entre 0 et 3 et la met dans le tableau
    s.nbr_couleurs++;
    return s;
    }
    
void lecture_tab(Simon s,int diffi)
    {
    Point change_carre;
    int i;
    Couleur color;
    for(i=0;i<s.nbr_couleurs;i++) //Boucle lisant le tableau de la structure jusqu'à la dernière couleur modifiée
        {
        attente(SEC/2);
        if(s.tab_couleur[i]==0) // Si le rectangle est Rouge
            {
            change_carre.x=(T_ECRANX/2)-T_CARRE-DECA; //Le point prend la position pour afficher la séquence à la fin de la boucle
            change_carre.y=(T_ECRANY/2)-DECA; 
            color = fabrique_couleur(255,0,0);
            }
        else if(s.tab_couleur[i]==1) // Si le rectangle est Bleu
            {
            change_carre.x=(T_ECRANX/2)-DECA;
            change_carre.y=(T_ECRANY/2)-DECA;
            color = fabrique_couleur(0,0,255);
            }

        else if(s.tab_couleur[i]==2) // Si le rectangle est Vert
            {
            change_carre.x=(T_ECRANX/2)-DECA;
            change_carre.y=(T_ECRANY/2)-T_CARRE-DECA;
            color = fabrique_couleur(0,255,0);
            }
        
        else if(s.tab_couleur[i]==3) // Si le rectangle est Jaune
            {
            change_carre.x=(T_ECRANX/2)-T_CARRE-DECA;
            change_carre.y=(T_ECRANY/2)-T_CARRE-DECA; 
            color = fabrique_couleur(255,255,0);
            }
        mini_ecran_noir();
        creation_fond();
        dessiner_rectangle(change_carre,T_CARRE+2*DECA,T_CARRE+2*DECA,color); //grossi le carré pour montrer la séquence
        actualiser();
        attente(SEC/diffi); 
        mini_ecran_noir();
        creation_fond();
        }
    }

int joueur_a_bien_clique(Simon s,int diffi)
	{
    static int score=0;
	int i=0;
	Couleur check=black; //Permet de vérifier plus tard que le joueur clique au bon endroit
	Point clic={0,0};
	struct timeval debut,fin; //Structure contenant des valeurs en secondes et en micro-secondes
	gettimeofday(&debut,NULL); //Fonction de la librairie <sys/time.h> qui permet de récuperer et mettre dans la structure début le temps the_epoque
    while(i<s.nbr_couleurs) //Boucle pour faire l'intégralité de la séquence
        {
        clic=attendre_clic();
        if (((clic.x >= T_ECRANX/2 - T_CARRE) && (clic.x <= T_ECRANX/2 + T_CARRE)) && ((clic.y >= T_ECRANY/2 - T_CARRE) && (clic.y <= T_ECRANY/2 +T_CARRE)))//verifie si le joueur clique bien sur un carre
            {		
            indique_clic(clic);
         	if(s.tab_couleur[i]==0) // Si le rectangle est Rouge
              	{
        	    if (!(((clic.x >= T_ECRANX/2 - T_CARRE)&& (clic.x <= T_ECRANX/2)) && (( clic.y >= T_ECRANY/2 )&& (clic.y <= T_ECRANY/2 + T_CARRE))))
    				check = rouge; // Check prend la couleur de l'erreur
        		}
    			
    		else if(s.tab_couleur[i]==1) // Si le rectangle est Bleu
    			{
    			if (!(((clic.x >= T_ECRANX/2)&& (clic.x <= T_ECRANX/2 + T_CARRE)) && (( clic.y >= T_ECRANY/2 )&& (clic.y <= T_ECRANY/2 + T_CARRE))))
    				check= blue;
    			}
    		else if(s.tab_couleur[i]==2) // Si le rectangle est Vert
    			{
    			if (!(((clic.x >= T_ECRANX/2)&& (clic.x <= T_ECRANX/2 + T_CARRE)) && (( clic.y <= T_ECRANY/2 )&& (clic.y >= T_ECRANY/2 - T_CARRE))))
					check = vert;
    			}
    		
    		else if(s.tab_couleur[i]==3) // Si le rectangle est Jaune
    			{
    			if (!( ((clic.x >= T_ECRANX/2 - T_CARRE)&& (clic.x <= T_ECRANX/2)) && (( clic.y <= T_ECRANY/2 )&& (clic.y >= T_ECRANY/2 - T_CARRE)) ))
  					check = jaune;
    		}
    		if (check != black) //Si le check est différent du noir, il y a eu une erreur et va donc vers la fonction perdu
    			{
    			score = perdu(check, score);
    			return score;
  				}
    		else
	            i++;
    	}
        
    }
    gettimeofday(&fin,NULL);  //Fonction de la librairie <sys/time.h> qui permet de récuperer et mettre dans la structure fin le temps the_epoque
    if ((((double) ((fin.tv_sec - debut.tv_sec) * 1000000 + fin.tv_usec) - debut.tv_usec)/1000)<1000*s.nbr_couleurs*0.5) 
//Fais la différence entre les la structure fin et début convertie en micro-seconde puis en milliseconde. Si le joueur répond en moins de 0.5s par carré son score sur ce tour est doublé
    	score+=2*diffi;
    else
    	score+=1*diffi; //Diffi influence le score
    bonne_sequence();
    creation_fond();
    attente(SEC); //attente entre 2 séquences pour "respirer"
    ecran_noir();
    return score;
}

void indique_clic(Point clic)
    {
    Point gros;
    Couleur color;
//Condition pour savoir où la personne a cliquée
    if (clic.x <T_ECRANX/2 && clic.y >T_ECRANY/2) 
        {
        gros.x=(T_ECRANX/2)-T_CARRE-DECA; //Le point prend la position pour afficher la séquence à la fin de la boucle
        gros.y=(T_ECRANY/2)-DECA; 
        color = fabrique_couleur(255,0,0);
        }
    else if (clic.x > T_ECRANX/2 && clic.y >T_ECRANY/2)
        {
        gros.x=(T_ECRANX/2)-DECA;
        gros.y=(T_ECRANY/2)-DECA; 
        color = fabrique_couleur(0,0,255);
        }
    else if (clic.x > T_ECRANX/2 && clic.y < T_ECRANY/2)
        {
        gros.x=(T_ECRANX/2)-DECA;
        gros.y=(T_ECRANY/2)-T_CARRE-DECA; 
        color = fabrique_couleur(0,255,0);
        }
    else if (clic.x < T_ECRANX/2 && clic.y < T_ECRANY/2)
        {
        gros.x=(T_ECRANX/2)-T_CARRE-DECA;
        gros.y=(T_ECRANY/2)-T_CARRE-DECA; 
        color = fabrique_couleur(255,255,0);
        }
    mini_ecran_noir();
    creation_fond();
    dessiner_rectangle(gros,T_CARRE+2*DECA,T_CARRE+2*DECA,color); //grossi le carré pour montrer un clic
    actualiser();
    attente(50);
    mini_ecran_noir();
    creation_fond();
    actualiser();
    }

void affiche_score(void)
    {
    printf("Ancien score\n");
    FILE *txt=fopen("./score.txt","r"); //ouvre le fichier en mode lecture
    char nom[50];
    int resu;
    while(!feof(txt)) //boucle pour afficher le contenu ligne par ligne jusqu'à la fin du fichier 
        {
        fscanf(txt,"%s : %d\n",nom,&resu);
        printf("%s : %d\n",nom,resu);
        }
    printf("-------------------------------------------\n");
    }
void renvoi_score(int score)
    {
    char nom[50];
    FILE *txt=NULL; 
    txt = fopen("./score.txt","a"); //Ouvre le fichier en mode écriture sans écrasé la mémoire et se met à la fin du fichier grâce au "a"
    printf("Quel est ton nom ?\n");
    scanf("%s",nom);
    fprintf(txt,"%s : %d\n",nom,score); //Ecrit le nom choisi et son score dans le fichier
    }
int menu(void)
	{
	ecran_noir();
	Point c;
	Point haut ={0,0};
	dessiner_rectangle(haut,T_ECRANX,90,darkgreen);
	Point bas ={0,T_ECRANY-90};
	dessiner_rectangle(bas,T_ECRANX,90,darkgreen);
	bas.y+=4;
	afficher_texte("Fait par Louis et Valentin",17,bas,white);
	bas.y+=25;
	afficher_texte("Projet 1",17,bas,white);
	Point img = {T_ECRANX/2 - 125 ,T_ECRANY/2-125};
	afficher_image("unnamed2.bmp", img);	
//Création interface graphique du menu
	Point p={ T_ECRANX/2 - taille_texte("Bienvenue dans Simon !!!", 30).x / 2 ,25};
	Point p1={ T_ECRANX/2 - taille_texte("Choix de la difficulte", 20).x /2,(T_ECRANY/3)*2-20};
	afficher_texte("Bienvenue dans Simon !!!",30,p,white);
	afficher_texte("Choix de la difficulte",20,p1,white);
	Point b1 ={T_ECRANX/2 -225,(T_ECRANY/3)*2+20};
	dessiner_rectangle(b1,50,50,lightblue);
	Point t1 ={T_ECRANX/2 -219,(T_ECRANY/3)*2+26}; 
//Créer 5 boutons pour chaque niveau de difficulté
	afficher_texte("x1",30,t1,black);
	t1.x+=101;
	b1.x+=100;
	dessiner_rectangle(b1,50,50,vert);
	afficher_texte("x2",30,t1,black);
	t1.x+=100;
	b1.x+=100;
	dessiner_rectangle(b1,50,50,jaune);
	afficher_texte("x3",30,t1,black);
	t1.x+=100;
	b1.x+=100;
	dessiner_rectangle(b1,50,50,orange);
	afficher_texte("x4",30,t1,black);
	t1.x+=99;
	b1.x+=100;
	dessiner_rectangle(b1,50,50,rouge);
	afficher_texte("x5",30,t1,black);
	actualiser();
	do
		{
		c = attendre_clic();
		if ((c.x >= T_ECRANX/2 -225 && c.x <= T_ECRANX/2 -225 + 50) && (c.y >= (T_ECRANY/3)*2+26 && c.y <= (T_ECRANY/3)*2+26 + 50)) //Zone a cliqué pour avoir la difficulté 1
			return 1;
		else if((c.x >= T_ECRANX/2 -225 + 100 && c.x <= T_ECRANX/2 -225 + 50+100) && (c.y >= (T_ECRANY/3)*2+20 && c.y <= (T_ECRANY/3)*2+26 + 50))//Zone a cliqué pour avoir la difficulté 2
			return 2;
		else if((c.x >= T_ECRANX/2 -225 + 200 && c.x <= T_ECRANX/2 -225 + 50+200) && (c.y >= (T_ECRANY/3)*2+20 && c.y <= (T_ECRANY/3)*2+26 + 50))//Zone a cliqué pour avoir la difficulté 3
			return 3;
		else if((c.x >= T_ECRANX/2 -225 + 300 && c.x <= T_ECRANX/2 -225 + 50+300) && (c.y >= (T_ECRANY/3)*2+20 && c.y <= (T_ECRANY/3)*2+26 + 50))//Zone a cliqué pour avoir la difficulté 4
			return 4;
		else if((c.x >= T_ECRANX/2 -225 + 400 && c.x <= T_ECRANX/2 - 225 + 50 + 400) && (c.y >= (T_ECRANY/3)*2+20 && c.y <= (T_ECRANY/3)*2+26 + 50))//Zone a cliqué pour avoir la difficulté 5
			return 5;
		}while ( (c.y != (c.y >= (T_ECRANY/3)*2+20 && c.y <= (T_ECRANY/3)*2+26 + 50) ) || (c.x != (c.x >= T_ECRANX/2 -225 && c.x <= T_ECRANX/2 -225 + 50) || (c.x >= T_ECRANX/2 -225 + 100 && c.x <= T_ECRANX/2 -225 + 50+100) || (c.x >= T_ECRANX/2 -225 + 200 && c.x <= T_ECRANX/2 -225 + 50+200) || (c.x >= T_ECRANX/2 -225 + 300 && c.x <= T_ECRANX/2 -225 + 50+300) || (c.x >= T_ECRANX/2 -225 + 400 && c.x <= T_ECRANX/2 - 225 + 50 + 400) ) );
// cette boucle permet d'ignorer tout clic en dehors de la zone de clic souhaitée
    return -1;
	}

void lancement_jeu (void)
	{
	Couleur c;
	c = fabrique_couleur(175, 175, 175);  
	Point p={T_ECRANX/2 - taille_texte("Cliquer pour lancer la partie", 20).x / 2 ,30};
	Point p1={T_ECRANX/2 - taille_texte("Tenez vous pret", 20).x / 2 ,60};
	afficher_texte("Cliquer pour lancer la partie", 20, p, c);
	afficher_texte("Tenez vous pret", 20, p1, c);
	actualiser();
	attendre_clic(); 
	ecran_noir_en_haut();
	}

void bonne_sequence(void)
	{
	Point gg={0,0};
	Point p={ T_ECRANX / 2 - taille_texte("Bonne Sequence", 40).x / 2 ,30};
	Couleur c;
	c = fabrique_couleur(0, 0, 0); 
    dessiner_rectangle(gg,T_ECRANX,T_ECRANY,fabrique_couleur(91,91,105));
    afficher_texte("Bonne Sequence", 40,p ,c);
    actualiser();
	}
	
void a_toi_de_jouer(void)
	{
	Point p={T_ECRANX / 2 - taille_texte("A toi de jouer", 20).x / 2 ,30};
	Couleur c;
	c = fabrique_couleur(175, 175, 175); 
	afficher_texte("A toi de jouer", 20, p, c);
	actualiser();
	}
	
void tour_ordinateur(void)
	{
	Point p={T_ECRANX / 2 - taille_texte("Tour de l'ordinateur", 20).x / 2 ,30};
	Couleur c;
	c = fabrique_couleur(175, 175, 175); 
	afficher_texte("Tour de l'ordinateur", 20, p, c);
	actualiser();
	}
	
void affiche_score_fenetre(int score)
	{
	char s[50]; //Stock tout le texte a afficher dans un tableau pour pouvoir stocker la variable score
	Point p={T_ECRANX/2 + T_ECRANX/4,T_ECRANY/2};
	Couleur c;
	c = fabrique_couleur(175, 175, 175); 
	sprintf(s, "Score : %d", score ); //utilisé pour afficher une variable sur l'interface graphique
	afficher_texte(s, 20, p, c); 
	actualiser();
	}
	
void affiche_nb_tour (int tour)
	{
	char t[50]; //Stock tout le texte a afficher dans un tableau pour pouvoir stocker la variable score
	Point p={T_ECRANX/2 + T_ECRANX/4,T_ECRANY/2 - 25};
	Couleur c;
	c = fabrique_couleur(175, 175, 175);
	if (tour==1)
		sprintf(t, "1er Tour"); 
	else 
		sprintf(t, "%deme Tour", tour); //utilisé pour afficher une variable sur l'interface graphique
	afficher_texte(t, 20, p, c);
	actualiser();
	}
	
int perdu (Couleur perd, int score)
	{
    static int scorememo=-1; //memoire du meilleur score
    if(score > scorememo) //Permet de garder en mémoire le meilleur score pour l'afficher plus tard
    	{
        scorememo = score;
        }
	Point ca={0,0};
	Point pa={30,30};
    Point ta={T_ECRANX / 2 - taille_texte("perdu lol", 30).x / 2 ,T_ECRANY/2- 33};
	dessiner_rectangle(ca,T_ECRANX,T_ECRANY,perd);
	afficher_texte("La couleur de fond est la couleur que tu as ratee (voir terminal pour rentrer votre nom)",15,pa,black);
	afficher_texte("perdu lol",30,ta,black);
	actualiser();
	
	char s[50]; //Stock tout le texte a afficher dans un tableau pour pouvoir stocker la variable score
	char s2[50];
	sprintf(s, "Score final : %d point(s)", score ); //sprintf permet d'afficher une variable sur l'interface graphique
	sprintf(s2, "Meilleur score : %d point(s)", scorememo );
	Couleur coul;
	Couleur coul2;
	coul2 = fabrique_couleur(0, 0, 0);
	coul = fabrique_couleur(175, 175, 175);
	Point c; 
	Point t = {T_ECRANX / 2 - taille_texte("Score final : 10 point(s)", 20).x / 2 ,T_ECRANY/2 - T_ECRANY/6 + 30};
	Point t2 = {T_ECRANX / 2 - taille_texte("Meilleur score : 10 point(s)", 20).x / 2 ,T_ECRANY/2 - T_ECRANY/6 };
	Point a = {T_ECRANX - 187, T_ECRANY - 135};
	Point b = {T_ECRANX - 187, T_ECRANY - 70};
	Point m = {T_ECRANX - 200, T_ECRANY - 150}; 
	Point q = {T_ECRANX - 200, T_ECRANY - 85};
	
	dessiner_rectangle(m, 170, 55, darkgreen);
	dessiner_rectangle(q, 170, 55, darkred);

	afficher_texte(s, 20, t, coul2); 
	afficher_texte(s2, 20, t2, coul2); 
	afficher_texte("Recommencer", 20, a, coul);
	afficher_texte("Quitter", 20, b, coul);
	actualiser();
	
	do 
		{
		c = attendre_clic();
	
		if ( (c.x >= T_ECRANX - 200 && c.x <= T_ECRANX - 30) && (c.y >= T_ECRANY - 150 && c.y <= T_ECRANY - 95) ) //Condition de clic pour recommencer une partie 
			{
			ecran_noir();
			return 0;
			}
	
		 else if ((c.x >= T_ECRANX - 200 && c.x <= T_ECRANX - 30) && (c.y >= T_ECRANY - 85 && c.y <= T_ECRANY - 30)) //Condition de clic pour quitter le jeu
			{ 
			ecran_noir();
			ecran_defaite();
			renvoi_score(scorememo);
			fermer_fenetre();
            break;
			}
		} while ( (c.x != (c.x >= T_ECRANX - 200 && c.x <= T_ECRANX - 30)) || (c.y != (c.y >= T_ECRANY - 150 && c.y <= T_ECRANY - 95) || (c.y >= T_ECRANY - 85 && c.y <= T_ECRANY - 30) ) );
// cette boucle permet d'ignorer tout clic en dehors de la zone de clic souhaitée
    return -1;
}

void ecran_defaite(void)
	{
	ecran_noir(); 
	Couleur coul = fabrique_couleur(175, 175, 175);
	Point p = {T_ECRANX / 2 - taille_texte("Merci d'avoir joue", 30).x / 2 , T_ECRANY/2 - 20};
	Point p1 = {T_ECRANX / 2 - taille_texte("A bientot", 30).x / 2 , T_ECRANY/2 - 20 + 40};
	Point p2 = {T_ECRANX / 2 - taille_texte("Rentrer votre nom sur le Terminal", 20).x / 2 , T_ECRANY/2 - 20 + 100};
	afficher_texte("Merci d'avoir joue", 30, p, coul);
	afficher_texte("A bientot", 30, p1, coul);
	afficher_texte("Rentrer votre nom sur le Terminal", 20, p2, coul);
	actualiser();
	}
	
void affiche_dfficulte (int diff)
	{
	char s[50]; //Stock tout le texte a afficher dans un tableau pour pouvoir stocker la variable score
	Point p={T_ECRANX/2 + T_ECRANX/4,T_ECRANY/2 - T_ECRANY/6};
	Couleur c;
	c = fabrique_couleur(175, 175, 175); 
	sprintf(s, "Vitesse : x%d", diff ); //utilisé pour afficher une variable sur l'interface graphique
	afficher_texte(s, 20, p, c);
	actualiser();
	}	
    
	


    
