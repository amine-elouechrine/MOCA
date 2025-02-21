#include <stdio.h>
#include <stdlib.h>
#include "dico.h"
#include "word.h"
#include "hash.h"


#ifdef FICJSON
#include "json.h"
#endif

#define TEXTE "hugo1.txt"

int main(int argc, char *argv[]) {
  if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        exit(1);
  }
  FILE* f = NULL;
  int i;
  f = fopen(argv[1], "r");
  if (f == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier");
    exit(1);
  }
  
  unsigned int* line = (unsigned int*) malloc(sizeof(int));
  unsigned int* colonne = (unsigned int*) malloc(sizeof(int));
  char* word = (char*) malloc(sizeof(char)*maxSizeWord);
  dico* dictionary = (dico*) malloc(sizeof(dico));
  dictionary->mot = NULL;
  dictionary->fg = NULL;
  dictionary->fd = NULL;

  /*
  dictionary->mot->data.tete_liste->line = 0;
  dictionary->mot->data.tete_liste->colonne = 0;
  dictionary->mot->data.tete_liste->next = NULL;
  dictionary->mot->data.queue_liste->line = 0;
  dictionary->mot->data.queue_liste->colonne = 0;
  dictionary->mot->data.queue_liste->next = NULL;
  */
 
  dico* copiedico = NULL;     

  mot_data_t **serialized_dico = (mot_data_t **)malloc(MaxSizeArray*sizeof(mot_data_t *));
  
  while(!feof(f)) {
    word = next_word(f,line,colonne);
    addToDico(&dictionary,word,line,colonne);
  }
  
  displayDico(dictionary);
  for(i=0; i<MaxSizeArray; i++)
    serialized_dico[i] = NULL;
  serializeDico(dictionary,serialized_dico);
  for(i=0; i<MaxSizeArray; i++)
    if (serialized_dico[i] != NULL) {
      printf("Index %d -> ", i);
      displayWord(serialized_dico[i],stdout);
    }
  for(i=0; i<MaxSizeArray; i++)
    if (serialized_dico[i] != NULL) {
      deserializeDico(&copiedico, serialized_dico[i]);
    }
  printf("A la fin : \n");
  displayNodes(copiedico, stdout);
  fclose(f);
  return 0;
}