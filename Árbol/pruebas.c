#include "abb.h"
#include <stdio.h>
#include <time.h>

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
	c->clave = clave;
    return c;
}

void crear_cosas(cosa* cosas[], int cantidad){
    for(int i = 0; i < cantidad; i++){
        cosas[i] = crear_cosa(i);
    }
}

void destruir_cosa(cosa* c){
    if(c)
	free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
	return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
	return -1;
    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
	return;
    destruir_cosa((cosa*)elemento);
}

bool acumular(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((cosa*)elemento)->clave;
    }
  return false;   
}

bool acumular_hasta_3(void* elemento, void* extra){
  extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
  if(elemento && extra){
    *(int*)extra += ((cosa*)elemento)->clave;
    if(((cosa*)elemento)->clave == 3)
      return true;
  }
  return false;
}

void DadoUnABBVacio_CuandoSePreguntaSiEstaVacio_EntoncesDevuelveTrue(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    //Actuar

    //Verificar
    if(arbol_vacio(arbol)) 
        printf("TEST PASADO: 'Arbol vacio devuelve true al preguntar si está vacio'\n");
    else printf("TEST NO PASADO: 'Arbol vacio devuelve true al preguntar si está vacio'\n");
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePreguntaSiEstaVacio_EntoncesDevuelveFalse(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar

    //Verificar
    if(!arbol_vacio(arbol)) 
        printf("TEST PASADO: 'Arbol no vacio devuelve false al preguntar si está vacio'\n");
    else printf("TEST NO PASADO: 'Arbol no vacio devuelve false al preguntar si está vacio'\n");
    arbol_destruir(arbol);
}

void DadounABBConElementos_CuandoSePideBuscarUnElementoQueNoSeEncuentraEnElABB_EntoncesDevuelveNull(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[10];
    crear_cosas(c, 10);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[7]);
    arbol_insertar(arbol, c[8]);
    arbol_insertar(arbol, c[9]);
    arbol_insertar(arbol, c[6]);
    arbol_insertar(arbol, c[5]);

    //Actuar
    cosa* c11 = crear_cosa(11);

    //Verificar
    if(!arbol_buscar(arbol, c11))
        printf("TEST PASADO: 'Arbol devuelve NULL cuando no tiene el elemento buscado'\n");
    else printf("TEST NO PASADO: 'Arbol devuelve NULL cuando no tiene el elemento buscado'\n");
    destructor_de_cosas(c11);
    arbol_destruir(arbol);
}  

void DadoUnABBCon1000Elementos_CuandoSeBorranLos1000ElementosYSePreguntaSiEstaVacio_EntoncesDevuelveTrue(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[1000];
    for(int i = 0;i < 1000; i++){
        c[i] = crear_cosa(i);
        arbol_insertar(arbol, c[i]);
    }

    //Actuar
    for(int i = 0;i < 1000; i++){
        arbol_borrar(arbol, c[i]);
    }

    //Verificar
    if(arbol_vacio(arbol)) 
        printf("TEST PASADO: 'Arbol inserta y elimina correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol inserta y elimina correctamente'\n");
    arbol_destruir(arbol);
}

void DadoUnABBVacio_CuandoSePideLaRaiz_EntoncesDevuelveNull(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    //Actuar

    //Verificar
    if(!arbol_raiz(arbol))
        printf("TEST PASADO: 'Arbol vacio devuelve NULL al pedir la raiz'\n");
    else printf("TEST NO PASADO: 'Arbol vacio devuelve NULL al pedir la raiz'\n");
    arbol_destruir(arbol);
}

