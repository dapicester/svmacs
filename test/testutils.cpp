#include "utils.h"
#include "convert.h"
using namespace utils;
using namespace cli;

#include <itpp/itbase.h>
using namespace itpp;

#include <iostream>
using namespace std;

void testFlipud(const vec& a) {
    vec b = flipud(a);
    cout << "flipud(a): " << b << endl;
    
    vec exp = "4 0 2 -1 0";
    cout << "expected : " << exp << endl;
    
    if (exp != b) {
        cout << "*flipud*" << endl;
        exit(1);
    }
}

void testFind(const vec& a) {
    ivec c = find(a);
    cout << "find(a)  : " << c << endl;
    
    ivec iexp = "1 2 4";
    cout << "expected : " << iexp << endl;
    
    if (iexp != c) {
        cout << "*find*" << endl;
        exit(1);
    }
}

void testDiff(const vec& a) {
    vec b = diff(a);
    cout << "diff(a)  : " << b << endl;
    
    vec exp = "-1 3 -2 4";
    cout << "expected : " << exp << endl;
    if (exp != b) {
        cout << "*diff*" << endl;
        exit(1);
    }
}

void testMaxima(const vec& a) {
    ivec c = maxima(a);
    cout << "maxima(a): " << c << endl;
    
    ivec iexp = "0 2 4";
    cout << "expected : " << iexp << endl;
    if (iexp != c) {
        cout << "*maxima*" << endl;
        exit(1);
    }
}

void testLinvec(int start, int stop) {
    vec v = linvec(start, stop);
    cout << "linvec: " << v << endl;
}

void testStringify(string start, string stop) {
    vec v = start + ":" + stop;
    cout << "string: " << v << endl;
}

int main(int argc, char** argv) {
    vec a = "0 -1 2 0 4";
    cout << "a        : " << vec2str(a) << endl;
    /*
    testFlipud(a);
    testFind(a);
    testDiff(a);
    testMaxima(a);
    */
    testLinvec(0, 10);
    testLinvec(1, 10);
    testStringify("0", "10");
    testStringify("1", "10");
}
