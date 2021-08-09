#include "hash.h"
#include "hash_iterador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DadoUnHashVacio_CuandoSeInsertan100Elementos_EntoncesLaCantidadDelHashEs100(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

	  char clave[] = "123";
	  //Actuar
	  for(int i = 1; i < 101; i++){
		  hash_insertar(garage, clave, "Auto");
		  *(int*)clave += i;
	  }

	  //Verificar
	  if(hash_cantidad(garage) == 100){
		  printf("TEST PASADO: 'El Hash crece correctamente al agregar muchos elementos'\n");
	  } else printf("TEST NO PASADO: 'El Hash crece correctamente al agregar muchos elementos'\n");
	  hash_destruir(garage);
}

void DadoUnHash_AlInsertarUnElemento_EntoncesDevuelve0(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

	  //Actuar

	  //Verificar
	  if(hash_insertar(garage, "AC123BD", "Auto de Mariano") == 0)
  		  printf("TEST PASADO: 'Hash devuelve 0 al insertar'\n");
  	else printf("TEST NO PASADO: 'Hash devuelve 0 al insertar'\n");
  	hash_destruir(garage);
}

void DadoUnHash_CuandoInsertoUnElementoConClaveRepetida_EntoncesElNuevoElementoReemplazaAlAnterior(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

	  //Actuar
	  hash_insertar(garage, "AC123BD", "Auto de Mariano");
  	hash_insertar(garage, "OPQ976", "Auto de Lucas");
  	hash_insertar(garage, "A421ACB", "Bici de Manu");

  	if((hash_insertar(garage, "A421ACB", "Auto de Joaquín") == 0) && (strcmp(hash_obtener(garage, "A421ACB"), "Auto de Joaquín") == 0)){
  		printf("TEST PASADO: Hash actualiza correctamente elementos con claves repetidas\n");
  	} else printf("TEST NO PASADO: Hash actualiza correctamente elementos con claves repetidas\n");
  	hash_destruir(garage);
}
void DadoUnHashNoVacio_CuandoSeBuscaUnElementoQueNoEstaEnElHash_EntoncesDevuelveNUll(){
    //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

  	hash_insertar(garage, "AC123BD", "Auto de Mariano");
  	hash_insertar(garage, "OPQ976", "Auto de Lucas");
  	hash_insertar(garage, "A421ACB", "Bici de Manu");

  	//Actuar

  	//Verificar
  	if(!hash_obtener(garage, "ABC123"))
  		printf("TEST PASADO: 'Hash devuelve NULL cuando el elemento buscado no se encuentra'\n");
  	else printf("TEST NO PASADO: 'Hash devuelve NULL cuando el elemento buscado no se encuentra'\n");
  	hash_destruir(garage);
}

void DadoUnHashNoVacio_CuandoSeBuscaUnElementoQueEstaEnElHash_EntoncesDevuelveElElementoCorrecto(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

  	hash_insertar(garage, "AC123BD", "Auto de Mariano");
  	hash_insertar(garage, "OPQ976", "Auto de Lucas");
  	hash_insertar(garage, "A421ACB", "Bici de Manu");

  	//Actuar
  	void* elemento = hash_obtener(garage, "OPQ976");

  	//Verificar
  	if(strcmp(elemento, "Auto de Lucas") == 0)
  		printf("TEST PASADO: 'Hash devuelve el elemento correcto cuando el elemento buscado se encuentra en el hash'\n");
  	else printf("TEST NO PASADO: 'Hash devuelve el elemento correcto cuando el elemento buscado se encuentra en el hash'\n");
  	hash_destruir(garage);
}

void DadoUnHashNoVacio_CuandoSeBorraUnElementoQuePerteneceAlHash_EntoncesLoBorraCorrectamenteYDevuelveTrue(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

  	hash_insertar(garage, "AC123BD", "Auto de Mariano");
  	hash_insertar(garage, "OPQ976", "Auto de Lucas");
  	hash_insertar(garage, "A421ACB", "Bici de Manu");

  	//Actuar

  	//Verificar
  	if((hash_quitar(garage, "AC123BD") == 0) && (!hash_contiene(garage, "AC123BD")))
  		printf("TEST PASADO: 'Hash borra un elemento correctamente'\n");
  	else printf("TEST NO PASADO: 'Hash borra un elemento correctamente'\n");
  	hash_destruir(garage);	
}

