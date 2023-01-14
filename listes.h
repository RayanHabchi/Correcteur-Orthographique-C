#ifndef LISTES_H
#define LISTES_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cellule{
    char* mot;
    struct cellule *next; 
} Cellule,*Liste;

Cellule* allouer_Cellule(char * mot);
/**
 * BUT: alloue la mémoire pour une cellule de la liste chainée
 * en faisant attention à faire une copie du mot pour éviter les problèmes de pointeurs
 * puis renvoie l'adresse de la Cellule
 * PARAMETRES: chaine de caractère contenue dans la céllule
 */
Liste inserer_en_tete(Liste L, char *mot);
/**
 * BUT: crée une cellule en appelant allouer_Cellule puis chaine cette Cellule
 * en tete de la liste L, puis renvoie la nouvelle liste
 * PARAMETRES: mot contenu dans la cellule et liste L
 */
void liberer_Liste(Liste *L);
/**
 * BUT: libère la mémoire allouée à la liste
 * 
 * PARAMETRES: liste L à désallouer
 */
void afficher_Liste(Liste L);
/**
 * BUT: affiche la liste sur le terminal
 * 
 * PARAMETRES: liste L à afficher
 */
int rechercher_dans_Liste(Liste L, char* mot);
/**
 * BUT: recherche un mot dans une liste et renvoie 1
 * si le mot est dans la liste, sinon 0
 * PARAMETRES: La chaine de caractère à rechercher et
 * la liste L dans laquelle on la cherche
 */

#endif