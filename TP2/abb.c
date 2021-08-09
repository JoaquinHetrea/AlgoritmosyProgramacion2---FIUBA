#include "abb.h"
#define EXITO 0
#define ERROR -1
/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) 
		return NULL;
	abb->nodo_raiz = NULL;
	abb->comparador = comparador;
	abb->destructor = destructor;
	return abb;
}

nodo_abb_t* crear_nodo(){
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	if(!nodo) return NULL;
	nodo->elemento = NULL;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	return nodo;
}

bool tiene_hijo_izquierdo(nodo_abb_t* subarbol){
	return subarbol->izquierda != NULL;
}

bool tiene_hijo_derecho(nodo_abb_t* subarbol){
	return subarbol->derecha != NULL;
}

void arbol_insertar_auxiliar(nodo_abb_t* subarbol, abb_comparador comparador, void* elemento){
	if(!subarbol) return;
	if(((comparador)(subarbol->elemento, elemento) <= 0)){
		if(!tiene_hijo_derecho(subarbol)) {
			nodo_abb_t* nodo_nuevo = crear_nodo();
			if(!nodo_nuevo) return;
			subarbol->derecha = nodo_nuevo;
			nodo_nuevo->elemento = elemento;
		} else {
			arbol_insertar_auxiliar(subarbol->derecha, comparador, elemento);
		}
	} else if((comparador)(subarbol->elemento, elemento) > 0){
		if(!tiene_hijo_izquierdo(subarbol)){
			nodo_abb_t* nodo_nuevo = crear_nodo();
			if(!nodo_nuevo) return;
			subarbol->izquierda = nodo_nuevo;
			nodo_nuevo->elemento = elemento;
		}
		else {
			arbol_insertar_auxiliar(subarbol->izquierda, comparador, elemento);
		}
	}
}

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
 int arbol_insertar(abb_t* arbol, void* elemento){
 	if(!arbol)
 		return -1;
 	if(!arbol->nodo_raiz){
 		nodo_abb_t* nodo_nuevo = crear_nodo();
		if(!nodo_nuevo) return -1;
		arbol->nodo_raiz = nodo_nuevo;
		nodo_nuevo->elemento = elemento;
 	} else {
 		arbol_insertar_auxiliar(arbol->nodo_raiz, arbol->comparador, elemento);
 	}
	return 0;
 }

 nodo_abb_t* arbol_buscar_mayor_de_los_menores(nodo_abb_t* subarbol){
	if(!subarbol) return NULL;
	if(!tiene_hijo_derecho(subarbol)){
		return subarbol;
	} else {
		nodo_abb_t* nodo_mayor = subarbol;
		while(tiene_hijo_derecho(nodo_mayor->derecha)){
			nodo_mayor = nodo_mayor->derecha;
		}
		nodo_abb_t* nodo_aux = nodo_mayor->derecha;
		nodo_mayor->derecha = NULL;
		return nodo_aux;
	}
}

nodo_abb_t* arbol_buscar_menor(nodo_abb_t* subarbol){
	if(!subarbol) return NULL;
	if(!tiene_hijo_izquierdo(subarbol)){
		return subarbol;
	} else {
		nodo_abb_t* nodo_menor = subarbol->izquierda;
		while(tiene_hijo_izquierdo(nodo_menor)){
			nodo_menor = nodo_menor->izquierda;
		}
		return nodo_menor;
	}
}

void* borrar_nodo_sin_hijos(nodo_abb_t* subarbol, abb_liberar_elemento destructor){
	if(destructor)
		destructor(subarbol->elemento);
	free(subarbol);
	return NULL;
}

void* borrar_nodo_con_un_hijo(nodo_abb_t* subarbol, nodo_abb_t* hijo, abb_liberar_elemento destructor){
	if(destructor)
		destructor(subarbol->elemento);
	free(subarbol);
	return hijo;
}

