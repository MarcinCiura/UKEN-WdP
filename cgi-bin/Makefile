CC=gcc -std=gnu99 -Os

all: przyjaciele.exe

przyjaciele.exe: przyjaciele.o baza_danych.o strony.o cgic.o sqlite3.o
	$(CC) $^ -o $@

przyjaciele.o: przyjaciele.c baza_danych.h strony.h
baza_danych.o: baza_danych.c baza_danych.h strony.h sqlite3.h
strony.o: strony.c strony.h cgic.h
cgic.o: cgic.c cgic.h
sqlite3.o: sqlite3.c sqlite3.h
