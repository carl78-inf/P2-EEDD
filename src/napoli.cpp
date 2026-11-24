#include "napoli.h"

// Al construir un objeto napoli se crean automaticamente los datos iniciales.
// main() hace "napoli app;", asi que nada mas arrancar el programa ya existen
// 10 centros y 30 ventas repartidas.
napoli::napoli()
{
    crearDatosIniciales();
}


napoli::~napoli()
{
}


// ----------------------------------------------------------------------------
// Comprueba si un id de centro ya existe.
// Se delega en Arbol::estaEnArbol(int), que recorre el ABB comparando ids.
// ----------------------------------------------------------------------------
bool napoli::idYaEnSistema(int id_centro)
{
    return centros.estaEnArbol(id_centro);
}

// ----------------------------------------------------------------------------
// Comprueba si un id de venta ya existe en cualquier centro.
// Se delega en Arbol::estaEnArbol(string), que recorre los centros y sus
// listas buscando ese id_venta.
// ----------------------------------------------------------------------------
bool napoli::idYaEnSistema(string id_venta)
{
    return centros.estaEnArbol(id_venta);
}


// ----------------------------------------------------------------------------
// Genera N_CENTROS centros aleatorios y los inserta en el ABB.
//
// Para cada centro:
//   1. Sortea un id con generarIDCentroRandom() (un numero de 100 a 999).
//   2. Si ese id ya existe en el sistema, vuelve a sortearlo (do/while).
//   3. generarCentroRandom(id) crea el Centro con ese id y una localidad
//      aleatoria. Su lista de ventas queda vacia automaticamente.
//   4. centros.insertar(c) coloca el centro en su posicion del ABB.
// ----------------------------------------------------------------------------
void napoli::generarCentros()
{
    int id; // Identificador que se va a sortear

    // Repetimos N_CENTROS veces el proceso de crear e insertar un centro
    for(int i = 0; i < N_CENTROS; i++)
    {
        // Sorteamos un id y lo repetimos mientras ya exista en el sistema.
        // Asi garantizamos que los ids de los centros no se repiten.
        do
        {
            id = generarIDCentroRandom(); // Genera un id entre 100 y 999
        }
        while(idYaEnSistema(id));         // Repetir si el id ya existe

        // Creamos el centro con ese id y una localidad aleatoria.
        // La lista de ventas se crea vacia en el constructor de Lista.
        Centro c = generarCentroRandom(id);

        // Lo insertamos en el ABB, ordenado por id_centro.
        centros.insertar(c);
    }
}


// ----------------------------------------------------------------------------
// Genera N_VENTAS ventas aleatorias y las deja al final de la lista "ventas".
// debe haber al menos un centro en el arbol, porque se elige un
// id_centro al azar entre los centros existentes. En el flujo normal siempre
// se llama despues de generarCentros() o con centros ya creados.
//
// Pasos:
//   1. getIDs(ids) llena ids[] con los id_centro de todos los centros.
//      El array se dimensiona con el numero actual de centros.
//   2. Para cada venta:
//      a. Sortea un id_venta y lo repite si ya existe.
//      b. generarVentaRandom(id) crea la venta con ese id.
//      c. Le asigna un centro existente: ids[rand() % numeroDeCentros].
//      d. La inserta al final de la lista temporal.
// ----------------------------------------------------------------------------
void napoli::generarVentas(Lista& ventas)
{
    // Array con un hueco por cada centro actual. Es un array de longitud
    int ids[centros.getNodos()];

    // Rellena ids[] con los identificadores de todos los centros del ABB.
    centros.getIDs(ids);

    string id; // Identificador que se va a sortear para cada venta

    // Repetimos N_VENTAS veces el proceso de crear una venta
    for(int i = 0; i < N_VENTAS; i++)
    {
        // Sorteamos un id de venta y lo repetimos mientras ya exista en
        // cualquier centro. Asi el id_venta es unico durante la ejecucion.
        do
        {
            id = generarIDVentaRandom(); // Genera V + 5 cifras
        }
        while(idYaEnSistema(id));        // Repetir si ya existe

        // Creamos la venta con ese id y el resto de campos aleatorios.
        Venta v = generarVentaRandom(id);

        // Le asignamos uno de los centros que existen ahora mismo en el ABB.
        // rand() % centros.getNodos() da una posicion valida de ids[].
        v.id_centro = ids[rand() % centros.getNodos()];

        // Guardamos la venta al final de la lista temporal.
        // Todavia no esta en el centro; se reparte despues.
        ventas.insertar(v);
    }
}


