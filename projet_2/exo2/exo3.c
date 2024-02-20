#include "EntreeSortieH.h"
#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <filename> <number_of_entries>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[2]);

    FILE *fichier_1;
    FILE *fichier_2;
    FILE *fichier_3;
    fichier_1 = fopen("vitesse_recherche_num.txt", "w");
    fichier_2 = fopen("vitesse_recherche_titre.txt", "w");
    fichier_3 = fopen("vitesse_recherche_auteur.txt", "w");
    
    if (fichier_1 == NULL || fichier_2 == NULL || fichier_3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
   
    int i = 0;
    while (i < n) {
        fprintf(fichier_1, "%d ", i);
        fprintf(fichier_2, "%d ", i);
        fprintf(fichier_3, "%d ", i);

        int k = 10;
        while (k <= n) {
            BiblioH *bib = charger_n_entrees(argv[1], n, k);

            clock_t temps_initial, temps_final;
            double temps_cpu1, temps_cpu2, temps_cpu3;

            temps_initial = clock();
            LivreH* l = recherche_ouvrage_num(bib, i);
            temps_final = clock();
            temps_cpu1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

            char* titre = l->titre;
            temps_initial = clock();
            recherche_ouvrage_titre(bib, titre);
            temps_final = clock();
            temps_cpu2 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

            char* auteur = l->auteur;
            temps_initial = clock();
            recherche_ouvrages_auteur(bib, auteur);
            temps_final = clock();
            temps_cpu3 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

            fprintf(fichier_1, "%f ", temps_cpu1);
            fprintf(fichier_2, "%f ", temps_cpu2);
            fprintf(fichier_3, "%f ", temps_cpu3);

            k *= 10;

            liberer_biblio(bib);
        }
        fprintf(fichier_1, "\n");
        fprintf(fichier_2, "\n");
        fprintf(fichier_3, "\n");
        i += 10;
    }
    fclose(fichier_1);
    fclose(fichier_2);
    fclose(fichier_3);
    printf("Les fichiers sont prêts.\n");
    return 0;
}
