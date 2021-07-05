#include <iostream>
#include<string>
using namespace std;

//Declaracion de las estructuras
struct Libro{
    int codigo;
    string titulo;
    string autor;
    int ISBN;
    int anioDePublicacion;
};
struct Nodo{
    Libro dato;
    Nodo* sig;
    Nodo* ant;
};
struct Lista{
    Nodo* inicio;
    Nodo* final;
};

//Declaracion de la Pila
struct NodoPila{
    int codigo;
    string titulo;
    string autor;
    int anioDePublicacion;
    NodoPila * sig;
};
struct Pila{
    NodoPila* tope;
};

//Funciones para manipular las listas doblemente enlazadas

Lista crearListaVacia(Lista lista){
    lista.inicio= nullptr;
    lista.final= nullptr;
    return lista;
}

bool lista_vacia(Lista lista){
    if(lista.inicio == nullptr){
        return true;
    }
    return false;
}

Lista insertar_inicio(Lista lista, Nodo* nuevo){
    if(lista.inicio ==nullptr){
        lista.inicio = nuevo;
        lista.final = nuevo;
    }else{
        nuevo->sig =lista.inicio;
        lista.inicio->ant =nuevo;
        lista.inicio = nuevo;
    }
    return lista;
}
//Funcion de carga para lista enlazada doble de libros.
Lista cargarLibro(Lista lista){
    int codigo;
    string titulo;
    string autor;
    int ISBN;
    int anioDePublicacion;
    string respuesta;

    cout<<"Ingrese codigo de libro(0 para salir): " << endl;
    cin>>codigo;
    cout<<"Ingrese titulo de libro: ";
    getline(cin>>ws,titulo);
    cout<<"Ingrese autor de libro: ";
    getline(cin>>ws,autor);
    cout<<"Ingrese ISBN de libro: ";
    cin>>ISBN;
    cout<<"Ingrese año de publicacion: ";
    cin>>anioDePublicacion;
    cout<<endl;

    while(codigo !=0){
        Nodo* nodo = new Nodo();
        nodo->dato.codigo=codigo;
        nodo->dato.titulo=titulo;
        nodo->dato.autor=autor;
        nodo->dato.ISBN=ISBN;
        nodo->dato.anioDePublicacion=anioDePublicacion;
        nodo->ant = nullptr;
        nodo->sig = nullptr;

        lista =insertar_inicio(lista,nodo);

        cout<<"Otro libro.."<<endl;

        cout<<"Ingrese codigo de libro(0 para salir): " << endl;
        cin>>codigo;
        if(codigo == 0)
            break;
        cout<<"Ingrese titulo de libro: ";
        getline(cin>>ws,titulo);
        cout<<"Ingrese autor de libro: ";
        getline(cin>>ws,autor);
        cout<<"Ingrese ISBN de libro: ";
        cin>>ISBN;
        cout<<"Ingrese año de publicacion: ";
        cin>>anioDePublicacion;
        cout<<endl;

    }
    return lista;
}

//Funcion que recorre la lista y de coincidir el autor del libro con el datoBuscado por parametro devuelve true, caso contrario false
bool buscarAutor(Lista lista, string datoBuscado){
    for (Nodo* aux = lista.inicio; aux != nullptr; aux = aux->sig){
        if (aux->dato.autor == datoBuscado){
            return true;
        }
    }
    return false;
}

//Funcion que muestra informacion de determinado autor en el caso que el autor este en la lista enlazada doble
void mostrarInformacionDelAutor(Lista lista, string autor){
    if (buscarAutor(lista, autor)){
        for(Nodo * libro = lista.final; libro != nullptr; libro = libro->ant)
        {
            if(libro->dato.autor == autor)
            {
                cout<< "Titulo: "<< libro->dato.titulo<<"\t" <<"Anio publicado: " << libro->dato.anioDePublicacion<<"\n";
                cout<<endl;
            }
        }
    } else {
        cout <<"El autor no se encuentra en la lista" << endl;
    }
}

