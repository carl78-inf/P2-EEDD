#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <iostream>
#include <string.h>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//Definición de los tipos enumerados que utilizará Venta
enum CategoriaPizza {Tradicional, Carne, Verduras, Quesos};

//Venta --> valor en NodoLista
struct Venta
{
    int id_centro;            //ID del centro (existente) al que está asociado la Venta
    string id_venta;          //ID único de la Venta (letra V seguida de 5 cifras)
    string cod_pizza;         //Código de la pizza vendida (NP01-NP08)
    CategoriaPizza categoria; //Categoría a la que pertenece esa pizza (dependiente de cod_pizza)
    int unidades;             //Número de pizzas incluidas en la Venta (1-20)
    string fecha_venta;       //Fecha en que se realizó la venta (formato DD-MM-2026)
};

int generarIDVentaRandom();               //Genera un ID de centro aleatorio

Centro generarVentaRandom(int id = NULL); //Genera una venta aleatoria (con el centro sin asignar)

bool mismoID(Venta v1, Venta v2);         //Compara el ID de dos ventas y devuelve True si son iguales

void mostrar(Venta v);                    //Muestra la información de la venta por pantalla en formato de tabla

#endif // VENTA_H
