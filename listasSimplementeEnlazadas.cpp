#include <iostream>
#include <stdlib.h> //srand, rand
#include <cstdlib>
#include <string>
#include <time.h> //time
#include <iomanip> //La utilizamos para realizar la tabla con setw y utilizo setfill para rellenarlos espacios en la tabla

using namespace std;
//Declaracion estructura
struct Tiempo{
    string metodo;
    int tamanioArray;
    float tiempoMetodo;
    Tiempo* sig;
};
//Funciones de los metodos de ordenamiento
void burbuja(int arreglo[], int df){
    for(int i = 0; i <(df-i); i++){
        for(int j = 0; j <(df-i); j++){
            if (arreglo[j] > arreglo[j+1]){
                int aux = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = aux;
            }
        }
    }
}

void burbuja_mejorado(int arreglo[], int df){
    bool intercambio;
    int i = 0;
    do{
        intercambio = true;
        for(int j = 0; j <(df-i); j++){
            if (arreglo[j] > arreglo[j+1]){
                int aux = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = aux;
            }
            else
                intercambio = false;
        }
        i++;
    }while(intercambio == false);
}

void seleccion(int arreglo[], int df){
    for(int i = 0; i < (df-1); i++){
        int min = arreglo[i];
        int pos= i;
        for(int j = i+1; j < (df); j++){
            if(arreglo[j] < min){
                min = arreglo[j];
                pos = j;
            }
        }
        if(min < arreglo[i]){
            int aux = arreglo[i];
            arreglo[i] = min;
            arreglo[pos] = aux;
        }
    }
}

void insercion(int arreglo[], int df){
    for(int i = 1; i< df; i++){
        int aux = arreglo[i];
        int j = i - 1;

        while(j >= 0 && aux < arreglo[j]){
                arreglo[j+1] = arreglo[j];
                j--;
        }
        arreglo[j+1]= aux;
    }
}

void shell(int arreglo[], int df){
    for(int salto= ((df)/2); salto != 0; salto/=2){
        bool cambios = true;
        while(cambios){
            for(int i = salto; i < df; i++){
                if(arreglo[i-salto] > arreglo[i]){
                    int aux = arreglo[i];
                    arreglo[i] = arreglo[i-salto];
                    arreglo[i-salto] = aux;
                    cambios = false;
                }
            }
        }
    }
}

void quicksort(int arreglo[], int primero, int ultimo){
    int i=primero;
    int j=ultimo;
    float central = arreglo[(primero+ultimo)/2];
    float temp;
    do
    {
        while(central>arreglo[i])i++;
        while(central<arreglo[j])j--;
        if(i<=j)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
            i++;
            j--;
        }
    }while(i<=j);
    if(primero<j) quicksort(arreglo, primero,j);
    if(ultimo>i) quicksort(arreglo, i,ultimo);

}
//Funcion para mostrar el array
void mostrar_array(int array[], int dl){
    cout<<"\t";
    for(int i=0; i<dl; i++){
        cout << array[i] << ",";
    }
}
//Funcion para llenar un array con numeros aleatorios en un rango de 1-100
int llenar_array(int array[], int dimensionLogica){
    int dl = dimensionLogica;
    srand(time(NULL));
    for(int i=0; i<dimensionLogica; i++){
        //lleno el array con numeros en un rango de 1-100
        array[i]= rand() % 100 + 1;

    }
    return dl;
}

//Funciones Listas simples
//Utilizamos listas simples para llevar la informacion de los metodos y su respectivos tiempos
Tiempo* insertarPrincipio(Tiempo* inicio, Tiempo* nuevo){
    nuevo->sig = inicio;
    return nuevo;
    }

