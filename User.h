#include <stdio.h>
#include <string.h> 
#include <iostream>

using namespace std;

class User{
    
    private:
    string name,password;
    int age;
    
    public:
    
    User(string n,string p,int a){
        
        this->name = n;
        this->password = p;
        this->age = a;
            
    };
    
    string getName()
    {
        return name;    
    };
    
    string getPassword()
    {
        return password;
    };
    
    int getAge()
    {
        return age;
    };
    
};

class Child: public User{
    
    public:
    Child(string n, string p, int a)
        : User(n, p, a) {
    };
};

class AdultUser: public User{

    private:
    string mail;

    public:

    AdultUser(string n, string p, int a, string m)
        : User(n, p, a) {
        this->mail = m;
    };

    string getMail(){

        return mail;
    };

};

class AdminUser: public AdultUser{

    private:
    bool accesLog;

    public:

    AdminUser(string n,string p,int a,string m)
        : AdultUser(n, p, a,m){
        this -> accesLog = true;

    };

    bool getAccesLog(){
        return accesLog;
    };

};
