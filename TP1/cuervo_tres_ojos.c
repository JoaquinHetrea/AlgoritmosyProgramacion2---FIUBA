#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cuervo_tres_ojos.h"
#define CARACTER_PASADO 'P'
#define CARACTER_FUTURO 'F'
#define FORMATO_LISTADO "%s;%s;%s;%c\n"

/*
 * Recibe el nombre del cuervo a invocar.
 * Creará la estructura cuervo_tres_ojos, reservando la memoria necesaria.
 * Devolverá la estructura con los topes de las visiones inicializados en 0.
 * En caso de no poder invocar al cuervo, devolverá NULL.
 */
cuervo_tres_ojos_t * invocar_cuervo(char* nombre){
	cuervo_tres_ojos_t * cuervo_viejo;
	cuervo_viejo = malloc(sizeof(cuervo_tres_ojos_t));
	if(cuervo_viejo == NULL){
		printf("Ocurrió un error: Memoria Agotada\n");
		return NULL;
	} else {
		strcpy(cuervo_viejo->nombre, nombre);
		cuervo_viejo->cantidad_visiones_pasado = 0;
		cuervo_viejo->cantidad_visiones_futuro = 0;
		cuervo_viejo->visiones_del_pasado = NULL;
		cuervo_viejo->visiones_del_futuro = NULL;
	}
	return cuervo_viejo;
}

/*
 * Recibe el nombre del aprendiz a invocar.
 * Creará la estructura cuervo_aprendiz, reservando la memoria necesaria.
 * Devolverá la estructura con el tope de las visiones inicializado en 0.
 * En caso de no poder invocar al aprendiz, devolverá NULL.
 */
cuervo_aprendiz_t* invocar_aprendiz(char* nombre){
	cuervo_aprendiz_t * cuervo_nuevo;
	cuervo_nuevo = malloc(sizeof(cuervo_aprendiz_t));
	if(cuervo_nuevo == NULL){
		printf("Ocurrió un error: Memoria Agotada\n");
		return NULL;
	} else {
		strcpy(cuervo_nuevo->nombre, nombre);
		cuervo_nuevo->cantidad_visiones = 0;
		cuervo_nuevo->visiones_adquiridas = NULL;
	}
	return cuervo_nuevo;
}

/*
 * Agrega una vision al vector de visiones,
 * reservando la memoria necesaria para ella.
 * Devolverá 0 si pudo agregarla o -1 si no pudo.
 */
int agregar_vision_auxiliar(vision_t** visiones_cuervo, int* cantidad_visiones, vision_t vision){
		void* puntero_auxiliar = realloc(*visiones_cuervo, (size_t)(*cantidad_visiones + 1) * sizeof(vision_t));
		if(puntero_auxiliar == NULL){
			return -1;
		} else {
			*visiones_cuervo = puntero_auxiliar;
			*(*visiones_cuervo + (*cantidad_visiones)) = vision;
			(*cantidad_visiones)++;
		}
		return 0;
}

/*
 * Agrega una vision al vector de visiones correspondiente.
 * Reservando la memoria necesaria para ella.
 * Devolverá 0 si pudo agregarla o -1 si no pudo.
 */
int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){
	bool pudo_agregar;
	if(vision.epoca == CARACTER_PASADO){
		pudo_agregar = !agregar_vision_auxiliar(&cuervo->visiones_del_pasado, &cuervo->cantidad_visiones_pasado, vision);
	} else if(vision.epoca == CARACTER_FUTURO){
		pudo_agregar = !agregar_vision_auxiliar(&cuervo->visiones_del_futuro, &cuervo->cantidad_visiones_futuro, vision);
	}
	return pudo_agregar;
}

/*
 * Recibe un puntero a un cuervo_aprendiz_t y una visión.
 * Devuelve true si la visión es igual campo a campo a
 * una de las visiones adquiridas del aprendiz.
 */
