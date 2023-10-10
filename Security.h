#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Security: public Software{

    private:
    string typeMalware;

    public:

    Security(string n, string d, int pe, double pr,stack<User*> user,string t)
        : Software(n, d, pe,pr,user) {
        this->typeMalware = t;
    };

    string getTypeMalware(){
        return typeMalware;
    };
};