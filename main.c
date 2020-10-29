//Richard Gajdosik, IDE = CLION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO Vyriesit instanciu kde sa upravuje tabulka viacerymi prikazmi za sebou, pri najlepsom kodit uz na linuxe cez command line
// todo prvy riadok pravdepodobne nikdy nebudem chciet vymazat, to budem musiet posetrit aby vsetky odstranovania riadkov zacinali od 1 a vsetky upravy tabulky pravdepodobne tiez
// TODO čo sa stane ked uzivatel vymaze vsetky riadky
// TODO napísať funkciu ktora kompletne prebehne argumenty a na jeden šup skontroluje či sú korektné
// TODO zistiť či vlastne prvy riadok chcem upravovať alebo vôbec nie a zjednotiť rozhodnutie naprieč celým projektom
// TODO Jo a ještě jedna věc, musím nahrazovat všechny oddělovače těch buněk na výstupu prvním znakem z delim? Nebo ty původní tam můžu nechat?
// todo nakodit funkcie ktore skontroluju ci dalsi argv je cislo
// TODO Vymysliet v podmienkach ako sa popasovat s chybnymi argumentami, napriklad cset cislo bez STR, ked by malo byt str tak skontrolujem či dalšie není argument, ak císlo skontrolujem ci sa tam proste nachadza cislo
// TODO okomentovať
// TODO spravit limit na dlzku stlpca a riadku celkovo, pravdepodobne redo nacitavanie
// todo nekonecny while cyklus prerobit na otazku ci char c, ktory si budem preposielat sa nerovna EOF
// todo presunut vsetky if podmienky do funkcii, vyzera to cistejsie
#define MAX 10000

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter);

void icol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void acol(char *tabulka, char delimiter, int dlzka_tabulky);

void dcol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void dcols(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky);

void cset(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky, char STR[]);

