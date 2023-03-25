#include <iostream>
using namespace std;
#include <boost/bind.hpp>
#include <string>

class Hello {
public:
    void say(string name) {
        cout << name << "say : hello world! " << endl; 
    } 
};

int main() {
    Hello h;
    auto func = boost::bind(&Hello::say, &h, "zhang san");
    func();

    return 0;
}
