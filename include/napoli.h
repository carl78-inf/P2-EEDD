#ifndef NAPOLI_H
#define NAPOLI_H

#include <Arbol.h>

// ============================================================================
// CONSTANTES PRINCIPALES DE LA SIMULACION
// ============================================================================

// Numero de centros que se crean automaticamente al arrancar el programa.
#define N_CENTROS 10

// Numero de ventas aleatorias que se generan en cada lote:
// - en la creacion inicial,
// - y en la opcion 8 (generar y distribuir nuevas ventas).
#define N_VENTAS 30

// Numero de localidades distintas que tiene el enum Localidad (Centro.h).
// Se usa para recorrer el enum y para validar la opcion que escribe el usuario.
#define N_LOCALIDADES 21

// ============================================================================
// CLASE napoli
// ----------------------------------------------------------------------------
// Es la capa de aplicacion del programa. Guarda el ABB de centros y ofrece un
// metodo publico por cada opcion del menu. main() solo crea un objeto napoli y
// llama al metodo de la opcion elegida.
//
// IMPORTANTE: dentro de esta clase NO se usan punteros ni memoria dinamica.
// Toda la gestion de nodos queda encapsulada en Arbol y Lista. Aqui solo se
// piden datos al usuario, se validan y se llama a los metodos del Arbol.
// ============================================================================
class napoli
{
private:
    // ABB con todos los centros de la cadena. Es el estado persistente del
    // programa: vive mientras exista el objeto napoli y, por tanto, se conserva
    // entre una opcion y la siguiente del menu.
    Arbol centros;

    // ------------------------------------------------------------------
    // METODOS AUXILIARES PRIVADOS
    // ------------------------------------------------------------------

    // Devuelve true si ya existe un centro con ese id_centro en el ABB.
    // Se usa para no insertar dos centros con el mismo identificador.
    bool idYaEnSistema(int id_centro);

    // Devuelve true si ya existe una venta con ese id_venta en cualquier lista
    // de cualquier centro del ABB. Se usa para que los ids de venta sean
    // unicos durante toda la ejecucion.
    bool idYaEnSistema(string id_venta);

    // Crea N_CENTROS centros aleatorios y los inserta en el ABB.
    // Cada centro recibe un id aleatorio no repetido y una localidad aleatoria.
    // La lista de ventas de cada centro se crea vacia automaticamente.
    void generarCentros();

    // Genera N_VENTAS ventas aleatorias y las guarda al final de la lista
    // "ventas" que recibe por referencia. Todavia NO estan metidas en los
    // centros: solo estan en esa lista temporal.
    // Cada venta recibe:
    //   - un id_venta unico,
    //   - un id_centro elegido entre los centros que ya existen en el ABB,
    //   - el resto de campos aleatorios (pizza, categoria, unidades, fecha).
    void generarVentas(Lista& ventas);

    // Recorre la lista "ventas" y mete cada venta en la lista del centro
    // indicado por su id_centro. Las ventas se anyaden al final.
    void distribuirVentas(Lista& ventas);

    // Une los pasos anteriores para la creacion inicial que se ejecuta al
    // arrancar: generar centros, generar ventas, mostrarlas, esperar Enter,
    // distribuirlas y mostrar el estado final del arbol.
    void crearDatosIniciales();

    // Lee un numero entero positivo por teclado sin usar cin.fail().
    // Lee el texto, comprueba que todos los caracteres sean digitos y lo
    // convierte a int. Devuelve false si el usuario no ha escrito un numero.
    // El resultado se guarda en "valor" (parametro de salida).
    bool leerEntero(int& valor);

    // Muestra por pantalla las N_LOCALIDADES localidades numeradas (1..21)
    // y pide una opcion. Devuelve el indice del enum Localidad (0..20) o -1
    // si la opcion no es valida.
    int pedirLocalidad();

public:
    // Constructor: crea el objeto y llama a crearDatosIniciales(), por lo que
    // al construir "napoli app" en main ya se crean los 10 centros y las 30
    // ventas iniciales.
    napoli();

    // Destructor: no hace nada porque el destructor de Arbol libera todos los
    // nodos y, en cadena, todas las listas de ventas.
    virtual ~napoli();

    // ------------------------------------------------------------------
    // METODOS PUBLICOS: UNO POR CADA OPCION DEL MENU
    // ------------------------------------------------------------------

    // Opcion 1: pide un id y una localidad y crea un centro manualmente.
    // Si el id ya existe, informa del error y NO modifica el arbol.
    void insertarCentro();

    // Opcion 2: pide un id y elimina ese centro del arbol con todas sus ventas.
    void borrarCentro();

    // Opcion 3: pide un id y muestra la localidad y las ventas de ese centro.
    void mostrarVentasCentro();

    // Opcion 4: pide un id_venta y lo busca en todos los centros.
    void buscarVenta();

    // Opcion 5: elimina una venta por su identificador (PENDIENTE).
    void extraerVenta();

    // Opcion 6: traslada una venta a otro centro (PENDIENTE).
    void trasladarVenta();

    // Opcion 7: muestra estadisticas de los centros (PENDIENTE).
    void mostrarEstadisticas();

    // Opcion 8: genera otro lote de N_VENTAS y lo distribuye entre los centros.
    void generarYDistribuirVentas();
};

#endif // NAPOLI_H
