
#include "gmpxx.h"

#ifndef __PAILLIER_192847381293484738
#define __PAILLIER_192847381293484738

class Paillier {

	private:
		fmpzxx p, q, lmc, g, mu;
	
	Paillier(int number_of_bits_of_n);


	fmpzxx enc(fmpzxx plaintext);
	
	fmpzxx dec(fmpzxx ciphertext);

	fmpzxx add(fmpzxx ciphertext1, fmpzxx ciphertext2);

	fmpzxx mul(fmpzxx ciphertext, fmpzxx plaintext);
}

#endif
