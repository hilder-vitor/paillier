#include"Paillier.h"
#include<iostream>

using namespace std;

int main(){
	Paillier p(2048);

	mpz_class m1 = 11;
	mpz_class m2 = 128;

	mpz_class c1 = p.enc(m1);
	mpz_class c2 = p.enc(m2);

	if (p.dec(c1) == m1)
		cout << "ENC(" << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << ") .....  OK" << endl;

	if (p.dec(c2) == m2)
		cout << "ENC(" << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << ") .....  OK" << endl;

	if (p.dec(p.add(c1, c2)) == m1+m2)
		cout << "ENC(" << m1 << " + " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << " + " << m2 << ") .....  OK" << endl;

	if (p.dec(p.add(c2, c1)) == m2+m1)
		cout << "ENC(" << m2 << " + " << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " + " << m1 << ") .....  OK" << endl;

	if (p.dec(p.mul(c1, m2)) == m1*m2)
		cout << "ENC(" << m1 << " * " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << " * " << m2 << ") .....  OK" << endl;

	if (p.dec(p.mul(c2, m1)) == m1*m2)
		cout << "ENC(" << m2 << " * " << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " * " << m1 << ") .....  OK" << endl;

	if (p.dec(p.mul(c2, m2)) == m2*m2)
		cout << "ENC(" << m2 << " * " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " * " << m2 << ") .....  ERROR" << endl;

	return 0;
}
