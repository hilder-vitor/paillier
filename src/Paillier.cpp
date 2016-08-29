
#include "Paillier.h"

void Paillier::generate_primes(int number_of_bits){
	mpz_t prime;
	mpz_t lower_bound;
	mpz_init (prime);
	mpz_init (lower_bound);
	
	mpz_ui_pow_ui (lower_bound, 2, number_of_bits);

	mpz_nextprime (prime, lower_bound);

	p = mpz_class (prime);

	mpz_add_ui(prime, 1);

	mpz_nextprime (prime, lower_bound);

}

Paillier::Paillier(int number_of_bits_of_n){
	int number_of_bits_of_primes = number_of_bits_of_n / 2; 


}


	fmpzxx enc(fmpzxx plaintext);
	
	fmpzxx dec(fmpzxx ciphertext);

	fmpzxx add(fmpzxx ciphertext1, fmpzxx ciphertext2);

	fmpzxx mul(fmpzxx ciphertext, fmpzxx plaintext);
}

#endif
