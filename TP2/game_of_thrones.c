#include "game_of_thrones.h"

/*
 * Crea un reino reservando la memoria necesaria.
 * Devuelve un puntero al reino creado o NULL en caso de error.
 */
reino_t* reino_crear(int (*comparador)(void*, void*)){
	reino_t* reino = malloc(sizeof(reino_t));
	if(!reino)
		return NULL;
	reino->arbol_casas = arbol_crear(comparador, NULL);
	if(!reino->arbol_casas){
		free(reino);
		return NULL;
	}
	reino->casas_extintas = cola_crear();
	if(!reino->casas_extintas){
		arbol_destruir(reino->arbol_casas);
		free(reino);
		return NULL;
	}
	return reino;
}

/*
 * Crea una casa reservando la memoria necesaria.
 * Devuelve un puntero a la casa creada o NULL en caso de error.
 */
casa_t* casa_crear(char* nombre, size_t factor_envejecimiento, size_t factor_nacimiento){
	casa_t* casa = malloc(sizeof(casa_t));
	if(!casa)
		return NULL;
	strcpy(casa->nombre, nombre);
	casa->factor_envejecimiento = factor_envejecimiento;
	casa->factor_nacimiento = factor_nacimiento;
	casa->integrantes = lista_crear();
	if(!casa->integrantes)
		return NULL;
	return casa;
}

/*
 * Crea un integrante reservando la memoria necesaria.
 * Devuelve un puntero al integrante creado o NULL en caso de error.
 */
integrante_t* integrante_crear(char* nombre, size_t edad){
	integrante_t* integrante = malloc(sizeof(integrante_t));
	if(!integrante)
		return NULL;
	strcpy(integrante->nombre, nombre);
	integrante->edad = edad;
	return integrante;
}

/*
Lee un nombre y retorna la cantidad que pudo leer.
*/
int leer_nombre(FILE* archivo, char* nombre){
	if(feof(archivo))
		rewind(archivo);
	return fscanf(archivo, "%[^\n]\n", nombre);
}

/*
Lee los datos de una casa y retorna la cantidad que pudo leer.
*/
int leer_casa(FILE* archivo, casa_t* casa){
	return fscanf(archivo, FORMATO_CASA, casa->nombre, &casa->factor_envejecimiento, &casa->factor_nacimiento);
}

/*
Lee los datos de un integrante y retorna la cantidad que pudo leer.
*/
int leer_integrante(FILE* archivo, integrante_t* integrante){
	return fscanf(archivo, FORMATO_INTEGRANTE, integrante->nombre, &integrante->edad);
}

/*
Lee un caracter y retorna la cantidad que pudo leer.
*/
int leer_letra(FILE* archivo, char* letra){
	return fscanf(archivo, "%c;", letra);
}


/*
Lee Integrantes del archivo, los crea reservando memoria y los agrega a la lista.
Requiere que exista memoria disponible en el sistema.
*/
int agregar_integrantes_de_archivo(FILE* archivo, lista_t* lista_integrantes, char* letra, int* leido){
	integrante_t integrante;
	(*leido) = leer_letra(archivo, letra);
	while((*letra) == INTEGRANTE && (*leido) > 0){
		(*leido) = leer_integrante(archivo, &integrante);
		if((*leido) != 2)
			return ERROR;
		integrante_t* nuevo_integrante = integrante_crear(integrante.nombre, integrante.edad);
		if(!nuevo_integrante)
			return ERROR;
		lista_insertar(lista_integrantes, nuevo_integrante);
		(*leido) = leer_letra(archivo, letra);
	}	
	return EXITO;
}

