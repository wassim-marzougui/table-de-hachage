#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EntreeSortieH.h"
#include "biblioH.h"
BiblioH* charger_n_entrees(char* nomfic, int n,int m) {
    BiblioH *bib = creer_biblio(m);
    
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
        inserer(bib, num, titre, auteur);
    }
    
    fclose(f);
    return bib;
}

void enregistrer_biblio(BiblioH *b, char* nomfic){
    FILE *f=fopen(nomfic,"w");
    for(int i=0;i<b->m;i++){
    LivreH *tmp=b->T[i];
        while(tmp){
            fprintf(f,"%d %s %s %d",tmp->num,tmp->titre,tmp->auteur,tmp->clef);
            tmp=tmp->suivant;
    }   
    }
    fclose(f);
}