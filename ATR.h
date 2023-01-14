#ifndef ATR_H
#define ATR_H
#include <stdio.h>
#include <stdlib.h>
#include "listes.h"

typedef struct noeud{
    char c;/*lettre contenue dans le noeud*/
    struct noeud* fg;
    struct noeud* fc;
    struct noeud* fd;
    /*fils gauche, centre, droit*/
}Noeud, *ATR;

ATR creer_ATR_vide();
/**
 * BUT: 
 * initialise et alloue une variable ATR vide
 * PARAMETRES:
 */
void liberer_ATR(ATR A);
/**
 * BUT: 
 * libère la mémoire occupée par la variable ATR et toutes ses branches
 * PARAMETRES:
 * ATR à free
 */ 
ATR alloue_noeud(char c);
/**
 * BUT: 
 * alloue la mémoire pour un noeud de l'ATR
 * PARAMETRES:
 * lettre contenue dans le noeud
 */
ATR alloue_mot(char mot[]);
/**
 * BUT: 
 * alloue la mémoire pour une branche de l'ATR noeud par noeud à l'aide de alloue_noeud
 * PARAMETRES:
 * le mot contenu dans la branche
 */
void inserer_dans_ATR(Noeud* A, char* mot);
/**
 * BUT: inserer le une branche contenant un mot dans un ATR, la branche est crée avec alloue_mot 
 * et inserée dans l'ATR noeud par noeud par un appel récursif
 * PARAMETRES:
 * ATR dans lequel la branche va être inserée 
 * mot contenue dans la branche
 */
int supprimer_dans_ATR(Noeud* A, char* mot);
/**
 * BUT: 
 * supprimer un mot de l'ATR -> appel recursif de la fonction pour chaque noeuds de la racine vers 
 * la derniere feuille '\0' -> la branche se supprime de bas en haut jusqu'à la derniere bifurcation pour ne pas 
 * supprimer de noeuds communs à d'autres mots
 * PARAMETRES:
 * adresse de l'ATR
 * mot à retirer
 */
void afficher_ATR(ATR A, char *mot, int i);
/**
 * BUT: 
 * afficher un ATR en recollant lettre par lettre les differents mots contenu dedans ( par appel recursif )
 * PARAMETRES:
 * l'ATR à afficher
 * un entier mis à 0 et un mot vide lors du premier appel de la fonction, le mot va se former lettre par lettre
 * et l'entier servira de compteur tout au long des appels recursifs
 */
int rechercher_dans_ATR(Noeud* A, char* mot);
/**
 * BUT: 
 * va rechercher le mot dans l'ATR lettre par lettre ( noeud par noeud ) par appel recursif et return 0/1
 * si le mot est dans l'ATR ou non
 * PARAMETRES:
 * l'ATR dans lequel le mot va être recherché
 * le mot à chercher
 */
Liste ATR_vers_liste(ATR A, char* mot, int i, Liste L);

#endif