void DadoUnHashNoVacio_CuandoSeBorraUnElementoQueNoPerteneceAlHash_EntoncesDevuelveError(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

  	hash_insertar(garage, "AC123BD", "Auto de Mariano");
  	hash_insertar(garage, "OPQ976", "Auto de Lucas");
  	hash_insertar(garage, "A421ACB", "Bici de Manu");

  	//Actuar

  	//Verificar
  	if(hash_quitar(garage, "DEF456"))
  		printf("TEST PASADO: 'Hash devuelve error al intentar borrar un elemento que no está almacenado'\n");
  	else printf("TEST NO PASADO: 'Hash devuelve error al intentar borrar un elemento que no está almacenado'\n");
  	hash_destruir(garage);		
}

void DadoUnHashNoVacio_CuandoSeBorraMultiplesElementos_EntoncesDevuelveExito(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);
	  hash_insertar(garage, "AC123BD", "Auto de Mariano");
    hash_insertar(garage, "OPQ976", "Auto de Lucas");
    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");
    hash_insertar(garage, "AC152AD", "Auto de Agustina");
    hash_insertar(garage, "DZE443", "Auto de Jonathan");
    hash_insertar(garage, "AA436BA", "Auto de Gonzalo");
    hash_insertar(garage, "QDM443", "Auto de Daniela");
    hash_insertar(garage, "BD123AC", "Auto de Pablo");
    hash_insertar(garage, "CD442AA", "Auto de Micaela");

	  //Actuar
	  hash_quitar(garage, "AA442CD");
	  hash_quitar(garage, "DZE443");
	  hash_quitar(garage, "CD442AA");

	  //Verificar
	  bool fallo_un_borrado = false;
	  if(hash_contiene(garage, "AA442CD") || hash_contiene(garage, "DZE433") || hash_contiene(garage, "CD442AA"))
		  fallo_un_borrado = true;

	  if(!fallo_un_borrado && hash_cantidad(garage) == 7){
		  printf("TEST PASADO: 'Hash realiza correctamente multiples borrados'\n");
	  } else printf("TEST NO PASADO: 'Hash realiza correctamente multiples borrados'\n");
	  hash_destruir(garage);
}

void DadoUnHashVacio_CuandoSeInsertan10ElementosySePideLaCantidad_EntoncesDevuelve10(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

	  //Actuar
	  hash_insertar(garage, "AC123BD", "Auto de Mariano");
    hash_insertar(garage, "OPQ976", "Auto de Lucas");
    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");
    hash_insertar(garage, "AC152AD", "Auto de Agustina");
    hash_insertar(garage, "DZE443", "Auto de Jonathan");
    hash_insertar(garage, "AA436BA", "Auto de Gonzalo");
    hash_insertar(garage, "QDM443", "Auto de Daniela");
    hash_insertar(garage, "BD123AC", "Auto de Pablo");
    hash_insertar(garage, "CD442AA", "Auto de Micaela");

    //Verificar
    if(hash_cantidad(garage) == 10)
    	printf("TEST PASADO: 'Hash devuelve la cantidad correcta de elementos contenidos luego de insertar'\n");
    else printf("TEST NO PASADO: 'Hash devuelve la cantidad correcta de elementos contenidos luego de insertar'\n");
  	hash_destruir(garage);
}

