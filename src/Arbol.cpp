#include "Arbol.h"

//Constructor
Arbol::Arbol()
{
    raiz = NULL; //Puntero raiz a NULL
    nodos = 0;   //Número de nodos a 0
}

//Destructor
Arbol::~Arbol()
{
    Podar(raiz);
}

//Elimina todos los nodos a partir de uno incluido
void Arbol::Podar(NodoArbol *nodo)
{
    //Algoritmo recursivo, recorrido en postorden
    if(nodo)
    {
        Podar(nodo->izquierda); //Podar izquierdo
        Podar(nodo->derecha);   //Podar derecho
        delete(nodo);           //Eliminar nodo
        nodo = NULL;            //Puntero nodo a NULL
    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True si el Arbol es vacío
bool Arbol::esVacio()
{
    return raiz == NULL;
}

//Devuelve True si el Arbol es una hoja (no tiene hijos)
bool Arbol::esHoja()
{
    return (raiz->izquierda == NULL) &&
           (raiz->derecha == NULL);
}

//-----------------------------------------------------------------------------------------------//

//Devuelve el número de nodos en el Arbol
int Arbol::getNodos()
{
    return nodos;
}

//-----------------------------------------------------------------------------------------------//

//Introduce todos los ID de los centros del subarbol en el array ids[] (preorden)
void Arbol::getIDsNodo(NodoArbol *nodo, int ids[], int& indice)
{
    //Si el nodo no es nulo
    if(nodo != NULL)
    {
        ids[indice] = nodo->valor.id_centro; //Insertamos el id_centro
        indice++;                            //Incrementamos el indice

        getIDsNodo(nodo->izquierda, ids, indice); //Obtenemos los del hijo izquierdo
        getIDsNodo(nodo->derecha, ids, indice);   //Obtenemos los del hijo derecho
    }
}

//Introduce todos los ID de los centros del Arbol en el array ids[] //Cuidado con el tamaño del array
void Arbol::getIDs(int ids[])
{
    int indice = 0;
    getIDsNodo(raiz, ids, indice);
}

//-----------------------------------------------------------------------------------------------//

//Inserta un nodo de forma ordenada en el Arbol
void Arbol::insertar(Centro& c)
{
    NodoArbol *nuevo = new NodoArbol(c); //Puntero al nuevo nodo

    //Si está vacío
    if(esVacio())
    {
        raiz = nuevo; //Raiz apunta al nuevo nodo
    }

    //Si no tiene hijos
    else if(esHoja())
    {
        //Si el nuevo nodo es menor o igual que la raiz
        if(c.id_centro <= raiz->valor.id_centro)
        {
            raiz->izquierda = nuevo; //Insertamos en el hijo izquierdo
        }

        //Si el nuevo nodo es mayor que la raiz
        else
        {
            raiz->derecha = nuevo; //Insertamos en el hijo derecho
        }
    }

    //Si no
    else
    {
        NodoArbol *aux = raiz;  //Puntero auxiliar a la raiz del arbol
        bool insertado = false; //Valor para detectar cuando se ha insertado el nodo

        //Mientras no se haya insertado
        while(!insertado)
        {
            //Si el nuevo nodo es menor o igual que aux
            if(c.id_centro <= aux->valor.id_centro)
            {
                //Si el hijo izquierdo es NULL
                if(aux->izquierda == NULL)
                {
                    aux->izquierda = nuevo; //Insertamos en el hijo izquierdo
                    insertado = true;       //Insertado
                }

                //Si no, comprobamos con el siguiente
                else
                {
                    aux = aux->izquierda; //Aux a su hijo izquierdo
                }

            }

            //Si el nuevo nodo es mayor que aux
            else
            {
                //Si el hijo derecho es NULL
                if(aux->derecha == NULL)
                {
                    aux->derecha = nuevo; //Insertamos en el hijo derecho
                    insertado = true;     //Insertado
                }

                //Si no, comprobamos con el siguiente
                else
                {
                    aux = aux->derecha; //Aux a su hijo derecho
                }
            }
        }
    }

    nodos++; //Incrementamos el número de nodos
}

//Inserta una venta en el centro correspondiente del Arbol al final
void Arbol::insertar(Venta v)
{
    NodoArbol *aux = raiz;  //Puntero auxiliar a la raiz del arbol
    bool insertado = false; //Valor para determinar si se ha insertado

    //Buscamos el nodo del centro de la venta
    while(!insertado && aux != NULL)
    {
        if(aux->valor.id_centro == v.id_centro)
        {
            aux->valor.ventas.insertar(v); //Se inserta al final de la lista
            insertado = true;
        }
        else if(v.id_centro < aux->valor.id_centro)
        {
            aux = aux->izquierda;
        }
        else
        {
            aux = aux->derecha;
        }
    }

    //Si no se ha encontrado el centro asociado
    if(!insertado)
    {
        cout << "El centro asociado a la venta no se encuentra en el Arbol" << endl;
    }
}

//-----------------------------------------------------------------------------------------------//

//Elimina un nodo del arbol
void Arbol::eliminarNodo(NodoArbol *nodo, NodoArbol *padre, bool derecha)
{
    //Si no tiene ningún hijo
    if((nodo->izquierda == NULL) && (nodo->derecha == NULL))
    {
        //Si es el nodo raiz
        if(padre == NULL)
        {
            raiz = NULL; //Raiz a NULL
        }

        //Si no
        else
        {
            //Ponemos el puntero del padre a NULL
            if(derecha)
            {
                padre->derecha = NULL; //Hijo derecho
            }
            else
            {
                padre->izquierda = NULL; //Hijo izquierdo
            }
        }

        delete(nodo); //Eliminamos el nodo
        nodo = NULL;  //Puntero nodo a NULL
    }

    //Si solo tiene el hijo derecho
    else if(nodo->izquierda == NULL)
    {
        //Si es el nodo raiz
        if(padre == NULL)
        {
            raiz = nodo->derecha; //Raiz al hijo derecho
        }

        //Si no
        else
        {
            //Ponemos el puntero del padre al hijo derecho
            if(derecha)
            {
                padre->derecha = nodo->derecha; //Hijo derecho padre
            }
            else
            {
                padre->izquierda = nodo->derecha; //Hijo izquierdo padre
            }

        }

        nodo->derecha = NULL; //Puntero al hijo a NULL
        delete(nodo); //Eliminamos el nodo
        nodo = NULL;  //Puntero nodo a NULL
    }

    //Si solo tiene el hijo izquierdo
    else if(nodo->derecha == NULL)
    {
        //Si es el nodo raiz
        if(padre == NULL)
        {
            raiz = nodo->izquierda; //Raiz al hijo izquierdo
        }

        //Si no
        else
        {
            //Ponemos el puntero del padre al hijo izquierdo
            if(derecha)
            {
                padre->derecha = nodo->izquierda; //Hijo derecho padre
            }
            else
            {
                padre->izquierda = nodo->izquierda; //Hijo izquierdo padre
            }
        }

        nodo->izquierda = NULL; // Limpiamos el puntero por seguridad
        delete(nodo); //Eliminamos el nodo
        nodo = NULL;  //Puntero nodo a NULL
    }

    //Si tiene los dos hijos
    else
    {
        NodoArbol *maximo = nodo->izquierda; //Puntero maximo al hijo izquierdo
        NodoArbol *padreMaximo = nodo;       //Padre específico para el máximo

        bool derechaMaximo = false; //Valor para saber si está a la derecha de su padreMaximo

        // Buscamos el mayor del hijo izquierdo (el más a la derecha)
        if (maximo->derecha != NULL)
        {
            derechaMaximo = true; //Vamos a la derecha

            while(maximo->derecha != NULL)
            {
                padreMaximo = maximo;     //Padre a maximo
                maximo = maximo->derecha; //Maximo al hijo de la derecha
            }
        }

        //Actualizamos el valor del nodo principal con el valor del máximo encontrado
        copiarCentro(maximo->valor, nodo->valor);

        //Eliminamos recursivamente el nodo máximo
        eliminarNodo(maximo, padreMaximo, derechaMaximo);
    }
}

//Elimina un Centro del arbol por su identificador
void Arbol::eliminar(int id)
{
    NodoArbol *padre = NULL; //Puntero al nodo padre
    bool derecha = false;    //Valor para determinar qué hijo es
    NodoArbol *aux = raiz;   //Puntero auxiliar a la raiz del arbol
    bool eliminado = false;  //Valor para detectar cuando se ha eliminado el nodo

    //Mientras no se haya eliminado y aún queden nodos posibles kjpor recorrer
    while(!eliminado && aux != NULL)
    {
        //Si aux apunta al nodo a eliminar
        if(aux->valor.id_centro == id)
        {
            eliminarNodo(aux, padre, derecha); //Lo eliminamos
            eliminado = true;                  //Eliminado
            nodos--;                           //Decrementamos el número de nodos
        }

        //Si no
        else
        {
            padre = aux; //Padre al nodo auxiliar

            //Si el nodo es menor o igual que aux
            if(id <= aux->valor.id_centro)
            {
                derecha = false;      //Vamos a la izquierda
                aux = aux->izquierda; //Aux a su hijo izquierdo
            }

            //Si el nodo es mayor que aux
            else
            {
                derecha = true;     //Vamos a la derecha
                aux = aux->derecha; //Aux a su hijo derecho
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True y el centro con el id buscado en c si se ha encontrado (False si no)
bool Arbol::buscar(int id, Centro& c)
{
    bool encontrado = false; //Valor para determinar si lo hemos encontrado
    NodoArbol *aux = raiz;   //Puntero auxiliar a la raiz del arbol

    while(!encontrado && aux != NULL)
    {
        //Si aux apunta al nodo con el identificador buscado
        if(aux->valor.id_centro == id)
        {
            copiarCentro(aux->valor, c); //Centro con el ID buscado en c
            encontrado = true;           //Encontrado
        }

        //Si no
        else
        {
            //Si el nodo es menor o igual que aux
            if(id <= aux->valor.id_centro)
            {
                aux = aux->izquierda; //Aux a su hijo izquierdo
            }

            //Si el nodo es mayor que aux
            else
            {
                aux = aux->derecha; //Aux a su hijo derecho
            }
        }
    }

    return encontrado; //Devolvemos si se ha encontrado el centro
}


//Busca una venta por su identificador en el subarbol que empieza en nodo (en inorden)
bool Arbol::buscarVentaNodo(NodoArbol *nodo, string id, Venta& v)
{
    //Si el subarbol esta vacio, no hay nada que buscar
    if(nodo == NULL)
    {
        return false;
    }

    //Buscamos primero en el subarbol izquierdo
    if(buscarVentaNodo(nodo->izquierda, id, v))
    {
        return true;
    }

    //Buscamos la venta en la lista del centro (sin modificar la lista)
    else if(nodo->valor.ventas.buscar(id, v))
    {
        return true;
    }


    //Si no esta, buscamos en el subarbol derecho
    else if(buscarVentaNodo(nodo->derecha, id, v))
    {
        return true;
    }

    //Si no se encuentra
    else
    {
        return false;
    }
}

//Devuelve True y la venta con el id buscado en v si se ha encontrado (False si no)
bool Arbol::buscar(string id, Venta& v)
{
    return buscarVentaNodo(raiz, id, v); //Empezamos por la raiz
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True si el centro con el identificador está en el Arbol
bool Arbol::estaEnArbol(int id)
{
    bool encontrado = false; //Valor para determinar si lo hemos encontrado
    NodoArbol *aux = raiz;   //Puntero auxiliar a la raiz del arbol
    Centro c;

    while(!encontrado && aux != NULL)
    {
        //Si aux apunta al nodo con el identificador buscado
        if(aux->valor.id_centro == id)
        {
            encontrado = true; //Encontrado
        }

        //Si no
        else
        {
            //Si el nodo es menor o igual que aux
            if(id <= aux->valor.id_centro)
            {
                aux = aux->izquierda; //Aux a su hijo izquierdo
            }

            //Si el nodo es mayor que aux
            else
            {
                aux = aux->derecha; //Aux a su hijo derecho
            }
        }
    }

    return encontrado; //Devolvemos encontrado
}

//Devuelve True si la venta está en el subarbol que empieza en nodo (en inorden)
bool Arbol::ventaEnNodo(NodoArbol *nodo, string id)
{
    //Si el subarbol esta vacio, no hay nada que buscar
    if(nodo == NULL)
    {
        return false;
    }

    //Buscamos primero en el subarbol izquierdo
    if(ventaEnNodo(nodo->izquierda, id))
    {
        return true;
    }

    //Buscamos la venta en la lista del centro (sin modificar la lista)
    else if(nodo->valor.ventas.estaEnLista(id))
    {
        return true;
    }


    //Si no esta, buscamos en el subarbol derecho
    else if(ventaEnNodo(nodo->derecha, id))
    {
        return true;
    }

    //Si no se encuentra
    else
    {
        return false;
    }
}

//Devuelve True si encuentra la venta en algun centro del arbol (el id es unico)
bool Arbol::estaEnArbol(string id)
{
    return ventaEnNodo(raiz, id); //Empezamos por la raiz
}

//-----------------------------------------------------------------------------------------------//

//Muestra por pantalla las filas de la tabla correspondientes al nodo (en inorden)
void Arbol::mostrarNodoInOrden(NodoArbol *nodo)
{
    //Si tiene hijo izquierdo
    if(nodo->izquierda != NULL)
    {
        mostrarNodoInOrden(nodo->izquierda); //Se muestra en inorden
    }

    Centro c;
    copiarCentro(nodo->valor, c); //Centro a mostrar por pantalla (raiz del subárbol)

    cout << left << "| " << setw(9) << c.id_centro              //ID centro
         << " | " << setw(22) << localidadToString(c.localidad) //Localidad
         << " | " << setw(6) << c.ventas.getLongitud()          //Número de ventas
         << " |" << endl;

    //Si tiene hijo derecho
    if(nodo->derecha != NULL)
    {
        mostrarNodoInOrden(nodo->derecha); //Se muestra en inorden
    }
}

//Muestra el arbol por pantalla en formato de tabla (en inorden)
void Arbol::mostrar()
{
    //Imprimimos la cabecera de la tabla
    cout << "+---------------------------------------------+" << endl
         << "| ID Centro |       Localidad        | Ventas |" << endl
         << "+---------------------------------------------+" << endl;

    //Si no está vacío, imprimimos cada elemento del Árbol en inOrden
    if(!esVacio())
    {
        mostrarNodoInOrden(raiz); //Mostramos de manera recursiva en inorden

    }

    //Si está vacía, imprimimos una fila vacía
    else cout << "|           |                        |        |" << endl;

    //Imprimimos el final de la tabla
    cout << "+---------------------------------------------+" << endl
         << "Centros: " << getNodos() << endl;
}
