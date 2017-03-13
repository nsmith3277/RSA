/*RSA Encryption algorithm
 * Author: Nicholas Smith
 * Using the Big Integer library, this program will generate 
 * the keys (e, n) and (d, n) needed to encrypt and decrypt 
 * messages from a text file. Using large prime numbers p and 
 * q found using the fermat test, these prime numbers generate 
 * the private key d and public key e in the range of n. 
 */

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

/* Fermat is an algorithm used to test if a number is prime. 
 * the formula states that we can pick a random a that makes 
 * a^(p-1) % n = 1. If this is true, then p is most likely prime. 
 * If it fails, we can say p definitely is not prime. Since a 
 * can possibly be a fermat liar, we test 3 times.
 */
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
/* function call to randomly pick a very large number by calling 
 * rand() * 10 two hundred times. We then call the fermat test function
 * to test primality. If it fails, we must pick another number.
 * If we are lucky, the function finds a prime within a few seconds. 
 * On average it takes roughly 30-60 seconds to find a prime number.
 */
void pickPrime(BigUnsigned *p) {
	bool isPrime = false;
	do {
		*p = 1;  //ensures p is non-zero to prevent infinite loop
		for (int i = 0;i<200;i++)
			*p = *p * 10 + rand(); //pick p
		isPrime = fermat(*p);
	} while (!isPrime);   //pick a different p if it isn't prime
}
