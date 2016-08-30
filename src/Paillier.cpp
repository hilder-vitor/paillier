
#include "Paillier.h"
#include<iostream>


mpz_class _lmc(mpz_class a, mpz_class b){
	return abs(a * b) / gcd(a, b);
}


mpz_class minus_one_over_n(mpz_class u, mpz_class n){
	return (u - 1) / n;
}

void Paillier::generate_primes(int number_of_bits) {
	bool valid = false;
	mpz_t prime;
	mpz_class lower_bound;

	mpz_init(prime);
	lower_bound = rand_gen.get_z_bits(number_of_bits);

	mpz_nextprime (prime, lower_bound.get_mpz_t());
	p = mpz_class (prime);

	lower_bound = p + 1; // new prime q will be greater than p

	while(! valid){
		mpz_nextprime (prime, lower_bound.get_mpz_t());
		q = mpz_class (prime);
		if (gcd (p*q, (p-1)*(q-1)) == mpz_class(1))
			valid = true;
		else
			lower_bound = q + 1;
	}
	mpz_clear(prime);

}

void Paillier::init_g_and_mu(){
	bool found_inverse  = false;
	mpz_class power_of_g;
	mpz_t tmp_mu;
	mpz_init(tmp_mu);

	while (! found_inverse){
		g = 2 + rand_gen.get_z_range(n_square - 2); // random g in [2, n^2 - 1]
		mpz_class power_of_g;
		mpz_powm (power_of_g.get_mpz_t(), g.get_mpz_t(), l.get_mpz_t(), n_square.get_mpz_t());
		found_inverse = mpz_invert(tmp_mu, minus_one_over_n(power_of_g, n).get_mpz_t(), n.get_mpz_t());
		mu = mpz_class(tmp_mu);
	}

	mu = mpz_class(tmp_mu);
	mpz_clear(tmp_mu);
}

Paillier::Paillier(int _number_of_bits_of_n) : rand_gen(gmp_randinit_default) {

	rand_gen.seed(123); // XXX: Just testing

	number_of_bits_of_n = _number_of_bits_of_n;
	int number_of_bits_of_primes = number_of_bits_of_n / 2; 

	generate_primes(number_of_bits_of_primes);

	n = p*q;
	n_square = n*n;
	l = _lmc(p-1, q-1);

	init_g_and_mu();
}

mpz_class Paillier::enc(mpz_class plaintext){
	mpz_class r = 1 + rand_gen.get_z_range(n-1); // random r in [1, n - 1]
	mpz_class power_of_g;

	mpz_powm (r.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t(), n_square.get_mpz_t());
	mpz_powm (power_of_g.get_mpz_t(), g.get_mpz_t(), plaintext.get_mpz_t(), n_square.get_mpz_t());
	return power_of_g * r;
}
	
mpz_class Paillier::dec(mpz_class ciphertext){
	mpz_class plain;
	mpz_powm (plain.get_mpz_t(), ciphertext.get_mpz_t(), l.get_mpz_t(), n_square.get_mpz_t());
	return (minus_one_over_n(plain, n) * mu) % n;
}

mpz_class Paillier::add(mpz_class ciphertext1, mpz_class ciphertext2){
	return (ciphertext1 * ciphertext2) % n_square;
}

mpz_class Paillier::mul(mpz_class ciphertext, mpz_class plaintext){
	mpz_class product;
	mpz_powm (product.get_mpz_t(), ciphertext.get_mpz_t(), plaintext.get_mpz_t(), n_square.get_mpz_t());
	return product;
}

