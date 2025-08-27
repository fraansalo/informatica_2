#ifndef _STR_H
#define _STR_H

/*
 * Prototipo de funcion mi_strlen - Funcion que emula strlen de string.h
 * @params: {char *} - Puntero a string para calcular la longitud
 * @returns: {int} - Entero que me indica la longitud del string ingresado
 */
int mi_strlen(char *caracter);

/*
 * Prototipo de funcion mi_strlen - Funcion que emula strcpy de string.h
 * @params: {char *, char*} - Punteros que me indican que string debo copiar en que string
 * @returns: {void}
 */
void mi_strcpy(char *destino, char *origen);

/*
 * Prototipo de funcion mi_strlen - Funcion que emula strcmp de string.h
 * @params: {char} - Punteros a string que me indican que palabras debo comparar.
 * @returns: {int} - Entero que segun sea positivo o negativo me indica la correspondencia de una palabra con otra.
 */
int mi_strcmp(const char *str1,const char *str2);

#endif