void DadoUnHashCon10Elementos_CuandoSeBorranLos10ElementosYSePideLaCantidad_EntoncesDevuelve10(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

	  hash_insertar(garage, "AC123BD", "Auto de Mariano");
    hash_insertar(garage, "OPQ976", "Auto de Lucas");
    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");
    hash_insertar(garage, "AC152AD", "Auto de Agustina");

    //Actuar
    hash_quitar(garage, "AC123BD");
    hash_quitar(garage, "OPQ976");
    hash_quitar(garage, "A421ACB");
    hash_quitar(garage, "AA442CD");
    hash_quitar(garage, "AC152AD");

    //Verificar
    if(hash_cantidad(garage) == 0)
    	printf("TEST PASADO: 'Hash devuelve la cantidad correcta de elementos contenidos luego de borrar'\n");
    else printf("TEST NO PASADO: 'Hash devuelve la cantidad correcta de elementos contenidos luego de borrar'\n");
  	hash_destruir(garage);
}

void DadaUnHashNoVacio_CuandoSePreguntaSiContieneUnElementoQueEstaAlmacenado_EntoncesDevuelveTrue(){
	  //Organizar
	  hash_t* garage = hash_crear(NULL, 5);

    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");
    hash_insertar(garage, "AC152AD", "Auto de Agustina");

    //Actuar

    //Verificar
    if(hash_contiene(garage, "A421ACB"))
    	printf("TEST PASADO: 'Hash devuelve true cuando se pregunta si contiene un elemento que esta almacenado'\n");
    else printf("TEST NO PASADO: 'Hash devuelve true cuando se pregunta si contiene un elemento que esta almacenado'\n");
    hash_destruir(garage);
}

void DadaUnHashNoVacio_CuandoSePreguntaSiContieneUnElementoQueNoEstaAlmacenado_EntoncesDevuelveFalse(){
	  //Organizar
    hash_t* garage = hash_crear(NULL, 5);

    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");
    hash_insertar(garage, "AC152AD", "Auto de Agustina");

    //Actuar

    //Verificar
    if(!hash_contiene(garage, "GHI789"))
    	printf("TEST PASADO: 'Hash devuelve false cuando se pregunta si contiene un elemento que no esta almacenado'\n");
    else printf("TEST NO PASADO: 'Hash devuelve false cuando se pregunta si contiene un elemento que no esta almacenado'\n");
    hash_destruir(garage);	
}

void DadoUnHashVacio_CuandoSeCreaUnIteradorYSePideElSiguienteElemento_EntoncesDevuelveNull(){
    //Organizar
    hash_t* garage = hash_crear(NULL, 5);

    //Actuar
    hash_iterador_t* iterador = hash_iterador_crear(garage);

    //Verificar
    if(!hash_iterador_siguiente(iterador))
      printf("TEST PASADO: 'iterador devuelve NULL si no quedan elementos por recorrer'\n");
    else printf("TEST NO PASADO: 'iterador devuelve NULL si no quedan elementos por recorrer'\n");
    hash_iterador_destruir(iterador);
    hash_destruir(garage);
}

void DadoUnHashNoVacio_CuandoSeCreaUnIteradorYSePideElSiguienteElemento_EntoncesDevuelveUnElemento(){
    //Organizar
    hash_t* garage = hash_crear(NULL, 5);
    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");

    //Actuar
    hash_iterador_t* iterador = hash_iterador_crear(garage);

    //Verificar
    if(hash_iterador_siguiente(iterador)){
        printf("TEST PASADO: 'iterador devuelve un elemento si quedan elementos por recorrer'\n");
    } else printf("TEST NO PASADO: 'iterador devuelve un elemento si quedan elementos por recorrer'\n");
    hash_iterador_destruir(iterador);
    hash_destruir(garage);
}

void prueba_extra(){
	//Organizar
    hash_t* garage = hash_crear(NULL, 5);
    hash_insertar(garage, "A421ACB", "Bici de Manu");	

        //Actuar
    hash_iterador_t* iterador = hash_iterador_crear(garage);

    if(strcmp((char*)hash_iterador_siguiente(iterador), "A421ACB") == 0){
    	printf("HOla\n");
    }
    hash_iterador_destruir(iterador);
    hash_destruir(garage);
}

