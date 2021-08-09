#include "pila.h"
#include <stdio.h>

void DadaUnaPilaCon5Elementos_CuandoSePideUno_EntoncesDevuelveElUltimoElemento(){
	//Organizar
	pila_t* pila = pila_crear();

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	pila_apilar(pila, &elemento_1);
	pila_apilar(pila, &elemento_2);
	pila_apilar(pila, &elemento_3);
	pila_apilar(pila, &elemento_4);
	pila_apilar(pila, &elemento_5);

	//Actuar
	int elemento_tope = *(int*)pila_tope(pila);

	//Verificar
	if(elemento_tope == elemento_5){
		printf("TEST: 'Devuelve el elemento correcto' PASADO\n");
	} else printf("TEST: 'Devuelve el elemento correcto' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaCon5Elementos_CuandoSeDesapilaUnoYSePideUnElemento_EntoncesDevuelveElCuartoElementoAlmacenado(){
	//Organizar
	pila_t* pila = pila_crear();

	char elemento_1 = 'H';
	char elemento_2 = 'o';
	char elemento_3 = 'l';
	char elemento_4 = 'a';
	char elemento_5 = '!';
	pila_apilar(pila, &elemento_1);
	pila_apilar(pila, &elemento_2);
	pila_apilar(pila, &elemento_3);
	pila_apilar(pila, &elemento_4);
	pila_apilar(pila, &elemento_5);

	//Actuar
	pila_desapilar(pila);
	char elemento_tope = *(char*)pila_tope(pila);

	//Verificar
	if(elemento_tope == elemento_4){
		printf("TEST: 'Devuelve el elemento correcto luego de desapilar' PASADO\n");
	} else printf("TEST: 'Devuelve el elemento correcto luego de desapilar' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaCon1000Elementos_CuandoSeDesapilan1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0(){
	//Organizar
	pila_t* pila = pila_crear();
	char string_1[] = "Hola";
	char string_2[] = "Que tal?";
	char string_3[] = "Todo bien?";
	char string_4[] = "Saludos";
	char string_5[] = "Cuidate!";
	for(int i = 0; i < 200; i++){
		pila_apilar(pila, &string_1);
		pila_apilar(pila, &string_2);
		pila_apilar(pila, &string_3);
		pila_apilar(pila, &string_4);
		pila_apilar(pila, &string_5);
	}

	//Actuar
	for(int i = 0; i < 1000; i++){
		pila_desapilar(pila);
	}

	//Verificar
	if(pila_vacia(pila)){
		printf("TEST: 'Pila con 1000 elementos, luego de desapilar 1000 elementos, devuelve 0 al preguntar si está vacía' PASADO\n");
	} else printf("TEST: 'Pila con 1000 elementos, luego de desapilar 1000 elementos, devuelve 0 al preguntar si está vacía' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaCon1000Elementos_CuandoSeDesapilan500ElementosYSePideLaCantidad_EntoncesDevuelve500(){
	//Organizar
	pila_t* pila = pila_crear();
	char string_1[] = "Hola";
	char string_2[] = "Que tal?";
	char string_3[] = "Todo bien?";
	char string_4[] = "Saludos";
	char string_5[] = "Cuidate!";
	for(int i = 0; i < 200; i++){
		pila_apilar(pila, &string_1);
		pila_apilar(pila, &string_2);
		pila_apilar(pila, &string_3);
		pila_apilar(pila, &string_4);
		pila_apilar(pila, &string_5);
	}

	//Actuar
	for(int i = 0; i < 500; i++){
		pila_desapilar(pila);
	}

	//Verificar
	if(pila_cantidad(pila) == 500){
		printf("TEST: 'Pila con 1000 elementos, luego de desapilar 500 elementos, devuelve 500 al pedir la cantidad' PASADO\n");
	} else printf("TEST: 'Pila con 1000 elementos, luego de desapilar 500 elementos, devuelve 500 al pedir la cantidad' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaVacia_CuandoSePideLaCantidadDeElementosAlmacenados_EntoncesDevuelve0(){
	//Organizar
	pila_t* pila = pila_crear();

	//Actuar

	//Verificar
	if(pila_cantidad(pila) == 0){
		printf("TEST: 'El tope de una pila vacía es 0' PASADO\n");
	} else printf("TEST: 'El tope de una pila vacía es 0' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaVacia_CuandoSeIntentaDesapilarUnElemento_EntoncesDevuelveError(){
	//Organizar
	pila_t* pila = pila_crear();

	//Actuar
	bool no_pudo_desapilar = pila_desapilar(pila);

	//Verificar
	if(no_pudo_desapilar){
		printf("TEST: 'No se puede desapilar de una pila vacia' PASADO\n");
	} else printf("TEST: 'No se puede desapilar de una pila vacia' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelve0(){
	//Organizar
	pila_t* pila = pila_crear();

	//Actuar
	bool esta_vacia = pila_vacia(pila);

	//Verificar
	if(esta_vacia){
		printf("TEST: 'Pila vacía devuelve verdadero al preguntar si está vacia' PASADO\n");
	} else printf("TEST: 'Pila vacía devuelve verdadero al preguntar si está vacia' NO PASADO\n");

	pila_destruir(pila);
}

void DadaUnaPilaVacia_CuandoSePideUnElemento_EntoncesDevuelveNull(){
	//Organizar
	pila_t* pila = pila_crear();

	//Actuar
	void* elemento = pila_tope(pila);

	//Verificar
	if(!elemento){
		printf("TEST: 'Pila vacía devuelve NULL al pedir elemento' PASADO\n");
	} else printf("TEST: 'Pila vacía devuelve NULL al pedir elemento' NO PASADO\n");

	pila_destruir(pila);
}

int main(){

	DadaUnaPilaCon5Elementos_CuandoSePideUno_EntoncesDevuelveElUltimoElemento();
	DadaUnaPilaCon5Elementos_CuandoSeDesapilaUnoYSePideUnElemento_EntoncesDevuelveElCuartoElementoAlmacenado();
	DadaUnaPilaCon1000Elementos_CuandoSeDesapilan1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0();
	DadaUnaPilaCon1000Elementos_CuandoSeDesapilan500ElementosYSePideLaCantidad_EntoncesDevuelve500();
	DadaUnaPilaVacia_CuandoSePideLaCantidadDeElementosAlmacenados_EntoncesDevuelve0();
	DadaUnaPilaVacia_CuandoSeIntentaDesapilarUnElemento_EntoncesDevuelveError();
	DadaUnaPilaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelve0();
	DadaUnaPilaVacia_CuandoSePideUnElemento_EntoncesDevuelveNull();

    return 0;
}