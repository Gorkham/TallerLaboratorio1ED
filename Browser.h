#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Browser: public Software {

    private:
    stack<string> history;

    public:

    Browser(string n, string d, int pe, double pr,stack<User*> user,stack<string> h)
        : Software(n, d, pe,pr,user) {
        this->history = h;
    };

    stack<string> getHistory(){
        return history;
    };
};