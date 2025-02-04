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

char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol);
void incWord(emplacement_t* location, unsigned int line, unsigned int colonne);
void displayWord(mot_data_t* word, FILE *filedes);
int compareWord(mot_data_t* w1, mot_data_t* w2);

#endif