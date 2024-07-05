
#include<gmpxx.h>
#include<vector>

#ifndef __CIPHERTEXT_PAILLIER_192847381293484738
#define __CIPHERTEXT_PAILLIER_192847381293484738

namespace paillier{

/*   A Paillier ciphertext is an element of Z_n^2, where n = pq (product of primes p and q).
 */
class Ciphertext {

	public:
    mpz_class c; // value in mod n^2
           
    // the two variables below represent c mod p and mod q. They are only used
    // by functions that have access to the secret key, since these primes are secret
	mpz_class c_p;
	mpz_class c_q;

};

};
#endif
