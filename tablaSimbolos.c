// En este fichero se define la tabla de simbolos a utilizar por el analizador lexico.

#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

//variable global que almacena la tabla de simbolos
abb tablaSimbolos;

//definicion de prototipos
void initTabla();
void destruyeTabla();
void printTabla();
void _printTabla(abb A);

void initTabla(){
    //inicializamos la tabla de simbolos
    crear(&tablaSimbolos);

    //aqui se deberian cargar todas las palabras reservadas a la tabla de simbolos
    //se debe ordenar la inserción para equilibrar el arbol binario
    /*
        CHAR
        DOUBLE
        FLOAT
        FOREACH

        IMPORT -PRIMER NODO

        INT
        RETURN
        VOID
        WHILE
    */
    tipoelem palabrasClave[] = {
        {"import", IMPORT},
        {"float", FLOAT},
        {"void", VOID},
        {"double", DOUBLE},
        {"char", CHAR},
        {"foreach", FOREACH},
        {"return", RETURN},
        {"int", INT},
        {"while", WHILE},
        
    };

    //insertamos las palabras reservadas en la tabla de simbolos
    for (int i = 0; i < (sizeof(palabrasClave) / sizeof(tipoelem)); i++) {
        insertar(&tablaSimbolos, palabrasClave[i]);
    }

}

//destruye la tabla de simbolos para liberar memoria
void destruyeTabla(){
    //se llama a la funcion destruir de la libreria abb
    destruir(&tablaSimbolos);
}


//funcion pública que permite imprimir la tabla de simbolos
void printTabla(){
    //imprimimos la tabla de simbolos
    printf("----------------------\nTabla de simbolos:\n");
    _printTabla(tablaSimbolos);
    printf("----------------------\n");
}

//funcion recursiva privada que recorre en profundidad la tabla de simbolos
void _printTabla(abb A){
    tipoelem E;
    if (!es_vacio(A)) {
        _printTabla(izq(A));
        leer(A, &E);
        printf("%-10s -> %d\n",E.identificador, E.valor);
        _printTabla(der(A));
    }
}

//funcion pública que permite buscar un elemento en la tabla de simbolos
//si el elemento esta en la tabla de simbolos, devuelve un valor, si no, se introduce
void buscaElemento(tipoelem *elemento){

    //buscamos el elemento en la tabla de simbolos
    if(es_miembro(tablaSimbolos, *elemento)){
        tipoelem find;
        buscar_nodo(tablaSimbolos, elemento->identificador, &find);
        elemento->valor = find.valor;
    //si no existe simplemente lo insertamos y establecemos como valor ID
    }else{
        elemento->valor = ID;
        insertar(&tablaSimbolos, *elemento);
    }
}