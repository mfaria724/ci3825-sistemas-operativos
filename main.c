#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/* Jesus Kauze 12-10273
   Manuel Faria 15-10463
   Juan Oropeza 15-11041

   Funciones del programa:
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


void comparisonSchema(struct Node *node, struct Node *posicion){
    int samescheme = 0;
    int yet = 1;
    int len_prev, len_current, len_next;
    int lower, higher;
    int have_next = 0;

    len_current = strlen(node->encryption);
    len_prev = strlen(node->prev->encryption);

    if ( node->next != NULL ){
        have_next = 1;
        len_next = strlen(node->next->encryption);
    }
    
    if ( len_current >= len_prev ){
        int higher = len_current;
        int lower = len_prev;
        for (int i = 0; i < lower; i++ ){
            
            samescheme = 0;
            
            for (int j = 0; j < higher; j++){
                if ( node->encryption[j] == node->prev->encryption[i] && node->letters[j] == node->prev->letters[i] ){
                    samescheme = 1;
                    break;
                }
            }

            if ( samescheme == 0 ){
                break;
            }
        }
    } else { 
        int higher = len_prev;
        int lower = len_current;
        for (int i = 0; i < lower; i++ ){

            samescheme = 0;
            
            for (int j = 0; j < higher; j++){
                if ( node->encryption[i] == node->prev->encryption[j] && node->letters[i] == node->prev->letters[j] ){
                    samescheme = 1;
                    break;
                } 
            }

            if ( samescheme == 0 ){
                break;
            }
        }
    }

    if (samescheme){
        int option = 0;
        while ( 1 ) {
            printf("\nTienes esquemas de cifrado iguales con la fecha <%i> previa: \n(1) Unir cifrados \n(2) Crear nuevo \nSelecciona una opcion: ", node->prev->date);
            scanf("%d", &option);
            if (option == 1 || option == 2){
                break;
            }
        }
        if ( option == 1 ) {
            if (len_current > len_prev){
                int counter = len_prev;
                for(int i = 0; i < len_current; i++){
                    for(int j = 0; j < len_prev; j++){
                        if (node->encryption[i] == node->prev->encryption[j]){
                            j = len_prev;
                        } else {
                            if ( j == len_prev - 1){
                                node->prev->encryption[counter]=node->encryption[i];
                                node->prev->letters[counter]=node->letters[i];
                                counter++;
                            }
                        }
                    }
                }
            node->prev->next=node->next;
            } else {
                int counter = len_current;
                for(int i = 0; i < len_prev; i++){
                    for(int j = 0; j < len_current; j++){
                        if (node->encryption[j] == node->prev->encryption[i]){
                            j = len_current;
                        } else {
                            if ( j == len_current - 1){
                                node->encryption[counter]=node->prev->encryption[i];
                                node->letters[counter]=node->prev->letters[i];
                                counter++;
                            }
                        }
                    }
                }
                node->date = node->prev->date;
                if (node->prev->prev != NULL) {
                    node->prev = node->prev->prev;
                } else {
                    node->prev = posicion;
                }
            }
            yet = 0; //to make only one UNION of dates.
        } else { // option == 2
            yet = 0;
        }
    }

    if ( len_current >= len_next && have_next ){
        int higher = len_current;
        int lower = len_next;
        for (int i = 0; i < lower; i++ ){

            samescheme = 0;
            
            for (int j = 0; j < higher; j++){
                if ( node->encryption[j] == node->next->encryption[i] && node->letters[j] == node->next->letters[i] ){
                    samescheme = 1;
                    break;
                } 
            }

            if ( samescheme == 0 ){
                break;
            }
        }
    } 
    else if ( len_current < len_next && have_next ){
        int higher = len_next;
        int lower = len_current;
        for (int i = 0; i < lower; i++ ){

            samescheme = 0;
            
            for (int j = 0; j < higher; j++){
                if ( node->encryption[i] == node->next->encryption[j] && node->letters[i] == node->next->letters[j] ){
                    samescheme = 1;
                } 
            }

            if ( samescheme == 0 ){
                break;
            }
        }
    }

    if (samescheme && yet){
        int option = 0;
        while ( 1 ) {
            printf("\nTienes esquemas de cifrado iguales con la siguiente fecha <%i> elige: \n(1) Unir cifrados \n(2) Crear nuevo\n Selecciona una opcion: ", node->next->date);
            scanf("%d", &option);
            if (option == 1 || option == 2){
                break;
            }
        }
        if ( option == 1 ) {
            if (len_current < len_next){
                int counter = len_current;
                for(int i = 0; i < len_next; i++){
                    // printf("-|[%i]:%c|-", i,node->next->encryption[i]);
                    for(int j = 0; j < len_current; j++){
                        if (node->next->encryption[i] == node->encryption[j]){
                            j = len_current;
                        } else {
                            if ( j == len_current - 1){
                                node->encryption[counter]=node->encryption[i];
                                node->letters[counter]=node->letters[i];
                                counter++;
                            }
                        }
                    }
                }
            
            if (node->next->next != NULL){
                node->next=node->next->next;
            } else {
                node->next=NULL;
            }

            } else {
                int counter = len_next;
                for(int i = 0; i < len_current; i++){
                    for(int j = 0; j < len_next; j++){
                        if (node->encryption[i] == node->next->encryption[j]){
                            j = len_next;
                        } else {
                            if ( j == len_next - 1){
                                node->next->encryption[counter]=node->encryption[i];
                                node->next->letters[counter]=node->letters[i];
                                counter++;
                            }
                        }
                    }
                }
                if (node->prev != NULL) {
                    node->next->prev = node->prev;
                } else {
                    node->next->prev = posicion;
                }
            }
        }
    }
    return;
}

