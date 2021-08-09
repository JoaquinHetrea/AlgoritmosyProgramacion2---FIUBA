#include "cola.h"
#include <stdio.h>

void DadaUnaColaCon5Elementos_CuandoSePideUnElemento_EntoncesDevuelveElPrimerElemento(){
	//Organizar
	cola_t* cola = cola_crear();

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	cola_encolar(cola, &elemento_1);
	cola_encolar(cola, &elemento_2);
	cola_encolar(cola, &elemento_3);
	cola_encolar(cola, &elemento_4);
	cola_encolar(cola, &elemento_5);

	//Actuar
	int primer_elemento = *(int*)cola_primero(cola);

	//Verificar
	if(primer_elemento == elemento_1) printf("TEST: 'La cola devuelve el primer elemento' PASADO\n");
	else printf("TEST: 'La cola devuelve el primer elemento' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaCon5Elementos_CuandoSeDesencolaUnoYSePideElPrimero_EntoncesDevuelveElSegundoElementoEncolado(){
	//Organizar
	cola_t* cola = cola_crear();

	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	cola_encolar(cola, &elemento_1);
	cola_encolar(cola, &elemento_2);
	cola_encolar(cola, &elemento_3);
	cola_encolar(cola, &elemento_4);
	cola_encolar(cola, &elemento_5);

	//Actuar
	cola_desencolar(cola);
	int segundo_elemento = *(int*)cola_primero(cola);

	//Verificar
	if(segundo_elemento == elemento_2) printf("TEST: 'La cola devuelve el elemento correcto luego de desapilar' PASADO\n");
	else printf("TEST: 'La cola devuelve el elemento correcto luego de desapilar' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaCon1000Elementos_CuandoSeDesencolan1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0(){
	//Organizar
	cola_t* cola = cola_crear();
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 200; i++){
		cola_encolar(cola, &elemento_1);
		cola_encolar(cola, &elemento_2);
		cola_encolar(cola, &elemento_3);
		cola_encolar(cola, &elemento_4);
		cola_encolar(cola, &elemento_5);
	}

	//Actuar
	for(int i = 0; i < 1000; i++){
		cola_desencolar(cola);
	}

	//Verificar
	if(cola_vacia(cola)) printf("TEST: 'La cola encola y desencola correctamente' PASADO\n");
	else printf("TEST: 'La cola encola y desencola correctamente' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaCon1000Elementos_CuandoSeDesencolan500ElementosYSePideLaCantidad_EntoncesDevuelve500(){
	//Organizar
	cola_t* cola = cola_crear();
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;
	for(int i = 0; i < 200; i++){
		cola_encolar(cola, &elemento_1);
		cola_encolar(cola, &elemento_2);
		cola_encolar(cola, &elemento_3);
		cola_encolar(cola, &elemento_4);
		cola_encolar(cola, &elemento_5);
	}

	//Actuar
	for(int i = 0; i < 500; i++){
		cola_desencolar(cola);
	}

	//Verificar
	if(cola_cantidad(cola) == 500) printf("TEST: 'La cola devuelve la cantidad correcta luego de desencolar' PASADO\n");
	else printf("TEST: 'La cola devuelve la cantidad correcta luego de desencolar' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(){
	//Organizar
	cola_t* cola = cola_crear();

	//Actuar

	//Verificar
	if(cola_vacia(cola)) printf("TEST: 'Cola vacia devuelve true al preguntar si esta vacia' PASADO\n");
	else printf("TEST: 'Cola vacia devuelve true al preguntar si esta vacia' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaNoVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveFalse(){
	//Organizar
	cola_t* cola = cola_crear();

	//Actuar
	char elemento_a = 'A';
	cola_encolar(cola, &elemento_a);

	//Verificar
	if(!cola_vacia(cola)) printf("TEST: 'Cola no vacia devuelve false al preguntar si esta vacia' PASADO\n");
	else printf("TEST: 'Cola no vacia devuelve false al preguntar si esta vacia' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaVacia_CuandoSePideUnElemento_EntoncesDevuelveNull(){
	//Organizar
	cola_t* cola = cola_crear();

	//Actuar

	//Verificar
	if(cola_primero(cola) == NULL) printf("TEST: 'Cola vacia devuelve NULL al pedir un elemento' PASADO\n");
	else printf("TEST: 'Cola vacia devuelve NULL al pedir un elemento' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaVacia_CuandoSeIntentaDesencolar_EntoncesDevuelveError(){
	//Organizar
	cola_t* cola = cola_crear();

	//Actuar
	bool pudo_desencolar = !cola_desencolar(cola);

	//Verificar
	if(!pudo_desencolar) printf("TEST: 'No se puede desencolar de una cola vacia' PASADO\n");
	else printf("TEST: 'No se puede desencolar de una cola vacia' NO PASADO\n");

	cola_destruir(cola);
}

void DadaUnaColaVacia_CuandoSeIntentaEncolarElElementoNull_EntoncesDevuelveExito(){
	//Organizar
	cola_t* cola = cola_crear();
	void* elemento_null = NULL;

	//Actuar

	//Verificar
	if(!cola_encolar(cola, elemento_null)) printf("TEST: 'Se puede apilar el elemento NULL' PASADO\n");
	else printf("TEST: 'Se puede apilar el elemento NULL' NO PASADO\n");

	cola_destruir(cola);
}

int main(){

	DadaUnaColaCon5Elementos_CuandoSePideUnElemento_EntoncesDevuelveElPrimerElemento();
	DadaUnaColaCon5Elementos_CuandoSeDesencolaUnoYSePideElPrimero_EntoncesDevuelveElSegundoElementoEncolado();
	DadaUnaColaCon1000Elementos_CuandoSeDesencolan1000ElementosYSePreguntaSiEstaVacia_EntoncesDevuelve0();
	DadaUnaColaCon1000Elementos_CuandoSeDesencolan500ElementosYSePideLaCantidad_EntoncesDevuelve500();
	DadaUnaColaVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue();
	DadaUnaColaNoVacia_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveFalse();
	DadaUnaColaVacia_CuandoSePideUnElemento_EntoncesDevuelveNull();
	DadaUnaColaVacia_CuandoSeIntentaDesencolar_EntoncesDevuelveError();
	DadaUnaColaVacia_CuandoSeIntentaEncolarElElementoNull_EntoncesDevuelveExito();

	return 0;
}