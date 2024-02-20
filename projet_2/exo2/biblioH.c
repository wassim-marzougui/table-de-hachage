#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int fonctionClef(char* auteur){
    int somme=0;
    int i=0;
    while(auteur[i]!='\0'){
        somme+=(int)auteur[i];
        i=i+1;
    }
    return somme;
}

LivreH* creer_livre(int num,char* titre,char* auteur){
    LivreH *l=(LivreH*)malloc(sizeof(LivreH));
    l->num=num;
    l->titre=strdup(titre);
    l->auteur=strdup(auteur);
    l->clef=fonctionClef(auteur);
    return l;
}
void liberer_livre(LivreH* l){
        free(l->titre);
        free(l->auteur);
        free(l);
}
BiblioH* creer_biblio(int m){
    BiblioH *biblio=(BiblioH*)malloc(sizeof(BiblioH));
    biblio->nE=0;
    biblio->m=m;
    biblio->T=(LivreH**)(malloc(sizeof(LivreH*)*m));
    for(int i=0;i<m;i++){
        biblio->T[i]=NULL;
    }
    return biblio;
}
void liberer_biblio(BiblioH* b){
    for(int i=0; i<b->m;i++){
        LivreH *tmp=b->T[i];
        LivreH *tmp1=NULL;
        while (tmp){
            tmp1=tmp->suivant;
            liberer_livre(tmp);
            tmp=tmp1;
        }
        
    }
    free(b->T);
    free(b);
}

int fonctionHachage(int cle, int m){
    float A=((sqrt(5)-1)/2);
    return (int)floor((m*(cle*A-(floor(cle*A)))));
}

void inserer(BiblioH* b,int num,char* titre,char* auteur){
    LivreH* new=creer_livre(num,titre,auteur);
    int pos=fonctionHachage(new->clef,b->m);
    new->suivant=b->T[pos];
    b->T[pos]=new;
    b->nE+=1;
}

void affichage_livre(LivreH* l){
    if (!l){
        printf("!!!vide!!!");
    }
    else{
        printf("%d => %d : %s (%s) \n",l->clef,l->num,l->titre,l->auteur);
    }
}
void affichage_bibli(BiblioH *b){
    printf("le nombre de livres dans cette bibliothèque est : %d \n",b->nE);
    for(int i=0;i<b->m;i++){
        LivreH* tmp=b->T[i];
        while(tmp){
            affichage_livre(tmp);
            tmp=tmp->suivant;
        } 
    }
}

LivreH* recherche_ouvrage_num(BiblioH* b,int num){
    for(int i=0;i < b->m;i++){
        LivreH *tmp=b->T[i];
        while (tmp)
        {
            if((tmp->num)==num){
                return tmp;
            }else{
                tmp=tmp->suivant;
            }
        }
        
    }
    return NULL;
}

LivreH* recherche_ouvrage_titre(BiblioH* b,char *titre){
        for(int i=0;i < b->m;i++){
        LivreH *tmp=b->T[i];
        while (tmp)
        {
            if(strcmp((tmp->titre),titre)== 0){
                return tmp;
            }else{
                tmp=tmp->suivant;
            }
        }
        
    }
    return NULL;
}
BiblioH* recherche_ouvrages_auteur(BiblioH* b ,char *auteur){
    BiblioH *newb=creer_biblio(1);
    LivreH *tmp=b->T[fonctionHachage(fonctionClef(auteur),b->m)];
    while (tmp){
        inserer(newb,tmp->num,tmp->titre,auteur);
        tmp=tmp->suivant;
    }
    return newb;
}

void suppression_ouvrage(BiblioH *b,int num,char* titre,char* auteur){
    int pos=fonctionHachage(fonctionClef(auteur),b->m);
    LivreH *tmp=b->T[pos];
    LivreH *pred=NULL;
    while (tmp){
        if((strcmp(tmp->auteur,auteur)==0)&&(strcmp(tmp->titre,titre)==0)&&(tmp->num==num)){
            if(pred){
                pred->suivant=tmp->suivant;
                liberer_livre(tmp);
                tmp=pred->suivant;
            }else{
                b->T[pos]=tmp->suivant;
                liberer_livre(tmp);
                tmp=b->T[pos];
            }
            b->nE=b->nE-1;
        }else{
            pred=tmp;
            tmp=tmp->suivant;
        }
    }

}

void fusion_2_biblio(BiblioH *b1,BiblioH *b2){
    for(int i=0;i<b2->m;i++){
        LivreH* tmp=b2->T[i];
        while(tmp){
            inserer(b1,tmp->num,tmp->titre,tmp->auteur);
        }
    }    
}

LivreH* ouvrage_exemplaire(BiblioH *b){
    LivreH *new=NULL;
    for(int i=0;i<b->m;i++){
        LivreH* tmp=b->T[i];
        while(tmp){
            LivreH* tmp2=b->T[i];
            while (tmp2){
                if ((tmp2->num!=tmp->num)&&(strcmp(tmp2->titre,tmp->titre)==0)&&strcmp(tmp2->auteur,tmp->auteur)==0){
                    LivreH *tmp3=creer_livre(tmp->num,tmp->titre,tmp->auteur);
                    tmp3->clef=tmp->clef;
                    tmp3->suivant=new;
                    new=tmp3;
                }
                tmp2=tmp2->suivant;
            }
        tmp=tmp->suivant;
        }
    }
    return new;
}



