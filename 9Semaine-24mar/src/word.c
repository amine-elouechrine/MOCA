#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define SEP " ,.-"   
#define MAX_LENGTH 100

char *separators=SEP; 
unsigned int current_line=1;
unsigned int current_col=1; 

int est_caractere_normal(char c) {
    // Vérifie si le caractère est dans la plage des caractères imprimables ASCII
    return (c >= 32 && c <= 126);
}

char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol) {
  char s[100];
  unsigned int i = 0;
  unsigned int startl = current_line;
  unsigned int startc = current_col;
  int c;

  // Sauter les séparateurs initiaux
  while ((c = fgetc(f)) != EOF) {
      if (strchr(separators, c) != NULL || c == '\n') {
          startc++;
          if (c == '\n') {
              startl++;
              startc = 1;
          }
      } else {
          ungetc(c, f); // On remet le premier caractère du mot
          break;
      }
  }

  // Lire le mot
  while (i < sizeof(s) - 1 && (c = fgetc(f)) != EOF && strchr(separators, c) == NULL && c != '\n' && isprint(c)) {
      s[i++] = c;
      startc++;
  }
  s[i] = '\0'; // Terminaison de chaîne

  // Mettre à jour les positions globales
  current_line = startl;
  current_col = startc;

  // Mettre à jour les paramètres de sortie
  if (nblin) *nblin = startl;
  if (nbcol) *nbcol = startc;

  // Allouer et copier le résultat
  char *res = malloc(i + 1);
  if (!res) {
      fprintf(stderr, "Erreur d'allocation de mémoire\n");
      exit(1);
  }
  strcpy(res, s);
  
  return res;
}

void incWord(emplacement_t* location, unsigned int line, unsigned int colonne) {
  emplacement_t* newLocation = (emplacement_t*) malloc(sizeof(emplacement_t));
  emplacement_t* tempLocation = (emplacement_t*) malloc(sizeof(emplacement_t));
  if (newLocation == NULL || tempLocation == NULL) {
    printf("Erreur d'allocation de memoire\n");
    exit(1);
  }
  tempLocation = location;
  newLocation->next = NULL;
  newLocation->line = line;
  newLocation->colonne = colonne;
  while(tempLocation->next != NULL) {
    tempLocation = tempLocation->next;
  }
  tempLocation->next = newLocation;
}

int compareWord(mot_data_t* w1, mot_data_t* w2) {
  if (w1 == NULL || w1->lemot == NULL) {
    return 1;
  } else if (w2 == NULL || w2->lemot == NULL) {
    return -1;
  } else {
    char* word1 = w1->lemot;   
    char* word2 = w2->lemot;
    int minSize = (strlen(word1)<strlen(word2))?strlen(word1):strlen(word2);
    int i= 0;
    int pos = 0;
    while(i<minSize && pos == 0) {
      pos = (word1[i]<word2[i])?-1:(word1[i]>word2[i])?1:0;
      i++;
    }
    return (pos == 0 && strlen(word1) < strlen(word2))?-1:(pos == 0 && strlen(word1) > strlen(word2))?1:pos;
  }
}


void displayWord(mot_data_t* word, FILE *filedes) {
  if (word == NULL) {
  } else {
    char* link = word->lemot;   
    emplacement_t* list = word->tete_liste;
    if (link != NULL) {
      fprintf(filedes,"%s",link);
      fflush(stdout);
    }
    while(list != NULL) {
      fprintf(filedes," (%i,%i)",list->line,list->colonne);
      list = list->next;
    }
    fprintf(filedes,"\n");
  }
}
void freeEmplacements(emplacement_t* tete) {
  emplacement_t* courant = tete;
  emplacement_t* suivant;
  while (courant != NULL) {
      suivant = courant->next; 
      free(courant);          
      courant = suivant;      
  }
}

void freeMotData(mot_data_t* motData) {
  if (motData == NULL) return;
  freeEmplacements(motData->tete_liste); // Libérer la liste d'emplacements
}