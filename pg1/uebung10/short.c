#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_NAME 100

typedef struct Mitarbeiter {
  char nachname[LEN_NAME + 1];
  int gehalt;
  int personalnr;
} Mitarbeiter;

int main() {
  int size = 0, cap = 2;
  struct Mitarbeiter *elems = malloc(cap * sizeof(Mitarbeiter));
  while (1) {
    printf("Personalverwaltung - Menü:\n0 = Beenden\n1 = Alle Mitarbeiter "
           "ausgeben\n2 = Mitarbeiter hinzufügen\n3 = Mitarbeiter "
           "löschen\nBitte auswählen: ");
    int in;
    scanf("%d", &in);
    switch (in) {
    case 0:
      return 0;
    case 1:
      printf("Anzahl Mitarbeiter: %d\n", size);
      for (int i = 0; i < size; i++) {
        printf("%s\n Gehalt: %d\n PersNr.: %d\n", elems[i].nachname,
               elems[i].gehalt, elems[i].personalnr);
      }
      break;
    case 2:
      printf("Bitte Nachnamen eingeben: Bitte Gehalt eingeben: Bitte "
             "Personalnummer eingeben: ");
      scanf("%s\n%d\n%d", elems[size].nachname, &(elems[size].gehalt),
            &(elems[size].personalnr));
      if (cap == ++size) {
        Mitarbeiter *new = malloc((cap *= 2) * sizeof(Mitarbeiter));
        memcpy(new, elems, size * sizeof(Mitarbeiter));
        free(elems);
        elems = new;
      }
      break;
    case 3:
      printf("Welche Personalnummer soll gelöscht werden? ");
      int nr;
      scanf("%d", &nr);
      for (int i = 0; i < size; i++) {
        if (elems[i].personalnr == nr) {
          for (int j = i; j < size - 1; j++)
            elems[j] = elems[j + 1];
          size--;
        }
        printf("Mitarbeiter %s wurde gelöscht!\n", elems[i].nachname);
      }
      break;
    }
    printf("\n");
  }
}
