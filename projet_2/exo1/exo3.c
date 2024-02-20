#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <filename> <number_of_entries>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]);
    Biblio *bib = charger_n_entrees(argv[1], n);
    FILE *fichier_1;
    FILE *fichier_2;
    FILE *fichier_3;
    fichier_1= fopen("vitesse_recherhe_num.txt", "w");
    fichier_2= fopen("vitesse_recherhe_titre.txt", "w");
    fichier_3= fopen("vitesse_recherhe_auteur.txt", "w");
    int i=0;
    while(i<n){
        double temps_cpu1, temps_cpu2, temps_cpu3;

        clock_t temps_initial = clock();
        Livre* l= recherche_ouvrage_num(bib, i);
        clock_t temps_final = clock();
        temps_cpu1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(fichier_1,"%d %f \n", i, temps_cpu1);

        char* titre = l->titre;
        temps_initial = clock();
        recherche_ouvrage_titre(bib, titre);
        temps_final = clock();
        temps_cpu2 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(fichier_2,"%d %f \n", i, temps_cpu2);

        char* auteur = l->auteur;
        temps_initial = clock();
        recherche_ouvrages_auteur(bib, auteur);
        temps_final = clock();
        temps_cpu3 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(fichier_3,"%d %f \n", i, temps_cpu3);

        i=i+10;
    }

    fclose(fichier_3);
    fclose(fichier_2);
    fclose(fichier_1);
    liberer_biblio(bib);
    printf("les fichiers sont prets \n");
    return 0;
}