/*
Lee y crea casas, y las agrega al arbol.
Requiere que exista memoria disponible en el sistema.
*/
int leer_y_agregar_casas(abb_t* arbol_casas, FILE* archivo){
	char letra;
	casa_t casa;
	int leido = leer_letra(archivo, &letra);
	if(leido != 1){
		printf("El archivo ingresado no contiene datos en el formato adecuado\n");
		return ERROR_ARCHIVO;
	}

	while(letra == CASA && leido > 0){
		leido = leer_casa(archivo, &casa);
		if(leido != 3)
			return ERROR;
		casa_t* nueva_casa = casa_crear(casa.nombre, casa.factor_envejecimiento, casa.factor_nacimiento);
		if(!nueva_casa)
			return ERROR;
		agregar_integrantes_de_archivo(archivo, nueva_casa->integrantes, &letra, &leido);
		arbol_insertar(arbol_casas, nueva_casa);
	}
	return EXITO;
}

/*
Devuelve true si la primera casa tiene mayor cantidad de integrantes que la segunda casa.
*/
bool es_mayor(void* casa_1, void* casa_2){
	return lista_elementos(((casa_t*)casa_1)->integrantes) > lista_elementos(((casa_t*)casa_2)->integrantes);
}

/*
Muestra por pantalla el nombre y la cantidad de integrantes de la casa.
*/
bool mostrar_nombre_e_integrantes(void* casa, void* extra){
	if(casa){
		printf("La casa %s tiene: %i integrante/s.\n", ((casa_t*)casa)->nombre, (int)lista_elementos(((casa_t*)casa)->integrantes));
	}
	return false;
}

/*
Aumenta la edad de casa integrante de la casa segun lo que indique el factor
de envejecimiento de la misma.
Necesita que exista memoria disponible en el sistema.
*/
bool aumentar_edad(void* casa, void* extra){
    if(casa){
    	if(((casa_t*)casa)->factor_envejecimiento != 0){
	    	lista_iterador_t* iterador = lista_iterador_crear(((casa_t*)casa)->integrantes);
			while(lista_iterador_tiene_siguiente(iterador)){
				integrante_t* integrante = lista_iterador_siguiente(iterador);
				integrante->edad += ((casa_t*)casa)->factor_envejecimiento;
			}
			lista_iterador_destruir(iterador);
		}
    }
  	return false;   
}

/*
Elimina los integrantes de la casa que tienen una edad mayor
o igual a la esperanza de vida indicada.
Requiere que exista memoria disponible en el sistema. 
*/
bool eliminar_integrantes_mayores(void* casa, void* extra){
	if(casa){
    	lista_iterador_t* iterador = lista_iterador_crear(((casa_t*)casa)->integrantes);
    	size_t i = 0;
		while(lista_iterador_tiene_siguiente(iterador)){
			integrante_t* integrante = lista_iterador_siguiente(iterador);
			if((int)integrante->edad >= ESPERANZA_DE_VIDA){
				free(integrante);
				lista_borrar_de_posicion(((casa_t*)casa)->integrantes, i);
				lista_iterador_destruir(iterador);
				iterador = lista_iterador_crear(((casa_t*)casa)->integrantes);
				i = 0;
			} else
				i++;
		}
		lista_iterador_destruir(iterador);
	}
	return false;
}

/*
Agrega nuevos integrantes a la casa.
En caso de no poder crear un integrante retorna true, sino false.
*/
bool nacimientos(void* casa, void* extra){
	if(casa){
		if(((casa_t*)casa)->factor_nacimiento != 0){
			size_t nuevos_hijos = lista_elementos(((casa_t*)casa)->integrantes) / ((casa_t*)casa)->factor_nacimiento;
			for(int i = 0; i < nuevos_hijos; i++){
				char nombre[MAX_NOMBRE_PERSONA];
				int leido = leer_nombre(extra, nombre);
				if(leido != 1)
					return ERROR;
				integrante_t* integrante = integrante_crear(nombre, 0);
				if(!integrante)
					return true;
				lista_insertar(((casa_t*)casa)->integrantes, integrante);
			} 
		}
	}
	return false;
}

