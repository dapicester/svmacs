#include "utils.h"
using namespace utils;

#include <itpp/itbase.h>
using namespace itpp;

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    vec a = "0 -1 2 0 4";
    cout << "a        : " << a << endl;
    //---------------------------------
    vec b = flipud(a);
    cout << "flipud(a): " << b << endl;
    
    vec exp = "4 0 2 -1 0";
    cout << "expected : " << exp << endl;
    
    if (exp != b) {
        cout << "*flipud*" << endl;
        exit(1);
    }
    //--------------------------------
    ivec c = find(a);
    cout << "find(a)  : " << c << endl;
    
    ivec iexp = "1 2 4";
    cout << "expected : " << iexp << endl;
    
    if (iexp != c) {
        cout << "*find*" << endl;
        exit(1);
    }
    //--------------------------------
    b = diff(a);
    cout << "diff(a)  : " << b << endl;
    
    exp = "-1 3 -2 4";
    cout << "expected : " << exp << endl;
    if (exp != b) {
        cout << "*diff*" << endl;
        exit(1);
    }
    //--------------------------------
    c = maxima(a);
    cout << "maxima(a): " << c << endl;
    
    iexp = "0 2 4";
    cout << "expected : " << iexp << endl;
    if (iexp != c) {
        cout << "*maxima*" << endl;
        exit(1);
    }
}
