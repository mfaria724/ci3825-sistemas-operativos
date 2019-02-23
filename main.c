#include <stdio.h>
#include <stdlib.h>

/* Funciones del programa:
        -Registro Nuevos Mensajes: Requiere mensaje cifrado y su descifrado
        -Descifrar Mensaje: Requiere escoger cifrado, requiere INPUT mensaje
        -Cifrar Mensaje:
        -Mostrar un esquema de cifrado
        -Borrar un esquema de cifrado

        Nota: Las primeras 3 deben recibir mensaje hasta que el user ingrese un #
 */


typedef struct Nodo{
    /* Atributos - modelo de la lista a seguir http://decsai.ugr.es/~jfv/ed1/tedi/cdrom/docs/ldoble.html  */
    int fecha;     //YYYYmmdd
    char * mensaje; //https://elcodigoascii.com.ar/codigos-ascii/letra-a-minuscula-codigo-ascii-97.html
    char * cifrado;
    struct Nodo *siguiente, *anterior;
} tiponodo;

// Definir estructura tPosicion: rige la posicion de los elementos & tLista: rige la lista
typedef tiponodo *tPosicion;
typedef tiponodo *tLista;

// Manejo de Errores
static void error(char *cad)
{
   fprintf(stderr, "ERROR: %s\n", cad);
   exit(1);
}

// Init de la lista, crea una lista "l" con el tamano correspondiente a su estructura
tLista Crear(){
    tLista l;                               //inicialista la lista l
    l = (tLista)malloc(sizeof(tiponodo));   //Asigna espacio que requiere l para tiponodo
    if (l == NULL)
        error("Memoria insuficiente");
    l->siguiente = l->anterior = l;         //define la conexion circular de l
    return l;
}

// Retorna Primer elemento (usados por funcion Posicion)
tPosicion Primero (tLista l){
    return l->siguiente;
}

// Retorna Ultimo elemento (usados por funcion Posicion)
tPosicion Fin (tLista l){
   return l;
}

// Inser Un nuevo_elemento de tiponodo en una nueva posicion de la tLista l
void Insertar (int fecha, char *mensaje, char *cifrado, tPosicion p, tLista l){
    tPosicion nuevo_elemento;
    nuevo_elemento = (tPosicion)malloc(sizeof(tiponodo));
    if (nuevo_elemento == NULL)
        error("Memoria insuficiente");
    nuevo_elemento->fecha = fecha;
    nuevo_elemento->mensaje = mensaje;
    nuevo_elemento->cifrado = cifrado;
    nuevo_elemento->siguiente = p;
    nuevo_elemento->anterior = p->anterior;
    p->anterior->siguiente=nuevo_elemento;
    p->anterior = nuevo_elemento;
    printf("Contenido del elemento: fecha %d | conteido %s | cifrado %s | siguiente DESHABILITADO para estas impresiones\n", nuevo_elemento->fecha, nuevo_elemento->mensaje, nuevo_elemento->cifrado, nuevo_elemento->siguiente->fecha);
    return;
}

// Retorna la posicion en la que se encuentra un nodo (busca por fecha)
// 1) si la fecha de la primera posicion es mayor que la fecha introducida, entonces la fecha introducida sera el primer elemento/nodo.
// 2) si la fecha introducida es >= que la fecha de la posicion p y <= que la fecha de la posicion siguiente, entonces anadir en la posicion p.siguiente la nueva fecha.
tPosicion posicion (int fecha, tLista l){
   tPosicion p;
   int encontrado;
   int contador_posicion;
   p = Primero(l);
   encontrado = 0;
   printf("primera fecha del primer nodo: %d | nodo siguiente: %d (esto es de la funcion posicion)\n", p->fecha, p->siguiente->fecha); //ELIMINAR ESTO ES UNICAMENTE PARA VERIFICAR BUEN MAPEO DE LA LISTA [CORRECTO]
   if (p->fecha < fecha){                                     // *1)
   while ((p != Fin(l)) && (!encontrado))
	if (p->fecha <= fecha && p->siguiente->fecha >= fecha){   // *2)
        p = p->siguiente;
		encontrado = 1;
    }else{
		p = p->siguiente;
    }
   }
   return p;
}

int elemento (tPosicion p, tLista l){
//     if (p == l){
// 	    error("Posicion fin(l)");
//    }
   return p->fecha;
}

// Toma lo valores necesarios para anadir un nuevo_elemento a la tLista l
void registro(tLista l) {
    int fecha = 0;
    char mensaje[10];
    char cifrado[10];
    printf("\nIngrese su fecha YYYYmmdd: ");
    scanf("%d", &fecha);
    printf("Ingrese su mensaje: ");
    scanf("%s", &mensaje);
    getchar();
    printf("Ingrese cifrado: ");
    scanf("%s",&cifrado);
    Insertar(fecha, mensaje, cifrado, posicion(fecha, l), l);
    printf("\nRegistro exitoso\n");
    return;
}

int descifrar(){
    printf("\nDescifrar\n");
}

int cifrar(){
    printf("\nCifrar\n");
}

int mostrar(tLista l){          //NO ESTA IMPLEMENTANDO, UNICAMENTE PARA VERIFICAR EL BUEN MAPEO DE LA LISTA
    int elementobuscar;
    printf("\nMostrar\n");
    printf("ingrese fecha: ");     // PON CUALQUIER VALOR RANDOM
    scanf("%d", &elementobuscar);
    printf("Fecha del nodo: %d\n",elemento(posicion(elementobuscar,l),l));
}

int borrar(){
    printf("Borrar");
}

/* Main: Menu principal - Display para elegir una de las funciones del programa*/
int main(){
    tLista l = Crear();
    int opcion;
    // Mientras opcion sea <0 o >6 permanecer en el loop;
    while ( opcion < 0 || opcion > 6 ){ 
    printf("Introduzca una opcion valida: (1)registro - (2)decifrar mensaje - (3)cifrar mensajes - (4)mostrar cifrados disponibles - (5)Borrar cifrado - (0)Salir\nOpcion: ");
    scanf("%d", &opcion);
    printf("\nHas Elegido Opcion: %i\n", opcion);
    if ( opcion==1 ) {
        registro(l);
    } else if ( opcion==2 ) {
        descifrar();
    } else if ( opcion==3 ) {
        cifrar();
    } else if ( opcion==4 ) {
        mostrar(l);     // NO ESTA IMPLEMENTADO UNICAMENTE PARA TESTEAR EL BUEN MAPEO DE LA LISTA
    } else if ( opcion==5 ) {
        borrar();
    } else if ( opcion==0 ) {
        break;
      }
      opcion = 8; // colocar cualquier valor aqui > 6
    }
    return 0;
}