bool es_repetida(cuervo_aprendiz_t* aprendiz, vision_t vision){
	bool es_repetida = false;
	for(int i = 0;i < aprendiz->cantidad_visiones;i++){
		if((strcmp((aprendiz->visiones_adquiridas + i)->protagonista, vision.protagonista) == 0) && (strcmp((aprendiz->visiones_adquiridas + i)->casa_protagonista, vision.casa_protagonista) == 0) && 
			(strcmp((aprendiz->visiones_adquiridas + i)->descripcion, vision.descripcion) == 0) && ((aprendiz->visiones_adquiridas + i)->epoca == vision.epoca)){
			es_repetida = true;
		}
	}
	return es_repetida;
}

/*
 * Transmitirá al aprendiz las visiones del cuervo que sean transmisibles 
 * de acuerdo a la funcion recibida como parámetro.
 * En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida),
 * no se agrega a las visiones del mismo.
 * Devolverá 0 si se transmitieron, -1 en caso contrario
 */
int transmitir_visiones_auxiliar(vision_t* visiones_cuervo, int cantidad_visiones, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
	for(int i = 0;i < cantidad_visiones;i++){
		if((*es_transmisible)(*(visiones_cuervo + i))){
			if(!es_repetida(aprendiz, *(visiones_cuervo + i))){
				void* puntero_auxiliar = realloc(aprendiz->visiones_adquiridas, (size_t)(aprendiz->cantidad_visiones + 1) * sizeof(vision_t));
				if(puntero_auxiliar == NULL){
					return -1;
				} else {
					aprendiz->visiones_adquiridas = puntero_auxiliar;
					*(aprendiz->visiones_adquiridas + aprendiz->cantidad_visiones) = *(visiones_cuervo + i);
					(aprendiz->cantidad_visiones)++;
				}
			}
		}
	}
	return 0;
}

/*
 * Transmitirá al aprendiz las visiones del pasado y del futuro del cuervo que sean 
 * transmisibles de acuerdo a la función recibida como parámetro.
 * En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida), 
 * no se agrega a las visiones del mismo.
 * Devolverá 0 si se transmitieron con eso, -1 en caso contrario
 */
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
	bool pudo_transmitir;
	pudo_transmitir = !transmitir_visiones_auxiliar(cuervo->visiones_del_pasado, cuervo->cantidad_visiones_pasado, aprendiz, (*es_transmisible));
	if(pudo_transmitir){
		pudo_transmitir = !transmitir_visiones_auxiliar(cuervo->visiones_del_futuro, cuervo->cantidad_visiones_futuro, aprendiz, (*es_transmisible));
	}

	return pudo_transmitir;
}

/*
 * Mostrará por pantalla las visiones adquiridas por el aprendiz.
 * Una visión se listará sólo si la función recibida como parámetro lo permite.
 */
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t)){
	for(int i = 0;i < aprendiz.cantidad_visiones;i++){
		if((*es_listable)(*(aprendiz.visiones_adquiridas + i))){
			printf(FORMATO_LISTADO, (aprendiz.visiones_adquiridas + i)->protagonista, (aprendiz.visiones_adquiridas + i)->casa_protagonista,
			(aprendiz.visiones_adquiridas + i)->descripcion, (aprendiz.visiones_adquiridas + i)->epoca);
		}
	}
}

/*
 * Destruirá la estructura del cuervo, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_cuervo(cuervo_tres_ojos_t* cuervo){
	if(cuervo != NULL){
		if(cuervo->visiones_del_pasado != NULL){
			free(cuervo->visiones_del_pasado);
		}
		if(cuervo->visiones_del_futuro != NULL){
			free(cuervo->visiones_del_futuro);
		}
		free(cuervo);
		return 0;
	} else {
		printf("Cuervo invalido\n");
		return -1;
	}
}

/*
 * Destruirá la estructura del aprendiz, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_aprendiz(cuervo_aprendiz_t* cuervo){
	if(cuervo != NULL){
		if(cuervo->visiones_adquiridas != NULL){	
			free(cuervo->visiones_adquiridas);
		}
		free(cuervo);
		return 0;
	} else {
		printf("Cuervo invalido\n");
		return -1;
	}
}
