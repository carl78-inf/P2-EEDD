#ifndef NAPOLI_H
#define NAPOLI_H

#include <Arbol.h>

#define N_CENTROS 10
#define N_VENTAS 30

#define N_LOCALIDADES 21

class napoli
{
private:
    Arbol centros; //ABB con todos los centros de la cadena

    bool idYaEnSistema(int id_centro);    //Devuelve True si el id_centro ya está registrado en el sistema
    bool idYaEnSistema(string id_venta);  //Devuelve True si el id_venta ya está registrado en el sistema

    void generarCentros();                //Genera N_CENTROS aleatorios y los añade al arbol de centros del sistema
    void generarVentas(Lista& ventas);    //Genera N_VENTAS aleatorias y las añade a la lista ventas
    void distribuirVentas(Lista& ventas); //Distribuye la lista de ventas entre los distintos centros del sistema

    void crearDatosIniciales();           //Crea los centros y las ventas del comienzo

    bool leerEntero(int& valor);          //Lee un entero por teclado controlando errores
    int pedirLocalidad();                 //Muestra las localidades y devuelve la elegida (-1 si error)

public:
    napoli();
    virtual ~napoli();

    void insertarCentro();           //Opcion 1: inserta un centro manualmente
    void borrarCentro();             //Opcion 2: elimina un centro por su identificador
    void mostrarVentasCentro();      //Opcion 3: muestra las ventas de un centro
    void buscarVenta();              //Opcion 4: busca una venta en todos los centros por su identificador
    void extraerVenta();             //Opcion 5: elimina una venta por su identificador
    void trasladarVenta();           //Opcion 6: se trasladara una venta a otro centro indicando el id_venta y el id_centro destino
    void mostrarEstadisticas();      //Opcion 7: muestra estadisticas (nº ventas, nº pizzas vendidas en cada centro, pizza mas vendida, centro con mas pizzas vendidas)
    void generarYDistribuirVentas(); //Opcion 8: se generara otro lote de N_VENTAS y se distribuira entre los centros del sistema

};

#endif // NAPOLI_H
