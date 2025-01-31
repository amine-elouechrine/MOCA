#ifndef WORD_H
#define WORD_H

#define maxSizeWord 25

char *separators=SEP; 
unsigned int current_line=1;
unsigned int current_col=1; 

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

#endif