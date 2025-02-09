#ifndef JSON_H
#define JSON_H

#include "word.h"

/**
 * @brief Crée un objet JSON à partir des données du dictionnaire.
 * 
 * Convertit une table de données de mots en un objet JSON.
 * 
 * @param d Tableau de mots à convertir en JSON.
 * @return Un objet JSON représentant les mots.
 */
struct json_object *createJSON(mot_data_t **d);

/**
 * @brief Extrait les données de mots d'un objet JSON.
 * 
 * Convertit un objet JSON en une table de mots.
 * 
 * @param o L'objet JSON à traiter.
 * @return Tableau de mots extraits du JSON.
 */
mot_data_t **extractJSON(struct json_object *o);

#endif