void DadoUnABBCon5Elementos_CuandoSePideLaRaiz_EntoncesDevuelveElPrimerElementoInsertardo(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);

    //Actuar

    //Verificar
    if(comparar_cosas(arbol_raiz(arbol), c[2]) == 0)
        printf("TEST PASADO: 'Arbol devuelve el elemento correcto al pedir la raiz'\n");
    else printf("TEST NO PASADO: 'Arbol devuelve el elemento correcto al pedir la raiz'\n");
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideBorrarUnNodoHoja_EntoncesLoBorraCorrectamenteYDevuelve0(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[3];
    crear_cosas(c, 3);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    cosa* aux = crear_cosa(3);

    //Verificar
    if(!arbol_borrar(arbol, c[2]) && !arbol_buscar(arbol, aux))
        printf("TEST PASADO: 'Arbol borra nodos hoja correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol borra nodos hoja correctamente'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConUnHijoDerecho_EntoncesLoBorraCorrectamenteYDevuelve0(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[4];
    crear_cosas(c, 4);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    cosa* aux = crear_cosa(2);

    //Verificar
    if(!arbol_borrar(arbol, c[2]) && !arbol_buscar(arbol, aux))
        printf("TEST PASADO: 'Arbol borra nodos con un hijo derecho correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol borra nodos con un hijo derecho correctamente'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConUnHijoIzquierdo_EntoncesLoBorraCorrectamenteYDevuelve0(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[4];
    crear_cosas(c, 4);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    cosa* aux = crear_cosa(3);

    //Verificar
    if(!arbol_borrar(arbol, c[3]) && !arbol_buscar(arbol, aux))
        printf("TEST PASADO: 'Arbol borra nodos con un hijo izquierdo correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol borra nodos con un hijo izquierdo correctamente'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConDosHijos_EntoncesLoBorraCorrectamenteYDevuelve0(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[4]);

    //Actuar
    cosa* aux = crear_cosa(3);

    //Verificar
    if(!arbol_borrar(arbol, c[3]) && !arbol_buscar(arbol, aux))
        printf("TEST PASADO: 'Arbol borra nodos con dos hijos correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol borra nodos con dos hijos correctamente'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);  
}

void DadoUnABBNoVacio_CuandoSePideBorrarLaRaizConDosHijos_EntoncesLaBorraCorrectamenteYDevuelve0(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[8];
    crear_cosas(c, 8);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[6]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[5]);
    arbol_insertar(arbol, c[7]);
    arbol_insertar(arbol, c[2]);

    //Actuar
    cosa* aux = crear_cosa(4);

    //Verificar
    if(!arbol_borrar(arbol, c[4]) && !arbol_buscar(arbol, aux))
        printf("TEST PASADO: 'Arbol borra nodo raiz con dos hijos correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol borra nodo raiz con dos hijos correctamente'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);  
}

void DadoUnABBNoVacio_CUandoSePideBorrarUnElementoNoAlmacenado_EntoncesDevuelveError(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[2]);

    //Actuar
    cosa* aux = crear_cosa(6);

    //Verificar
    if(arbol_borrar(arbol, aux))
        printf("TEST PASADO: 'Arbol devuelve error si no contiene el elemento a ser eliminado'\n");
    else printf("TEST NO PASADO: 'Arbol devuelve error si no contiene el elemento a ser eliminado'\n");
    destructor_de_cosas(aux);
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideUnRecorridoInorden_EntoncesElArrayEsLlenadoCorrectamente(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[7];
    crear_cosas(c, 7);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[5]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[6]);

    //Actuar
    int tamanio_array = 10;
    void* array[tamanio_array];
    int tope_array = arbol_recorrido_inorden(arbol, array, tamanio_array);

    //Verificar
    bool lo_recorrio_bien = true;
    cosa* recorrido_correcto[7] = {c[0], c[1], c[2], c[3], c[4], c[5], c[6]};
    for(int i = 0; i < tope_array; i++){
        if(comparar_cosas(array[i], recorrido_correcto[i]) != 0){
            lo_recorrio_bien = false;
        }
    }
    if(lo_recorrio_bien)
        printf("TEST PASADO: 'Arbol realiza el recorrido inorden correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol realiza el recorrido inorden correctamente'\n");
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideUnRecorridoPreorden_EntoncesElArrayEsLlenadoCorrectamente(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[7];
    crear_cosas(c, 7);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[5]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[6]);

    //Actuar
    int tamanio_array = 10;
    void* array[tamanio_array];
    int tope_array = arbol_recorrido_preorden(arbol, array, tamanio_array);

    //Verificar
    bool lo_recorrio_bien = true;
    cosa* recorrido_correcto[7] = {c[3], c[1], c[0], c[2], c[5], c[4], c[6]};
    for(int i = 0; i < tope_array; i++){
        if(comparar_cosas(array[i], recorrido_correcto[i]) != 0){
            lo_recorrio_bien = false;
        }
    }
    if(lo_recorrio_bien)
        printf("TEST PASADO: 'Arbol realiza el recorrido preorden correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol realiza el recorrido preorden correctamente'\n");
    arbol_destruir(arbol);
}

void DadoUnABBNoVacio_CuandoSePideUnRecorridoPostorden_EntoncesElArrayEsLlenadoCorrectamente(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[7];
    crear_cosas(c, 7);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[5]);
    arbol_insertar(arbol, c[0]);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[6]);

    //Actuar
    int tamanio_array = 10;
    void* array[tamanio_array];
    int tope_array = arbol_recorrido_postorden(arbol, array, tamanio_array);

    //Verificar
    bool lo_recorrio_bien = true;
    cosa* recorrido_correcto[7] = {c[0], c[2], c[1], c[4], c[6], c[5], c[3]};
    for(int i = 0; i < tope_array; i++){
        if(comparar_cosas(array[i], recorrido_correcto[i]) != 0){
            lo_recorrio_bien = false;
        }
    }
    if(lo_recorrio_bien)
        printf("TEST PASADO: 'Arbol realiza el recorrido postorden correctamente'\n");
    else printf("TEST NO PASADO: 'Arbol realiza el recorrido postorden correctamente'\n");
    arbol_destruir(arbol);
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoInorden_EntoncesDevuelve10(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, acumular, &acumulador);

    //Verificar
    if(acumulador == 10){
        printf("TEST PASADO: 'Arbol aplica la funcion correctamente en el recorrido inorden'\n");
    } else printf("TEST NO PASADO: 'Arbol aplica la funcion correctamente en el recorrido inorden'\n");
    arbol_destruir(arbol);
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoPreorden_EntoncesDevuelve10(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, acumular, &acumulador);

    //Verificar
    if(acumulador == 10){
        printf("TEST PASADO: 'Arbol aplica la funcion correctamente en el recorrido preorden'\n");
    } else printf("TEST NO PASADO: 'Arbol aplica la funcion correctamente en el recorrido preorden'\n");
    arbol_destruir(arbol);
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoPostorden_EntoncesDevuelve10(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, acumular, &acumulador);

    //Verificar
    if(acumulador == 10){
        printf("TEST PASADO: 'Arbol aplica la funcion correctamente en el recorrido postorden'\n");
    } else printf("TEST NO PASADO: 'Arbol aplica la funcion correctamente en el recorrido postorden'\n");
    arbol_destruir(arbol);  
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoInorden_EntoncesDevuelve6(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, acumular_hasta_3, &acumulador);

    //Verificar
    if(acumulador == 6){
        printf("TEST PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido inorden'\n");
    } else printf("TEST NO PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido inorden'\n");
    arbol_destruir(arbol);
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoPreorden_EntoncesDevuelve6(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, acumular_hasta_3, &acumulador);

    //Verificar
    if(acumulador == 6){
        printf("TEST PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido preorden'\n");
    } else printf("TEST NO PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido preorden'\n");
    arbol_destruir(arbol);
}

void DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoPostorden_EntoncesDevuelve8(){
    //Organizar
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa* c[5];
    crear_cosas(c, 5);
    arbol_insertar(arbol, c[2]);
    arbol_insertar(arbol, c[1]);
    arbol_insertar(arbol, c[3]);
    arbol_insertar(arbol, c[4]);
    arbol_insertar(arbol, c[0]);

    //Actuar
    int acumulador = 0;
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, acumular_hasta_3, &acumulador);

    //Verificar
    if(acumulador == 8){
        printf("TEST PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido postorden'\n");
    } else printf("TEST NO PASADO: 'Arbol deja de aplicar la funcion correctamente en el recorrido postorden'\n");
    arbol_destruir(arbol);
}

