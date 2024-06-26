#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include "clases.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

struct Alumno{
    char Nombre[20];
    int Edad;
    char Ciudad[30];
};

void Lectura();
void Menu();
void Login(string, string);
void MenuPr(string);
void CargarLista(string, ofstream[], Alumno[]);
void Registro(string, string);
void CompararUsuarioExistente(string, string, bool&);


int main(){
    ofstream archivo[4];
    Alumno alumnos[100];
    string nombrearchivo;
    int i=0;
    
    fs::create_directory("Usuarios"); //Crear una carpeta para los usuarios registrados


    Menu(); //Menu de login o registro


    return 0;
}

void Menu(){
    ifstream Cuentas;
    int Opcion;
    string Usuario, Contraseña;
    do{
        cout<<"1 Ingresar."<<endl;
        cout<<"2 Registrarse."<<endl;
        cin>>Opcion;

        if(Opcion!=1 && Opcion!=2){
            system("cls");
            cout<<"Opcion incorrecta."<<endl;
        }
    }while(Opcion!=1 && Opcion!=2);

    switch(Opcion){
        case 1: 
            system("cls");
            Login(Usuario, Contraseña);
            break;
        case 2:
            system("cls");
            Registro(Usuario, Contraseña);
            break;
        
    }
}

void MenuPr(string Usuario){
    int Opcion;
    do{
        cout<<"1: Crear una lista de alumnos."<<endl;
        cout<<"2: Eliminar una lista de alumnos."<<endl;
        cout<<"3: Acceder a una lista (cargar alumnos, modificar, etc)"<<endl;
        cout<<"4: Mostrar listas."<<endl;
        cout<<"5: Cerrar sesion."<<endl;
        cin>>Opcion;

        if(Opcion!=1 && Opcion!=2 && Opcion!=3 && Opcion!=4 && Opcion!=5 && Opcion!=6 && Opcion!=7 && Opcion!=8 && Opcion!=9 && Opcion!=10){
            system("cls");
            cout<<"Opcion incorrecta."<<endl;
        }
    }while(Opcion!=1 && Opcion!=2 && Opcion!=3 && Opcion!=4 && Opcion!=5 && Opcion!=6 && Opcion!=7 && Opcion!=8 && Opcion!=9 && Opcion!=10);

    switch(Opcion){
        case 1:
            system("cls");
            Crearlista(Usuario);
            break;
        case 2:
            system("cls");
            EliminarLista(Usuario);
            break;
        case 3:
            system("cls");
            ModificarLista(Usuario);
            break;
        case 4:
            break;
        case 5:
            system("cls");
            Menu();
            break;
    }
}

void Login(string Usuario, string Contraseña){
    ifstream Cuentas;
    string linea, us, con;
    int x;
    bool Encontrado = false; 
    Cuentas.open("Cuentas.txt");
    if(Cuentas.fail()){ //Error que se muestra si no hay ninguna cuenta registrada
        system("cls");
        cout<<"Todavia no hay ninguna cuenta registrada."<<endl;
        Menu();
    }else{
        cout<<"Usuario: "<<endl;
        cin>>Usuario;
        cout<<"Contrasenia: "<<endl;
        cin>>Contraseña;

        //Mientras haya lineas para leer, seguir el bucle
        while(getline(Cuentas, linea)){
            stringstream ss(linea); //Pasa toda la linea que lee al objeto ss
            string valor;
            x=0;
            while(getline(ss, valor, ',')){
                if(x==0){ //Esto hace que el primer valor que lee (El usuario) se guarde en la variable us.
                    us=valor;
                    x++;
                }else if(x==1){//Esto hace que el segundo valor (Contraseña) se guarde en la variable con.
                    cout<<valor<<endl;
                    con=valor;
                }
            }

            if(Usuario==us && Contraseña==con){ //Esto comprueba el usuario y contraseña ingresados con cada linea del archivo.
                Encontrado=true;
                break;
            }


        }
        //Si el logueo es exitoso
            if(Encontrado==true){
                system("cls");
                cout<<"Logueo exitoso! entrando..."<<endl;
                this_thread::sleep_for(chrono::seconds(3)); //Esperar 3 segundos para darle tiempo al usuario a leer "Logueo exitoso" antes del system cls
                system("cls");
                cout<<"\t\t Bienvenid@"<<" "<<Usuario<<endl;
                MenuPr(Usuario);
            }else{
                system("cls");
                cout<<"Usuario o contrasenia incorrectas, vuelve a intentarlo."<<endl;
                Login(Usuario, Contraseña);
            }
    }
}

