#include "lista.h"
#include <stdio.h>

void DadaUnaListaNoVacia_CuandoSePideElElementoDeLaPosicion0_EntoncesDevuelveElPrimerElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	lista_insertar(lista, &elemento_1);
	lista_insertar(lista, &elemento_2);
	lista_insertar(lista, &elemento_3);
	lista_insertar(lista, &elemento_4);
	lista_insertar(lista, &elemento_5);

	//Actuar

	//Verificar
	if(*(int*)lista_elemento_en_posicion(lista, 0) == elemento_1){
		printf("TEST PASADO: 'Lista devuelve el primer elemento al pedir el elemento de la posicion 0'\n");
	} else printf("TEST NO PASADO: 'Lista devuelve el primer elemento al pedir el elemento de la posicion 0'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon5Elementos_CuandoSePideElElementoDeLaUltimaPosicion_EntoncesDevuelveElQuintoElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	lista_insertar(lista, &elemento_1);
	lista_insertar(lista, &elemento_2);
	lista_insertar(lista, &elemento_3);
	lista_insertar(lista, &elemento_4);
	lista_insertar(lista, &elemento_5);

	//Actuar

	//Verificar
	if(*(int*)lista_ultimo(lista) == elemento_5){
		printf("TEST PASADO: 'Lista devuelve el ultimo elemento al pedir el elemento de la ultima posicion'\n");
	} else printf("TEST NO PASADO: 'Lista devuelve el ultimo elemento al pedir el elemento de la ultima posicion'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon1000Elementos_CuandoSeBorran1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 200; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar
	for(int i = 0; i < 1000; i++){
		lista_borrar(lista);
	}

	//Verificar
	if(lista_vacia(lista)){
		printf("TEST PASADO: 'Lista inserta y borra correctamente' \n");
	} else printf("TEST NO PASADO: 'Lista inserta y borra correctamente'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon1000Elementos_CuandoSeBorran500ElementosYSePideLaCantidad_EntoncesDevuelve500(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 200; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar
	for(int i = 0; i < 500; i++){
		lista_borrar(lista);
	}

	//Verificar
	if(lista_elementos(lista) == 500){
		printf("TEST PASADO: 'Lista devuelve la cantidad correcta de elementos luego de insertar y borrar multiples veces'\n");
	} else printf("TEST NO PASADO: 'Lista devuelve la cantidad correcta de elementos luego de insertar y borrar multiples veces'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	//Actuar

	//Verificar
	if(lista_vacia(lista)){
		printf("TEST PASADO: 'Lista vacia devuelve true al preguntar si está vacia'\n");
	} else printf("TEST NO PASADO: 'Lista vacia devuelve true al preguntar si está vacia'\n");
	lista_destruir(lista);
}

void DadaUnaListaConElementos_CuandoSePideUnElementoDeUnaPosicionInexistente_EntoncesDevuelveNull(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 10; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar

	//Verificar
	if(!lista_elemento_en_posicion(lista, 100)){
		printf("TEST PASADO: 'Pedir elemento de una posicion inexistente devuelve null'\n");
	} else printf("TEST NO PASADO: 'Pedir elemento de una posicion inexistente devuelve null'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon5Elementos_CuandoSePideBorrarUnElementoDeUnaPosicionInexistente_EntoncesBorraElUltimoElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	lista_insertar(lista, &elemento_1);
	lista_insertar(lista, &elemento_2);
	lista_insertar(lista, &elemento_3);
	lista_insertar(lista, &elemento_4);
	lista_insertar(lista, &elemento_5);

	//Actuar
	lista_borrar_de_posicion(lista, 100);
	void* elemento_en_ultima_pos = lista_ultimo(lista);

	//Verificar
	if(*(int*)elemento_en_ultima_pos == elemento_4){
		printf("TEST PASADO: 'Pedir borrar de una posición inexistente borra la ultima posición'\n");
	} else printf("TEST NO PASADO: 'Pedir borrar de una posición inexistente borra la ultima posición'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSeIntentaEncolarElElementoNull_EntoncesDevuelveExito(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	void* elemento_null = NULL;

	//Actuar

	//Verificar
	if(!lista_insertar(lista, elemento_null)){
		printf("TEST PASADO: 'Insertar el elemento Null'\n");
	} else printf("TEST NO PASADO: 'Insertar el elemento Null'\n");
	lista_destruir(lista);
}

void DadaUnaListaNoVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveFalse(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	char elemento_a = 'A';
	char elemento_b = 'B';
	char elemento_c = 'C';
	lista_insertar(lista, &elemento_a);
	lista_insertar(lista, &elemento_b);
	lista_insertar(lista, &elemento_c);

	//Actuar

	//Verificar
	if(!lista_vacia(lista)){
		printf("TEST PASADO: 'Lista no vacia devuelve false al preguntar si está vacia'\n");
	} else printf("TEST NO PASADO: 'Lista no vacia devuelve false al preguntar si está vacia'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSePideElElementoDeUnaPosicion_EntoncesDevuelveNull(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	//Actuar 

	//Verificar
	if(!lista_ultimo(lista)){
		printf("TEST PASADO: 'Lista vacia devuelve NULL al pedir elemento en la posicion 0'\n");
	} else printf("TEST NO PASADO: 'Lista vacia devuelve NULL al pedir elemento en la posicion 0'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSeIntentaBorrar_EntoncesDevuelveError(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	//Actuar
	bool pudo_borrar = !lista_borrar(lista);
	//Borrar
	if(!pudo_borrar){
		printf("TEST PASADO: 'No se puede borrar de una lista vacia'\n");
	} else printf("TEST NO PASADO: 'No se puede borrar de una lista vacia'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CUandoSeIntentaBorrarDeUnaPosicion_EntoncesDevuelveError(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	//Actuar
	bool pudo_borrar = !lista_borrar_de_posicion(lista, 100);

	//Borrar
	if(!pudo_borrar){
		printf("TEST PASADO: 'No se puede borrar de una lista vacia'\n");
	} else printf("TEST NO PASADO: 'No se puede borrar de una lista vacia'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSeInsertanElementosEnDistintasPosiciones_EntoncesLosElementosSeInsertanEnLasPosicionesIndicadas(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;

	//Actuar
	lista_insertar_en_posicion(lista, &elemento_3, 3);
	lista_insertar_en_posicion(lista, &elemento_5, 1);
	lista_insertar_en_posicion(lista, &elemento_1, 0);
	lista_insertar_en_posicion(lista, &elemento_4, 2);
	lista_insertar_en_posicion(lista, &elemento_2, 1);

	//Verificar
	bool estan_en_orden = true;
	for(size_t i = 0; i < 4; i++){
		if(*(int*)lista_elemento_en_posicion(lista, i) > *(int*)lista_elemento_en_posicion(lista, i+1))
			estan_en_orden = false;
	}

	if(estan_en_orden){
		printf("TEST PASADO: 'La lista inserta correctamente en la posicion indicada'\n");
	} else printf("TEST NO PASADO: 'La lista inserta correctamente en la posicion indicada'\n");
	lista_destruir(lista);
}

void DadaUnaListaNoVacia_CuandoSeIntentaInsertarEnUnaPosicionInexistente_EntoncesInsertaEnLaUltimaPosicion(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 10; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar
	int elemento_6 = 6;
	lista_insertar_en_posicion(lista, &elemento_6, 1000);

	//Verificar
	if(*(int*)lista_ultimo(lista) == elemento_6){
		printf("TEST PASADO: 'Lista inserta en ultima posicion si la posicion indicada no existe'\n");
	} else printf("TEST NO PASADO: 'Lista inserta en ultima posicion si la posicion indicada no existe'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon5Elementos_CuandoSeBorraElElementoDeLaPosicion2_EntoncesSeBorraElTercerElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	lista_insertar(lista, &elemento_1);
	lista_insertar(lista, &elemento_2);
	lista_insertar(lista, &elemento_3);
	lista_insertar(lista, &elemento_4);
	lista_insertar(lista, &elemento_5);

	//Actuar
	lista_borrar_de_posicion(lista, 2);

	//Verificar
	if(*(int*)lista_elemento_en_posicion(lista, 2) == elemento_4){
		printf("TEST PASADO: 'La lista borra en la posicion indicada correctamente'\n");
	} else printf("TEST NO PASADO: 'La lista borra en la posicion indicada correctamente'\n");
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSePideElUltimoElemento_EntoncesDevuelveNull(){
	//Organizar
	lista_t* lista = lista_crear();

	//Actuar

	//Verificar
	if(!lista_ultimo(lista)){
		printf("TEST PASADO: 'Lista Vacia devuelve Null al pedir el ultimo elemento'\n");
	} else printf("TEST NO PASADO: 'Lista Vacia devuelve Null al pedir el ultimo elemento'\n");
	lista_destruir(lista);
}

void DadaUnaListaCon5Elementos_CuandoBorroLaPosicion4YPidoElUltimoElemento_EntoncesDevuelveElCuartoElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	lista_insertar(lista, &elemento_1);
	lista_insertar(lista, &elemento_2);
	lista_insertar(lista, &elemento_3);
	lista_insertar(lista, &elemento_4);
	lista_insertar(lista, &elemento_5);

	//Actuar
	lista_borrar_de_posicion(lista, 4);

	//Verificar
	if(*(int*)lista_ultimo(lista) == elemento_4){
		printf("TEST PASADO: 'Lista devuelve el correctamente el ultimo elemento luego de borrar el elemento de la última posición'\n");
	} else printf("TEST NO PASADO: 'Lista devuelve el correctamente el ultimo elemento luego de borrar el elemento de la última posición'\n");
	lista_destruir(lista);
}

void DadaUnaListaNoVacia_CuandoSeIntentaInsertarEnLaPosicion0_EntoncesSeIncertaEnLaPosicionInicial(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	char elemento_a = 'A';
	char elemento_b = 'B';
	char elemento_c = 'C';
	lista_insertar(lista, &elemento_a);
	lista_insertar(lista, &elemento_b);
	lista_insertar(lista, &elemento_c);

	//Actuar
	char elemento_d = 'D';
	lista_insertar_en_posicion(lista, &elemento_d, 0);

	//Verificar
	if(*(char*)lista_elemento_en_posicion(lista, 0) == elemento_d){
		printf("TEST PASADO: 'Lista inserta correctamente en la posicion inicial'\n");
	} else printf("TEST NO PASADO: 'Lista inserta correctamente en la posicion inicial'\n");
	lista_destruir(lista);
}

void DadaUnaListaConElementos_CuandoSeBorraLosElementoYSePreguntaSiEstaVacia_EntoncesDevuelveTrue(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 20; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar
	for(int i = 0; i < 100; i++){
		lista_borrar(lista);
	}

	//Verificar
	if(lista_vacia(lista)){
		printf("TEST PASADO: 'La lista borra todos los elementos correctamente'\n");
	} else printf("TEST NO PASADO: 'La lista borra todos los elementos correctamente'\n");
	lista_destruir(lista);
}

void DadaUnaListaNoVacia_CuandoSeCreaUnIteradorYSeLePreguntaSiTieneSiguiente_EntoncesDevuelveTrue(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	char elemento_a = 'A';
	char elemento_b = 'B';
	char elemento_c = 'C';
	lista_insertar(lista, &elemento_a);
	lista_insertar(lista, &elemento_b);
	lista_insertar(lista, &elemento_c);

	//Actuar
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(!iterador) return;

	//Verificar
	if(lista_iterador_tiene_siguiente(iterador)){
		printf("TEST PASADO: 'Iterador al inicio de una lista con multiples elementos tiene siguiente'\n");
	} else printf("TEST NO PASADO: 'Iterador al inicio de una lista con multiples elementos tiene siguiente'\n");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void DadaUnaListaVacia_CuandoSeCreaUnIteradorYSePideElSiguiente_EntoncesDevuelveNull(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;

	//Actuar
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(!iterador) return;

	//Verificar
	if(!lista_iterador_siguiente(iterador)){
		printf("TEST PASADO: 'Iterador no puede avanzar en una lista vacia'\n");
	} else printf("TEST NO PASADO: 'Iterador no puede avanzar en una lista vacia'\n");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void DadaUnaLIstaNoVacia_CuandoSeCreaUnIteradorYsePideElSiguiente_EntoncesDevuelveElPrimerElemento(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	char elemento_a = 'A';
	char elemento_b = 'B';
	char elemento_c = 'C';
	lista_insertar(lista, &elemento_a);
	lista_insertar(lista, &elemento_b);
	lista_insertar(lista, &elemento_c);

	//Actuar
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(!iterador) return;

	//Verificar
	if(*(char*)lista_iterador_siguiente(iterador) == elemento_a){
		printf("TEST PASADO: 'El iterador avanza correctamente'\n");
	} else printf("TEST NO PASADO: 'El iterador avanza correctamente'\n");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void DadaUnaListaNoVacia_CuandoSeCreaUnIteradorYAvanzaHastaLaUltimaPosicion_EntoncesAlPedirSiguienteDevuelveNull(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	char elemento_a = 'A';
	char elemento_b = 'B';
	char elemento_c = 'C';
	char elemento_d = 'D';
	lista_insertar(lista, &elemento_a);
	lista_insertar(lista, &elemento_b);
	lista_insertar(lista, &elemento_c);
	lista_insertar(lista, &elemento_d);
	int cantidad_ingresada = 4;

	//Actuar
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(!iterador) return;
	for(int i = 0; i < cantidad_ingresada; i++){
		lista_iterador_siguiente(iterador);
	}

	//Verificar
	if(!lista_iterador_siguiente(iterador)){
		printf("TEST PASADO: 'Iterador parado en la ultima posicion devuelve Null al pedirle avanzar'\n");
	} else printf("TEST NO PASADO: 'Iterador parado en la ultima posicion devuelve Null al pedirle avanzar'\n");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void funcion_para_probar_el_iterador_interno(void* elemento){
	if(elemento)
		*(int*)elemento = 0;
}

void DadaUnaListaNoVacia_CuandoSeLePasaUnaFuncionAlIteradorInterno_EntoncesLaFuncionSeEjecutaConTodosLosElementos(){
	//Organizar
	lista_t* lista = lista_crear();
	if(!lista) return;
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 100; i++){
		lista_insertar(lista, &elemento_1);
		lista_insertar(lista, &elemento_2);
		lista_insertar(lista, &elemento_3);
		lista_insertar(lista, &elemento_4);
		lista_insertar(lista, &elemento_5);
	}

	//Actuar
	lista_con_cada_elemento(lista, &funcion_para_probar_el_iterador_interno);

	//Verificar
	bool todos_son_cero = true;
	for(size_t i = 0; i < lista_elementos(lista); i++){
		if(*(int*)lista_elemento_en_posicion(lista, i) != 0){
			todos_son_cero = false;
		}
	}
	if(todos_son_cero){
		printf("TEST PASADO: 'Iterador interno de la lista funciona correctamente'\n");
	} else printf("TEST NO PASADO: 'Iterador interno de la lista funciona correctamente'\n");
	lista_destruir(lista);
}

int main(){

	//TESTS LISTA
	DadaUnaListaNoVacia_CuandoSePideElElementoDeLaPosicion0_EntoncesDevuelveElPrimerElemento();
	DadaUnaListaCon5Elementos_CuandoSePideElElementoDeLaUltimaPosicion_EntoncesDevuelveElQuintoElemento();
	DadaUnaListaCon1000Elementos_CuandoSeBorran1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0();
	DadaUnaListaCon1000Elementos_CuandoSeBorran500ElementosYSePideLaCantidad_EntoncesDevuelve500();
	DadaUnaListaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue();
	DadaUnaListaConElementos_CuandoSePideUnElementoDeUnaPosicionInexistente_EntoncesDevuelveNull();
	DadaUnaListaCon5Elementos_CuandoSePideBorrarUnElementoDeUnaPosicionInexistente_EntoncesBorraElUltimoElemento();
	DadaUnaListaVacia_CuandoSeIntentaEncolarElElementoNull_EntoncesDevuelveExito();
	DadaUnaListaNoVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveFalse();
	DadaUnaListaVacia_CuandoSePideElElementoDeUnaPosicion_EntoncesDevuelveNull();
	DadaUnaListaVacia_CuandoSeIntentaBorrar_EntoncesDevuelveError();
	DadaUnaListaVacia_CUandoSeIntentaBorrarDeUnaPosicion_EntoncesDevuelveError();
	DadaUnaListaVacia_CuandoSeInsertanElementosEnDistintasPosiciones_EntoncesLosElementosSeInsertanEnLasPosicionesIndicadas();
	DadaUnaListaNoVacia_CuandoSeIntentaInsertarEnUnaPosicionInexistente_EntoncesInsertaEnLaUltimaPosicion();
	DadaUnaListaCon5Elementos_CuandoSeBorraElElementoDeLaPosicion2_EntoncesSeBorraElTercerElemento();
	DadaUnaListaVacia_CuandoSePideElUltimoElemento_EntoncesDevuelveNull();
	DadaUnaListaCon5Elementos_CuandoBorroLaPosicion4YPidoElUltimoElemento_EntoncesDevuelveElCuartoElemento();
	DadaUnaListaNoVacia_CuandoSeIntentaInsertarEnLaPosicion0_EntoncesSeIncertaEnLaPosicionInicial();
	DadaUnaListaConElementos_CuandoSeBorraLosElementoYSePreguntaSiEstaVacia_EntoncesDevuelveTrue();

	//TESTS ITERADOR 
	DadaUnaListaNoVacia_CuandoSeCreaUnIteradorYSeLePreguntaSiTieneSiguiente_EntoncesDevuelveTrue();
	DadaUnaListaVacia_CuandoSeCreaUnIteradorYSePideElSiguiente_EntoncesDevuelveNull();
	DadaUnaLIstaNoVacia_CuandoSeCreaUnIteradorYsePideElSiguiente_EntoncesDevuelveElPrimerElemento();
	DadaUnaListaNoVacia_CuandoSeCreaUnIteradorYAvanzaHastaLaUltimaPosicion_EntoncesAlPedirSiguienteDevuelveNull();
	DadaUnaListaNoVacia_CuandoSeLePasaUnaFuncionAlIteradorInterno_EntoncesLaFuncionSeEjecutaConTodosLosElementos();

	return 0;
}