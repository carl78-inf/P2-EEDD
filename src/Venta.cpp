#include "Venta.h"

//Genera un ID de venta aleatoria
string generarIDVentaRandom()
{
    string id = "V";
    for (int i = 0; i < 5; i++)
    {
        id += ('0' + (rand() % 10)); //Genera un cáracter aleatorio entre '0' y '9'
    }
    return id;
}

//Genera una venta aleatoria
Venta generarVentaRandom(string id)
{
    Venta v; //Venta a devolver

    if(id == "")
    {
        v.id_venta = generarIDVentaRandom(); //Generamos id aleatorio
    }
    else
    {
        v.id_venta = id; //Si le pasamos un id, se lo asignamos al pedido
    }

    int num = rand() % 8 + 1;
    v.cod_pizza = "NP0";
    v.cod_pizza += ('0' + num); //Código de pizza aleatorio

    //Categoría correspondiente según el código de pizza
    switch(num)
    {
        case 1:
            v.categoria = Tradicional;
            break;
        case 2:
            v.categoria = Tradicional;
            break;
        case 3:
            v.categoria = Carne;
            break;
        case 4:
            v.categoria = Carne;
            break;
        case 5:
            v.categoria = Verduras;
            break;
        case 6:
            v.categoria = Verduras;
            break;
        case 7:
            v.categoria = Quesos;
            break;
        case 8:
            v.categoria = Quesos;
            break;
    }

    v.unidades = rand() % 20 + 1; //Número de pizzas aleatorio entre 1 y 20

    int mes, dias_en_mes, dia; //Variables para mes, días en el mes y día concreto

    mes = 1 + rand() % 12; //Mes aleatorio

    //Establecemos el número de días según el mes
    if(mes == 2)
    {
        dias_en_mes = 28; //Febrero en 2026
    }
    else if (mes == 4 || mes == 6 | mes == 9 | mes == 11)
    {
        dias_en_mes = 30; //Abril, Junio, Septiembre, Noviembre
    }
    else
    {
        dias_en_mes = 31; //Resto de meses
    }

    dia = 1 + rand() % dias_en_mes; //Día aleatorio y válido según el mes

    //Fecha aleatoria con formato DD-MM-2026
    string dia_str = (dia < 10) ? ("0" + to_string(dia)) : to_string(dia);
    string mes_str = (mes < 10) ? ("0" + to_string(mes)) : to_string(mes);

    v.fecha_venta = dia_str + "-" + mes_str + "-2026";

    return v;
}

//-----------------------------------------------------------------------------------------------//

//Pasa el tipo enumerado CategoriaPizza a string
string categoriaPizzaToString(CategoriaPizza categoria)
{
    string resultado;
    switch(categoria)
    {
    case Tradicional:
        resultado = "Tradicional";
        break;
    case Carne:
        resultado = "Carne";
        break;
    case Verduras:
        resultado = "Verduras";
        break;
    case Quesos:
        resultado = "Quesos";
        break;
    defautl:
        resultado = "NULL";
    }
    return resultado;
}

//-----------------------------------------------------------------------------------------------//

//Muestra la Venta por pantalla en formato de fila de una tabla para la lista
void mostrarFila(Venta v)
{
    cout << left
         << "| " << setw(9) << v.id_centro                           //ID del centro
         << " | " << setw(8) << v.id_venta                           //ID de la venta
         << " | " << setw(12) << v.cod_pizza                         //Código de la pizza
         << " | " << setw(11) << categoriaPizzaToString(v.categoria) //Categoría
         << " | " << setw(8) << v.unidades                           //Numero de pizzas incluidas
         << " | " << v.fecha_venta                                   //Fecha de la venta
         << " |";
}
