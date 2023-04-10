#ifndef INTERPRETEMAT_H
#define INTERPRETEMAT_H

//declararemos algunos colores para cambiar los distintos echo de la consola
#define ROJO "\x1b[31m    "
#define VERDE "\x1b[32m    "
#define CYAN "\x1b[36m"
#define AMARILLO  "\x1b[33m    "
#define RESET "\x1b[0m"

//declaramos la estructura de componente léxico que se usará para almacenar los componentes léxicos
//de esta vez, se ha tenido que añadir una unión para el uso correcto con byson
//en otras entregas mi char * se llamaba identificador, por quitar ambiguedad del código he decidido cambiarle el nombre a lexema. Lo mismo con el int valor, para poder llamar asi a la unión
typedef struct  {
    char *lexema;
    int valorLexico;
    //usamos una union para poder tener informacion de distintos tipos, solo se puede acceder 1 campo cada vez y queda todo debajo de la misma dir de memoria
    union 
    {
        double var;
        double (*funcptr)(); //usado para el callback, de manera que podamos guardar funciones en la tabla de simbolos
    }valor;
    
} CompLexico;

//funcion que invoca nuestro interprete
void interpreteMatD(char *nombreFichero);

#endif	// Estructura del interprete matematico