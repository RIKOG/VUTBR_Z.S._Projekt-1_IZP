/*
 * IDE CLion - Richard Gajdošík
 * Implementacia prveho projektu z predmetu IZP, zimny semester, skolsky rok 20/21
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Command list * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * irow R - vloží řádek tabulky před řádek R > 0 (insert-row).
 * arow - přidá nový řádek tabulky na konec tabulky (append-row).
 * drow R - odstraní řádek číslo R > 0 (delete-row).
 * drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
 * icol C - vloží prázdný sloupec před sloupec daný číslem C.
 * acol - přidá prázdný sloupec za poslední sloupec.
 * dcol C - odstraní sloupec číslo C.
 * dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.
 * cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.
 * tolower C - řetězec ve sloupci C bude převeden na malá písmena.
 * toupper C - řetězec ve sloupce C bude převeden na velká písmena.
 * round C - ve sloupci C zaokrouhlí číslo na celé číslo.
 * int C - odstraní desetinnou část čísla ve sloupci C.
 * copy N M - přepíše obsah buněk ve sloupci M hodnotami ze sloupce N.
 * swap N M - zamění hodnoty buněk ve sloupcích N a M.
 * move N M - přesune sloupec N před sloupec M.
 * rows N M - procesor bude zpracovávat pouze řádky N až M včetně (N <= M). N=1 znamená zpracování od prvního řádku.
                Pokud je místo čísla M zadán znak - (pomlčka), ta reprezentuje poslední řádek vstupního souboru.
                Pokud je pomlčka také místo sloupce N, myslí se tím výběr pouze posledního řádku.
                Pokud není tento příkaz zadán, uvažuje se implicitně o všech řádcích.
 * beginswith C STR - procesor bude zpracovávat pouze ty řádky, jejichž obsah buňky ve sloupci C začíná řetězcem STR.
 * contains C STR - procesor bude zpracovávat pouze ty řádky, jejichž buňky ve sloupci C obsahují řetězec STR.
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO okomentovať
// todo nacitavanie mimo delimiter
#define MAX 10241
#define dlzka_stlpca 100
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * Declaracia funkcii * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter, char delimiter_array[], int *koniec_riadku);
void icol(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);
void acol(char *tabulka, char delimiter, int *dlzka_tabulky);
void dcol(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);
void dcols(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky);
void cset(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky, char STR[]);
void toLower(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);
void toUpper(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky);
int Round(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);
int Int(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky);
void copy(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky);
void swap(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky);
int beginswith(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky, char STR[]);
int contains(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky, char STR[]);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * Hlavny program * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main(int argc, char *argv[]) {
    char delimiter = ' ', tabulka[MAX] = {0}, STR[MAX] = {0}, STR_2[MAX] = {0}, delimiter_array[MAX] = {0};
    int i = 0,
    riadok = 0, stlpec = 0, stlpec_kontrola = 0, command_riadok = 0, command_riadok_do = 0,
    command_stlpec = 0, command_stlpec_do = 0, dlzka_tabulky = 0, pomocna_stlpec = 0, pomocna_riadok = 0,
    rows_command_riadok = 0, rows_command_riadok_do = 0, prazdny_riadok_na_konci_tabulky = 0, rows = 1,
    uprava_tabulky = 0,  zpracovanie_dat = 0, selekcia_riadkov = 0, koniec_vstupu = 0;
    while (!koniec_vstupu) {                                                    // Hlavny while cyklus ktory kazdym novym cyklom nacita novy riadok, spusti cyklus na spracovanie riadku ktory prebehne vsetky argumenty
        i = 1;                                                                  // Nastavime si zaciatok iteracie(indexovanie) na jednotky, nakolko na nultom indexe sa nachadza adresa spustaneho programu
        while (i < argc) {                                                      // Dany cyklus sa vykonava dovtedy, dokym riadok neni spracovany vsetkymi zadanymi argumentami
            if ((strcmp(argv[i], "-d")) == 0 && i + 1 < argc) {                 /* If podmienka ktora sa pyta, ci sme nenarazili na znamy argument a zaroven ci sa v argv nachadza
                                                                                dostatocny pocet podporujucich argumentov, napr. po -d ako dalsie ma prist string delimiteru/ov */
                // Nakopirujeme si delimitere do char array-u
                strcpy(delimiter_array, argv[++i]);
                // Ak uzivatel specifikoval delimitre, nastavime ako hlavny delimiter znak na nultom indexe, inak defaultne delimiter je medzera
                if(delimiter_array[0] != '\0'){
                    delimiter = delimiter_array[0];
                }
                dlzka_tabulky = nacitaj(tabulka, &riadok, &stlpec, delimiter, delimiter_array, &koniec_vstupu);
                // Ak nacitavame iny, nez prvy riadok skontrolujeme, ci novy riadok zodpoveda velkosti prveho riadku
                if(riadok > 1 && stlpec_kontrola != stlpec){
                    fprintf(stderr, "%s", "Iny pocet stlpcov nez prvy riadok!\n");
                    return -1;
                } else {
                    stlpec_kontrola = stlpec;
                }
                // Ak nam nacitavacia funkcia vratila -1, znamena to ze sme presiahli pri nacitavani zadanu velkost
                if(dlzka_tabulky == -1 && koniec_vstupu == 0){
                    fprintf(stderr, "%s", "Presiahnutia limitu riadku / stlpca!\n");
                    return -1;
                }
                // Skontrolujeme ci sa pred -d nevykonal ziaden iny argument
                if(zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne poradie argumentov, alebo zle zadana hodnota!\n");
                    return -1;
                }
            }


            else if (strcmp(argv[i], "irow") == 0 && i + 1 < argc) {
                command_riadok = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument
                if(command_riadok <= 0 || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne poradie argumentov, alebo argument < 0!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sme riadok upravami nevymazali && nachadzame sa na riadku pred ktory chceme dat prazdny riadok && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && command_riadok == riadok && rows == 1) {
                    // Zaznamenam že som pridal riadok
                    pomocna_riadok++;
                    // Vypisem na vstup prazdny riadok
                    for (int g = 0; g < stlpec - 1; g++) {
                        printf("%c", delimiter);
                    }
                    printf("\n");
                }
            }


            else if (strcmp(argv[i], "arow") == 0) {
                // Zaznacime si do pomocnej premennej, ze po skonceni nacitavania je treba vypisat prazdny riadok
                prazdny_riadok_na_konci_tabulky = 1;
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument
                if(zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
            }


            else if (strcmp(argv[i], "drow") == 0 && i + 1 < argc) {
                command_riadok = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a zadane cisla su spravne N>0
                if(command_riadok <= 0 || zpracovanie_dat == 1 || selekcia_riadkov == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory chcem odstranit && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && command_riadok == riadok && rows == 1) {
                    // Vymazeme dany riadok
                    tabulka[0] = '\0';
                }
            }


            else if (strcmp(argv[i], "drows") == 0 && i + 2 < argc) {
                command_riadok = atoi(argv[++i]);
                command_riadok_do = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a zadane cisla su spravne N<=M
                if(command_riadok <= 0 || command_riadok_do <= 0 || command_riadok > command_riadok_do || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory chcem odstranit && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1 && command_riadok <= riadok && riadok <= command_riadok_do) {
                    // Vymazeme dany riadok
                    tabulka[0] = '\0';
                }
            }


            else if (strcmp(argv[i], "icol") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || dlzka_tabulky + 1 > MAX || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    icol(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky);
                    // Pridame do pomocnej premennej informaciu, ze vo finalnom pocte stlpcov bude + 1
                    pomocna_stlpec++;
                }
            }


            else if (strcmp(argv[i], "acol") == 0) {
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument
                if(dlzka_tabulky + 1 > MAX || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    acol(tabulka, delimiter, &dlzka_tabulky);
                    // Pridame do pomocnej premennej informaciu, ze vo finalnom pocte stlpcov bude + 1
                    pomocna_stlpec++;
                }
            }


            else if (strcmp(argv[i], "dcol") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    dcol(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky);
                    // Pridame do pomocnej premennej informaciu, ze vo finalnom pocte stlpcov bude - 1
                    pomocna_stlpec--;
                }
            }


            else if (strcmp(argv[i], "dcols") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                command_stlpec_do = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a zadane cisla su spravne N<=M
                if(command_stlpec <= 0 || command_stlpec_do <= 0 || command_stlpec > command_stlpec_do || zpracovanie_dat == 1 || selekcia_riadkov == 1 || uprava_tabulky == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na upravu tabulky by znamenal chybu
                uprava_tabulky = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    dcols(tabulka, stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
                    pomocna_stlpec -= command_stlpec_do - command_stlpec + 1; // odcitame vymazane stlpce
                }
            }


            else if (strcmp(argv[i], "cset") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                strcpy(STR, argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0 a neni pridanim daneho stringu presiahnuty limit stlpca/riadku
                if(command_stlpec <= 0 || dlzka_tabulky + (int)strlen(STR) > MAX || (int)strlen(STR) > dlzka_stlpca || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    cset(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky, STR);
                }
                STR[0] = '\0';
            }


            else if (strcmp(argv[i], "tolower") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    toLower(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky);
                }
            }


            else if (strcmp(argv[i], "toupper") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    toUpper(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky);
                }
            }


            else if (strcmp(argv[i], "round") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    // Ak sa v danom stlpci nenachadza cislo, funkcia vrati -1 co znaci chybu, inak funkcia na danych miestach zaokruhli cisla
                    if(Round(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky) == -1){
                        fprintf(stderr, "%s %d%s", "V danom stlpci sa nenachadza cislo! Zle data na riadku:", riadok, "%d"); // todo tento error nedava zmysel
                        return -1;
                    }
                }
            }


            else if (strcmp(argv[i], "int") == 0 && i + 1 < argc) {
                command_stlpec = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0
                if(command_stlpec <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    // Ak sa v danom stlpci nenachadza cislo, funkcia vrati -1 co znaci chybu, inak funkcia na danych miestach odstrani desatinne miesta
                    if(Int(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky) == -1){
                        fprintf(stderr, "%s %d%s", "V danom stlpci sa nenachadza cislo! Zle data na riadku:", riadok, "%d"); // todo tento error nedava zmysel
                        return -1;
                    }
                }
            }


            else if (strcmp(argv[i], "copy") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                command_stlpec_do = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0, M>0
                if(command_stlpec <= 0 || command_stlpec_do <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    copy(tabulka, stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
                }
            }


            else if (strcmp(argv[i], "swap") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                command_stlpec_do = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0, M>0
                if(command_stlpec <= 0 || command_stlpec_do <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    swap(tabulka, stlpec, delimiter, command_stlpec, command_stlpec_do, &dlzka_tabulky);
                }
            }


            else if (strcmp(argv[i], "move") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                command_stlpec_do = atoi(argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0, M>0
                if(command_stlpec <= 0 || command_stlpec_do <= 0 || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na zpracovanie dat by znamenal chybu
                zpracovanie_dat = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && jedna sa o riadok ktory chceme spracovavat v procesore
                if (tabulka[0] != '\0' && rows == 1) {
                    // Kontrola ci sa dane stlpce ktore chceme menit vobec nachadzaju v riadku, N!=M nakolko nechceme presunut stlpec pred ten isty stlpec, N!=M-1 nakolko nechceme stlpec presunut na jeho vlastnu poziciu
                    if (command_stlpec <= stlpec && command_stlpec_do <= stlpec && command_stlpec != command_stlpec_do && command_stlpec != command_stlpec_do - 1) {
                        // Pridali sme delimiter(stlpec) - icol pred stlpec M kam budeme kopirovat N
                        icol(tabulka, stlpec, delimiter, command_stlpec_do, &dlzka_tabulky);
                        // Zaznamename ze riadok ma momentalne o jeden stlpec navyse a pribudla mu dlzka o 1
                        stlpec++, dlzka_tabulky++;
                        // Osetrenie pripadu kedy N > M kedy pridanim prazdneho stlpcu(icol) sa zmeni poloha oboch stlpcov, nielen M stlpca (toto neviem bohuzial dostatocne vysvetlit)
                        if (command_stlpec < command_stlpec_do) {
                            // Kopirujeme N do miesta kde predtym bolo M
                            copy(tabulka, stlpec, delimiter, command_stlpec, command_stlpec_do,&dlzka_tabulky);
                            // Odstranime N
                            dcol(tabulka, stlpec, delimiter, command_stlpec, &dlzka_tabulky);
                        } else {
                            // Kopirujeme N do miesta kde predtym bolo M
                            copy(tabulka, stlpec, delimiter, command_stlpec + 1, command_stlpec_do, &dlzka_tabulky);
                            // Odstranime N
                            dcol(tabulka, stlpec, delimiter, command_stlpec + 1, &dlzka_tabulky);
                        }
                        // Zaznamename ze riadok ma zase spat povodny pocet stlpcov a ubudla mu dlzka o 1
                        stlpec--, dlzka_tabulky--;
                    }
                }
            }


            else if (strcmp(argv[i], "rows") == 0 && i + 2 < argc) {
                rows_command_riadok = atoi(argv[++i]);
                strcpy(STR, argv[i]);
                rows_command_riadok_do = atoi(argv[++i]);
                strcpy(STR_2, argv[i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument
                if(uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na selekciu riadkov by znamenal chybu
                selekcia_riadkov = 1;
                // Ak zistime ze chceme spracovavat iba posledny riadok, nastavujeme dve pomocne premenne na hodnoty ktore nikdy nesputia if podmienku na riadku 422 az dokym koniec_vstupu neni true (riadok 410)
                if((strcmp(STR, "-")) == 0 && (strcmp(STR_2, "-")) == 0){
                    rows_command_riadok = riadok + 1;
                    rows_command_riadok_do = riadok + 1;
                }
                // Ak zistime ze chceme spracovavat iba posledny riadok a nachadzam sa na poslednom riadku, nastavim dve pomocne premenne na taku hodnotu aby mi presla kontrola na riadku 422
                if((strcmp(STR, "-")) == 0 && (strcmp(STR_2, "-")) == 0 && koniec_vstupu == 1){
                    rows_command_riadok = 1;
                    rows_command_riadok_do = riadok;
                }
                // Ak zistim ze chcem spracovavat vsetky riadky az od nejakeho riadku, nastavujem pomocnu rows_command_riadok_do na taku hodnotu,
                // aby ked sa konecne budem nachadzat na riadku od ktoreho chcem spracovavat riadky, sa spustila kontrola na riadku 422
                if((strcmp(STR, "-")) != 0 && (strcmp(STR_2, "-")) == 0){
                    rows_command_riadok_do = riadok + rows_command_riadok;
                }
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument az na selekciu riadku a zadane cisla su spravne N>0, M>0, N<=M
                if(rows_command_riadok <= 0 || rows_command_riadok_do <= 0 || rows_command_riadok > rows_command_riadok_do) {
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Pokracujem iba ak som dany riadok nevynuloval
                if (tabulka[0] != '\0') {
                    // Ak narazime na riadky s ktorymi chceme pracovat, nic sa nemeni, rows sa stale bude rovnat 1
                    if (rows_command_riadok <= riadok && riadok <= rows_command_riadok_do) {
                        rows = 1;
                    // inak ostatne riadky maju v pomocnej premennej nastavene ze s nimi pracovat nechceme
                    } else {
                        rows = 0;
                    }
                }
                STR[0] = '\0', STR_2[0] = '\0';
            }


            else if (strcmp(argv[i], "beginswith") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                strcpy(STR, argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a kontrola ci dany argument nepresahuje dlzku stlpca, N>0
                if(command_stlpec <= 0 || (int)strlen(argv[i]) > dlzka_stlpca || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na selekciu riadkov by znamenal chybu
                selekcia_riadkov = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && v riadku sa nachadza stlpec ktory chceme skontrolovat
                if (tabulka[0] != '\0' && command_stlpec <= stlpec) {
                    // Funkcia returne -1 ak sa dany string v stlpci nezacina rovnako
                    if (!beginswith(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR)) {
                        rows = 0;
                    } else {
                        rows = 1;
                    }
                // Ak sa v danom riadku nenachadza stlpec ktory chceme skontrolovat, nastavim ze dany riadok nechceme spracovavat
                } else {
                    rows = 0;
                }
            }


            else if (strcmp(argv[i], "contains") == 0 && i + 2 < argc) {
                command_stlpec = atoi(argv[++i]);
                strcpy(STR, argv[++i]);
                // Skontrolujeme ci sa pred upravou tabulky nevykonal ziaden iny argument a kontrola ci dany argument nepresahuje dlzku stlpca, N>0
                if(command_stlpec <= 0 || (int)strlen(argv[i]) > dlzka_stlpca || uprava_tabulky == 1 || zpracovanie_dat == 1){
                    fprintf(stderr, "%s", "Nevalidne argumenty!\n");
                    return -1;
                }
                // Zaznacime si do kontrolnej premennej, ze dalsi argument na selekciu riadkov by znamenal chybu
                selekcia_riadkov = 1;
                // Ak sa nachadzame na riadku, ktory neni odstraneny predoslymi upravami && v riadku sa nachadza stlpec ktory chceme skontrolovat
                if (tabulka[0] != '\0' && command_stlpec > 0 && command_stlpec <= stlpec) {
                    // Funkcia returne -1 ak sa dany string v stlpci nenachadza
                    if (!contains(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR)) {
                        rows = 0;
                    } else {
                        rows = 1;
                    }
                // Ak sa v danom riadku nenachadza stlpec ktory chceme skontrolovat, nastavim ze dany riadok nechceme spracovavat
                } else {
                    rows = 0;
                }
            }
            // Ak sa program cez vsetky else if dostal az sem, znamena to ze sa nenachadza v argumentoch ziaden programu znamy, alebo neobsahoval vsetky nalezitosti, ako napriklad po cset neslo cislo a string
            else {
                fprintf(stderr, "%s %s%s", "Zadany prikaz nezodpovedna ziadnemu znamemu argumentu / argument je znamy, ale neobsahuje pozadovane dodatocne argumenty! Zly argument:", argv[i], "\n");
                return -1;
            }
            i++;
        }
        // Vynulovanie vsetky premennych ktore drzia kontrolu nad poctom pouzivania argumentov
        uprava_tabulky = 0,  zpracovanie_dat = 0, selekcia_riadkov = 0;
        // Ulozime si do premennych novu hodnotu riadkov(ak sme nejake pridavali) a pocet novych stlpcov riadku
        riadok += pomocna_riadok, stlpec += pomocna_stlpec;
        pomocna_riadok = 0, pomocna_stlpec = 0;
        if (tabulka[0] != '\0') {           // vypisem na vstup iba vtedy ked sa nestalo ze som upravou tabuliek nevymazal riadok
//            printf("%s\t\triadok: %d, stlpcov: %d dlzka_tabulky: %d\n", tabulka, riadok, stlpec, dlzka_tabulky);
            printf("%s\n", tabulka);
        } else if(stlpec == 0) {
            printf("\n");
        }
    }
    if (prazdny_riadok_na_konci_tabulky == 1) {
        for (int g = 0; g < stlpec - 1; g++) {
            printf("%c", delimiter);        // vypisem na vstup prazdny riadok
        }
        printf("\n");
    }
    return 0;
}

int nacitaj(char *tabulka, int *riadok, int *stlpec, char delimiter, char delimiter_array[], int *koniec_riadku) {
    char c = 0;
    int pocet_znakov = 0, i = 0, j = 0, chars_in_col = 0, pomocna_stlpec = 1, max_riadok = MAX, max_stlpec = dlzka_stlpca;
    while ((c = getc(stdin)) != EOF) {                              // while cyklus sa vykonava dokym nenarazi na koniec suboru
        if (c == '\n' && (c = getc(stdin)) != EOF) {                /* Ak narazime na riadok ktory konci na enter a dalsi znak v stdin neni \0, znamena to ze este nenacitavam posledny riadok.
                                                                    Tato podmienka tu je kvoli tomu, ze moja implementacia nacitavania nevedela rozpoznat ze sa nachadza na poslednom riadku a vzdy v bufferi ostal iba ukoncovaci znak,
                                                                    preto je dolezite skontrolovat aj nasledujuci znak po enteri*/
            tabulka[i] = '\0';
            *riadok += 1;                                           // Nacitali sme dalsi riadok, zapocitame si to do premennej
            ungetc(c, stdin);                                       // Vratime znak ktorym sme kontrolovali ci sa jedna o posledny riadok do bufferu
            return pocet_znakov;
        } else if(c == EOF) {
            tabulka[i] = '\0';
            *riadok += 1;
            *koniec_riadku = 1;
            return pocet_znakov;
        }
        tabulka[pocet_znakov] = c;
        while (j < (int)strlen(delimiter_array)) {
            if (tabulka[pocet_znakov] == delimiter_array[j]) {            // Skontrolujeme znak ktory sme prave nacitali na vyskyt v znakoch ktore uzivatel zadal ako delimitre, ak ano, nastavime dany znak na hlavny delimiter
                tabulka[pocet_znakov] = delimiter;
                pomocna_stlpec += 1;
                chars_in_col = 0;                                         // Nakolko sme narazili na delimiter(novy stlpec) vynulujeme kontrolu presiahnutie maxima znakov v stlpci
            }
            j++;
        }
        j = 0;
        pocet_znakov++, i++, chars_in_col++;
        *stlpec = pomocna_stlpec;
        if(i == max_riadok || chars_in_col == max_stlpec){          // Ak nacitavanim presiahneme limit stlpca alebo riadku, returneme -1 ako oznamenie o chybe vstupnych dat
            tabulka[0] = '\0';
            return -1;
        }
    }
    return -1;    // akekolvek neukoncenie cyklusu vo vnútri naznacuje neocakavnu chybu ktoru oznamime cez -1, napriklad ze nenarazi na ukoncovaci znak alebo znak enteru
}

void icol(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    // Ak sa dany stlpec nachadza v riadku
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < (*dlzka_tabulky) + 1) {
            // Ak sa nachadzam na stlpci kde chcem pridat stlpec
            if (kontrola == command_stlpec) {
                // Zapisem na dany stlpec dalsi delimiter
                pomocna_tabulka[j++] = delimiter;
                ++kontrola;
            }
            // Prepisem si tabulku na indexe i do pomocneho pola
            pomocna_tabulka[j++] = tabulka[i];
            // Ak narazime na delimiter, cez premennu kontrola si drzim informaciu o tom, na akom stlpci sa nachadzam
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            // iteracia
            i++;
        }
        // prekopirujem si novy riadok s novym stlpcom do tabulky
        strcpy(tabulka, pomocna_tabulka);
        // nova dlzka
        *dlzka_tabulky = strlen(tabulka);
    }
}

void acol(char *tabulka, char delimiter, int *dlzka_tabulky) {
    // Nastavim na dlzku tabulky miesto \0 delimiter
    tabulka[*dlzka_tabulky] = delimiter;
    // Nastavim na dlzku tabulky +1 \0
    tabulka[*dlzka_tabulky + 1] = '\0';
    *dlzka_tabulky = strlen(tabulka);
}

void dcol(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    // Ak sa nachadzam na danom stlpci
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < *dlzka_tabulky) {
            // Ak narazime na delimiter, cez premennu kontrola si drzim informaciu o tom, na akom stlpci sa nachadzam
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            // Ak chcem odstranit posledny stlpec
            if (kontrola == command_stlpec) { //osetrenie pripadu kedy chceme odstranit posledny stlpec
            } else {
                if (kontrola == 2 && command_stlpec == 1 &&
                    tabulka[i] == delimiter) { // specialny pripad ked chceme vymazat prvy stlpec
                } else {
                    // Prepisem si tabulku na indexe i do pomocneho pola
                    pomocna_tabulka[j++] = tabulka[i];
                }
            }
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);
        *dlzka_tabulky = strlen(pomocna_tabulka);           // zmenime dlzku tabulky na novu dlzku
    }
}

void dcols(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    // Ak sa nachadzam na danom stlpci
    if (command_stlpec <= stlpec && command_stlpec_do <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < *dlzka_tabulky) {
            // Ak narazime na delimiter, cez premennu kontrola si drzim informaciu o tom, na akom stlpci sa nachadzam
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            if (kontrola >= command_stlpec && kontrola <= command_stlpec_do) {
            } else {
                // specialny pripad ked chceme vymazat od prveho stlpca
                if (kontrola - 1 == command_stlpec_do && command_stlpec == 1 && tabulka[i] == delimiter) {
                } else {
                    pomocna_tabulka[j++] = tabulka[i];
                }
            }
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);
    }
    *dlzka_tabulky = strlen(tabulka);
}

void cset(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky, char STR[]) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    // Ak ideme menit stlpec ktory sa realne nachadza v riadku
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < (*dlzka_tabulky) + 1) {
            // ked upravujeme iny, nez posledny stlpec a ci som kontrolou stlpcov na spravnej pozicii
            if ((command_stlpec == 1 && kontrola == 1) || (command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
                // Nakolko potrebujem to, co je v danom stlpci vymazat, proste to odignorujem a nastavim si i na  dalsi stlpec v pozadi
                while (tabulka[i] != delimiter) {
                    i++;
                }
                // nakopirujem string do pomocneho pola
                for (int p = 0; p < (int)strlen(STR); p++) {
                    pomocna_tabulka[j++] = STR[p];
                }
                // kontrola ci upravujeme posledny stlpec a ci som kontrolou stlpcov na spravnej pozicii
            } else if (command_stlpec == stlpec && kontrola == stlpec) {
                // nakopirujem string do pomocneho pola
                for (int p = 0; p < (int)strlen(STR); p++) {
                    pomocna_tabulka[j++] = STR[p];
                }
                break;
            }
            if (tabulka[i] == delimiter) {
                kontrola++;
            }
            // Nakopirujem si tabulku do pomocnej premennej, kedze sme pri najdeni stlpca do ktoreho chceme kopirovat i presunuli v tabulke na dalsi stlpec,
            // a do tabulky nakopirovali novu hodnotu toho stlpca ktory sme preskocili, dane polia pokracuju v kopirovni dalsich stlpcov
            pomocna_tabulka[j] = tabulka[i];
            j++;
            i++;
        }
        strcpy(tabulka, pomocna_tabulka);                   // prekopirujeme si zmeny do originalnej tabulky aby sa zmeny prejavili v maine v hlavnom while cykle
        *dlzka_tabulky = strlen(pomocna_tabulka);           // zmenime dlzku tabulky na novu dlzku
    }
}

