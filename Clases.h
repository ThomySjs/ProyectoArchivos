#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <filesystem>
using namespace std;

void MenuPr(string);
void MenuListas(string, string, string);

void Crearlista(string Usuario){
    ofstream Archivo;
    string Lista;
    
    cout<<"Ingrese el nombre de la lista que desea crear."<<endl;
    cin>>Lista;

    Lista=Lista+".txt"; //Le agrega el txt para que el usuario no tenga que hacerlo
    string path= "Usuarios//"+Usuario+"//"+Lista; //La direccion donde se van a guardar las listas (Las listas son personales de cada usuario)
    

    if(filesystem::exists(path)){
        system("cls");
        cout<<"Ya existe una lista con ese nombre, prueba utilizando otro."<<endl;
        Crearlista(Usuario);
    }else{
        Archivo.open(path, ios::out); //Crea el archivo de la lista
        Archivo.close(); //Lo cerramos 
        system("cls");
        cout<<"Lista creada con exito!"<<endl;
        MenuPr(Usuario);
    }

}

void EliminarLista(string Usuario){
    string Lista;

    cout<<"Ingrese el nombre de la lista que desea eliminar"<<endl;
    cin>>Lista;

    Lista= Lista+".txt";
    string path = "Usuarios//"+Usuario+"//"+Lista;

    if(filesystem::exists(path)){ //Si el archivo existe, lo eliminamos, sino vuelve al menu anterior
        filesystem::remove(path);
        system("cls");
        cout<<"La lista fue eliminada con exito."<<endl;
        MenuPr(Usuario);
    }else{
        system("cls");
        cout<<"La lista que desea eliminar no existe."<<endl;
        MenuPr(Usuario);
    }

    
}

void ModificarLista(string Usuario){
    ofstream Archivo;
    string Lista, Lista1;
    
    cout<<"Ingrese el nombre de la lista que desea modificar: "<<endl;
    cin>>Lista;
    Lista1= Lista+".txt";
    string path = "Usuarios//"+Usuario+"//"+Lista1; //Lo mismo que las veces anteriores, cargamos la ubicacion de la lista dentro de la variable path
    if(filesystem::exists(path)){ //Si la lista que ingreso el usuario exise, entra en el menu de listas, sino vuelve al menu anterior
        system("cls");
        MenuListas(Lista, path, Usuario);

    }else{
        system("cls");
        cout<<"La lista no existe."<<endl;
        MenuPr(Usuario);
    }
}

void MenuListas(string Lista, string path, string Usuario){
    int Opcion;
    cout<<"\t\t Modificando: "<<" "<<Lista<<endl;
    do{
        cout<<"0: Volver."<<endl;
        cout<<"1: Cargar alumno."<<endl;
        cout<<"2: Modificar datos de un alumno."<<endl;
        cout<<"3: Quitar un alumno de la lista."<<endl;
        cout<<"4: Mostrar datos de un alumno."<<endl;
        cout<<"5: Mostrar lista completa."<<endl;
        cin>>Opcion;

        if(Opcion!=0 && Opcion!=1 && Opcion!=2 && Opcion!=3 && Opcion!=4 && Opcion!=5){
            system("cls");
            cout<<"Opcion incorrecta."<<endl;
        }
    }while(Opcion!=0 && Opcion!=1 && Opcion!=2 && Opcion!=3 && Opcion!=4 && Opcion!=5);

    switch(Opcion){
        case 0:
            system("cls");
            MenuPr(Usuario);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        
    }
}

void CargarAlumno(){

}

#endif