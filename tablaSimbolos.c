// En este fichero se define la tabla de simbolos a utilizar por el analizador lexico.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "abb.h"
#include "interpreteMat.h"
#include "definiciones.h"
#include "system.h"
#include "bison.tab.h"
#include "tablaSimbolos.h"

//variable global que almacena la tabla de simbolos
abb tSimbolos;

int num_variables = 0;

void initTabla(){
    //inicializamos la tabla de simbolos
    crear(&tSimbolos);
    tipoelem inicializacion[] = {
            {"pi", CONS, .valor.var=3.1415926535897932},
            {"e", CONS, .valor.var=2.718281828459045},
            {"clear", CMND0, .valor.funcptr=clear},
            {"salir",CMND0, .valor.funcptr=salir},
            {"help", CMND0, .valor.funcptr=help},
            {"echo", CMND0, .valor.funcptr=echo},
            {"tabla", CMND0, .valor.funcptr=tabla},
            {"ws", CMND0, .valor.funcptr=workSpace},
            {"eliminarWs", CMND0, .valor.funcptr=eliminarWs},
            {"loadFichero", CMND1, .valor.funcptr=cargar},
            //cargamos las funciones matematicas
            {"sin", CMND2, .valor.funcptr=sin},
            {"cos", CMND2, .valor.funcptr=cos},
            {"tan", CMND2, .valor.funcptr=tan},
            {"log", CMND2, .valor.funcptr=log10},
            {"ln", CMND2, .valor.funcptr=log},
            {"exp", CMND2, .valor.funcptr=exp}
    };

    //insertamos las palabras reservadas en la tabla de simbolos
    for (int i = 0; i < (sizeof(inicializacion) / sizeof(tipoelem)); i++) {
        insertar(&tSimbolos, inicializacion[i]);
    }

}

//destruye la tabla de simbolos para liberar memoria
void destruyeTabla(){
    //se llama a la funcion destruir de la libreria abb
    destruir(&tSimbolos);
}

double ejecutaFuncionMatematica(char *operacion, char *expresion){
    tipoelem elemento;

    elemento = buscarLexema(operacion);

    return elemento.valor.funcptr(expresion);
    
}


//funcion recursiva privada que recorre en profundidad la tabla de simbolos
void _printTabla(abb A){
    tipoelem E;
    if (!es_vacio(A)) {
        _printTabla(izq(A));
        leer(A, &E);
        switch (E.valorLexico)
        {
        case VAR:
            printf("    %-6s\t\t    %-6s\t\t%-6lf\n", "Variable", E.lexema, E.valor.var);
            break;
        case CONS:
            printf("    %-6s\t\t    %-6s\t\t%-6lf\n", "Constante", E.lexema, E.valor.var);
            break;
        case FUNC:
            printf("    %-6s\t\t    %-6s\t\t%-6s\n", "Función", E.lexema, "NULL");
            break;
        
        default:
            printf("    %-6s\t\t    %-6s\t\t%-6s\n", "Comando", E.lexema, "NULL");
            break;
        }
        
        _printTabla(der(A));
    }
}

void _printWS(abb A){
    tipoelem E;
    if (!es_vacio(A)) {
        _printWS(izq(A));
        leer(A, &E);
        if(E.valorLexico == VAR){
            printf("    %-6s\t\t    %-6lf\n", E.lexema, E.valor.var);
        }
        _printWS(der(A));
    }
}

void _eliminaVarRecursiva(abb A, int *stop){
    tipoelem E;
    if(!es_vacio(A) && !*stop){
        //buscamos la rama izq
        _eliminaVarRecursiva(izq(A), stop);
        leer(A, &E);
        //si se encuentra una variable se elimina, si ya ha sido encontrada y se encuentra otra, la flag stop evita que se eliminen variables de mas cada vez que se llama a esta función
        if(E.valorLexico == VAR && !*stop){
            suprimir(&A, E);
            *stop = 1;
        }
        if(!*stop){
            //si no se ha encontrado seguimos buscando por la derecha
            _eliminaVarRecursiva(der(A), stop);
        }
    }
}

void _eliminaVar(){
    int stop = 0;
    _eliminaVarRecursiva(tSimbolos, &stop);
}

// Función que busca un lexema concreto.
//  Si el lexema está en la tabka, devuelve su componente léxico.
//  Si oçel lexema no está en la tabla, devuelve NULL.
CompLexico buscarLexema(char *lexema) {
    tipoelem comp_busqueda = {NULL, 0 };
    buscar_nodo(tSimbolos, lexema, &comp_busqueda);
    return comp_busqueda;
}

// Función que inserta un componente léxico en la tabla de símbolos
void insertarComponente(CompLexico comp) {
    insertar(&tSimbolos, comp);
    if (comp.valorLexico == VAR) {
        num_variables++;
    }
}

// Función que modifica el valor de variable en un componente léxico en la tabla de símbolosd
void modificarValorVariable(char *lexema, double valor) {
    tipoelem comp_busqueda = {NULL, 0 };

    // Busca en la tabla un lexema concreto devolviendolo
    buscar_nodo(tSimbolos, lexema, &comp_busqueda);
    if (comp_busqueda.lexema != NULL) { // Se está en la tabla, se modifica
        modificarNodo(&tSimbolos, lexema, valor);
    }
}

//funcion pública que permite buscar un elemento en la tabla de simbolos
//si el elemento esta en la tabla de simbolos, devuelve un valor, si no, se introduce
void buscaElemento(CompLexico *elemento){

    //buscamos el elemento en la tabla de simbolos
    if(es_miembro(tSimbolos, *elemento)){
        tipoelem find;
        buscar_nodo(tSimbolos, elemento->lexema, &find);
        elemento->valorLexico = find.valorLexico;
    //si no existe simplemente lo insertamos y establecemos como valor ID
    }else{
        elemento->valorLexico = ID;
        insertar(&tSimbolos, *elemento);
    }
}

//funcion pública que permite imprimir la tabla de simbolos
void printTabla(){
    //imprimimos la tabla de simbolos
    printf("---------------------------------------------------------\n"
           "\t\t    Tabla de simbolos:\n"
           "---------------------------------------------------------\n"
           "    %-6s\t\t     %-6s\t\t%-6s\n"
           "---------------------------------------------------------\n", "Tipo", "Lexema", "Valor");
    _printTabla(tSimbolos);
    printf("---------------------------------------------------------\n");
}

//funcion pública que permite imprimir la tabla de simbolos
void printWorkSpace(){
    //imprimimos la tabla de simbolos
    printf("------------------------------------------------\n"
           "\t     WORKSPACE:\n"
           "------------------------------------------------\n"
           "    %-6s\t\t%-6s\n"
           "------------------------------------------------\n", "Lexema", "Valor");
    _printWS(tSimbolos);
    printf("------------------------------------------------\n");
}

void eliminarWorkSpace(){
    for(int i=0; i < num_variables; i++){
        _eliminaVar();
    }
    num_variables = 0;
}

