#include <iostream>


using namespace std;

int main()
{
    srand(time(NULL)); //Una vez en todo el programa para que funcione rand()

    int option; //Opción elegida

    do
    {
        cout << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "|      SIMULACION CENTRO CONTROL PIZZERIA          |" << endl;
        cout << "|                  NAPOLI                          |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "|  1. Insertar un centro                           |" << endl;
        cout << "|  2. Borrar un centro                             |" << endl;
        cout << "|  3. Mostrar las ventas de un centro              |" << endl;
        cout << "|  4. Buscar una venta                             |" << endl;
        cout << "|  5. Extraer una venta                            |" << endl;
        cout << "|  6. Trasladar una venta a otro centro            |" << endl;
        cout << "|  7. Mostrar estadisticas de los centros          |" << endl;
        cout << "|  8. Generar y distribuir nuevas ventas           |" << endl;
        cout << "|  0. Salir                                        |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "Seleccion > ";

        cin >> option;

        switch (option)
        {

        case 1:
            // Sin implementar

            break;

        case 2:
            // Sin implementar
            break;

        case 3:
            // Sin implementar
            break;

        case 4:
            // Sin implementar
            break;

        case 5:
            // Sin implementar
            break;

        case 6:
            // Sin implementar
            break;

        case 7:
            // Sin implementar
            break;

        case 8:
            // Sin implementar
            break;

        //Salir
        case 0:
            cout << "Saliendo" << endl;
            break;

        //Caso base para opción no válida
        default:
            cout << "Opcion no valida." << endl;
        }

    }
    while (option != 0);

    return 0;
}
