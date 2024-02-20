#include "EntreeSortieH.h"
#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename> \n", argv[0]);
        return 1;
    }

    FILE *fichier_1;
    fichier_1 = fopen("vitesse_exemplaire.txt", "w");
    
    if (fichier_1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    int k = 1000;
    while (k <= 20000) {
        BiblioH *bib = charger_n_entrees(argv[1], k, k/2);

        clock_t temps_initial,temps_final;
        double temps_cpu1;

        temps_initial = clock();
        ouvrage_exemplaire(bib);
        temps_final = clock();
        temps_cpu1 = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

        fprintf(fichier_1, "%d %f \n",k, temps_cpu1);

        k += 100;

        liberer_biblio(bib);
    }

    fclose(fichier_1);

    printf("Le fichier est prêt.\n");
    return 0;
}