#ifndef CLASES_H
#define CLASES_H

#include<iostream>
using namespace std;

void Crearlista(string Usuario){
    ofstream Archivo;
    string Lista;
    
    cout<<"Ingrese el nombre de la lista que desea crear."<<endl;
    cin>>Lista;

    Lista=Lista+".txt";
    string path= "Usuarios//"+Usuario+"//"+Lista;
    cout<<path<<endl;
    Archivo.open(path, ios::out);
}

#endif