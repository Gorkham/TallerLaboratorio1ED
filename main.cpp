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
            
            // Se intenta convertir la edad a un int
            try {
                age = stoi(ageString); 
            } catch (exception& e) {
                cerr << "Error al convertir la edad a un número: " << e.what() << std::endl;
                age = 0; 
            }

            //Dependiendo del tipo de usuario se crea un usuario y se agrega a la lista de usuarios
            if(tipo == "admin"){
                string mail;
                getline(ss, mail, ';');
                userList.push(new AdminUser(name, password, age, mail));
            }else if(tipo == "normal"){
                string mail;
                getline(ss, mail, ';');
                userList.push(new AdultUser(name, password, age, mail));
            }else{
                userList.push(new Child(name, password, age));
            }
        }
         
    }
    archivo.close(); // Cierra el archivo 

    return userList;
}  

//Funcion que lee el archivo de softwares y los guarda en una stack/pila
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
            
            // Se intenta convertir la clasificacion de edad a un int
            try {
                pegi = stoi(pegiString);
            } catch (exception& e) {
                cerr << "Error al convertir el pegi a un número: " << e.what() << std::endl;
                pegi = 0; 
            }
            //Se intenta convertir el precio en un double
            try {
                price = stod(priceString); 
            } catch (exception& e) {
                cerr << "Error al convertir el precio a un número: " << e.what() << std::endl;
                price = 0; 
            }
            
            istringstream userStream(users);
            string userElement;
            
            // Utilizando el nombre del usuario, se busca en la pila de usuarios y se agrega a la pila de usuarios del software
            while (getline(userStream, userElement, ',')) {

                stack<User*> u = userList;
                while (!u.empty()) {
                User* userStack = u.top();
                    if(userStack){

                        if(lower(userStack->getName())==lower(userElement)){

                            userListSoftware.push(userStack);
                        }
                    u.pop();
                    }
        
                }
            }
             //Dependiendo del tipo de software se crea un software y se agrega a la lista de software
            if(type == "juego"){
                string gender;
                getline(ss, gender, ';');
                
                library.push(new Game(name,developer,pegi,price,userListSoftware,gender));
            }else if(type == "ofimatica"){
                string cantString;
                int cant;
                getline(ss, cantString, ';');
                //Se trata de convertir la cantidad de elementos a un int
                try {
                    cant = stoi(cantString); 
                } catch (exception& e) {
                    cerr << "Error al convertir el pegi a un número: " << e.what() << std::endl;
                    cant = 0; 
                }
                
                library.push(new Ofimatica(name,developer,pegi,price,userListSoftware,cant));
            }else if(type == "produccion"){
                string solution;
                getline(ss, solution, ';');
                
                library.push(new Production(name,developer,pegi,price,userListSoftware,solution));
            }else if(type == "navegador"){
                string webs;
                getline(ss, webs, ';');
                
                istringstream userStream(webs);
                string webElement;
                stack<string> websStack;

                while (getline(userStream, webElement, ',')) {
                    websStack.push(webElement);  
                }
                library.push(new Browser(name,developer,pegi,price,userListSoftware,websStack));
            }else if(type == "seguridad"){
                string malware;
                getline(ss, malware, ';');
                
                library.push(new Security(name,developer,pegi,price,userListSoftware,malware));
            }else if(type == "social"){

            }
        }

              
    }
    return library;  
}


//Funcion que comprueba si el nombre de usuario es valido o existe
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

//Funcion que comprueba si el nombre del software es valido o existe
bool checkSoftwareName(string name,stack<Software*> softwareList){
     while (!softwareList.empty()) {
        Software* softwareStack = softwareList.top();
        if(softwareStack){
            if(lower(softwareStack->getName()) == lower(name)){
                return true;     
            }
        }
            softwareList.pop();
    }
}

