#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Production: public Software{

    private:
    string typeOfSolution;

    public:
    
    Production(string n, string d, int pe, double pr,stack<User*> user,string t)
        : Software(n, d, pe,pr,user) {
        this->typeOfSolution = t;
    };

    string gettypeOfSolution(){
        return typeOfSolution;
    };
};