void* borrar_nodo_con_dos_hijos(nodo_abb_t* subarbol, abb_liberar_elemento destructor, abb_comparador comparador){
	nodo_abb_t* mayor_de_los_menores = arbol_buscar_mayor_de_los_menores(subarbol->izquierda);
	if(destructor)
		destructor(subarbol->elemento);
	subarbol->elemento = mayor_de_los_menores->elemento;
	if(!tiene_hijo_izquierdo(mayor_de_los_menores)){
		if(comparador(subarbol->izquierda->elemento, mayor_de_los_menores->elemento) == 0)
			subarbol->izquierda = NULL;
	} else {
		if(comparador(subarbol->izquierda->elemento, mayor_de_los_menores->elemento) != 0){
			nodo_abb_t* menor_del_mayor = arbol_buscar_menor(mayor_de_los_menores->izquierda);
			menor_del_mayor->izquierda = subarbol->izquierda;
		} 
		subarbol->izquierda = mayor_de_los_menores->izquierda;
	}
	free(mayor_de_los_menores);
	return subarbol;
}

nodo_abb_t* arbol_borrar_auxiliar(nodo_abb_t* subarbol, abb_comparador comparador, abb_liberar_elemento destructor, void* elemento, bool* pudo_eliminar){
	if(!subarbol){
		(*pudo_eliminar) = false;
		return NULL;
	}
	if((comparador)(subarbol->elemento, elemento) == 0){
		if(!tiene_hijo_izquierdo(subarbol) && !tiene_hijo_derecho(subarbol)){
			return borrar_nodo_sin_hijos(subarbol, destructor);
		} else if(tiene_hijo_izquierdo(subarbol) && !tiene_hijo_derecho(subarbol)){
			return borrar_nodo_con_un_hijo(subarbol, subarbol->izquierda, destructor);
		} else if(!tiene_hijo_izquierdo(subarbol) && tiene_hijo_derecho(subarbol)){
			return borrar_nodo_con_un_hijo(subarbol, subarbol->derecha, destructor);
		} else {
			return borrar_nodo_con_dos_hijos(subarbol, destructor, comparador);
		}
	} else if((comparador)(subarbol->elemento, elemento) > 0){
		subarbol->izquierda = arbol_borrar_auxiliar(subarbol->izquierda, comparador, destructor, elemento, pudo_eliminar); 
		return subarbol;
	} else {
		subarbol->derecha = arbol_borrar_auxiliar(subarbol->derecha, comparador, destructor, elemento, pudo_eliminar);
		return subarbol;
	}
}
/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.  
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol) return ERROR;
	bool pudo_eliminar = true;
	arbol->nodo_raiz = arbol_borrar_auxiliar(arbol->nodo_raiz, arbol->comparador, arbol->destructor, elemento, &pudo_eliminar);
	if(pudo_eliminar)
		return EXITO;
	return ERROR;

}

void* arbol_buscar_auxiliar(nodo_abb_t* subarbol, abb_comparador comparador, void* elemento){
	if(!subarbol) return NULL;
	if(comparador(subarbol->elemento, elemento) == 0){
		return subarbol->elemento;
	} else if(comparador(subarbol->elemento, elemento) > 0){
		return arbol_buscar_auxiliar(subarbol->izquierda, comparador, elemento);
	} else return arbol_buscar_auxiliar(subarbol->derecha, comparador, elemento);
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 * 
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol) return NULL;
	return arbol_buscar_auxiliar(arbol->nodo_raiz, arbol->comparador, elemento);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío.
 */
void* arbol_raiz(abb_t* arbol){
	if(!arbol) return NULL;
	if(!arbol->nodo_raiz) return NULL;
	return arbol->nodo_raiz->elemento;
}

/*
 * Determina si el árbol está vacío. 
 * Devuelve true si lo está, false en caso contrario.
 */
bool arbol_vacio(abb_t* arbol){
	if(!arbol) return true;
	return arbol->nodo_raiz == NULL;
}

void recorrido_inorden_auxiliar(nodo_abb_t* subarbol, void** array, int tamanio_array, int* cantidad_almacenada){
	if(!subarbol) return;
	recorrido_inorden_auxiliar(subarbol->izquierda, array, tamanio_array, cantidad_almacenada);
	if(tamanio_array <= (*cantidad_almacenada)) return;
	else {
		*(array + *cantidad_almacenada) = subarbol->elemento;
		(*cantidad_almacenada)++;
	}
	recorrido_inorden_auxiliar(subarbol->derecha, array, tamanio_array, cantidad_almacenada);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol) return 0;
	int cantidad_almacenada = 0;
	recorrido_inorden_auxiliar(arbol->nodo_raiz, array, tamanio_array, &cantidad_almacenada);
	return cantidad_almacenada;
}