//Retorna el usuario que tenga el nombre ingresado
User* returnUser(string name,stack<User*> userList){
    while (!userList.empty()) {
        User* userStack = userList.top();
        if(userStack){
            if(lower(userStack->getName()) == lower(name)){
                return userStack;     
            }
        }
            userList.pop();
    }
}

//Retorna el software que tenga el nombre ingresado
Software* returnSoftware(string name,stack<Software*> softwareList){
     while (!softwareList.empty()) {
        Software* softwareStack = softwareList.top();
        if(softwareStack){
            if(lower(softwareStack->getName()) == lower(name)){
                return softwareStack;     
            }
        }
            softwareList.pop();
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

//Funcion que muestra todos los softwares disponibles
void showSoftwares(stack<Software*> userSoftware){
    cout << "Los Software en el sistema son:" << endl;
    while (!userSoftware.empty()) {
    Software* softwareStack = userSoftware.top();
    cout<<softwareStack->getName()<<endl;
        if (softwareStack) {

            stack<User*> userLis = softwareStack->getUserList(); // Hacer una copia temporal de la pila

            cout << "Usuarios del programa " << softwareStack->getName() << ":" << endl;

            while (!userLis.empty()) {

                User* userStack = userLis.top();
                cout << userStack->getName() << endl;
                userLis.pop();
            }
       
    }
     userSoftware.pop();
}
}


//Funcion de login del menu
void login(stack<User*> userList,stack<Software*> userSoftware){

    string username,password;

    cout<<"Bienvenido, ingrese su nombre de usuario:"<< endl;
    
    cin>> username;
    //Se comprueba que el nombre del usuario exista en la base de datos
    while (!checkUserName(username,userList))
    {
        cout << "Usuario no valido, ingrese un nombre de usuario valido por favor: "<<endl;
        cin>>username;
    };

    cout<< "Ingrese su contraseña:"<< endl;

    cin>>password;
    //Se comprueba que la clave del usuario exista en la base de datos y sea la que le corresponda
    while (!checkUserPassword(password,username,userList))
    {
        cout<< "Contraseña incorrecta, ingrese su contraseña nuevamente:";
        cin>>password;
    };
    
    string optionMenu1;

    cout<<"Bienvenido "<<username<<endl;

    cout<<"Que desea realizar?"<<endl;

    cout<<"1)Agregar un sofware."<<endl;

    cout<<"2)Eliminar un software."<<endl;

    cin>>optionMenu1;

    if(optionMenu1=="1"){

        string nameSoftware;

        showSoftwares(userSoftware);

        cout<<"Ingrese el nombre del software que desea agregar a su bibloteca"<<endl;

        cin>>nameSoftware;
        //Control de error para que se ingrese el nombre de un programa valido
        while (!checkSoftwareName(username,userSoftware))
        {
            cout << "Programa no valido, ingrese un programa valido por favor: "<<endl;
            cin>>nameSoftware;
        };

        returnUser(username,userList) ->getSoftwareList().push(nameSoftware);

    }else{
        cout<<"Working in progress..."<<endl;
    }

}

int main() {
    
    //Lista de todos los usuarios del txt usuarios
    stack<User*> userList = readUserFile();
    //Lista de todos los softwares del txt softwares
    stack<Software*> userSoftware = readSoftwareFile(userList);

    string option;

    cout<<"---Bienvenido, que accion desea realizar?---"<<endl;

    cout<<"1)Iniciar sesion"<<endl;

    cout<<"2)Terminar el programa"<<endl;

    cin>>option;

    while (option !="2")
    {
        if(option=="1"){
            
            
            login(userList,userSoftware);

            cout<<"---Que accion desea realizar?---"<<endl;

            cout<<"1)Iniciar sesion"<<endl;

            cout<<"2)Terminar el programa"<<endl;

            cin>>option;

        }else{
            cout<<"---Opcion no valida, ingrese una opcion valida---" <<endl;
            
            cout<<"1)Iniciar sesion"<<endl;

            cout<<"2)Terminar el programa"<<endl;

            cin>>option;
        }

        

    }
       

    return 0;
}

