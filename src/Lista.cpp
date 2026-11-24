#include "Lista.h"

//Constructor
Lista::Lista()
{
    cabeza = NULL; //Puntero cabeza a NULL
    ultimo = NULL; //Puntero ultimo a NULL
    longitud = 0;  //Longitud a 0
}

//Constructor de copia: crea una lista nueva e independiente de la recibida
Lista::Lista(const Lista& l)
{
    cabeza = NULL; //Puntero cabeza a NULL
    ultimo = NULL; //Puntero ultimo a NULL
    longitud = 0;  //Longitud a 0

    NodoLista *aux = l.cabeza; //Puntero auxiliar a la cabeza de la lista recibida

    //Copiamos cada venta al final de la nueva lista
    while(aux != NULL)
    {
        insertar(aux->valor); //Insertamos una copia de la venta
        aux = aux->siguiente; //Siguiente nodo
    }
}

//Operador de asignacion: vacia la lista y copia los elementos de la recibida
Lista& Lista::operator=(const Lista& l)
{
    //Evitamos el caso de asignar una lista a si misma
    if(this != &l)
    {
        vaciar(); //Vaciamos la lista actual

        NodoLista *aux = l.cabeza; //Puntero auxiliar a la cabeza de la lista recibida

        //Copiamos cada venta al final de la lista
        while(aux != NULL)
        {
            insertar(aux->valor); //Insertamos una copia de la venta
            aux = aux->siguiente; //Siguiente nodo
        }
    }

    return *this; //Devolvemos la lista actual
}

//Destructor
Lista::~Lista()
{
    NodoLista *aux; //Nodo auxiliar para eliminar los nodos

    //Mientras queden nodos
    while(cabeza)
    {
        aux = cabeza;               //Nodo auxiliar apunta al primer nodo
        cabeza = cabeza->siguiente; //Cabeza apunta al siguiente
        delete(aux);                //Eliminamos el nodo apuntado por auxiliar
        aux = NULL;                 //Puntero auxiliar a NULL

    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True si la Lista es vacía
bool Lista::esVacia()
{
    return (cabeza == NULL)
           && (ultimo == NULL);
}

//Devuelve la longitud de la Lista
int Lista::getLongitud()
{
    return longitud;
}

//-----------------------------------------------------------------------------------------------//

//Inserta un nodo en la posición indicada de la Lista (por defecto al final)
void Lista::insertar(Venta v, int pos)
{
    //Validamos que la posición sea válida
    if (pos != -1 && (pos < 0 || pos >= longitud))
    {
        cout << "Error: Posicion fuera de los limites de la lista." << endl;
    }
    else
    {
        NodoLista *nuevo = new NodoLista(v); //Puntero al nuevo nodo

        //Si está vacía
        if(esVacia())
        {
            //Los dos punteros apuntan al nuevo nodo
            cabeza = nuevo;
            ultimo = nuevo;
        }

        //Si se inserta al inicio de la lista
        else if(pos == 0)
        {
            nuevo->siguiente = cabeza; //Nuevo nodo apunta al primer nodo de la lista
            cabeza = nuevo;            //Puntero cabeza apunta al nuevo nodo
        }

        //Si se inserta al final de la lista
        else if(pos == -1)
        {
            ultimo->siguiente = nuevo; //Último nodo apunta al nuevo nodo
            ultimo = nuevo;            //Puntero ultimo apunta al nuevo nodo
        }

        //Si se inserta en una posición intermedia
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

            //Insertamos el nuevo nodo entre aux y aux->siguiente
            nuevo->siguiente = aux->siguiente; //El nuevo nodo apunta a aux->siguiente
            aux->siguiente = nuevo;            //El nodo apuntado por aux apunta al nuevo nodo
        }

        longitud++; //Incrementamos la longitud
    }
}

//Elimina el nodo en la posición indicada (por defecto elimina la cabeza -> 0)
void Lista::eliminar(int pos)
{
    //Validamos que la posición sea válida
    if (pos < 0 || pos >= longitud)
    {
        cout << "Error: Posicion fuera de los limites de la lista." << endl;
    }
    else
    {
        NodoLista *aux = cabeza; //Puntero auxiliar que apunta al primer nodo

        //Si solo hay un elemento
        if((cabeza == ultimo) && (cabeza->siguiente == NULL))
        {
            cabeza = NULL; //Cabeza a NULL
            ultimo = NULL; //Ultimo a NULL
            delete(aux);   //Eliminamos el nodo
        }

        //Si eliminamos el primer elemento
        else if(pos == 0)
        {
            cabeza = cabeza->siguiente; //Cabeza apuntará al siguiente nodo
            aux->siguiente = NULL;      //El nodo a eliminar apuntará a NULL
            delete(aux);                //Eliminamos el nodo
        }

        //Si eliminamos un nodo distinto
        else
        {
            int contador = 0;        //Inicializamos un contador a cero

            //Avanzamos en la lista hasta la posición anterior a la indicada
            while(contador < pos - 1)
            {
                aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
                contador++;           //Incrementamos el contador
            }

            NodoLista *elim = aux->siguiente; //Puntero al nodo que queremos eliminar
            aux->siguiente = elim->siguiente; //Nodo anterior apuntará al siguiente a eliminar

            //Si es el ultimo elemento
            if(elim->siguiente == NULL)
            {
                ultimo = aux; //Ultimo apuntará al nodo anterior
            }

            delete(elim);                     //Eliminamos el nodo
        }

        longitud--; //Decrementamos la longitud
    }
}

//Elimina todos los elementos de la lista
void Lista::vaciar()
{
    //Mientras queden nodos
    while(!esVacia())
    {
        eliminar(); //Eliminamos la cabeza
    }
}

//Modifica la Venta en la posición indicada
void Lista::modificar(Venta v, int pos)
{
    //Validamos que la posición sea válida
    if (pos < 0 || pos >= longitud)
    {
        cout << "Error: Posicion fuera de los limites de la lista." << endl;
    }

    else
    {
        int contador = 0; //Inicializamos un contador a cero
        NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

        //Avanzamos en la lista hasta la posición indicada
        while(contador < pos)
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
            contador++;           //Incrementamos el contador
        }

        aux->valor = v; //Cambiamos el valor del nodo por la nueva venta
    }
}

