#include "Lista.h"

//Constructor
Lista::Lista()
{
    cabeza = NULL; //Puntero cabeza a NULL
    ultimo = NULL; //Puntero ultimo a NULL
    longitud = 0;  //Longitud a 0
}

//-----------------------------------------------------------------------------------------------//

//Destructor
Lista::~Lista()
{
    NodoLista *aux; //Nodo auxiliar para eliminar los nodos

    //Mientras queden nodos
    while(cabeza)
    {
        aux = cabeza;               //Nodo auxiliar apunta al primer nodo
        cabeza = cabeza->siguiente; //Cabeza apunta al siguiente
        delete aux;                 //Eliminamos el nodo apuntado por auxiliar
    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True si la Lista vacía
bool Lista::esVacia()
{
    return (cabeza == NULL)
        && (ultimo == NULL);
}

//-----------------------------------------------------------------------------------------------//

//Devuelve la longitu de la Lista
int Lista::getLongitud()
{
    return longitud;
}

//-----------------------------------------------------------------------------------------------//

//Inserta un nodo al inicio de la Lista
void Lista::insertarNodoInicio(Venta v)
{
    NodoLista *nuevo = new NodoLista(v); //Puntero a un nuevo nodo

    //Si está vacía, los dos punteros apuntan al nuevo nodo
    if(esVacia())
    {
        cabeza = nuevo;
        ultimo = nuevo;
    }

    //Si no
    else
    {
        nuevo->siguiente = cabeza; //Nuevo nodo apunta al primer nodo de la lista
        cabeza = nuevo;            //Puntero cabeza apunta al nuevo nodo
    }

    longitud++; //Incrementamos la longitud
}

//Inserta un nodo al final de la Lista
void Lista::insertarNodoFin(Venta v)
{
    NodoLista *nuevo = new NodoLista(v); //Puntero a un nuevo nodo

    //Si está vacía, los dos punteros apuntan al nuevo nodo
    if(esVacia())
    {
        cabeza = nuevo;
        ultimo = nuevo;
    }

    //Si no
    else
    {
        ultimo->siguiente = nuevo; //Último nodo apunta al nuevo nodo
        ultimo = nuevo;            //Puntero ultimo apunta al nuevo nodo
    }

    longitud++; //Incrementamos la longitud
}

//Inserta un nodo en una posición intermedia de la Lista
void Lista::insertarNodoIntermedio(Venta v, int pos)
{
    //Error si no es una posición valida
    if(pos < 0 || pos >= longitud)
    {
        cout << "Error: posicion fuera de los limites de la lista";
    }

    //Error si no es una posición intermedia de la lista
    else if(pos == 0 || pos == longitud - 1)
    {
        cout << "Error: no es una posicion intermedia";
    }

    //Si es una posición intermedia de la lista
    else
    {
        int contador = 0;        //Inicializamos un contador a cero
        NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

        //Avanzamos en la lista hasta la posición anterior a la indicada
        while(contador < pos - 1)
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
            contador++;           //Incrementamos el contador
        }

        //El nuevo nodo apunta a la posición siguiente de aux
        NodoLista *nodo = new NodoLista(v, aux->siguiente);

        aux->siguiente = nodo; //El nodo apuntado por aux apunta al nuevo nodo
    }

    longitud++; //Incrementamos la longitud
}

//Inserta un nodo en la posición indicada de la Lista
void Lista::insertar(Venta v, int pos)
{
    if(pos == -1) pos = (longitud == 0)? (0) : (longitud - 1); //Por defecto, se inserta al final

    //Error si no es una posición valida (y != -1)
    if(pos < 0 || pos >= longitud)
    {
        cout << "Error: posicion fuera de los limites de la lista";
    }

    //Si es la primera posición de la lista
    else if(pos == 0)
    {
        insertarNodoInicio(v);
    }

    //Si es la última posición de la lista
    else if(pos == longitud - 1)
    {
        insertarNodoFin(v);
    }

    //Si es una posición intermedia
    else
    {
        insertarNodoIntermedio(v, pos);
    }

    longitud++; //Incrementamos la longitud
}

//-----------------------------------------------------------------------------------------------//

//Elimina el nodo al inicio de la Lista
void Lista::borrarNodoInicio()
{
    if(!esVacia())
    {
        NodoLista *aux = cabeza; //Puntero auxiliar que apunta al primer nodo

        //Si solo hay un elemento, ponemos todos los punteros a null y lo eliminamos
        if((cabeza == ultimo) && (cabeza->siguiente == NULL))
        {
            cabeza = NULL;
            ultimo = NULL;
            delete(aux);
        }

        //Si no, eliminaremos el primer elemento Y primero apuntará al siguiente nodo
        else
        {
            cabeza = cabeza->siguiente;
            aux->siguiente = NULL;
            delete(aux);
        }

        longitud--; //Decrementamos la longitud
    }
}

//Elimina el nodo al final de la Lista
void Lista::borrarNodoFin()
{
    if(!esVacia())
    {
        NodoLista *aux = cabeza; //Puntero auxiliar que apunta al primer nodo

        //Si solo hay un elemento, ponemos todos los punteros a null y lo eliminamos
        if((cabeza == ultimo) && (cabeza->siguiente == NULL))
        {
            cabeza = NULL;
            ultimo = NULL;
            delete(aux);
        }

        //Si no, eliminaremos el primer elemento Y primero apuntará al siguiente nodo
        else
        {
            cabeza = cabeza->siguiente;
            aux->siguiente = NULL;
            delete(aux);
        }

        longitud--; //Decrementamos la longitud
    }
}

void Lista::borrarNodoIntermedio(int pos)
{
    //Error si no es una posición valida
    if(pos < 0 || pos >= longitud)
    {
        cout << "Error: posicion fuera de los limites de la lista";
    }

    //Error si no es una posición intermedia de la lista
    else if(pos == 0 || pos == longitud - 1)
    {
        cout << "Error: no es una posicion intermedia";
    }

    //Si es una posición intermedia de la lista
    else
    {
        int contador = 0;        //Inicializamos un contador a cero
        NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

        //Avanzamos en la lista hasta la posición anterior a la indicada
        while(contador < pos - 1)
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
            contador++;           //Incrementamos el contador
        }

        //El nodo apuntado por aux apuntará al siguiente de la posición a eliminar
        aux->siguiente = aux->siguiente->siguiente;

        aux->siguiente = nodo; //El nodo apuntado por aux apunta al nuevo nodo
    }

    longitud--; //Decrementamos la longitud
}

