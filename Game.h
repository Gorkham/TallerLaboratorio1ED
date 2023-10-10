#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <stack>


using namespace std;

class Game: public Software{

    private:
    string genre;

    public:

    Game(string n, string d, int pe, double pr,stack<User*> user,string g)
        : Software(n, d, pe,pr,user) {
        this->genre = g;
    };

    string getGenre(){
        return genre;
    };

    void setGnere(string g){
        this->genre = g;
    }
};