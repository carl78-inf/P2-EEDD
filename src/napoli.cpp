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

//Crea los centros y las ventas iniciales al comenzar el programa
void napoli::crearDatosIniciales()
{
    int ids[N_CENTROS]; //Identificadores de los centros creados
    bool localidad_usada[N_LOCALIDADES] = {false}; //Localidades ya elegidas
    Lista nuevas; //Ventas generadas antes de distribuirlas

    cout << "Creando el ABB con " << N_CENTROS << " centros:" << endl;

    //Creamos los centros con identificadores y localidades distintas
    for(int i = 0; i < N_CENTROS; i++)
    {
        int id;
        int localidad;

        //Generamos un identificador que no exista ya en el arbol
        do
        {
            id = rand() % 900 + 100;
        } while(centros.estaEnArbol(id));

        //Generamos una localidad que no se haya usado todavia
        do
        {
            localidad = rand() % N_LOCALIDADES;
        } while(localidad_usada[localidad]);

        localidad_usada[localidad] = true;

        //Creamos el centro con su lista de ventas vacia
        Centro c;
        c.id_centro = id;
        c.localidad = (Localidad)localidad;
        centros.insertar(c);

        ids[i] = id; //Guardamos el identificador para las ventas
    }

    cout << "Arbol inicial:" << endl;
    centros.mostrarResumen();

    //Generamos las ventas, cada una asignada a un centro existente
    for(int i = 0; i < N_VENTAS; i++)
    {
        Venta v = generarVentaRandom();

        v.id_centro = ids[rand() % N_CENTROS]; //Centro que existe en el ABB

        //Si el identificador de la venta ya ha salido, generamos otro
        while(nuevas.estaEnLista(v.id_venta))
        {
            v.id_venta = generarIDVentaRandom();
        }

        nuevas.insertar(v);
    }

    cout << endl << "Ventas nuevas:" << endl;
    nuevas.mostrar();

    cout << endl << "Pulse Enter para distribuir las ventas" << endl;
    cin.get();

    //Distribuimos cada venta al final de la lista de su centro
    for(int i = 0; i < nuevas.getLongitud(); i++)
    {
        Venta v = nuevas.obtener(i);
        centros.insertarVenta(v);
    }

    cout << "Ventas distribuidas. Estado del arbol:" << endl;
    centros.mostrarResumen();
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

    cout << endl << "Centro insertado correctamente:" << endl;
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

    //Si el centro no existe, informamos
    if(!centros.estaEnArbol(id))
    {
        cout << "Error: no existe ningun centro con el identificador " << id << "." << endl;
        return;
    }

    //Obtenemos el centro y mostramos su localidad y sus ventas
    Centro c = centros.obtener(id);
    mostrarCentro(c);
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
    if(!centros.buscarVenta(id, v))
    {
        cout << "Error: no existe ninguna venta con el identificador " << id << "." << endl;
        return;
    }

    //La propia venta guarda el id del centro al que pertenece
    Centro c = centros.obtener(v.id_centro);

    //Mostramos los datos de la venta y el centro al que pertenece
    cout << endl << "Venta encontrada:" << endl;
    cout << "CENTRO " << c.id_centro << " - " << localidadToString(c.localidad) << endl;
    cout << "+---------------------------------------------------------------------------+" << endl
         << "| ID Centro | ID Venta | Codigo Pizza |  Categoria  | Unidades |   Fecha    |" << endl
         << "+---------------------------------------------------------------------------+" << endl;
    mostrarFila(v);
    cout << endl
         << "+---------------------------------------------------------------------------+" << endl;
}
