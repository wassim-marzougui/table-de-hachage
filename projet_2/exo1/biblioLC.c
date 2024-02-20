#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Livre* creer_livre(int num,char* titre,char* auteur){
    Livre *l=(Livre*)malloc(sizeof(Livre));
    l->num=num;
    l->titre=strdup(titre);
    l->auteur=strdup(auteur);
    return l;
}
void liberer_livre(Livre* l){
        free(l->titre);
        free(l->auteur);
        free(l);
}

Biblio* creer_biblio(){
    Biblio *biblio=(Biblio*)malloc(sizeof(Biblio));
    biblio->L=NULL;
    return biblio;
}
void liberer_biblio(Biblio* b){
    Livre *tmp=b->L;
    while(b->L){
        b->L=b->L->suiv;
        liberer_livre(tmp);
        tmp=b->L;
    }
    free(b);
}
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre *new=creer_livre(num,titre,auteur);
    new->suiv=b->L;
    b->L=new;
}

void affichage_livre(Livre* l){
    if (!l){
        printf("!!!vide!!!");
    }
    else{
        printf(" %d : %s (%s)",l->num,l->titre,l->auteur);
    }
}

void affichage_biblio(Biblio* b){
    if (!b){
        printf("!!!vide!!!");
    }
    else{
        while (b->L){
            affichage_livre(b->L);
            printf("\n");
            b->L=b->L->suiv;
        }
    }
}
Livre* recherche_ouvrage_num(Biblio* b,int num){
    Livre* tmp = b->L;
    while(tmp){
        if(tmp->num==num){
            return tmp;
        }
        tmp=tmp->suiv;
    }
    return tmp;
}

Livre* recherche_ouvrage_titre(Biblio* b,char* titre){
    Livre* tmp = b->L;
    while(tmp){
        if(strcmp(tmp->titre,titre)==0){
            return tmp;
        }
        tmp=tmp->suiv;
    }
    return tmp;
}

Biblio* recherche_ouvrages_auteur(Biblio* b ,char *auteur){
    Biblio* new=creer_biblio();
    Livre* tmp = b->L;
    while (tmp){
        if(strcmp(tmp->auteur,auteur)==0){
            inserer_en_tete(new,tmp->num,tmp->titre,auteur);
        }
        tmp=tmp->suiv;
    }
    return new;
}

void suppression_ouvrage(Biblio *b,int num,char* titre,char* auteur){
    Livre* tmp = b->L;
    Livre* pred=NULL;
    while (tmp){
        if((strcmp(tmp->auteur,auteur)==0)&&(strcmp(tmp->titre,titre)==0)&&(tmp->num==num)){
            if(pred){
                pred->suiv=tmp->suiv;
                liberer_livre(tmp);
                tmp=pred->suiv;
            }else{
                b->L=tmp->suiv;
                liberer_livre(tmp);
                tmp=b->L;
            }
        }else{
            pred=tmp;
            tmp=tmp->suiv;
        }
    }
}

void fusion_2_biblio(Biblio *b1,Biblio *b2){
    if (!(b1->L)){
        b1->L=b2->L;
    }
    else{
        Livre* tmp=b1->L;
    
        while(tmp->suiv){
            tmp=tmp->suiv;
        }
    tmp->suiv=b2->L;
    }
    free(b2);
}

Livre* ouvrage_exemplaire(Biblio *b){
    Biblio* b2=creer_biblio();
    Livre* tmp=b->L;
    while(tmp){
        Livre* tmp2=b->L;
        while (tmp2){
            if ((tmp2->num!=tmp->num)&&(strcmp(tmp2->titre,tmp->titre)==0)&&strcmp(tmp2->auteur,tmp->auteur)==0){
                inserer_en_tete(b2,tmp->num,tmp->titre,tmp->auteur);
            }
            tmp2=tmp2->suiv;
        }
        tmp=tmp->suiv;
    }
    return (b2->L);
}