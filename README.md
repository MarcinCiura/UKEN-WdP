# Program `przyjaciele`
Program `przyjaciele` to serwis internetowy, dzięki któremu można szukać przyjaciół.

Użytkownik serwisu loguje się do niego, wpisując swój kod dostępu.
Po zalogowaniu użytkownik przegląda profile innych osób, które zarejestrowały się w serwisie.

Użytkownik może zaznaczyć, że chciałby poznać którąś z tych osób.
Jeśli ta osoba już wcześniej zaznaczyła, że chciałaby poznać użytkownika, to serwis przekaże użytkownikowi adres email tej osoby.
Jeśli ta osoba w przyszłości zaznaczy, że chciałaby poznać użytkownika, to serwis przekaże tej osobie adres email użytkownika.
Dalszy los znajomości jest w rękach użytkownika i tej osoby.

Użytkownik, który nie ma kodu dostępu, otrzyma ten kod, gdy wypełni krótką ankietę o sobie.

## Kod źródłowy programu
Kod źródłowy programu `przyjaciele` składa się z kilku plików w katalogu `cgi-bin`:
* [cgic.c](cgi-bin/cgic.c) i [cgic.h](cgi-bin/cgic.h) — moduł, który obsługuje standard tworzenia serwisów internetowych, zwany CGI (Common Gateway Interface). Autorem tego modułu jest [Thomas Boutell](https://github.com/boutell/cgic)
* [sqlite3.c](cgi-bin/sqlite3.c) i [sqlite3.h](cgi-bin/sqlite3.h) — biblioteka, która obsługuje bazę danych [SQLite](https://sqlite.org/). Głównym autorem tej biblioteki jest D. Richard Hipp
* [baza_danych.c](cgi-bin/baza_danych.c) i [baza_danych.h](cgi-bin/baza_danych.h) — moduł komunikacji z bazą danych SQLite. Współautorem tego modułu jest pan Marek Zarzycki. W pliku [baza_danych.h](cgi-bin/baza_danych.h) znajduje się opis funkcji tego modułu
* [strony.c](cgi-bin/strony.c) i [strony.h](cgi-bin/strony.h) — moduł, który tworzy strony internetowe i pobiera z nich dane. W pliku [strony.h](cgi-bin/strony.h) znajduje się opis funkcji tego modułu
* [przyjaciele.c](cgi-bin/przyjaciele.c) — główny moduł programu. Ten moduł zawiera funkcje, które tworzą strony internetowe na podstawie danych przekazanych przez użytkownika i danych zapisanych w bazie danych. Aby program `przyjaciele` działał, należy uzupełnić ten moduł zgodnie z poniższą instrukcją

## Co robić?
1. W terminalu wpisać na próbę polecenia `git`, `make` i `gcc`. Aby wykonać zadanie, każde z tych poleceń musi być zainstalowane.
2. Założyć własne konto na GitHubie (https://github.com) i zalogować się na to konto
3. W prawym górnym rogu strony https://github.com/MarcinCiura/UKEN-WdP/ kliknąć **Fork** i postępować według instrukcji z [tej strony](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo#forking-a-repository)
4. Pobrać na komputer pliki ze swojej kopii repozytorium zgodnie z instrukcją z [tej strony](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo#forking-a-repository)
5. Zmienić katalog: `cd UKEN-WdP/cgi-bin`
6. Otworzyć w edytorze plik `przyjaciele.c` i uzupełnić w nim na początek funkcję `stan_A` zgodnie z poniższym schematem blokowym
7. Zapisać plik `przyjaciele.c`
8. Wydać polecenie `make`
9. Jeśli podczas kompilowania programu wystąpią błędy, poprawić kod w pliku `przyjaciele.c` i wrócić do punktu 7
10. Powstał program `przyjaciele.exe`, hurra!
11. Zmienić katalog: `cd ..`
12. Uruchomić plik `./uruchom.bat`
13. Otworzyć w przeglądarce stronę http://localhost:8000/cgi-bin/przyjaciele.exe i cieszyć się pierwszą stroną serwisu internetowego
14. Potem przerwać działanie pliku `./uruchom.bat` kombinacją klawiszy Ctrl+C i uzupełniać w edytorze kolejne funkcje z pliku `przyjaciele.c`: `stan_B`, `wygeneruj_kod`, `stan_C`, `stan_D`, `stan_E`. Wyniki pracy można sprawdzać na bieżąco, powtarzając punkty 7-13
15. Na koniec dnia zapisać zmiany na swoim koncie na GitHubie: wydać kolejno polecenia `git add cgi-bin/przyjaciele.c`, `git commit -m "Opis zmian, na przykład: uzupełniono funkcje do stan_C"`, `git push origin main`

## Schematy blokowe tych funkcji, które należy uzupełnić

### Funkcja `stan_A`
![Funkcja `stan_A`](images/stan_A.png)

### Funkcja `stan_B`
![Funkcja `stan_B`](images/stan_B.png)

### Funkcja `wygeneruj_kod`
![Funkcja `wygeneruj_kod`](images/wygeneruj_kod.png)

### Funkcja `stan_C`
![Funkcja `stan_C`](images/stan_C.png)

### Funkcja `stan_D`
![Funkcja `stan_D`](images/stan_D.png)

### Funkcja `stan_E`
![Funkcja `stan_E`](images/stan_E.png)
