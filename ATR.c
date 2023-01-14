#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ATR.h"
#include "listes.h"

ATR creer_ATR_vide(){
    Noeud* tmp = malloc(sizeof(*tmp));
    if(tmp == NULL){
        printf("erreur allocation ATR-vide\n");
        exit(EXIT_FAILURE);
    }
    return tmp;
}

void liberer_ATR(ATR A){
    if(NULL == A){
        return;
    }
    liberer_ATR(A->fg);
    liberer_ATR(A->fc);
    liberer_ATR(A->fd);
    free(A);
    return;
}

ATR alloue_noeud(char c){
    Noeud* noeud;
    noeud = malloc(sizeof(*noeud));
    if(noeud == NULL){
        return NULL;
    }
    noeud->c = c;
    noeud->fg = NULL;
    noeud->fc = NULL;
    noeud->fd = NULL;
    return noeud;
}

ATR alloue_mot(char mot[]){
    ATR noeud, lettre, lettre_suivante;
    int i;
    if (NULL == mot){
        return NULL;
    }
    noeud = alloue_noeud(mot[0]);
    lettre = noeud;
    for (i = 1 ; i <  strlen(mot)-1 ; i ++){
        lettre_suivante = alloue_noeud(mot[i]);
        lettre->fc = lettre_suivante;
        lettre = lettre->fc;
    }
    lettre_suivante = alloue_noeud('\0');
    lettre->fc = lettre_suivante;
    return noeud;
}

void inserer_dans_ATR(Noeud* A, char* mot){
    char c = *mot;
    if (A == NULL){
        return;
    }
    if(*mot == '\0' || *mot == '\n' || *mot == '\t'){
        c = '\0';

    }
    if(A->c == *mot){
        if (A->fc == NULL){
            A->fc = alloue_noeud(-1);/*-1 car pas de lettre dedans*/
        }
    inserer_dans_ATR(A->fc, mot + 1);
    }
    else if(A->c == -1){
        A->c = c;
        if(c == '\0'){
            return;
        }
        if (A->fc == NULL){
            A->fc = alloue_noeud(-1);/*-1 car pas de lettre dedans*/
        }
        inserer_dans_ATR(A->fc, mot + 1);
    
    }
    else if(A->c > *mot){
        if(A->fg == NULL){
            A->fg = alloue_noeud(-1);
        }
        inserer_dans_ATR(A->fg, mot);

    }
    else if(A->c < *mot){
        if(A->fd == NULL){
            A->fd = alloue_noeud(-1);
        }
        inserer_dans_ATR(A->fd, mot);
    }
}

int supprimer_dans_ATR(Noeud* A, char* mot){
    /*on verifie que le mot est dedans*/
    if (rechercher_dans_ATR(A, mot) == 0){
        return 0;
    }
    /*fin de mot -> on peut supprimmer jusqu'à la dernière bifurcation*/
    if (strlen(mot) == 0){
        free(A->fc);
        if((A->fg == NULL)&&(A->fd == NULL)){/*on verifie si il n'y a pas une branche sous jacente au dernier noeud*/
            free(A);
            return 1;
        }
        else{
            return 0;
        }
        
    }
        
    /*pas de bifurcation -> potentiellement supprimable, en attente du '\0'*/
    if ((A->fc->c == *mot+1) && (A->fg == NULL) && (A->fd == NULL)){
        if (supprimer_dans_ATR(A->fc, mot+1)){
            free(A);
            /*il n'y a pas bifurcation entre ce noeud et le '\0' -> suppression des noeuds jusqu'à la derniere bifurcation*/
            return 1;
        }
        else{
            /*il y a une bifurcation plus bas, on ne supprime pas ces noeuds ni ceux plus haut*/
            return 0;
        }
    }

    /*il y'a bifurcation -> on regarde si c'est la derniere avant le '\0' auquel cas on supprime la branche sous jacente*/
    if ((A->fc->c < *mot+1) || ((A->fc->c == '\0')&&(strlen(mot)!=0))){/*le mot continue sur la droite*/
        supprimer_dans_ATR(A->fd, mot+1);
        return 0;
    }
    if (A->fc->c > *mot+1){/*le mot continue sur la gauche*/
        supprimer_dans_ATR(A->fg, mot+1);
        return 0;
    }
    return 0;
}

void afficher_ATR(ATR A, char *mot, int i){
    if (A->c == '\0'){ /* condition d'arret fin de mot */
        strcat(mot, "\n");
        printf("%s", mot);
    }
    if (A->fg != NULL){/* cas ou il y a un frere gauche */
        afficher_ATR(A->fg, mot, i);
    }
    if (A->fc != NULL){
        mot[i] = A->c; /* recupere chaque lettre pour ne pas oublier les prefixe */
        mot[i+1] = '\0';
        afficher_ATR(A->fc, mot, i+1);
    }
    if (A->fd != NULL){/* cas ou il ya un frere droit */
        afficher_ATR(A->fd, mot, i);
    }
}

int rechercher_dans_ATR(Noeud* A, char* mot){
    if (A == NULL || mot == NULL){
        return 0;
    }
    if(*mot == '\0' && A->c == '\0'){
        return 1;
    }

    if (A->c == *mot){
        return rechercher_dans_ATR(A->fc, mot+1 );
    }
    if (A->c < *mot){
        return rechercher_dans_ATR(A->fd, mot);
    }
    if (A->c > *mot){
        return rechercher_dans_ATR(A->fg, mot);
    }
    return 0;
}

Liste ATR_vers_liste(ATR A, char* mot, int i, Liste L){
    if (A->c == '\0'){ /* condition d'arret fin de mot */
        L = inserer_en_tete(L, mot);
    }
    if (A->fg != NULL){/* cas ou il y a un frere gauche */
        L = ATR_vers_liste(A->fg, mot, i, L);
    }
    if (A->fc != NULL){
        mot[i] = A->c; /* recupere chaque lettre pour ne pas oublier les prefixe */
        mot[i+1] = '\0';
        L = ATR_vers_liste(A->fc, mot, i+1, L);
    }
    if (A->fd != NULL){/* cas ou il ya un frere droit */
        L = ATR_vers_liste(A->fd, mot, i, L);
    }
    return L; 
}