// Inserts a new node into the list
void insertAfterNode(struct Node *node, struct Node *position){

    node->next = position->next;
    position->next = node;
    
    if(node->next != NULL){
        node->next->prev = node;
    }

    node->prev = position; 

    comparisonSchema(node,position);
    return;
}

void insertBeforeNode(struct Node *node, struct Node *position){
    node->prev = position->prev;
    position->prev = node;

    if (node->prev != NULL){
        node->prev->next = node;
    }

    node->next = position;

    comparisonSchema(node, position);
    return;
}

struct Node* newSchema(struct Node* list){

    // Pide datos al usuario
    int date = 0;
    char *message = (char*)malloc(sizeof(char)*100);
    char *encryption = (char*)malloc(sizeof(char)*100);

    printf("Ingrese la fecha (YYYYMMDD): ");
    scanf("%i", &date);

    fflush(stdin);
    printf("Ingrese el mensaje sin decifrar: ");
    fgets(message, 2, stdin);
    fgets(message, 100, stdin);
    strtok(message, "\n");

    printf("Ingrese el mensaje cifrado: ");
    fgets(encryption, 100, stdin);
    strtok(encryption, "\n");

    
    // Inicializa nuevo nodo
    struct Node* newNode; 

    if(list->date == 0){
        newNode = list;
    }else {
        newNode = malloc(sizeof(struct Node));
    }

    newNode->date = date;


    int len = strlen(message);

    for(int x = 0; x < len; x++){
        for(int y = 0; y < 67; y++){
            if(message[x] == newNode->letters[y]){
                y = 67;
            }else if(newNode->letters[y] == '\0'){
                newNode->letters[y] = message[x];
                newNode->encryption[y] = encryption[x];
                y = 67;
            }
        }
    }

    for(int x = 0; x < 5; x++){
    }
    
    if(newNode->date != list->date){
        struct Node* current = malloc(sizeof(struct Node));
        current = list;

        while(current->next != NULL && current->date < newNode->date){
            current = current->next;
        }

        if(current->prev != NULL){
            current = current->prev;
        }
        
        insertAfterNode(newNode, current);
    }

    printf("\nSe ha registrado el esquema correctamente\n");
    return list;
}


int descifrar(struct Node* current){
    char message[67];
    int date;


    printf("\nIngrese la fecha (YYYYMMDD): ");
    scanf("%d", &date);
    printf("\nIngrese mensaje cifrado: ");
    scanf("%s", message);
    int len = strlen(message);


    if (date < current->date) {
        printf("\nNo existe ningun esquema anterior al mensaje\n");
        return 0;
    }
    

    while(current->next != NULL && date >= current->next->date){
        current = current->next;
    }

    int lenSchema = strlen(current->encryption);

    int cambio;
    for(int i = 0; i < len; i++)
    {
        cambio = 0;
        for(int j = 0; j < lenSchema; j++)
        {
            if (message[i] == current->encryption[j]) {
                message[i] = current->letters[j];
                cambio = 1;
            }
        }
        if (!cambio) {
            message[i]= '#';
        }
    }
    printf("\n%s\n", message);
}

