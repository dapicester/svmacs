/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <itpp/itbase.h>
using namespace itpp;

#include <iostream>
using namespace std;

#define PRINT(X) cout << #X << ": " << X << endl;

int main() {
	mat A = "1 2 3; 4 5 6; 7 8 9"; PRINT(A);
	mat B = "1; 2; 3"; PRINT(B);
	
	mat C = A*B; PRINT(C);
        mat D = B.hermitian_transpose() * A; PRINT(D);
}