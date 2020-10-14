//Richard Gajdosik, IDE = CLION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO Vyriesit instanciu kde sa upravuje tabulka viacerymi prikazmi za sebou, pri najlepsom kodit uz na linuxe cez command line

#define MAX 10000

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter);

void icol(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void acol(char tabulka[MAX], char delimiter, int dlzka_tabulky);

void dcol(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void dcols(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky);

void irow(char tabulka[MAX]);


int main(int argc, char *argv[]) {
    char delimiter = 0, tabulka[MAX] = "0";
    int i = 0, riadok = 0, stlpec = 0, command_stlpec = 0, command_stlpec_do = 0, dlzka_tabulky = 0;
//            irow R - vloží řádek tabulky před řádek R > 0 (insert-row).
//            arow - přidá nový řádek tabulky na konec tabulky (append-row).
//            drow R - odstraní řádek číslo R > 0 (delete-row).
//            drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
//            icol C - vloží prázdný sloupec před sloupec daný číslem C.
//            acol - přidá prázdný sloupec za poslední sloupec.
//            dcol C - odstraní sloupec číslo C.
//            dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.
    char argument_irow[MAX] = "irow";
    char argument_arow[MAX] = "arow";
    char argument_drow[MAX] = "drow";
    char argument_drows[MAX] = "drows";
    char argument_icol[MAX] = "icol";
    char argument_acol[MAX] = "acol";
    char argument_dcol[MAX] = "dcol";
    char argument_dcols[MAX] = "dcols";

//    printf("\n-----------------------------------\n%s", tabulka);
    i = 0;
    while (i < argc) {
        if ((strcmp(argv[i], "-d")) ==
            0) {                                                 //TODO musi sa realne aj hybat kurzor po argumentoch cize miesto i+1 dorobit ++i a otestovat
            delimiter = *argv[++i];
            dlzka_tabulky = nacitaj(tabulka, &riadok, &stlpec, delimiter);
            printf("riadok: %d, stlpec: %d\n", riadok, stlpec);
        } else if (strcmp(argv[i], argument_irow) == 0) {
//                    irow(tabulka);
        } else if (strcmp(argv[i], argument_arow) == 0) {

        } else if (strcmp(argv[i], argument_drow) == 0) {

        } else if (strcmp(argv[i], argument_drows) == 0) {

        } else if (strcmp(argv[i], argument_icol) == 0) {
            command_stlpec = (*argv[++i] - '0');                      //pretypovanie
            if (delimiter != 0 && tabulka[0] != '\0') {
                icol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
//                printf("riadok: %d, stlpec: %d\n", riadok, stlpec);
                command_stlpec = 0;
            }
        } else if (strcmp(argv[i], argument_acol) == 0) {
            if (delimiter != 0 && tabulka[0] != '\0') {
                acol(tabulka, delimiter, dlzka_tabulky);
            }
        } else if (strcmp(argv[i], argument_dcol) == 0) {
            command_stlpec = (*argv[++i] - '0');                      //pretypovanie
            if (delimiter != 0 && tabulka[0] != '\0') {
                dcol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                command_stlpec = 0;
            }
        } else if (strcmp(argv[i], argument_dcols) == 0) {
            command_stlpec = (*argv[++i] - '0');                      //pretypovanie
            command_stlpec_do = (*argv[++i] - '0');                      //pretypovanie
            if (delimiter != 0 && tabulka[0] != '\0') {
                dcols(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, dlzka_tabulky);
                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                command_stlpec = 0;
                command_stlpec_do = 0;
            }
        }
        i++;
    }
    return 0;
}

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter) {
    char c = 0;
    int pocet_znakov = 0, i = 0;
    while ((c = getc(stdin)) != EOF) {
        if (*riadok == 0) {
            if (c == delimiter) {
                *stlpec += 1;
            }
        }
        if (c == '\n') {
            *riadok += 1;
        }
        tabulka[pocet_znakov++] = c;
//        printf("\n-----------------------------------\n%s", tabulka);
        ++i;
        if (i == 143) {
            *stlpec += 1;
            *riadok += 1;
            return pocet_znakov;
        }
    }
}

void irow(char tabulka[MAX]) {
    printf("\n................................\n%s", tabulka);
}

void icol(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, kontrola = 1;
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola == command_stlpec) {
                printf("%c", delimiter);
                ++kontrola;
            }
            printf("%c", tabulka[i]);
            if (tabulka[i] == '\n') {
                kontrola = 1;
            }
            i++;
        }
        *stlpec += 1;
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
    printf("\n");
}

void acol(char tabulka[MAX], char delimiter, int dlzka_tabulky) {
    int i = 0;
    while (i < dlzka_tabulky) {
        if (tabulka[i] == '\n') {
            printf("%c", delimiter);
        }
        printf("%c", tabulka[i]);
        i++;
    }
}

void dcol(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {

        int i = 0, kontrola = 1;
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola == command_stlpec && tabulka[i] != '\n') { //osetrenie pripadu kedy chceme odstranit poslednu tabulku
            } else {
                if (kontrola == 2 && command_stlpec == 1 && tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat prvy stlpec
                } else {
                    printf("%c", tabulka[i]);
                }
            }
            if (tabulka[i] == '\n') {
                kontrola = 1;
            }
            i++;
        }
        *stlpec -= 1;
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void dcols(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky){
    printf("slpec od: %d slpec do: %d\n", command_stlpec, command_stlpec_do);
}
