
#include "Paillier.h"
#include<iostream>

using namespace std;
using namespace paillier;

/***********  AUX FUNCTIONS  ****************************/
mpz_class _lmc(mpz_class a, mpz_class b){
	return abs(a * b) / gcd(a, b);
}


mpz_class minus_one_over_n(mpz_class u, mpz_class n){
	return (u - 1) / n;
}

/* Chinese Remainder Theorem: x is an element of Z_n^2 and n = p * q */
pair<mpz_class, mpz_class> Paillier::crt(mpz_class x){
	return pair<mpz_class, mpz_class>(x % p_square, x % q_square);
}

/* Inverse CRT -- input: a in Z_p^2 and b in Z_q^2. Output: x in Z_n^2 */
mpz_class Paillier::inv_crt(mpz_class a, mpz_class b){
	return (a * inv_q_square * q_square + b * inv_p_square * p_square) % n_square;
}
/***********  END AUX FUNCTIONS  *************************/


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
	mpz_class power_of_g, _g;

	while (! found_inverse){
		_g = 2 + rand_gen.get_z_range(n_square - 2); // random g in [2, n^2 - 1]
		mpz_powm (power_of_g.get_mpz_t(), _g.get_mpz_t(), l.get_mpz_t(), n_square.get_mpz_t());
		found_inverse = mpz_invert(mu.get_mpz_t(), minus_one_over_n(power_of_g, n).get_mpz_t(), n.get_mpz_t());
	}
	g = crt(_g);
}

Paillier::Paillier(int _number_of_bits_of_n) : rand_gen(gmp_randinit_default) {

	rand_gen.seed(12345); // XXX: Just testing

	number_of_bits_of_n = _number_of_bits_of_n;
	int number_of_bits_of_primes = number_of_bits_of_n / 2; 

	generate_primes(number_of_bits_of_primes);

	p_square = p*p;
	q_square = q*q;
	mpz_invert (inv_p_square.get_mpz_t(), p_square.get_mpz_t(), q_square.get_mpz_t());
	mpz_invert (inv_q_square.get_mpz_t(), q_square.get_mpz_t(), p_square.get_mpz_t());

	n = p*q;
	n_square = n*n;
	l = _lmc(p-1, q-1);

	init_g_and_mu();
}

Ciphertext Paillier::enc(mpz_class plaintext){

	pair<mpz_class, mpz_class> plain = crt(plaintext);

	Ciphertext c;
	pair<mpz_class, mpz_class> r = crt(mpz_class(1 + rand_gen.get_z_range(n-1))); // random r in [1, n - 1]
	mpz_class power_of_g;

	mpz_powm (r.first.get_mpz_t(), r.first.get_mpz_t(), n.get_mpz_t(), p_square.get_mpz_t());
	mpz_powm (power_of_g.get_mpz_t(), g.first.get_mpz_t(), plain.first.get_mpz_t(), p_square.get_mpz_t());
	c.a = (power_of_g * r.first) % p_square;

	mpz_powm (r.second.get_mpz_t(), r.second.get_mpz_t(), n.get_mpz_t(), q_square.get_mpz_t());
	mpz_powm (power_of_g.get_mpz_t(), g.second.get_mpz_t(), plain.second.get_mpz_t(), q_square.get_mpz_t());
	c.b = (power_of_g * r.second) % q_square;

	return c;
}
	
mpz_class Paillier::dec(Ciphertext ciphertext){
	mpz_class plain, a, b;
	mpz_powm (a.get_mpz_t(), ciphertext.a.get_mpz_t(), l.get_mpz_t(), p_square.get_mpz_t());
	mpz_powm (b.get_mpz_t(), ciphertext.b.get_mpz_t(), l.get_mpz_t(), q_square.get_mpz_t());

	plain = inv_crt(a, b);

	return (minus_one_over_n(plain, n) * mu) % n;
}

Ciphertext Paillier::add(Ciphertext c1, Ciphertext c2){
	Ciphertext c;
	c.a = (c1.a * c2.a) % p_square;
	c.b = (c1.b * c2.b) % q_square;
	return c;
}

Ciphertext Paillier::mul(Ciphertext ciphertext, mpz_class plaintext){
	Ciphertext c;
	mpz_powm (c.a.get_mpz_t(), ciphertext.a.get_mpz_t(), plaintext.get_mpz_t(), p_square.get_mpz_t());
	mpz_powm (c.b.get_mpz_t(), ciphertext.b.get_mpz_t(), plaintext.get_mpz_t(), q_square.get_mpz_t());
	return c;
}

// --- Vector functions
vector<Ciphertext> Paillier::enc(vector<mpz_class> plaintext){
	vector<Ciphertext> enc_v(plaintext.size());
	for (unsigned int i = 0; i < enc_v.size(); i++){
		enc_v[i] = enc(plaintext[i]);
	}
	return enc_v;
}
	
vector<mpz_class> Paillier::dec(vector<Ciphertext> ciphertext){
	vector<mpz_class> plain_v(ciphertext.size());
	for (unsigned int i = 0; i < plain_v.size(); i++){
		plain_v[i] = dec(ciphertext[i]);
	}
	return plain_v;
}

vector<Ciphertext> Paillier::add(std::vector<Ciphertext> ciphertext1, std::vector<Ciphertext> ciphertext2){
	vector<Ciphertext> sum_v(ciphertext1.size());
	for (unsigned int i = 0; i < ciphertext1.size(); i++){
		sum_v[i] = add(ciphertext1[i], ciphertext2[i]);
	}
	return sum_v;
}


vector<Ciphertext> Paillier::mul(std::vector<Ciphertext> ciphertext, std::vector<mpz_class> plaintext){
	vector<Ciphertext> prod_v(ciphertext.size());
	for (unsigned int i = 0; i < ciphertext.size(); i++){
		prod_v[i] = mul(ciphertext[i], plaintext[i]);
	}
	return prod_v;
}

