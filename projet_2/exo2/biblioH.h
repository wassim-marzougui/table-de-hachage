#ifndef _Bibli
#define _Bibli

typedef struct livreh {
int clef ;
int num;
char *auteur;
char *titre;
struct livreh * suivant ;
} LivreH ;

typedef struct table {
int nE ; /*nombre d’elements contenus dans la table de hachage */
int m ; /*taille de la table de hachage */
LivreH ** T ; /*table de hachage avec resolution des collisions par chainage */
} BiblioH ;


int fonctionClef(char* auteur);

LivreH* creer_livre(int num,char* titre,char* auteur);

void liberer_livre(LivreH* l);

BiblioH* creer_biblio(int m);

int fonctionHachage(int cle, int m);

void liberer_biblio(BiblioH* b);

void inserer(BiblioH* b,int num,char* titre,char* auteur);

void affichage_livre(LivreH* l);

void affichage_bibli(BiblioH *b);

LivreH* recherche_ouvrage_num(BiblioH* b,int num);

LivreH* recherche_ouvrage_titre(BiblioH* b,char *titre);

BiblioH* recherche_ouvrages_auteur(BiblioH* b ,char *auteur);

void suppression_ouvrage(BiblioH *b,int num,char* titre,char* auteur);

void fusion_2_biblio(BiblioH *b1,BiblioH *b2);

LivreH* ouvrage_exemplaire(BiblioH *b);

#endif