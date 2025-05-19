#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <math.h>

#define MaxSizeArray 16381

/**
 * @brief Calcule le hash d'un mot.
 * 
 * Cette fonction génère un code hash à partir d'une chaîne de caractères.
 * 
 * @param m Le mot.
 * @return La valeur.
 */
int hash(char *m);

#endif