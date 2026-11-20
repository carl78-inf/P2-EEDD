#include <iostream>

#include <napoli.h>

using namespace std;

void pruebas()
{
    cout << "Pruebas de implementacion de listas" << endl;
    cout << "-----------------------------------" << endl;
    Venta v1, v2, v3, v4;

    //Generamos 6 ventas aleatorias
    v1 = generarVentaRandom();
    v2 = generarVentaRandom();
    v3 = generarVentaRandom();
    v4 = generarVentaRandom();
    Lista l;

    //Lista vacía
    cout << "\n+ Lista vacia" << endl;
    l.mostrar();

    cout << "\n+ Insertamos en lista vacia" << endl;
    cout << "  - Caso 1 / insertar(0) -> ";
    l.insertar(v1, 0);
    cout << "  - Caso 2 / insertar(n) -> ";
    l.insertar(v1, 5);
    cout << "  - Caso 3 / insertar(-1) -> Caso por defecto" << endl;
    l.insertar(v1);
    l.mostrar();

    //Insertar
    cout << "\n+ Insertamos al principio de la lista" << endl;
    l.insertar(v2, 0);
    l.mostrar();

    cout << "\n+ Insertamos al final de la lista" << endl;
    l.insertar(v3);
    l.mostrar();

    cout << "\n+ Insertamos en una posicion intermedia (1)" << endl;
    l.insertar(v4, 1);
    l.mostrar();

    cout << "\n+ Insertamos en una posicion erronea (5)" << endl;
    l.insertar(v4, 5);

    //Obtener
    cout << "\n+ Obtenemos todas las ventas de la lista / obtener(n) y una erronea" << endl;
    for(int i = 0; i < l.getLongitud(); i++)
    {
        cout << "  - ID / pos = " << i << " -> " << l.obtener(i).id_venta << endl;
    }
    cout << "  - ID / pos = " << l.getLongitud() << " -> ";
    l.obtener(l.getLongitud());

    //Modificar
    Venta v5, v6, v7;
    v5 = generarVentaRandom();
    v6 = generarVentaRandom();
    v7 = generarVentaRandom();
    cout << "\n+ Modificamos el primer elemento" << endl;
    l.modificar(v5, 0);
    l.mostrar();

    cout << "\n+ Modificamos el ultimo elemento" << endl;
    l.modificar(v6, l.getLongitud()-1);
    l.mostrar();

    cout << "\n+ Modificamos una posicion intermedia (2)" << endl;
    l.modificar(v7, 2);
    l.mostrar();

    cout << "\n+ Modificamos una posicion erronea (5)" << endl;
    l.modificar(v7, 5);

    //Eliminar
    cout << "\n+ Eliminamos el primer elemento" << endl;
    l.eliminar(0);
    l.mostrar();

    cout << "\n+ Eliminamos una posicion intermedia (1)" << endl;
    l.eliminar(1);
    l.mostrar();

    cout << "\n+ Eliminamos el ultimo elemento" << endl;
    l.eliminar(l.getLongitud()-1);
    l.mostrar();

    cout << "\n+ Eliminamos una posicion erronea (5)" << endl;
    l.eliminar(5);

    cout << "\n+ Eliminamos el unico elemento de la lista" << endl;
    l.eliminar(0);
    l.mostrar();

    cout << "\n+ Insertamos la venta: " << v1.id_venta << endl;
    l.insertar(v1);
    l.mostrar();

    //Ver si está la venta en la lista
    cout << "\n+ Comprobamos si distintas ventas estan en la lista" << endl;
    cout << "  - " << v1.id_venta << ": " << (l.estaEnLista(v1.id_venta)? "True": "False") << endl;
    cout << "  - " << v2.id_venta << ": " << (l.estaEnLista(v2.id_venta)? "True": "False") << endl;
    cout << "  - " << v3.id_venta << ": " << (l.estaEnLista(v3.id_venta)? "True": "False") << endl;
    cout << "  - " << v4.id_venta << ": " << (l.estaEnLista(v4.id_venta)? "True": "False") << endl;
    cout << "  - " << v5.id_venta << ": " << (l.estaEnLista(v5.id_venta)? "True": "False") << endl;
    cout << "  - " << v6.id_venta << ": " << (l.estaEnLista(v6.id_venta)? "True": "False") << endl;
    cout << "  - " << v7.id_venta << ": " << (l.estaEnLista(v7.id_venta)? "True": "False") << endl;

    cout << "\n+ Comprobamos en una lista vacia" << endl;
    l.eliminar(0);
    l.mostrar();
    cout << "  - " << v1.id_venta << ": " << (l.estaEnLista(v1.id_venta)? "True": "False") << endl;

    //Buscar
    cout << "\n+ Buscamos " << v1.id_venta << " en una lista vacia" << endl;
    cout << v1.id_venta << " en la posicion: " << (l.buscar(v1.id_venta) == -1 ? "No encontrado": to_string(l.buscar(v1.id_venta))) << endl;

    cout << "\n+ Buscamos " << v1.id_venta << " en una lista llena" << endl;
    l.insertar(v7);
    l.insertar(v5);
    l.insertar(v2);
    l.insertar(v1);
    l.insertar(v4);
    l.mostrar();
    cout << v1.id_venta << " en la posicion: " << (l.buscar(v1.id_venta) == -1 ? "No encontrado": to_string(l.buscar(v1.id_venta))) << endl;

    cout << "\n+ Buscamos " << v3.id_venta << " en la lista llena" << endl;
    cout << v3.id_venta << " en la posicion: " << (l.buscar(v3.id_venta) == -1 ? "No encontrado": to_string(l.buscar(v3.id_venta))) << endl;

    //Concatenar
    cout << "\n+ Creamos dos listas vacias" << endl;
    Lista l2, l3;
    l2.mostrar();
    l3.mostrar();

    cout << "\n+ Concatenamos las listas" << endl;
    l2.concatenar(l3);
    l2.mostrar();

    cout << "\n+ Llenamos la primera lista" << endl;
    l2.insertar(v1);
    l2.insertar(v2);
    l2.insertar(v3);
    l2.insertar(v4);
    l2.mostrar();
    l3.mostrar();

    cout << "\n+ Concatenamos las listas" << endl;
    l2.concatenar(l3);
    l2.mostrar();

    cout << "\n+ Llenamos la segunda lista" << endl;
    l3.insertar(v5);
    l3.insertar(v6);
    l3.insertar(v7);
    l2.mostrar();
    l3.mostrar();

    cout << "\n+ Concatenamos las listas" << endl;
    l2.concatenar(l3);
    l2.mostrar();

    cout << "\n+ Vaciamos la primera lista" << endl;
    l2.eliminar();
    l2.eliminar();
    l2.eliminar();
    l2.eliminar();
    l2.eliminar();
    l2.eliminar();
    l2.eliminar();
    l2.mostrar();
    l3.mostrar();

    cout << "\n+ Concatenamos las listas" << endl;
    l2.concatenar(l3);
    l2.mostrar();

    cout << "\n+ Concatenamos con ella misma" << endl;
    l2.concatenar(l2);
    l2.mostrar();

    //Centro
    cout << "\n+ Creamos un centro" << endl;
    Centro c1;
    c1 = generarCentroRandom();
    mostrarCentro(c1);

    cout << "\n+ Asignamos ventas al centro" << endl;
    c1.ventas.copiar(l);
    mostrarCentro(c1);
}

int main()
{
    srand(time(NULL)); //Una vez en todo el programa para que funcione rand()

    int option; //Opción elegida

    do
    {
        cout << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "|            SIMULACION PIZZERIA NAPOLI            |" << endl;
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
        cout << "|                                                  |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "|  99 --> Pruebas                                  |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "Seleccion > ";

        cin >> option; cout << endl;

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

        //Salir
        case 99:
            pruebas();
            break;

        //Caso base para opción no válida
        default:
            cout << "Opcion no valida." << endl;
        }

    }
    while (option != 0);

    return 0;
}
