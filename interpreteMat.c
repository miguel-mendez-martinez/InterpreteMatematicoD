#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.yy.h"
#include "interpreteMat.h"
#include "system.h"
#include "bison.tab.h"
#include "tablaSimbolos.h"


void interpreteMatD(char *nombreFichero){

    //en esta función se inicia en interprete, si llega un archivo, primero se ejecuta su analisis y luego se deja el interprete abierto a uso
    
    if (nombreFichero!=NULL)
    {
        //llegó algo que ejecutar, puede ser la opción -h, que es la opción para que aparezca la ayuda, o un fichero a cargar
        if (strcmp(nombreFichero, "-h") == 0) {
            help();
        } else {
            cargar(nombreFichero);
        }
    }

    yyparse(); //funcion que activa lo implementado en byson
}