void DadoUnHashVacio_CuandoSeCreaUnIteradorYSePreguntaSiTieneSiguiente_EntoncesDevuelveFalse(){
    //Organizar
    hash_t* garage = hash_crear(NULL, 5);

    //Actuar
    hash_iterador_t* iterador = hash_iterador_crear(garage);

    //Verificar
    if(!hash_iterador_tiene_siguiente(iterador))
      printf("TEST PASADO: 'iterador devuelve false si no quedan elementos por recorrer'\n");
    else printf("TEST NO PASADO: 'iterador devuelve false si no quedan elementos por recorrer'\n");
    hash_iterador_destruir(iterador);
    hash_destruir(garage);
}

void DadoUnHashNoVacio_CuandoSeCreaUnIteradorYSePreguntaSiTieneSiguiente_EntoncesDevuelveTrue(){
    //Organizar
    hash_t* garage = hash_crear(NULL, 5);
    hash_insertar(garage, "A421ACB", "Bici de Manu");
    hash_insertar(garage, "AA442CD", "Auto de Guido");

    //Actuar
    hash_iterador_t* iterador = hash_iterador_crear(garage);

    //Verificar
    if(hash_iterador_tiene_siguiente(iterador))
      printf("TEST PASADO: 'iterador devuelve true si quedan elementos por recorrer'\n");
    else printf("TEST NO PASADO: 'iterador devuelve true si quedan elementos por recorrer'\n");
    hash_iterador_destruir(iterador);
    hash_destruir(garage);
}

int main(){

    //test-de-dimension
	  DadoUnHashVacio_CuandoSeInsertan100Elementos_EntoncesLaCantidadDelHashEs100();
	  //hash_insertar
	  DadoUnHash_AlInsertarUnElemento_EntoncesDevuelve0();
	  DadoUnHash_CuandoInsertoUnElementoConClaveRepetida_EntoncesElNuevoElementoReemplazaAlAnterior();
    //hash_obtener
  	DadoUnHashNoVacio_CuandoSeBuscaUnElementoQueNoEstaEnElHash_EntoncesDevuelveNUll();
  	DadoUnHashNoVacio_CuandoSeBuscaUnElementoQueEstaEnElHash_EntoncesDevuelveElElementoCorrecto();
	  //hash_quitar
	  DadoUnHashNoVacio_CuandoSeBorraUnElementoQuePerteneceAlHash_EntoncesLoBorraCorrectamenteYDevuelveTrue();
	  DadoUnHashNoVacio_CuandoSeBorraUnElementoQueNoPerteneceAlHash_EntoncesDevuelveError();
	  DadoUnHashNoVacio_CuandoSeBorraMultiplesElementos_EntoncesDevuelveExito();
	  //hash_cantidad
	  DadoUnHashVacio_CuandoSeInsertan10ElementosySePideLaCantidad_EntoncesDevuelve10();
	  DadoUnHashCon10Elementos_CuandoSeBorranLos10ElementosYSePideLaCantidad_EntoncesDevuelve10();
	  //hash_contiene
	  DadaUnHashNoVacio_CuandoSePreguntaSiContieneUnElementoQueEstaAlmacenado_EntoncesDevuelveTrue();
	  DadaUnHashNoVacio_CuandoSePreguntaSiContieneUnElementoQueNoEstaAlmacenado_EntoncesDevuelveFalse();
  
	  //TEST HASH ITERADOR
	  //hash_iterador_siguiente
  	DadoUnHashVacio_CuandoSeCreaUnIteradorYSePideElSiguienteElemento_EntoncesDevuelveNull();
  	DadoUnHashNoVacio_CuandoSeCreaUnIteradorYSePideElSiguienteElemento_EntoncesDevuelveUnElemento();
  	prueba_extra();
	  //hash_iterador_tiene_siguiente
  	DadoUnHashVacio_CuandoSeCreaUnIteradorYSePreguntaSiTieneSiguiente_EntoncesDevuelveFalse();
  	DadoUnHashNoVacio_CuandoSeCreaUnIteradorYSePreguntaSiTieneSiguiente_EntoncesDevuelveTrue();

  	return 0;
}