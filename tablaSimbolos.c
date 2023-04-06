// En este fichero se define la tabla de simbolos a utilizar por el analizador lexico.

#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"
#include "system.h"
//#include "bison.tab.h"

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
    tipoelem inicializacion[] = {
            {CONST, "pi", .valor.var=3.14159265358979323846},
            {CONST, "e", .valor.var=2.7182818284590452354},
            {CMND0, "clear", .valor.funcptr=clear},
            {CMND0, "salir", .valor.funcptr=salir},
            {CMND0, "help", .valor.funcptr=help},
            {CMND0, "echo", .valor.funcptr=echo},
            {CMND0, "tabla", .valor.funcptr=tabla},
            {CMND0, "ws", .valor.funcptr=workSpace},
            {CMND0, "limparws", .valor.funcptr=limpiarws},
            {CMND1, "cargar", .valor.funcptr=cargar},
            {CMND1, "importar", .valor.funcptr=importar},
    };
    CompLexico palabrasClave[] = {
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
    for (int i = 0; i < (sizeof(palabrasClave) / sizeof(CompLexico)); i++) {
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
    CompLexico E;
    if (!es_vacio(A)) {
        _printTabla(izq(A));
        leer(A, &E);
        printf("%-10s -> %d\n",E.lexema, E.valorLexico);
        _printTabla(der(A));
    }
}

//funcion pública que permite buscar un elemento en la tabla de simbolos
//si el elemento esta en la tabla de simbolos, devuelve un valor, si no, se introduce
void buscaElemento(CompLexico *elemento){

    //buscamos el elemento en la tabla de simbolos
    if(es_miembro(tablaSimbolos, *elemento)){
        CompLexico find;
        buscar_nodo(tablaSimbolos, elemento->lexema, &find);
        elemento->valorLexico = find.valorLexico;
    //si no existe simplemente lo insertamos y establecemos como valor ID
    }else{
        elemento->valorLexico = ID;
        insertar(&tablaSimbolos, *elemento);
    }
}