/*
Devuelve la posicion de la casa con mayor cantidad de integrantes.
*/
int buscar_casa_ganadora(casa_t* array[], int tope){
	int cantidad_maxima = (int)lista_elementos(array[0]->integrantes);
	int indice_casa_ganadora = 0;
	for(int j = 1; j < tope; j++){
		if(lista_elementos(array[j]->integrantes) > cantidad_maxima){
			cantidad_maxima = (int)lista_elementos(array[j]->integrantes);
			indice_casa_ganadora = j;
		}
	}
	return indice_casa_ganadora;
}

/*
Pide una cantidad de años y simula esa cantidad ingresada
Por cada año, recorre todas las casas y: Aumenta la edad de
todos sus integrantes segun indique el factor de envejecimiento de la casa,
elimina los integrantes mayores de edas, encola y elimina del arbol las casas 
que no tienen integrantes, y muestra por pantalla las casas y su cantidad de integrantes.
Se requiere un archivo con nombres, en caso de no podes abrirlo retorna -1.
*/
int simulacion(reino_t* reino){
	if(!arbol_vacio(reino->arbol_casas)){
		printf("Cantidad de años a simular: ");
		int cantidad_de_anios = 0;
		scanf(" %i", &cantidad_de_anios);

		FILE* nombres = fopen(ARCHIVO_NOMBRES, LECTURA);
		if(!nombres)
			return ERROR;
		
		for(int i = 0; i < cantidad_de_anios; i++){
			printf("---INICIO AÑO %i---\n", i+1);

			void* extra = NULL;
			//RECORRE TODAS LAS CASA, AGREGA A LA EDAD DE CADA INTEGRANTE LOS AÑOS QUE INDIQUE EL FACTOR DE ENVEJECIMIENTO DE LA CASA
			abb_con_cada_elemento(reino->arbol_casas, ABB_RECORRER_INORDEN, aumentar_edad, extra);
			//RECORRE TODAS LAS CASAS, ELIMINA A LOS INTEGRANTES MAYORES DE EDAD 
			abb_con_cada_elemento(reino->arbol_casas, ABB_RECORRER_INORDEN, eliminar_integrantes_mayores, extra);
			
			//RECORRE TODAS LAS CASAS, SI ALGUNA ESTÁ VACIA, LA ENCOLA EN LA COLA DE CASAS EXTINTAS Y LA ELIMINA DEL ARBOL	
			casa_t* array_de_casas[CANTIDAD_MAXIMA_CASAS];
			int tope = arbol_recorrido_inorden(reino->arbol_casas, (void*)array_de_casas, CANTIDAD_MAXIMA_CASAS);

			for(int i = 0; i < tope; i++){
				if(lista_elementos(array_de_casas[i]->integrantes) == 0){
					cola_encolar(reino->casas_extintas, arbol_buscar(reino->arbol_casas, array_de_casas[i]->nombre));
					arbol_borrar(reino->arbol_casas, array_de_casas[i]->nombre);
				}
			}

			//RECORRE TODAS LAS CASAS, AGREGA NUEVOS INTEGRANTES SEGUN LA REGLA: Cantidad a nacer = cantidad de integrantes / factor de nacimiento
			abb_con_cada_elemento(reino->arbol_casas, ABB_RECORRER_INORDEN, nacimientos, nombres);

			//RECORRE TODAS LAS CASAS, MUESTRA POR PANTALLA EL NOMBRE Y LA CANTIDAD DE INTEGRANTES DE CADA UNA
			abb_con_cada_elemento(reino->arbol_casas, ABB_RECORRER_INORDEN, mostrar_nombre_e_integrantes, extra);
			printf("Cantidad de casas extintas: %i\n", cola_cantidad(reino->casas_extintas));

			printf("---FIN AÑO %i---\n\n", i+1);
		}

		fclose(nombres);

		casa_t* array_de_casas[CANTIDAD_MAXIMA_CASAS];
		int tope = arbol_recorrido_inorden(reino->arbol_casas, (void*)array_de_casas, CANTIDAD_MAXIMA_CASAS);
		if(tope == 0){
			printf("No sobrevivió ninguna casa \n");
		} else {
			int pos_ganadora = buscar_casa_ganadora(array_de_casas, tope);
			printf("La casa que domina el Trono de Hierro despues de %i años es: ¡La casa %s!, con %i integrantes\n",
			cantidad_de_anios, array_de_casas[pos_ganadora]->nombre, (int)lista_elementos(array_de_casas[pos_ganadora]->integrantes));
		}
	} else 
		printf("No existen casas\n");

	return EXITO;	
}

