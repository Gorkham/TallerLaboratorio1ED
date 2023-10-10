#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <algorithm>
#include "User.h"
#include "Software.h"
#include "Game.h"
#include "Ofimatica.h"
#include "Production.h"
#include "Browser.h"
#include "Security.h"
#include "Social.h"

using namespace std;

//Funcion para volver todas las letras de un string minusculas
string lower(string word) {
    for (int i = 0; i < word.length(); i++) word[i] = tolower(word[i]);
    return word;
}

//Funcion que lee el archivo de usuarios y guarda los usuarios en una stack/pila
stack<User*> readUserFile(){
    
    ifstream archivo("usuarios.txt");

    string linea;

    stack<User*> userList;

    while (getline(archivo, linea)) {

        istringstream ss(linea);

        string tipo,name,password,ageString;
        int age;

        if (getline(ss, tipo, ';') && 
            getline(ss, name, ';') &&
            getline(ss, password, ';') &&
            getline(ss, ageString, ';')) {
            
                        // Intenta convertir la cadena de edad_str a un entero
            try {
                age = stoi(ageString); // Convierte la cadena a un entero
            } catch (exception& e) {
                cerr << "Error al convertir la edad a un número: " << e.what() << std::endl;
                age = 0; // Valor predeterminado en caso de error
            }

            if(tipo == "admin"){
                string mail;
                getline(ss, mail, ';');
                userList.push(new AdminUser(name, password, age, mail));
                cout<<"admin--------" <<endl;
            }else if(tipo == "normal"){
                string mail;
                getline(ss, mail, ';');
                userList.push(new AdultUser(name, password, age, mail));
                cout<<"adulto--------" <<endl;
            }else{
                userList.push(new Child(name, password, age));
                cout<<"nino--------" <<endl;
            }
        }


        // Procesa cada línea del archivo
        cout << linea << "HOLAAAAAAAAA" << endl;
         
    }
    archivo.close(); // Cierra el archivo cuando hayas terminado de usarlo

    return userList;
}  

stack<Software*> readSoftwareFile(stack<User*> userList){
        
    ifstream archivo("softwares.txt");

    string linea;
        
    stack<Software*> library;

     while (getline(archivo, linea)) {

        istringstream ss(linea);

        string type,name,developer,pegiString,users,priceString;
        int pegi;
        double price;
        stack<User*> userListSoftware;

        if (getline(ss, type, ',') && 
            getline(ss, name, ',') &&
            getline(ss, developer, ',') &&
            getline(ss, pegiString, ';')&&
            getline(ss, users,';')&&
            getline(ss,priceString,',')) {
            
                        // Intenta convertir la cadena de edad_str a un entero
            try {
                pegi = stoi(pegiString); // Convierte la cadena a un entero
            } catch (exception& e) {
                cerr << "Error al convertir el pegi a un número: " << e.what() << std::endl;
                pegi = 0; // Valor predeterminado en caso de error
            }
            
            try {
                price = stod(priceString); // Convierte la cadena a un entero
            } catch (exception& e) {
                cerr << "Error al convertir el precio a un número: " << e.what() << std::endl;
                price = 0; // Valor predeterminado en caso de error
            }
            
            // Separar los usuarios en elementos individuales utilizando la coma como delimitador
            istringstream userStream(users);
            string userElement;
            
            cout<<users<<"------"<<endl;
            cout<<pegiString<<endl;
            // Utilizando el nombre del usuario, se busca en la pila de usuarios y se agrega a la pila de usuarios del software
            while (getline(userStream, userElement, ',')) {
                cout<<userElement<<"------"<<endl;
                stack<User*> u = userList;
                while (!u.empty()) {
                User* userStack = u.top();
                    if(userStack){
                        cout<<lower(userStack->getName())<<endl;
                        if(lower(userStack->getName())==lower(userElement)){
                            cout<<"probando-----"<<endl;
                            userListSoftware.push(userStack);
                        }
                    u.pop();
                    }
        
                }
            }

            if(type == "juego"){
                string gender;
                getline(ss, gender, ';');
                library.push(new Game(name,developer,pegi,price,userListSoftware,gender));
                cout<<"juego--------" <<endl;
            }
        }

        return library;
        // Procesa cada línea del archivo
        cout << linea << "HOLAAAAAAAAA" << endl;
         
    }
}



//Funcion que comprueba si el nombre de usuario es valido
bool checkUserName(string name,stack<User*> userList){

    while (!userList.empty()) {
        User* userStack = userList.top();
        if(userStack){
            if(lower(userStack->getName()) == lower(name)){
                return true;     
            }
        }
            userList.pop();
    }
        
}

//Funcion que comprueba si la contraseña es la correcta
bool checkUserPassword(string password,string name,stack<User*> userList){

    while (!userList.empty()) {
        User* userStack = userList.top();
        if(userStack){
            if(lower(userStack->getName()) == lower(name)){
                if(userStack->getPassword()==password){
                    return true;
                }
            }
        }
            userList.pop();
    }
        
}

void login(stack<User*> userList){

    string username,password;

    cout<<"Bienvenido, ingrese su nombre de usuario:"<< endl;

    cin>> username;

    while (!checkUserName(username,userList))
    {
        cout << "Usuario no valido, ingrese un nombre de usuario valido por favor: "<<endl;
        cin>>username;
    };

    cout<< "Ingrese su contraseña:"<< endl;

    cin>>password;

    while (!checkUserPassword(password,username,userList))
    {
        cout<< "Contraseña incorrecta, ingrese su contraseña nuevamente:";
        cin>>password;
    };
    
    cout<<"Bienvenido "<<username<< " su contrasena es :"<<password<<endl;

}

int main() {
    
    stack<User*> userList = readUserFile();

    stack<Software*> userSoftware = readSoftwareFile(userList);

    string option;

    cout << "Software en el sistema son:" << endl;
    while (!userSoftware.empty()) {
    Software* softwareStack = userSoftware.top();
    cout<<"hola"<<endl;
    if (softwareStack) {
        
        cout<<"aaaaaaaa"<<endl;

        stack<User*> userLis = softwareStack->getUserList(); // Hacer una copia temporal de la pila

        cout << "Usuarios del programa " << softwareStack->getName() << ":" << endl;

        if(userLis.empty()){
            cout<<"Esta vacio"<<endl;
        }
        while (!userLis.empty()) {

            cout<<"usuario"<<endl;
            User* userStack = userLis.top();
            cout << userStack->getName() << "234" << endl;
            userLis.pop();
        }

        cout << "Nombre del programa: " << softwareStack->getName() << endl;
       
    }
     userSoftware.pop();
}


    cout<<"---Bienvenido, que accion desea realizar?---"<<endl;

    cout<<"1)Iniciar sesion"<<endl;

    cout<<"2)Terminar el programa"<<endl;

    cin>>option;

    while (option !="2")
    {
        if(option=="1"){
            
            login(userList);

        }else{
            cout<<"---Opcion no valida, ingrese una opcion valida---" <<endl;
            
            cout<<"1)Iniciar sesion"<<endl;

            cout<<"2)Terminar el programa"<<endl;

            cin>>option;
        }
    }
    
    



    User u1("Pepito", "pepito123", 17);

    cout << "Hello World" << endl;

    cout << u1.getName() << endl;

    

    return 0;
}

