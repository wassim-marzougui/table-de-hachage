#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"
Biblio* charger_n_entrees(char* nomfic, int n) {
    Biblio *bib = creer_biblio();
    
    FILE *f = fopen(nomfic, "r");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier!\n");
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        int num;
        char titre[40];
        char auteur[40];
        if (fscanf(f, "%d %39s %39s", &num, titre, auteur) != 3) {
            printf("Erreur lors de la lecture du fichier!\n");
            break;
        }
        inserer_en_tete(bib, num, titre, auteur);
    }
    
    fclose(f);
    return bib;
}

void enregistrer_biblio(Biblio *b, char* nomfic){
    FILE *f=fopen(nomfic,"w");
    Livre *tmp=b->L;
    while(tmp){
        fprintf(f,"%d %s %s",tmp->num,tmp->titre,tmp->auteur);
        tmp=tmp->suiv;
    }
    fclose(f);
}