#include "roguelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 20 //view depth

int **generate_map(int size, int *punt_riga, int *punt_col, int *punt_time)
{
  cella **traccia;
  int **map,i,j;
  int nrighe = size;
  int ncol = size;

  traccia = calloc(nrighe,sizeof(cella*));
  for (i=0; i<nrighe; i++)
    traccia[i] = calloc(ncol,sizeof(cella));

    for (i=0; i<nrighe; i++){
      for (j=0; j<ncol; j++){
        traccia[i][j].riga=i;
        traccia[i][j].col=j;
        traccia[i][j].valore=1;
        traccia[i][j].visitata=0;
        traccia[i][j].partenza=0;
      }
    }

  //sistemo ora la cella da cui inizierò a scavare per poter interrompere opportunamente la funzione ricorsiva
  int r_inizio = 1;
  int c_inizio = 1;
  //devono essere dispari assieme al numero di righe e colonne totali per il funzionamento dell'algoritmo

  int *uscita_messa = calloc(1, sizeof(int));//serve per far mettere l'uscita dentro alla funzione ricorsiva

  traccia[r_inizio][c_inizio].partenza=1;
  scava (traccia, r_inizio, c_inizio, size, uscita_messa);
  traccia[r_inizio][c_inizio].valore=2;

  map = calloc(nrighe,sizeof(int*));
  for (i=0; i<nrighe; i++)
    map[i] = calloc(ncol,sizeof(int));

    for (i=0; i<nrighe; i++){
      for (j=0; j<ncol; j++){
        map[i][j]=traccia[i][j].valore;
      }
    } //copia della mappa di struct solo il valore delle caselle

  *punt_riga = r_inizio;
  *punt_col = c_inizio;

  return map;
  }