//Funciones para manipular las Pilas
bool pila_vacia(Pila pila){
    if(pila.tope == nullptr){
        return true;
    }
    return false;
}
NodoPila * crearPilaVacia(Pila pila){
    pila.tope = nullptr;
    return pila.tope;
}
Lista insertar_inicio_Pila(Lista lista, Nodo* nuevo){
    if(lista.inicio ==nullptr){
        lista.inicio = nuevo;
        lista.final = nuevo;
    }else{
        nuevo->sig =lista.inicio;
        lista.inicio->ant =nuevo;
        lista.inicio = nuevo;
    }
    return lista;
}
//Funcion que devuelve el tope pila del dato codigo.
int recuperar_tope_cod(Pila pila){
    if(pila.tope != nullptr){
        return(pila.tope->codigo);
    }
    return(pila.tope->codigo);
}
//Funcion que devuelve el tope pila del dato titulo.
string recuperar_tope_titu(Pila pila){
    if(pila.tope != nullptr){
        return(pila.tope->titulo);
    }
    return(pila.tope->titulo);
}
//Funcion que devuelve el tope pila del dato autor.
string recuperar_tope_aut(Pila pila){
    if(pila.tope != nullptr){
        return(pila.tope->autor);
    }
    return(pila.tope->autor);
}
//Funcion que devuelve el tope pila del dato anioDePublicacion.
int recuperar_tope_anio(Pila pila){
    if(pila.tope != nullptr){
        return(pila.tope->anioDePublicacion);
    }
    return(pila.tope->anioDePublicacion);
}


NodoPila * desapilar(Pila pila){
    NodoPila * aux;
    if(not(pila_vacia(pila))){
        aux = pila.tope;
        pila.tope = pila.tope->sig;
        delete aux;
    }

    return pila.tope;
}
NodoPila * apilar(Pila pila, NodoPila * nuevo){
    if(not(pila_vacia(pila)))
        nuevo->sig = pila.tope;
    pila.tope = nuevo;

    return pila.tope;
}
//Funcion para intercambiar pilas.
Pila intercambiar_pila(Pila pila, Pila pilaAux){
    while(not pila_vacia(pila)){
        NodoPila * nodo = new NodoPila();
        nodo->sig = nullptr;
        nodo->codigo = recuperar_tope_cod(pila);
        nodo->titulo = recuperar_tope_titu(pila);
        nodo->autor = recuperar_tope_aut(pila);
        nodo->anioDePublicacion = recuperar_tope_anio(pila);

        pilaAux.tope = apilar(pilaAux, nodo);
        pila.tope = desapilar(pila);
    }
    return(pilaAux);
}
//Funcion que apila ordenado recibiendo una pila y un nodo a apilar.
NodoPila* apilar_ordenado(Pila pila, NodoPila* nuevo){
    Pila pilaAux;
    pilaAux.tope = crearPilaVacia(pilaAux);

    if(pila_vacia(pila)){
        pila.tope = nuevo;
    }else{
        if(nuevo->anioDePublicacion <= pila.tope->anioDePublicacion){
            nuevo->sig = pila.tope;
            pila.tope = nuevo;
        }else{
            bool apile= false;
            while(not pila_vacia(pila)){
                NodoPila* nodoAux = new NodoPila();
                nodoAux->sig = nullptr;
                nodoAux->codigo = recuperar_tope_cod(pila);
                nodoAux->titulo = recuperar_tope_titu(pila);
                nodoAux->autor = recuperar_tope_aut(pila);
                nodoAux->anioDePublicacion = recuperar_tope_anio(pila);
                if(nodoAux->anioDePublicacion > nuevo->anioDePublicacion){
                    apile =true;
                    pilaAux.tope = apilar(pilaAux,nuevo);
                }
                pilaAux.tope = apilar(pilaAux, nodoAux);
                pila.tope = desapilar(pila);
            }
            if(not apile)pilaAux.tope = apilar(pilaAux, nuevo);
            pila.tope =crearPilaVacia(pila);
            pila = intercambiar_pila(pilaAux, pila);
        }
    }
    return pila.tope;
}
//Funcion que muestra los campos codigo, titulo y autor de cada nodo apilado en la pila.
Pila mostrar_pila(Pila pila){
    Pila pilaAux;
    pilaAux.tope = crearPilaVacia(pilaAux);
    while(not pila_vacia(pila)){
        NodoPila * nodo = new NodoPila();
        nodo->sig = nullptr;
        nodo->codigo = recuperar_tope_cod(pila);
        nodo->titulo = recuperar_tope_titu(pila);
        nodo->autor = recuperar_tope_aut(pila);

        cout<<"Codigo de libro: "<<nodo->codigo<<"\n";
        cout<<"Titulo de libro: "<<nodo->titulo<<"\n";
        cout<<"Autor de libro: "<<nodo->autor<<"\n";
        cout<<endl;


        pilaAux.tope = apilar(pilaAux, nodo);
        pila.tope = desapilar(pila);
    }

    pila.tope = crearPilaVacia(pila);
    pila = intercambiar_pila(pilaAux, pila);
    return(pila);
}
//Funcion que carga la pila con los datos contenidos en lista, en un intervalo del año 2019 a 2021.
NodoPila* cargar_pila(Pila pila,Lista lista){
   for(Nodo* aux = lista.inicio; aux != nullptr; aux = aux->sig)
   {
       if(aux->dato.anioDePublicacion >= 2019 && aux->dato.anioDePublicacion <= 2021){
           NodoPila* nodop = new NodoPila();
           nodop->codigo = aux->dato.codigo;
           nodop->titulo = aux->dato.titulo;
           nodop->autor = aux->dato.autor;
           nodop->anioDePublicacion = aux->dato.anioDePublicacion;
           nodop->sig = nullptr;

           pila.tope = apilar_ordenado(pila,nodop);
        }
   }
   return pila.tope;
}

