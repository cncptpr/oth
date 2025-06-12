#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_NAME 100

typedef struct Mitarbeiter {
  char nachname[LEN_NAME + 1];
  int gehalt;
  int personalnr;
  struct Mitarbeiter *next;
  struct Mitarbeiter *prev;
} Mitarbeiter;

void printMenu() {
  printf("Personalverwaltung - Menü:\n");
  printf("0 = Beenden\n");
  printf("1 = Alle Mitarbeiter ausgeben\n");
  printf("2 = Mitarbeiter hinzufügen\n");
  printf("3 = Mitarbeiter löschen\n");
  printf("Bitte auswählen: ");
}

void readMitarbeiter(Mitarbeiter *m) {
  printf("Bitte Nachnamen eingeben: Bitte Gehalt eingeben: Bitte "
         "Personalnummer eingeben: ");
  scanf("%100s %d %d", m->nachname, &(m->gehalt), &(m->personalnr));
}

Mitarbeiter *add(Mitarbeiter *tail) {
  Mitarbeiter *m = malloc(sizeof(Mitarbeiter));
  m->next = tail;
  m->prev = tail->prev;
  tail->prev = tail->prev->next = m;
  return m;
}

int length(Mitarbeiter *node) {
  if (node->next == NULL)
    return 0;
  return length(node->next) + (node->prev != NULL);
}

void printList(Mitarbeiter *node) {
  if (node->next == NULL)
    return;
  if (node->prev != NULL)
    printf("%s\n Gehalt: %d\n PersNr.: %d\n", node->nachname, node->gehalt,
           node->personalnr);
  printList(node->next);
}

void del(Mitarbeiter *node, int nr) {
  // Tail reached
  if (node->next == NULL)
    return;

  // Not node to del or head
  if (node->personalnr != nr || node->prev == NULL)
    return del(node->next, nr);

  node->prev->next = node->next;
  node->next->prev = node->prev;
  printf("Mitarbeiter %s wurde gelöscht!\n", node->nachname);
  free(node);
}

int main() {
  // Keine echten Mitarbeiter, macht recursion nur einfacher.
  Mitarbeiter head, tail;
  head.next = &tail;
  tail.prev = &head;
  tail.next = head.prev = NULL;
  while (1) {
    printMenu();
    int in;
    scanf("%d", &in);
    switch (in) {
    case 0:
      return 0;
    case 1:
      printf("Anzahl Mitarbeiter: %d\n", length(&head));
      printList(&head);
      break;
    case 2:
      readMitarbeiter(add(&tail));
      break;
    case 3:
      printf("Welche Personalnummer soll gelöscht werden? ");
      int nr;
      scanf("%d", &nr);
      del(&head, nr);
      break;
    }
    printf("\n");
  }
}
