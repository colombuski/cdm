#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ID 50
#define NB_LIGNES_FICHIERS_PLACES 12
#define MAX_NOM_CAT 15
#define MAX_NOM_EQUIPE 100
#define MAX_NOM_FICHIER 100
#define MAX_NOM_PERS 100
#define MAX_NOM_STADE 100
#define MAX_NOM_TRIBUNE 50
#define MAX_NB_RESERVATIONS 50
#define NB_MATCHS_HUITIEMES 8
#define NB_MATCHS_QUARTS 4
#define NB_MATCHS_DEMI 2
#define NB_MATCHS_POULES 6
#define TAILLE_DATE 15
#define TAILLE_HEURE 15


struct match {
	char e1[MAX_NOM_EQUIPE]   ;
	char e2[MAX_NOM_EQUIPE]   ;
	int buts_e1               ;
	int buts_e2               ;
	char stade[MAX_NOM_STADE] ;
	char date[TAILLE_DATE]    ;  
	char heure[TAILLE_HEURE]  ;
};

struct classement {
	char nomEquipe[MAX_NOM_EQUIPE];
	int butsMarques               ;
	int butsEncaisses             ;
	int points                    ;
};

struct place {
	char nomStade[MAX_NOM_STADE]     ;
	char nomTribune[MAX_NOM_TRIBUNE] ;
	char categorie[MAX_NOM_CAT]      ;
	int block                        ;
	int rang                         ;
	int place                        ;
	char date[TAILLE_DATE]           ;    
	char nom[MAX_NOM_PERS]           ;
	char prenom[MAX_NOM_PERS]        ;
	char heure[TAILLE_HEURE]         ;
	char e1[MAX_NOM_EQUIPE]          ;
	char e2[MAX_NOM_EQUIPE]          ;
};

//variables globales
char id[MAX_ID]                                ;
struct classement leClassement[3]              ;
struct match lesResultats[NB_MATCHS_HUITIEMES] ;
struct match lesHuitiemes[NB_MATCHS_HUITIEMES] ;
struct match lesQuarts[NB_MATCHS_QUARTS]       ;
struct match lesDemi[NB_MATCHS_DEMI]           ;
struct match laPetiteFinale                    ;
struct match laFinale                          ;
struct place unePlace                          ;

//fonctions et proc�dures
void affichage_billet(struct place unBillet)                                        ;
void affichage_classement()                			                                ;
void affichage_demi()                                                               ;
void affichage_finale()                                                             ;
void affichage_huitiemes()                                                          ;
void affichage_quarts()                                                             ;
void affichage_petite_finale()                                                      ;
void affichage_match_poule(char param_nom_file[MAX_NOM_FICHIER])                    ;
void affichage_res_manche(char p_manche[MAX_NOM_FICHIER])                           ;  
void bienvenu()                                                                     ;
void chargement_equipes_demi()                                                      ;
void chargement_equipes_finale()                                                    ;
void chargement_equipes_huitiemes()                                                 ;
void chargement_equipes_petite_finale()                                             ;
void chargement_equipes_quarts()                                                    ;
void classement_poule(char nomFichier[MAX_NOM_FICHIER]) 		                    ;
void compteur_cat(char p_fichier[], int *compteur1, int *compteur2, int *compteur3) ;
void conv_maj(char chaine[])                                                        ;
void creation_compte()                                                              ;
void espace_en_tiret(char ch[])                                                     ;
void flush_pour_linux()                                                             ;
void identification()                                                               ;
void incrementation_place()                                                         ;
void initialisation_unePlace()                                                      ;
void les_classements()                                                              ;
int log_id(int *num_log)                                                            ;
int log_mdp(int num_log)                                                            ;
int max_block()                                                                     ;
int max_rang()                                                                      ;
void menu_admin()                                                                   ;
void mes_reservations()                                                             ;
void quitter()                                                                      ;
void quitter_espace_client()                                                        ;
void recuperation_place()                                                           ;
int recuperation_place_nom_prenom_incrementation()                                  ;
void reservation_demi(int p_choix)                                                  ;
void reservation_finale(int p_choix)                                                ; 
void reservation_huitiemes(int p_choix)                                             ;
void reservation_petite_finale(int p_choix)                                         ;
void reservation_quarts(int p_choix)                                                ;
void saisie_demi()                                                                  ;
void saisie_finale()                                                                ;
void saisie_huitiemes()                                                             ;
void saisie_petite_finale()                                                         ;
void saisie_place()                                                                 ;
void saisie_quarts()                                                                ;
void sauvegarde_fichier_stade(struct place p_place)                                 ;
void sauvegarde_place(int p_choix)                                                  ;
void selection_et_affichage_matchs_poules()                                         ;
void selection_demi()                                                               ;
void selection_huitieme()                                                           ;
void selection_quart()                                                              ;
void stade_date_heure_demi()                                                        ;
void stade_date_heure_finale()                                                      ;
void stade_date_heure_huitiemes()                                                   ;
void stade_date_heure_petite_finale()                                               ;
void stade_date_heure_quarts()                                                      ;
void tiret_en_espace(char ch[])                                                     ;
void total_reservations()                                                           ;
void tri_classement()                      		                                	;
void tri_classement_buts()                                                          ;
int verif_null(char p_fichier[])                                                    ;



