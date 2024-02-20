#include "EntreeSortieH.h"
#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    if (argc != 4) {
        printf("Usage: %s <filename> <number_of_entries>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]);
    int m=atoi(argv[3]);
    BiblioH *bib = charger_n_entrees(argv[1], n,m);
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
                affichage_bibli(bib);
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

                inserer(bib, num, titre, auteur);
                break;
            case 3:
                printf("donner moi le numéro de l'ouvrage que vous chercher : ");
                fgets(buffer, sizeof(buffer), stdin);
                num = atoi(buffer);
                LivreH *l = recherche_ouvrage_num(bib, num);
                affichage_livre(l);
                printf("\n");
                break;
            case 4:
                printf("donner moi le titre de l'ouvrage que vous chercher : ");
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = 0; // Supprimer le saut de ligne
                LivreH *l_titre = recherche_ouvrage_titre(bib, titre);
                affichage_livre(l_titre);
                break;
            case 5:
                printf("donner moi l'auteur des ouvrages que vous chercher : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = 0; // Supprimer le saut de ligne
                BiblioH* b_auteur = recherche_ouvrages_auteur(bib, auteur);
                affichage_bibli(b_auteur);
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
                BiblioH *b = creer_biblio(1);
                inserer(b, 300, "methode_x", "melin");
                fusion_2_biblio(bib, b);
                liberer_biblio(b);
                break;
            }
            case 8: {
                LivreH* l=ouvrage_exemplaire(bib);
                LivreH* tmp=l;
                while(tmp){
                    affichage_livre(tmp);
                    tmp=tmp->suivant;
                    printf("\n");
                }
                tmp=l;
                while(l){
                    l=l->suivant;
                    liberer_livre(tmp);
                    tmp=l;
                } 
                break;
            }
            case 9: {
                BiblioH *b = creer_biblio(m);
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