/*
Retorna la posicion en el array donde se encuentra la casa con el nombre recibido o
-1 si no la encuentra.
*/
int buscar_posicion_casa(casa_t* array[], int tope, char* nombre_casa_buscada){
	int i = 0;
	bool es_repetida = false;
	while(i < tope && !es_repetida){
		if(strcmp(array[i]->nombre, nombre_casa_buscada) == 0){
			es_repetida = true;
		} else 
			i++;
	}

	if(es_repetida)
		return i;
	else 
		return -1;
}

/*
Pide el usuario el nombre de un archivo que contenga una casa y si este archivo existe agrega la casa.
Si la casa ya fue ingresada, agrega los integrantes. Si no fue ingresada, crea la casa.
Requiere que exista memoria disponible en el sistema. 
*/
int agregar_casa(abb_t* arbol_casas){
	printf("Nombre del archivo donde se encuentra la casa: ");
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	scanf(" %s", nombre_archivo);

	FILE* nuevo_archivo_casa = fopen(nombre_archivo, LECTURA);
	if(!nuevo_archivo_casa){
		printf("No se pudo encontrar un archivo con tal nombre\n");
		return ERROR_ARCHIVO;
	}

	casa_t casa;
	char letra;
	int leido = leer_letra(nuevo_archivo_casa, &letra);
	if(letra != CASA || leido != 1)
		return ERROR;
	
	leido = leer_casa(nuevo_archivo_casa, &casa);
	if(leido != 3)
		return ERROR;

	casa_t* array_de_casas[CANTIDAD_MAXIMA_CASAS];
	int tope = arbol_recorrido_inorden(arbol_casas, (void*)array_de_casas, CANTIDAD_MAXIMA_CASAS);
	int pos_casa = buscar_posicion_casa(array_de_casas, tope, casa.nombre);

	if(pos_casa != -1){
		agregar_integrantes_de_archivo(nuevo_archivo_casa, array_de_casas[pos_casa]->integrantes, &letra, &leido);
	} else {
		casa_t* nueva_casa = casa_crear(casa.nombre, casa.factor_envejecimiento, casa.factor_nacimiento);
		if(!nueva_casa)
			return ERROR;
		agregar_integrantes_de_archivo(nuevo_archivo_casa, nueva_casa->integrantes, &letra, &leido);
		arbol_insertar(arbol_casas, nueva_casa);
	}

	printf("La casa del archivo %s se ha agregado correctamente\n", nombre_archivo);
	fclose(nuevo_archivo_casa);
	return EXITO;
}

void merge(casa_t** vector, int inicio1, int fin1, int fin2, bool (*es_mayor)(void*, void*)){
	int inicio2 = fin1+1;
	while(inicio1 <= fin1 && inicio2 <= fin2){
		if(es_mayor(vector[inicio1], vector[inicio2])){
			inicio1++;
		} else {
			casa_t* aux = vector[inicio2];
			for(int i = inicio2; i > inicio1; i--){
				vector[i] = vector[i-1];
			}
			vector[inicio1] = aux;
			inicio1++;
			inicio2++;
			fin1++;
		}
	}
}

/*
Ordena el vector de casas de mayor a menor según cantidad de integrantes.
*/
void merge_sort(casa_t** vector, int inicio, int fin, bool (*es_mayor)(void*, void*)){
	if(inicio == fin)
		return;
	int medio = (fin+inicio)/2;
	merge_sort(vector, inicio, medio, es_mayor);
	merge_sort(vector, medio+1, fin, es_mayor);
	merge(vector, inicio, medio, fin, es_mayor);
}

void ordenar_por_cantidad_integrantes(casa_t** array, int tope){
	merge_sort(array, 0, tope-1, es_mayor);
}

