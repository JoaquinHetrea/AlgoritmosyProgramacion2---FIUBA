#include "cola.h"
#include "abb.h"
#include "lista.h"
#include <stdio.h>
#include <string.h>
#include "game_of_thrones.h"
#define INICIAR_SIMULACION 'S'
#define AGREGAR_CASA 'A'
#define MOSTRAR_INTEGRANTES 'L'
#define CASAS_EXTINTAS 'E'
#define FINALIZAR_EJECUCION 'Q'

/*
Compara los elementos como si fueran strings.
Devuelve mayor a 0 si el primero es mayor, 0 si son iguales o menor a 0 si el segundo es mayor.
*/
int comparador_nombres(void* elemento_1, void* elemento_2){
	if(elemento_1 && elemento_2)
		return strcmp(((casa_t*)elemento_1)->nombre, ((casa_t*)elemento_2)->nombre);
	return 0;
}

int main(){

	char nombre_archivo_inicial[MAX_NOMBRE_ARCHIVO];
	printf("Ingrese el nombre del archivo principal de casas: ");
	scanf("%s", nombre_archivo_inicial);

	FILE* archivo_casas = fopen(nombre_archivo_inicial, LECTURA);
	if(!archivo_casas){
		printf("No se pudo encontrar un archivo con tal nombre\n");
		return ERROR;
	}

	reino_t* reino = reino_crear(comparador_nombres);
	if(!reino)
		return ERROR;

	int estado_actual = leer_y_agregar_casas(reino->arbol_casas, archivo_casas);
	fclose(archivo_casas);

	char respuesta = 'B';
	while(respuesta != FINALIZAR_EJECUCION && estado_actual != ERROR){
		printf("\nMENU DE SIMULACION\n");
		printf("'%c' -> Iniciar Simulacion\n", INICIAR_SIMULACION);
		printf("'%c' -> Agregar Casa\n", AGREGAR_CASA);
		printf("'%c' -> Mostrar Integrantes por Casa\n", MOSTRAR_INTEGRANTES);
		printf("'%c' -> Mostrar Casas Extintas\n", CASAS_EXTINTAS);
		printf("'%c' -> Finalizar Ejecución\n", FINALIZAR_EJECUCION);
		scanf(" %c", &respuesta);
		
		switch(respuesta){
			case INICIAR_SIMULACION:
				estado_actual = simulacion(reino);
			break;
			case AGREGAR_CASA:
				estado_actual = agregar_casa(reino->arbol_casas);
			break;
			case MOSTRAR_INTEGRANTES:
				estado_actual = mostrar_integrantes(reino->arbol_casas);
			break;
			case CASAS_EXTINTAS:
				estado_actual = mostrar_casas_extintas(reino->casas_extintas);
			break;
		}
	}

	destruir_reino(reino);
	return EXITO;
}