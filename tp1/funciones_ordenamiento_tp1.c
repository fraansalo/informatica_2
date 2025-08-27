#include "funciones_tp1.h"
#include "funciones_ordenamiento.h"
#include "funciones_str_tp1.h"



void intercambiar(articulo_t* a, articulo_t* b) {
    articulo_t temp = *a;
    *a = *b;
    *b = temp;
}


void menu_ordenamiento(articulo_t *articulos){
int opcion;
opcion = pedir_validado("\n---------->como desea ordenar los articulos?\n1.Por total\n2.alfabeticamente\nOpcion: ", validar_rango, RANGO(1,2));

switch (opcion) {
    case 1:
        ordenar_articulos(articulos, cant_articulos, comparar_por_total);
        break;
    case 2:
        ordenar_articulos(articulos, cant_articulos, comparar_alfabeticamente);
        break;
    default:
        printf("Opcion no valida. Mostrando sin ordenar.\n");   
    }
}


int comparar_por_total(articulo_t a, articulo_t b) {
    return a.Total - b.Total;
}


int comparar_alfabeticamente(articulo_t a, articulo_t b) {
    return mi_strcmp(a.descripcion, b.descripcion);
}

void ordenar_articulos(articulo_t* lista, int cantidad, criterio_t criterio) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (criterio(lista[j], lista[j+1]) < 0) {
                intercambiar(&lista[j], &lista[j+1]);
            }
        }
    }
}