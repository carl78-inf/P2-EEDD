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
        delete(nodo);            //Eliminar nodo
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

//Inserta un nodo de forma ordenada en el Arbol
void Arbol::insertar(Centro c)
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

        //Ponemos el puntero del padre al hijo izquierdo
        if(derecha)
        {
            padre->derecha = nodo->izquierda; //Hijo derecho padre
        }
        else
        {
            padre->izquierda = nodo->izquierda; //Hijo izquierdo padre
        }

        nodo->derecha = NULL; //Puntero al hijo a NULL
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
        nodo->valor = maximo->valor;

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
            nodos--; //Decrementamos el número de nodos
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

//Devuelve el Centro con el identificador dado
Centro Arbol::obtener(int id)
{
    bool encontrado = false; //Valor para determinar si lo hemos encontrado
    NodoArbol *aux = raiz;   //Puntero auxiliar a la raiz del arbol
    Centro c;

    while(!encontrado && aux != NULL)
    {
        //Si aux apunta al nodo con el identificador buscado
        if(aux->valor.id_centro == id)
        {
            c = aux->valor;    //Centro con el ID buscado
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

    return c; //Devolvemos el centro (por defecto si no encontrado)
}

//Devuelve True si el identificador está en el arbol
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

//-----------------------------------------------------------------------------------------------//

//Busca una venta por su identificador en el subarbol que empieza en nodo (en inorden)
bool Arbol::buscarVentaRec(NodoArbol *nodo, string id, Venta& v)
{
    //Si el subarbol esta vacio, no hay nada que buscar
    if(nodo == NULL)
    {
        return false;
    }

    //Buscamos primero en el subarbol izquierdo
    if(buscarVentaRec(nodo->izquierda, id, v))
    {
        return true;
    }

    //Buscamos la venta en la lista del centro (sin modificar la lista)
    int pos = nodo->valor.ventas.buscar(id);

    //Si esta en este centro, guardamos la venta y terminamos
    if(pos != -1)
    {
        v = nodo->valor.ventas.obtener(pos); //Venta encontrada
        return true;
    }

    //Si no esta, buscamos en el subarbol derecho
    return buscarVentaRec(nodo->derecha, id, v);
}

//Devuelve True si encuentra la venta en algun centro del arbol (el id es unico)
bool Arbol::buscarVenta(string id, Venta& v)
{
    return buscarVentaRec(raiz, id, v); //Empezamos por la raiz
}

//-----------------------------------------------------------------------------------------------//

//Inserta una venta al final de la lista del centro indicado en v.id_centro
bool Arbol::insertarVenta(Venta v)
{
    NodoArbol *aux = raiz; //Puntero auxiliar a la raiz del arbol

    //Buscamos el nodo del centro de la venta
    while(aux != NULL)
    {
        if(aux->valor.id_centro == v.id_centro)
        {
            aux->valor.ventas.insertar(v); //Se inserta al final de la lista
            return true;
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

    return false; //No existe ningun centro con ese identificador
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

    Centro c = nodo->valor; //Centro a mostrar por pantalla (raiz del subárbol)

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

//-----------------------------------------------------------------------------------------------//

//Muestra por pantalla los datos de los nodos del subarbol (en inorden)
void Arbol::mostrarResumenRec(NodoArbol *nodo)
{
    //Si tiene hijo izquierdo
    if(nodo->izquierda != NULL)
    {
        mostrarResumenRec(nodo->izquierda);
    }

    //Mostramos el identificador, la localidad y el numero de ventas
    cout << "ID: " << nodo->valor.id_centro
         << " Localidad: " << setw(22) << localidadToString(nodo->valor.localidad)
         << " Num ventas: " << nodo->valor.ventas.getLongitud() << endl;

    //Si tiene hijo derecho
    if(nodo->derecha != NULL)
    {
        mostrarResumenRec(nodo->derecha);
    }
}

//Muestra un resumen de todos los centros del arbol (en inorden)
void Arbol::mostrarResumen()
{
    if(esVacio())
    {
        cout << "El arbol esta vacio." << endl;
    }
    else
    {
        mostrarResumenRec(raiz);
    }
}
