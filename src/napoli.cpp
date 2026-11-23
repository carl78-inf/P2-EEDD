#include "napoli.h"

//Constructor
napoli::napoli()
{
    //El ABB se crea vacio en el constructor de Arbol
}

//Destructor
napoli::~napoli()
{
    //El destructor de Arbol libera todos los nodos y sus listas de ventas
}

//-----------------------------------------------------------------------------------------------//

//Lee un entero por teclado. Devuelve False si lo introducido no es un numero
bool napoli::leerEntero(int& valor)
{
    string texto;
    int numero = 0;

    cin >> texto; //Leemos lo que escribe el usuario como texto

    //Recorremos el texto caracter a caracter
    for(int i = 0; i < (int)texto.length(); i++)
    {
        //Si algun caracter no es un digito, no es un numero
        if(texto[i] < '0' || texto[i] > '9')
        {
            return false;
        }

        //Vamos formando el numero: 3, luego 38, luego 381
        numero = numero * 10 + (texto[i] - '0');
    }

    valor = numero; //Guardamos el numero en la variable
    return true;
}

//-----------------------------------------------------------------------------------------------//

//Muestra el menu de localidades y devuelve la posicion del enum elegida (-1 si no es valida)
int napoli::pedirLocalidad()
{
    int opcion;

    cout << "\nLocalidades disponibles:" << endl;

    //Mostramos las 21 localidades numeradas
    for(int i = 1; i <= N_LOCALIDADES; i++)
    {
        cout << "  " << i << ". " << localidadToString((Localidad)(i - 1)) << endl;
    }

    cout << "Localidad (1-" << N_LOCALIDADES << "): ";

    //Validamos que la opcion sea un numero dentro del rango
    if(!leerEntero(opcion) || opcion < 1 || opcion > N_LOCALIDADES)
    {
        return -1; //Opcion no valida
    }

    return opcion - 1; //El enum Localidad empieza en 0
}

//-----------------------------------------------------------------------------------------------//

//Opcion 1: inserta un centro introducido manualmente por el usuario
void napoli::insertarCentro()
{
    int id;
    int localidad;

    cout << "ID del centro (100-999): ";

    //Validamos que el identificador sea un numero de 3 cifras
    if(!leerEntero(id) || id < 100 || id > 999)
    {
        cout << "Error: el identificador debe ser un numero de 3 cifras (100-999)." << endl;
        return;
    }

    //Si ya existe un centro con ese identificador no se modifica el arbol
    if(centros.estaEnArbol(id))
    {
        cout << "Error: ya existe un centro con el identificador " << id
             << ". No se modifica el arbol." << endl;
        return;
    }

    //Pedimos la localidad del nuevo centro
    localidad = pedirLocalidad();

    if(localidad == -1)
    {
        cout << "Error: localidad no valida. No se inserta el centro." << endl;
        return;
    }

    //Creamos el centro con su lista de ventas inicialmente vacia
    Centro c;
    c.id_centro = id;
    c.localidad = (Localidad)localidad;

    centros.insertar(c); //Se inserta ordenado por id_centro

    cout << "\nCentro insertado correctamente:" << endl;
    mostrarCentro(c);
}

//-----------------------------------------------------------------------------------------------//

//Opcion 3: muestra la localidad y las ventas de un centro
void napoli::mostrarVentasCentro()
{
    int id;

    cout << "ID del centro (100-999): ";

    if(!leerEntero(id))
    {
        cout << "Error: el identificador no es un numero valido." << endl;
        return;
    }

    //El Arbol busca el centro y muestra sus ventas (devuelve False si no existe)
    if(!centros.mostrarVentasCentro(id))
    {
        cout << "Error: no existe ningun centro con el identificador " << id << "." << endl;
    }
}

//-----------------------------------------------------------------------------------------------//

//Opcion 4: busca una venta por su identificador en todos los centros del arbol
void napoli::buscarVenta()
{
    string id;
    Venta v;
    int id_centro;
    Localidad localidad;

    cout << "ID de la venta (formato V12345): ";
    cin >> id;

    //Recorremos el ABB hasta encontrar la venta
    if(!centros.buscarVenta(id, v, id_centro, localidad))
    {
        cout << "Error: no existe ninguna venta con el identificador " << id << "." << endl;
        return;
    }

    //Mostramos los datos de la venta y el centro al que pertenece
    cout << "\nVenta encontrada:" << endl;
    cout << "CENTRO " << id_centro << " - " << localidadToString(localidad) << endl;
    cout << "+---------------------------------------------------------------------------+" << endl
         << "| ID Centro | ID Venta | Codigo Pizza |  Categoria  | Unidades |   Fecha    |" << endl
         << "+---------------------------------------------------------------------------+" << endl;
    mostrarFila(v);
    cout << endl
         << "+---------------------------------------------------------------------------+" << endl;
}