void toLower(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, kontrola = 1;
    // Ak sa dany stlpec nachadza v riadku
    if (command_stlpec <= stlpec) {
        while (i < dlzka_tabulky) {
            // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            // ak narazime na stlpec ktory chceme menit
            if (kontrola == command_stlpec) {
                // Ak dany znak patri do A-Z zmenime ho na lowercase
                if (tabulka[i] >= 'A' && tabulka[i] <= 'Z') {
                    tabulka[i] = tabulka[i] + 32;
                }
            }
            i++;
        }
    }
}

void toUpper(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky) {
    int i = 0, kontrola = 1;
    // Ak sa dany stlpec nachadza v riadku
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < dlzka_tabulky) {
            // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            if (tabulka[i] == delimiter) {
                ++kontrola;
            }
            // ak narazime na stlpec ktory chceme menit
            if (kontrola == command_stlpec) {
                // Ak dany znak patri do A-Z zmenime ho na lowercase
                if (tabulka[i] >= 'a' && tabulka[i] <= 'z') {
                    tabulka[i] = tabulka[i] - 32;
                }
            }
            i++;
        }
    }
}

int Round(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    float cislo_float = 0;
    char STR[MAX] = {0}, *ptr;
    // Ak ideme menit stlpec ktory sa realne nachadza v riadku
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < (*dlzka_tabulky) + 1) {
            // Ked upravujeme iny, nez posledny stlpec a nachadzame sa na spravnom stlpci
            if ((command_stlpec == 1 && kontrola == 1) || (command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != delimiter) {
                    if((tabulka[i] <= '9' && tabulka[i] >= '0') || tabulka[i] == '.' || (tabulka[i] == '-' && (tabulka[i+1] <= '9' && tabulka[i+1] >= '0'))){
                        STR[j++] = tabulka[i++];
                        // Ak sa v danom stlpci nenachadzaju spravne udaje returneme -1
                    } else {
                        return -1;
                    }
                }
                // Kontrola ci upravujeme posledny stlpec a nachadzame sa na spravnom stlpci
            } else if (command_stlpec == stlpec && kontrola == stlpec) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != '\0') {
                    if((tabulka[i] <= '9' && tabulka[i] >= '0') || tabulka[i] == '.' || (tabulka[i] == '-' && (tabulka[i+1] <= '9' && tabulka[i+1] >= '0'))){
                        STR[j++] = tabulka[i++];
                    } else {
                        // Ak sa v danom stlpci nenachadzaju spravne udaje returneme -1
                        return -1;
                    }
                }
                break;
            }
            // Ak narazime na delimiter, posunieme znacenie stlpca o jedno dopredu
            if (tabulka[i] == delimiter) {
                kontrola++;
            }
            i++;
        }
        // Prevedieme si string na float cislo
        cislo_float = strtod(STR, &ptr);
        // Zaokruhlime
        cislo_float = cislo_float < 0 ? cislo_float - 0.5 : cislo_float + 0.5;
        // Pretypujeme na int aby sme odstranili desatinnu cast
        int cislo_int = cislo_float;
        STR[0] = '\0';
        // Pretypujeme cislo spat na string
        sprintf(STR,"%d", cislo_int);
        // Cez cset prepiseme stare nezaokruhlene cislo novym
        cset(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR);
        return 0;
    }
    return 0;
}

