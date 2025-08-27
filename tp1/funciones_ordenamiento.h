#ifndef _ORDEN_H
#define _ORDEN_H

#include <stdio.h>
#include <string.h>

/*
 * Prototipo de funcion intercambiar - Intercambio de posicion entre dos posiciones adyacentes del arreglo de estructuras.
 * @params: {articulo_t *, articulo *} - Punteros a las direcciones de una estructura y a la estructura siguiente.
 * @returns: {void}
 */
void intercambiar(articulo_t* a, articulo_t* b);

/*
 * Prototipo de funcion menu_ordenamiento - Despliegue de menu para opciones de ordenamiento con distinto criterio
 * @params: {articulo_t *} - Puntero a arreglo de estructuras.
 * @returns: {void}
 */
void menu_ordenamiento(articulo_t *articulos);

/*
 * Prototipo de funcion ordenar_articulos - Ordena arreglo de estructuras segun criterio de comparación recibido
 * @params: {articulo_t *, int, criterio_t} - Puntero al arreglo de estructuras, cantidad de elementos a ordenar y puntero a función que define criterio de comparación.
 * @returns: {void}
 */
void ordenar_articulos(articulo_t *lista, int cantidad, criterio_t criterio);

/*
 * Prototipo de funcion comparar_por_total Compara los totales de las estructuras adyacentes usando funciones a puntero.
 * @params: {articulo_t, articulo_t} - Estructuras a comparar.
 * @returns: {int} - Devuelve un entero positivo o negativo en función de que estructura tiene mayor total 
 */
int comparar_por_total(articulo_t a,articulo_t b);

/*
 * Prototipo de funcion comparar_alfabeticamente - Compara alfabeticamente las descripciones de estructuras adyacentes usando funciones a puntero.
 * @params: {articulo_t, articulo_t} - Estructuras a comparar.
 * @returns: {int} - devolvera valor positivo o negativo en función al orden de los parametros pasados
 */
int comparar_alfabeticamente(articulo_t a,articulo_t b);

#endif