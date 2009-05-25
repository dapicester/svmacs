#include "utils.h"
using namespace utils;

#include <itpp/itbase.h>
using namespace itpp;

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    vec a = "0 -1 2 -3 4";
    vec b = flipud(a);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    /*
    cout << "a.*b: " << elem_mult(a,b) << endl;

    vec c(a);
    cout << "c: " << c << endl;
    
    c.ins(c.length(),b);
    cout << "c: " << c << endl;
    
    vec d = c.get(1,4);
    cout << "d: " << d << endl;
    cout << "size: " << d.size() << endl;
    */
    
    //vec s = sign(a);
    vec s = a-b;
    cout << "s: " << s << endl;
}
