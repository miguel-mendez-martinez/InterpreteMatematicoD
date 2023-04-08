#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "interpreteMat.h"

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
 *  */

void buscaElemento(CompLexico *element);

void insertarComponente(CompLexico comp);

void modificarValorVariable(char *lexema, double valor);

CompLexico buscarLexema(char *lexema);

void printWorkSpace();

void eliminarWorkSpace();
#endif