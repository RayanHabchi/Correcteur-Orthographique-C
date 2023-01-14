#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ATR.h"
#include "listes.h"
#include "Levenshtein.h"
#include "ArbreBK.h"

int main(int argc, char* argv[]){

/*gestion argument main*/
    if(argc != 3){
        printf("entrez 2 arguments :\n-chemin vers le texte à corriger\n-chemin vers le dico\n");
        exit(2);
    }

/*initialisation des variables*/
    int d, dmin;
    char texte[256],str[256];
    ATR A = creer_ATR_vide();
    FILE* f,*f2;
    Liste l = NULL, a_corriger = NULL, dico = NULL, corrections = NULL, correctionsBK = NULL, tmp1 = NULL, tmp2 = NULL;

/*chargement du dico*/
    f2 = fopen(argv[2],"r");
    if(f2 == NULL){
        printf("fichier non chargé\n");
        exit(1);
    }
    while(fgets(texte, 255, f2) != NULL){
        inserer_dans_ATR( A, texte);
    }
    printf("---------dico----------\n");
    afficher_ATR( A, texte, 0);

/*chargement liste des mots à corriger*/
    f = fopen(argv[1],"r");
    while(fgets(str, 255, f) != NULL){
        char separateurs[] = " ,'-.\n";/*le separateur apostrophe ne marche pas ??*/
        char *p = strtok(str, separateurs);
        while(p != NULL){
            if((p[0]>=65)&&(p[0]<=90)){
                p[0] += 32;
            }
            l = inserer_en_tete(l, p);
            p = strtok(NULL, separateurs);
        }
    }
    printf("\n\n---------mots--------\n");
    afficher_Liste(l);
    printf("\n");

/*Algorithme 1*/
    tmp1 = l;
    while(tmp1 != NULL){
        if((rechercher_dans_ATR( A, tmp1->mot) == 0)&&(rechercher_dans_Liste(a_corriger, tmp1->mot) == 0)){
            a_corriger = inserer_en_tete(a_corriger, tmp1->mot);
        }
        tmp1 = tmp1->next;
    }
    printf("\n\n----mots-à-corriger-(algo partie 1)---\n");
    afficher_Liste(a_corriger);
    printf("--------------------------------------\n\n");

/*Algorithme 2*/
    printf("----Corrections méthode brute (partie 2)----\n");
    dico = ATR_vers_liste( A, texte, 0, dico);

    tmp1 = a_corriger;
    while(tmp1 != NULL){
        tmp2 = dico;
        dmin = 999;
        while(tmp2 != NULL){
                d = L(tmp1->mot, tmp2->mot);
                if(d<=dmin){
                    if(d<dmin){
                        dmin = d;
                        liberer_Liste(&corrections);
                    }
                    corrections = inserer_en_tete(corrections, tmp2->mot);
                }
            tmp2 = tmp2->next;
        }
        printf("corrections suggerées pour %s :\n", tmp1->mot);
        afficher_Liste(corrections);
        tmp1=tmp1->next;
    }
    
/*Algorithme 3*/
    rewind(f2);/*on recommence le fichier dico comme il a deja été lu pour creer l'ATR*/
    ArbreBK ABK = creer_ArbreBK(f2);
    printf("\n\n---------------ABK-----------------\n");
    afficher_ArbreBK(ABK, 0);

    /* 1)algo 1bis (recherche des mots mal orthographiés par parcours d'ABK)*/
    tmp1 = l;
    liberer_Liste(&a_corriger);
    while(tmp1 != NULL){
        d=L(tmp1->mot,ABK->mot);
        if((est_dans_ABK( ABK, tmp1->mot, d) == 0)&&(rechercher_dans_Liste(a_corriger, tmp1->mot) == 0)){
            d=L(tmp1->mot,ABK->mot);
            a_corriger = inserer_en_tete(a_corriger, tmp1->mot);
        }
        tmp1 = tmp1->next;
    }

    printf("\n\n---mots-à-corriger-(algo 1-bis - parcours ABK)--------\n");
    afficher_Liste(a_corriger);
    printf("--------------------------------------------------------\n\n");


    /* 2)recherche approximative des corrections*/
    tmp1 = a_corriger;
    printf("\n\ncorrection approximative par ArbreBK (seuil 2):----------\n\n");
    while(tmp1 != NULL){
        correctionsBK = rechercher_dans_ArbreBK(ABK, tmp1->mot, correctionsBK, 2);
        printf("corrections suggerées pour '%s' : \n", tmp1->mot);
        afficher_Liste(correctionsBK);
        tmp1 = tmp1->next;
    }
    
/*liberation de mémoire*/
    liberer_ATR(A);
    fclose(f);
    fclose(f2);
    liberer_Liste(&l);
    liberer_Liste(&a_corriger);
    liberer_Liste(&correctionsBK);
    liberer_Liste(&dico);
    liberer_ArbreBK(&ABK);
    return 0;
}