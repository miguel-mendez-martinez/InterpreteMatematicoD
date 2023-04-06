#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "system.h"
#include "lex.yy.h"

double clear(){
    system("clear");
    return 0;
}

double salir(){
    printf("Finalizando el programa...\n\n");
    //liberamos la memoria de la tabla de simbolos y cerramos el sistema de entrada
    destruyeTabla();
    yylex_destroy();
    exit(EXIT_SUCCESS);
}

double help(){

}

double echo(){

}

double tabla(){

}

double workSpace(){

}

double limpiarws(){

}

double cargar(char *fichero){
    yyin = fopen(fichero, "r");



}

double importar(char *libreria){

}