#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "system.h"
#include "interpreteMat.h"
#include "lex.yy.h"
#include "bison.tab.h"
#include "tablaSimbolos.h"

int V_Echo = 0;

double clear(){
    system("clear");
    return 0;
}

double salir(){
    printf(AMARILLO"Finalizando el programa..."RESET"\n\n");
    //liberamos la memoria de la tabla de simbolos y cerramos el sistema de entrada
    destruyeTabla();
    yylex_destroy();
    exit(EXIT_SUCCESS);
}

double help(){
    printf("Bienvenido al interprete matematico perra.\n");
    return 0;
}

double echo(){
    if(V_Echo == 1){
        V_Echo = 0;
    }else{
        V_Echo = 1;
    }
    cambiarEcho(V_Echo);
    return 0;
}

double tabla(){
    printTabla();
    return 0;
}

double workSpace(){
    printWorkSpace();
    return 0;
}

double limpiarws(){
    eliminarWorkSpace();
    printf(AMARILLO"Espacio de trabajo limpiado correctamente.\n\n"RESET);
    return 0;
}

double cargar(char *fichero){
    yyin = fopen(fichero, "r");

    if(yyin == NULL){
        printf(ROJO"FICHERO NO ENCONTRADO."RESET"\n\n");
    }else{
        ejecutandoScript(1);
    }

    return 0;

}