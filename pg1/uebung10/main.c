#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LEN_NAME 100

struct Mitarbeiter {
  char nachname[LEN_NAME];
  int gehalt;
  int personalnr;
};

struct Node {
  struct Mitarbeiter data;
  struct Node *next;
};

struct Node *add_rec(struct Node *node, struct Mitarbeiter m) {
  if (node == NULL) {
    struct Node *new = malloc(sizeof(struct Node));
    new->data = m;
    return new;
  }
  node->next = add_rec(node->next, m);
  return node;
}

void add(struct Node **head, struct Mitarbeiter m) {
  *head = add_rec(*head, m);
}

void printMenu() {
  printf("Personalverwaltung - Menü:\n");
  printf("0 = Beenden\n");
  printf("1 = Alle Mitarbeiter ausgeben\n");
  printf("2 = Mitarbeiter hinzufügen\n");
  printf("3 = Mitarbeiter löschen\n");
  printf("Bitte auswählen: ");
}

void readMitarbeiter(struct Mitarbeiter *m) {
  printf("Bitte Nachnamen eingeben: ");
  getchar();
  fgets(m->nachname, LEN_NAME, stdin);
  m->nachname[strlen(m->nachname)-1] = '\0';
  printf("Bitte Gehalt eingeben: ");
  scanf("%d", &(m->gehalt));
  printf("Bitte Personalnummer eingeben: ");
  scanf("%d", &(m->personalnr));
}

int length(struct Node *node) {
  if (node == NULL) return 0;
  return length(node->next)+1;
}

void printList(struct Node *node) {
  if (node==NULL) return;
  struct Mitarbeiter m = node->data;
  printf("%s\n Gehalt: %d\n PersNr.: %d\n", m.nachname, m.gehalt, m.personalnr);
  printList(node->next);
}

struct Node *del_rec(struct Node *node, int nr) {
  if (node == NULL) return NULL;
  if (node->data.personalnr == nr) {
    struct Node *next = node->next;
    free(node);
    return next;
  }
  node->next = del_rec(node->next, nr);
  return node;
}

void del(struct Node **head, int nr) {
  *head = del_rec(*head, nr);
}

int main() {
  struct Node *head = NULL;
  while(1) {
    printMenu();
    int in; scanf("%d", &in);
    switch (in) {
      case 0:
        return 0;
      case 1:
        printf("Anzahl Mitarbeiter: %d\n", length(head));
        printList(head);
        break;
      case 2:
        struct Mitarbeiter m;
        readMitarbeiter(&m);
        add(&head, m);
        break;
      case 3:
        printf("Welche Personalnummer soll gelöscht werden? ");
        int nr; scanf("%d", &nr);
        del(&head, nr);
        break;
    }
    printf("\n");
  }
}

