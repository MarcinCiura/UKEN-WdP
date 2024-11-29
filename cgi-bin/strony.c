#include "strony.h"

#include <stdio.h>
#include <stdlib.h>

#include "cgic.h"

void start_HTML() {
  cgiHeaderContentType("text/html");
  fprintf(cgiOut,
          "<html>\n"
          "<head><meta charset=\"UTF-8\"></head>\n"
          "<title>Znajdź przyjaciół</title>\n"
          "<style>\n"
          "body,input,textarea {\n"
          "  font-family: Helvetica, Arial, sans-serif;\n"
          "  font-size: 16pt;\n"
          "}\n"
          "body {\n"
          "  background-color: #000;\n"
          "  color: #FF8;\n"
          "  line-height: 1.4;\n"
          "  max-width: 40ex;\n"
          "}\n"
          "input,textarea {\n"
          "  background-color: #FFB;\n"
          "  color: #000;\n"
          "  border-radius: 10px;\n"
          "  padding: 0.25em;\n"
          "}\n"
          "</style>\n"
          "<body>\n"
          "<h2>Znajdź przyjaciół</h2>\n");
}

void koniec_HTML() {
  fprintf(cgiOut,
          "</body>\n"
          "</html>\n");
}

void start_formularza() {
  fprintf(cgiOut, "<form action=\"/cgi-bin/przyjaciele.exe\" method=\"get\">\n");
}

void ukryty_kod(const char *kod) {
  fprintf(cgiOut, "<input type=\"hidden\" name=\"kod\" value=\"%s\">\n", kod);
}

void koniec_formularza(char nowy_stan) {
  fprintf(cgiOut,
          "<input type=\"hidden\" name=\"nowy-stan\" value=\"%c\">\n"
          "<input type=\"submit\" value=\"OK\">\n"
          "</form>\n", nowy_stan);
}

char *pobierz_opcjonalne_pole_formularza(char *nazwa_pola) {
  int dlugosc_pola;
  if (cgiFormStringSpaceNeeded(nazwa_pola, &dlugosc_pola) != cgiFormSuccess) {
    dlugosc_pola = 1;
  }
  char *pole = malloc(dlugosc_pola);
  if (cgiFormString(nazwa_pola, pole, dlugosc_pola) != cgiFormSuccess) {
    pole[0] = '\0';
  }
  return pole;
}

char *pobierz_pole_formularza(char *nazwa_pola) {
  int dlugosc_pola;
  if (cgiFormStringSpaceNeeded(nazwa_pola, &dlugosc_pola) != cgiFormSuccess) {
    strona_blad("nie mogę odczytać pola %s", nazwa_pola);
  }
  char *pole = malloc(dlugosc_pola);
  if (cgiFormString(nazwa_pola, pole, dlugosc_pola) != cgiFormSuccess) {
    strona_blad("nie mogę odczytać pola %s", nazwa_pola);
  }
  return pole;
}

int pobierz_liczbe_z_formularza(char *nazwa_pola) {
  int liczba;
  cgiFormInteger(nazwa_pola, &liczba, 0);
  return liczba;
}

void strona_blad(char *format, char *argument) {
  start_HTML();
  fprintf(cgiOut, "<p>Coś poszło nie tak: ");
  fprintf(cgiOut, format, argument);
  fprintf(cgiOut, ")</p>\n");
  start_formularza();
  koniec_formularza('A');
  koniec_HTML();
  exit(EXIT_FAILURE);
}

