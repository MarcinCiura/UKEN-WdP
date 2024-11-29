// TODO
char *pobierz_opcjonalne_pole_formularza(char *nazwa_pola);
char *pobierz_pole_formularza(char *nazwa_pola);
int pobierz_liczbe_z_formularza(char *nazwa_pola);

// Wypisuje komunikat o błędzie
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `A`
void strona_blad(char *format, char *argument);

// Wypisuje komunikat o tym, że program nie zna tego kodu dostępu,
// który wprowadził użytkownik
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
void strona_nieznany_kod(char nowy_stan);

// Wypisuje komunikat o tym, że program wyświetlił użytkownikowi profile
// wszystkich innych użytkowników
void strona_nie_ma_profili();

// Wypisuje kod dostępu do serwisu
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
//
// Pola formularza:
// "kod" - ukryty kod dostępu
void strona_pokaz_kod(const char *kod, char nowy_stan);

// Prosi, żeby wpisać w formularzu kod dostępu
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
//
// Pola formularza:
// "kod" - tu użytkownik wpisuje swój kod dostępu
// "nie-mam-kodu" - tu użytkownik zaznacza, że nie ma kodu dostępu
void strona_pobierz_kod(char nowy_stan);

// Prosi, żeby wypełnić formularz z ankietą
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
//
// Pola formularza:
// "imie" - tu użytkownik wpisuje swoje imię
// "email" - tu użytkownik wpisuje swój email
// "opis" - tu użytkownik pisze o sobie
void strona_ankieta(char nowy_stan);

// Wypisuje `opis_osoby` i podpis: `imie_osoby`
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
//
// Pola formularza:
// "kod" - ukryty kod dostępu
// "id-osoby" - ukryty identyfikator osoby
// "chce-poznac" - tu użytkownik zaznacza, czy chce poznać tę osobę
void strona_pokaz_opis(
    const char *kod,
    const char *imie_osoby,
    const char *opis_osoby,
    int id_osoby,
    char nowy_stan);

// Potwierdza, że użytkownik chce poznać osobę o imieniu `imie_osoby`
// Kiedy użytkownik naciśnie OK, program przejdzie do stanu `nowy_stan`
//
// Pola formularza:
// "kod" - ukryty kod dostępu
void strona_czekaj(const char *kod, const char *imie_osoby, char nowy_stan);

// Wypisuje `imię_osoby` i `email_osoby`
void strona_pokaz_email_osoby(const char *imie_osoby, const char *email_osoby);
