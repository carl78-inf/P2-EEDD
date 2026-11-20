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
        void borrarNodoInicio();            //Borra el primer elemento de la Lista
        void borrarNodoFin();               //Borra el último elemento de la Lista
        void borrarNodoIntermedio(int pos); //Borra el elemento intermedio de la Lista en la posición indicada

    public:
        Lista();  //Constructor
        ~Lista(); //Destructor

        bool esVacia();    //Devuelve True si la Lista es vacía
        int getLongitud(); //Devuelve la longitud de la Lista

        void insertar(Venta v, int pos = -1); //Inserta un elemento en la posición indicada (por defecto al final = -1) (0 - longitud-1)
        void eliminar(int pos = 0);           //Elimina el elemento en la posición indicada (por defecto la cabeza) (0 - longitud-1)
        void vaciar();                        //Elimina todos los elementos de la lista
        void modificar(Venta v, int pos);     //Modifica el elemento en la posición indicada (0 - longitud-1)
        void copiar(Lista& l);                //Realiza una copia de la lista pasada como argumento (arreglar errores de asignación)

        Venta obtener(int pos);               //Obtene el elemento en la posición indicada (0 - longitud-1)

        int buscar(string id);                //Devuelve la posición de la primera aparición del elemento (-1 si no lo encuentra)
        bool estaEnLista(string id);          //Devuelve True si la venta está en la lista

        void concatenar(Lista& l);             //Añade la lista pasada como argumento al final de la lista

        void mostrar();                       //Mostrar la lista por pantalla en formato de tabla
};

#endif // LISTA_H
