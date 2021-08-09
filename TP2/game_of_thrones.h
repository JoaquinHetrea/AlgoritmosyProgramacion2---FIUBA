#ifndef __GAME_OF_THRONES_H__
#define __GAME_OF_THRONES_H__

#include "cola.h"
#include "abb.h"
#include "lista.h"
#include <stdio.h>
#include <string.h>
#define MAX_NOMBRE_ARCHIVO 30
#define MAX_NOMBRE_PERSONA 50
#define CANTIDAD_MAXIMA_CASAS 100
#define ESPERANZA_DE_VIDA 60
#define ARCHIVO_NOMBRES "nombres.txt"
#define FORMATO_CASA "%[^;];%zu;%zu\n"
#define FORMATO_INTEGRANTE "%[^;];%zu\n"
#define CASA 'C'
#define INTEGRANTE 'I'
#define EXITO 0
#define ERROR -1
#define ERROR_ARCHIVO -2
#define LECTURA "r"

typedef struct reino {
	abb_t* arbol_casas;
	cola_t* casas_extintas;
} reino_t;

typedef struct casa {
	char nombre[MAX_NOMBRE_PERSONA];
	size_t factor_envejecimiento;	
	size_t factor_nacimiento;
	lista_t* integrantes;
} casa_t;

typedef struct integrante {
	char nombre[MAX_NOMBRE_PERSONA];
	size_t edad;
} integrante_t;

/*
 * Crea un reino reservando la memoria necesaria.
 * Devuelve un puntero al reino creado o NULL en caso de error.
 */
reino_t* reino_crear(int (*comparador)(void*, void*));

/*
Lee y crea casas, y las agrega al arbol
Requiere que exista memoria disponible en el sistema
*/
int leer_y_agregar_casas(abb_t* arbol_casas, FILE* archivo);

/*
Pide una cantidad de años y simula esa cantidad ingresada
Por cada año, recorre todas las casas y: Aumenta la edad de
todos sus integrantes segun indique el factor de envejecimiento de la casa,
elimina los integrantes mayores de edas, encola y elimina del arbol las casas 
que no tienen integrantes, y muestra por pantalla las casas y su cantidad de integrantes.
Se requiere un archivo con nombres, en caso de no podes abrirlo retorna -1
*/
int simulacion(reino_t* reino);

/*
Pide el usuario el nombre de un archivo que contenga una casa y si este archivo existe agrega la casa.
Si la casa ya fue ingresada, agrega los integrantes. Si no fue ingresada, crea la casa.
Requiere que exista memoria disponible en el sistema. 
*/
int agregar_casa(abb_t* arbol_casas);

/*
Muestra todas las casas y los integrantes de cada una
Necesita que exista memoria disponible en el sistema
*/
int mostrar_integrantes(abb_t* arbol_casas);

/*
Muestras las casas extintas en el orden en el que se extinguieron
Necesita que exita memoria disponible en el sistema
*/
int mostrar_casas_extintas(cola_t* casas_extintas);

/*
Destruye el reino, liberando toda la memoria de los integrantes y las casas
*/
void destruir_reino(reino_t* reino);

#endif