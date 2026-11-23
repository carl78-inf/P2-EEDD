#include "napoli.h"

//Constructor
napoli::napoli()
{
    //Al empezar se crean los centros y las ventas iniciales
    crearDatosIniciales();
}

//Destructor
napoli::~napoli()
{
    //El destructor de Arbol libera todos los nodos y sus listas de ventas
}

//-----------------------------------------------------------------------------------------------//

//Devuelve True si el id_centro ya está registrado en el sistema
bool napoli::idYaEnSistema(int id_centro)
{
    return centros.estaEnArbol(id_centro);
}

//Devuelve True si el id_venta ya está registrado en el sistema
bool napoli::idYaEnSistema(string id_venta)
{
    return centros.estaEnArbol(id_venta);
}

//Genera N_CENTROS aleatorios y los añade al arbol de centros del sistema
void napoli::generarCentros()
{
    int id; //ID del centro
    for(int i = 0; i < N_CENTROS; i++)
    {
        do
        {
            id = generarIDCentroRandom(); //Generamos un ID aleatorio
        }
        while(idYaEnSistema(id));        //Repetimos si el ID ya existe en el sistema

        //Generamos un centro aleatorio con ese id y lo insertamos en el arbol del sistema
        Centro c = generarCentroRandom(id);
        centros.insertar(c);
    }
}

//Genera N_VENTAS aleatorias y las añade a la lista ventas
void napoli::generarVentas(Lista& ventas)
{
    int ids[centros.getNodos()]; //Identificadores de los centros registrados en el sistema
    centros.getIDs(ids);         //Obtenemos todos los identificadores en el Arbol

    string id; //ID de la venta
    for(int i = 0; i < N_VENTAS; i++)
    {
        do
        {
            id = generarIDVentaRandom(); //Generamos un ID aleatorio
        }
        while(idYaEnSistema(id));        //Repetimos si el ID ya existe en el sistema

        //Generamos una venta aleatoria con ese id y lo insertamos al final de la lista
        Venta v = generarVentaRandom(id);
        v.id_centro = ids[rand() % centros.getNodos()]; //Le asignamos un centro existente
        ventas.insertar(v);
    }
}

//Distribuye la lista de ventas entre los distintos centros del sistema
void napoli::distribuirVentas(Lista& ventas)
{
    //Para todas las ventas de la lista
    Venta v;
    for(int i = 0; i < ventas.getLongitud(); i++)
    {
        Venta v = ventas.obtener(i); //Venta en la posición i
        centros.insertar(v);  //La insertamos en el Arbol
    }
}

//Crea los centros y las ventas iniciales al comenzar el programa
void napoli::crearDatosIniciales()
{
    cout << "Creando el ABB con " << N_CENTROS << " centros:" << endl;
    generarCentros(); //Generamos N_CENTROS

    cout << "\nArbol inicial:" << endl;
    centros.mostrar(); //Mostramos el Arbol de centros por pantalla

    Lista ventas; //Lista para almacenar las ventas creadas
    generarVentas(ventas); //Generamos N_VENTAS

    cout << endl << "Ventas nuevas:" << endl;
    ventas.mostrar(); //Mostramos las ventas generadas

    cout << endl << "Pulse Enter para distribuir las ventas" << endl;
    cin.get();

    distribuirVentas(ventas); //Distribuimos las ventas

    cout << "Ventas distribuidas. Estado del arbol:" << endl;
    centros.mostrar();
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

//Muestra el menu de localidades y devuelve la posicion del enum elegida (-1 si no es valida)
int napoli::pedirLocalidad()
{
    int opcion;

    cout << endl << "Localidades disponibles:" << endl;

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
    int id;        //ID del centro
    int localidad; //Localidad

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

    cout << endl << "Centro insertado correctamente:" << endl;
    mostrarCentro(c);
}

//-----------------------------------------------------------------------------------------------//

//Opcion 2: elimina un centro por su identificador
void napoli::borrarCentro()
{
    int id;        //ID del centro
    int localidad; //Localidad

    cout << "ID del centro (100-999): ";

    //Validamos que el identificador sea un numero de 3 cifras
    if(!leerEntero(id) || id < 100 || id > 999)
    {
        cout << "Error: el identificador debe ser un numero de 3 cifras (100-999)." << endl;
        return;
    }

    //Comprobamos que esté en el sistema
    if(!idYaEnSistema(id))
    {
        cout << "No existe un centro con el identificador " << id << " en el sistema." << endl;
    }
    else
    {
        centros.eliminar(id); //Eliminamos el centro
        cout << endl << "Centro eliminado correctamente:" << endl;
        centros.mostrar(); //Mostramos el estado del sistema
    }
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

    //Si el centro no existe, informamos
    if(!centros.estaEnArbol(id))
    {
        cout << "Error: no existe ningun centro con el identificador " << id << "." << endl;
        return;
    }

    else
    {
        //Obtenemos el centro y mostramos su localidad y sus ventas
        Centro c;
        centros.buscar(id, c);
        mostrarCentro(c);
    }
}

//-----------------------------------------------------------------------------------------------//

//Opcion 4: busca una venta por su identificador en todos los centros del arbol
void napoli::buscarVenta()
{
    string id;
    Venta v;

    cout << "ID de la venta (formato V12345): ";
    cin >> id;

    //Recorremos el ABB hasta encontrar la venta
    if(!centros.buscar(id, v))
    {
        cout << "Error: no existe ninguna venta con el identificador " << id << "." << endl;
    }

    //Una vez encontrada
    else
    {
        cout << endl << "Venta encontrada:" << endl;

        cout << "+---------------------------------------------------------------------------+" << endl
             << "| ID Centro | ID Venta | Codigo Pizza |  Categoria  | Unidades |   Fecha    |" << endl
             << "+---------------------------------------------------------------------------+" << endl;

        mostrarFila(v); //Lo mostramos por pantalla

        cout << "\n+---------------------------------------------------------------------------+" << endl;
    }

}

//-----------------------------------------------------------------------------------------------//

//Opcion 5: elimina una venta por su identificador
void napoli::extraerVenta()
{
    //Sin implementar
}

//-----------------------------------------------------------------------------------------------//

//Opcion 6: se trasladara una venta a otro centro indicando el id_venta y el id_centro destino
void napoli::trasladarVenta()
{
    //Sin implementar
}

//-----------------------------------------------------------------------------------------------//

//Opcion 7: muestra estadisticas (nº ventas, nº pizzas vendidas en cada centro, pizza mas vendida, centro con mas pizzas vendidas)
void napoli::mostrarEstadisticas()
{
    //Sin implementar
}

//-----------------------------------------------------------------------------------------------//

//Opcion 8: se generara otro lote de N_VENTAS y se distribuira entre los centros del sistema
void napoli::generarYDistribuirVentas()
{
    Lista ventas; //Lista para almacenar las ventas creadas
    generarVentas(ventas); //Generamos N_VENTAS

    cout << endl << "Ventas nuevas:" << endl;
    ventas.mostrar(); //Mostramos las ventas generadas

    distribuirVentas(ventas); //Distribuimos las ventas

    cout << "Ventas distribuidas. Estado del arbol:" << endl;
    centros.mostrar();
}

