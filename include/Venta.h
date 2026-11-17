#ifndef VENTA_H
#define VENTA_H

//Definición de los tipos enumerados que utilizará Venta
enum CategoriaPizza {Tradicional, Carne, Verduras, Quesos};

//Struct para el elemento Venta
struct Venta
{
    int id_centro;            //ID del centro al que está asociado la Venta
    string id_venta;          //ID único de la Venta (letra V seguida de 5 cifras)
    string cod_pizza;         //Código de la pizza vendida (NP01-NP07)
    CategoriaPizza categoria; //Categoría a la que pertenece esa pizza (dependiente de cod_pizza)
    int unidades;             //Número de pizzas incluidas en la Venta (1-20)
    string fecha_venta        //Fecha en que se realizó la venta (formato DD-MM-2026)
};

#endif // VENTA_H
