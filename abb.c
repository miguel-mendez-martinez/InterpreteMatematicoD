#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreteMat.h"
#include "bison.tab.h"

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};


/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->lexema;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    if(strcmp(cl1,cl2) == 0){
        return 0;
    }else if(strcmp(cl1,cl2) > 0){
        return 1;
    }else{
        return -1;
    }
}

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}

void aux_destruir_elem(tipoelem *elem){
    free(elem->lexema);
}

void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        destruir(&(*A)->der);
        aux_destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, tipoelem *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}
//Función privada para informar si una clave está en el árbol

unsigned _es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _es_miembro_clave(der(A), cl);
    }
    //cl < A->info
    return _es_miembro_clave(izq(A), cl);
}

//Funciones públicas

unsigned es_miembro(abb A, tipoelem E) {
    return _es_miembro_clave(A, _clave_elem(&E));
}

//si no encuentra devuelve NULL
void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        *nodo = A->info;
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(A->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(A->der, cl, nodo);
    }
}
//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo 
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.valorLexico = E.valorLexico;
        (*A)->info.lexema = malloc((strlen(E.lexema) + 1) * sizeof(char)); //añadimos 1 para que strcpy nos incluya el /0
        strcpy((*A)->info.lexema, E.lexema);
        (*A)->info.valor = E.valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        insertar(&(*A)->der, E);
    } else {
        insertar(&(*A)->izq, E);
    }
}

/* Funcion privada que devuelve mínimo de subárbol dcho */
tipoelem _suprimir_min(abb * A) {//Se devuelve el elemento más a la izquierda
    abb aux;
    tipoelem ele;
    if (es_vacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        if(es_vacio((*A)->der)){
            //si el arbol derecho no tiene nada liberamos memoria
            aux_destruir_elem(&(*A)->info);
            free(*A);
            *A = NULL;
        }else{
            //si hay subarbol derecho substituimos
            *A = (*A)->der;
        }
        aux_destruir_elem(&aux->info);
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

/* Funcion que permite eliminar un nodo del arbol */
void suprimir(abb *A, tipoelem E) {
    abb aux;
    if (es_vacio(*A)) {
        return;
    }

    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp < 0) { //if (E < (*A)->info) {
        suprimir(&(*A)->izq, E);
    } else if (comp > 0) { //(E > (*A)->info) {
        suprimir(&(*A)->der, E);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) { //no tiene subarboles
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) { // existe un subarbol izq
        //printf("Tiene subarbol izq.\n");
        aux = *A;
        *A = (*A)->der;
        free(aux);
    } else if (es_vacio((*A)->der)) { // existe un subarbol der
        //printf("Tiene subarbol der.\n");
        aux = *A;
        *A = (*A)->izq;
        free(aux);
    } else { //existen subarboles a ambos lados, busco mínimo subárbol derecho, pues voy a susututuir el nodo con el mínimo del subárbol derecho
        //printf("Hola voy a suprimir minimos.\n");
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(abb A, tipoclave cl, tipoelem nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}

void modificarNodo(abb *A, tipoclave clave, double valorMod){
    if (es_vacio(*A)) {
        return;
    }

    int comp = _comparar_clave_elem(clave,(*A)->info);
    if(comp == 0){
        (*A)->info.valor.var = valorMod;
    }else if(comp < 0){
        modificarNodo(&(*A)->izq, clave, valorMod);
    }else{
        modificarNodo(&(*A)->der, clave, valorMod);
    }
}

/* Permite modificar el nodo extrayendo del mismo la clave */
void modificar(abb A, tipoelem nodo) {
    tipoclave cl = _clave_elem(&nodo);
    _modificar(A, cl, nodo);
}