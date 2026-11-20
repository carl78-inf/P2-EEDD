#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//Definición de los tipos enumerados que utilizará Venta
enum CategoriaPizza {Tradicional, Carne, Verduras, Quesos};

//Venta --> valor en NodoLista
struct Venta
{
    int id_centro = 0;        //ID del centro (existente) al que está asociado la Venta
    string id_venta;          //ID único de la Venta (letra V seguida de 5 cifras)
    string cod_pizza;         //Código de la pizza vendida (NP01-NP08)
    CategoriaPizza categoria; //Categoría a la que pertenece esa pizza (dependiente de cod_pizza)
    int unidades;             //Número de pizzas incluidas en la Venta (1-20)
    string fecha_venta;       //Fecha en que se realizó la venta (formato DD-MM-2026)
};

string generarIDVentaRandom();            //Genera un ID de centro aleatorio

Venta generarVentaRandom(string id = ""); //Genera una venta aleatoria (con el centro sin asignar)

void mostrarFila(Venta v);                //Muestra la información de la venta por pantalla en formato fila de tabla

#endif // VENTA_H
