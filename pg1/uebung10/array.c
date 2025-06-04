#include <stdio.h>
#include <stdlib.h>
#define LEN_NAME 100

typedef struct Mitarbeiter {
  char nachname[LEN_NAME + 1];
  int gehalt;
  int personalnr;
} Mitarbeiter;

typedef struct List {
  Mitarbeiter *elements;
  int size, cap;
} List;

List init() {
  List l = {.size = 0, .cap = 2};
  l.elements = malloc(l.cap * sizeof(Mitarbeiter));
  return l;
}

void add(List *list, Mitarbeiter elem) {
  if (list->cap == list->size) {
    list->cap *= 2;
    list->elements = realloc(list->elements, list->cap * sizeof(Mitarbeiter));
  }
  list->elements[list->size++] = elem;
}

void printMenu() {
  printf("Personalverwaltung - Menü:\n");
  printf("0 = Beenden\n");
  printf("1 = Alle Mitarbeiter ausgeben\n");
  printf("2 = Mitarbeiter hinzufügen\n");
  printf("3 = Mitarbeiter löschen\n");
  printf("Bitte auswählen: ");
}

Mitarbeiter readMitarbeiter() {
  Mitarbeiter m;
  printf("Bitte Nachnamen eingeben: Bitte Gehalt eingeben: Bitte "
         "Personalnummer eingeben: ");
  scanf("%100s %d %d", m.nachname, &(m.gehalt), &(m.personalnr));
  return m;
}

void printList(List *list) {
  printf("Anzahl Mitarbeiter: %d\n", list->size);
  for (int i = 0; i < list->size; i++) {
    const Mitarbeiter m = list->elements[i];
    printf("%s\n Gehalt: %d\n PersNr.: %d\n", m.nachname, m.gehalt,
           m.personalnr);
  }
}

void del(List *list, int nr) {
  for (int i = 0; i < list->size; i++) {
    const Mitarbeiter m = list->elements[i];
    if (m.personalnr == nr) {
      for (int j = i; j < list->size; j++)
        list->elements[j] = list->elements[j + 1];
      list->size--;
      printf("Mitarbeiter %s wurde gelöscht!\n", m.nachname);
      return;
    }
  }
}

int main() {
  List list = init();
  while (1) {
    printMenu();
    int in;
    scanf("%d", &in);

    switch (in) {
    case 0:
      return 0;
    case 1:
      printList(&list);
      break;
    case 2:
      add(&list, readMitarbeiter());
      break;
    case 3:
      printf("Welche Personalnummer soll gelöscht werden? ");
      int nr;
      scanf("%d", &nr);
      del(&list, nr);
      break;
    }
    printf("\n");
  }
}
