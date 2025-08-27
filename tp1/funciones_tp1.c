#include "funciones_tp1.h"
#include "funciones_ordenamiento.h"
#include "funciones_str_tp1.h"

void inicializar_articulos(articulo_t* lista, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        (*(lista+i)).descripcion[0] = '\0';
        (*(lista+i)).Total = 0;
        for (int j = 0; j < 3; j++) (*(lista+i)).cant_sucursal[j] = 0;
    }
}

int validar_rango(int valor, void* contexto) {
    rango_t* r = (rango_t*) contexto;
    return valor >= r->min && valor <= r->max;
}

int pedir_validado(const char* mensaje, validador_t validador, void* contexto) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (!validador(valor, contexto)) {
            printf("..ERROR. valor invalido. Intente nuevamente.\n");
        }
    } while (!validador(valor, contexto));
    return valor;
}


int buscar_articulo(articulo_t* lista, char desc[]){
    int i = 0;
    while( (*(lista +i)).descripcion[0] && mi_strcmp(desc,(*(lista +i)).descripcion)) i++;
    return i;
}

void calcular_total(articulo_t* art){
    art->Total = 0;
    for(int i=0; i<cant_sucursales; i++) art->Total += art->cant_sucursal[i];
}

void mostrar_articulos(articulo_t *art){
    int i=0;
    printf("\n\n%-15s %-10s %-10s %-10s %-10s\n", "Articulo", "Sucursal 1", "Sucursal 2", "Sucursal 3", "Total");
    while(i<cant_articulos && (*(art+i)).descripcion[0]){
        printf("%10s %10d %10d %10d %10d\n", (*(art+i)).descripcion, (*(art+i)).cant_sucursal[SUCURSAL_1],(*(art+i)).cant_sucursal[SUCURSAL_2],(*(art+i)).cant_sucursal[SUCURSAL_3],(*(art+i)).Total);
        i++;
    }
}

articulo_t cargar_articulo(articulo_t *articulos){
    int sucursal=0,idx=0,cantidad=0;
    char descripcion[60];
    idx = 0;

    printf("---> ingrese descripcion de producto: ");
    scanf("%s",descripcion);
    idx = buscar_articulo(articulos,descripcion);
    ((articulos+idx))->idx = idx;
    mi_strcpy(((articulos+idx))->descripcion,descripcion);
    printf("\t.%s, indice: %d\n",(articulos+idx)->descripcion,(articulos+idx)->idx);

    sucursal = pedir_validado("---> ingrese que sucursal realiza la carga(1-3): ", validar_rango, RANGO(1,3));
    cantidad = pedir_validado("---> ingrese cantidad del articulo a cargar: ", validar_rango, RANGO(1,1000));
    
    (*(articulos+idx)).cant_sucursal[sucursal-1] += cantidad;
    calcular_total((articulos+idx));
    printf("Articulo en indice %d: %s\n", idx, articulos[idx].descripcion);

    return (*(articulos+idx));
}


int continuar_carga(void){
    int opc;
    printf("\n\n. desea finalizar la carga? (1.SI  2.NO): ");
    scanf("%d",&opc);
    return opc;
}