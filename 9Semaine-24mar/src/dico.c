#include "dico.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TEXTE "hugo1.txt"
#define DICORES "dictionnaires.txt"

void insertDico(dico** dictionary, mot_t* linkWord) {
    // Base case: if we've reached a NULL pointer, create a new node here
    if (*dictionary == NULL) {
        dico* newDictionary = (dico*)malloc(sizeof(dico));
        if (newDictionary == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
        newDictionary->mot = linkWord;
        newDictionary->fg = NULL;
        newDictionary->fd = NULL;
        *dictionary = newDictionary;
        return;
    }

    // Compare the word to the current node
    int compareResult = compareWord(&((*dictionary)->mot->data), &(linkWord->data));

    if (compareResult > 0) {
        // If current word is greater, go left
        insertDico(&((*dictionary)->fg), linkWord);
    } else if (compareResult < 0) {
        // If current word is smaller, go right
        insertDico(&((*dictionary)->fd), linkWord);
    } else {
        // Word already exists, add new occurrence to the list
        emplacement_t* newTail = incWord(
                (*dictionary)->mot->data.queue_liste,
                linkWord->data.tete_liste->line,
                linkWord->data.tete_liste->colonne
        );

        // Update the queue pointer to the new tail
        (*dictionary)->mot->data.queue_liste = newTail;

        // Free the redundant mot_t structure as we're only using its location data
        free(linkWord);
    }
}


void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne) {
  mot_t* newLinkWord = (mot_t*) malloc(sizeof(mot_t));
  if (newLinkWord == NULL) {
    printf("Erreur d'allocation de memoire\n");
    exit(1);
  }
  emplacement_t* location = (emplacement_t*) malloc(sizeof(emplacement_t));
  if (location == NULL) {
    printf("Erreur d'allocation de memoire\n");
    exit(1);
  }
  strcpy(newLinkWord->data.lemot, word);
  newLinkWord->lehash = hash(word);
  location->line = *line;
  location -> colonne = *colonne;
  location->next = NULL;
  newLinkWord->data.tete_liste = location;
  newLinkWord->data.queue_liste = location;
  if(*dictionary==NULL) {
    dico* newDictionary = (dico*) malloc(sizeof(dico));
    newDictionary->mot = newLinkWord;
    newDictionary->fg = newDictionary->fd = NULL;
    *dictionary = newDictionary;
  } else if ((*dictionary)->mot == NULL) {
    (*dictionary)->mot = newLinkWord;
  } else {
    insertDico(dictionary,newLinkWord);
  }
}

void displayDico(dico* dictionary) {
  FILE *f = NULL;
  f = fopen(DICORES, "w");
  if (!feof(f))
    printf("Resultat existant dans le fichier resultat, on ecrase\n");
  if (dictionary == NULL) {
    printf("displayDico : NULL\n");
  } else {
    //fprintf(f, "Contenu dictionnaire pour %s : \n", TEXTE);
    dico* tempDico = (dico*) malloc(sizeof(dico));
    tempDico = dictionary;
    displayNodes(tempDico, f);
    fflush(f);
  }
}

void serializeDico(dico * dictionary, mot_data_t **table) {
  if (dictionary) {
    serializeDico(dictionary->fg, table);
    table[abs(dictionary->mot->lehash)] = &(dictionary->mot->data); 
    serializeDico(dictionary->fd, table);
  }
}

void deserializeDico(dico** dic, mot_data_t *elt) {
  dico *temp = NULL;
  mot_t* newLinkWord = (mot_t*) malloc(sizeof(mot_t));
  if (newLinkWord == NULL) {
    printf("Erreur d'allocation de memoire\n");
    exit(1);
  }
  if (elt == NULL) {
    return;
  }
  newLinkWord->lehash = hash(elt->lemot);
  newLinkWord->data = *elt;
  if((*dic)==NULL) {
    temp = (dico *)malloc(sizeof(dico));
    temp->fg = temp->fd = NULL;
    temp->mot = newLinkWord;
    *dic = temp;
    return;
  }

  if (compareWord(&((*dic)->mot->data),&(newLinkWord->data))>0) {  
    
    deserializeDico(&(*dic)->fg, elt);
  }
  else
    deserializeDico(&(*dic)->fd, elt);
}

void displayNodes(dico *d, FILE* f) {
  if (d) {
    displayNodes(d->fg, f);
    displayWord(&(d->mot->data),f);
    displayNodes(d->fd, f);
  }
}
