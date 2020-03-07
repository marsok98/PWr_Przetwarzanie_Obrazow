#include "pgm.h"


/*****************************Funkcja zeruj************************/
void wyzeruj_opcje(w_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
  wybor->w_progu=0;
  wybor->czytaj=0;            
  wybor->zapisz=0;
  wybor->zapisano=0;
  wybor->operacja=0;
  wybor->red = 0;
  wybor->green =0;
  wybor->blue =0;
  wybor->grey =0;


  wybor->odczytano=1;               /*Tu wpisujemy wartosc ktora zwraca funkcja czytaj*/          
  wybor->prawidlowe_opcje=1;        /*Tu wpisujemy wartosc ktora zwraca funkcja przetwarzaj_opcje*/
  

}

/****************************Przetwarzaj opcje***************************/

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*  poprawnie wystapily w linii wywolania programu,                     */
/*  pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;         */
/*  zwraca wartosc W_OK, gdy wywolanie bylo poprawne                    */
/*  lub kod bledu zdefiniowany stalymi B_* (<0)                         */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor){
  int i;
  int czy_podane_zostalo_i = 0;                              /*Czy zostalo podane i w wywolaniu programu*/
  int czy_podane_zostalo_o = 0;                              /*Czy zostalo podane o w wywolaniu programu*/
  int czy_podane_zostalo_m = 0;                              /*Czy zostalo podane m w wywolaniu programu*/

  wyzeruj_opcje(wybor);
  wybor->plik_wy = stdout;                                   /*Na wypadek gdyby nie podano opcji*/

  for(i=1; i<argc; i++){
    if(argv[i][0] !='-')                                     /*Blad: to nie jest opcja - brak "-"*/
      return B_NIEPOPRAWNAOPCJA;

    switch(argv[i][1]){

      case 'i' :                                             /*opcja z nazwa pliku wejsciowego */
        czy_podane_zostalo_i=1;
        if(++i<argc){                                        /*wczytujemy kolejny argument jako nazwe pliku*/
           wybor->nazwa_pliku_we=argv[i];
           
           if(strcmp(wybor->nazwa_pliku_we,"-")==0){         /*gdy nazwa jest "-"*/

              wybor->plik_we=stdin;                          /*Ustawiamy wejscie na stdin*/
              wybor->czytaj=1;                               /*Mozemy czytac z stdin*/

           }else if(strcmp(wybor->nazwa_pliku_we,"-k")==0){  /*Na wypadek gdyby po -i uzytkownik wpisal odrazu inna komende*/
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_we,"-o")==0){  /*Ktora jest rozpoznawana w tym programie*/
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_we,"-n")==0){  /*to oznacza że uzytkownik nie podal nazwy obrazu do przetworzenie*/
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_we,"-p")==0){
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_we,"-d")==0){
              return B_BRAKNAZWY;

           }else{                                              /*Otwieramy wskazany plik*/
              wybor->plik_we=fopen(wybor->nazwa_pliku_we, "r");
              wybor->czytaj=1;
           }
        }else{
            return B_BRAKNAZWY;                               /*blad:brak nazwy pliku */    
        }
        break;

      case 'o' :                                              /* opcja z nazwa pliku wyjsciowego */
        czy_podane_zostalo_o=1;
        if(++i<argc){                                         /* wczytujemy kolejny argument jako nazwe pliku */
          wybor->nazwa_pliku_wy=argv[i];
          if(strcmp(wybor->nazwa_pliku_wy,"-")==0){            /*analogicznie do poprzedniego*/
              
              wybor->plik_wy=stdout;                           /*Wypisanie na stdout*/
              wybor->zapisz =1;                             

           }else if(strcmp(wybor->nazwa_pliku_wy,"-i")==0){
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_wy,"-n")==0){
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_wy,"-k")==0){
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_wy,"-p")==0){
              return B_BRAKNAZWY;
           }else if(strcmp(wybor->nazwa_pliku_wy,"-d")==0){
              return B_BRAKNAZWY;


          }else{
              wybor->plik_wy=fopen(wybor->nazwa_pliku_wy,"w");
              wybor->zapisz = 1;
          }
        }else{
          return B_BRAKNAZWY;
        }
        break;

      case 'n' :                                                      /*gdy mamy dokonac negatywu */
        wybor->negatyw=1;
        break;

      case 'k' : 
        wybor->konturowanie=1;
        break;

      case 'd':
        wybor->wyswietlenie =1;
        break;

      case 'p':
        if(++i<argc){
           if(strcmp(argv[i],"-i")==0){
              return B_WPROG;                         
           }else if(strcmp(argv[i],"-n")==0){
              return B_WPROG;
           }else if(strcmp(argv[i],"-k")==0){
              return B_WPROG;
           }else if(strcmp(argv[i],"-o")==0){
              return B_WPROG;
           }else if(strcmp(argv[i],"-d")==0){
              return B_WPROG;
           }else if(strcmp(argv[i]," ")==0){
              return B_WPROG;
           }

          wybor->w_progu =  atoi(argv[i]) ;                          /*rzutowanie z char na int */
          if(0<=wybor->w_progu && wybor->w_progu<=100){              /*Sprawdzanie poprawnosci wpisanego progu*/
              wybor->progowanie =1;
          }else{
             return(B_WPROG);
          }

        }else{
          return B_WPROG;
        }
        break;

      case 'm':
        czy_podane_zostalo_m=1;                           
        if(++i<argc){
          if(strcmp(argv[i],"-i")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"-n")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"-k")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"-o")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"-d")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i]," ")==0){
              return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"-p")==0){
             return B_NIEPODANO_KOLORU;
           }else if(strcmp(argv[i],"r")==0){     
              wybor->red = 1;                                       /*Wiemy z jakiego koloru bedziemy korzystac*/
           }else if(strcmp(argv[i],"g")==0){
              wybor->green = 1;
           }else if(strcmp(argv[i],"b")==0){
              wybor->blue = 1;
           }else if(strcmp(argv[i],"s")==0){
              wybor->grey = 1;
           }else{
              return B_NIEPODANO_KOLORU;
           }

        }
        break;


      default:
        return B_NIEPOPRAWNAOPCJA;
    } /*Koniec switcha */
  }/*Koniec for */
  if(!czy_podane_zostalo_i)                                       /*Jesli wogole nie zostalo wywolane 'i' w programie*/
    return B_BRAKNAZWY;
  if(!czy_podane_zostalo_m)                                       /*Jesli nie zostalo podane m*/
    return B_NIEPODANO_KOLORU;
  if(!czy_podane_zostalo_o){                                      /*Jesli nie zostalo podane o to wyswietl na stdout obraz juz przetworzony*/
     wybor->plik_wy=stdout;
     wybor->zapisz =1;
  }

  if(wybor->plik_we!=NULL)
    return W_OK;
  else
    return B_BRAKPLIKU;
}




