#ifndef WORD_H
#define WORD_H
#define SEP " ,.-"   
#include <stdio.h>

#define maxSizeWord 25

extern char *separators; 
extern unsigned int current_line;
extern unsigned int current_col; 

typedef struct emplacement_t emplacement_t;
struct emplacement_t {
  unsigned int line;
  unsigned int colonne;
  emplacement_t* next;
};

typedef struct mot_data_t mot_data_t;
struct mot_data_t {
  char lemot[maxSizeWord];
  emplacement_t* tete_liste;
  emplacement_t* queue_liste;
};

typedef struct mot_t mot_t;
struct mot_t {
  int lehash;
  mot_data_t data;
};

/**
 * @brief Récupère le prochain mot dans un fichier.
 * 
 * Cette fonction lit un fichier et extrait le prochain mot, en mettant à jour
 * les lignes et colonnes.
 * 
 * @param f Fichier à lire.
 * @param nblin Pointeur vers le nombre de lignes.
 * @param nbcol Pointeur vers le nombre de colonnes.
 * @return Le mot extrait.
 */
char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol);

/**
 * @brief Incrémente la position d'un mot dans la liste des emplacements.
 * 
 * Cette fonction enregistre une nouvelle occurrence d'un mot avec sa position.
 * 
 * @param location Pointeur vers l'emplacement du mot.
 * @param line Numéro de la ligne.
 * @param colonne Numéro de la colonne.
 */
emplacement_t * incWord(emplacement_t* location, unsigned int line, unsigned int colonne);

/**
 * @brief Affiche un mot dans un fichier.
 * 
 * Cette fonction affiche un mot et ses emplacements dans un fichier donné.
 * 
 * @param word Le mot à afficher.
 * @param filedes Fichir où afficher le mot.
 */
void displayWord(mot_data_t* word, FILE *filedes);

/**
 * @brief Compare deux mots.
 * 
 * Une fonction compare les données de deux mots.
 * 
 * @param w1 Premier mot.
 * @param w2 Deuxième mot.
 * @return 0 si les mots sont égaux, une valeur différente sinon.
 */
int compareWord(mot_data_t* w1, mot_data_t* w2);

void freeEmplacements(emplacement_t* tete) ;

void freeMotData(mot_data_t* motData) ;

#endif