void toLower(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void toUpper(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);

void Round(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);

void Int(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);

void copy(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky);

void swap(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky);

int main(int argc, char *argv[]) {
    char delimiter = 0, tabulka[MAX] = {0}, STR[MAX] = {0}, cislo[MAX] = {0};
    int i = 0, riadok = 0, stlpec = 0, command_riadok = 0, command_riadok_do = 0, command_stlpec = 0, command_stlpec_do = 0, dlzka_tabulky = 0, pomocna_stlpec = 0, pomocna_riadok = 0, round_cislo = 0;
    int prazdny_riadok_na_konci_tabulky = 0;
    char argument_irow[MAX] = "irow";
    char argument_arow[MAX] = "arow";
    char argument_drow[MAX] = "drow";
    char argument_drows[MAX] = "drows";
    char argument_icol[MAX] = "icol";
    char argument_acol[MAX] = "acol";
    char argument_dcol[MAX] = "dcol";
    char argument_dcols[MAX] = "dcols";

    char argument_cset[MAX] = "cset";
    char argument_tolower[MAX] = "tolower";
    char argument_toupper[MAX] = "toupper";     //TODO možnože nemusím mať tieto a rovno všade psíať "nieco"
    char argument_round[MAX] = "round";
    char argument_int[MAX] = "int";
    char argument_copy[MAX] = "copy";
    char argument_swap[MAX] = "swap";
    char argument_move[MAX] = "move";
    while (1) {
        i = 0;
        while (i < argc) {
            pomocna_stlpec = 0; //todo random resetovanie dat asi skor na koniec
            if ((strcmp(argv[i], "-d")) == 0) {
                delimiter = *argv[++i];
                dlzka_tabulky = nacitaj(tabulka, &riadok, &stlpec, delimiter);
            } else if (strcmp(argv[i], argument_irow) == 0) {
                command_riadok = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0' && command_riadok > 0 &&
                    command_riadok == riadok) { // ak sa nachadzame na riadku, pred ktorý chceme dat riadok
                    pomocna_riadok++;                           // zaznamenam že som pridal riadok
                    for (int g = 0; g < stlpec - 1; g++) {
                        printf("%c", delimiter);        // vypisem na vstup prazdny riadok
                    }
                    printf("\n");                       //todo zbierat chybne hlasky pravdepodobne ?
                }
                command_riadok = 0;
            } else if (strcmp(argv[i], argument_arow) ==
                       0) {   //TODO vyriesit nacitavanie aby bolo konecne co znamena ze budem moct aplikovat totok
                prazdny_riadok_na_konci_tabulky = 1;
            } else if (strcmp(argv[i], argument_drow) == 0) {
                command_riadok = (*argv[++i] - '0');            //todo zase problem s tym ze cisla su ulozene ako char
                if (delimiter != 0 && tabulka[0] != '\0' && command_riadok > 0 &&
                    command_riadok == riadok) {  // ak sa nachadzame na riadku, ktory chcem odstranit
                    tabulka[0] = '\0';
                }
            } else if (strcmp(argv[i], argument_drows) == 0) {
                command_riadok = (*argv[++i] - '0');
                command_riadok_do = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_riadok > 0 && command_riadok <= riadok && riadok <= command_riadok_do) {
                        tabulka[0] = '\0';
                    }
                }
            } else if (strcmp(argv[i], argument_icol) == 0) {
                command_stlpec = (*argv[++i] - '0');                      //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0' && command_stlpec > 0 && command_stlpec <= stlpec) {
                    icol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                    pomocna_stlpec++;
                    dlzka_tabulky++;                                        //pridame do dlzky tabulky + 1 kvoli delimiteru a stlpcu ktory sme prave pridali
                }
            } else if (strcmp(argv[i], argument_acol) == 0) {
                if (delimiter != 0 && tabulka[0] != '\0') {
                    acol(tabulka, delimiter, dlzka_tabulky);
                    pomocna_stlpec++;
                    dlzka_tabulky++;
                }
            } else if (strcmp(argv[i], argument_dcol) == 0) {
                command_stlpec = (*argv[++i] - '0');                        //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0' && command_stlpec > 0 && command_stlpec <= stlpec) {
                        dcol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                        pomocna_stlpec--;
                        dlzka_tabulky = strlen(tabulka);                    // nova dlzka po vymazani stlpca
                }
            } else if (strcmp(argv[i], argument_dcols) == 0) {
                command_stlpec = (*argv[++i] - '0');                        //pretypovanie
                command_stlpec_do = (*argv[++i] - '0');                     //pretypovanie
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec && command_stlpec_do >= command_stlpec) {
                        pomocna_stlpec -= command_stlpec_do - command_stlpec + 1; // odcitame vymazane stlpce
                        dcols(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, dlzka_tabulky); //TODO posunul som to za if podmienku, skontrolovat ci to stale funguje
                        dlzka_tabulky = strlen(tabulka);                    // nova dlzka po vymazani stlpcov
                    }
                }
            } else if (strcmp(argv[i], argument_cset) == 0) {
                command_stlpec = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    strcpy(STR, argv[++i]);
                    cset(tabulka, &stlpec, delimiter, command_stlpec, &dlzka_tabulky, STR);
                }
                dlzka_tabulky = strlen(tabulka);                    // nova dlzka po vymeneni obsahu stlpca
                STR[0] = '\0';
            } else if (strcmp(argv[i], argument_tolower) == 0) {
                command_stlpec = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    toLower(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                }
            } else if (strcmp(argv[i], argument_toupper) == 0) {
                command_stlpec = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    toUpper(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
                }
            } else if (strcmp(argv[i], argument_round) == 0) {
                command_stlpec = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    Round(tabulka, &stlpec, delimiter, command_stlpec, &dlzka_tabulky);
                }
            } else if (strcmp(argv[i], argument_int) == 0) {
                command_stlpec = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    Int(tabulka, &stlpec, delimiter, command_stlpec, &dlzka_tabulky);
                }
                command_stlpec = 0;
            } else if (strcmp(argv[i], argument_copy) ==
                       0) {       //todo spravit iba jednu funckiu ktora skontroluje ci dalsi argument je cislo
                command_stlpec = (*argv[++i] -
                                  '0');                //todo zjednodusiť podmienky, nemusia furt byt na kazdom riadku separatne, mozem sa to spytat pre vsetko naraz
                command_stlpec_do = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec &&
                        command_stlpec_do > 0) {
                        copy(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
                    }
                }
                command_stlpec = 0;
                command_stlpec_do = 0;
            } else if (strcmp(argv[i], argument_swap) == 0) {
                command_stlpec = (*argv[++i] - '0');
                command_stlpec_do = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec &&
                        command_stlpec_do > 0) {
                        swap(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
                    }
                }
                command_stlpec = 0;
                command_stlpec_do = 0;
            } else if (strcmp(argv[i], argument_move) == 0) {
                command_stlpec = (*argv[++i] - '0');
                command_stlpec_do = (*argv[++i] - '0');
                if (delimiter != 0 && tabulka[0] != '\0') {
                    if (command_stlpec > 0 && command_stlpec <= stlpec && command_stlpec_do <= stlpec &&
                        command_stlpec_do > 0) {
                        icol(tabulka, &stlpec, delimiter, command_stlpec_do, dlzka_tabulky);
                        dlzka_tabulky++;                                                                        // Pridali sme delimiter(stlpec) - icol pred stlpec M
                        stlpec++;

//todo nieco je mega zle v csete - navrhujem zajtra preskusat funkciu samostatne, mimo move

//                        if(command_stlpec > command_riadok_do){                                                 // osetrenie pripadu kedy N > M a stlpec ktory chceme presunut sa presunul o jeden stlpec dopredu kvoli svojej kopii ktora je pred nim
                        copy(tabulka, &stlpec, delimiter, command_stlpec + 1, command_stlpec_do,
                             &dlzka_tabulky);   // skopirujeme string v stlpci N do stlpcu pred M
//                            dcol(tabulka, &stlpec, delimiter, command_stlpec+1, dlzka_tabulky);
//                        }
//                        else{
//                            copy(tabulka, &stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
//                            dcol(tabulka, &stlpec, delimiter, command_stlpec, dlzka_tabulky);
//                        }
//
//                        dlzka_tabulky--;                                                                      // Odstránili sme delimiter(stlpec) - dcol stlpec N
//                        stlpec--;
                    }
                }
                command_stlpec = 0;
                command_stlpec_do = 0;
            }
            i++;
        }
        riadok += pomocna_riadok, stlpec += pomocna_stlpec;
        pomocna_riadok = 0, pomocna_stlpec = 0;
        if (tabulka[0] !=
            '\0') {           // vypisem na vstup iba vtedy ked sa nestalo ze som upravou tabuliek nevymazal vsetko //todo napisat funkciu ktora skontroluje ci v riadku neni iba nejaky brajgel ako prazdne charaktery ako enter a medzery
            printf("%s\t\t\t\t\t\triadok: %d, stlpcov: %d dlzka_tabulky: %d\n", tabulka, riadok, stlpec, dlzka_tabulky);
        }
    }
    if (prazdny_riadok_na_konci_tabulky == 1) {
        for (int g = 0; g < stlpec - 1; g++) {
            printf("%c", delimiter);        // vypisem na vstup prazdny riadok
        }
    }
    return 0;
}

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter) {
    char c = 0;
    int pocet_znakov = 0, i = 0, pomocna_stlpec = 1;
    while ((c = getc(stdin)) != EOF) {                          // TODO fgets možno odpoved ako spravne načítať vstup
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
}

void acol(char *tabulka, char delimiter, int dlzka_tabulky) {
    tabulka[dlzka_tabulky] = delimiter;
    tabulka[dlzka_tabulky + 1] = '\0';
}

void dcol(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
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
}

void dcols(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int dlzka_tabulky) {
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
}

void cset(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky, char STR[]) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < *dlzka_tabulky) {
            if (tabulka[i] == delimiter && kontrola !=
                                           command_stlpec) {                  // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
                ++kontrola;
            }
            if (kontrola == command_stlpec) {               // ak narazime na stlpec ktory chceme menit
                if (kontrola > 1) {
                    pomocna_tabulka[j++] = delimiter;       // ak menime iny, nez prvy riadok tak potrebujeme dat na zaciatok upraveneho stlpca delimiter kvoli sposobu akym implementujem riesenie
                }
                for (int p = 0; p < strlen(STR); p++) {      // nakopirujem string do stlpca
                    pomocna_tabulka[j++] = STR[p];
                }
                ++i;                                        // skocim o jeden index dopredu aby som sa nenachdzal na delimitri
                while (tabulka[i] !=
                       delimiter) {             // v originalnej tabulke preskocim stlpec ktory som v pomocnej tabulke menil
                    if (i ==
                        *dlzka_tabulky) {                // ak sa jedna uz o posledny stlpec tak nikdy nenarazi na delimiter, co znamena ze musi zabranit nekonecnemu zacykleniu
                        break;
                    }
                    i++;
                }
                ++kontrola;                                 // kontrola nam znaci na ktorom stlpci sa nachdzame, nakolko sme teraz jeden stlpec spracovali posunieme sa o jeden dopredu
            }
            pomocna_tabulka[j] = tabulka[i];                // prekopirujeme chary ktore nijako nemenime do pomocnej tabulky
            j++;
            i++;
        }
        strcpy(tabulka,
               pomocna_tabulka);                   // prekopirujeme si zmeny do originalnej tabulky aby sa zmeny prejavili v maine v hlavnom while cykle
        *dlzka_tabulky = strlen(pomocna_tabulka);           // zmenime dlzku tabulky na novu dlzku
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void toLower(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, kontrola = 1;
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < dlzka_tabulky) {
            if (tabulka[i] ==
                delimiter) {                  // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
                ++kontrola;
            }
            if (kontrola == command_stlpec) {               // ak narazime na stlpec ktory chceme menit
                if (tabulka[i] >= 'A' && tabulka[i] <= 'Z') {
                    tabulka[i] = tabulka[i] + 32;
                }
            }
            i++;
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void toUpper(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, kontrola = 1;
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < dlzka_tabulky) {
            if (tabulka[i] ==
                delimiter) {                  // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
                ++kontrola;
            }
            if (kontrola == command_stlpec) {               // ak narazime na stlpec ktory chceme menit
                if (tabulka[i] >= 'a' && tabulka[i] <= 'z') {
                    tabulka[i] = tabulka[i] - 32;
                }
            }
            i++;
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void Round(char *tabulka, int *stlpec, char delimiter, int command_stlpec,
           int *dlzka_tabulky) {  //123.4 zaokruhli na 123 ... 123.5 zaukruhli na 124 ... -123.4 zaokruhli na -123 ... -123.5 zaokruhli na -124
    int i = 0, j = 0, kontrola = 1, pomocne_cislo = 0, necele_cislo = -1;
    char cislo[MAX] = {0}, *pointer;
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < *dlzka_tabulky) {
            if (tabulka[i] ==
                delimiter) {                          // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
                ++kontrola;
            }
            if (kontrola == command_stlpec) {                       // ak narazime na stlpec ktory chceme menit
                if (kontrola >
                    1) {                                   // chceme sa z delimitera posunut nacislo, ale iba v tom pripade ze sa jedna o iny, nez prvy riadok, v tom pripade sa uz nachadzame hned na cisle
                    ++i;
                }
                if ((tabulka[i] >= '0' && tabulka[i] <= '9') || tabulka[i] == '-') { /* skontrolujeme ci sa vobec v danom stlpci nachadza nejake cislo, ak nie cela funkcia sa preskoci
                                                                                    format typu 1458R45D mozu byt udaj ktory nechceme menit, no bohuzial zacinaju na prvom mieste cislom,
                                                                                    mat taketo udaje v stlpcoch a dat na ne prikaz round je vec ktoru budem nateraz predpokladat za nepravdepodobnu*/
                    while (tabulka[i] != delimiter) {
                        if (tabulka[i] == '.' || tabulka[i] ==
                                                 ',') {     // kedze sme dostali argument na zarovnanie cisla, hladame necele cislo(desatinnu ciarku)
                            necele_cislo = tabulka[++i] - '0';          // pretypovanie
                        }
                        if (necele_cislo == -1) {
                            cislo[j++] = tabulka[i];                    // nacitavame iba ked sme stale nezachytili necele cislo(nejake cislo za desatinnou ciarkou)
                        }
                        i++;
                        if (i ==
                            *dlzka_tabulky) {                        // osetrenie posledneho stlpca, kde while cyklus uz nikdy na ziaden delimiter nenarazi, preto treba breaknut ked sa dostane na dlzku stringu
                            break;
                        }
                    }
                    ++kontrola;

                    pomocne_cislo = strtol(cislo, &pointer, 0);
                    printf("\nnezaokruhlene cislo: %d ", pomocne_cislo);
                    if (necele_cislo >= 5 && necele_cislo <=
                                             9) {                 // robime upravu iba ked je dovod cislo zvacsovat, v opacnom pripade cislo za desatinnou ciarkou iba vynehame
                        if (pomocne_cislo >= 0) {
                            pomocne_cislo++;
                        } else {
                            pomocne_cislo--;
                        }
                    }
                    cislo[0] = '\0';
                    sprintf(cislo, "%d", pomocne_cislo);
                    printf("zaokruhlene cislo: %d - %s\n", pomocne_cislo, cislo);
                }
            }
            i++;
        }
        if (cislo[0] != '\0') {           // ak sme v danom stlpci skutocne nasli cislo
            cset(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky,
                 cislo); // pouzijeme uz existujucu funkciu na zapis upraveneho cisla do daneho stlpca
        }
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void Int(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1, necele_cislo = -1;
    char pomocna_tabulka[MAX] = {0};
    if (command_stlpec > 0 && command_stlpec <= *stlpec) {
        while (i < *dlzka_tabulky) {
            if (tabulka[i] ==
                delimiter) {                          // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
                ++kontrola;
            }
            if (kontrola == command_stlpec) {                       // ak narazime na stlpec ktory chceme menit
                if (kontrola >
                    1) {                                 // chceme sa z delimitera posunut na cislo, ale iba v tom pripade ze sa jedna o iny, nez prvy riadok, v tom pripade sa uz nachadzame hned na cisle
                    pomocna_tabulka[j++] = delimiter;
                    ++i;
                }
                while (tabulka[i] != delimiter) {
                    if (tabulka[i] == '.' || tabulka[i] ==
                                             ',') {                 // kedze sme dostali argument na zarovnanie cisla, hladame necele cislo(desatinnu ciarku)
                        necele_cislo = tabulka[++i] - '0';          // pretypovanie
                    }
                    if (necele_cislo == -1) {
                        pomocna_tabulka[j++] = tabulka[i];          // nacitavame iba ked sme stale nezachytili necele cislo(nejake cislo za desatinnou ciarkou)
                    }
                    i++;
                    if (i == *dlzka_tabulky) {                      // osetrenie posledneho stlpca
                        break;
                    }
                }
                ++kontrola;
            }
            pomocna_tabulka[j] = tabulka[i];
            j++;
            i++;
        }
        strcpy(tabulka,
               pomocna_tabulka);                   // prekopirujeme si zmeny do originalnej tabulky aby sa zmeny prejavili v maine v hlavnom while cykle
        *dlzka_tabulky = strlen(pomocna_tabulka);           // zmenime dlzku tabulky na novu dlzku
    } else {
        printf("Zle zadany command_stlpec (command_stlpec <= 0 || command_stlpec > *stlpec)\n");
    }
}

void copy(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char STR[MAX] = {0};
    while (i < *dlzka_tabulky) {
        if (tabulka[i] == delimiter && kontrola !=
                                       command_stlpec) {        // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu //todo tuto kontrolu aplikovat vsade
            ++kontrola;
            i++;                                                            // posunieme sa z delimitera na dalsi char
        }
        if (kontrola ==
            command_stlpec) {                                   // ak narazime na stlpec ktory chceme prekopirovavat
            while (tabulka[i] != delimiter && i <
                                              *dlzka_tabulky) {           // osetrenie pripadu kde kopirujeme posledny stlpec, cize narazime na \0, nie na delimiter
                STR[j++] = tabulka[i];                                      // prekopirujeme chary do pomocneho pola
                i++;
            }
//            printf("%s", STR);
            cset(tabulka, stlpec, delimiter, command_stlpec_do, dlzka_tabulky, STR);
            break;
        }
        i++;
    }
}

void swap(char *tabulka, int *stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char STR1[MAX] = {0}, STR2[MAX] = {0};
    while (i < *dlzka_tabulky) {
        if (tabulka[i] ==
            delimiter) {                                      // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            ++kontrola;
            i++;                                                            // posunieme sa z delimitera na dalsi char
        }
        if (kontrola ==
            command_stlpec) {                                   // ak narazime na stlpec ktory chceme prekopirovavat
            while (tabulka[i] != delimiter && i <
                                              *dlzka_tabulky) {           // osetrenie pripadu kde kopirujeme posledny stlpec, cize narazime na \0, nie na delimiter
                STR1[j++] = tabulka[i];                                      // prekopirujeme chary do pomocneho pola
                i++;
            }
            break;
        }
        i++;
    }
    i = 0, j = 0, kontrola = 1;
    while (i < *dlzka_tabulky) {
        if (tabulka[i] ==
            delimiter) {                                      // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            ++kontrola;
            i++;                                                            // posunieme sa z delimitera na dalsi char
        }
        if (kontrola ==
            command_stlpec_do) {                                   // ak narazime na stlpec ktory chceme prekopirovavat
            while (tabulka[i] != delimiter && i <
                                              *dlzka_tabulky) {           // osetrenie pripadu kde kopirujeme posledny stlpec, cize narazime na \0, nie na delimiter
                STR2[j++] = tabulka[i];                                      // prekopirujeme chary do pomocneho pola
                i++;
            }
            break;
        }
        i++;
    }
    cset(tabulka, stlpec, delimiter, command_stlpec_do, dlzka_tabulky, STR1);
    cset(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR2);
}
