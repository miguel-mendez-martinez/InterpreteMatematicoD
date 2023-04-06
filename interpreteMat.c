#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreteMat.h"
#include "system.h"


void interpreteMatD(char *arg){

    //en esta función se inicia en interprete, si llega un archivo, primero se ejecuta su analisis y luego se deja el interprete abierto a uso
    
    if (arg!=NULL)
    {
        //llegó algo que ejecutar, puede ser la opción -h, que es la opción para que aparezca la ayuda, o un fichero a cargar
        if (strcmp(arg, "-h") == 0) {
            //help();
        } else {
            //cargar(arg);
        }
    }

    yyparse(); //funcion que activa lo implementado en byson
}

/*tipoelem compLex = {NULL, 0};
    printf("AnalizadorSintactico operativo\n");
    iniciarAnalizadorLexico(arg);
    printf("----- INICIO DEL ANALISIS -----\n");
    sigCompLexico(&compLex);
    while (compLex.valor != EOF) {
        if (compLex.identificador != NULL) { // Realízase esta comprobación xa que en caso de erro o lexema será NULL
            printf("< %d, %s >\n", compLex.valor, compLex.identificador);
        }
        sigCompLexico(&compLex);
    }
    printf("-----  FIN DEL ANALISIS   -----\n");

    finalizarAnalizadorLexico(&compLex);*/