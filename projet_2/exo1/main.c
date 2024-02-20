#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
    printf("Menu :\n");
    printf("0 - Sortie du programme\n");
    printf("1 - Affichage de la bibliothèque\n");
    printf("2 - Insérer un ouvrage\n");
    printf("3 - Rechercher un ouvrage par numéro\n");
    printf("4 - Rechercher un ouvrage par titre\n");
    printf("5 - Rechercher les ouvrages d'un auteur\n");
    printf("6 - Supprimer un ouvrage\n");
    printf("7 - Fusionner deux bibliothèques\n");
    printf("8 - Rechercher les ouvrages avec plusieurs exemplaires\n");
    printf("9 - Enregistrer la bibliothèque dans un fichier\n");
    printf("\nChoisissez une action : ");
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <filename> <number_of_entries>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]);
    Biblio *bib = charger_n_entrees(argv[1], n);
    int choix = -1;
    while (choix != 0) {
        menu();
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        choix = atoi(buffer);
        
        int num;
        char titre[50];
        char auteur[20];
        switch (choix) {
            case 0:
                printf("Sortie du programme.\n");
                break;
            case 1:
                affichage_biblio(bib);
                break;
            case 2:
                printf("donner moi le numéro de l'ouvrage : ");
                fgets(buffer, sizeof(buffer), stdin);
                num = atoi(buffer);

                printf("donner moi le titre de l'ouvrage : ");
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = 0; // Supprimer le saut de ligne
               
                printf("donner moi l'auteur de l'ouvrage : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = 0; // Supprimer le saut de ligne

                inserer_en_tete(bib, num, titre, auteur);
                break;
            case 3:
                printf("donner moi le numéro de l'ouvrage que vous chercher : ");
                fgets(buffer, sizeof(buffer), stdin);
                num = atoi(buffer);
                Livre *l = recherche_ouvrage_num(bib, num);
                affichage_livre(l);
                printf("\n");
                break;
            case 4:
                printf("donner moi le titre de l'ouvrage que vous chercher : ");
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = 0; // Supprimer le saut de ligne
                Livre *l_titre = recherche_ouvrage_titre(bib, titre);
                affichage_livre(l_titre);
                break;
            case 5:
                printf("donner moi l'auteur des ouvrages que vous chercher : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = 0; // Supprimer le saut de ligne
                Biblio* b_auteur = recherche_ouvrages_auteur(bib, auteur);
                affichage_biblio(b_auteur);
                liberer_biblio(b_auteur);
                break;
            case 6:
                printf("donner moi le numéro de l'ouvrage à supprimer : ");
                fgets(buffer, sizeof(buffer), stdin);
                num = atoi(buffer);

                printf("donner moi le titre de l'ouvrage à supprimer : ");
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = 0; // Supprimer le saut de ligne

                printf("donner moi l'auteur de l'ouvrage à supprimer : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = 0; // Supprimer le saut de ligne

                suppression_ouvrage(bib, num, titre, auteur);
                break;
            case 7: {
                Biblio *b = creer_biblio();
                inserer_en_tete(b, 300, "methode_x", "melin");
                fusion_2_biblio(bib, b);
                liberer_biblio(b);
                break;
            }
            case 8: {
                Biblio *b=creer_biblio();
                Livre* l=ouvrage_exemplaire(bib);
                b->L=l;
                affichage_biblio(b);
                liberer_biblio(b);
                break;
            }
            case 9: {
                Biblio *b = creer_biblio();
                enregistrer_biblio(b, "res_exmplaire.txt");
                liberer_biblio(b);
                break;
            }
            default:
                printf("Choix invalide.\n");
        }
    }

    liberer_biblio(bib);

    return 0;
}