// ----------------------------------------------------------------------------
// Reparte las ventas de la lista temporal entre los centros del ABB.
//
// Para cada posicion i de la lista:
//   1. Copia la venta con obtener(i).
//   2. centros.insertar(v) busca el centro cuyo id_centro coincide con
//      v.id_centro y anyade la venta al final de su lista.
//
// La lista temporal no se modifica; al salir de la funcion se destruye y
// libera sus nodos. Los centros se quedan con copias independientes.
// ----------------------------------------------------------------------------
void napoli::distribuirVentas(Lista& ventas)
{
    // Recorremos todas las ventas de la lista temporal
    for(int i = 0; i < ventas.getLongitud(); i++)
    {
        // Copiamos la venta que esta en la posicion i
        Venta v = ventas.obtener(i);

        // La insertamos en el centro correspondiente (al final de su lista)
        centros.insertar(v);
    }
}


// ----------------------------------------------------------------------------
// Creacion inicial completa (la que se ejecuta al arrancar el programa).
//
// Sigue el orden del enunciado:
//   1. Crear y mostrar los N_CENTROS centros (con listas vacias).
//   2. Generar y mostrar las N_VENTAS ventas (aun sin repartir).
//   3. Esperar a que el usuario pulse Enter.
//   4. Distribuir cada venta en la lista de su centro.
//   5. Mostrar el estado final del arbol con el numero de ventas por centro.
// ----------------------------------------------------------------------------
void napoli::crearDatosIniciales()
{
    // PASO 1: crear los centros y mostrarlos
    cout << "Creando el ABB con " << N_CENTROS << " centros:" << endl;
    generarCentros();

    cout << "\nArbol inicial:" << endl;
    centros.mostrar();

    // PASO 2: generar las ventas y mostrarlas antes de repartirlas
    Lista ventas;          // Lista temporal para las ventas generadas
    generarVentas(ventas); // Genera N_VENTAS y las guarda en la lista

    cout << endl << "Ventas nuevas:" << endl;
    ventas.mostrar();

    // PASO 3: pausa hasta que el usuario pulse Enter
    cout << endl << "Pulse Enter para distribuir las ventas" << endl;
    cin.get();

    // PASO 4: repartir cada venta en el centro que le corresponde
    distribuirVentas(ventas);

    // PASO 5: mostrar el estado final del arbol
    cout << "Ventas distribuidas. Estado del arbol:" << endl;
    centros.mostrar();
}


// ----------------------------------------------------------------------------
// Lee un entero positivo por teclado.
//
// Por que no usar directamente "cin >> valor"?
// Porque si el usuario escribe letras, cin queda en estado de error y habria
// que limpiarlo. Aqui se lee el texto y se comprueba caracter a caracter:
//
//   "381" -> '3' (numero = 3)
//            '8' (numero = 38)
//            '1' (numero = 381)
//
// Devuelve false si algun caracter no es un digito o si el texto esta vacio.
// El numero final se guarda en "valor", que es un parametro por referencia.
// ----------------------------------------------------------------------------
bool napoli::leerEntero(int& valor)
{
    string texto;      // Lo que escribe el usuario, como texto
    int numero = 0;    // Numero que vamos construyendo

    cin >> texto; // Leemos la entrada como texto

    // Recorremos el texto caracter a caracter
    for(int i = 0; i < (int)texto.length(); i++)
    {
        // Si algun caracter no esta entre '0' y '9', no es un numero
        if(texto[i] < '0' || texto[i] > '9')
        {
            return false;
        }

        // Convertimos el caracter a digito y lo anyadimos al final:
        // numero = numero * 10 + digito
        // Ejemplo: 3 -> 38 -> 381
        numero = numero * 10 + (texto[i] - '0');
    }

    // Guardamos el resultado en la variable del llamador
    valor = numero;
    return true;
}

// ----------------------------------------------------------------------------
// Muestra las localidades numeradas (1..21) y pide una opcion.
// ----------------------------------------------------------------------------
int napoli::pedirLocalidad()
{
    int opcion;

    cout << endl << "Localidades disponibles:" << endl;

    // Mostramos las N_LOCALIDADES localidades con un numero delante.
    // (Localidad)(i - 1) convierte el numero 1..21 al indice 0..20 del enum.
    for(int i = 1; i <= N_LOCALIDADES; i++)
    {
        cout << "  " << i << ". " << localidadToString((Localidad)(i - 1)) << endl;
    }

    cout << "Localidad (1-" << N_LOCALIDADES << "): ";

    // Validamos que sea un numero y que este dentro del rango
    if(!leerEntero(opcion) || opcion < 1 || opcion > N_LOCALIDADES)
    {
        return -1; // Opcion no valida
    }

    return opcion - 1; // El enum Localidad empieza en 0
}


