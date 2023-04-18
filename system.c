#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "system.h"
#include "interpreteMat.h"
#include "lex.yy.h"
#include "bison.tab.h"
#include "tablaSimbolos.h"

int V_Echo = 1; //igual que en el byson.y, el echo esta activado por defecto.

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
    printf("\n===================================================================================================================================================\n\n"
           "\t\t\t\t\t\t\t\t\tHELP\n\n"
           "---------------------------------------------------------------------------------------------------------------------------------------------------\n\n"
           "\t  \n"
           "\t\t  \n"
           "\t\t  \n"
           "\t\t  \n\n"
           "\t\t  \n\n"
           "\t\t  \n"
           "\t\t  \n"
           "\t\t  \n"
           "\t\t  \n\n"
           "\t\t  \n"
           "\t\t  \n"
           "\t\t  \n\n\n"
           "\tCOMANDOS\n"
           "\t\tPara a execución de comandos hai dous tipos de sintaxe: con paréntesis ou sen eles. Nos comandos sen parámetros sería 'CMND'\n"
           "\t\tou 'CMND()', respectivamente; e nos comandos cun parámetro sería 'CMND PARAM' ou 'CMND(PARAM)', respectivamente.\n\n"
           "\t\tOs comandos dispoñibles son:\n\n"
           "\t\t\t- axuda\t\t\t\tMostra esta axuda. Tamén se pode mostar ao iniciar o propio intérprete indicando a\n"
           "\t\t\t\t\t\t\topción '-h': './nicalc -h'.\n\n"
           "\t\t\t- cargar FICHEIRO\t\tCarga e executa un ficheiro.\n"
           "\t\t\t\t\t\t\tEste ficheiro debe respectar a sintaxe do intérprete e non poderá cargar outros\n"
           "\t\t\t\t\t\t\tficheiros desde el (en caso de que o faga non se asegura o correcto funcionamento\n"
           "\t\t\t\t\t\t\tdo intérprete).\n"
           "\t\t\t\t\t\t\tTamén se poden executar ficheiros ao iniciar o propio intérprete inidicándoo como\n"
           "\t\t\t\t\t\t\targumento: './nicalc FICHEIRO'.\n\n"
           "\t\t\t- clear\t\t\t\tLimpa a terminal de saída.\n\n"
           "\t\t\t- echo\t\t\t\tActiva/Desactiva a impresión da información de saída. Por defecto está activada.\n\n"
           "\t\t\t- importar LIBRERIA\t\tImporta unha librería de forma dinámica a través do seu ficheiro .so.\n"
           "\t\t\t\t\t\t\tSe se indica só o nome, buscarase por orde nas rutas /lib e /usr/lib, non obstante\n"
           "\t\t\t\t\t\t\tpódense importar librerías indicando a ruta completa do seu ficheiro .so.\n\n"
           "\t\t\t- limparws\t\t\tLimpa o espazo de traballo.\n\n"
           "\t\t\t- sair\t\t\t\tSae do intérprete.\n\n"
           "\t\t\t- taboa\t\t\t\tMostra a táboa de símbolos, que contén os comandos, constantes, funcións usadas\n"
           "\t\t\t\t\t\t\talgunha vez, librerías importadas e variables.\n\n"
           "\t\t\t- ws\t\t\t\tMostrar o espazo de traballo actual, que contén as variables definidas ata o momento.\n\n"
           "\n===================================================================================================================================================\n\n");
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

double eliminarWs(){
    eliminarWorkSpace();
    printf(AMARILLO"Espacio de trabajo limpiado correctamente.\n\n"RESET);
    return 0;
}

double cargar(char *fichero){
    printf("He llegado a cargar el fichero\n");
    yyin = fopen(fichero, "r");

    if(yyin == NULL){
        printf(ROJO"FICHERO NO ENCONTRADO."RESET"\n\n");
    }else{
        ejecutandoScript(1);
    }

    return 0;

}