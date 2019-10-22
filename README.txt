Travail accompli :

	Nous avons bien apprecié le projet, il faudrait meme instaurer plus de travaux de ce type car apprendre par le projet est une des meilleures facons 	d'apprendre et d'acquerir de l'experience (philosophie de nous).

	Fonction réalisée par Valouz :

		- mini_ecran_noir

		- ecran_noir_en_haut

		- a_toi_de_jouer

		- tour_ordinateur

		- ajout_couleur

		- bonne_sequence

		- affiche_score_fenetre

		- affiche_nb_tour

		- perdu

		- affiche_difficulte

		- ecran_defaite

		- lancement_jeu

	J’ai travaillé en majorité sur l’interface graphique et les affichages qui y sont liés.

	J’ai également travaillé sur la fonction de reinitialisation du jeu pour recommencer une partie qui fais partie du main.

	J’ai également aider Louis pour la fonction lecture_tab et  la fonction joueur_a_bien_cliqué cependant il en a fais la majorité.

	J'ai fait la moitié de la fonction perdu.

	Fonction réalisée par Barraque:
	   
		- lecture_tab

		- ecran_noir

		- creation_fond

		- joueur_a_bien_clique

		- a_clique_en_dehors

		- renvoi_score

		- menu

		- perdu

		- reini_struct
	   
		- indique_clic

	Je me suis occuper principalement tu technique mais que l'algorythme de ces fonctions etaient de base pensé par nous deux.


Problème rencontrés :


	Valouz :

	J’ai eu peu de problème seul. La plupart des problèmes rencontrés étaient sur les fonctions où Louis et moi travaillons ensemble.

	J’en ai eu un pour faire afficher du score sur l’interface graphique qui variait en temps réel. L’utilisation d’un tableau de caractère pour stocker le texte et la variable à afficher m’as permis de résoudre le problème.

	J’ai également au un problème pour la fonction permettant de recommencer la partie. Ayant commencé à travailler seul dessus, j’ai réussi à faire fonctionner le jeu 2 fois de suite puis une fois perdu une seconde fois, plus aucune action n’était possible. Louis a donc travaillé par la suite dessus et à su résoudre le problème.

	Barraque:

	Je n' ai pas vraiment rencontrée de grande difficulté dans le projet, je dirais plutôt que j ai perdu du temps. La plus grosse perte de temps pour moi à été la compréhension de certaines fonctions plus precisement des fonction Time et de resoudre le bug de recommencement de la partie (niveau algorithme).
	J ai trouve que le projet était plutôt simple à faire mais le fait de rajouter de + en + de fonction l'a commencer a le rendre plus compliqué.

	Pour le Menu j'ai pris du temps a placer les figures symetrique et bien au millieu de l'ecran.


Bug connu :


	Nous avons rencontré un bug récurrent : il fallais cliquer 2 fois pour lancer une partie ou cliquer 2 fois pour sélectionner la couleur de la séquence cependant le fais de cliquer 2 fois décalais le compteur d’un cran ce qui rendais le clic d’apres forcement mauvais quoi qu’il arrive.

	Il a été résolu grâce à des printf() aux bons endroits. Le problème venais du fait que nous appellions la fonction dans le main puis une nouvelle fois dans une fonction qui était elle meme appelé dans le main.

	Le plus gros bug était dans la fonction main pour la condition de reinitialisation, ou le programme se bloquait "sans aucune raison" mais en modifiant l'algorithme, le bug a ete resolu.


Idée originale :


	Nous avons eu plusieurs idées nous semblant originale que nous n’avons pourtant pas pris le temps de réaliser.

		- Tout d’abord une fonction “techno“ qui, quand la difficulté maximale est choisis, fais clignoter le fond du jeu de toute les couleurs pour perturber le joueur pour mémoriser la séquence mais cependant il obtient plus de point si il réalise la bonne séquence. (Variante également imaginée : faire un damier comme vu en tp ou plusieurs couleurs clignote en même temps pour encore plus de difficulté)
		- Ensuite nous avons pensé à permettre au joueur de rentrer son nom dans l’interface graphique comme sur les bornes d’arcades de la bonne vieille époque. J’explique : la longueur max du nom aurait été de 3 caractères. Le joueur aurait cliqué sur des flèches horizontales pour choisir quel caractère il veut modifié et sur des flèches verticales pour modifier le caractère sélectionné de a à z ou de 0 à 9.
		- Rajouter un 5ème carré pour la difficulté
		- Trier le score par ordre de meilleur score afin de voir directement le meilleur joueur sur le terminale
		- Creer un menu "Extra"/"Reglage" oû l'on peut choisir la difficultée,afficher les crédit et les scores à l'écran
