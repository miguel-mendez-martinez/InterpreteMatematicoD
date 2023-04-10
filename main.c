#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"
#include "interpreteMat.h"

int main(int argc, char **argv){
    //argumentos
    if (argc == 1) {
        //creamos la tabla de simbolos
        initTabla(); 
        //iniciamos el interprete sin ejecutar nada al principio
        interpreteMatD(NULL);
    }else if(argc == 2){
        //creamos la tabla de simbolos
        initTabla();
        //iniciamos el interprete ejecutando un script de primeras
        interpreteMatD(argv[1]);
    }else{
        //error en el número de argumentos
        printf("\nERRO: número de parámetros incorrecto.\n\tUsa %s [FICHEIRO_CODIGO_FUENTE]\n", argv[0]);
    }

    exit(EXIT_SUCCESS);
    
}