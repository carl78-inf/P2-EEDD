#ifndef LISTA_H
#define LISTA_H

#include <Venta.h>

class NodoLista
{
    private:
        int valor;
        NodoLista *siguiente;
        friend class Lista;

    public:
        NodoLista(int v, NodoLista *sig = NULL)
        {
            valor = v;
            siguiente = sig;
        }
};

class Lista
{
    private:
        NodoLista *cabeza;
        NodoLista *ultimo;
        int longitud;

        void insertarNodoInicio(int v);
        void insertarNodoFin(int v);
        void insertarNodoIntermedio(int pos, int v);

        void obtenerNodoInicio();
        void obtenerNodoFin();
        void obtenerNodoIntermedio(int pos);

        void borrarNodoInicio();
        void borrarNodoFin();
        void borrarNodoIntermedio(int pos);

    public:
        Lista();
        ~Lista();
        void insertar(int v, int pos = -1);
        int obtener(int pos);
        int buscar(int v);
        void borrar(int v);
        bool esVacia();
        int getLongitud();
};

#endif // LISTA_H