int Int(char *tabulka, int stlpec, char delimiter, int command_stlpec, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    float cislo_float = 0;
    char STR[MAX] = {0}, *ptr;
    // Ak ideme menit stlpec ktory sa realne nachadza v riadku
    if (command_stlpec <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < (*dlzka_tabulky) + 1) {
            // Ked upravujeme iny, nez posledny stlpec a nachadzame sa na spravnom stlpci
            if ((command_stlpec == 1 && kontrola == 1) || (command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != delimiter) {
                    if((tabulka[i] <= '9' && tabulka[i] >= '0') || tabulka[i] == '.' || (tabulka[i] == '-' && (tabulka[i+1] <= '9' && tabulka[i+1] >= '0'))){
                        STR[j++] = tabulka[i++];
                    } else {
                        // Ak sa v danom stlpci nenachadzaju spravne udaje returneme -1
                        return -1;
                    }
                }
                // Kontrola ci upravujeme posledny stlpec a nachadzame sa na spravnom stlpci
            } else if (command_stlpec == stlpec && kontrola == stlpec) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != '\0') {
                    if((tabulka[i] <= '9' && tabulka[i] >= '0') || tabulka[i] == '.' || (tabulka[i] == '-' && (tabulka[i+1] <= '9' && tabulka[i+1] >= '0'))){
                        STR[j++] = tabulka[i++];
                    } else {
                        // Ak sa v danom stlpci nenachadzaju spravne udaje returneme -1
                        return -1;
                    }
                }
                break;
            }
            // Ak narazime na delimiter, posunieme znacenie stlpca o jedno dopredu
            if (tabulka[i] == delimiter) {
                kontrola++;
            }
            i++;
        }
        // Prevedieme si string na float cislo
        cislo_float = strtod(STR, &ptr);
        // Pretypujeme na int aby sme odstranili desatinnu cast
        int cislo_int = cislo_float;
        STR[0] = '\0';
        // Pretypujeme cislo spat na string
        sprintf(STR,"%d", cislo_int);
        // Cez cset prepiseme stare nezaokruhlene cislo novym
        cset(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR);
        return 0;
    }
    return 0;
}

