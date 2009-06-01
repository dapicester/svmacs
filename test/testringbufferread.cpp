#include "ringbufferread.h"
using namespace jack;

#include <iostream>
using std::cout;
using std::endl;

int main(){
	double t[] = {1,2,3,4,5,6,7,8};    
	//int r;	
	
	int L = 8; // lunghezza array
	int N = 4; // lunghezza frame
	//int R = 2; // overlap
	
	RingBufferRead input(2*L+1); // deve essere abbastanza grande, diciamo 2L+1
	cout << "input length = " << input.length() << endl;
	cout << "input writeSpace = " << input.getWriteSpace() << endl;
	double zeros[] = {0,0,0};
	input.write(zeros,3); // pre-pad
	input.write(t,L);
	input.write(zeros,3); // post-pad
	
	RingBufferRead buf(2*N+1);   // non conta la grandezza di questo buffer perché leggo solo N
					// importante è che sia almeno N+1
	cout << "buf length = " << buf.length() << endl;
	cout << "buf writeSpace = " << buf.getWriteSpace() << endl;
	/*
	int curr[R];
	int frame[N];
	while(input.getReadSpace() != 0) {
		input.read(curr,R);          
		buf.write(curr,R);
		
		input.peek(curr,R);
		buf.write(curr,R);
		
		while(buf.getReadSpace() != 0) {
		buf.read(frame,N);
		cout << "[";
		for (int i=0; i<N; i++)
			cout << frame[i] << " ";
		cout << "]" << endl;
		}
}    */
}