// ----------------------------------------------------------------------------
// OPCION 1: insertar un centro manualmente.
//
// Pasos:
//   1. Pedir el id y comprobar que es un numero entre 100 y 999.
//   2. Comprobar que no existe ya. Si existe, informar y NO tocar el arbol.
//   3. Pedir la localidad.
//   4. Crear el Centro (su lista de ventas se crea vacia).
//   5. Insertarlo en el ABB.
//   6. Mostrarlo por pantalla como confirmacion.
// ----------------------------------------------------------------------------
void napoli::insertarCentro()
{
    int id;        // Identificador del nuevo centro
    int localidad; // Indice del enum Localidad elegido

    cout << "ID del centro (100-999): ";

    // PASO 1: validar que el id sea un numero de 3 cifras
    if(!leerEntero(id) || id < 100 || id > 999)
    {
        cout << "Error: el identificador debe ser un numero de 3 cifras (100-999)." << endl;
        return;
    }

    // PASO 2: si ya existe un centro con ese id, no se modifica el arbol
    if(centros.estaEnArbol(id))
    {
        cout << "Error: ya existe un centro con el identificador " << id
             << ". No se modifica el arbol." << endl;
        return;
    }

    // PASO 3: pedir la localidad
    localidad = pedirLocalidad();

    if(localidad == -1)
    {
        cout << "Error: localidad no valida. No se inserta el centro." << endl;
        return;
    }

    // PASO 4: crear el centro con su lista de ventas vacia
    Centro c;
    c.id_centro = id;
    c.localidad = (Localidad)localidad;

    // PASO 5: insertarlo en el ABB (ordenado por id_centro)
    centros.insertar(c);

    // PASO 6: mostrar el centro recien creado
    cout << endl << "Centro insertado correctamente:" << endl;
    centros.mostrar();
}


// ----------------------------------------------------------------------------
// OPCION 2: borrar un centro por su identificador.
//
// Pasos:
//   1. Pedir el id y comprobar que es un numero de 3 cifras.
//   2. Comprobar que existe en el sistema.
//   3. Si existe, Arbol::eliminar(id) borra el nodo y libera su lista de ventas.
//   4. Mostrar el estado del arbol tras el borrado.
// Si no existe, informar y no modificar nada.
// ----------------------------------------------------------------------------
void napoli::borrarCentro()
{
    int id; // Identificador del centro que se quiere borrar

    cout << "ID del centro (100-999): ";

    // PASO 1: validar el identificador
    if(!leerEntero(id) || id < 100 || id > 999)
    {
        cout << "Error: el identificador debe ser un numero de 3 cifras (100-999)." << endl;
        return;
    }

    // PASO 2: comprobar que existe
    if(!idYaEnSistema(id))
    {
        // PASO 2a: no existe -> informar y no hacer nada
        cout << "No existe un centro con el identificador " << id << " en el sistema." << endl;
    }
    else
    {
        // PASO 3: existe -> eliminarlo del ABB (y con el, su lista de ventas)
        centros.eliminar(id);

        // PASO 4: mostrar el estado del sistema
        cout << endl << "Centro eliminado correctamente:" << endl;
        centros.mostrar();
    }
}


// ----------------------------------------------------------------------------
// OPCION 3: mostrar la localidad y las ventas de un centro.
//
// Pasos:
//   1. Pedir el id y validar que sea un numero.
//   2. Comprobar que el centro existe.
//   3. centros.buscar(id, c) devuelve una copia del centro en c.
//   4. mostrarCentro(c) muestra su localidad y sus ventas en orden.
//      Si la lista esta vacia, muestra el mensaje correspondiente.
// ----------------------------------------------------------------------------
void napoli::mostrarVentasCentro()
{
    int id; // Identificador del centro que se quiere consultar

    cout << "ID del centro (100-999): ";

    // PASO 1: validar que sea un numero
    if(!leerEntero(id))
    {
        cout << "Error: el identificador no es un numero valido." << endl;
        return;
    }

    // PASO 2: comprobar que el centro existe
    if(!centros.estaEnArbol(id))
    {
        cout << "Error: no existe ningun centro con el identificador " << id << "." << endl;
        return;
    }
    else
    {
        // PASO 3: obtener una copia del centro
        Centro c;
        centros.buscar(id, c);

        // PASO 4: mostrar su localidad y sus ventas
        mostrarCentro(c);
    }
}


