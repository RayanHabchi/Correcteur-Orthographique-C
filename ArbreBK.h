#ifndef ARBREBK_H
#define ARBREBK_H
#include "listes.h"
#include "Levenshtein.h"

typedef struct NoeudBK {
    char * mot;
    int valeur;
    struct NoeudBK * filsG;
    struct NoeudBK * frereD;
} NoeudBK, * ArbreBK;

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);
/**
 * BUT: insere un mot dans un arbreBK, en appelant la fonction rechercher_dans_ArbreBK
 * avec la distance de Levenstein entre le mot et la racine de l'arbre
 * PARAMETRES: mot à inserer et ArbreBK dans lequel on l'insere
 */
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste corrections, int seuil);
/**
 * BUT: rechercher de maniere approximée les meilleurs correction orthographique d'un mot.
 * En utilisant les propriété de la distance de Levenstein en tant que norme on peut considerer ( suivant le seuil 
 * d'approximation ) que certains sous arbres ne doivent pas être explorer. Ainsi, on parcours les branches de l'arbre interressantes
 * et on garde les meilleurs corrections ( les plus proches du mot ).
 * PARAMETRES: l'ABK dans lequel on effectue la recherche, le mot à corriger, le seuil d'approximation
 * et la liste dans laquelle on insere les correction, c'est cette liste qui est aussi return.
 */
int rechercher_NoeudBK(ArbreBK * A, char* mot, int val);
/**
 * BUT: inserer le mot dans le bon sous arbre ou crée la nouvelle sous branche, en fonction de la distance
 * entre le mot et la racine ( passée en paramètre depuis la fonction inserer_dans_ArbreBK)
 * PARAMETRES: l'arbre Bk et le mot à inserer, et la distance entre le mot et la racine
 */
int est_dans_ABK(ArbreBK A, char *mot, int val);
/**
 * BUT: recherche un mot dans un arbre ABK
 * PARAMETRES: l'ABK et le mot à rechercher, return 1 si le mot est dans l'ABK, 0 sinon
 */
ArbreBK creer_ArbreBK(FILE * f);
/**
 * BUT: découpe le dico en mot et les insere un par un dans l'arbreBK en appelant la fonction inserer_dans_ArbreBK
 * PARAMETRES: le fichier contenant le dico
 */
void liberer_ArbreBK(ArbreBK * A);
/**
 * BUT: 
 * libère la mémoire occupée par la variable ArbreBK et toutes ses branches
 * PARAMETRES:
 * Arbre à free
 */ 
void afficher_ArbreBK(ArbreBK A, int hauteur);
/**
 * BUT: Affiche l'arbreBK en suivant un parcours préfixe
 * PARAMETRES: l'arbre à afficher et la hauteur de cet arbre si c'est un noeud de l'arbre 
 * principal ( pour pouvoir indenter )
 */


#endif