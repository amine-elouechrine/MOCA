#ifndef DICO_H
#define DICO_H
#include "word.h"

typedef struct dico dico;
struct dico {
  mot_t* mot;
  dico *fg, *fd;
};

/**
 * @brief Insère un mot dans le dictionnaire.
 * 
 * Cette fonction insère un mot dans l'arbre binaire du dictionnaire.
 * 
 * @param dictionary Pointeur vers le dictionnaire.
 * @param linkWord Pointeur vers le mot à insérer.
 */
void insertDico(dico** dictionary, mot_t* linkWord);

/**
 * @brief Ajoute un mot au dictionnaire.
 * 
 * Ajoute un mot en créant une nouvelle entrée dans l'arbre et en enregistrant
 * sa position (ligne, colonne).
 * 
 * @param dictionary Pointeur vers le dictionnaire.
 * @param word Le mot à ajouter.
 * @param line Pointeur vers la ligne du mot.
 * @param colonne Pointeur vers la colonne du mot.
 */
void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne);

/**
 * @brief Affiche les mots du dictionnaire.
 * 
 * Cette fonction parcourt l'arbre et affiche tous les mots stockés.
 * 
 * @param dictionary Pointeur vers le dictionnaire.
 */
void displayDico(dico* dictionary);

/**
 * @brief Sérialise le dictionnaire.
 * 
 * Convertit l'arbre binaire du dictionnaire en une structure linéaire.
 * 
 * @param dictionary Pointeur vers le dictionnaire.
 * @param table Tableau de mots sérialisés.
 */
void serializeDico(dico * dictionary, mot_data_t **table);

/**
 * @brief Désérialise un dictionnaire.
 * 
 * Reconstruit l'arbre binaire du dictionnaire à partir d'une structure linéaire.
 * 
 * @param dic Pointeur vers le dictionnaire à reconstruire.
 * @param elt Tableau de mots désérialisés.
 */
void deserializeDico(dico** dic, mot_data_t *elt);

/**
 * @brief Affiche les nœuds du dictionnaire dans un fichier.
 * 
 * Cette fonction effectue un parcours en profondeur de l'arbre binaire et
 * affiche chaque nœud dans un fichier.
 * 
 * @param d Pointeur vers le dictionnaire.
 * @param f Fichier de destination pour l'affichage.
 */
void displayNodes(dico *d, FILE* f);

#endif