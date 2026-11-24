#ifndef NAPOLI_H
#define NAPOLI_H

#include <Arbol.h>

//Constantes principales de la simulacion
#define N_CENTROS 10
#define N_VENTAS 30

//Numero de localidades disponibles (enum Localidad de Centro.h)
#define N_LOCALIDADES 21

class napoli
{
private:
    Arbol centros; //ABB con todos los centros de la cadena

    bool leerEntero(int& valor); //Lee un entero por teclado controlando errores
    int pedirLocalidad();        //Muestra las localidades y devuelve la elegida (-1 si error)

    void crearDatosIniciales();  //Crea los centros y las ventas del comienzo

public:
    napoli();
    virtual ~napoli();

    void insertarCentro(); //Opcion 1: inserta un centro manualmente
    void mostrarVentasCentro(); //Opcion 3: muestra las ventas de un centro
    void buscarVenta();    //Opcion 4: busca una venta en todos los centros
};

#endif // NAPOLI_H
