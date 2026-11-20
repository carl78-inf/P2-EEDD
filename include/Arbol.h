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


class Arbol
{
    private:
        NodoArbol *raiz; //Raíz del arbol
        int altura;      //Altura


    public:
        Arbol();

       /* ~Arbol() { podar(raiz); }
        void buscarNodo (char v);
        void insertarNodo (char v);
        void borrarNodo (char v);
        bool esVacio(pNodo nodo) { return r==NULL; }
        bool esHoja(pNodo nodo) { return !nodo->derecho && !nodo>izquierdo; }
        int numeroNodos();
        int getAlturaArbol();
        char getValorActual() { return actual->dato; }
        void esRaiz() { actual = raiz; }
        void inOrden(Nodo *nodo);
        void preOrden(Nodo *nodo);
        void postOrden(Nodo *nodo);*/

    //lista vacía, añadir por la izquierda, resto (eliminar primero), eliminar último, obtener primero, último, comprobar si es vacía, lista unitaria

};

#endif // ARBOL_H
