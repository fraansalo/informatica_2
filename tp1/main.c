#include "funciones_tp1.h"
#include "funciones_ordenamiento.h"

int main(int argc, const char **argv){
    articulo_t articulos[cant_articulos];
    articulo_t mi_articulo;

    inicializar_articulos(articulos,cant_articulos);
    printf("**********Bienvenidos TP1**********\n\n");
    do{
        mi_articulo = cargar_articulo(articulos);
        articulos[mi_articulo.idx] = mi_articulo;
    } while (continuar_carga() == 2);

    mostrar_articulos(articulos);
    menu_ordenamiento(articulos);
    mostrar_articulos(articulos);

    return 0;
}