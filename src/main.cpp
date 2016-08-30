#include"Paillier.h"
#include<iostream>

using namespace std;

int main(){
	Paillier p(2048);

	int m = 10;
	if (p.dec(p.enc(mpz_class(m))) == m)
		cout << "ENC(" << m << ") .....  OK" << endl;

	m = 0;
	if (p.dec(p.enc(mpz_class(m))) == m)
		cout << "ENC(" << m << ") .....  OK" << endl;

	m = 1312123;
	if (p.dec(p.enc(mpz_class(m))) == m)
		cout << "ENC(" << m << ") .....  OK" << endl;

	return 0;
}
