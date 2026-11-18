#ifndef LISTA_H
#define LISTA_H

#include <Venta.h>

//Clase NodoLista
class NodoLista
{
    private:
        Venta valor;          //Valor del elemento
        NodoLista *siguiente; //Puntero al siguiente Nodo
        friend class Lista;

    public:
        //Constructor con parámetros
        NodoLista(Venta v, NodoLista *sig = NULL)
        {
            valor = v;
            siguiente = sig;
        }
};

//Clase Lista
class Lista
{
    private:
        NodoLista *cabeza; //Puntero al primer elemento
        NodoLista *ultimo; //Puntero al último elemento
        int longitud;      //Longitud

        //Métodos auxiliares para inserción y eliminación de nodos
        void insertarNodoInicio(Venta v);              //Inserta un elemento al inicio de la Lista
        void insertarNodoFin(Venta v);                 //Inserta un elemento al final de la Lista
        void insertarNodoIntermedio(Venta v, int pos); //Inserta un elemento intermedio en la Lista en la posición indicada

        void borrarNodoInicio();            //Borra el primer elemento de la Lista
        void borrarNodoFin();               //Borra el último elemento de la Lista
        void borrarNodoIntermedio(int pos); //Borra el elemento intermedio de la Lista en la posición indicada

    public:
        Lista();  //Constructor
        ~Lista(); //Destructor

        bool esVacia();    //Devuelve True si la Lista es vacía
        int getLongitud(); //Devuelve la longitud de la Lista

        void insertar(Venta v, int pos = -1); //Inserta un elemento en la posición indicada (por defecto al final = -1) (0 - longitud-1)
        void borrar(int pos);                 //Borra el elemento en la posición indicada (0 - longitud-1)
        Venta obtener(int pos);               //Obtene el elemento en la posición indicada (0 - longitud-1)
        int buscar(Venta v);                  //Devuelve la posición de la primera aparición del elemento (-1 si no lo encuentra)
};

#endif // LISTA_H
