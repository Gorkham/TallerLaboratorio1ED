#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Software
{
    private:
    string name,developer;
    int pegi;
    stack<User*> userList;
    double price;
    
    public:
    
    Software(string n,string d,int pe, double pr,stack<User*> user){
        
        this->name= n;
        this->developer=d;
        this->pegi= pe;
        this->price= pr;
        this->userList = user;
    };
    
    string getName()
    {
        return name;
    }
    
    string getDeveloper()
    {
        return developer;
    }
    
    int getPegi()
    {
        return pegi;
    }
    
    stack<User*> getUserList()
    {
        return userList;
    }
    
    double getPrice()
    {
        return price;
    }
};
