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

void
dcols(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky);

void irow(char tabulka[MAX]);


int main(int argc, char *argv[]) {
    char delimiter = 0, tabulka[MAX] = {0};
    int i = 0, riadok = 0, stlpec = 0, command_stlpec = 0, command_stlpec_do = 0, dlzka_tabulky = 0, pomocna_stlpec = 0;
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
    while (1) {
        i = 0;
        while (i < argc) {
            pomocna_stlpec = 0;
            if ((strcmp(argv[i], "-d")) == 0) {
                delimiter = *argv[++i];
                dlzka_tabulky = nacitaj(tabulka, &riadok, &stlpec, delimiter);
//            printf("riadok: %d, stlpec: %d\n", riadok, stlpec);
            } else if (strcmp(argv[i], argument_irow) == 0) {
//                    irow(tabulka);
            } else if (strcmp(argv[i], argument_arow) == 0) {

            } else if (strcmp(argv[i], argument_drow) == 0) {

            } else if (strcmp(argv[i], argument_drows) == 0) {

            } else if (strcmp(argv[i], argument_icol) == 0) {
                command_stlpec = (*argv[++i] - '0');                      //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0') {
                    icol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                    if (command_stlpec > 0 && command_stlpec <= stlpec) {
                        pomocna_stlpec++;
                    }
//                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                    command_stlpec = 0;
                }
            } else if (strcmp(argv[i], argument_acol) == 0) {
                if (delimiter != 0 && tabulka[0] != '\0') {
                    acol(tabulka, delimiter, dlzka_tabulky);
                    pomocna_stlpec++;
                }
            } else if (strcmp(argv[i], argument_dcol) == 0) {
                command_stlpec = (*argv[++i] - '0');                      //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0') {
                    dcol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                    if (command_stlpec > 0 && command_stlpec <= stlpec) {
                        pomocna_stlpec--;
                    }
//                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                    command_stlpec = 0;
                }
            } else if (strcmp(argv[i], argument_dcols) == 0) {
                command_stlpec = (*argv[++i] - '0');                      //pretypovanie
                command_stlpec_do = (*argv[++i] - '0');                      //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0') {
                dcols(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, dlzka_tabulky);
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec && command_stlpec_do >= command_stlpec) {
                        pomocna_stlpec -= command_stlpec_do - command_stlpec + 1;
                    }
//                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                    command_stlpec = 0;
                    command_stlpec_do = 0;
                }
            }
            i++;
        }                                                                                       //TODO Podmienku ze ked neni vobec ziaden arguemnt nech aspon vypise obsah, inak vypis klasicky vo funkciach
//        printf("%s\n", tabulka);
        printf("\t\t\triadok: %d, stlpec: %d\n", riadok, stlpec + pomocna_stlpec);
    }
    return 0;
}

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter) {
    char c = 0;
    int pocet_znakov = 0, i = 0, pomocna_stlpec = 1;
    while ((c = getc(stdin)) != EOF) {
        if (c == '\n') {
            tabulka[i] = '\0';
            *riadok += 1;
            return pocet_znakov;
        }
        if (c == delimiter) {
            pomocna_stlpec += 1;
        }
        tabulka[pocet_znakov++] = c;
        i++;
        *stlpec = pomocna_stlpec;
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
            i++;
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
//    printf("\n");
}

void acol(char tabulka[MAX], char delimiter, int dlzka_tabulky) {
    tabulka[dlzka_tabulky] = delimiter;
    tabulka[dlzka_tabulky+1] = '\0';
    printf("%s", tabulka);
}

void dcol(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        int i = 0, kontrola = 1;
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola == command_stlpec) { //osetrenie pripadu kedy chceme odstranit posledny stlpec
            } else {
                if (kontrola == 2 && command_stlpec == 1 &&
                    tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat prvy stlpec
                } else {
                    printf("%c", tabulka[i]);
                }
            }
            i++;
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void dcols(char tabulka[MAX], int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky) {
    
    if (command_stlpec > 0 && command_stlpec <= *stlpec && command_stlpec_do <= *stlpec && command_stlpec_do >= command_stlpec) {
        int i = 0, kontrola = 1;
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola >= command_stlpec && kontrola <= command_stlpec_do) {
            } else {
                if (kontrola-1 == command_stlpec_do && command_stlpec == 1 && tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat od prveho stlpca
                } else {
                    printf("%c", tabulka[i]);
                }
            }
            i++;
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec || command_stlpec_do > *stlpec || command_stlpec_do < command_stlpec)\n");
    }
}
