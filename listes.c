#include "listes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Cellule * allouer_Cellule(char * mot){
    
    Cellule* tmp = (Cellule *) malloc(sizeof(Cellule));
    if (tmp == NULL){
        printf("erreur alloc\n");
        exit(1);
    }
    char *tmpmot = malloc(sizeof(char) * strlen(mot));
    
    strcpy(tmpmot,mot);
    tmp->mot = tmpmot;
    tmp->next = NULL;
    return tmp;
}

Liste inserer_en_tete(Liste L, char *mot){
    Cellule *cell = allouer_Cellule(mot);
    if (L == NULL){
        cell->next = NULL;
        return cell;
    }
    cell->next = L;
    return cell;
}

void liberer_Liste(Liste *L){
  while((*L) != NULL){
    Cellule *tmp;
    tmp = malloc(sizeof(*tmp));
    if(tmp == NULL){
      fprintf(stderr,"erreur alloc\n");
      exit(EXIT_FAILURE);
    }
    tmp = (*L)->next;
    free((*L));
    (*L) = tmp;
  }
  return;
}

void afficher_Liste(Liste L){
    Cellule* tmp = L;
    while(tmp != NULL){
        printf("'%s' ", tmp->mot);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}

int rechercher_dans_Liste(Liste L, char* mot){
    int i=0, c=0;
    Cellule* tmp = L;
    while(tmp != NULL){
        if(strlen(tmp->mot) == strlen(mot)){
            for(i=0; i<strlen(mot); i++){
                if(tmp->mot[i] == mot[i]){
                    c+=1;
                }
            }
            if(c==strlen(mot)){
                return 1;
            }
            c = 0;
        }
        tmp = tmp->next;
    }
    return 0;
}