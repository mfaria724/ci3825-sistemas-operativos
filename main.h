#ifndef _main_h
#define _main_h

struct Node* newSchema(struct Node* list);

void comparisonSchema(struct Node *node, struct Node *posicion);

void insertAfterNode(struct Node *node, struct Node *position);

void insertBeforeNode(struct Node *node, struct Node *position);


int descifrar(struct Node* current);

int cifrar(struct Node* current);

void printList(struct Node* listHead);

int mostrar(struct Node* current);

int borrar(struct Node* current);

int main();
#endif