#ifndef _CONF_H
#define _CONF_H
#include <stdio.h>
#include <string.h>

#define cant_articulos 60
#define cant_sucursales 3
#define RANGO(min, max) &(rango_t){min, max}

typedef struct{
    int min;
    int max;
}rango_t;


typedef enum{
    SUCURSAL_1 = 0,
    SUCURSAL_2 = 1,
    SUCURSAL_3 = 2,
}sucursales_t;

typedef struct{
    char descripcion[60];
    int cant_sucursal[3];
    int Total;
    int idx;
}articulo_t;

typedef int (*validador_t)(int valor, void* contexto);
typedef int (*criterio_t)(articulo_t a, articulo_t b);
typedef unsigned char uint8_t;

/*
 * Prototipo de funcion validar_rango - 
 * @params: {int, void *} - Numero entero a validar y puntero a una estructura de tipo rango_t que contiene los limites del rango
 * (se pasa como puntero void generico para poder recibir cualquier tipo de dato. Luego lo transformamos a tipo rango_t).
 * @returns: {int} - Devuelve 1 o 0 en función a si el valor se encuentra en el rango.
 */
int validar_rango(int valor, void* contexto);

/*
 * Prototipo de funcion pedir_validado - Solicita un valor y lo valida segun el criterio proporcionado mediante puntero a función.
 * @params: {const char *, validador_t, void *} - Mensaje a mostar, puntero a función de validación y contexto adicional necesario para validar.
 * @returns: {int} - Devuelve el valor ingresado que haya pasado la validacion.
 */
int pedir_validado(const char* mensaje, validador_t validador, void* contexto);


/*
 * Prototipo de funcion inicializar_articulos - Inicializa en cero los parámetros de los elementos de la estructura
 * @params: {articulo_t *, int} - Puntero arreglo de estructura tipo articulo_t y cantidad de elementos
 * @returns: {void}
 */
void inicializar_articulos(articulo_t* lista, int cantidad);

/*
 * Prototipo de funcion cargar_articulo - Carga inicial de la estructura.
 * @params: {articulos_t *} - Puntero a arreglo de estructuras
 * @returns: {articulo_t} - Devuelve estructura cargada.
 */
articulo_t cargar_articulo(articulo_t *articulos);

/*
 * Prototipo de funcion buscar_articulo busca la estructura coincidente de la descripcion.
 * @params: {articulo_t *, char []} - Puntero a arreglo de estructura y parametro de descripcion
 * @returns: {int} - Devuelve indice de estructura
 */
int buscar_articulo(articulo_t* lista,char desc[]);

/*
 * Prototipo de funcion calcular_total - Calcula sumatoria de las sucursales y lo asigna al parametro Total.
 * @params: {articulo_t *} - Puntero a arreglo de estructuras
 * @returns: {void}
 */
void calcular_total(articulo_t * art);

/*
 * Prototipo de funcion mostrar_articulo - Muestreo de los datos de cada estructura.
 * @params: {articulo_t *} - Puntero a arreglo de estructuras
 * @returns: {void}
 */
void mostrar_articulos(articulo_t *art);


/*
 * Prototipo de funcion continuar_carga - Despliegue de menu para indicar continuidad de la carga de ficheros.
 * @params: {void} 
 * @returns: {int} - Devuelve un valor entero que indica si se sigue o no con la carga
 */
int continuar_carga(void);


#endif