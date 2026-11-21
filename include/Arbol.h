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

        //Métodos auxiliares para eliminar un nodo y mostrar por pantalla
        void eliminarNodo(NodoArbol *nodo, NodoArbol *padre, bool derecha);
        void mostrarNodoInOrden(NodoArbol *nodo);

        //Método auxiliar para eliminar el árbol
        void Podar(NodoArbol *nodo);


    public:
        Arbol();  //Constructor
        ~Arbol(); //Destructor

        bool esVacio(); //Devuelve True si el Arbol es vacío
        bool esHoja();  //Devuelve True si el Arbol es una hoja (no tiene hijos)

        int getNodos(); //Devuelve el número de nodos en el Arbol

        void insertar(Centro c);  //Inserta un centro en el Arbol de forma ordenada

        void eliminar(int id);    //Elimina el centro con el identificador dado

        Centro obtener(int id);   //Devuelve el centro con el identificador dado
        bool estaEnArbol(int id); //Devuelve True si el identificador está en el Arbol

        void mostrar(); //Muestra el Arbol por pantalla en formato de tabla (inorden)
};

#endif // ARBOL_H