int main(){

    //arbol_vacio
    DadoUnABBVacio_CuandoSePreguntaSiEstaVacio_EntoncesDevuelveTrue();
    DadoUnABBNoVacio_CuandoSePreguntaSiEstaVacio_EntoncesDevuelveFalse();
    //arbol_buscar
    DadounABBConElementos_CuandoSePideBuscarUnElementoQueNoSeEncuentraEnElABB_EntoncesDevuelveNull();
    //test de volumen
    DadoUnABBCon1000Elementos_CuandoSeBorranLos1000ElementosYSePreguntaSiEstaVacio_EntoncesDevuelveTrue();
    //arbol_raiz
    DadoUnABBVacio_CuandoSePideLaRaiz_EntoncesDevuelveNull();
    DadoUnABBCon5Elementos_CuandoSePideLaRaiz_EntoncesDevuelveElPrimerElementoInsertardo();
    //abb_borrar
    DadoUnABBNoVacio_CuandoSePideBorrarUnNodoHoja_EntoncesLoBorraCorrectamenteYDevuelve0();
    DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConUnHijoDerecho_EntoncesLoBorraCorrectamenteYDevuelve0();
    DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConUnHijoIzquierdo_EntoncesLoBorraCorrectamenteYDevuelve0();
    DadoUnABBNoVacio_CuandoSePideBorrarUnNodoConDosHijos_EntoncesLoBorraCorrectamenteYDevuelve0();
    DadoUnABBNoVacio_CuandoSePideBorrarLaRaizConDosHijos_EntoncesLaBorraCorrectamenteYDevuelve0();
    DadoUnABBNoVacio_CUandoSePideBorrarUnElementoNoAlmacenado_EntoncesDevuelveError();
    //arbol_recorrido's...
    DadoUnABBNoVacio_CuandoSePideUnRecorridoInorden_EntoncesElArrayEsLlenadoCorrectamente();
    DadoUnABBNoVacio_CuandoSePideUnRecorridoPreorden_EntoncesElArrayEsLlenadoCorrectamente();
    DadoUnABBNoVacio_CuandoSePideUnRecorridoPostorden_EntoncesElArrayEsLlenadoCorrectamente();
    //abb_con_cada_elemento
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoInorden_EntoncesDevuelve10();
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoPreorden_EntoncesDevuelve10();
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosConRecorridoPostorden_EntoncesDevuelve10();
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoInorden_EntoncesDevuelve6();
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoPreorden_EntoncesDevuelve6();
    DadoUnABBConElementosDel0Al4_CuandoSePideLaSumaDeTodosLosElementosHastaEl3ConRecorridoPostorden_EntoncesDevuelve8();

    return 0;
}
