ENTREGA: Entrega de la implementación del TDA Lista y un iterador externo, implementado con primitivas del TDA Pila como vector dinámico. Además se adjunta la implementación de la Pila para su correcto funcionamiento y archivos .c con ejemplos de como utilizar las funciones de la lista. 

COMPILAR/CORRER: Para utilizar este TDA en un archivo .c, compilar escribiendo el siguiente comando en la consola: "gcc lista.c pila.c [nombre_archivo_.c].c -o [nombre]"
Para ejecutar el programa usar el comando: "./[nombre]".
Ejemplo: "gcc lista.c pila.c ejemplo_1.c -o ejemplo_1"
		 "./ejemplo_1"

ESTRUCTURAS: En esta implementación en particular, la estructura de la lista esta compuesta solamente por un puntero a una pila, ya que solo se utilizan primitivas de este TDA para desarrollar las funciones. 
Con respecto al iterador, su estructura es un puntero a la lista sobre la cual va a iterar y un contador de la posicion actual.
En cuanto a la estructura de la Pila, está compuesta por un puntero a un vector de punteros a void, y dos contadores, uno para su tamaño actual, y uno para la cantidad de elementos ingresados.

ALGORITMOS: tranferir_elementos: Se utiliza este algoritmo frecuentemente para avanzar a distintas posiciones de la pila, ya que con primitivas solo podemos acceder a la última posición. 
								 Conciste en transferir todos los elementos de la pila a una auxiliar, hasta dejar en último lugar la posición sobre la cual queremos operar.
			unir_pilas: Una variación del algoritmo anterior. Utilizado para vaciar la pila auxiliar en la pila original, devolviendo todos los elementos a la lista en su respectivo orden luego de operar.

CONSIDERACIONES: * El TDA Pila está implementado como un vector dinámico con la siguiente politica de redimension:
						* Si el vector está lleno, al apilar, el tamaño del vector se duplica.
						* Si el vector tiene menos del 25% ocupado y su tamaño es mayor al tamaño inicial, al desapilar, el vector se reduce a la mitad.
						
				 * Esta implementación de la lista no soporta estructuras que a su vez utilicen memoria dinámica (La pila no recibe una función "destructor").

				 * Se han tenido en cuenta los siguientes casos bordes:
						* Insertar el elemento NULL.
						* Insertar en una posicion inexistente.
						* Borrar en una lista vacía.
						* Borrar de una posición inexistente
						* Borrar de la primera posición.
						* Borrar de la ultima posición.
						* Buscar elemento de una posición inexistente.
						* Buscar elemento en una lista vacía.
						* Pedir siguiente a un iterador ubicado en la ultima posición.
						* Pedir siguiente a un iterador de una lista vacía.
	
CONVENCIONES UTILIZADAS: * Si no se especifica una posicion tanto en la inserción como en el borrado, entonces se trabaja sobre la última posición de la lista.
					     * Si las posiciones indicadas al insertar y borrar no existen, entonces se inserta/borra en la ultima posición.
					     * Si la posicion indicada en la busqueda no existe, entonces devuelve NULL.
					     * En caso de ERROR se devuelve -1, y los casos de EXITO devuelven 0.
					     * En la insercion en posicion, se considera a "0" como la posicion antes del primer elemento, "1" entre el primer y segundo elemento, etc...
					     
En cuanto al tamaño soportado, se han hecho pruebas con exito de inserción, busqueda y borrado con hasta 10000 elementos.
