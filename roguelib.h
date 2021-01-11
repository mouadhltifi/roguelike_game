typedef struct {
  int riga;
  int col;
  int valore;
  int visitata; //0 non visitata, 1 visitata
  int riga_prec;
  int col_prec;
  int partenza; // 1 se è la casella da cui si è partiti per scavare
}cella;

//step 2

int **generate_map(int size, int *punt_riga, int *punt_col, int *punt_time);

void scava (cella **traccia, int r_inizio, int c_inizio, int size, int *uscita_messa);

int move_rand (int rigaP,int colP,int size); //sceglie casuelamente la mossa da fare evitando quelle non opportune su lati e angoli

int check_rimanenti (cella **traccia, int rigaP, int colP, int size); //controlla se ci sono altre possibili caselle da scavare o se tornare indietro
                                                                      // 1 se ci sono caselle rimanenti; 0 se non ce ne sono

void save_game(int **map, int size, const char filename[], int riga_curr, int col_curr, int time_curr);
/*che salva la mappa in ingresso (map), di dimensione size, in un file testo di nome filename*/
// riga-col-time-size-mappa

int **load_map(int *punt_size, char filename[], int *punt_riga, int *punt_col, int *punt_time);

/*riceve un puntatore a un intero dispari che indica la dimensione della mappa e la stringa col nome del file testo da cui leggere;
  ritorna un doppio puntatore a una matrice di interi*/

void visualize_map(int **map, int size, int riga_curr, int col_curr);
/*
stampa la mappa nel seguente modo:
-  0 -> ' ' -> spazio vuoto
-  1 -> '#' -> muro
-  2 -> 'P' -> player
-  3 -> 'O' -> uscita
*/

//step 3

  void play (int **map, const char filename[], int riga_curr, int col_curr, int size, int time_curr);

  void visualize_status(int tempo);
/*
  void save_game();*/