/*
Muestra todas las casas y los integrantes de cada una.
Necesita que exista memoria disponible en el sistema.
*/
int mostrar_integrantes_por_casa(casa_t** array, int tope){
	for(int i = 0; i < tope; i++){
		printf("\nCASA %s:\n", array[i]->nombre);
		printf("INTEGRANTES: \n");
		lista_iterador_t* iterador = lista_iterador_crear(array[i]->integrantes);
		if(!iterador)
			return ERROR;
		while(lista_iterador_tiene_siguiente(iterador)){
			integrante_t* integrante_actual = lista_iterador_siguiente(iterador);
			printf("%s\n", integrante_actual->nombre);
		}
		lista_iterador_destruir(iterador);
	}
	return EXITO;
}

/*
Ordena el vector de casas por cantidad de integrantes y lo muestra.
Necesita que exista memoria disponible en el sistema.
*/
int mostrar_integrantes(abb_t* arbol_casas){
	casa_t* array_de_casas[CANTIDAD_MAXIMA_CASAS];
	int tope = arbol_recorrido_inorden(arbol_casas, (void*)array_de_casas, CANTIDAD_MAXIMA_CASAS);
	if(tope != 0){
		ordenar_por_cantidad_integrantes(array_de_casas, tope);
		return mostrar_integrantes_por_casa(array_de_casas, tope);
	} else {
		printf("No existen casas\n");
		return EXITO;
	}
}

/*
Intercambia las colas.
*/
void swap(cola_t* cola_1, cola_t* cola_2){
	cola_t aux = *cola_1;
	*cola_1 = *cola_2;
	*cola_2 = aux; 
}

/*
Muestras las casas extintas en el orden en el que se extinguieron.
Necesita que exista memoria disponible en el sistema.
*/
int mostrar_casas_extintas(cola_t* casas_extintas){
	if(cola_vacia(casas_extintas)){
		printf("No hay casas extintas\n");
		return EXITO;
	}

	cola_t* cola_aux = cola_crear();
	if(!cola_aux)
		return ERROR;

	printf("CASAS EXTINTAS: \n");
	while(!cola_vacia(casas_extintas)){
		casa_t* casa = cola_primero(casas_extintas);
		printf("%s\n", casa->nombre);
		cola_encolar(cola_aux, casa);
		cola_desencolar(casas_extintas);
	}

	swap(casas_extintas, cola_aux);
	cola_destruir(cola_aux);
	return EXITO;
}

/*
Destruye la casa, liberando toda la memoria de los integrantes y de si misma.
*/
bool destructor_de_casas(void* casa, void* extra){
	if(casa){
		while(!lista_vacia(((casa_t*)casa)->integrantes)){
			integrante_t* integrante = lista_elemento_en_posicion(((casa_t*)casa)->integrantes, 0);
			free(integrante);
			lista_borrar_de_posicion(((casa_t*)casa)->integrantes, 0);
		}
		lista_destruir(((casa_t*)casa)->integrantes);
		free(casa);
	}
	return false;
}

/*
LIbera la memoria de la cola y de las casas almacenadas en ella.
*/
void destruir_cola_de_casas(cola_t* cola){
	void* extra = NULL;
	while(!cola_vacia(cola)){
		casa_t* casa_actual = cola_primero(cola);
		destructor_de_casas(casa_actual, extra);
		cola_desencolar(cola);
	}
	cola_destruir(cola);
}

/*
Libera la memoria del arbol y de las casas almacenadas en el.
*/
void destruir_arbol_de_casas(abb_t* arbol){
	void* extra = NULL;
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, destructor_de_casas, extra);
	arbol_destruir(arbol);
}

/*
Destruye el reino, liberando toda la memoria de los integrantes y las casas.
*/
void destruir_reino(reino_t* reino){
	if(reino){
		destruir_arbol_de_casas(reino->arbol_casas);
		destruir_cola_de_casas(reino->casas_extintas);
		free(reino);
	}
}