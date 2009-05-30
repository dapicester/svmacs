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
    
    cout << concat(a,b) << endl;
    
    vec c;
    c = concat(c,3.14);
    cout << c << endl;
    
    c = concat(c,a);
    cout << c << endl;
}
