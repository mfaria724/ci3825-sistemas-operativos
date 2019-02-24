#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funciones del programa:
        -Registro Nuevos Mensajes: Requiere mensaje cifrado y su descifrado
        -Descifrar Mensaje: Requiere escoger cifrado, requiere INPUT mensaje y fecha
        -Cifrar Mensaje: require INPUT mensaje
        -Mostrar un esquema de cifrado
        -Borrar un esquema de cifrado

        Nota: Las primeras 3 deben recibir mensaje hasta que el user ingrese un #
 */

struct Node{
    /* Atributtes */
    int date;               //yyyymmdd
    char letters[67];
    char encryption[67];
    struct Node* next;  
    struct Node* prev;
};

// Error handling
static void error(char *cad)
{
   fprintf(stderr, "ERROR: %s\n", cad);
   exit(1);
}

// Initialize list with a single node
struct Node *createList(){
    struct Node *l = malloc(sizeof(struct Node));          //Asigna espacio que requiere l para tiponodo
    if (l == NULL){
        error("Memoria insuficiente");
        exit(1);
    }
    l->next = l->prev = NULL;         
    return l;
}

struct Node* newSchema(struct Node* list){

    int *date = malloc(sizeof(int));
    char *message = (char*)malloc(sizeof(char)*100);
    char *encryption = (char*)malloc(sizeof(char)*100);

    printf("Ingrese la fecha (YYYYMMDD): ");
    scanf("%i", &date);
    printf("Ingrese el mensaje sin decifrar: ");
    scanf("%s", message);
    printf("Ingrese el mensaje cifrado: ");
    scanf("%s", encryption);

    printf("DATE: %i\nMESSAGE: %s\nENCRYPTION: %s\n", date, message, encryption);
    
    struct Node* newNode; 

    if(list->date == 0){
        newNode = list;
    }else {
        newNode = malloc(sizeof(struct Node));
    }

    newNode->date = date;
    

    printf("DATE: %i\n", newNode->date);

    int len = strlen(message);
    printf("MESSAGE LENGTH: %i\n", len);

    for(int x = 0; x < len; x += 1){
        printf("MESSAGE[%i]: %c\n", x, message[x]);
    }
    return list;
}

// Inserts a new node into the list
void insertAfterNode(struct Node *node, struct Node *position){
    node->next = position->next;
    position->next = node;
    node->prev = position; 
    return;
}

int descifrar(){
    printf("\nDescifrar\n");
}

int cifrar(){
    printf("\nCifrar\n");
}

// int mostrar(tLista l){          //NO ESTA IMPLEMENTANDO, UNICAMENTE PARA VERIFICAR EL BUEN MAPEO DE LA LISTA
//     int elementobuscar;
//     printf("\nMostrar\n");
//     printf("ingrese fecha: ");     // PON CUALQUIER VALOR RANDOM
//     scanf("%d", &elementobuscar);
//     printf("Fecha del nodo: %d\n",elemento(posicion(elementobuscar,l),l));
// }

int borrar(){
    printf("Borrar");
}

/* Main: Menu principal - Display para elegir una de las funciones del programa*/
int main(){

    int opcion;
    struct Node *listHead = malloc(sizeof(struct Node));

    // Mientras opcion sea <0 o >6 permanecer en el loop;
    while (1){ 
        printf("Introduzca una opcion valida: \n(1) Registro \n(2) Decifrar Mensaje \n(3) Cifrar Mensajes \n(4) Mostrar Cifrados Disponibles \n(5) Borrar Cifrado \n(0) Salir\nOpcion: ");
        scanf("%d", &opcion);
        printf("\nHas Elegido Opcion: %i\n", opcion);
        if ( opcion==1 ) {
            listHead = newSchema(listHead);
        // } else if ( opcion==2 ) {
        //     descifrar();
        // } else if ( opcion==3 ) {
        //     cifrar();
        // } else if ( opcion==4 ) {
        //     mostrar(l);     // NO ESTA IMPLEMENTADO UNICAMENTE PARA TESTEAR EL BUEN MAPEO DE LA LISTA
        // } else if ( opcion==5 ) {
        //     borrar();
        } else if ( opcion==0 ) {
            break;
        }
        opcion = 8; // colocar cualquier valor aqui > 6
    }
    return 0;
}
