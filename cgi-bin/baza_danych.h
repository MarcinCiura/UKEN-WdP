// Zapisuje do bazy danych `moj_kod`, `moje_imie`, `moj_email` i `moj_opis`
void zapisz_moj_profil(
    char *moj_kod,
    char *moje_imie,
    char *moj_email,
    char *moj_opis);

// Zwraca taki id_osoby, który odpowiada polu `kod_osoby`
// Jeśli `kod_osoby` nie odpowiada żadnej osobie, zgłasza błąd
int odczytaj_id_osoby(char *kod_osoby);

// Zwraca 1 jeśli `kod_osoby` jest zapisany w bazie danych
int kod_jest_zarejestrowany(char *kod_osoby);

// Odczytuje z bazy danych takie `imie_osoby` i `email_osoby`,
// które odpowiadają danemu `id_osoby`
void odczytaj_imie_i_email_osoby(
    int id_osoby, char *imie_osoby, char *email_osoby);

// Zapisuje do bazy danych `id_kto`, `id_kogo` i `chce_poznac`
void zapisz_czy_chce_poznac_te_osobe(
    int id_kto, int id_kogo, int chce_poznac);

// Jeśli `id_kto` chce poznać `id_kogo`, zwraca 1
// Jeśli `id_kto` nie chce poznać `id_kogo` lub nie zna `id_kogo`, zwraca 0
int chce_poznac(int id_kto, int id_kogo);

// Odczytuje z bazy danych losową spośród tych osób,
// których `moj_kod` jeszcze nie widział, i zwraca 1
// Jeśli nie ma takiej osoby, zwraca 0
int wybierz_osobe(
    char *moj_kod,
    char *imie_osoby,
    char *opis_osoby,
    int *id_osoby);