//Realiza una copia de la lista pasada como argumento (arreglar errores de asignación)
void Lista::copiar(Lista& l)
{
    vaciar(); //Vaciamos la lista

    NodoLista *aux = l.cabeza; //Puntero auxiliar a la cabeza de l

    //Para cada elemento de la lista l
    while(aux != NULL)
    {
        insertar(aux->valor); //Lo insertamos al final de la lista
        aux = aux->siguiente; //Siguiente nodo
    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve el elemento en la posición indicada
Venta Lista::obtener(int pos)
{
    //Validamos que la posición sea válida
    if (pos < 0 || pos >= longitud)
    {
        cout << "Error: Posicion fuera de los limites de la lista." << endl;
        return Venta(); //Devuelve una venta vacía por seguridad
    }

    else
    {
        int contador = 0; //Inicializamos un contador a cero
        NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

        //Avanzamos en la lista hasta la posición indicada
        while(contador < pos)
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
            contador++;           //Incrementamos el contador
        }

        return aux->valor; //Devolvemos el valor del nodo apuntado por aux
    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve la posición de la primera aparición de la Venta con ese id (-1 si no lo encuentra)
int Lista::buscar(string id)
{
    bool encontrado = false; //Inicializamos encontrado a False
    int contador = 0;         //Inicializamos un contador a cero
    NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

    //Avanzamos el puntero auxiliar hasta encontrar el elemento o llegar al final de la lista
    while(!encontrado && aux != NULL)
    {
        //Si lo encontramos
        if(aux->valor.id_venta == id)
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

//Devuelve True si la Venta con ese id está en la lista
bool Lista::estaEnLista(string id)
{
    bool encontrado = false; //Inicializamos encontrado a False
    NodoLista *aux = cabeza; //Puntero auxiliar apunta a la cabeza

    //Avanzamos el puntero auxiliar hasta encontrar el elemento o llegar al final de la lista
    while(!encontrado && aux != NULL)
    {
        //Si lo encontramos
        if(aux->valor.id_venta == id)
        {
            encontrado = true;
        }

        //Si no
        else
        {
            aux = aux->siguiente; //Avanzamos el puntero al siguiente nodo
        }
    }

    return encontrado; //Se devuelve True si se ha encontrado la venta
}

//-----------------------------------------------------------------------------------------------//

//Añade la lista pasada como argumento al final de la lista
void Lista::concatenar(Lista& l)
{
    NodoLista *aux; //Puntero auxiliar para recorrer l
    Lista copia;
    copia.copiar(l);
    aux = copia.cabeza; //Puntero auxiliar a la cabeza de la copia

    //Para cada elemento de la lista l
    while(aux != NULL)
    {
        insertar(aux->valor); //Lo insertamos al final de la lista
        aux = aux->siguiente; //Siguiente nodo
    }
}

//-----------------------------------------------------------------------------------------------//

//Muestra la lista por pantalla en formato de tabla
void Lista::mostrar()
{
    //Imprimimos la cabecera de la tabla
    cout << "+---------------------------------------------------------------------------+" << endl
         << "| ID Centro | ID Venta | Codigo Pizza |  Categoria  | Unidades |   Fecha    |" << endl
         << "+---------------------------------------------------------------------------+" << endl;

    //Si no está vacía, imprimimos cada elemento de la Lista
    if(!esVacia())
    {
        for (NodoLista* aux = cabeza; aux != NULL; aux = aux->siguiente)
        {
            Venta v = aux->valor; //Venta a imprimir
            mostrarFila(v);       //Imprimimos cada venta
            cout << endl;
        }

    }

    //Si está vacía, imprimimos una fila vacía
    else cout << "|           |          |              |             |          |            |" << endl;

    //Imprimimos el final de la tabla
    cout << "+---------------------------------------------------------------------------+" << endl
         << "Longitud: " << getLongitud() << endl;
}