/************************Funkcja czytaj ********************/

int czytaj(FILE *plik, obraz *wsk,w_opcje *wybor){
  char buf[DL_LINII];                                             /*bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                                                       /*zmienna pomocnicza do czytania komentarzy*/
  int koniec = 0;                                                 /* czy napotkano koniec danych w pliku */
  int i,j;


  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  
  if(plik == NULL) {
    return(B_BRAKPLIKU);
  }

  /*Sprawdzenie "numeru magicznego" - powinien byc P2 */

  if(fgets(buf,DL_LINII,plik) == NULL){                           /*Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                                                   /* Nie udalo sie? Koniec danych! */
  }

  if((buf[0]=='P') && (buf[1]=='2') && !koniec) {                 /*Czy jest magiczne P2 */
    wsk->kolor=0;
    
  }else if((buf[0] == 'P') && (buf[1]=='3') && !koniec){          /*Czy jest magiczne P3 */ 
    wsk->kolor =1;                                                /*Obraz jest w kolorze */              
  }else{
    return(B_NIEPOPRAWNYFORMAT);
  }
  


  /*Pominiecie komentarzy*/

  do {
    if((znak = fgetc(plik)) == '#'){                              /* Czy linia rozpoczyna sie od znaku '#' */
      if(fgets(buf,DL_LINII,plik) == NULL){                       /* Przeczytaj ja do bufora */
	       koniec = 1;                                              /*zapamietaj ewentualny koniec danych*/
      }

      
    }else{
	     ungetc(znak,plik);                                         /*Gdy przeczytany znak z poczatk linii nie jest '#' zwroc go */
      }
  }while (znak == '#' && !koniec);                                /*Powtarzaj dopoki sa linie komentarza i nie nastapil koniec danych */


  /*Pobranie wymiarow obrazu i liczby odcieni szarosci */

  if(fscanf(plik,"%d %d %d",&wsk->wymx,&wsk->wymy,&wsk->odcieni)!=3){
      return(B_NIEPOPRAWNYFORMAT);                                                               
  }

  
  wsk->obraz_wej= malloc(wsk->wymy*sizeof(int *));                  /*Mamy juz wszystkie wymiary wiec mozemy deklarowac tablice dynamiczne*/
    if(wsk->obraz_wej==NULL){
        return(B_PAMIEC);
    }
    for(i=0;i<wsk->wymy;i++){
        wsk->obraz_wej[i] = malloc(wsk->wymx * sizeof(int));
        if(wsk->obraz_wej[i]==NULL){
          return(B_PAMIEC);
        }
    }

  wsk->obraz_wyj= malloc(wsk->wymy*sizeof(int *));
    if(wsk->obraz_wyj==NULL){ 
      return(B_PAMIEC);
    }
    for(i=0;i<wsk->wymy;i++){
      wsk->obraz_wyj[i] = malloc(wsk->wymx * sizeof(int));
      if(wsk->obraz_wyj[i]==NULL){ 
        return(B_PAMIEC);
      }
    }
/*Zaalokowanie miejsca trzem tablicom na skladowe koloru w obrazie */
  wsk->obraz_red = malloc(wsk->wymy*sizeof(int*));
    if(wsk->obraz_red==NULL){
      return(B_PAMIEC);
    }
    for(i=0;i<wsk->wymy;i++){
      wsk->obraz_red[i] = malloc(wsk->wymx*sizeof(int));
      if(wsk->obraz_red[i]==NULL){
        return(B_PAMIEC);
      }
    }

  wsk->obraz_green = malloc(wsk->wymy*sizeof(int*));
    if(wsk->obraz_green==NULL){
      return(B_PAMIEC);
    }
    for(i=0;i<wsk->wymy;i++){
      wsk->obraz_green[i] = malloc(wsk->wymx*sizeof(int));
      if(wsk->obraz_green[i]==NULL){
        return(B_PAMIEC);
        }
    }

   wsk->obraz_blue = malloc(wsk->wymy*sizeof(int*));
    if(wsk->obraz_blue==NULL){
      return(B_PAMIEC);
    }
    for(i=0;i<wsk->wymy;i++){
      wsk->obraz_blue[i] = malloc(wsk->wymx*sizeof(int)); 
      if(wsk->obraz_blue[i]==NULL){
        return(B_PAMIEC);
      }
    }



  if(!wsk->kolor){                                                            /*jesli obraz jest szary */
    for(i=0;i<wsk->wymy;i++) {
      for(j=0;j<wsk->wymx;j++){
        if(fscanf(plik,"%d",&(wsk->obraz_wej[i][j]))!=1){
      	  return(B_NIEPOPRAWNYFORMAT);
        }
      }
    }




  }else if(wsk->kolor){                                                      /*Jesli obraz jest kolorowy*/ 
    for(i=0;i<wsk->wymy;i++) {
      for(j=0;j<wsk->wymx;j++){
        if(fscanf(plik,"%d %d %d",&(wsk->obraz_red[i][j]), &(wsk->obraz_green[i][j]), &(wsk->obraz_blue[i][j]))!=3){
          return(B_NIEPOPRAWNYFORMAT);
        }
      }
    }

    if(wybor->grey==1){                      /* Jesli zostala wywolana opcja 's' to Konwersja z koloru na odcienie szarosci */
     for(i=0;i<wsk->wymy;i++) {
       for(j=0;j<wsk->wymx;j++){
            wsk->obraz_wej[i][j]=(wsk->obraz_red[i][j] + wsk->obraz_green[i][j] + wsk->obraz_blue[i][j])/3; 
        }
     }

     

    }else if(wybor->red==1){                    /* Jesli zostala wywolana opcja 'r'*/
      for(i=0;i<wsk->wymy;i++){
        for(j=0;j<wsk->wymx;j++){
          wsk->obraz_wej[i][j]=wsk->obraz_red[i][j];
        }
      }
    }else if(wybor->green==1){
      for(i=0;i<wsk->wymy;i++){
        for(j=0;j<wsk->wymx;j++){
          wsk->obraz_wej[i][j]=wsk->obraz_green[i][j];
        }
      }
    }else if(wybor->blue==1){
      for(i=0;i<wsk->wymy;i++){
        for(j=0;j<wsk->wymx;j++){
          wsk->obraz_wej[i][j]=wsk->obraz_blue[i][j];
        }
      }
    }

    for(i=0;i<wsk->wymy;i++){                   /*Uwalniamy teraz pamiec bo juz nie potrzebne nam sa te tablice*/
      free(wsk->obraz_red[i]);                  /*Obraz zostal juz przetworzony na odcienie szarosci*/
    }
    for(i=0;i<wsk->wymy;i++){
      free(wsk->obraz_green[i]);
    }
    for(i=0;i<wsk->wymy;i++){
      free(wsk->obraz_blue[i]);
    }

    free(wsk->obraz_red);
    free(wsk->obraz_green);
    free(wsk->obraz_blue);
    }
  
    
  
  return (W_OK);       /*Czytanie zakonczone sukcesem */
  /*Zwraca 0*/
}                   