int cifrar(struct Node* current){
    char message[67];
    int date;


    printf("\nIngrese la fecha (YYYYMMDD) \n");
    scanf("%d", &date);
    printf("\nIngrese mensaje a cifrar:\n");
    scanf("%s", message);
    int len = strlen(message);


    if (date < current->date) {
        printf("\nNo existe ningun esquema anterior al mensaje\n");
        return 0;
    }

    while(current->next != NULL && date >= current->next->date){
        current = current->next;
    }

    int lenSchema = strlen(current->encryption);

    int cambio;
    for(int i = 0; i < len; i++)
    {
        cambio = 0;
        for(int j = 0; j < lenSchema; j++)
        {
            if (message[i] == current->letters[j]) {
                message[i] = current->encryption[j];
                cambio = 1;
            }
        }
        if (!cambio) {
            message[i]= '#';
        }
    }
    printf("\n%s\n", message);
}

void printList(struct Node* listHead){

    int counter = 0;

    while(listHead != NULL){
        printf("\n##### NODO #%i #####\n", counter);
        printf("DATE: %i - PREV %p - NEXT: %p\n", listHead->date, listHead->prev, listHead->next);
        printf("LETTERS: \n");
        int len = strlen(listHead->letters);
        for(int x = 0; x < len; x++){
            printf("LETTERS[%i]: %c\n", x, listHead->letters[x]);
            printf("ENCRYPTION[%i]: %c\n", x, listHead->encryption[x]);
        }
        listHead = listHead->next;
        counter++;
    }
}

int mostrar(struct Node* current){          //NO ESTA IMPLEMENTANDO, UNICAMENTE PARA VERIFICAR EL BUEN MAPEO DE LA LISTA
    int date;
    printf("\nIngrese fecha: ");     // PON CUALQUIER VALOR RANDOM
    scanf("%d", &date);

    while(current->next != NULL && date >= current->next->date){
        current = current->next;
    }

    if(date == current->date){
        printf("\nFecha: %i\nCifrado: %s\nDescifrado: %s\n\n", current->date, current->encryption, current->letters);
    } else {
        printf("No existe ningun esquema con la fecha ingresada");
    }
}

int borrar(struct Node* current){
    int date;
    printf("\nIngrese fecha: ");     // PON CUALQUIER VALOR RANDOM
    scanf("%d", &date);

    while(current->next != NULL && date >= current->next->date){
        current = current->next;
    }

    if(date == current->date && current->next == NULL && current->prev == NULL){
        free(current);
        printf("Esquema eliminado");
    } else if(date == current->date && current->next == NULL){
        current->prev->next = NULL;
        free(current);
        printf("Esquema eliminado");
    } else if(date == current->date && current->prev == NULL){
        current->next->prev = NULL;
        free(current);
        printf("Esquema eliminado");
    } else if(date == current->date){
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        printf("Esquema eliminado");
    } else {
        printf("\nNo existe ningun esquema con la fecha ingresada\n");
    }
}

/* Main: Menu principal - Display para elegir una de las funciones del programa*/
int main(){

    int opcion;
    struct Node *listHead = malloc(sizeof(struct Node));

    // Mientras opcion sea <0 o >6 permanecer en el loop;
    while (1){ 
        printf("Introduzca una opcion valida: \n(1) Registro \n(2) Decifrar Mensaje \n(3) Cifrar Mensajes \n(4) Mostrar Cifrado\n(5) Borrar Cifrado \n(0) Salir\nOpcion: ");
        scanf("%d", &opcion);
        printf("\nHas Elegido Opcion: %i\n", opcion);
        if ( opcion==1 ) {
            listHead = newSchema(listHead);

        } else if ( opcion==2 ) {
            descifrar(listHead);
        } else if ( opcion==3 ) {
            cifrar(listHead);
        } else if ( opcion==6 ){
            printList(listHead);
        } else if ( opcion==4 ) {
            mostrar(listHead);
        } else if ( opcion==5 ) {
            borrar(listHead);
        } else if ( opcion==0 ) {
            break;
        }
        opcion = 8; // colocar cualquier valor aqui > 6
    }
    return 0;
}