void scava (cella **traccia, int r_inizio, int c_inizio, int size, int *uscita_messa)
{
  int rigaP = r_inizio;
  int colP = c_inizio;
  int dir;

  traccia[rigaP][colP].valore=0;
  traccia[rigaP][colP].visitata=1;

  dir = move_rand (rigaP, colP, size);
//  dir = 1;
  switch (dir) {
    case 0:
  //  printf("%d\n",dir );
      if (traccia[rigaP-2][colP].visitata == 0)
      {
        traccia[rigaP-1][colP].valore=0;
        traccia[rigaP-2][colP].riga_prec=rigaP;
        traccia[rigaP-2][colP].col_prec=colP;

        rigaP = rigaP-2;
        scava(traccia, rigaP, colP, size, uscita_messa);
      }
      else if (traccia[rigaP-2][colP].visitata == 1)
      {
        if (check_rimanenti(traccia, rigaP, colP, size)==1)
        {
          scava(traccia, rigaP, colP, size, uscita_messa);
        }
        else if (check_rimanenti(traccia, rigaP, colP, size)==0)
        {
          if ((*uscita_messa)==0)
          {
            traccia[rigaP][colP].valore = 3;
            (*uscita_messa)=1;
          }
          if (traccia[rigaP][colP].partenza == 0)
          {
            scava(traccia, traccia[rigaP][colP].riga_prec, traccia[rigaP][colP].col_prec, size, uscita_messa);
          }
        }
        else
        {
          printf("Errore: check rimanenti case %d\n", dir);
        }
      }
      break;

    case 1:
  //  printf("%d\n",dir );
      if (traccia[rigaP][colP+2].visitata == 0)
      {
        traccia[rigaP][colP+1].valore=0;
        traccia[rigaP][colP+2].riga_prec=rigaP;
        traccia[rigaP][colP+2].col_prec=colP;

        colP = colP+2;
        scava(traccia, rigaP, colP, size, uscita_messa);
      }
      else if (traccia[rigaP][colP+2].visitata == 1)
      {
        if (check_rimanenti(traccia, rigaP, colP, size)==1)
        {
          scava(traccia, rigaP, colP, size, uscita_messa);
        }
        else if (check_rimanenti(traccia, rigaP, colP, size)==0)
        {
          if ((*uscita_messa)==0)
          {
            traccia[rigaP][colP].valore = 3;
            (*uscita_messa)=1;
          }
          if (traccia[rigaP][colP].partenza == 0)
          {
            scava(traccia, traccia[rigaP][colP].riga_prec, traccia[rigaP][colP].col_prec, size, uscita_messa);
          }
        }
        else
        {
          printf("Errore: check rimanenti case %d\n", dir);
        }
      }
      break;

    case 2:
  //  printf("%d\n",dir );
      if (traccia[rigaP+2][colP].visitata == 0)
      {
        traccia[rigaP+1][colP].valore=0;
        traccia[rigaP+2][colP].riga_prec=rigaP;
        traccia[rigaP+2][colP].col_prec=colP;

        rigaP = rigaP+2;
        scava(traccia, rigaP, colP, size, uscita_messa);
      }
      else if (traccia[rigaP+2][colP].visitata == 1)
      {
        if (check_rimanenti(traccia, rigaP, colP, size)==1)
        {
          scava(traccia, rigaP, colP, size, uscita_messa);
        }
        else if (check_rimanenti(traccia, rigaP, colP, size)==0)
        {
          if ((*uscita_messa)==0)
          {
            traccia[rigaP][colP].valore = 3;
            (*uscita_messa)=1;
          }
          if (traccia[rigaP][colP].partenza == 0)
          {
            scava(traccia, traccia[rigaP][colP].riga_prec, traccia[rigaP][colP].col_prec, size, uscita_messa);
          }
        }
        else
        {
          printf("Errore: check rimanenti case %d\n", dir);
        }
      }
      break;

    case 3:
  //  printf("%d\n",dir );
      if (traccia[rigaP][colP-2].visitata == 0)
      {
        traccia[rigaP][colP-1].valore=0;
        traccia[rigaP][colP-2].riga_prec=rigaP;
        traccia[rigaP][colP-2].col_prec=colP;

        colP = colP-2;
        scava(traccia, rigaP, colP, size, uscita_messa);
      }
      else if (traccia[rigaP][colP-2].visitata == 1)
      {
        if (check_rimanenti(traccia, rigaP, colP, size)==1)
        {
          scava(traccia, rigaP, colP, size, uscita_messa);
        }
        else if (check_rimanenti(traccia, rigaP, colP, size)==0)
        {
          if ((*uscita_messa)==0)
          {
            traccia[rigaP][colP].valore = 3;
            (*uscita_messa)=1;
          }
          if (traccia[rigaP][colP].partenza == 0)
          {
            scava(traccia, traccia[rigaP][colP].riga_prec, traccia[rigaP][colP].col_prec, size, uscita_messa);
          }
        }
        else
        {
          printf("Errore: check rimanenti case %d\n", dir);
        }
      }
      break;

    default:
      printf("Errore: direzione scava non valida\n");
  }


}

