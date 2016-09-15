
#include<gmpxx.h>
#include<vector>

#ifndef __CIPHERTEXT_PAILLIER_192847381293484738
#define __CIPHERTEXT_PAILLIER_192847381293484738

namespace paillier{

/*   A Paillier ciphertext is an element of Z_n^2, where n = pq (product of primes p and q).
 *   To make operations more efficient, it is represented as an element of Z_p^2 x Z_q^2,
 * that is, a pair of elements (a, b) with a being an element of the integers mod p^2 and b
 * an element of the integers mod q^2.
 *   This is achieved by using the CRT (Chinese Remainder Theorem).
 */
class Ciphertext {

	public:
	mpz_class a, b;

};

};
#endif
