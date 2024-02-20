#ifndef _Bibli
#define _Bibli

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct {
    /* Tete fictive */
    Livre *L; /* Premier element */
} Biblio;

Livre* creer_livre(int num,char* titre,char* auteur);

void liberer_livre(Livre* l);

Biblio* creer_biblio();

void liberer_biblio(Biblio* b);

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);

void affichage_livre(Livre* l);

void affichage_biblio(Biblio* b);

Livre* recherche_ouvrage_num(Biblio* b,int num);

Livre* recherche_ouvrage_titre(Biblio* b,char *titre);

Biblio* recherche_ouvrages_auteur(Biblio* b ,char *auteur);

void suppression_ouvrage(Biblio *b,int num,char* titre,char* auteur);

void fusion_2_biblio(Biblio *b1,Biblio *b2);

Livre* ouvrage_exemplaire(Biblio *b);
#endif