int move_rand (int rigaP,int colP,int size)
{//0 su; 1 destra; 2 sinistra; 3 giu

  int ris = rand()%4;

  if (colP == 1)
  {
    if (rigaP == 1)//alto sinistra
    {
      if (ris == 0 || ris == 3){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
    else if (rigaP == (size-2))//basso sinistra
    {
      if (ris == 2 || ris == 3){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
    else//colonna sinistra
    {
      if (ris == 3){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
  }

  else if (colP == (size-2))
  {
    if (rigaP == 1)//alto destra
    {
      if (ris == 0 || ris == 1){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
    else if (rigaP == (size-2))//basso destra
    {
      if (ris == 2 || ris == 1){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
    else//colonna destra
    {
      if (ris == 1){
        return move_rand (rigaP, colP, size);
      }
      else{
        return ris;
      }
    }
  }

  else if (rigaP == 1)//riga alto
  {
    if (ris == 0){
      return move_rand (rigaP, colP, size);
    }
    else{
      return ris;
    }
  }

  else if (rigaP == (size-2))//riga basso
  {
    if (ris == 2){
      return move_rand (rigaP, colP, size);
    }
    else{
      return ris;
    }
  }

  else//generale
  {
    return ris;
  }

}

int check_rimanenti (cella **traccia, int rigaP, int colP, int size)
{// 0 no rimanenti; 1 si rimanenti
  if (colP == 1)
  {
    if (rigaP == 1)//alto sinistra
    {
      if (traccia[rigaP][colP+2].visitata == 0 ||
          traccia[rigaP+2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }

    else if (rigaP == (size-2))//basso sinistra
    {
      if (traccia[rigaP][colP+2].visitata == 0 ||
          traccia[rigaP-2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }

    else//colonna sinistra
    {
      if (traccia[rigaP][colP+2].visitata == 0 ||
          traccia[rigaP-2][colP].visitata == 0 ||
          traccia[rigaP+2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }

  else if (colP == (size-2))
  {
    if (rigaP == 1)//alto destra
    {
      if (traccia[rigaP][colP-2].visitata == 0 ||
          traccia[rigaP+2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }

    else if (rigaP == (size-2))//basso destra
    {
      if (traccia[rigaP][colP-2].visitata == 0 ||
          traccia[rigaP-2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }

    else//colonna destra
    {
      if (traccia[rigaP][colP-2].visitata == 0 ||
          traccia[rigaP-2][colP].visitata == 0 ||
          traccia[rigaP+2][colP].visitata == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }

  else if (rigaP == 1)//riga alto
  {
    if (traccia[rigaP][colP-2].visitata == 0 ||
        traccia[rigaP][colP+2].visitata == 0 ||
        traccia[rigaP+2][colP].visitata == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }

  else if (rigaP == (size-2))//riga basso
  {
    if (traccia[rigaP][colP-2].visitata == 0 ||
        traccia[rigaP][colP+2].visitata == 0 ||
        traccia[rigaP-2][colP].visitata == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }

  else//generale
  {
    if (traccia[rigaP][colP-2].visitata == 0 ||
        traccia[rigaP][colP+2].visitata == 0 ||
        traccia[rigaP-2][colP].visitata == 0 ||
        traccia[rigaP+2][colP].visitata == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

int **load_map(int *punt_size, char filename[], int *punt_riga, int *punt_col, int *punt_time)
{
  FILE *finput;
  finput = fopen(filename, "r");

  if (finput!=NULL){
    //avendo riaperto il file in questo modo mi riposiziono dopo la prima riga con dim mappa
    fscanf (finput, "%d", punt_riga);
    fscanf (finput, "%d", punt_col);
    fscanf (finput, "%d", punt_time);
    fscanf (finput, "%d", punt_size);

    int **map,i,j, size;
    size = *punt_size;
    int nrighe = size;
    int ncol = size;

    map = calloc(nrighe,sizeof(int*));
    for (i=0; i<nrighe; i++)
		  map[i] = calloc(ncol,sizeof(int));

      for (i=0; i<nrighe; i++){
        for (j=0; j<ncol; j++){
          fscanf (finput, "%d", map[i]+j);
        }
      }
      fclose (finput);
      return map;
    }
    else{
      printf("Errore: lettura mappa\n");
      return NULL;
    }
  }

void save_game(int **map, int size, const char filename[], int riga_curr, int col_curr, int time_curr)
{
  int i, j;
  FILE *foutput;
  foutput = fopen(filename, "w");

  fprintf(foutput, "%d\n",riga_curr);
  fprintf(foutput, "%d\n",col_curr);
  fprintf(foutput, "%d\n",time_curr);
  fprintf(foutput, "%d\n",size);

  for (i=0; i<size; i++)
  {
    for (j=0; j<size; j++)
    {
      fprintf(foutput, "%d",map[i][j]);
      if (j<size-1){
        fprintf(foutput, " ");
      }
    }
    fprintf(foutput,"\n");
  }
  fclose (foutput);
}

void visualize_map(int **map, int size, int riga_curr, int col_curr)
{
    int map2[size+V][size+V];
    int i,j;

    for(i=0; i<size+V; i++)
    {
      for(j=0; j<size+V; j++)
      {
        if (i<(V/2)||i>size+((V/2)-1)||j<(V/2)||j>size+((V/2)-1))
        {
          map2[i][j]=0;
        }
        else
        {
          map2[i][j]=*(map[i-(V/2)]+(j-(V/2)));
        }
      }
    }

    printf("\n");
    for (i=riga_curr; i<riga_curr+V; i++){
      for (j=col_curr; j<col_curr+V; j++){
        switch (map2[i][j]) {
          case 0:
            printf("%c", 32);
            break;
          case 1:
            printf("%c", 35);
            break;
         case 2:
            printf("%c", 'P');
            break;
         case 3:
            printf("%c", 'O');
            break;
        }
      }
      printf("\n");
    }
//    printf("\n");
  }

void play (int **map, const char filename[], int riga_curr, int col_curr, int size, int time_curr)
{
  char scarto_input;
  scanf("%c", &scarto_input);

  char avvio;
  printf("Digit a character and press [Enter] to start\n");
  scanf("%c%*c", &avvio);

  int end_game = 0; //lo uso per uscire dal while della partita
  int save = 0 ;
//  int time_curr;
  char move; //w a s d per muoversi; l "leave game"
  int temp; //per il valore di player da spostare

//  time_curr = 0;

  while(end_game!=1)
  {
    visualize_map(map, size, riga_curr, col_curr);
    visualize_status(time_curr);
    scanf("%c%*c", &move);
    switch (move) {
      case 'w':
        if (map[riga_curr-1][col_curr]==0)
        {
          temp = map[riga_curr][col_curr];
          map[riga_curr][col_curr] = 0;
          riga_curr = riga_curr-1;
          map[riga_curr][col_curr] = temp;
        }
        else if (map[riga_curr-1][col_curr]==3)
        {
          end_game = 1;
        }
        time_curr = time_curr+1;
        break;

      case 'a':
        if (map[riga_curr][col_curr-1]==0)
        {
          temp = map[riga_curr][col_curr];
          map[riga_curr][col_curr] = 0;
          col_curr = col_curr-1;
          map[riga_curr][col_curr] = temp;
        }
        else if (map[riga_curr][col_curr-1]==3)
        {
          end_game = 1;
        }
        time_curr = time_curr+1;
        break;

      case 's':
        if (map[riga_curr+1][col_curr]==0)
        {
          temp = map[riga_curr][col_curr];
          map[riga_curr][col_curr] = 0;
          riga_curr = riga_curr+1;
          map[riga_curr][col_curr] = temp;
        }
        else if (map[riga_curr+1][col_curr]==3)
        {
          end_game = 1;
        }
        time_curr = time_curr+1;
        break;

      case 'd':
        if (map[riga_curr][col_curr+1]==0)
        {
          temp = map[riga_curr][col_curr];
          map[riga_curr][col_curr] = 0;
          col_curr = col_curr+1;
          map[riga_curr][col_curr] = temp;
        }
        else if (map[riga_curr][col_curr+1]==3)
        {
          end_game = 1;
        }
        time_curr = time_curr+1;
        break;

      case 'l':
        end_game = 1;
        break;

      default :
        printf("Comando [%c] inserito non valido\nInserire comando valido\n", move);
        break;
    }
  }

  printf("Do you want to save this game?\n[1] - Yes\n[0] - No\n");
  scanf("%d", &save);

  if (save == 1)
  {
    save_game(map, size, filename, riga_curr, col_curr, time_curr);
  }
}

  void visualize_status(int tempo)
  {
    printf("Time: %d\n", tempo);
    printf("Choose your next action:\n- [W] [A] [S] [D] to move\n- [L] to leave the game\n");
  }
