#include "ArbreBK.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int inserer_dans_ArbreBK(ArbreBK * A, char * tmpmot){
    
    char *mot = malloc(sizeof(char) * strlen(tmpmot));
    strcpy(mot,tmpmot);/*on crée une copie du mot pour ne pas avoir de probleme de pointeur*/

    if((*A) == NULL){/*arbre vide*/
        (*A) = malloc(sizeof(NoeudBK));
        (*A)->mot = mot;
        (*A)->valeur = 0;
        (*A)->filsG = NULL;
        (*A)->frereD = NULL;
        return 1;   
    }

    int val = L((*A)->mot,mot);
    if(rechercher_NoeudBK(&(*A)->filsG, mot,val)){
        return 1;
    }
    return 0;
}

int rechercher_NoeudBK(ArbreBK * A, char* mot, int val){
    ArbreBK tmp = malloc(sizeof(NoeudBK));
    tmp->mot = mot;
    tmp->valeur = val;
    tmp->filsG = NULL;

    if((*A) == NULL){/*la racine n'avait pas de fils on insere directement ou on est arrivé au dernier frere droit*/
        tmp->frereD = NULL;
        (*A) = tmp;
        return 1;
    }

    if( val < (*A)->valeur ){/*on insere sur la gauche et on reconecte*/
        ArbreBK CopyA = (*A);/*on copie le noeud*/
        A = &tmp;/*l'adresse de A deviens celle de tmp pour que le noeud précédent A pointe sur tmp*/
        CopyA->frereD = tmp->frereD;/*Le noeud A pointe sur son frère droit*/
        tmp->frereD = CopyA;/*Le nouveau noeud pointe vers la copie de A*/
        return 1;
    }

    if(val == (*A)->valeur){/*on insere sur ce sous arbre donc on rappelle la fonction d'insertion*/
        return inserer_dans_ArbreBK(A, mot);
    }

    if( val > (*A)->valeur ){/*on continue à chercher sur la droite*/
        return rechercher_NoeudBK( &(*A)->frereD, mot, val);
    }

    printf("probleme fonction recherche noeuds n'a rien trouvé\n");
    return 0;
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste corrections, int seuil){
    if(A == NULL){
        return corrections;
    }
    else{
        int val = L(A->mot,mot);
        if( val == seuil ){
            corrections = inserer_en_tete(corrections, A->mot);
        }
        if( val < seuil ){
            liberer_Liste(&corrections);
            corrections = inserer_en_tete(corrections, A->mot);
            seuil = val;
        }
        if(A->filsG != NULL){
            ArbreBK tmp = A->filsG;
            while(tmp != NULL){
                if( (seuil*(-1) <= (tmp->valeur - val))&&((tmp->valeur - val) <= seuil) ){
                    corrections = rechercher_dans_ArbreBK(tmp, mot, corrections, seuil);
                }
                tmp = tmp->frereD;
            }
        }
    }
    return corrections;
}

int est_dans_ABK(ArbreBK A, char *mot, int val){
  if(A == NULL){
    return 0;
  }
  if(strcmp(A->mot , mot) == 0){
    return 1;
  }
  if(A->valeur == 0){/*on part du principe que l'arbre n'est pas reduit à un seul noeud*/
    return est_dans_ABK(A->filsG,mot,val);
  }
  if(A->valeur == val){
    return est_dans_ABK(A->filsG,mot,L(A->mot, mot));
  }
  if(A->valeur < val){
    return est_dans_ABK(A->frereD,mot,val);
  }
  return 0;
}

ArbreBK creer_ArbreBK(FILE * f){
    ArbreBK A = NULL;
    char texte[256];
    while(fgets(texte, 255, f) != NULL){
        if(texte[strlen(texte)-1] == '\n'){/*tout les mots sauf le dernier ont un retour chariot qu il faut retirer*/
            texte[strlen(texte)-1] = '\0';
        }
        inserer_dans_ArbreBK( &A, texte);
    }
    return A;
}

void liberer_ArbreBK(ArbreBK * A){
    ArbreBK tmp = (*A);
    if(A == NULL){
        return;
    }
    if(tmp->filsG){
        liberer_ArbreBK(&(*A)->filsG);
    }
    if(tmp->frereD){
        liberer_ArbreBK(&(*A)->frereD);
    }
    free(tmp);
    (*A)=NULL;
}

void afficher_ArbreBK(ArbreBK A, int hauteur){
    if(A == NULL){
        printf("impossible d'afficher l'arbre BK n'existe pas\n");
        return;
    }
    int i;
    for(i=1;i<hauteur;i++){
        printf("        ");
    }
    if(A->valeur == 0){
        printf("'%s'\n",A->mot);
    }
    else{
        printf("|--%d--> '%s'\n",A->valeur,A->mot);
    }
    if(A->filsG != NULL){
        afficher_ArbreBK(A->filsG, hauteur+1);
    }
    if(A->frereD != NULL){
        afficher_ArbreBK(A->frereD, hauteur);
    }
    return;
}