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
           "\t\t Bienvenido al interprete matemático de Miguel Méndez Martínez  \n"
           "\t\t Esto es una beta, con algunas funciones aun por arreglar y mejorar. \n\n"
           "\t\t Hay dos constantes definidas, 'e' y 'pi' que no se pueden modificar.  \n\n"
           "\t\t Las operaciones permitidas son la suma '+', la resta '-', la multiplicación '*', división '/',\n"
           "\t\t módulo '%%' y la potencia '^', cuidado con esta última, porque se debe usar la tecla ^, luego la barra \n"
           "\t\t espaciadora y luego el segundo numero, si se hace directo muchas veces da problemas. \n"
           "\t\t Además de estas operaciones, se incluyen en la tabla varias funciones matemáticas: sin, cos, tan, ln, log y exp. \n\n"
           "\t\t Estas funciones se llaman con un único argumento, entre parentesis y su resultado puede ser asignado a  \n"
           "\t\t variables o usado en operaciones mas complejas. \n"
           "\t\t  \n\n\n"
           "\tCOMANDOS\n"
           "\t\tPara la ejecución de comandos se pueden usar o no los parentesis. Los comandos sin parámetros son 'CMND'\n"
           "\t\to 'CMND()', respectivamente; y los comandos con un argumento sería FUNC ARG o FUNC(ARG), respectivamente.\n\n"
           "\t\tLos comandos correctamente implementados, y que funcionan son:\n\n"
           "\t\t\t- help\t\t\t\tMuestra este mensaje. Tambien podemos mostrarlo directo con la opción  \n"
           "\t\t\t\t\t\t\t '-h' tal que: './interMatD23 -h'.\n\n"
           "\t\t\t\t\t\t\tTambien se pueden ejecutar ficheros al iniciar el programa pasando el nombre por\n"
           "\t\t\t\t\t\t\targumentos: './interMatD23 FICHERO'.\n\n"
           "\t\t\t- clear\t\t\t\tLimpia la terminal.\n\n"
           "\t\t\t- echo\t\t\t\tActiva o Desactiva la impresión de los resultados. Por defecto está activada.\n\n"
           "\t\t\t- limparws\t\t\tLimpa el espacio de traballo.\n\n"
           "\t\t\t- salir\t\t\t\tSale del intérprete, finalizando el programa.\n\n"
           "\t\t\t- tabla\t\t\t\tMuestra la tabla de simbolos, que tiene los comandos, constantes, funciones usadas\n"
           "\t\t\t\t\t\t\ty en medio de ejecuciones, si se han creado, variables.\n\n"
           "\t\t\t- ws\t\t\t\tMuestra el espacio de trabajo actual, que contiene las variables creadas hasta el momento.\n\n"
           "\t\t\t- cargar\t\t\tCarga un fichero que se encuentre en el directorio. Actualmente esta función no se \n\n"
           "\t\t\t\t\t\t\tencuentra correctamente implementada, se puede llamar pero genera un error sintáctico \n\n"
           "\t\t\t\t\t\t\ty sale del programa, por lo que no recomiendo su uso.\n\n"
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
    yyin = fopen(fichero, "r");

    if(yyin == NULL){
        printf(ROJO"FICHERO NO ENCONTRADO."RESET"\n\n");
    }else{
        ejecutandoScript(1);
    }

    return 0;

}