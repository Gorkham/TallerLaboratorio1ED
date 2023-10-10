#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>

using namespace std;

class Social: public Software{

    private:
    stack<User*> userListSocial; 

    public:
    
    Social(string n, string d, int pe, double pr,stack<User*> user,stack<User*> u)
        : Software(n, d, pe,pr,user) {
        this->userListSocial = u;
    };

    stack<User*> getUserListSocial(){
        return userListSocial;
    };
    
};