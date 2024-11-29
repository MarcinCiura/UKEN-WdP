#include "baza_danych.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#include "strony.h"

static void zglos_blad_i_zakoncz_program(sqlite3 *db) {
  fprintf(stderr, "Błąd SQLite: %s\n", sqlite3_errmsg(db));
  sqlite3_close(db);
  exit(EXIT_FAILURE);
}

sqlite3 *zaloz_baze_danych() {
  static char nazwa_pliku[] = "baza_danych.sqlite";
  static char sql[] = "CREATE TABLE IF NOT EXISTS Osoby(\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  kod TEXT NOT NULL,\n"
    "  imie TEXT NOT NULL,\n"
    "  email TEXT NOT NULL,\n"
    "  opis TEXT NOT NULL);\n"
    "CREATE UNIQUE INDEX IF NOT EXISTS index_Osoby_kod ON Osoby(kod);\n"
    "CREATE TABLE IF NOT EXISTS ChcePoznac(\n"
    "  id_kto INTEGER NOT NULL REFERENCES Osoby(id),\n"
    "  id_kogo INTEGER NOT NULL REFERENCES Osoby(id),\n"
    "  chce_poznac INTEGER NOT NULL);\n"
    "CREATE UNIQUE INDEX IF NOT EXISTS \n"
    "  index_chce_poznac ON ChcePoznac(id_kto, id_kogo);";
  sqlite3* db;
  char* errmsg;

  if (sqlite3_open(nazwa_pliku, &db) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
    fprintf(stderr, "Błąd SQLite: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }
  return db;
}

void zapisz_moj_profil(
    char *moj_kod,
    char *moje_imie,
    char *moj_email,
    char *moj_opis) {
  char *dane[4] = {moj_kod, moje_imie, moj_email, moj_opis};
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;
  int i;

  if (sqlite3_prepare_v2(
          db,
          "INSERT INTO Osoby(kod, imie, email, opis) VALUES(?,?,?,?)",
          -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  for (i = 0; i < 4; i++) {
    if (sqlite3_bind_text(stmt, i + 1, dane[i], -1, SQLITE_STATIC) !=
        SQLITE_OK) {
      zglos_blad_i_zakoncz_program(db);
    }
  }
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    zglos_blad_i_zakoncz_program(db);
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

int odczytaj_id_osoby(char *kod_osoby) {
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db,
                         "SELECT id FROM Osoby WHERE kod = ?",
                         -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  if (sqlite3_bind_text(stmt, 1, kod_osoby, -1, SQLITE_STATIC) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return id;
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  strona_blad("Nie znam osoby z kodem %s", kod_osoby);
  return 0;
}

int kod_jest_zarejestrowany(char *kod_osoby) {
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db,
                         "SELECT id FROM Osoby WHERE kod = ?",
                         -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  if (sqlite3_bind_text(stmt, 1, kod_osoby, -1, SQLITE_STATIC) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}

void odczytaj_imie_i_email_osoby(
    int id_osoby, char *imie_osoby, char *email_osoby) {
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(
          db,
          "SELECT imie, email FROM Osoby WHERE id = ?",
          -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  if (sqlite3_bind_int(stmt, 1, id_osoby) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *imie = sqlite3_column_text(stmt, 0);
    const unsigned char *email = sqlite3_column_text(stmt, 1);
    // TODO: bezpiecznie
    strcpy(imie_osoby, (const char*)imie);
    strcpy(email_osoby, (const char*)email);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  strona_blad("nie znam osoby z danym id", "");
  exit(EXIT_FAILURE);
}

void zapisz_czy_chce_poznac_te_osobe(
    int id_kto, int id_kogo, int chce_poznac) {
  int dane[3] = {id_kto, id_kogo, chce_poznac};
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;
  int i;

  if (sqlite3_prepare_v2(
          db,
          "INSERT INTO ChcePoznac(id_kto, id_kogo, chce_poznac) VALUES(?,?,?)",
          -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  for (i = 0; i < 3; i++) {
    if (sqlite3_bind_int(stmt, i + 1, dane[i]) != SQLITE_OK) {
      zglos_blad_i_zakoncz_program(db);
    }
  }
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    zglos_blad_i_zakoncz_program(db);
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

int chce_poznac(int id_kto, int id_kogo) {
  int dane[2] = {id_kto, id_kogo};
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;
  int i;

  if (sqlite3_prepare_v2(
          db,
          "SELECT COALESCE((SELECT chce_poznac FROM ChcePoznac "
          "WHERE id_kto = ? AND id_kogo = ?), 0)",
          -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  for (i = 0; i < 2; i++) {
    if (sqlite3_bind_int(stmt, i + 1, dane[i]) != SQLITE_OK) {
      zglos_blad_i_zakoncz_program(db);
    }
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int chce = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chce;
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  fprintf(stderr, "To nie powinno się zdarzyć: brak wyników\n");
  exit(EXIT_FAILURE);
}

int wybierz_osobe(
    char *moj_kod,
    char *imie_osoby,
    char *opis_osoby,
    int *id_osoby) {
  sqlite3* db = zaloz_baze_danych();
  sqlite3_stmt *stmt;
  int i;

  if (sqlite3_prepare_v2(
          db,
          "SELECT id, imie, opis FROM Osoby "
          "WHERE NOT EXISTS (SELECT * FROM ChcePoznac "
          " WHERE id_kto = (SELECT id FROM Osoby WHERE kod = ?) "
          " AND id_kogo = id) "
          "AND id <> (SELECT id FROM Osoby WHERE kod = ?) "
          "ORDER BY RANDOM() LIMIT 1",
          -1, &stmt, NULL) != SQLITE_OK) {
    zglos_blad_i_zakoncz_program(db);
  }
  for (i = 1; i <= 2; i++) {
    if (sqlite3_bind_text(stmt, i, moj_kod, -1, SQLITE_STATIC) != SQLITE_OK) {
      zglos_blad_i_zakoncz_program(db);
    }
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *imie = sqlite3_column_text(stmt, 1);
    const unsigned char *opis = sqlite3_column_text(stmt, 2);
    *id_osoby = sqlite3_column_int(stmt, 0);
    // TODO: bezpiecznie
    strcpy(imie_osoby, (const char*)imie);
    strcpy(opis_osoby, (const char*)opis);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}
