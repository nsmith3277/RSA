// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h> 


// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

using std::cout;
using std::endl;

bool Fermat(BigUnsigned);
void pickPrime(BigUnsigned*);

int main(int argc, char **argv) {
	try {
		BigUnsigned p = BigUnsigned(1);
		BigUnsigned q = BigUnsigned(1);
		BigUnsigned n = BigUnsigned(1);
		BigUnsigned e = BigUnsigned(3);
		BigUnsigned d = BigUnsigned(1);
		std::ofstream file;
		
		/*Selecting 2 very large prime numbers p and q*/
		cout << "selecting p...\n";
		pickPrime(&p);
		cout << "P found!\n" << p << endl;
		cout << "\nselecting q...\n";
		pickPrime(&q);
		cout << "q found!\n" << q << endl;
		/* write p and q to a txt file */
		file.open("p_q.txt");
		file << p << endl << q;
		file.close();
		/* Compute phi(n) */
		n = (p-1) * (q-1);
		/* Compute e such that e is relativley prime to phi(n) */
		while(gcd(n, e) != 1)
			e++;
		/* Compute d */
		d = modinv(e, n);
		/* compute n*/
		n = p * q;
		/* write our two keys (d, n) and (e, n) to a file */
		file.open("e_n.txt");
		file << e << endl << n;
		file.close();
		file.open("d_n.txt");
		file << d << endl << n; 
		file.close();
		
	} catch(char const* err) {
		cout << "The library threw an exception:\n"
			<< err << endl;
	}
	return 0;
}

bool fermat(BigUnsigned p) { 
	BigInteger a = BigInteger(2);
	if (modexp(a, p - 1, p) != 1) {
		return false;
	} 
	a = 3;
	if(modexp(a, p - 1, p) != 1) {
		return false;
	}
	a = 7; 
	if(modexp(a, p - 1, p) != 1) {
		return false;
	}
	return true;
}

void pickPrime(BigUnsigned *p) {
	bool isPrime = false;
	do {
		*p = 1;  //ensures p is non-zero to prevent infinite loop
		for (int i = 0;i<200;i++)
			*p = *p * 10 + rand(); //pick p
		isPrime = fermat(*p);
	} while (!isPrime);   //pick a different p if it isn't prime
}