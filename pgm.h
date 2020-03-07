#ifndef PGM_H   /*Jesli nie zostala zdefiniowana stala PGM_H, zabezpieczenie przed powtornym deklarowaniem stałych*/

#define PGM_H  /* To zdefiniuj */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2         
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define B_NIEPOPRAWNYFORMAT -5
#define B_PAMIEC -6
#define B_WPROG -7              /*Wartosc progu podanego przez uzytkownika nie miesci sie w przedziale od 0 do 100 lub jej brak*/
#define B_NIEPODANO_KOLORU -8   


/**************************************************Deklaracja struktury************************/

 typedef struct  {
  int **obraz_wej;              /*tablica dynamiczna do ktorej zapisujemy obraz wejsciowy*/
  int **obraz_wyj;              /*tablice do ktorej zapisujemy obraz juz przetworzony*/
  int **obraz_red;              /*Kazdy kolor składowy ma swoją tablice dwuwymiarową*/
  int **obraz_green;
  int **obraz_blue;
  
  int kolor;                           /*Czy obrazek jest kolorowy*/                           
  int wymx;                            /*szerokosc obrazka*/
  int wymy;                            /*wysokosc  obrazka*/
  int odcieni;                         /*ilosc odcieni szarosci*/  

} obraz;

  typedef struct {                        /*struktura do zapamietywania opcji podanych w wywołaniu programów */
    FILE *plik_we, *plik_wy;              /* uchwyty do pliku wej. i wyj. */
    char *nazwa_pliku_we;                 /*bufor do ktorego zapisujemy nazwe pliku wejsciowego*/
    char *nazwa_pliku_wy;
    int negatyw;                          /*Jesli 1 to wykonaj operacje negatywu*/
    int progowanie;                       /*Analogicznie*/
    int konturowanie;      
    int wyswietlenie;
    int czytaj;                          /*Jesli 1 to wczytaj obraz*/            
    int zapisz;                          /*Jesli 1 to zapisz obraz*/
    int odczytano;                       /*zmienna pomocnicza do sprawdzenia czy zostal prawidlowo  odczytany plik */
    int prawidlowe_opcje;                /*jesli 0 to w wywolaniu nie ma bledow*/                
    int operacja;                        /*okreslanie czy zostala wykonana juz jakas operacja, potrzebne do okreslenia czy mozna juz zapisac obraz  */  
    int zapisano;                        /*Jesli 1 to znaczy ze obraz zostal zapisany*/
    int w_progu;                         /* wartosc progu dla opcji progowanie */
    int red;                             /*Jesli uzytkownik chce przetwarzac kolor czerwony to red jest rowne 1*/
    int green;                           /*Analogicznie*/
    int blue;
    int grey;


    
  }w_opcje;



/********************************************Prototypy funkcji********************************/

int czytaj(FILE *plik,obraz *wsk, w_opcje *wybor);
void zapisz(FILE *plik,obraz *wsk);
void negatyw( obraz *wsk);
void progowanie(obraz *wsk, int prog_procent);
void konturowanie(obraz *wsk);
void wyzeruj_opcje(w_opcje * wybor);
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);




#endif