void strona_nieznany_kod(char nowy_stan) {
  start_HTML();
  fprintf(cgiOut, "<p>Przykro mi, nie znam tego kodu dostępu</p>\n");
  start_formularza();
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_nie_ma_profili() {
  start_HTML();
  fprintf(cgiOut,
          "<p>Nie ma więcej osób. "
          "Oderwij się od ekranu. Możesz tu wrócić jutro :-)</p>");
  koniec_HTML();
}

void strona_pokaz_kod(const char *kod, char nowy_stan) {
  start_HTML();
  fprintf(cgiOut,
          "<p>Proszę, oto Twój kod dostępu:<br><b>%s</b></p>\n"
          "<p>Proszę Cię, zapamiętaj go :-)</p>\n",
          kod);
  start_formularza();
  ukryty_kod(kod);
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_pobierz_kod(char nowy_stan) {
  start_HTML();
  start_formularza();
  fprintf(cgiOut,
          "<label for=\"kod\">Podaj mi swój kod dostępu:</label>\n"
          "<input type=\"password\" id=\"kod\" name=\"kod\" autofocus><br>\n"
          "<input type=\"checkbox\" id=\"nie-mam-kodu\" name=\"nie-mam-kodu\" value=\"1\">\n"
          "<label for=\"bez-kodu\">Nie mam kodu. Chcę się zarejestrować :-)</label><br>\n");
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_ankieta(char nowy_stan) {
  start_HTML();
  fprintf(cgiOut,
          "<p>Jeśli chcesz, wypełnij tę ankietę o&nbsp;sobie</p>\n");
  start_formularza();
  fprintf(cgiOut,
          "<label for=\"imie\">Jak masz na imię?</label><br>\n"
          "<input type=\"text\" id=\"imie\" name=\"imie\" size=\"40\" required autofocus><br>\n"
          "<label for=\"email\">Jaki jest Twój adres email?</label><br>\n"
          "<input type=\"email\" id=\"email\" name=\"email\" size=\"40\" required><br>\n"
          "<label for=\"opis\">Tu możesz napisać na przykład\n"
          "o&nbsp;swoich studiach lub pracy, o&nbsp;podróżach,\n"
          "o&nbsp;tym, jakiej muzyki słuchasz, jakie filmy oglądasz,\n"
          "jakie książki czytasz, jakie jedzenie lubisz,\n"
          "jakie sporty uprawiasz, czym się interesujesz</label></br>\n"
          "<textarea id=\"opis\" name=\"opis\" cols=\"39\" rows=\"12\" required></textarea><br>\n");
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_pokaz_opis(
    const char *kod,
    const char *imie_osoby,
    const char *opis_osoby,
    int id_osoby,
    char nowy_stan) {
  start_HTML();
  fprintf(cgiOut, "<p>");
  cgiHtmlEscape(opis_osoby);
  fprintf(cgiOut, "</br>\n");
  cgiHtmlEscape(imie_osoby);
  fprintf(cgiOut, "</p>\n");
  start_formularza();
  fprintf(cgiOut,
          "<input type=\"hidden\" id=\"id-osoby\" name=\"id-osoby\" value=\"%d\">\n"
          "<input type=\"checkbox\" id=\"chce-poznac\" name=\"chce-poznac\" value=\"1\">\n"
          "<label for=\"chce-poznac\">Chcę poznać tę osobę :-)</label><br>\n",
          id_osoby);
  ukryty_kod(kod);
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_czekaj(const char *kod, const char *imie_osoby, char nowy_stan) {
  start_HTML();
  fprintf(cgiOut, "<p>Cieszymy się. Jeśli ");
  cgiHtmlEscape(imie_osoby);
  fprintf(cgiOut, " też da nam znać, że chce Cię poznać, to zobaczy Twój adres email</p>");
  start_formularza();
  ukryty_kod(kod);
  koniec_formularza(nowy_stan);
  koniec_HTML();
}

void strona_pokaz_email_osoby(const char *imie_osoby, const char *email_osoby) {
  start_HTML();
  fprintf(cgiOut, "<p>Bingo :-) ");
  cgiHtmlEscape(imie_osoby);
  fprintf(cgiOut, " &lt;");
  cgiHtmlEscape(email_osoby);
  fprintf(cgiOut, "&gt; też chce Cię poznać. Napisz email. To wszystko na dziś :-)</p>\n");
  koniec_HTML();
}
