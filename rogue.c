#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "roguelib.h"


int main(){
  time_t t;
  srand(time(&t));

  char filename [100];

  int **map= NULL;
  int riga_curr, col_curr;
  int *punt_riga = &riga_curr;
  int *punt_col = &col_curr;

  int time_curr = 0;
  int *punt_time = &time_curr;

  int size;
  int *punt_size = &size;

  int load_create;

  printf("Do you want to create a new game or load an existing one?\n[1] create new game\n[2] load existing game\n");
  scanf("%d", &load_create);

  while (load_create != 1 && load_create != 2)
  {
    printf("Invalid choise\n");
    printf("Do you want to create a new game or load an existing one?\n[1] create new game\n[2] load existing game\n");
    scanf("%d%*c", &load_create);
  }

  switch (load_create) {
    case 1://create
      printf("Insert file name in which you want to create your game (file_name.txt)\n");
      scanf("%s",filename);

      printf("What size do you want your map to be? (uneven numbers only)\n");
      scanf("%d", &size);

      while ((size %2) != 1)
      {
        printf("Invalid choice\n");
        printf("What size do you want your map to be? (uneven numbers only)\n");
        scanf("%d%*c\n", &size);
      }

      map=generate_map(size, punt_riga, punt_col, punt_time);

      if (map == NULL)
      {
        printf("Error: create_map\n");
      }

      break;

    case 2://load
      printf("Insert file name from which you want to load your game (file_name.txt)\n");
      scanf("%s",filename);

      map = load_map(punt_size, filename, punt_riga, punt_col, punt_time);

      if (map == NULL)
      {
        printf("Error: load_map\n");
      }
      break;

    default:
    printf("Errore switch load_create\n");
  }
/*
  riga_curr = 1;
  col_curr = 1;
*/
  play (map, filename, riga_curr, col_curr, size, time_curr);


//  char filename [100];
  //strcpy(filename, "output.txt");
  /*
  int time_curr;
  int *punt_time;
  punt_time = &time_curr;

  int size;
  int *punt_size;
  punt_size = &size;
*/
  /*
  FILE *finput;
  finput = fopen (filename, "r");
  fscanf (finput, "%d", &size);
  fclose(finput);
  */

//  size = 21;
/*
  int **map= NULL;
  int riga_curr, col_curr;
  int *punt_riga = &riga_curr;
  int *punt_col = &col_curr;
*/
//  map=generate_map(size, punt_riga, punt_col);

//  map = load_map(punt_size, filename, punt_riga, punt_col, punt_time);

//  visualize_map (map, size);
/*
  int size = 19;//dimensione della mappa
                //deve essere dispari
  int **map=NULL;
  map=generate_map(size);

  visualize_map(map, size);
*/
//  int riga_curr = 1;
//  int col_curr = 1;
//  play (map, riga_curr, col_curr, size, time_curr);



  return 0;
}