// ----------------------------------------------------------------------------
// OPCION 4: buscar una venta por su identificador en todos los centros.
//
// Pasos:
//   1. Pedir el id_venta.
//   2. centros.buscar(id, v) recorre el arbol y busca la venta.
//   3. Si no existe, informar del error.
//   4. Si existe, mostrar la cabecera de la tabla y la fila de la venta.
//
// La busqueda no modifica el arbol ni el orden de las listas.
// ----------------------------------------------------------------------------
void napoli::buscarVenta()
{
    string id; // Identificador de la venta que se busca
    Venta v;   // Aqui se guardara la venta encontrada

    cout << "ID de la venta (formato V12345): ";
    cin >> id;

    // PASO 2: buscar la venta en todos los centros del arbol
    if(!centros.buscar(id, v))
    {
        // PASO 3: no existe
        cout << "Error: no existe ninguna venta con el identificador " << id << "." << endl;
    }
    else
    {
        // PASO 4: existe -> mostrar los datos de la venta
        cout << endl << "Venta encontrada:" << endl;

        cout << "+---------------------------------------------------------------------------+" << endl
             << "| ID Centro | ID Venta | Codigo Pizza |  Categoria  | Unidades |   Fecha    |" << endl
             << "+---------------------------------------------------------------------------+" << endl;

        mostrarFila(v); // Imprime la fila con los datos de la venta

        cout << "\n+---------------------------------------------------------------------------+" << endl;
    }
}

//-----------------------------------------------------------------------------------------------//

// ----------------------------------------------------------------------------
// OPCION 5: extraer una venta (PENDIENTE).
//
// Cuando se implemente deberia:
//   1. Pedir el id_venta.
//   2. Localizar la venta y su centro (recorriendo el arbol y las listas).
//   3. Eliminarla de la lista del centro con Lista::eliminar(posicion).
//   4. Si no existe, informar y no modificar ninguna estructura.
// ----------------------------------------------------------------------------
void napoli::extraerVenta()
{
    // Sin implementar
}

//-----------------------------------------------------------------------------------------------//

// ----------------------------------------------------------------------------
// OPCION 6: trasladar una venta a otro centro (PENDIENTE).
//
// Cuando se implemente deberia:
//   1. Pedir el id_venta y el id_centro de destino.
//   2. Comprobar que existen la venta y el centro de destino.
//   3. Extraer la venta de la lista de su centro de origen.
//   4. Actualizar v.id_centro al centro destino.
//   5. Insertarla al final de la lista del centro destino.
//   6. Si algo no existe o el origen es el mismo que el destino, no hacer nada
//      e informar del error.
// ----------------------------------------------------------------------------
void napoli::trasladarVenta()
{
    // Sin implementar
}

//-----------------------------------------------------------------------------------------------//

// ----------------------------------------------------------------------------
// OPCION 7: mostrar estadisticas de los centros (PENDIENTE).
//
// Cuando se implemente deberia recorrer el ABB y las listas para calcular:
//   - numero de ventas y de pizzas vendidas en cada centro,
//   - pizza mas vendida en total (sumando unidades),
//   - centro con mas pizzas vendidas.
// No se deben usar contadores globales: se calcula en el momento de pedirlo.
// ----------------------------------------------------------------------------
void napoli::mostrarEstadisticas()
{
    // Sin implementar
}


// ----------------------------------------------------------------------------
// OPCION 8: generar otro lote de N_VENTAS y distribuirlo.
//
// Pasos:
//   1. Crear una lista temporal vacia.
//   2. generarVentas(ventas): crea N_VENTAS ventas nuevas, asignadas a centros
//      que ya existen.
//   3. Mostrar las ventas generadas.
//   4. distribuirVentas(ventas): anyadirlas al final de las listas de sus
//      centros. No se sustituyen las ventas anteriores.
//   5. Mostrar el estado final del arbol.
// ----------------------------------------------------------------------------
void napoli::generarYDistribuirVentas()
{
    Lista ventas; // Lista temporal para las nuevas ventas

    // PASO 2: generar las ventas nuevas
    generarVentas(ventas);

    // PASO 3: mostrarlas antes de repartirlas
    cout << endl << "Ventas nuevas:" << endl;
    ventas.mostrar();

    // PASO 4: repartirlas entre los centros existentes
    distribuirVentas(ventas);

    // PASO 5: mostrar el estado final
    cout << "Ventas distribuidas. Estado del arbol:" << endl;
    centros.mostrar();
}
