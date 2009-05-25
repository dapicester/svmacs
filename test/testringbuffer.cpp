#include <jackringbuffer.hpp>
using namespace JackCpp;

#include <iostream>
using std::cout;
using std::endl;

int main(){
	int t[] = {1,2,3,4,5,6,7,8};
	int r;
	RingBuffer<int> f(20);
	cout << "the length of the ring buffer is: " << f.length() << endl;
	cout << "the free space to write is: " << f.getWriteSpace() << endl;
	
	// write
	f.write(t,8);
	
	//read
	int i = 1;
	while(f.getReadSpace() != 0){
		f.read(r);
		cout << r << endl;
		i++;
	}
}
