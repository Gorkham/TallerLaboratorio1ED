#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Ofimatica: public Software{

    private:
    int numbersFile;

    public:
    
    Ofimatica(string n, string d, int pe, double pr,stack<User*> user,int nu)
        : Software(n, d, pe,pr,user) {
        this->numbersFile = nu;
    };

    int getNumbersFile(){
        return numbersFile;
    };
};