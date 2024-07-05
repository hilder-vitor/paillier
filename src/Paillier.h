
#include<gmpxx.h>
#include<vector>
#include <utility> // pair

#include"Ciphertext.h"

#ifndef __PAILLIER_192847381293484738
#define __PAILLIER_192847381293484738

namespace paillier{

class Paillier {

	private:
	gmp_randclass rand_gen;
	mpz_class p, q, l, mu, p_square, q_square, inv_p_square, inv_q_square;
    mpz_class g; // generator of group. Used for encryption. Set to 1 + n mod n^2

  	std::pair<mpz_class, mpz_class> g_decomp; // value g used in encryption and decryption represented in Z_p^2 x Z_q^2

	void generate_primes(int number_of_bits);

	void init_g_and_mu();
	void init_g_and_mu_fast();
		
	/* Chinese Remainder Theorem: x is an element of Z_n^2 and n = p * q */
	std::pair<mpz_class, mpz_class> crt(mpz_class x);

	/* Inverse CRT -- input: a in Z_p^2 and b in Z_q^2. Output: x in Z_n^2 */
	mpz_class inv_crt(mpz_class a, mpz_class b);
	
	
	public:

	int number_of_bits_of_n;
    mpz_class n, n_square;

	Paillier(int number_of_bits_of_n);

	Ciphertext enc(mpz_class plaintext);
	
    /* encrypt plaintext with the secret key instead of the public key,
     * that is, explointing secret factorization of n into primes p and q */
    Ciphertext enc_sk(mpz_class plaintext);
	
	mpz_class dec(Ciphertext ciphertext);

	Ciphertext add(Ciphertext c1, Ciphertext c2);

	Ciphertext mul(Ciphertext c, mpz_class plaintext);
	

	// --- Vector functions
	std::vector<Ciphertext> enc(std::vector<mpz_class> plaintext);
	
	std::vector<mpz_class> dec(std::vector<Ciphertext> ciphertext);

	std::vector<Ciphertext> add(std::vector<Ciphertext> ciphertext1, std::vector<Ciphertext> ciphertext2);

	std::vector<Ciphertext> mul(std::vector<Ciphertext> ciphertext, std::vector<mpz_class> plaintext);


};

};
#endif