/*********************Fukcja zapisu********************/
void zapisz( FILE *plik,obraz *wsk){
  int i, j;
  fprintf(plik,"P2 \n");  /*Zapisanie w pliku wszystkich informacji o formacie pliku */
  fprintf(plik,"%d %d \n",wsk->wymx,wsk->wymy);
  fprintf(plik,"%d \n",wsk->odcieni);

  for(i = 0; i<wsk->wymy; i++){
    for(j = 0; j<wsk->wymx; j++) {
      fprintf(plik,"%d ",wsk->obraz_wyj[i][j]);
    }
  }
  
  fclose(plik);
}


/********************Funkcja Negatywu*******************/
void negatyw(obraz *wsk){
  int i,j;
  for(i=0; i<wsk->wymy; i++){
    for(j=0; j<wsk->wymx; j++){
      wsk->obraz_wyj[i][j] = wsk->odcieni - wsk->obraz_wej[i][j];
    }
  }
}
/*******************Funkcja progowania********************/

void progowanie(obraz *wsk,int prog_procent){
  int i,j;
  int  prog = 0;        
 
  prog=prog_procent*wsk->odcieni*0.01;

  for(i=0;i<wsk->wymy;i++){
    for(j=0;j<wsk->wymx;j++){
      if(wsk->obraz_wej[i][j]<=prog){
	       wsk->obraz_wyj[i][j]=0;
	
      }else{
	       wsk->obraz_wyj[i][j]=wsk->odcieni;
      }
    }
  }
}
  
/************************Funkcja Konturowania******************************/

void konturowanie(obraz *wsk){
  int i,j;
  for(i=0;i<wsk->wymy-1;i++){    /*wczytywanie bez ostatniego wiersza*/   
    for(j=0;j<wsk->wymx-1;j++){  /*wczytywanie bez ostatniej kolumny*/
      wsk->obraz_wyj[i][j]=abs(wsk->obraz_wej[i+1][j] - wsk->obraz_wej[i][j]) + 
                           abs(wsk->obraz_wej[i][j+1] - wsk->obraz_wej[i][j]);
    }
  }
}