void copy(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char STR[MAX] = {0};
    // Ak ideme menit stlpec ktory sa realne nachadza v riadku
    if (command_stlpec <= stlpec && command_stlpec_do <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < (*dlzka_tabulky) + 1) {
            // Ked upravujeme iny, nez posledny stlpec a nachadzame sa na spravnom stlpci
            if ((command_stlpec == 1 && kontrola == 1) || (command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != delimiter) {
                    STR[j++] = tabulka[i++];
                }
                // Kontrola ci upravujeme posledny stlpec a nachadzame sa na spravnom stlpci
            } else if (command_stlpec == stlpec && kontrola == stlpec) {
                // Prekopirujeme si obsah stlpca do pomocneho pola
                while (tabulka[i] != '\0') {
                    STR[j++] = tabulka[i++];
                }
                break;
            }
            // Ak narazime na delimiter, posunieme znacenie stlpca o jedno dopredu
            if (tabulka[i] == delimiter) {
                kontrola++;
            }
            i++;
        }
        // Prekopirujeme pomocne pole na poziciu urcenu uzivatelom
        cset(tabulka, stlpec, delimiter, command_stlpec_do, dlzka_tabulky, STR);
    }
}
// TODO skontrolovat swap je to take shady
void swap(char *tabulka, int stlpec, char delimiter, int command_stlpec, int command_stlpec_do, int *dlzka_tabulky) {
    int i = 0, j = 0, kontrola = 1;
    char STR1[MAX] = {0}, STR2[MAX] = {0};
    // Ak ideme menit stlpec ktory sa realne nachadza v riadku
    if (command_stlpec <= stlpec && command_stlpec_do <= stlpec) {
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < *dlzka_tabulky) {
            // Ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            if (tabulka[i] == delimiter) {
                 ++kontrola;
                // Posunieme sa z delimitera na dalsi char
                i++;
            }
            // ak narazime na stlpec ktory chceme prekopirovavat
            if (kontrola == command_stlpec) {
                // Osetrenie pripadu kde kopirujeme posledny stlpec, cize narazime na \0, nie na delimiter
                while (tabulka[i] != delimiter && i < *dlzka_tabulky) {
                    // Prekopirujeme chary do pomocneho pola
                    STR1[j++] = tabulka[i];
                    i++;
                }
                break;
            }
            i++;
        }
        i = 0, j = 0, kontrola = 1;
        // While cyklus bezi dokym neprebehne cely riadok
        while (i < *dlzka_tabulky) {
            // ak narazime na delimiter posunieme znacenie stlpcov(kontrola) o jedno dopredu
            if (tabulka[i] == delimiter) {
                ++kontrola;
                // Posunieme sa z delimitera na dalsi char
                i++;
            }
            // Ak narazime na stlpec ktory chceme prekopirovavat
            if (kontrola == command_stlpec_do) {
                // osetrenie pripadu kde kopirujeme posledny stlpec, cize narazime na \0, nie na delimiter
                while (tabulka[i] != delimiter && i < *dlzka_tabulky) {
                    // Prekopirujeme chary do pomocneho pola
                    STR2[j++] = tabulka[i];
                    i++;
                }
                break;
            }
            i++;
        }
        // Vymenime dane stlpce
        cset(tabulka, stlpec, delimiter, command_stlpec_do, dlzka_tabulky, STR1);
        cset(tabulka, stlpec, delimiter, command_stlpec, dlzka_tabulky, STR2);
    }
}

