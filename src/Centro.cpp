#include "Centro.h"

//Genera un ID de centro aleatorio
int generarIDCentroRandom()
{
    int id, DESDE = 100, HASTA = 999;
    id = rand() % (HASTA - DESDE + 1) + DESDE; //ID de centro aleatorio
    return id;
}

//Genera un centro aleatorio con la lista de ventas vacía
Centro generarCentroRandom(int id)
{
    Centro c; //Centro a devolver

    if(id == NULL)
    {
        c.id_centro = generarIDCentroRandom(); //Generamos id aleatorio
    }
    else
    {
        c.id_centro = id; //Si le pasamos un id, se lo asignamos al centro
    }

    Localidad local[] = {Mostoles, Alcala, Leganes, Fuenlabrada, Getafe, Alcorcon, Torrejon, Parla,
                         Alcobendas, Coslada, Pozuelo, Rivas, Valdemoro, Majadahonda, Aranjuez, Arganda,
                         Boadilla, Pinto, Colmenar, TresCantos, Azuqueca};

    c.localidad = local[rand() % (21)]; //Localidad aleatoria

    return c;
}

//Compara el ID de dos centros y devuelve True si son iguales
bool mismoID(Centro c1, Centro c2)
{
    return c1.id_centro == c2.id_centro;
}

//Pasa el tipo enumerado Localidad a string
string localidadToString(Localidad localidad)
{
    string resultado;
    switch(localidad)
    {
    case Mostoles:
        resultado = "Mostoles";
        break;
    case Alcala:
        resultado = "Alcala de Henares";
        break;
    case Leganes:
        resultado = "Leganes";
        break;
    case Fuenlabrada:
        resultado = "Fuenlabrada";
        break;
    case Getafe:
        resultado = "Getafe";
        break;
    case Alcorcon:
        resultado = "Alcorcon";
        break;
    case Torrejon:
        resultado = "Torrejon";
        break;
    case Parla:
        resultado = "Parla";
        break;
    case Alcobendas:
        resultado = "Alcobendas";
        break;
    case Coslada:
        resultado = "Coslada";
        break;
    case Pozuelo:
        resultado = "Pozuelo";
        break;
    case Rivas:
        resultado = "Rivas";
        break;
    case Valdemoro:
        resultado = "Valdemoro";
        break;
    case Majadahonda:
        resultado = "Majadahonda";
        break;
    case Aranjuez:
        resultado = "Aranjuez";
        break;
    case Arganda:
        resultado = "Arganda";
        break;
    case Boadilla:
        resultado = "Boadilla";
        break;
    case Pinto:
        resultado = "Pinto";
        break;
    case Colmenar:
        resultado = "Colmenar";
        break;
    case TresCantos:
        resultado = "Tres Cantos";
        break;
    case Azuqueca:
        resultado = "Azuqueca de Henares";
        break;
    defautl:
        resultado = "NULL";
    }
    return resultado;
}


//Muestra el Centro por pantalla con su información y la de todas sus ventas asociadas
void mostrar(Centro c)
{
    cout << left << "| " << c.id_centro     //ID del pedido
         << " | " << setw(7) << c.localidad //Localidad
         << " |";
    //c.ventas.mostrar();
}
