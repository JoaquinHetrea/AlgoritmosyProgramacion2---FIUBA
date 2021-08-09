#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cuervo_tres_ojos.h"
#define NOMBRE_CUERVO_VIEJO "Verdevidente"
#define NOMBRE_CUERVO_NUEVO "Bran Stark"
#define NOMBRE_ARCHIVO_VISIONES "visiones.txt"
#define CARACTER_PASADO 'P'
#define CARACTER_FUTURO 'F'
#define CANT_CAMPOS_VISION 4
#define FORMATO_LECTURA "%[^;];%[^;];%[^;];%c\n"

/*
 * Recibe una visión.
 * Devuelve true si el protagonista
 * de la visión es Jon Snow.
 */
bool es_de_jon_snow(vision_t vision){
	if(strcmp(vision.protagonista, "Jon Snow") == 0){
		return true;
	} else { 
		return false;
	}
}

/*
 * Recibe una visión.
 * Devuelve true si la epoca de 
 * la visión es del pasado.
 */
bool es_del_pasado(vision_t vision){
	if(vision.epoca == CARACTER_PASADO){
		return true;
	} else { 
		return false;
	}
}

/*
 * Recibe una visión.
 * Devuelve true si la epoca de 
 * la visión es del futuro.
 */
bool es_del_futuro(vision_t vision){
	if(vision.epoca == CARACTER_FUTURO){
		return true;
	} else { 
		return false;
	}
}

/*
 * Recibe una visión.
 * Devuelve true si la protagonista de 
 * la visión es Daenerys Targaryen.
 */
bool es_de_daenerys(vision_t vision){
	if(strcmp(vision.protagonista, "Daenerys Targaryen") == 0){
		return true;
	} else { 
		return false;
	}
}

/*
 * Recibe una visión.
 * Devuelve true si la casa del protagonista
 * de la visión es Lannister.
 */
bool es_de_los_lannister(vision_t vision){
	if(strcmp(vision.casa_protagonista, "Lannister") == 0){
		return true;
	} else { 
		return false;
	}
}

/*
 * Recibe el FILE* de un archivo de texto y una visión.
 * Se cargan los campos de la vision con datos del archivo y
 * devuelve la cantidad de elementos escritos.
 */
int leer_vision(FILE* archivo, vision_t* vision){
	return fscanf(archivo, FORMATO_LECTURA, vision->protagonista, vision->casa_protagonista, vision->descripcion, &vision->epoca);
}

/*
 * Recibe un puntero a un cuervo_tres_ojos_t y
 * un puntero a un cuervo_aprendiz_t.
 * Libera la memoria de ambos cuervos.
 * Devuelve -1 si uno de los cuervos es inválido.
 */
int destruir_cuervos(cuervo_tres_ojos_t* cuervo_anciano, cuervo_aprendiz_t* cuervo_nuevo){
	bool pudo_destruir = 0;
	pudo_destruir = destruir_cuervo(cuervo_anciano);
	if(pudo_destruir){
   		pudo_destruir = destruir_aprendiz(cuervo_nuevo);
   	} else {
   		destruir_aprendiz(cuervo_nuevo);
   	}

   	return pudo_destruir;
}

int main(){
	int elementos_leidos = 0;
	bool pudo_agregar = true, pudo_transmitir = true;
	vision_t vision_leida;

	bool (*func_ha_transmitir[])(vision_t) = {es_de_jon_snow, es_de_los_lannister, es_de_daenerys};	
	int cantidad_func_transmitir = sizeof(func_ha_transmitir)/sizeof(bool*);

	bool(*func_ha_listar[])(vision_t) = {es_del_pasado, es_de_los_lannister};
	int cantidad_func_listar = sizeof(func_ha_listar)/sizeof(bool*);

    FILE* visiones = fopen(NOMBRE_ARCHIVO_VISIONES, "r");
    if(visiones == NULL){
    	printf("Error al abrir el archivo de visiones\n");
    	return -1; 	
    }

    cuervo_tres_ojos_t * cuervo_anciano = invocar_cuervo(NOMBRE_CUERVO_VIEJO);
	cuervo_aprendiz_t * cuervo_nuevo = invocar_aprendiz(NOMBRE_CUERVO_NUEVO);

	if((cuervo_anciano != NULL) && (cuervo_nuevo != NULL)){
	    elementos_leidos = leer_vision(visiones, &vision_leida);
	    while((elementos_leidos == CANT_CAMPOS_VISION) && (pudo_agregar)){
	    	pudo_agregar = agregar_vision(cuervo_anciano, vision_leida);
	    	elementos_leidos = leer_vision(visiones, &vision_leida);
	    }
	}

    fclose(visiones);
    
    if(elementos_leidos == EOF){
		if(pudo_agregar){			
			int i = 0;
			while((i < cantidad_func_transmitir) && (pudo_transmitir)){
				pudo_transmitir = transmitir_visiones(cuervo_anciano, cuervo_nuevo, func_ha_transmitir[i]);
				i++;
			}		
			if(pudo_transmitir){
				for(int i = 0;i < cantidad_func_listar;i++){
					listar_visiones_transmitidas(*cuervo_nuevo, func_ha_listar[i]);
				}
			} else {
				printf("Error al transmitir visiones\n");
			}
		} else {
			printf("Error al agregar visiones\n");
		}
	} else {
		printf("No se pudo realizar correctamente la lectura de visiones. Línea invalida\n");
	}

	return destruir_cuervos(cuervo_anciano, cuervo_nuevo);
}