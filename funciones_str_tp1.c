#include "funciones_tp1.h"
#include "funciones_ordenamiento.h"
#include "funciones_str_tp1.h"

int mi_strlen(char *s){
    int longitud = 0;
    while (*s){
        longitud++;
        s++;
    }
    return longitud+1;
}

void mi_strcpy(char *destino, char *origen){
    while(*origen){
        *destino = *origen;
        origen ++;
        destino++;
    } *destino = '\0';
    return;
}


int mi_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        }return (unsigned char)*s1 - (unsigned char)*s2;
}