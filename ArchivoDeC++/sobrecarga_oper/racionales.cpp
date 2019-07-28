#include "racionales.h"
#include <iostream>

using namespace std;

int main(){
	Racional r1(2,2);
	Racional r2(3,3);
	Racional r3(0,0);

	r3=operator+(r1,r2);
	
	cout << "numerador: " << r3.Numerador() << " Denominador :"<< r3.Denominador() <<endl;
}