Tiempo* cargaDeTiempo(Tiempo* inicio, float tiempo, string metodo, int tArray){
    Tiempo* nuevo;

    nuevo = new Tiempo;
    nuevo->metodo = metodo;
    nuevo->tamanioArray = tArray;
    nuevo->tiempoMetodo = tiempo;

    nuevo->sig = nullptr;

    inicio = insertarPrincipio(inicio, nuevo);
    return inicio;
}
//Funcion para visualizar una tabla con los datos respectivos de los tiempos y metodos
void mostrarTabla(Tiempo* inicio){
    cout << setw(65) << setfill( '-' ) << '\n' << setfill( ' ' );
    /*Utilizo setw para modificar el ancho de la salida
     * y setfill para modificar cada espacio y convertirlo a lo que desee,
     * en nuestro caso utilizamos guiones y espacio vacios
    */
    cout << "|"
         << left << setw(25) << "Metodo:"
         << "|"
         << right << setw(20) << "Tamanio array:"
         << "|"
         << right << setw(15) << "Duracion:"
         << "|"
         << '\n';
    for (Tiempo* i = inicio; i != nullptr; i = i->sig)
    {
       cout << "|"
            << setw(25) << i->metodo
            << "|"
            << right << setw(20) << i->tamanioArray
            << "|"
            << right << setw(15) << i->tiempoMetodo
            << "|"
            << endl;
    }
    cout << setw(65) << setfill( '-' ) << '\n' << setfill( ' ' );
    cout<<"DATOS DE LA PC:\nProcesador: Intel Core i5-7600K\nRAM: 8GB\nSistema operativo: Windows 10 PRO\n";
    cout<<endl;
}
//Menu para poder optar por los distintos metodos de ordenamiento
Tiempo* menu_ordenamiento(int array[], int dl, Tiempo* inicio){
    int opcionAlgoritmo;
    string metodo;
    do{
        cout <<"Elija un metodo de ordenamiento"<<endl;
        cout <<"1) Burbuja\n2) Burbuja mejorado\n3) Seleccion\n4) Insercion\n5) Shell\n6) Quicksort\n"<<endl;
        cout <<"0 Para volver al menu principal"<<endl;
        cin>> opcionAlgoritmo;

        switch (opcionAlgoritmo)
        {
            case 1:
                cout << "Usted ha elegido el metodo burbuja"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                float tiempo;
                mostrar_array(array, dl);
                clock_t TBurbuja;
                TBurbuja = clock();
                burbuja(array, dl);
                TBurbuja = clock() - TBurbuja;
                tiempo = float(TBurbuja)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo burbuja queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Burbuja",dl);
                break;

            case 2:
            {
                cout << "Usted ha elegido el metodo burbuja mejorado"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                mostrar_array(array, dl);
                float tiempo;
                clock_t TBurbujaM;
                TBurbujaM = clock();
                burbuja_mejorado(array, dl);
                TBurbujaM = clock() - TBurbujaM;
                tiempo= float(TBurbujaM)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo burbuja mejorado queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Burbuja mejorado",dl);
                break;
             }

            case 3:
            {
                cout << "Usted ha elegido el metodo seleccion"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                mostrar_array(array, dl);
                float tiempo;
                clock_t TSelec;
                TSelec = clock();
                seleccion(array, dl);
                TSelec = clock() - TSelec;
                tiempo = float(TSelec)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo seleccion queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Seleccion", dl);
                break;
             }

            case 4:
        {
                cout << "Usted ha elegido el metodo insercion"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                mostrar_array(array, dl);
                float tiempo;
                clock_t TInsercion;
                TInsercion = clock();
                insercion(array, dl);
                TInsercion = clock() - TInsercion;
                tiempo = float(TInsercion)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo insercion queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Insercion", dl);
                break;
        }
            case 5:
        {
                cout << "Usted ha elegido el metodo shell"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                mostrar_array(array, dl);
                float tiempo;
                clock_t TShell;
                TShell = clock();
                shell(array, dl);
                TShell = clock() - TShell;
                tiempo = float(TShell)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo shell queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Shell", dl);
                break;
        }
            case 6:
        {
                cout << "Usted ha elegido el metodo quicksort"<<endl;
                cout <<"Tu array sin ordenar es el siguiente"<<endl;
                mostrar_array(array, dl);
                float tiempo;
                clock_t TQuicksort;
                TQuicksort = clock();
                quicksort(array,0, dl);
                TQuicksort = clock() - TQuicksort;
                tiempo = float(TQuicksort)/CLOCKS_PER_SEC;
                cout <<"\nEl array ordenado con el metodo quicksort queda asi"<<endl;
                mostrar_array(array, dl);
                cout<<endl;
                inicio = cargaDeTiempo(inicio, tiempo, "Quicksort",dl);
                break;
        }
        }
    } while (opcionAlgoritmo != 0);
    return inicio;
}

int main()
{

    cout <<"\tAlgoritmos de ordenamiento" << endl;
    int opcionArray;
    Tiempo* inicio = nullptr;

    do
    {
        cout << setw(30) << "* Menu principal *"<<endl;
        cout <<"Por favor, elija el tamanio del array que desee utilizar"<<endl;
        cout <<"1) 50.000\n2) 100.000\n3) 500.000\n4)Tiempos de los metodos empleados(ejecutar una vez realizados los ordenamientos deseados)\n0)Salir del programa"<<endl;
        cout <<""<<endl;
        cin >> opcionArray;
        switch (opcionArray)
        {
            case 1:
                int arrayUno[50000], dlUno;
                cout << "Ingrese cuantos numeros desea agregar al array"<<endl;
                cout <<"\tMaximo 50000 numeros\nEl array se llenara con numeros aleatorios"<<endl;
                cin >> dlUno;
                llenar_array(arrayUno, dlUno);
                inicio = menu_ordenamiento(arrayUno, dlUno, inicio);break;
            case 2:
                int arrayDos[100000], dlDos;
                cout << "\tIngrese cuantos numeros desea agregar al array"<<endl;
                cout <<"\tMaximo 100000 numeros\nEl array se llenara con numeros aleatorios"<<endl;
                cin >> dlDos;
                inicio = menu_ordenamiento(arrayDos, dlDos, inicio); break;
            case 3:
                int arrayTres[500000], dlTres;
                cout << "\tIngrese cuantos numeros desea agregar al array"<<endl;
                cout <<"\tMaximo 500000 numeros\nEl array se llenara con numeros aleatorios"<<endl;
                cin >> dlTres;
                inicio = menu_ordenamiento(arrayTres, dlTres, inicio); break;
            case 4:
                mostrarTabla(inicio);break;
        }
    } while (opcionArray != 0);
        cout<<"Gracias por utilizar nuestro programa!\nVuelva pronto..."<<endl;
    return 0;
}
