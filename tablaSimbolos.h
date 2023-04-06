#ifndef TABLA_H
#define TABLA_H

#include "definiciones.h"

/**
 * Funcion que inicializa la tabla de simbolos
 */
void initTabla();

/**
 * Funcion que libera la memoria la tabla de simbolos
 */
void destruyeTabla();

/**
 * Funcion que imprime la tabla de simbolos
 */
void printTabla();

/**
 * Funcion que busca un elemento en la tabla de simbolos
 * Si este existe, devuelve un struct con su valor 
 * Si no existe, se inserta en la tabla de simbolos y se devuelve un struct con su valor
 * @param elem elemento a buscar
 */
void buscaElemento(tipoelem *element);
#endif