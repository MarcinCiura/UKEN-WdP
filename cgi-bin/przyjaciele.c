#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "baza_danych.h"
#include "strony.h"

#define DLUGOSC_KODU 8
char spolgloski[] = "bdfghklmnpstwz";
char samogloski[] = "aeiou";

// Wypełnia `moj_kod` losową kombinacją spółgłosek i samogłosek
void wygeneruj_kod(char moj_kod[DLUGOSC_KODU+1]) {
  // Proszę uzupełnić kod tej funkcji
}

void stan_A() {
  // Proszę uzupełnić kod tej funkcji
}

// To jest tylko nagłówek funkcji stan_D
void stan_D();

void stan_B() {
  // Proszę uzupełnić kod tej funkcji
}

void stan_C() {
  char moj_kod[DLUGOSC_KODU+1];
  char *moje_imie;
  char *moj_email;
  char *moj_opis;
  // Proszę uzupełnić kod tej funkcji
}

void stan_D() {
  char imie_osoby[100];
  char opis_osoby[16*1024];
  int id_osoby;
  char *moj_kod;
  // Proszę uzupełnić kod tej funkcji
}

void stan_E() {
  char imie_osoby[100];
  char email_osoby[100];
  int moj_id;
  int id_osoby;
  char *moj_kod;
  // Proszę uzupełnić kod tej funkcji
}

int cgiMain() {
  char *stan = pobierz_opcjonalne_pole_formularza("nowy-stan");
  switch (stan[0]) {
  case '\0':
  case 'A':
    stan_A();
    break;
  case 'B':
    stan_B();
    break;
  case 'C':
    stan_C();
    break;
  case 'D':
    stan_D();
    break;
  case 'E':
    stan_E();
    break;
  default:
    strona_blad("nie umiem obsłużyć stanu %s", stan);
    break;
  }
  free(stan);
  return 0;
}
