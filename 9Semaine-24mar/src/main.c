#include <stdio.h>
#include <stdlib.h>
#include "dico.h"
#include "word.h"
#include "hash.h"

#ifdef FICJSON
#include "json.h"
#endif

#define TEXTE "hugo1.txt"

// Fonction pour libérer récursivement le dictionnaire
void freeDico(dico* dic) {
    if (dic == NULL) return;
    freeDico(dic->fg); // Libérer le sous-arbre gauche
    freeDico(dic->fd); // Libérer le sous-arbre droit
    free(dic->mot);    // Libérer le mot
    free(dic);         // Libérer le nœud
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        exit(1);
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    unsigned int* line = (unsigned int*) malloc(sizeof(int));
    if (line == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour la ligne\n");
        exit(1);
    }

    unsigned int* colonne = (unsigned int*) malloc(sizeof(int));
    if (colonne == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour la colonne\n");
        free(line); // Libérer line en cas d'erreur
        exit(1);
    }

    char* word = (char*) malloc(sizeof(char) * maxSizeWord);
    if (word == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour le mot\n");
        free(line);
        free(colonne);
        exit(1);
    }

    dico* dictionary = (dico*) malloc(sizeof(dico));
    if (dictionary == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour le dictionnaire\n");
        free(line);
        free(colonne);
        free(word);
        exit(1);
    }
    dictionary->mot = NULL;
    dictionary->fg = NULL;
    dictionary->fd = NULL;

    dico* copiedico = NULL;

    mot_data_t **serialized_dico = (mot_data_t **)malloc(MaxSizeArray * sizeof(mot_data_t *));
    if (serialized_dico == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour le tableau de mots\n");
        free(line);
        free(colonne);
        free(word);
        free(dictionary);
        exit(1);
    }

    free(word); // Libérer l'allocation initiale de word
    while (!feof(f)) {
        word = next_word(f, line, colonne); 
        addToDico(&dictionary, word, line, colonne);
    }

    displayDico(dictionary);

    for (int i = 0; i < MaxSizeArray; i++) {
        serialized_dico[i] = NULL;
    }

    serializeDico(dictionary, serialized_dico);

    for (int i = 0; i < MaxSizeArray; i++) {
        if (serialized_dico[i] != NULL) {
            printf("Index %d -> ", i);
            displayWord(serialized_dico[i], stdout);
        }
    }

    for (int i = 0; i < MaxSizeArray; i++) {
        if (serialized_dico[i] != NULL) {
            deserializeDico(&copiedico, serialized_dico[i]);
        }
    }

    printf("A la fin : \n");
    displayNodes(copiedico, stdout);

    // Liberer la mémoire
    free(line);
    free(colonne);
    freeDico(dictionary);
    freeDico(copiedico);

    /*for (int i = 0; i < MaxSizeArray; i++) {
        if (serialized_dico[i] != NULL) {
            free(serialized_dico[i]);
            serialized_dico[i] = NULL;
        }
    }*/
    free(serialized_dico);

    fclose(f);
    return 0;
}