//Borra el nodo en la posición indicada (0 - longitud-1)
void Lista::borrar(int pos)
{
    //Error si no es una posición valida (y != -1)
    if(pos < 0 || pos >= longitud)
    {
        cout << "Error: posicion fuera de los limites de la lista";
    }

    //Si es la primera posición de la lista
    else if(pos == 0)
    {
        insertarNodoInicio(v);
    }

    //Si es la última posición de la lista
    else if(pos == longitud - 1)
    {
        insertarNodoFin(v);
    }

    //Si es una posición intermedia
    else
    {
        insertarNodoIntermedio(v, pos);
    }

    longitud++; //Incrementamos la longitud
}

//-----------------------------------------------------------------------------------------------//

//Devuelve el elemento en la posición indicada
Venta Lista::obtener(int pos)
{
    int contador = 0; //Inicializamos un contador a cero
    NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

    //Avanzamos en la lista hasta la posición indicada
    while(contador < pos - 1)
    {
        aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
        contador++;           //Incrementamos el contador
    }

    return aux->valor; //Devolvemos el valor del nodo apuntado por aux
}

//-----------------------------------------------------------------------------------------------//

//Devuelve la posición de la primera aparición del elemento (-1 si no lo encuentra)
int Lista::buscar(Venta v)
{
    bool encontrado = false; //Inicializamos encontrado a False
    int contador = 0;         //Inicializamos un contador a cero
    NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

    //Avanzamos el puntero auxiliar hasta encontrar el elemento o llegar al final de la lista
    while(!encontrado && aux->siguiente != NULL)
    {
        //Si lo encontramos
        if(aux->valor.id_venta == v.id_venta)
        {
            encontrado = true;
        }

        //Si no
        else
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
            contador++;           //Incrementamos el contador
        }
    }

    //Si lo hemos encontrado
    if(encontrado)
    {
        return contador; //Devolvemos la posición
    }

    //Si no
    else
    {
        return -1; //Devolvemos -1
    }
}
