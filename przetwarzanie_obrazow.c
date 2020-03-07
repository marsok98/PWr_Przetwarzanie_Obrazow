#include "pgm.h"


void menu();
void wyswietl(char *n_pliku);



int main(int argc, char **argv){
  
  obraz parametry ;                                     /*Deklaracja struktury parametrow obrazu */
  w_opcje opcje;                                        /*struktura zawierajaca zmienne okreslajace czy mamy zrobic jakąs operacje*/
  opcje.prawidlowe_opcje=przetwarzaj_opcje(argc,argv,&opcje);
  

  
  if(opcje.prawidlowe_opcje==0){                        /*Jesli opcje wprowadzone sa prawidlowe*/
    opcje.odczytano=czytaj(opcje.plik_we,&parametry,&opcje);               
  }

  if(opcje.negatyw == 1 && opcje.odczytano == 0){
    negatyw(&parametry);
    opcje.operacja =1;                                  /*Wiemy wtedy czy mozemy to zapisac*/
  }

  if(opcje.konturowanie == 1 && opcje.odczytano == 0){
    konturowanie(&parametry);
    opcje.operacja=1;
  }
  if(opcje.progowanie == 1 && opcje.odczytano == 0){
    progowanie(&parametry,opcje.w_progu);
    opcje.operacja = 1;
    
  }

  if(opcje.zapisz == 1 && opcje.operacja == 1){
    zapisz(opcje.plik_wy, &parametry);
    opcje.zapisano =1;                                   /*Wiemy ze teraz mozemu juz zwalniac pamiec*/
    
  }

  if(opcje.wyswietlenie == 1 && opcje.zapisano == 1){
    wyswietl(opcje.nazwa_pliku_wy);
   
  }


 if(opcje.zapisano){
  for(int i=0;i<parametry.wymy;i++)               /*zwalniamy pamiec*/
    free(parametry.obraz_wej[i]);
  
  for(int i=0;i<parametry.wymy;i++)
    free(parametry.obraz_wyj[i]);
  
  
  free(parametry.obraz_wej);
  free(parametry.obraz_wyj);
 }
}


/**********************Funkcja Wyswietl************************/

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu display */


void wyswietl(char *n_pliku){
  char polecenie[DL_LINII];   /*bufor gdzie bedzie zapisywac sie nasze polecenie */
  strcpy(polecenie,"display "); /*wpisanie do tablicy slowa display */
  strcat(polecenie,n_pliku); /*dopisanie do naszej tablicy nazwy pliku do wyswietlenia */
  strcat(polecenie," &");
  printf("%s\n",polecenie); /*wydruk kontrolny polecenia */
  system(polecenie); /*wykonanie polecenia */
}

