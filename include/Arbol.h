#ifndef ARBOL_H
#define ARBOL_H

#include <Centro.h>

//Clase NodoAB
class NodoArbol
{
private:
    Centro valor;         //Valor del elemento
    NodoArbol *izquierda; //Puntero al Nodo hijo izquierdo
    NodoArbol *derecha;   //Puntero al Nodo hijo derecho
    friend class Arbol;

public:
    //Constructor con parámetros
    NodoArbol(Centro v, NodoArbol *izq = NULL, NodoArbol *der = NULL)
    {
        valor = v;
        izquierda = izq;
        derecha = der;
    }
};

//Clase Árbol Binario de Búsqueda
class Arbol
{
private:
    NodoArbol *raiz; //Raíz del arbol
    int nodos;       //Número de nodos del árbol

    //Método auxiliar para eliminar el árbol
    void Podar(NodoArbol *nodo);

    //Método auxiliar para obtener los IDs y localidades de un nodo (subarbol)
    void getIDsNodo(NodoArbol *nodo, int ids[], int& indice);
    /*void getLocalidadesNodo(NodoArbol *nodo, int Localidad localidades[], int& indice);*/

    //Métodos auxiliares para eliminar un nodo, buscar una venta y mostrar por pantalla
    void eliminarNodo(NodoArbol *nodo, NodoArbol *padre, bool derecha);
    bool buscarVentaNodo(NodoArbol *nodo, string id, Venta& v);
    bool ventaEnNodo(NodoArbol *nodo, string id);
    void mostrarNodoInOrden(NodoArbol *nodo);

public:
    Arbol();  //Constructor
    ~Arbol(); //Destructor

    bool esVacio(); //Devuelve True si el Arbol es vacío
    bool esHoja();  //Devuelve True si el Arbol es una hoja (no tiene hijos)

    int getNodos(); //Devuelve el número de nodos en el Arbol

    void getIDs(int ids[]);                       //Introduce todos los ID de los centros del Arbol en el array ids[]
    /*void getLocalidades(Localidad localidades[]); //Introduce todas las localidades de los centros del Arbol en el array localidades[]*/

    void insertar(Centro& c);         //Inserta un centro en el Arbol de forma ordenada
    void insertar(Venta v);           //Inserta una venta en el centro correspondiente del Arbol al final

    void eliminar(int id);            //Elimina el centro con el identificador dado

    bool buscar(int id, Centro& c);   //Devuelve True y el centro con el id buscado en c si se ha encontrado (False si no se ha encontrado)
    bool buscar(string id, Venta& v); //Devuelve True y la venta con el id buscado en v (False si no se ha encontrado)

    bool estaEnArbol(int id);         //Devuelve True si el centro con el identificador está en el Arbol
    bool estaEnArbol(string id);      //Devuelve True si la venta con el identificador está en el Arbol

    void mostrar();                   //Muestra el Arbol por pantalla en formato de tabla (inorden)
};

#endif // ARBOL_H