int beginswith(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky, char STR[]) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0};
    // While cyklus bezi dokym neprebehne cely riadok
    while (i < (dlzka_tabulky) + 1) {
        // Ak sa nachadzame na prvom stlpci
        if (command_stlpec == 1 && kontrola == 1) {
            // Kopirujeme dokym nenarazime na delimiter
            while (tabulka[i] != delimiter) {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            // Ak potrebujeme sa nastavit na iny, nez prvy a posledny stlpec
        } else if ((command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
            // Kopirujeme dokym nenarazime na delimiter
            while (tabulka[i] != delimiter) {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            // Ak potrebujeme posledny stlpec
        } else if (command_stlpec == stlpec && kontrola == stlpec) {
            // Kopirujeme dokym nenarazime na koniec riadku
            while (tabulka[i] != '\0') {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            break;
        }
        // Ak narazime na stlpec posunieme znacenie stlpcov o jedna
        if (tabulka[i] == delimiter) {
            kontrola++;
        }
        i++;
    }
    i = 0;
    // Po spravnom nastaveni sa stlpec, skontrolujeme ci sa dany stlpec zacina zadanym stringom od uzivatela
    while (i < (int)strlen(STR)) {
        if (STR[i] != pomocna_tabulka[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

int contains(char *tabulka, int stlpec, char delimiter, int command_stlpec, int dlzka_tabulky, char STR[]) {
    int i = 0, j = 0, kontrola = 1;
    char pomocna_tabulka[MAX] = {0}, *pointer;
    // While cyklus bezi dokym neprebehne cely riadok
    while (i < (dlzka_tabulky) + 1) {
        // Ak sa nachadzame na prvom stlpci
        if (command_stlpec == 1 && kontrola == 1) {
            // Kopirujeme dokym nenarazime na delimiter
            while (tabulka[i] != delimiter) {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            // Ak sa nachadzame na inom nez prvom alebo poslednom stlpci
        } else if ((command_stlpec > 1 && command_stlpec < stlpec && kontrola == command_stlpec)) {
            // Kopirujeme dokym nenarazime na delimiter
            while (tabulka[i] != delimiter) {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            // Ak sa nachadzam na poslednom stlpci
        } else if (command_stlpec == stlpec && kontrola == stlpec) {
            // Kopirujeme dokym nenarazime na koniec riadku
            while (tabulka[i] != '\0') {
                // Prekopirujeme chary do pomocneho pola
                pomocna_tabulka[j++] = tabulka[i++];
            }
            break;
        }
        // Ak narazim na delimiter, posunieme znacenie delimitera o jedno dopredu
        if (tabulka[i] == delimiter) {
            kontrola++;
        }
        i++;
    }
    // do argumentu sa neda dat medzera ani prazdny znak, takze ak je stlpec prazdny, nevieme v ziadnom pripade spustit kontrolu contains, cize tym padom automaticky prazdne stlpce berem tak, ze ich nechceme spracovavat
    if (j == 0) {
        return 0;
    }
    // Pointer == NULL ak sa v stlpci nevyskytuje string
    pointer = strstr(pomocna_tabulka, STR);
    // Ak zistime ze je null vratime -1
    if(pointer != NULL){
        return 1;
    }
    return 0;
}