void recorrido_preorden_auxiliar(nodo_abb_t* subarbol, void** array, int tamanio_array, int* cantidad_almacenada){
	if(!subarbol) return;
	if(tamanio_array <= (*cantidad_almacenada)) return;
	else {
		*(array + *cantidad_almacenada) = subarbol->elemento;
		(*cantidad_almacenada)++;
	}
	recorrido_preorden_auxiliar(subarbol->izquierda, array, tamanio_array, cantidad_almacenada);
	recorrido_preorden_auxiliar(subarbol->derecha, array, tamanio_array, cantidad_almacenada);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol) return 0;
	int cantidad_almacenada = 0;
	recorrido_preorden_auxiliar(arbol->nodo_raiz, array, tamanio_array, &cantidad_almacenada);
	return cantidad_almacenada;	
}

void recorrido_postorden_auxiliar(nodo_abb_t* subarbol, void** array, int tamanio_array, int* cantidad_almacenada){
	if(!subarbol) return;
	recorrido_postorden_auxiliar(subarbol->izquierda, array, tamanio_array, cantidad_almacenada);
	recorrido_postorden_auxiliar(subarbol->derecha, array, tamanio_array, cantidad_almacenada);
	if(tamanio_array <= (*cantidad_almacenada)) return;
	else {
		*(array + *cantidad_almacenada) = subarbol->elemento;
		(*cantidad_almacenada)++;
	}
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol) return 0;
	int cantidad_almacenada = 0;
	recorrido_postorden_auxiliar(arbol->nodo_raiz, array, tamanio_array, &cantidad_almacenada);
	return cantidad_almacenada;	
}

void arbol_destruir_auxiliar(nodo_abb_t* subarbol, abb_liberar_elemento destructor){
	if(subarbol){
		arbol_destruir_auxiliar(subarbol->izquierda, destructor);
		arbol_destruir_auxiliar(subarbol->derecha, destructor);
		if(destructor)
			destructor(subarbol->elemento);
		free(subarbol);
	}
}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
	if(arbol){
		arbol_destruir_auxiliar(arbol->nodo_raiz, arbol->destructor);
		free(arbol);
	}
}

bool recorrido_postorden_con_funcion(nodo_abb_t* subarbol, bool (*funcion)(void*, void*), void* extra){
	if(!subarbol) return false;
	if(!recorrido_postorden_con_funcion(subarbol->izquierda, funcion, extra))
		if(!recorrido_postorden_con_funcion(subarbol->derecha, funcion, extra))
			return funcion(subarbol->elemento, extra);
	return true;
}

bool recorrido_preorden_con_funcion(nodo_abb_t* subarbol, bool (*funcion)(void*, void*), void* extra){
	if(!subarbol) return false;
	if(!funcion(subarbol->elemento, extra))
		if(!recorrido_preorden_con_funcion(subarbol->izquierda, funcion, extra))
			return recorrido_preorden_con_funcion(subarbol->derecha, funcion, extra);
	return true;
}

bool recorrido_inorden_con_funcion(nodo_abb_t* subarbol, bool (*funcion)(void*, void*), void* extra){
	if(!subarbol) return false;
	if(!recorrido_inorden_con_funcion(subarbol->izquierda, funcion, extra))
		if(!funcion(subarbol->elemento, extra))
			return recorrido_inorden_con_funcion(subarbol->derecha, funcion, extra);
	return true;
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el 
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol){
		switch(recorrido){
			case ABB_RECORRER_INORDEN:
				recorrido_inorden_con_funcion(arbol->nodo_raiz, funcion, extra);
			break;
			case ABB_RECORRER_PREORDEN:
				recorrido_preorden_con_funcion(arbol->nodo_raiz, funcion, extra);
			break;
			case ABB_RECORRER_POSTORDEN:
				recorrido_postorden_con_funcion(arbol->nodo_raiz, funcion, extra);
			break;
		}
	}
}
