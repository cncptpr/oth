#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//v.1.0.1

//strtol ja / nein was ist die bessere praxis ?
// buffer anlegen sinnvoll ?? -> wenns besser geht wäre ein Kommentar nice :)
// malloc und realloc durchaus sinvoll -> ergänzung nach grundfunktionen


// Wenn es bessere möglichkeiten gibt etwas zu lösen gerne anmerken.
// ich bin mir hier gerade selber nicht sicher was ich noch anders machen sollte

#define MAX_PERSONAL 100 // maximum personal

struct Personal {
    char name[100];
    int gehalt;
    int personalnr;
};

struct Personal personalListe[MAX_PERSONAL];
int personalCounter = 0;

void enterGehalt(int *gehalt) {
    bool check = false;
    char gehaltBuffer[21];
    do {
        printf("Bitte Gehalt eingeben: ");
        if (fgets(gehaltBuffer, sizeof(gehaltBuffer), stdin)) {
            if (sscanf(gehaltBuffer, "%i", gehalt) != 1) {
                printf("\n Ungültiges Format neu eingeben 10.22 bsp \n");
                check = false;
            }
            else { check = true;}
        }
        else {printf("\n Fehler bitte erneut eingeben"); check = false;}

    } while (!check);
}

void enterPersonalnr(int *personalnr, bool del) {
    char personalNumberBuffer[21];
    bool check = false;
    do {
        if (del) {
            printf("Welche Personalnummer soll gelöscht werden? ");
        }
        else {
            printf("Bitte Personalnummer eingeben: \n");
        }
         // random oder auto increment would be nice
        if (fgets(personalNumberBuffer, sizeof(personalNumberBuffer), stdin)) {
            if (sscanf(personalNumberBuffer, "%i", personalnr) != 1) {
                printf("\n Ungültige personalnummer");
                check = false;
            }
            else {check = true;}
        }
        else {printf("\n Fehler bitte erneut eingeben"); check = false;}
    } while (!check);
}
void enterName(char *name) {
    char nameBuffer[100];
    bool check = false;
    do {
        printf("Bitte Nachnamen eingeben: ");
        if (fgets(nameBuffer, sizeof(nameBuffer), stdin)) {
            nameBuffer[strcspn(nameBuffer, "\n")] = 0;
            strcpy(name , nameBuffer);
            check = true;
        } else {
            printf("\n Name falsch nochmal eingeben");
            check = false;
        }
    } while (!check);
}

void addPersonal() {
    // struct "importieren"
    extern struct Personal personalListe[];
    //int importieren
    extern int personalCounter;

    // variablen zur Eintragung definieren
    char name[100];
    int gehalt = 0;
    int personalNumber = 0;

    enterName(name);
    enterGehalt(&gehalt);
    enterPersonalnr(&personalNumber, false);


    if (personalCounter < MAX_PERSONAL) {
        strcpy(personalListe[personalCounter].name, name);
        personalListe[personalCounter].gehalt = gehalt;
        personalListe[personalCounter].personalnr = personalNumber;
        personalCounter++;
    }
    else {printf("Zu viele Mitarbeiter vergrößer den Platz in der Liste.");}

}


void deletePersonal() {
    extern struct Personal personalListe[];
    extern int personalCounter;
    int personalNumber = 0;
    int found = -1;
    char name[100];
    enterPersonalnr(&personalNumber, true);

    for (int i = 0; i < personalCounter; i++) {
        if (personalListe[i].personalnr == personalNumber) {
            strcpy(name, personalListe[i].name);
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (int i = found; i < personalCounter - 1; i++) {
            personalListe[i] = personalListe[i + 1];
        }
        personalCounter--;
    }
    printf("Mitarbeiter %s wurde gelöscht.\n", name);


}
void displayPersonal() {

    extern struct Personal personalListe[];
    extern int personalCounter;


    printf("Anzahl Mitarbeiter: %d\n", personalCounter);
    if (personalCounter == 0) {
        printf("\n");
        return;
    }
    for (int i = 0; i < personalCounter; i++) {
        printf("%s\n", personalListe[i].name);
        printf(" Gehalt: %d\n", personalListe[i].gehalt);
        printf(" PersNr.: %d\n", personalListe[i].personalnr);
    }
    printf("\n");
}


int main() {

    int selector;
    char inputBuffer[4]; // 4 is enough -> 3 chars and \n maxed
    bool exit = false;

    do {
        printf("Personalverwaltung - Menü:\n");
        printf("0 = Beenden\n");
        printf("1 = Alle Mitarbeiter ausgeben\n");
        printf("2 = Mitarbeiter hinzufügen\n");
        printf("3 = Mitarbeiter löschen\n");
        printf("Bitte auswählen: ");


        if (fgets(inputBuffer, sizeof(inputBuffer), stdin)) {
            if (sscanf(inputBuffer, "%d", &selector) == 1){

                switch (selector) {
                    case 0:
                        exit = true;
                        break;
                    case 1:
                        displayPersonal();
                        break;
                    case 2:
                        addPersonal();
                        break;
                    case 3:
                        deletePersonal();
                        break;
                    default:
                        printf("Invalid Input");
                        break;
                }
            }else {
                printf("Invalid Input");
            }
        }
    } while (!exit);
    return 0;


}