void Registro(string Usuario, string Contraseña){
    ofstream Cuentas;
    ifstream CuentasL;
    string linea;
    bool Existe=false;
    Cuentas.open("Cuentas.txt", ios::out | ios::app); //ios::app hace que el nuevo usuario se guarde en la ultima linea del archivo

    cout<<"Ingrese su usuario: "<<endl;
    cin>>Usuario;
    cout<<"Ingrese la contrasenia: "<<endl;
    cin>>Contraseña;
    
    CompararUsuarioExistente(Usuario, Contraseña, Existe);

    if(Existe==true){
        system("cls");
        cout<<"El usuario ya existe!"<<endl;
        Cuentas.close();
        Registro(Usuario, Contraseña);
    }else{
        fs::path fullpath= fs::path("Usuarios") / Usuario; //Guarda la direccion donde quiero crear las carpetas y el nombre en la variable fullpath
        Cuentas<<Usuario<<","<<Contraseña<<endl;
        system("cls");
        cout<<"Usuario registrado con exito!"<<endl;
        fs::create_directory(fs::path(fullpath)); //Crea la carpeta del usuario donde va a tener sus listas.
        Menu();
        Cuentas.close();
    }
    
}


void CompararUsuarioExistente(string Usuario, string Contraseña, bool &Existe){
    ifstream CuentasL;
    string linea, us, con;
    int contador;

    //Leer el archivo para comparar si ya existe el usuario
    CuentasL.open("Cuentas.txt");

    if(CuentasL.fail()){
        system("cls");
        cout<<"Ocurrio un error, vuelva a intentarlo."<<endl;
        Registro(Usuario, Contraseña);
    }else{
        while(getline(CuentasL, linea)){ //Mientras haya lineas para leer, sigue.
            stringstream ss(linea);
            string valor;
            contador=0;

            while(getline(ss, valor, ',')){ //En cada linea, lee los valores separados por la , y los asigna a las variables
                if(contador==0){
                    us=valor;
                    contador++;
                }
            }

            if(Usuario == us){
                Existe=true;
                break;
            }

        }
    }
    CuentasL.close();
}


void CargarLista(string nombrearchivo, ofstream archivo[], Alumno alumnos[]){
    int i=0;
    cout<<"Ingrese el nombre del archivo."<<endl;
    cin>>nombrearchivo;
    archivo[i].open(nombrearchivo,ios::out); //abrir el archivo y si no existe crearlo.

        if(archivo->fail()){
            cout<<"No se pudo abrir el archivo."<<endl;
            exit(1);
        }else{
            
            archivo[i]<<"Nombre,Edad,Ciudad"<<endl;
            cout<<"Ingrese el nombre del alumno"<<endl;
            cin>>alumnos[i].Nombre;
            cout<<"Ingrese la edad del alumno"<<endl;
            cin>>alumnos[i].Edad;
            cout<<"Ingrese la ciudad del alumno"<<endl;
            cin>>alumnos[i].Ciudad;

            //Agregar los datos al archivo
            archivo[i]<<alumnos[i].Nombre<<","<<alumnos[i].Edad<<","<<alumnos[i].Ciudad<<endl;

        }


        archivo->close();
}


void Lectura(){
    ifstream archivo;
    string Nombre, Nombre1, Ciudad, Edad,linea;

    cout<<"Ingrese el nombre del archivo que desea abrir."<<endl;
    cin>>Nombre;

    archivo.open(Nombre,ios::in); //Abre el archivo en modo lectura

    while(!archivo.eof()){ //Mientras no sea el final del archivo
        getline(archivo, linea);
        getline(archivo, Nombre1,',');
        getline(archivo, Edad, ',');
        getline(archivo, Ciudad, ',');

        cout<<"Nombre: "<<" "<<Nombre1<<endl;
        cout<<"Edad: "<<" "<<Edad<<endl;
        cout<<"Ciudad: "<<" "<<Ciudad<<endl;

    }

    archivo.close();
}