int main()
{
	int choix = -1  ;
	int choix2 = -1 ;
	
	bienvenu() ;
	
	while(choix != 0)
	{
		//premier menu de connexion/inscription
		printf("Veuiller choisir parmis les options suivantes :\n") ;
		printf("\n")                                                ;
		printf("-1- S'identifier\n")                                ;
		printf("-2- S'inscrire\n")                                  ;
		printf("-0- Quitter\n")                                     ;
		printf("\n")                                                ;
	
		scanf("%d", &choix) ;
		printf("\n")        ;
		
		switch(choix)
		{
			case 1 : printf("Veuillez saisir votre identifiant (Saisir 'q' pour quitter) : ") ;
					 scanf("%s", id) ;
					 
					 if(strcmp(id, "q") != 0)
					 {
					 	identification() ;
					 	
					 	if(strcmp(id, "q") != 0)
					 	{
					 		choix2 = -1 ;//initialisation de choix2 car si on se deconnecte et qu'on se connecte avec un autre compte choix2 = 0 donc pas de proposition du menu
					 		
					 		while(choix2 != 0)//Menu des fonctions accessibles aux utilisateurs
					 		{						 		
					 			printf("Veuiller choisir parmis les options suivantes :\n")     ;
					 			printf("-1- Afficher les resultats des matchs de poules\n")     ;
					 			printf("-2- Afficher les classements des poules\n")             ;
					 			
					 			/*On propose une fonction de r�servation pour chaque manche, on v�rifie avant si un fichier de r�sultats existe pour la manche.
								 Si c'est la cas, cela veur dire que la manche a �t� jou�e, on ne propose plus la r�servation mais l'affichage des r�sultats*/
					 			if(verif_null("RESULTATSHUITIEMES.txt"))
					 			{
					 				printf("-3- Reserver une place pour les huitiemes de finale\n") ;
								}
								else
								{
									printf("-3- Afficher les resultats des huitiemes de finale\n")  ;
								}
								if(verif_null("RESULTATSQUARTS.txt"))
								{
					 				printf("-4- Reserver une place pour les quarts de finale\n")    ;									
								}
								else
								{
									printf("-4- Afficher les resultats des quarts de finale\n")     ;
								}
								if(verif_null("RESULTATSDEMI.txt"))
								{
									printf("-5- Reserver une place pour les demi-finales\n")        ;
								}
								else
								{
									printf("-5- Afficher les resultats des demi-finales\n")         ;									
								}
								if(verif_null("RESULTATPETITEFINALE.txt"))
								{
									printf("-6- Reserver une place pour la petite finale\n")        ;
								}
								else
								{
									printf("-6- Afficher les resultats pour la petite finale\n")    ;									
								}
								if(verif_null("RESULTATFINALE.txt"))
								{
									printf("-7- Reserver une place pour la finale\n")               ;
								}
								else
								{
									printf("-7- Afficher les resultats pour la finale\n")           ;									
								}
								//propose � l'utilisateur d'acc�der � ses r�servations
					 			printf("-8- Acceder a mes reservations\n")                      ;
					 			
					 			
					 			//acc�s aux fonctions administrateur
					 			if(strcmp(id, "admin") == 0)
					 			{
					 				printf("-9- Acceder aux fonctions administrateur\n")        ;
								}
					 			
					 			printf("-0- Quitter l'espace client\n")                         ;
					 			printf("\n")                                                    ;
					 			
					 			scanf("%d", &choix2) ;
								printf("\n")	     ;
								
								switch(choix2)
								{
									case 1 : selection_et_affichage_matchs_poules() ;
										break ;
									case 2 : les_classements() ;
										break ;
									case 3 : if(verif_null("RESULTATSHUITIEMES.txt"))
											 {
											 	reservation_huitiemes(choix2) ; //permet de r�server des places
											 }
											 else
											 {
											 	affichage_res_manche("RESULTATSHUITIEMES.txt") ;//affiche les r�sultats des huiti�mes si renseign�s
											 }
										break ;	
									case 4 : if(verif_null("RESULTATSQUARTS.txt"))
											 {
											 	reservation_quarts(choix2) ;//permet de r�server des places											 	
											 }
											 else
											 {
											 	affichage_res_manche("RESULTATSQUARTS.txt") ;//affiche les r�sultats des quarts si renseign�s
											 }
										break ;
									case 5 : if(verif_null("RESULTATSDEMI.txt")) 
											 {
											 	reservation_demi(choix2) ;//permet de r�server des places
											 }
											 else
											 {
											 	affichage_res_manche("RESULTATSDEMI.txt") ;//affiche les r�sultats des demi si renseign�s
											 }
										break ;
									case 6 : if(verif_null("RESULTATPETITEFINALE.txt"))
											 {
												 reservation_petite_finale(choix2) ;//permet de r�server des places											 	
											 }
											 else
											 {
											 	affichage_res_manche("RESULTATPETITEFINALE.txt") ;//affiche les r�sultats de la petite finale si renseign�s
											 }
										break ;
									case 7 : if(verif_null("RESULTATFINALE.txt"))
											 {
												reservation_finale(choix2) ;//permet de r�server des places												 	
											 }
											 else
											 {
											 	affichage_res_manche("RESULTATFINALE.txt") ;//affiche les r�sultats de la finale si renseign�s
											 }
										break ;																				
									case 8 : mes_reservations() ;
										break ;
									case 9 : if(strcmp(id, "admin") == 0)
											 {
											 	menu_admin() ;//acc�s au menu des fonctions administrateur
											 }
											 else
											 {
											 	printf("Saisie erronee, veuillez recommencer\n") ;
											 	printf("\n")                                     ;
											 }
										break ;																			
									case 0 : quitter_espace_client() ;
										break ;
									default :	printf("Saisie erronee, veuillez recommencer\n") ;
												printf("\n")                                     ;
										break ;
								}
							}
						}
						else //sortie de l'identification => retour au premier menu
						 {
					 		printf("\n") ;
						 }						
					 }
					 else
					 {
					 	printf("\n") ;
					 }
				break;
			case 2 : creation_compte() ;
				break;
			case 0 : quitter() ;
				break;
		}
	
	}

	return 0 ; 
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------Identification---------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void identification()
{
	int ok      ;
	int cpt_log ;
	
	cpt_log = 0           ;
	ok = log_id(&cpt_log) ;	
	//boucle de saisie de l'id si premier essais rat�
	while(ok != 1)
	{
		printf("Veuillez saisir votre identifiant (Saisir 'q' pour quitter) : ") ;
		scanf("%s", id) ;
		
		if(strcmp(id, "q") != 0)
		{
			ok = log_id(&cpt_log) ;
		}
		else
		{
			ok = 1 ;
		}
	}
	if(strcmp(id, "q") != 0)
	{
		//saisie du mdp
		ok = log_mdp(cpt_log) ;
		
		//boucle de saisie du mdp si premier essais rat�
		while(ok != 1)
		{
			ok = log_mdp(cpt_log) ;
		}
		printf("\n")                  ;
		printf("Bienvenu %s !\n", id) ;
		printf("\n")                  ;
	}	

}



/*---------------------------------------------------------------------*/
/*----------------------V�rification de l'ID---------------------------*/
/*---------------------------------------------------------------------*/

int log_id(int *num_log)
{	
	FILE *f1 ;
	char id_fichier[30] ;
	*num_log = 0        ;

	//Fichier de stockage des ID
	f1 = fopen("Id_V1.txt", "r") ;
	strcpy(id_fichier, "init")   ;//initialisation de la variable de comparaison
		
	//Parcours du fichier pour trouver un id correspondant 
	while((! feof(f1))&&(strcmp(id, id_fichier) != 0))
	{
		fscanf(f1, "%s", id_fichier)  ; //recup�ration de l'ID de chaque ligne
		*num_log = *num_log+1         ; //compte les lignes
	}
	if (strcmp(id_fichier, id) != 0)
	{
		printf("\n")                                                                                                   ;
		printf("Identifiant inconnu, veuillez reessayer.\n")                                                           ;
		printf("--------------------------------------------------------------------------------------------------\n") ;
		printf("\n")                                                                                                   ;
		return 0                                                                                                       ;
	}
	else
	{
		return 1 ;
	}
	
	fclose(f1) ;
}



/*---------------------------------------------------------------------*/
/*-------------------Verification du mot de passe----------------------*/
/*---------------------------------------------------------------------*/

int log_mdp(int num_log)
{
	FILE *f1     ;
	char mdp_fichier[30], mdp[30] ;
	int i        ;
	
	//Ouverture du fichier des mdp
	f1 = fopen("Mdp_V1.txt", "r") ;
			
	printf("Veuillez saisir votre mot de passe :") ;
	scanf("%s", mdp)                               ;
			
	//cherche le mdp au m�me num�ro de ligne que l'id
	for (i=0 ; i<num_log ; i++)
	{
		fscanf(f1, "%s", mdp_fichier) ;
	}
			
	if(strcmp(mdp, mdp_fichier) != 0)
	{
		printf("\n")                                  ;
		printf("Mdp errone, veuillez recommencer.\n") ;
		printf("--------------------------------------------------------------------------------------------------\n") ;
		printf("\n")                                  ;
		
		return 0 ;
	}
	else
	{
		return 1 ;
	}
	
	fclose(f1) ;
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------Cr�ation compte---------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void creation_compte()
{
	char new_id[30], new_id_verif[30], id_fichier[30] ;
	char new_mdp[30], new_mdp_verif[30] ;
	FILE * f1 ;
	
	printf("Veuillez saisir un nouvel identifiant (30 caracteres max) : ") ;
	scanf("%s", new_id)                                                    ;
	
	//V�rifie si l'id existe d�j�
	f1 = fopen("Id_V1.txt", "r") ;
		
	//Parcours du fichier pour trouver un id correspondant 
	while((! feof(f1))&&(strcmp(new_id, id_fichier) != 0))
	{
		fscanf(f1, "%s", id_fichier) ; //recup�ration de l'ID de chaque ligne
	}
	
	if (strcmp(id_fichier, new_id) == 0)
	{
		printf("Identifiant deja utilise, veuillez en saisir un nouveau\n") ;
		creation_compte()                                                   ; //rappel de la fonction pour ressaisir un nouvel id
	}
	
	else
	{
		printf("Veuillez saisir votre identifiant a nouveau : ") ;
		scanf("%s", new_id_verif)                                ;
	
		//On v�rifie si l'utilisateur a bien saisi l'ID qu'il voulait
		while(strcmp(new_id, new_id_verif) != 0)
		{
			printf("Saisie erronee, veuillez recommencer\n") ;
			printf("--------------------------------------------------------------------------------------------------\n") ;
			printf("\n") ;	
			
			printf("Veuillez saisir un identifiant (30 caracteres max) : ") ;
			scanf("%s", new_id)                                             ;
		
			printf("Veuillez saisir votre identifiant � nouveau : ") ;
			scanf("%s", new_id_verif)                                ;
		}
		
		f1 = fopen("Id_V1.txt", "a") ; //ajoute l'ID � en derni�re position sur le fichier des ID
		fprintf(f1, "%s\n", new_id)  ;
		fclose(f1)                   ;
		
		
		printf("Veuillez saisir un mot de passe (30 caracteres max) : ") ;
		scanf("%s", new_mdp)                                             ;
		
		printf("Veuillez saisir votre mot de passe a nouveau : ") ;
		scanf("%s", new_mdp_verif)                                ;
		
		//On v�rifie si l'utilisateur a bien saisi le mot de passe qu'il voulait
		while(strcmp(new_mdp, new_mdp_verif) != 0)
		{
			printf("Saisie erronee, veuillez recommencer\n") ;
			printf("--------------------------------------------------------------------------------------------------\n") ;
			printf("\n") ;	
			
			printf("Veuillez saisir un mot de passe (30 caracteres max) : ") ;
			scanf("%s", new_mdp)                                             ;
		
			printf("Veuillez saisir votre mot de passe � nouveau : ") ;
			scanf("%s", new_mdp_verif)                                ;
			
		}	
		
		f1 = fopen("Mdp_V1.txt", "a")  ; //ajoute le mdp � en derni�re position sur le fichier des mdp
		fprintf(f1, "%s\n", new_mdp) ;
		fclose(f1)                   ;	
		
		printf("\n") ;
		printf("Identifiants enregistres !\n")                                             ;
		printf("--------------------------------------------------------------------------------------------------\n") ;
		printf("\n") ;
	}
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------S�lection et affichage des matchs de poules-----------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void selection_et_affichage_matchs_poules()
{
	char lettre_poule ;
	
	lettre_poule = 'z' ;
	
	while(lettre_poule != 'Q')
	{
		flush_pour_linux(stdin) ;
		printf("-------------------------------------------------------------------------------------------------------------------\n") ;
		printf("Veuillez entrer la lettre de la poule a afficher : A, B, C, D, E, F, G ou H ? (Q pour quitter) : ") ;
		scanf("%c", &lettre_poule)                                                                                  ;
		printf("\n")                                                                                                ;
		printf("\n")                                                                                                ;
		lettre_poule = toupper(lettre_poule)                                                                        ;
	
		switch(lettre_poule)//menu de s�lection des poules � afficher
		{
			case 'A' : printf("POULE A") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_A.txt") ;
				break ;
			case 'B' : printf("POULE B") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_B.txt") ;
				break ;  
			case 'C' : printf("POULE C") ;
					   printf("\n")      ;
					   printf("\n")      ;
			           affichage_match_poule("Poule_C.txt") ;
				break ;  
			case 'D' : printf("POULE D") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_D.txt") ;
				break ;  
			case 'E' : printf("POULE E") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_E.txt") ;
				break ;  
			case 'F' : printf("POULE F") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_F.txt") ;
				break ;  
			case 'G' : printf("POULE G") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_G.txt") ;
				break ;    
			case 'H' : printf("POULE H") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   affichage_match_poule("Poule_H.txt") ;
				break ;
			case 'Q' : printf("\n")                              ;
					   printf("Retour au menu utilisateur...\n") ;
					   printf("-------------------------------------------------------------------------------------------------------------------\n") ;
					   printf("\n")                              ;  
				break ;
			default : printf("Poule non reconnue, veuillez saisir une lettre entre A et H\n") ;
				break ;		
		}
	}
}



/*---------------------------------------------------------------------*/
/*---Boucle d'affichage des matchs � partir du fichier des r�sultats---*/
/*---------------------------------------------------------------------*/
void affichage_match_poule(char nomFichier[MAX_NOM_FICHIER])
{
	FILE * f1            ;
	int i                ;
	struct match unMatch ;
	
	f1 = fopen(nomFichier, "r") ;
	
	for(i=0 ; i<NB_MATCHS_POULES ; i++)
	{
		fflush(stdin)                                                                         ;
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
		
		switch (i)
		{
			case 0 : printf("1e journee \n") ;
					 printf("-------------------------------------------------------\n") ;
					 printf("\n") ;
				break ;
			case 2 : printf("2e journee\n") ;
					 printf("-------------------------------------------------------\n") ;
					 printf("\n") ;			
				break ;
			case 4 : printf("3e journee\n") ;
					 printf("-------------------------------------------------------\n") ;
					 printf("\n") ;			
				break ;				
		}

		tiret_en_espace(unMatch.e1)  ;
        tiret_en_espace(unMatch.e2)  ;
		printf("%25s %2d %2d %-25s\n", unMatch.e1, unMatch.buts_e1, unMatch.buts_e2, unMatch.e2) ;
		printf("\n")                                                                             ;
	}
	fclose(f1) ;
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------Affiche les classements--------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void les_classements()
{
	char lettre_poule ;
	
	lettre_poule = 'z' ;
	
	while(lettre_poule != 'Q')
	{
		flush_pour_linux(stdin) ;
		printf("-------------------------------------------------------------------------------------------------------------------\n") ;
		printf("Veuillez entrer la lettre de la poule a afficher : A, B, C, D, E, F, G ou H ? (Q pour quitter) : ") ;
		scanf("%c", &lettre_poule)                                                                                  ;
		printf("\n")                                                                                                ;
		printf("\n")                                                                                                ;
		lettre_poule = toupper(lettre_poule)                                                                        ;
	
		switch(lettre_poule)//menu de s�lection des poules � afficher
		{
			case 'A' : printf("POULE A") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_A.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;
				break ;
			case 'B' : printf("POULE B") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_B.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;  
			case 'C' : printf("POULE C") ;
					   printf("\n")      ;
					   printf("\n")      ;
			           classement_poule("Poule_C.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;			           
				break ;  
			case 'D' : printf("POULE D") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_D.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;  
			case 'E' : printf("POULE E") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_E.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;  
			case 'F' : printf("POULE F") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_F.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;  
			case 'G' : printf("POULE G") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_G.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;    
			case 'H' : printf("POULE H") ;
					   printf("\n")      ;
					   printf("\n")      ;
					   classement_poule("Poule_H.txt") ;
					   tri_classement()                ;
					   tri_classement_buts()           ;
					   affichage_classement()          ;					   
				break ;
			case 'Q' : printf("\n")                              ;
					   printf("Retour au menu utilisateur...\n") ;
					   printf("-------------------------------------------------------------------------------------------------------------------\n") ;
					   printf("\n")                              ;  
				break ;
			default : printf("Poule non reconnue, veuillez saisir une lettre entre A et H\n") ;
				break ;		
		}
	}
}


/*---------------------------------------------------------------------*/
/*---------       vide le buffer à la place de fflush           -------*/
/*---------------------------------------------------------------------*/
void flush_pour_linux()
{
    int i ; 
    while ((i = getchar()) != '\n' && i != EOF) ; 
}



/*---------------------------------------------------------------------*/
/*---------Fait un classement � partir des r�sultats d'une poule-------*/
/*---------------------------------------------------------------------*/
void classement_poule(char nomFichier[MAX_NOM_FICHIER])
{
	FILE *f1                          ;
	int i, cpt                        ;
	struct match unMatch              ;
	struct classement uneEquipe       ;
	
	f1 = fopen(nomFichier, "r") ;
	
	for(i=0 ; i<NB_MATCHS_POULES ; i++)
	{
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
		
		switch(i)
		{
			case 0 : strcpy(uneEquipe.nomEquipe,unMatch.e1)    ; //Initialisation 1e equipe du classement
					 uneEquipe.butsMarques = unMatch.buts_e1   ;
					 uneEquipe.butsEncaisses = unMatch.buts_e2 ;
					 leClassement[0] = uneEquipe               ;
					 
					 strcpy(uneEquipe.nomEquipe,unMatch.e2)    ;//Initialisation 2e equipe du classement
					 uneEquipe.butsMarques = unMatch.buts_e2   ;
					 uneEquipe.butsEncaisses = unMatch.buts_e1 ;
					 leClassement[1] = uneEquipe               ;
					 
					 if(unMatch.buts_e1 > unMatch.buts_e2)//On d�termine le gagnant pour attibuer les points
					 {
					 	leClassement[0].points = 3 ;
					 	leClassement[1].points = 0 ;
					 }
					 else if (unMatch.buts_e1 < unMatch.buts_e2)
					 {
					 	leClassement[1].points = 3 ;
					 	leClassement[0].points = 0 ;
					 }
					 else
					 {
					 	leClassement[0].points = 1 ;
					 	leClassement[1].points = 1 ;
					 }
				break ;
			case 1 : strcpy(uneEquipe.nomEquipe,unMatch.e1)    ; //Initialisation 1e equipe du classement
					 uneEquipe.butsMarques = unMatch.buts_e1   ;
					 uneEquipe.butsEncaisses = unMatch.buts_e2 ;
					 leClassement[2] = uneEquipe               ;
					 
					 strcpy(uneEquipe.nomEquipe,unMatch.e2)    ;//Initialisation 2e equipe du classement
					 uneEquipe.butsMarques = unMatch.buts_e2   ;
					 uneEquipe.butsEncaisses = unMatch.buts_e1 ;
					 leClassement[3] = uneEquipe               ;
					 
					 if(unMatch.buts_e1 > unMatch.buts_e2)//On d�termine le gagnant pour attibuer les points
					 {
					 	leClassement[2].points = 3 ;
					 	leClassement[3].points = 0 ;
					 }
					 else if (unMatch.buts_e1 < unMatch.buts_e2)
					 {
					 	leClassement[3].points = 3 ;
					 	leClassement[2].points = 0 ;
					 }
					 else
					 {
					 	leClassement[2].points = 1 ;
					 	leClassement[3].points = 1 ;
					 }
				break ;	
			default : for(cpt=0 ; cpt<=3 ; cpt++) //On cherche les �quipes du match par leur noms et on ajoute les donn�es relatives au match
					  {
					  	if(strcmp(unMatch.e1, leClassement[cpt].nomEquipe) == 0) //comparaison nom equipe 1
					  	{
					  		leClassement[cpt].butsMarques = leClassement[cpt].butsMarques + unMatch.buts_e1     ;
					  		leClassement[cpt].butsEncaisses = leClassement[cpt].butsEncaisses + unMatch.buts_e2 ;
					  		
					  		if(unMatch.buts_e1 > unMatch.buts_e2)//On d�termine le gagnant pour attibuer les points
						    {
					 			leClassement[cpt].points = leClassement[cpt].points + 3 ;
					 		}
					 		else if (unMatch.buts_e1 == unMatch.buts_e2)
					 		{
					 			leClassement[cpt].points = leClassement[cpt].points + 1 ;
							}
					  	}
						else if(strcmp(unMatch.e2, leClassement[cpt].nomEquipe) == 0) //comparaison nom equipe 2
					  	{
					  		leClassement[cpt].butsMarques = leClassement[cpt].butsMarques + unMatch.buts_e2     ;
					  		leClassement[cpt].butsEncaisses = leClassement[cpt].butsEncaisses + unMatch.buts_e1 ;
					  		
					  		if(unMatch.buts_e2 > unMatch.buts_e1)//On d�termine le gagnant pour attibuer les points
						    {
					 			leClassement[cpt].points = leClassement[cpt].points + 3 ;
					 		}
					 		else if (unMatch.buts_e2 == unMatch.buts_e1)
					 		{
					 			leClassement[cpt].points = leClassement[cpt].points + 1 ;
							}
					  	}			
					  }
		}
	}
}



/*---------------------------------------------------------------------*/
/*---------------------Tri un classement par les points----------------*/
/*---------------------------------------------------------------------*/
void tri_classement()
{
	int i, cpt, diff_buts_i, diff_buts_j ;
	struct classement uneEquipe          ;
	
	for(i=0 ; i<3 ; i++) //on ne va pas jusqu'a 3 car on va d�border hors du tableau lors du test leClassement[i+1]
	{
		if(leClassement[i].points < leClassement[i+1].points) //on interverti les �quipes si l'equipe � l'indice i � moins de poitns que l'equipe � l'indice i+1
		{
			uneEquipe = leClassement[i]         ;
			leClassement[i] = leClassement[i+1] ;
			leClassement[i+1] = uneEquipe       ;
			
			if(i>=2)
			{
				for(cpt=i ; i>0 ; i--) //on v�rifie si les equipes aux indices inf�rieurs n'ont pas un nombre de point inf�rieur � l'equipe qu'on vient de d�caler
				{
					if(leClassement[i].points > leClassement[i-1].points) //on interverti les �quipes si l'equipe � l'indice i � moins de points que l'equipe � l'indice i+1
					{
						uneEquipe = leClassement[i-1]       ;
						leClassement[i-1] = leClassement[i] ;
						leClassement[i] = uneEquipe         ;
					}
				}
			}
		}
	}
}



/*---------------------------------------------------------------------*/
/*---------------------Tri un classement par les buts------------------*/
/*---------------------------------------------------------------------*/
void tri_classement_buts()
{
	int i, diff_buts_i, diff_buts_j ;
	struct classement uneEquipe     ;
	
	for(i=0 ; i<3 ; i++ ) //on ne va pas jusqu'a 3 car on va d�border hors du tableau lors du test leClassement[i+1]
	{
		diff_buts_i = leClassement[i].butsMarques - leClassement[i].butsEncaisses     ;
		diff_buts_j = leClassement[i+1].butsMarques - leClassement[i+1].butsEncaisses ;
		
		if((diff_buts_i < diff_buts_j)&&(leClassement[i].points == leClassement[i+1].points)) //on v�rifie la diff de buts
		{
			uneEquipe = leClassement[i]         ;
			leClassement[i] = leClassement[i+1] ;
			leClassement[i+1] = uneEquipe       ;
		}
		else if ((diff_buts_i == diff_buts_j)&&(leClassement[i].butsMarques < leClassement[i+1].butsMarques)&&(leClassement[i].points == leClassement[i+1].points)) //si meme diff�rence de buts on v�rifie le nombre de buts marqu�s
		{
			uneEquipe = leClassement[i]         ;
			leClassement[i] = leClassement[i+1] ;
			leClassement[i+1] = uneEquipe       ;
		}
	}
}



/*---------------------------------------------------------------------*/
/*------------------------Affichage Classement-------------------------*/
/*---------------------------------------------------------------------*/
void affichage_classement()
{
	struct classement uneEquipe ;
	int i                       ;
	
	printf(" ---------------------------------------------------------------\n")                    ;
	printf("| %-20s | %12s | %14s | %6s |\n", "EQUIPE", "BUTS MARQUES", "BUTS ENCAISSES", "POINTS") ;
	printf(" ---------------------------------------------------------------\n")                    ;
	
	for(i=0 ; i<=3 ; i++)
	{
		uneEquipe = leClassement[i] ;
		tiret_en_espace(uneEquipe.nomEquipe)  ;
		
		printf("| %-20s | %12d | %14d | %6d |\n", uneEquipe.nomEquipe, uneEquipe.butsMarques, uneEquipe.butsEncaisses, uneEquipe.points) ;
		printf(" ---------------------------------------------------------------\n")                                                     ;
	}
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Reservation huiti�mes de finales----------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void reservation_huitiemes(int p_choix)
{	
	int ok ;
	
	initialisation_unePlace()                           ;
	chargement_equipes_huitiemes()                      ;
	stade_date_heure_huitiemes()                        ;		 									 
	affichage_huitiemes()                               ;
	selection_huitieme()                                ;
	
	if(strcmp(unePlace.nomStade, "init") != 0)//Si l'utilisateur n'a pas s�lectionn� 0 -> quitter la fonction
	{
		ok = recuperation_place_nom_prenom_incrementation() ;
	
		//Si le stock n'est pas complet pour cette type de place, et que l'utilisateur � valid� la r�servation : on sauvegarde la r�servation
		if((unePlace.place != -1)&&(ok == 1))
		{
			sauvegarde_place(p_choix)                      ;		
		}
	}    
}



/*----------------------------------------------------------------------------------*/
/*Initialisation de la variable globale unePlace avant de proc�der � une r�servation*/
/*----------------------------------------------------------------------------------*/
void initialisation_unePlace()
{
	unePlace.block = 0 ;
	unePlace.place = 0 ;
	unePlace.rang = 0  ;
	
	strcpy(unePlace.categorie, "init")  ;   
	strcpy(unePlace.date, "init")       ;
	strcpy(unePlace.e1, "init")         ; 
	strcpy(unePlace.e2, "init")         ;  	
	strcpy(unePlace.heure, "init")      ;
	strcpy(unePlace.nom, "init")        ;
	strcpy(unePlace.nomStade, "init")   ;
	strcpy(unePlace.nomTribune, "init") ;
	strcpy(unePlace.prenom, "init")     ;  
}



/*---------------------------------------------------------------------*/
/*--Charge les �quipes qualifi�es pour les huiti�mes de finale---*/
/*---------------------------------------------------------------------*/
void chargement_equipes_huitiemes()
{
	classement_poule("Poule_A.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[1].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[4].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_B.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[4].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[1].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_C.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[0].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[5].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_D.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[5].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[0].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_E.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[2].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[6].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_F.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[6].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[2].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_G.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[3].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[7].e2,leClassement[1].nomEquipe) ;
	
	classement_poule("Poule_H.txt")                      ;
	tri_classement()                                     ;
	tri_classement_buts()                                ;
	strcpy(lesHuitiemes[7].e1,leClassement[0].nomEquipe) ;
	strcpy(lesHuitiemes[3].e2,leClassement[1].nomEquipe) ;
}



/*---------------------------------------------------------------------*/
/*------Attribue les stades et les dates aux huiti�mes de finales------*/
/*---------------------------------------------------------------------*/
void stade_date_heure_huitiemes()
{
	strcpy(lesHuitiemes[0].stade, "VELODROME") ;
	strcpy(lesHuitiemes[0].date, "01-03-2021")   ;
	strcpy(lesHuitiemes[0].heure, "18h00")     ;
	
	strcpy(lesHuitiemes[1].stade, "STADE-DE-FRANCE") ;
	strcpy(lesHuitiemes[1].date, "01-03-2021")         ;
	strcpy(lesHuitiemes[1].heure, "21h00")           ;
	
	strcpy(lesHuitiemes[2].stade, "BEAUJOIRE") ;
	strcpy(lesHuitiemes[2].date, "02-03-2021")   ;
	strcpy(lesHuitiemes[2].heure, "18h00")     ;
	
	strcpy(lesHuitiemes[3].stade, "VELODROME") ;
	strcpy(lesHuitiemes[3].date, "02-03-2021")   ;
	strcpy(lesHuitiemes[3].heure, "21h00")     ;
	
	strcpy(lesHuitiemes[4].stade, "STADE-DE-FRANCE") ;
	strcpy(lesHuitiemes[4].date, "03-03-2021")         ;
	strcpy(lesHuitiemes[4].heure, "18h00")           ;
	
	strcpy(lesHuitiemes[5].stade, "BEAUJOIRE") ;
	strcpy(lesHuitiemes[5].date, "03-03-2021")   ;
	strcpy(lesHuitiemes[5].heure, "21h00")     ;
	
	strcpy(lesHuitiemes[6].stade, "VELODROME") ;
	strcpy(lesHuitiemes[6].date, "04-03-2021")   ;
	strcpy(lesHuitiemes[6].heure, "18h00")     ;
	
	strcpy(lesHuitiemes[7].stade, "STADE-DE-FRANCE") ;
	strcpy(lesHuitiemes[7].date, "04-03-2021")         ;
	strcpy(lesHuitiemes[7].heure, "21h00")           ;
}



/*---------------------------------------------------------------------*/
/*---------------Affichage des matchs des huiti�mes de finales---------*/
/*---------------------------------------------------------------------*/
void affichage_huitiemes()
{
	int i                ;
	struct match unMatch ;
	
	printf("------------------------------------------------------------------------------------------------------\n")            ;
	printf("%60s\n", "HUITIEMES DE FINALE")                                                                                       ;
	printf("------------------------------------------------------------------------------------------------------\n")            ;
	printf("\n")                                                                                                                  ;
	printf(" %-8s | %-41s | %-12s | %-20s | %7s\n", "NUMERO", "MATCH", "DATE", "STADE", "HEURE")                                  ;
	printf("------------------------------------------------------------------------------------------------------\n")            ;
	
	for(i=0 ; i<NB_MATCHS_HUITIEMES ; i++)
	{
		unMatch = lesHuitiemes[i] ;
		tiret_en_espace(unMatch.e1)     ; 
        tiret_en_espace(unMatch.e2)     ;
        tiret_en_espace(unMatch.date)   ;
        tiret_en_espace(unMatch.stade)  ; 
		
		printf("%8d   %20s %-20s   %-12s   %-20s   %7s\n", i+1, unMatch.e1, unMatch.e2, unMatch.date, unMatch.stade, unMatch.heure) ;
	}
	printf("\n") ;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/*Transmet les informations du huiti�me de finale vers la place en cours de r�servation selon le choix de l'utilisateur*/
/*---------------------------------------------------------------------------------------------------------------------*/
void selection_huitieme()
{
	int numMatch ;
	
	printf("Veuillez saisir le numero du match que vous souhaitez reserver (saisir 0 pour quitter) : ") ;
	scanf("%d", &numMatch)                                                                              ;
	
	if(numMatch != 0)
	{
		numMatch-- ;//numMatch doit correspondre aux indices de lesHuitiemes donc de 0 a 7
	
		//On transfert les informations du huiti�me s�lectionn� � la place de l'utilisateur : stade, date et heure. Le stade et la date vont permettre de retrouver le fichier dans lequel le stock de place est g�r� pour ce match.
		switch(numMatch)
		{
			case 0 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;
				break ;
			case 1 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 2 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 3 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 4 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 5 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 6 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;
			case 7 : strcpy(unePlace.nomStade, lesHuitiemes[numMatch].stade) ;
					 strcpy(unePlace.date, lesHuitiemes[numMatch].date)      ;
					 strcpy(unePlace.heure, lesHuitiemes[numMatch].heure)    ;
					 strcpy(unePlace.e1, lesHuitiemes[numMatch].e1)          ;
					 strcpy(unePlace.e2, lesHuitiemes[numMatch].e2)          ;				 
				break ;																				
		}
	}
}



/*--------------------------------------------------------------------------------------*/
/*Recuperation de la place dispo selon les choix de l'utilisateur + saisie nom et prenom*/
/*--------------------------------------------------------------------------------------*/
int recuperation_place_nom_prenom_incrementation()
{
	FILE *f1                 ;
	char confirmation[2]     ;
	
	
	//Saisie utilisateur de la tribune et cat�gorie
	saisie_place() ;
	
	//R�cup�ration de la premi�re place disponible pour cette tribune et cette cat�gorie
	recuperation_place() ;
	
	if(unePlace.place == -1)
	{
		printf("Plus de place disponibles pour ce match, cette tribune et cette cat�gorie\n") ;
		printf("\n")                                                                          ;
	}
	else
	{
		//demande de confirmation pour la r�servation
		printf("La place %d rang %d block %d de la tribune %s est disponible pour la categorie %s\n", unePlace.place, unePlace.rang, unePlace.block, unePlace.nomTribune, unePlace.categorie) ;
		printf("\n")                                                                                                                                                                          ;
		printf("Veuillez saisir OK pour confirmer la reservation (A pour abandonner) :")              ;
		scanf("%s", confirmation)                                                                     ;
		conv_maj(confirmation)                                                                        ;
		
		if(strcmp(confirmation, "OK") == 0)
		{	
			//incr�mentation de la premi�re place disponible pour la prochaine reservation
			incrementation_place() ;
			
			//saisie de l'identit� de la personne
			printf("Veuillez saisir le nom de la personne qui assistera au match (veuillez utiliser des tirets si le nom est compose) : ")        ;
			scanf("%s", unePlace.nom)                                                                                                            ;
			printf("Veuillez saisir le prenom de la personne qui assistera au match (veuillez utiliser des tirets si le prenom est compose) : ") ;
			scanf("%s", unePlace.prenom)                                                                                                         ;
			printf("\n")                                                                                                                         ;
            printf("La place a bien été réservée ! \n")                                                                                          ;
            printf("\n")                                                                                                                         ;
			conv_maj(unePlace.nom)                                                                                                               ;
			conv_maj(unePlace.prenom)                                                                                                            ;
			
			return 1 ;
		}
		else
		{
			return 0 ;
		}
	}
}



/*---------------------------------------------------------------------*/
/*-----------------------------Saisie de la tribune--------------------*/
/*---------------------------------------------------------------------*/
void saisie_place()
{
	if(strcmp(unePlace.nomStade, "BEAUJOIRE") !=0)
	{
		while((strcmp(unePlace.nomTribune, "NORD") != 0)&&(strcmp(unePlace.nomTribune, "SUD") != 0)&&(strcmp(unePlace.nomTribune, "EST") != 0)&&(strcmp(unePlace.nomTribune, "OUEST") != 0))
		{
			printf("Veuillez saisir la tribune dans laquelle vous souhaitez reserver votre place : (NORD, SUD, EST ou OUEST) : ") ;
			scanf("%s", unePlace.nomTribune)                                                                                   ;
			conv_maj(unePlace.nomTribune)                                                                                      ;
		}		
	}
	else
	{
		while((strcmp(unePlace.nomTribune, "OCEANE") != 0)&&(strcmp(unePlace.nomTribune, "JULES-VERNE") != 0)&&(strcmp(unePlace.nomTribune, "ERDRE") != 0)&&(strcmp(unePlace.nomTribune, "LOIRE") != 0))
		{
			printf("Veuillez saisir la tribune dans laquelle vous souhaitez reserver votre place : (OCEANE, JULES-VERNE, ERDRE ou LOIRE) : ") ;
			scanf("%s", unePlace.nomTribune)                                                                                               ;
			conv_maj(unePlace.nomTribune)                                                                                                  ;
		}	
	}	

	if((strcmp(unePlace.nomTribune, "ERDRE") == 0)||(strcmp(unePlace.nomTribune, "LOIRE") == 0))
	{
		printf("\n")                                                                                        ;
		printf("Cette tribune n'a que des places en categories BRONZE\n")                                   ;
		strcpy(unePlace.categorie, "BRONZE")                                                                ;	
	}
	else
	{
		while((strcmp(unePlace.categorie, "OR") != 0)&&(strcmp(unePlace.categorie, "ARGENT") != 0)&&(strcmp(unePlace.categorie, "BRONZE") != 0))
		{
			printf("\n")                                                                                        ;
			printf("Veuillez selectionner la categorie dans laquelle vous souhaitez reserver votre place : \n") ;
			printf("\n")                                                                                        ;
			printf("OR : PROCHE DE LA PELOUSE\n")                                                               ;
			printf("ARGENT : AU MILIEU\n")                                                                      ;
			printf("BRONZE : EN HAUTEUR\n")                                                                     ;
			printf("Categorie : ")                                                                              ;
			scanf("%s", unePlace.categorie) ;
			conv_maj(unePlace.categorie)    ;
		}
	}
}



/*--------------------------------------------------------------------------*/
/*R�cup�ration de la prochaine place dispo pour une tribune et une cat�gorie*/
/*--------------------------------------------------------------------------*/
void recuperation_place()
{
	FILE *f1 ;
	char tribuneFichier[MAX_NOM_TRIBUNE] ;
	char categorieFichier[MAX_NOM_CAT]   ;
	char nomFichier[MAX_NOM_FICHIER]     ;
	
	//concatenation nom stade + date pour avoir le nom du fichier de sauvegarde pour les places de ce match
	strcpy(nomFichier, unePlace.nomStade) ;
	strcat(nomFichier, unePlace.date)     ;
	strcat(nomFichier, ".txt")            ;
	
	f1 = fopen(nomFichier, "r") ;
	
	while((strcmp(unePlace.nomTribune,tribuneFichier) != 0)||(strcmp(unePlace.categorie,categorieFichier) != 0))//r�cup�re la place disponible pour une cat�gorie d'un tribune
	{
		fscanf(f1, "%s %s %d %d %d", tribuneFichier, categorieFichier, &unePlace.block, &unePlace.rang, &unePlace.place) ;
	}
	fclose(f1) ;	
}



/*------------------------------------------------------------------------*/
/*Incr�mentation de la prochaine place dispo place apr�s r�servation*/
/*------------------------------------------------------------------------*/
void incrementation_place()
{
	int maxRang, maxBlock            ;
	struct place prochainePlaceLibre ;
	
	prochainePlaceLibre = unePlace ;
	
	maxRang = max_rang()   ;
	maxBlock = max_block() ;

	if(prochainePlaceLibre.place<100) //si le num de place est compris entre 1 et 100, on incr�mente seulement le num�ro de place car toutes les rang�es de tous les stades font 100 places
	{
		prochainePlaceLibre.place++ ;
	}
	else if(prochainePlaceLibre.rang<maxRang)//si le num de place=100, on passe � la premiere place de la rang�e suivante
	{
		prochainePlaceLibre.place = 1 ;
		prochainePlaceLibre.rang++    ;
	}
	else if(prochainePlaceLibre.block<maxBlock)//si le num de rang�e = maxRang, on passe � la premi�re place de la premi�re rang�e du block suivant
	{
		prochainePlaceLibre.place = 1 ;
		prochainePlaceLibre.rang = 1  ;
		prochainePlaceLibre.block++   ;
	}
	else if(prochainePlaceLibre.block == maxBlock)//Si toutes les places sont r�serv�es pour une tribune, on met un indicateur (-1) pour signifier qu'il n'y a plus de places disponibles
	{
		prochainePlaceLibre.place = -1 ;
	}

	sauvegarde_fichier_stade(prochainePlaceLibre)  ;
}



/*---------------------------------------------------------------------*/
/*-----Sauvegarde de la prochaine place disponible dans le fichier-----*/
/*---------------------------------------------------------------------*/
void sauvegarde_fichier_stade(struct place p_place)
{
	struct place tabPlace[NB_LIGNES_FICHIERS_PLACES] ;//tableau o� on va extraire les donn�es et les modifier
	struct place unePlace                            ;
	FILE *f1                                         ;
	char nomFichier[MAX_NOM_FICHIER]                 ;
	int i, cpt, check                                ;
	
	//concatenation nom stade + date pour avoir le nom du fichier de sauvegarde pour les places de ce match
	strcpy(nomFichier, p_place.nomStade) ;
	strcat(nomFichier, p_place.date)     ;
	strcat(nomFichier, ".txt")           ;
	
	f1 = fopen(nomFichier, "r") ;
	i = 0                       ;
	
	//extraction des donn�es du fichier de places dans un tableau
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %d %d %d", unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if(check != EOF)
		{
			tabPlace[i++] = unePlace ; 
		}
	}
	
	fclose(f1) ;
	
	//modification de la ligne correspondant � la place
	for(cpt=0 ; cpt<i ; cpt++)
	{
		unePlace = tabPlace[cpt] ;
		
		if((strcmp(unePlace.nomTribune, p_place.nomTribune) == 0)&&(strcmp(unePlace.categorie, p_place.categorie) == 0))
		{
			tabPlace[cpt] = p_place ;
		}
	}
	
	f1 = fopen(nomFichier, "w") ;
	
	for(cpt=0 ; cpt<i ; cpt++)
	{
		unePlace = tabPlace[cpt]                                                                                                ;
		fprintf(f1, "%s %s %d %d %d\n", unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
	}
	
	fclose(f1) ;
}



/*-----------------------------------------------------------------------------*/
/*Sauvegarde de la place r�serv�e dans le fichier des r�servation des huiti�mes*/
/*-----------------------------------------------------------------------------*/
void sauvegarde_place(int p_choix)
{
	FILE *f1 ;
	
	//sauvegarde la place dans un fichier correspondant au type de match (huiti�mes, quarts, etc) en fonction du choix de fonction de l'utilisateur (r�server un huiti�me -> sauvegarde fichier huiti�mes)
	switch(p_choix)
	{
		case 3 : f1 = fopen("RESERVATIONSHUITIEMES.txt", "a") ;
				 fprintf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d\n", id, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
				 fclose(f1) ;
			break ;
		case 4 : f1 = fopen("RESERVATIONSQUARTS.txt", "a") ;
				 fprintf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d\n", id, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
				 fclose(f1) ;
			break ;
		case 5 : f1 = fopen("RESERVATIONSDEMI.txt", "a") ;
				 fprintf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d\n", id, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
				 fclose(f1) ;
			break ;
		case 6 : f1 = fopen("RESERVATIONSPETITEFINALE.txt", "a") ;
				 fprintf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d\n", id, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
				 fclose(f1) ;		
			break ;
		case 7 : f1 = fopen("RESERVATIONSFINALE.txt", "a") ;
				 fprintf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d\n", id, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, unePlace.block, unePlace.rang, unePlace.place) ;
				 fclose(f1) ;		
			break ;
	}
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------R�servations quarts de finale------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void reservation_quarts(int p_choix)
{
	int ok ;
	
	initialisation_unePlace()                           ;
	chargement_equipes_quarts()                         ;
	stade_date_heure_quarts()                           ;
	affichage_quarts()                                  ;
	selection_quart()                                   ;

	if(strcmp(unePlace.nomStade, "init") != 0)//Si l'utilisateur n'a pas s�lectionn� 0 -> quitter la fonction
	{
		ok = recuperation_place_nom_prenom_incrementation() ;
	
		//Si le stock n'est pas complet pour cette type de place, et que l'utilisateur � valid� la r�servation : on sauvegarde la r�servation
		if((unePlace.place != -1)&&(ok == 1))
		{
		sauvegarde_place(p_choix)                      ;		
		}

	}
	
}



/*---------------------------------------------------------------------*/
/*--------Charge les �quipes qualifi�es pour les quarts de finale------*/
/*---------------------------------------------------------------------*/
void chargement_equipes_quarts()
{
	FILE *f1             ;
	int i                ;
	struct match unMatch ;

	if(verif_null("RESULTATSHUITIEMES.txt"))//si les r�sultats des huiti�mes ne sont pas encore connus
	{
		strcpy(lesQuarts[0].e1, "VAINQUEUR-DU-1e-HUITIEME-DE-FINALE") ;
		strcpy(lesQuarts[0].e2, "VAINQUEUR-DU-2e-HUITIEME-DE-FINALE") ;
		
		strcpy(lesQuarts[1].e1, "VAINQUEUR-DU-3e-HUITIEME-DE-FINALE") ;
		strcpy(lesQuarts[1].e2, "VAINQUEUR-DU-4e-HUITIEME-DE-FINALE") ;
		
		strcpy(lesQuarts[2].e1, "VAINQUEUR-DU-5e-HUITIEME-DE-FINALE") ;
		strcpy(lesQuarts[2].e2, "VAINQUEUR-DU-6e-HUITIEME-DE-FINALE") ;
		
		strcpy(lesQuarts[3].e1, "VAINQUEUR-DU-7e-HUITIEME-DE-FINALE") ;
		strcpy(lesQuarts[3].e2, "VAINQUEUR-DU-8e-HUITIEME-DE-FINALE") ;
	}
	else//extraction des r�sultats du fichier
	{
		f1 = fopen("RESULTATSHUITIEMES.txt", "r") ;
		
		for(i=0 ; i<NB_MATCHS_QUARTS ; i++)
		{
			fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
			//attribution de la premi�re equipe en fonction des r�sultats des huiti�mes
			if(unMatch.buts_e1 > unMatch.buts_e2)
			{
				strcpy(lesQuarts[i].e1, unMatch.e1) ;
			}
			else
			{
				strcpy(lesQuarts[i].e1, unMatch.e2) ;
			}
			
			fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
			//attribution de la deuxi�me equipe en fonction des r�sultats des huiti�mes
			if(unMatch.buts_e1 > unMatch.buts_e2)
			{
				strcpy(lesQuarts[i].e2, unMatch.e1) ;
			}
			else
			{
				strcpy(lesQuarts[i].e2, unMatch.e2) ;
			}
		}
		fclose(f1) ;
	}
}



/*---------------------------------------------------------------------*/
/*-------Attribue les stades et les dates aux quarts de finale---------*/
/*---------------------------------------------------------------------*/
void stade_date_heure_quarts()
{
	strcpy(lesQuarts[0].stade, "BEAUJOIRE") ;
	strcpy(lesQuarts[0].date, "07-03-2021") ;
	strcpy(lesQuarts[0].heure, "18h00")     ;
	
	strcpy(lesQuarts[1].stade, "VELODROME") ;
	strcpy(lesQuarts[1].date, "07-03-2021") ;
	strcpy(lesQuarts[1].heure, "21h00")     ;
	
	strcpy(lesQuarts[2].stade, "BEAUJOIRE") ;
	strcpy(lesQuarts[2].date, "08-03-2021") ;
	strcpy(lesQuarts[2].heure, "21h00")     ;
	
	strcpy(lesQuarts[3].stade, "STADE-DE-FRANCE") ;
	strcpy(lesQuarts[3].date, "08-03-2021")       ;
	strcpy(lesQuarts[3].heure, "18h00")           ;	
}




/*---------------------------------------------------------------------*/
/*----------------Affichage des matchs des quarts de finale------------*/
/*---------------------------------------------------------------------*/
void affichage_quarts()
{
	int i                ;
	struct match unMatch ;
	
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf("%60s\n","QUARTS DE FINALE\n")                                                                                                                                ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;                                                                                                                                                        ;
	printf(" %-8s | %-71s | %-12s | %-20s | %7s\n", "NUMERO", "MATCH", "DATE", "STADE", "HEURE")                                                                         ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	
	for(i=0 ; i<NB_MATCHS_QUARTS ; i++)
	{
		unMatch = lesQuarts[i] ;
		tiret_en_espace(unMatch.e1)     ; 
        tiret_en_espace(unMatch.e2)     ;
        tiret_en_espace(unMatch.date)   ;
        tiret_en_espace(unMatch.stade)  ;
		
		printf("%8d   %34s - %-34s   %-12s   %-20s   %7s\n", i+1, unMatch.e1, unMatch.e2, unMatch.date, unMatch.stade, unMatch.heure) ;
	}
	printf("\n") ;
}



/*------------------------------------------------------------------------------------------------------------*/
/*Transmet les informations du Quart de finale choisit par l'utilisateur vers la place en cours de r�servation*/
/*------------------------------------------------------------------------------------------------------------*/
void selection_quart()
{
	int numMatch ;
	
	printf("Veuillez saisir le numero du match que vous souhaitez reserver (saisir 0 pour quitter) : ") ;
	scanf("%d", &numMatch)                                                      ;

	if(numMatch != 0)
	{
		numMatch--;//numMatch doit correspondre aux indices de lesQuarts donc de 0 � 4
	
		//On transfert les informations du quart s�lectionn� � la place de l'utilisateur : stade, date et heure. Le stade et la date vont permettre de retrouver le fichier dans lequel le stock de place est g�r� pour ce match.
		switch(numMatch)
		{
			case 0 : strcpy(unePlace.nomStade, lesQuarts[numMatch].stade) ;
				 	 strcpy(unePlace.date, lesQuarts[numMatch].date)      ;
				 	 strcpy(unePlace.heure, lesQuarts[numMatch].heure)    ;
				 	 strcpy(unePlace.e1, lesQuarts[numMatch].e1)          ;
				 	 strcpy(unePlace.e2, lesQuarts[numMatch].e2)          ;
				break ;
			case 1 : strcpy(unePlace.nomStade, lesQuarts[numMatch].stade) ;
				 	 strcpy(unePlace.date, lesQuarts[numMatch].date)      ;
				 	 strcpy(unePlace.heure, lesQuarts[numMatch].heure)    ;
				 	 strcpy(unePlace.e1, lesQuarts[numMatch].e1)          ;
				 	 strcpy(unePlace.e2, lesQuarts[numMatch].e2)          ;				 
				break ;
			case 2 : strcpy(unePlace.nomStade, lesQuarts[numMatch].stade) ;
				 	 strcpy(unePlace.date, lesQuarts[numMatch].date)      ;
				 	 strcpy(unePlace.heure, lesQuarts[numMatch].heure)    ;
				 	 strcpy(unePlace.e1, lesQuarts[numMatch].e1)          ;
				 	 strcpy(unePlace.e2, lesQuarts[numMatch].e2)          ;				 
				break ;
			case 3 : strcpy(unePlace.nomStade, lesQuarts[numMatch].stade) ;
				 	 strcpy(unePlace.date, lesQuarts[numMatch].date)      ;
				 	 strcpy(unePlace.heure, lesQuarts[numMatch].heure)    ;
				 	 strcpy(unePlace.e1, lesQuarts[numMatch].e1)          ;
				 	 strcpy(unePlace.e2, lesQuarts[numMatch].e2)          ;		
				break ; 																			
		}
	}
}





/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------R�servations demi-finale-----------------------------------------------------------*/
/*--------------------_---------------------------------------------------------------------------------------------------------------------*/
void reservation_demi(int p_choix)
{
	int ok ;
	
	initialisation_unePlace()                           ;
	chargement_equipes_demi()                           ;
	stade_date_heure_demi()                             ;
	affichage_demi()                                    ;
	selection_demi()                                    ;

	if(strcmp(unePlace.nomStade, "init") != 0)//Si l'utilisateur n'a pas s�lectionn� 0 -> quitter la fonction
	{
		ok = recuperation_place_nom_prenom_incrementation() ;
	
		//Si le stock n'est pas complet pour cette type de place, et que l'utilisateur � valid� la r�servation : on sauvegarde la r�servation
		if((unePlace.place != -1)&&(ok == 1))
		{
			sauvegarde_place(p_choix)                      ;		
		}
	}
}



/*---------------------------------------------------------------------*/
/*----------Charge les �quipes qualifi�es pour les demi-finales--------*/
/*---------------------------------------------------------------------*/
void chargement_equipes_demi()
{
	FILE *f1             ;
	int i                ;
	struct match unMatch ;
	
	
	if(verif_null("RESULTATSQUARTS.txt"))//si les r�sultats des huiti�mes ne sont pas encore connus
	{
		strcpy(lesDemi[0].e1, "VAINQUEUR-DU-1e-QUART-DE-FINALE") ;
		strcpy(lesDemi[0].e2, "VAINQUEUR-DU-2e-QUART-DE-FINALE") ;
		
		strcpy(lesDemi[1].e1, "VAINQUEUR-DU-3e-QUART-DE-FINALE") ;
		strcpy(lesDemi[1].e2, "VAINQUEUR-DU-4e-QUART-DE-FINALE") ;
	}
	else
	{
		f1 = fopen("RESULTATSQUARTS.txt", "r") ;
		
		for(i=0 ; i<NB_MATCHS_DEMI ; i++)
		{
			fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
			//attribution de la premi�re equipe en fonction des r�sultats des quarts
			if(unMatch.buts_e1 > unMatch.buts_e2)
			{
				strcpy(lesDemi[i].e1, unMatch.e1) ;
			}
			else
			{
				strcpy(lesDemi[i].e1, unMatch.e2) ;
			}
			
			fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
			//attribution de la deuxi�me equipe en fonction des r�sultats des quarts
			if(unMatch.buts_e1 > unMatch.buts_e2)
			{
				strcpy(lesDemi[i].e2, unMatch.e1) ;
			}
			else
			{
				strcpy(lesDemi[i].e2, unMatch.e2) ;
			}
		}
		fclose(f1) ;
	}
}



/*---------------------------------------------------------------------*/
/*-----------Attribue les stades et les dates aux demi-finales---------*/
/*---------------------------------------------------------------------*/
void stade_date_heure_demi()
{
	strcpy(lesDemi[0].stade, "STADE-DE-FRANCE") ;
	strcpy(lesDemi[0].date, "12-03-2021") ; 
	strcpy(lesDemi[0].heure, "18h00")     ;
	
	strcpy(lesDemi[1].stade, "VELODROME") ;
	strcpy(lesDemi[1].date, "13-03-2021") ;
	strcpy(lesDemi[1].heure, "21h00")     ;
	
}



/*---------------------------------------------------------------------*/
/*------------------Affichage des matchs des demi-finales--------------*/
/*---------------------------------------------------------------------*/
void affichage_demi()
{
	int i                ;
	struct match unMatch ;
	
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf("%60s\n","DEMI-FINALE\n")                                                                                                                                     ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf(" %-8s | %-71s | %-12s | %-20s | %7s\n", "NUMERO", "MATCH", "DATE", "STADE", "HEURE")                                                                         ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	
	for(i=0 ; i<NB_MATCHS_DEMI ; i++)
	{
		unMatch = lesDemi[i] ;
		tiret_en_espace(unMatch.e1)     ; 
        tiret_en_espace(unMatch.e2)     ;
        tiret_en_espace(unMatch.date)   ;
        tiret_en_espace(unMatch.stade)  ;
		
		printf("%8d   %34s - %-34s   %-12s   %-20s   %7s\n", i+1, unMatch.e1, unMatch.e2, unMatch.date, unMatch.stade, unMatch.heure) ;

	}
	printf("\n") ;
}



/*-----------------------------------------------------------------------------------------------------------*/
/*Transmet les informations de la demi-finale choisit par l'utilisateur vers la place en cours de r�servation*/
/*-----------------------------------------------------------------------------------------------------------*/
void selection_demi()
{
	int numMatch ;
	
	printf("Veuillez saisir le numero du match que vous souhaitez reserver (saisir 0 pour quitter) : ") ;
	scanf("%d", &numMatch)                                                                              ;
	
	if(numMatch != 0)
	{
		numMatch--                                                                                       ;//numMatch doit correspondre aux indices de lesQuarts donc de 0 � 4
	
			//On transfert les informations du quart s�lectionn� � la place de l'utilisateur : stade, date et heure. Le stade et la date vont permettre de retrouver le fichier dans lequel le stock de place est g�r� pour ce match.
			switch(numMatch)
			{
				case 0 : strcpy(unePlace.nomStade, lesDemi[numMatch].stade) ;
				 		strcpy(unePlace.date, lesDemi[numMatch].date)      ;
				 		strcpy(unePlace.heure, lesDemi[numMatch].heure)    ;
				 		strcpy(unePlace.e1, lesDemi[numMatch].e1)          ;
				 		strcpy(unePlace.e2, lesDemi[numMatch].e2)          ;
					break ;
				case 1 : strcpy(unePlace.nomStade, lesDemi[numMatch].stade) ;
				 		strcpy(unePlace.date, lesDemi[numMatch].date)      ;
				 		strcpy(unePlace.heure, lesDemi[numMatch].heure)    ;
				 		strcpy(unePlace.e1, lesDemi[numMatch].e1)          ;
				 		strcpy(unePlace.e2, lesDemi[numMatch].e2)          ;			 
					break ;
			}

	}                                                                   
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------R�servations petite finale--------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void reservation_petite_finale(int p_choix)
{
	int ok        ;
	
	initialisation_unePlace()                           ;
	chargement_equipes_petite_finale()                  ;
	stade_date_heure_petite_finale()                    ;
	affichage_petite_finale()                           ;
	
	strcpy(unePlace.nomStade, laPetiteFinale.stade) ;
	strcpy(unePlace.date, laPetiteFinale.date)      ;
	strcpy(unePlace.heure, laPetiteFinale.heure)    ;
	strcpy(unePlace.e1, laPetiteFinale.e1)          ;
	strcpy(unePlace.e2, laPetiteFinale.e2)          ;
	
 	ok = recuperation_place_nom_prenom_incrementation() ;	
 	
	//Si le stock n'est pas complet pour cette type de place, et que l'utilisateur � valid� la r�servation : on sauvegarde la r�servation
	if((unePlace.place != -1)&&(ok == 1))
	{
		sauvegarde_place(p_choix)                      ;		
	}	

}



/*---------------------------------------------------------------------*/
/*----------Charge les �quipes qualifi�es pour la petite finale--------*/
/*---------------------------------------------------------------------*/
void chargement_equipes_petite_finale()
{
	FILE *f1             ;
	struct match unMatch ; 
	
	if(verif_null("RESULTATSDEMI.txt"))//si les r�sultats des demi-finales ne sont pas encore connus
	{
		strcpy(laPetiteFinale.e1, "PERDANT-DE-LA-1e-DEMI-FINALE") ;
		strcpy(laPetiteFinale.e2, "PERDANT-DE-LA-2e-DEMI-FINALE") ;
	}
	else
	{
		f1 = fopen("RESULTATSDEMI.txt", "r") ;
			
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
		//attribution de la premi�re equipe en fonction des r�sultats des quarts
		if(unMatch.buts_e1 < unMatch.buts_e2)
		{
			strcpy(laPetiteFinale.e1, unMatch.e1) ;
		}
		else
		{
			strcpy(laPetiteFinale.e1, unMatch.e2) ;
		}
		
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
		
		//attribution de la deuxi�me equipe en fonction des r�sultats des quarts
		if(unMatch.buts_e1 < unMatch.buts_e2)
		{
			strcpy(laPetiteFinale.e2, unMatch.e1) ;
		}
		else
		{
			strcpy(laPetiteFinale.e2, unMatch.e2) ;
		}
		fclose(f1) ;
	}
}



/*---------------------------------------------------------------------*/
/*---------Attribue les stades et les dates � la petite finale---------*/
/*---------------------------------------------------------------------*/
void stade_date_heure_petite_finale()
{
	strcpy(laPetiteFinale.stade, "VELODROME") ;
	strcpy(laPetiteFinale.date, "17-03-2021") ; 
	strcpy(laPetiteFinale.heure, "21h00")     ;
}



/*---------------------------------------------------------------------*/
/*----------------------Affichage de la petite finale------------------*/
/*---------------------------------------------------------------------*/
void affichage_petite_finale()
{
	
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf("%60s\n","PETITE FINALE\n")                                                                                                                                   ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf(" %-8s | %-71s | %-12s | %-20s | %7s\n", "NUMERO", "MATCH", "DATE", "STADE", "HEURE")                                                                         ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;

		tiret_en_espace(laPetiteFinale.e1)     ; 
        tiret_en_espace(laPetiteFinale.e2)     ;
        tiret_en_espace(laPetiteFinale.date)   ;
        tiret_en_espace(laPetiteFinale.stade)  ;
	printf("%8d   %34s - %-34s   %-12s   %-20s   %7s\n", 1, laPetiteFinale.e1, laPetiteFinale.e2, laPetiteFinale.date, laPetiteFinale.stade, laPetiteFinale.heure) ;
		espace_en_tiret(laPetiteFinale.e1)    ;
		espace_en_tiret(laPetiteFinale.e2)    ;
		espace_en_tiret(laPetiteFinale.date)  ;
		espace_en_tiret(laPetiteFinale.stade) ;
	printf("\n") ;
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------R�servations finale------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void reservation_finale(int p_choix)
{
	int ok ;
	
	initialisation_unePlace()                           ;
	chargement_equipes_finale()                         ;
	stade_date_heure_finale()                           ;
	affichage_finale()                                  ;
	
	strcpy(unePlace.nomStade, laFinale.stade) ;
	strcpy(unePlace.date, laFinale.date)      ;
	strcpy(unePlace.heure, laFinale.heure)    ;
	strcpy(unePlace.e1, laFinale.e1)          ;
	strcpy(unePlace.e2, laFinale.e2)          ;
	
	ok = recuperation_place_nom_prenom_incrementation() ;
	
	//Si le stock n'est pas complet pour cette type de place, et que l'utilisateur � valid� la r�servation : on sauvegarde la r�servation
	if((unePlace.place != -1)&&(ok == 1))
	{
		sauvegarde_place(p_choix)                      ;		
	}
}



/*---------------------------------------------------------------------*/
/*-------------Charge les �quipes qualifi�es pour la finale------------*/
/*---------------------------------------------------------------------*/
void chargement_equipes_finale()
{
	FILE *f1             ;
	struct match unMatch ;
	
	if(verif_null("RESULTATSDEMI.txt"))//si les r�sultats des demi-finales ne sont pas encore connus
	{
		strcpy(laFinale.e1, "VAINQUEUR-DE-LA-1e-DEMI-FINALE") ;
		strcpy(laFinale.e2, "VAINQUEUR-DE-LA-2e-DEMI-FINALE") ;
	}
	else
	{
		f1 = fopen("RESULTATSDEMI.txt", "r") ;
			
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
			
		//attribution de la premi�re equipe en fonction des r�sultats des quarts
		if(unMatch.buts_e1 > unMatch.buts_e2)
		{
			strcpy(laFinale.e1, unMatch.e1) ;
		}
		else
		{
			strcpy(laFinale.e1, unMatch.e2) ;
		}
		
		fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
		
		//attribution de la deuxi�me equipe en fonction des r�sultats des quarts
		if(unMatch.buts_e1 > unMatch.buts_e2)
		{
			strcpy(laFinale.e2, unMatch.e1) ;
		}
		else
		{
			strcpy(laFinale.e2, unMatch.e2) ;
		}
		fclose(f1) ;
	}
}



/*---------------------------------------------------------------------*/
/*---------Attribue les stades et les dates � la petite finale---------*/
/*---------------------------------------------------------------------*/
void stade_date_heure_finale()
{
	strcpy(laFinale.stade, "STADE-DE-FRANCE") ;
	strcpy(laFinale.date, "18-03-2021") ; 
	strcpy(laFinale.heure, "21h00")     ;
}



/*---------------------------------------------------------------------*/
/*----------------------Affichage de la finale-------------------------*/
/*---------------------------------------------------------------------*/
void affichage_finale()
{	
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf("%60s\n","FINALE\n")                                                                                                                                         ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
	printf(" %-8s | %-71s | %-12s | %-20s | %7s\n", "NUMERO", "MATCH", "DATE", "STADE", "HEURE")                                                                         ;
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n")            ;
		tiret_en_espace(laFinale.e1)     ; 
        tiret_en_espace(laFinale.e2)     ;
        tiret_en_espace(laFinale.date)   ;
        tiret_en_espace(laFinale.stade)  ;
	
	printf("%8d   %34s - %-34s   %-12s   %-20s   %7s\n", 1, laFinale.e1, laFinale.e2, laFinale.date, laFinale.stade, laFinale.heure) ;
		espace_en_tiret(laFinale.e1)    ;
		espace_en_tiret(laFinale.e2)    ;
		espace_en_tiret(laFinale.date)  ;
		espace_en_tiret(laFinale.stade) ;

	printf("\n") ;
}






/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------Acc�der aux r�servations de l'utilisateur de la session------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void mes_reservations()
{
	FILE *f1                    ;
	int check, i, cpt, nbplaces ;
	int j, lechoix, numresa   ;
	char identifiant[MAX_ID]    ;
	
	struct place mesPlaces[MAX_NB_RESERVATIONS] ;
	
	i = 0                                        ;
	
	f1 = fopen("RESERVATIONSHUITIEMES.txt", "r") ;//on cherche les r�servations de l'utilisateur pour les huiti�mes
	
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", identifiant, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if((check != EOF)&&(strcmp(identifiant, id) == 0))//si l'ID de l'utilisateur appara�t sur une ligne du fichier des r�servation, on extrait les donn�es de la r�servation dans mesPlaces
		{
			mesPlaces[i++] = unePlace ;
		}
	}
	fclose(f1) ;
	
	f1 = fopen("RESERVATIONSQUARTS.txt", "r") ;//on cherche les r�servation de l'utilisateur pour les quarts
	
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", identifiant, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if((check != EOF)&&(strcmp(identifiant, id) == 0))//si l'ID de l'utilisateur appara�t sur une ligne du fichier des r�servation, on extrait les donn�es de la r�servation dans mesPlaces
		{
			mesPlaces[i++] = unePlace ;
		}
	}
	fclose(f1) ;
	
	f1 = fopen("RESERVATIONSDEMI.txt", "r") ;//on cherche les r�servation de l'utilisateur pour les demi-finales
	
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", identifiant, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if((check != EOF)&&(strcmp(identifiant, id) == 0))//si l'ID de l'utilisateur appara�t sur une ligne du fichier des r�servation, on extrait les donn�es de la r�servation dans mesPlaces
		{
			mesPlaces[i++] = unePlace ;
		}
	}
	fclose(f1) ;
	
	f1 = fopen("RESERVATIONSPETITEFINALE.txt", "r") ;//on cherche les r�servation de l'utilisateur pour les demi-finales
	
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", identifiant, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if((check != EOF)&&(strcmp(identifiant, id) == 0))//si l'ID de l'utilisateur appara�t sur une ligne du fichier des r�servation, on extrait les donn�es de la r�servation dans mesPlaces
		{
			mesPlaces[i++] = unePlace ;
		}
	}
	fclose(f1) ;
	
		f1 = fopen("RESERVATIONSFINALE.txt", "r") ;//on cherche les r�servation de l'utilisateur pour les demi-finales
	
	while(! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", identifiant, unePlace.nom, unePlace.prenom, unePlace.e1, unePlace.e2, unePlace.nomStade, unePlace.date, unePlace.heure, unePlace.nomTribune, unePlace.categorie, &unePlace.block, &unePlace.rang, &unePlace.place) ;
		
		if((check != EOF)&&(strcmp(identifiant, id) == 0))//si l'ID de l'utilisateur appara�t sur une ligne du fichier des r�servation, on extrait les donn�es de la r�servation dans mesPlaces
		{
			mesPlaces[i++] = unePlace ;
		}
	}
	fclose(f1) ;
	
	if(i == 0)//i est le compteur du nombre de places 
	{
		printf("Aucune reservation a afficher\n") ;
	}
	else
	{
		printf("%-3s | %-25s | %-71s | %-25s | %-12s\n", "NUM", "NOM", "MATCH", "STADE", "DATE") ;
		printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n") ;
	
		for(cpt=0 ; cpt<i ; cpt++)
		{
			tiret_en_espace(mesPlaces[cpt].nom)      ; 
        	tiret_en_espace(mesPlaces[cpt].e1)       ;
        	tiret_en_espace(mesPlaces[cpt].e2)       ;
        	tiret_en_espace(mesPlaces[cpt].nomStade) ;
			tiret_en_espace(mesPlaces[cpt].date)     ;
			printf("%-3d   %-25s   %34s - %-34s   %-25s   %-12s\n", cpt+1, mesPlaces[cpt].nom, mesPlaces[cpt].e1, mesPlaces[cpt].e2, mesPlaces[cpt].nomStade, mesPlaces[cpt].date) ;
		}
		printf("\n") ; 
        printf("Voulez-vous afficher un billet : (1 pour oui, 2 pour non ) ") ;
        scanf("%d", &lechoix) ; 

        if (lechoix == 1)
        {
          printf("Le billet de quelle réservation voulez-vous afficher (entrer numéro de reservation) : ") ; 
          scanf("%d", &numresa) ;
          if ((numresa > i) || (numresa <1)) 
          {
              printf("Ce numéro de resarvation n'existe pas\n") ; 
              printf("\n") ; 
          }
          else
          {  

            affichage_billet(mesPlaces[numresa-1]) ; 
          }
	    } // fin du if 
        else
        {
			printf("\n") ;
        }
	}
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------Chargement du maximum de rangs par block------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
int max_rang()
{
	if(strcmp(unePlace.nomStade,"BEAUJOIRE") == 0)
	{
		return 10 ;
	}
	else
	{
		return 5 ;
	}
}



/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------Chargement du maximum de blocks par tribune et de rangs par blocks----------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
int max_block()
{
	FILE *f1                 ;
	char nomFichier[MAX_NOM_FICHIER]      ;
	char tribune[MAX_NOM_TRIBUNE]         ;
	char cat[MAX_NOM_CAT]              ;
	int block, rang, place   ;
	
	strcpy(nomFichier, unePlace.nomStade) ;
	strcat(nomFichier, ".txt")            ;
	
	f1 = fopen(nomFichier, "r") ;
	
	while((strcmp(unePlace.nomTribune, tribune) != 0)||(strcmp(unePlace.categorie, cat) != 0))
	{
		fscanf(f1, "%s %s %d %d %d", tribune, cat, &block, &rang, &place) ;
	}
	
	fclose(f1)   ;
	return block ;
	
}



/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Conversion majuscules-----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void conv_maj(char chaine[])
{
  int taille, i ;

  taille = strlen(chaine);

  for (i = 0 ; i < taille ; i++)
  {
    chaine[i] = toupper(chaine[i]);
  }
}





/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Affichage Bienvenu--------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void bienvenu()
{
	printf("\n")                                                                                                   ;
	printf("--------------------------------------------------------------------------------------------------\n") ;
	printf("               Bienvenu sur le programme de reservation de la Coupe du Monde 2021 !               \n") ;
	printf("--------------------------------------------------------------------------------------------------\n") ;
	printf("\n")                                                                                                   ;
}



/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------Quitter--------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void quitter()
{
	printf("\n")                                     ;
	printf("Fermeture du programme...A bientot !\n") ;
}



/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------Quitter espace client---------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void quitter_espace_client()
{
	printf("Vous quittez votre espace client...A bientot !\n") ;
	printf("-------------------------------------------------------------------------------------------------------------------\n") ;
	printf("\n")                                               ;
}



/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Procédure  changement en espace ------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

void tiret_en_espace(char ch[])
{
	char car=' ' ;
	int i     ;
	int taille ; 
	taille = strlen(ch) ; 


	for (i=0 ; i <= taille ; i++)
    {	
		car = ch[i] ; 
        if(car == '-')
        car = ' ' ; 
		ch[i]=car     ;
	}
	ch[i-1]='\0'; 

}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Procédure  changement en tiret ------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


void espace_en_tiret(char ch[])
{
	char car=' ' ;
	int i     ;
	int taille ; 
	taille = strlen(ch) ; 


	for (i=0 ; i <= taille ; i++)
    {	
		car = ch[i] ; 
        if(car == ' ')
        car = '-' ; 
		ch[i]=car     ;
	}
	ch[i-1]='\0'; 

}





/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Procédure d'affichage d'un billet ------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

void affichage_billet(struct place unBillet) 
{

			tiret_en_espace(unBillet.nom)       ; 
        	tiret_en_espace(unBillet.e1)        ;
        	tiret_en_espace(unBillet.e2)        ;
        	tiret_en_espace(unBillet.nomStade)  ;
			tiret_en_espace(unBillet.date)      ;
			tiret_en_espace(unBillet.prenom)    ;				

    printf("|----------------------------------------------------------------------------|\n")                    ;
	printf("|%40s %36s\n",unBillet.nomStade, "|")                                                                 ;
	printf("|----------------------------------------------------------------------------|\n")                    ;
	printf("|%-10s %5s %10s %49s\n",unBillet.date, "A" ,unBillet.heure, "|")                                      ;
	printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%-7s %-20s %-7s %-20s %17s\n","NOM :",unBillet.nom,"PRENOM : ",unBillet.prenom, "|"  )               ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%-40s %36s\n","TRIBUNE :","|"  )                                                                     ;
    printf("|%-40s %36s\n",unBillet.nomTribune, "|")                                                              ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%-40s %36s \n","CATEGORIE : ","|"  )                                                                 ;
    printf("|%-40s %36s\n",unBillet.categorie,"|")                                                                ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%35s %2s %-35s  %1s            \n", unBillet.e1, "-", unBillet.e2,"|")                               ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%-30s | %-10s | %-10s                    | \n", "BLOC", "RANG", "PLACE")                             ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
    printf("|%-30d | %-10d | %-10d                    |\n", unBillet.block, unBillet.rang, unBillet.place)        ;
    printf("|----------------------------------------------------------------------------|\n")                    ;
	printf("\n")                                                                                                  ;

}








/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------MENU DES FONCTIONS DE L'ADMIN-------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void menu_admin()
{
	int choix3 = -1 ;

	printf("\n")                    ;
	printf("MENU ADMINISTRATEUR\n") ;
	printf("\n")                    ;

	
	while(choix3 != 0)
	{
		printf("-1- Saisir les resultats des huitiemes de finale\n") ;
		printf("-2- Saisir les resultats des quarts de finale\n")    ;
		printf("-3- Saisir les resultats des demi-finales\n")        ;
		printf("-4- Saisir les resultats de la petite finale\n")     ;
		printf("-5- Saisir les resultats de la finale\n")            ;
		printf("-6- Voir les totaux de reservations\n")              ;
		printf("-0- Quitter le menu administrateur\n")               ;
		
		scanf("%d", &choix3) ;
		
		
			switch(choix3)
			{
				case 1 : saisie_huitiemes() ;
					break ;
				case 2 : saisie_quarts() ;
					break ;
				case 3 : saisie_demi() ;
					break ;
				case 4 : saisie_petite_finale() ;
					break ;
				case 5 : saisie_finale() ;
					break ;
				case 6 : total_reservations() ;
					break ;
				case 0 : printf("\n")                                                  ;
						 printf("Vous quittez le menu administrateur...A bientot !\n") ;
						 printf("\n")                                                  ;
					break ;
				default : printf("\n")                                     ;
						  printf("Saisie erronee, veuillez recommencer\n") ;
						  printf("\n")                                     ;
			}
	}
}




/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------Saisie des r�sultats des huit�mes--------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void saisie_huitiemes()
{
	FILE *f1             ;
	int i, cpt           ;
	struct match unMatch ;
	char check[15]       ;
	
	if(verif_null("RESULTATSHUITIEMES.txt"))
	{
		chargement_equipes_huitiemes() ;
		
		for(i=0; i<NB_MATCHS_HUITIEMES ; i++)//saisie des scores des huiti�mes �quipe par �quipe
		{
			unMatch = lesHuitiemes[i] ;
			
			//initialisation pour comparaison
			unMatch.buts_e1 = -1 ;
			unMatch.buts_e2 = -1 ;
			
			//comparaison des scores : score nul impossible en phase finale 
			while(unMatch.buts_e1 == unMatch.buts_e2)
			{
				printf("\n")                                                     ;
				printf("%de HUITIEME : %s vs %s\n", i+1, unMatch.e1, unMatch.e2) ;
				
				printf("Saisir le score de %s : ", unMatch.e1) ;
				scanf("%d", &unMatch.buts_e1)                  ;
				
				printf("Saisir le score de %s : ", unMatch.e2) ;
				scanf("%d", &unMatch.buts_e2)                  ;	
			}
			
			lesHuitiemes[i] = unMatch ;
		}
		
		//recapitulatif de saisie
		printf("\n") ;
		printf("RECAPITULATIF DE LA SAISIE : \n") ;
		for(i=0; i<NB_MATCHS_HUITIEMES ; i++)
		{
			unMatch = lesHuitiemes[i] ;
			printf("%25s %2d - %-2d %-25s\n", unMatch.e1, unMatch.buts_e1, unMatch.buts_e2, unMatch.e1) ;
		}
		
		//demande de confirmation de la saisie
		printf("\n") ;
		printf("Saisir 'OK' pour confirmer la saisie (Q pour annuler) : \n") ;
		printf(" /!\\ TOUTE SAISIE EST DEFINITIVE ET NON MODIFIABLE, ASSUREZ VOUS DE RENSEIGNER LES BONS RESULTATS /!\\ ") ;
		scanf("%s", check) ;
		conv_maj(check)    ;
		
		//sauvegarde de la saisie si confirmation
		if(strcmp(check, "OK") == 0)
		{
			f1 = fopen("RESULTATSHUITIEMES.txt", "w") ;
			
			for(cpt=0; cpt<NB_MATCHS_HUITIEMES ; cpt++)
			{
				unMatch = lesHuitiemes[cpt] ;
				fprintf(f1, "%s %d %s %d\n", unMatch.e1, unMatch.buts_e1, unMatch.e2, unMatch.buts_e2) ;
			}
			
			fclose(f1)                                                  ;
			printf("\n")                                                ;
			printf("Resultats des huitiemes de finale sauvegardes !\n") ;
			printf("\n")                                                ;
		}
		else
		{
			printf("\n")                     ;
			printf("Saisie abandonnee ...\n") ;
			printf("\n")                     ;
		}
	}
	else
	{
		printf("\n")                                         ;
		printf("Les resultats ont deja ete renseignes...\n") ;
		printf("\n")                                         ;
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------Saisie des r�sultats des quarts de finale-----------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void saisie_quarts()
{
	FILE *f1             ;
	int i, cpt           ;
	struct match unMatch ;
	char check[15]       ;
	
	if(verif_null("RESULTATSQUARTS.txt"))
	{
		chargement_equipes_quarts()    ;
		
		for(i=0; i<NB_MATCHS_QUARTS ; i++)//saisie des scores des huiti�mes �quipe par �quipe
		{
			unMatch = lesQuarts[i] ;
			
			//initialisation pour comparaison
			unMatch.buts_e1 = -1 ;
			unMatch.buts_e2 = -1 ;
			
			//comparaison des scores : score nul impossible en phase finale 
			while(unMatch.buts_e1 == unMatch.buts_e2)
			{
				printf("\n")                                                  ;
				printf("%de QUART : %s vs %s\n", i+1, unMatch.e1, unMatch.e2) ;
				
				printf("Saisir le score de %s : ", unMatch.e1) ;
				scanf("%d", &unMatch.buts_e1)                  ;
				
				printf("Saisir le score de %s : ", unMatch.e2) ;
				scanf("%d", &unMatch.buts_e2)                  ;	
			}			
			lesQuarts[i] = unMatch ;
		}
		
		//recapitulatif de saisie
		printf("\n") ;
		printf("RECAPITULATIF DE LA SAISIE : \n") ;
		for(i=0; i<NB_MATCHS_QUARTS ; i++)
		{
			unMatch = lesQuarts[i] ;
			printf("%25s %2d - %-2d %-25s\n", unMatch.e1, unMatch.buts_e1, unMatch.buts_e2, unMatch.e1) ;
		}
		
		//demande de confirmation de la saisie
		printf("\n") ;
		printf("Saisir 'OK' pour confirmer la saisie (Q pour annuler) : \n") ;
		printf(" /!\\ TOUTE SAISIE EST DEFINITIVE ET NON MODIFIABLE, ASSUREZ VOUS DE RENSEIGNER LES BONS RESULTATS /!\\ ") ;
		scanf("%s", check) ;
		conv_maj(check)    ;
		
		//sauvegarde de la saisie si confirmation
		if(strcmp(check, "OK") == 0)
		{
			f1 = fopen("RESULTATSQUARTS.txt", "w") ;
		
			for(cpt=0; cpt<NB_MATCHS_QUARTS ; cpt++)//sauvegarde des r�sultats saisis dans un fichier d�di� aux huiti�mes
			{
				unMatch = lesQuarts[cpt] ;
				fprintf(f1, "%s %d %s %d\n", unMatch.e1, unMatch.buts_e1, unMatch.e2, unMatch.buts_e2) ;
			}
			
			fclose(f1)                                               ;
			printf("\n")                                             ;
			printf("Resultats des quarts de finale sauvegardes !\n") ;
			printf("\n")                                             ;
		}
		else
		{
			printf("\n")                     ;
			printf("Saisie abandonnee...\n") ;
			printf("\n")                     ;			
		}
	}
	else
	{
		printf("\n")                                         ;
		printf("Les resultats ont deja ete renseignes...\n") ;
		printf("\n")                                         ;
	}
}



/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------Saisie des r�sultats des demi-finales-------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void saisie_demi()
{
	FILE *f1             ;
	int i, cpt           ;
	struct match unMatch ;
	char check[15]       ;
	
	
	if(verif_null("RESULTATSDEMI.txt"))
	{
		chargement_equipes_demi()    ;
		
		for(i=0; i<NB_MATCHS_DEMI ; i++)//saisie des scores des huiti�mes �quipe par �quipe
		{
			unMatch = lesDemi[i] ;
			
			//initialisation pour comparaison
			unMatch.buts_e1 = -1 ;
			unMatch.buts_e2 = -1 ;
			
			//comparaison des scores : score nul impossible en phase finale 
			while(unMatch.buts_e1 == unMatch.buts_e2)
			{
				printf("\n")                                                  ;
				printf("%de DEMI-FINALE : %s vs %s\n", i+1, unMatch.e1, unMatch.e2) ;
				
				printf("Saisir le score de %s : ", unMatch.e1) ;
				scanf("%d", &unMatch.buts_e1)                  ;
				
				printf("Saisir le score de %s : ", unMatch.e2) ;
				scanf("%d", &unMatch.buts_e2)                  ;	
			}			
			lesDemi[i] = unMatch ;
		}
		
		//recapitulatif de saisie
		printf("\n") ;
		printf("RECAPITULATIF DE LA SAISIE : \n") ;
		for(i=0; i<NB_MATCHS_DEMI ; i++)
		{
			unMatch = lesDemi[i] ;
			printf("%25s %2d - %-2d %-25s\n", unMatch.e1, unMatch.buts_e1, unMatch.buts_e2, unMatch.e1) ;
		}
		
		//demande de confirmation de la saisie
		printf("\n") ;
		printf("Saisir 'OK' pour confirmer la saisie (Q pour annuler) : \n") ;
		printf(" /!\\ TOUTE SAISIE EST DEFINITIVE ET NON MODIFIABLE, ASSUREZ VOUS DE RENSEIGNER LES BONS RESULTATS /!\\ ") ;
		scanf("%s", check) ;
		conv_maj(check)    ;
		
		//sauvegarde de la saisie si confirmation
		if(strcmp(check, "OK") == 0)
		{
			f1 = fopen("RESULTATSDEMI.txt", "w") ;
		
			for(cpt=0; cpt<NB_MATCHS_DEMI ; cpt++)//sauvegarde des r�sultats saisis dans un fichier d�di� aux huiti�mes
			{
				unMatch = lesDemi[cpt] ;
				fprintf(f1, "%s %d %s %d\n", unMatch.e1, unMatch.buts_e1, unMatch.e2, unMatch.buts_e2) ;
			}
			
			fclose(f1)                                           ;
			printf("\n")                                         ;
			printf("Resultats des demi-finales sauvegardes !\n") ;
			printf("\n")                                         ;
		}
		else
		{
			printf("\n")                     ;
			printf("Saisie abandonnee...\n") ;
			printf("\n")                     ;			
		}
	}
	else
	{
		printf("\n")                                         ;
		printf("Les resultats ont deja ete renseignes...\n") ;
		printf("\n")                                         ;
	}
}



/*------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------Saisie des r�sultats de la petite finale----------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------------*/
void saisie_petite_finale()
{
	FILE *f1             ;
	int i, cpt           ;
	struct match unMatch ;
	char check[15]       ;
	
	if(verif_null("RESULTATPETITEFINALE.txt"))
	{
		chargement_equipes_petite_finale() ;
			
		//initialisation pour comparaison
		laPetiteFinale.buts_e1 = -1 ;
		laPetiteFinale.buts_e2 = -1 ;
			
		//comparaison des scores : score nul impossible en phase finale 
		while(laPetiteFinale.buts_e1 == laPetiteFinale.buts_e2)
		{
			printf("\n")                                                               ;
			printf("PETITE FINALE : %s vs %s\n", laPetiteFinale.e1, laPetiteFinale.e2) ;
			
			printf("Saisir le score de %s : ", laPetiteFinale.e1) ;
			scanf("%d", &laPetiteFinale.buts_e1)                  ;
			
			printf("Saisir le score de %s : ", laPetiteFinale.e2) ;
			scanf("%d", &laPetiteFinale.buts_e2)                  ;	
		}
		
		//recapitulatif de saisie
		printf("\n") ;
		printf("RECAPITULATIF DE LA SAISIE : \n") ;
		printf("%25s %2d - %-2d %-25s\n", laPetiteFinale.e1, laPetiteFinale.buts_e1, laPetiteFinale.buts_e2, laPetiteFinale.e1) ;			
		
		//demande de confirmation de la saisie
		printf("\n") ;
		printf("Saisir 'OK' pour confirmer la saisie (Q pour annuler) : \n") ;
		printf(" /!\\ TOUTE SAISIE EST DEFINITIVE ET NON MODIFIABLE, ASSUREZ VOUS DE RENSEIGNER LES BONS RESULTATS /!\\ ") ;
		scanf("%s", check) ;
		conv_maj(check)    ;
		
		//sauvegarde de la saisie si confirmation
		if(strcmp(check, "OK") == 0)
		{
			f1 = fopen("RESULTATPETITEFINALE.txt", "w") ;

			fprintf(f1, "%s %d %s %d\n", laPetiteFinale.e1, laPetiteFinale.buts_e1, laPetiteFinale.e2, laPetiteFinale.buts_e2) ;
		
			fclose(f1)                                            ;
			printf("\n")                                          ;
			printf("Resultat de la petite finale sauvegarde !\n") ;
			printf("\n")                                          ;
		}
		else
		{
			printf("\n")                     ;
			printf("Saisie abandonnee...\n") ;
			printf("\n")                     ;	
		}
	}
	else
	{
		printf("\n")                                         ;
		printf("Les resultats ont deja ete renseignes...\n") ;
		printf("\n")                                         ;
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------Saisie des r�sultats la finale----------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void saisie_finale()
{
	FILE *f1             ;
	int i, cpt           ;
	struct match unMatch ;
	char check[15]       ;
	
	if(verif_null("RESULTATFINALE.txt"))
	{
		chargement_equipes_finale() ;
			
		//initialisation pour comparaison
		laFinale.buts_e1 = -1 ;
		laFinale.buts_e2 = -1 ;
			
		//comparaison des scores : score nul impossible en phase finale 
		while(laFinale.buts_e1 == laFinale.buts_e2)
		{
			printf("\n")                                            ;
			printf("FINALE : %s vs %s\n", laFinale.e1, laFinale.e2) ;
			
			printf("Saisir le score de %s : ", laFinale.e1) ;
			scanf("%d", &laFinale.buts_e1)                  ;
			
			printf("Saisir le score de %s : ", laFinale.e2) ;
			scanf("%d", &laFinale.buts_e2)                  ;	
		}
		
		//recapitulatif de saisie
		printf("\n") ;
		printf("RECAPITULATIF DE LA SAISIE : \n") ;
		printf("%25s %2d - %-2d %-25s\n", laFinale.e1, laFinale.buts_e1, laFinale.buts_e2, laFinale.e1) ;			
		
		//demande de confirmation de la saisie
		printf("\n") ;
		printf("Saisir 'OK' pour confirmer la saisie (Q pour annuler) : \n") ;
		printf(" /!\\ TOUTE SAISIE EST DEFINITIVE ET NON MODIFIABLE, ASSUREZ VOUS DE RENSEIGNER LES BONS RESULTATS /!\\ ") ;
		scanf("%s", check) ;
		conv_maj(check)    ;
		
		//sauvegarde de la saisie si confirmation
		if(strcmp(check, "OK") == 0)
		{
			f1 = fopen("RESULTATFINALE.txt", "w") ;

			fprintf(f1, "%s %d %s %d\n", laFinale.e1, laFinale.buts_e1, laFinale.e2, laFinale.buts_e2) ;
		
			fclose(f1)                                     ;
			printf("\n")                                   ;
			printf("Resultat de la finale sauvegarde !\n") ;
			printf("\n")                                   ;
		}
		else
		{
			printf("\n")                     ;
			printf("Saisie abandonnee...\n") ;
			printf("\n")                     ;	
		}			
	}
	else
	{
		printf("Les resultats ont deja ete renseignes...\n") ;
		printf("\n")                                         ;
	}
}




/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------Affichage des r�sultats des manches de phase finale-----------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void affichage_res_manche(char p_manche[MAX_NOM_FICHIER])
{
	int i, check, cpt    ;
	struct match unMatch ;
	FILE *f1             ;
	
	f1 = fopen(p_manche, "r") ; 
	i = 0                     ;
	
	while(! feof(f1))//lecture des r�sultats enregistr�s dans les fichiers de r�sultat
	{
		check = fscanf(f1, "%s %d %s %d", unMatch.e1, &unMatch.buts_e1, unMatch.e2, &unMatch.buts_e2) ;
		
		if(check != EOF)
		{
			lesResultats[i++] = unMatch ;
		}
	}
	fclose(f1) ;

	printf("------------------------------------------------------------------------------------------------------\n")            ;
	switch(i)/*i nous donne la manche des r�sultats : si on a lu 8 �quipes, i =8, on est donc en huiti�me de finale.
	           Pour la petite finale et la finale il n'y a qu'un match, on va donc faire une fonction ind�pendante pour l'affichage de la finale*/
	{
		case 8 : printf("%58s\n", "HUITIEMES DE FINALE")                                                                          ;
			break;
		case 4 : printf("%57s\n", "QUARTS DE FINALE")                                                                             ;
			break;
		case 2 : printf("%57s\n", "DEMI-FINALES")                                                                                 ;
			break;
		case 1 : if(strcmp(p_manche, "RESULTATPETITEFINALE.txt") == 0)
				 {
				 	printf("%56s\n", "PETITE FINALE")                                                                             ;
				 }
				 else
				 {
					printf("%53s\n", "FINALE")                                                                                    ;	
				 }
			break;
	}
	printf("------------------------------------------------------------------------------------------------------\n")            ;
	


	for(cpt = 0 ; cpt<i ; cpt++)
	{
		unMatch = lesResultats[cpt] ;
		
		printf("%45s %2d - %-2d %-25s\n", unMatch.e1, unMatch.buts_e1, unMatch.buts_e2, unMatch.e2) ;
		printf("\n")                                                                        ;	
	}
	printf("------------------------------------------------------------------------------------------------------\n")            ;
	printf("\n") ;
}



/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------V�rifie si le fichier est renseign�-------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
int verif_null(char p_fichier[])
{
	FILE *f1  ;
	int check ;
	
	f1 = fopen(p_fichier, "r") ;
	
	fscanf(f1, "%d", &check) ;
	
	if(check == -1)
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}



/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------Affiche les nombres de r�servations par manche et par cat�gorie-------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void total_reservations()
{
	int total8Or = 0, total8Arg = 0, total8Brz = 0 ;//totaux des huit�mes par cat�gorie
	int total4Or = 0, total4Arg = 0, total4Brz = 0 ;//totaux des quarts par cat�gories
	int total2Or = 0, total2Arg = 0, total2Brz = 0 ;//totaux des demi par cat�gories
	int totalfOr = 0, totalfArg = 0, totalfBrz = 0 ;//totaux finale par cat�gorie
	int totalpfOr = 0, totalpfArg = 0, totalpfBrz = 0 ;//totaux petite finale par cat�gorie 
	int total = 0, totalOr = 0, totalArg = 0, totalBrz = 0;//total + totaux par cat�gorie
	int total8 = 0, total4 = 0, total2 = 0, totalpf = 0, totalf ;//totaux par manche
	
	compteur_cat("RESERVATIONSHUITIEMES.txt", &total8Or, &total8Arg, &total8Brz)      ;
	compteur_cat("RESERVATIONSQUARTS.txt", &total4Or, &total4Arg, &total4Brz)         ;
	compteur_cat("RESERVATIONSDEMI.txt", &total2Or, &total2Arg, &total2Brz)           ;
	compteur_cat("RESERVATIONSPETITEFINALE.txt", &totalpfOr, &totalpfArg, &totalfBrz) ;
	compteur_cat("RESERVATIONSFINALE.txt", &totalfOr, &totalfArg, &totalfBrz)         ;
	
	totalOr = total8Or + total4Or + total2Or + totalpfOr + totalfOr       ;
	totalArg = total8Arg + total4Arg + total2Arg + totalpfArg + totalfArg ;
	totalBrz = total8Brz + total4Brz + total2Brz + totalfBrz + totalfBrz  ;
	total = totalOr + totalArg + totalBrz                                 ;
	
	total8 = total8Or + total8Arg + total8Brz    ;
	total4 = total4Or + total4Arg + total4Brz    ;
	total2 = total2Or + total2Arg + total2Brz    ;
	totalpf = totalpfOr + totalpfArg + totalfBrz ;
	totalf = totalfOr + totalfArg + totalfBrz    ;
	
	printf("\n")                                                                                           ;
	printf("%15s | %-7s | %-7s | %-7s | %7s\n", "MANCHE", "OR", "ARGENT", "BRONZE", "TOTAL")              ;
	printf("---------------------------------------------------------\n")                                  ;
	printf("%15s | %7d | %7d | %7d | %7d\n" , "HUITIEMES", total8Or, total8Arg, total8Brz, total8)         ;
	printf("%15s | %7d | %7d | %7d | %7d\n" , "QUARTS", total4Or, total4Arg, total4Brz, total4)            ;
	printf("%15s | %7d | %7d | %7d | %7d\n" , "DEMI-FINALES", total2Or, total2Arg, total2Brz, total2)      ;
	printf("%15s | %7d | %7d | %7d | %7d\n" , "PETITE FINALE", totalpfOr, totalpfArg, totalpfBrz, totalpf) ;
	printf("%15s | %7d | %7d | %7d | %7d\n" , "FINALE", totalfOr, totalfArg, totalfBrz, totalf)            ;
	printf("---------------------------------------------------------\n")                                  ;	
	printf("%15s | %7d | %7d | %7d | %7d\n" , "TOTAL", totalOr, totalArg, totalBrz, total)                 ;
	printf("\n")                                                                                           ;
}


/*---------------------------------------------------------------------*/
/*--------------Compte le nombre de place par cat�gorie----------------*/
/*---------------------------------------------------------------------*/
void compteur_cat(char p_fichier[], int *compteur1, int *compteur2, int *compteur3)
{
	FILE *f1                    ;
	struct place uneReservation ;
	int check                   ;
	char idFichier[MAX_ID]      ;
	
	
	f1 = fopen(p_fichier, "r") ;
	
	while (! feof(f1))
	{
		check = fscanf(f1, "%s %s %s %s %s %s %s %s %s %s %d %d %d", idFichier, uneReservation.nom, uneReservation.prenom, uneReservation.e1, uneReservation.e2, uneReservation.nomStade, uneReservation.date, uneReservation.heure, uneReservation.nomTribune, uneReservation.categorie, &uneReservation.block, &uneReservation.rang, &uneReservation.place) ;
		if(check != EOF)
		{			
			if(strcmp(uneReservation.categorie, "OR") == 0)
			{
				*compteur1 = *compteur1 + 1 ;
			}
			else if((strcmp(uneReservation.categorie, "ARGENT") == 0))
			{
				*compteur2 = *compteur2 + 1 ;
			}
			else
			{
				*compteur3 = *compteur3 + 1 ;
			}
		}
	}
	fclose(f1) ;
}
