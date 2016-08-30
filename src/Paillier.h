
#include<gmpxx.h>

#ifndef __PAILLIER_192847381293484738
#define __PAILLIER_192847381293484738

class Paillier {

	private:
	gmp_randclass rand_gen;
	mpz_class p, q, l, g, mu, n, n_square;
	int number_of_bits_of_n;

	void generate_primes(int number_of_bits);

	void init_g_and_mu();
		
	
	public:
	Paillier(int number_of_bits_of_n);


	mpz_class enc(mpz_class plaintext);
	
	mpz_class dec(mpz_class ciphertext);

	mpz_class add(mpz_class ciphertext1, mpz_class ciphertext2);

	mpz_class mul(mpz_class ciphertext, mpz_class plaintext);
};

#endif
