#ifndef CENTRO_H
#define CENTRO_H

#include <Lista.h>

using namespace std;

//Definición de los tipos enumerados que utilizará Venta
enum Localidad {Mostoles, Alcala, Leganes, Fuenlabrada, Getafe, Alcorcon, Torrejon, Parla,
                Alcobendas, Coslada, Pozuelo, Rivas, Valdemoro, Majadahonda, Aranjuez, Arganda,
                Boadilla, Pinto, Colmenar, TresCantos, Azuqueca
               };

//Centro --> valor en NodoABB
struct Centro
{
    int id_centro;       //ID único del Centro de 3 cifras (100-999)
    Localidad localidad; //Localidad donde se encuentra el Centro
    Lista ventas;        //Lista de ventas asociadas al centro (inicialmente vacía)
};

int generarIDCentroRandom();                   //Genera un ID de centro aleatorio

Centro generarCentroRandom(int id = NULL);     //Genera un centro aleatorio (lista de ventas vacía)

string localidadToString(Localidad localidad); //Pasa del tipo enumerado Localidad a string

void copiarCentro(Centro& c1, Centro& c2);     //Copia toda la información del centro c1 en c2

void mostrarCentro(Centro& c);                 //Muestra el centro por pantalla

#endif // CENTRO_H