int main()
{
    cout<<"Actividad Obligatoria 4 \t Jeremias Arriondo \t Martin Gauna "<<endl;
    cout<<endl;
    Lista lista;
    Pila pila;
    lista = crearListaVacia(lista);
    string autor;
    int opcion;
    do
    {
        cout <<"*Bienvenido al registro de libros de la biblioteca ATLAS" << endl;
        cout <<"\t MENU PRINCIPAL - Elija una opcion "<< endl;
        cout <<"1. Cargar libros en la biblioteca"<<endl;
        cout <<"2. Mostrar libros disponibles de algun autor" << endl;
        cout <<"3. Filtar libros entre rango de dos años" << endl;
        cout <<"4. Mostrar los datos de la Pila creada en el item 3." << endl;
        cout <<"0. Salir del registro." << endl;
        cin >> opcion;
        cin.ignore();
        switch(opcion)
        {
        case 1:
            cout<<"A continuacion se le pedira informacion sobre los libros.."<<endl;
            lista = cargarLibro(lista);
            break;
        case 2:
        {
            cout <<"Ingrese el autor del libro que desea obtener informacion"<<endl;
            cout<<endl;
            string autor;
            getline(cin>>ws, autor);
            mostrarInformacionDelAutor(lista, autor);
            break;
        }
        case 3:
        {
            cout<<"Filtrando libros entre el año 2019 y 2021 de manera ascendente*"<<endl;
            pila.tope = crearPilaVacia(pila);
            pila.tope = cargar_pila(pila, lista);
            break;

        }
        case 4:
        {
            pila = mostrar_pila(pila);
            break;
        }
        default:
            cout<<"Seleccione una opcion valida"<<endl;
        }
    } while(opcion != 0);

    return 0;
}
