//Richard Gajdosik, IDE = CLION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO Vyriesit instanciu kde sa upravuje tabulka viacerymi prikazmi za sebou, pri najlepsom kodit uz na linuxe cez command line
// todo prvy riadok pravdepodobne nikdy nebudem chciet vymazat, to budem musiet posetrit aby vsetky odstranovania riadkov zacinali od 1 a vsetky upravy tabulky pravdepodobne tiez
#define MAX 10000

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter);

void icol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void acol(char *tabulka, char delimiter, int dlzka_tabulky);

void dcol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void dcols(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky);


int main(int argc, char *argv[]) {
    char delimiter = 0, tabulka[MAX] = {0};
    int i = 0, riadok = 0, stlpec = 0, command_riadok = 0, command_riadok_do = 0, command_stlpec = 0, command_stlpec_do = 0, dlzka_tabulky = 0, pomocna_stlpec = 0, pomocna_riadok = 0;
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
                command_riadok = (*argv[++i] - '0') +
                                 1; //magickych +1 pretoze nechcem vymazat prvy riadok ktory je len na upresnenie co presne aky stlpec je ake data
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_riadok > 1 && command_riadok <= riadok) {
                        if (command_riadok == riadok) {
                            pomocna_riadok++;
                            for (int g = 0; g < stlpec - 1; g++) {
                                printf("%c", delimiter);
                            }
                            printf("\n"); //todo zbierat chybne hlasky pravdepodobne ?
                        }
                    }
                }
                command_riadok = 0;
            } else if (strcmp(argv[i], argument_arow) ==
                       0) { //TODO vyriesit nacitavanie aby bolo konecne co znamena ze budem moct aplikovat totok

            } else if (strcmp(argv[i], argument_drow) == 0) {
                command_riadok = (*argv[++i] - '0') +
                                 1;//magickych +1 pretoze nechcem vymazat prvy riadok ktory je len na upresnenie co presne aky stlpec je ake data //todo zase problem s tym ze cisla su ulozene ako char
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_riadok > 1 && command_riadok <= riadok) {
                        if (command_riadok == riadok) {
                            tabulka[0] = '\0';
                            pomocna_riadok--;
                        }
                    }
                }
                command_riadok = 0;
            } else if (strcmp(argv[i], argument_drows) == 0) {
                command_riadok = (*argv[++i] - '0') + 1;    //magickych +1 pretoze nechcem vymazat prvy riadok ktory je len na upresnenie co presne aky stlpec je ake data
                command_riadok_do = (*argv[++i] - '0') + 1;//magickych +1 pretoze nechcem vymazat prvy riadok ktory je len na upresnenie co presne aky stlpec je ake data
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_riadok > 1 && command_riadok <= riadok) { //todo odstranit tieto podmienky nakolko su pravdepodobne zbytocne
                        if(riadok <= command_riadok_do){
                        tabulka[0] = '\0';
                        pomocna_riadok--;
                        }
                    }
                }
                command_riadok = 0;
                command_riadok_do = 0;
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
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec &&
                        command_stlpec_do >= command_stlpec) {
                        pomocna_stlpec -= command_stlpec_do - command_stlpec + 1;
                    }
//                printf("\nriadok: %d, stlpec: %d\n", riadok, stlpec);
                    command_stlpec = 0;
                    command_stlpec_do = 0;
                }
            }
            i++;
        }                                                                                       //TODO Podmienku ze ked neni vobec ziaden arguemnt nech aspon vypise obsah, inak vypis klasicky vo funkciach
        if (tabulka[0] != '\0') {
            printf("%s\t\t\triadok: %d, stlpec: %d\n", tabulka, riadok + pomocna_riadok, stlpec + pomocna_stlpec);
        }
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
} //TODO vyriesit nacitavanie cisel nad 10 kedze je to vsetko char

void icol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola == command_stlpec) {
                pomocna_tabulka[j++] = delimiter;
                ++kontrola;
            }
            pomocna_tabulka[j++] = tabulka[i];
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
//    printf("\n");
}

void acol(char *tabulka, char delimiter, int dlzka_tabulky) {
    tabulka[dlzka_tabulky] = delimiter;
    tabulka[dlzka_tabulky + 1] = '\0';
}

void dcol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        int i = 0, j = 0, kontrola = 1;
        char pomocna_tabulka[MAX] = {0};
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola == command_stlpec) { //osetrenie pripadu kedy chceme odstranit posledny stlpec
            } else {
                if (kontrola == 2 && command_stlpec == 1 &&
                    tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat prvy stlpec
                } else {
                    pomocna_tabulka[j++] = tabulka[i];
                }
            }
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void dcols(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky) {
    if (command_stlpec > 0 && command_stlpec <= *stlpec && command_stlpec_do <= *stlpec &&
        command_stlpec_do >= command_stlpec) {
        int i = 0, j = 0, kontrola = 1;
        char pomocna_tabulka[MAX] = {0};
        while (i < dlzka_tabulky) {
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola >= command_stlpec && kontrola <= command_stlpec_do) {
            } else {
                if (kontrola - 1 == command_stlpec_do && command_stlpec == 1 &&
                    tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat od prveho stlpca
                } else {
                    pomocna_tabulka[j++] = tabulka[i];
                }
            }
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec || command_stlpec_do > *stlpec || command_stlpec_do < command_stlpec)\n");
    }
}
