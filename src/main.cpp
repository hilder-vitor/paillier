#include"Paillier.h"
#include<iostream>

using namespace std;

template <typename ELEMENT>
void operator+=(vector<ELEMENT>& u, const vector<ELEMENT>& v){
	if (v.size() != u.size())
		throw std::invalid_argument("It is impossible to add vectors of different sizes.");
	unsigned int n = u.size();
	for (unsigned int i = 0; i < n; i++){
		u[i] = u[i] + v[i];
	}
}

template <typename ELEMENT>
vector<ELEMENT> operator+(const vector<ELEMENT>& u, const vector<ELEMENT>& v){
	vector<ELEMENT> vec(u);
	vec += v;
	return vec;
}

vector<mpz_class> mult_component_wise(vector<mpz_class> u, vector<mpz_class> v){
	vector<mpz_class> w(u.size());
	for (unsigned int i = 0; i < u.size(); i++){
		w[i] = u[i]*v[i];
	}
	return w;
}

int main(){
	Paillier p(2048);

	mpz_class m1 = 111212333;
	mpz_class m2 = 1123;

	cout << "ENC m1 = " << m1 << endl;
	mpz_class c1 = p.enc(m1);
	mpz_class c2 = p.enc(m2);

	for (unsigned int i = 0; i < 1000; i++){
		p.enc(m1);
		p.enc(m2);
	}

	return 0;



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

	vector<mpz_class> vec1(5, 2); // vector with five number two
	vector<mpz_class> vec2(5, 3); // vector with five number two

	vector<mpz_class> enc_vec1 = p.enc(vec1);
	vector<mpz_class> enc_vec2 = p.enc(vec2);

	
	vector<mpz_class> sum_vec = p.add(enc_vec1, enc_vec2);

	if (p.dec(sum_vec) == vec1 + vec2)
		cout << "ENC( vector1 + vector2 ) .....  OK" << endl;
	else
		cout << "ENC( vector1 + vector2 ) .....  ERROR" << endl;


	vector<mpz_class> prod_vec = p.mul(enc_vec1, vec2);

	if (p.dec(prod_vec) == mult_component_wise(vec1, vec2))
		cout << "ENC( vector1 *. vector2 ) .....  OK" << endl;
	else
		cout << "ENC( vector1 *. vector2 ) .....  ERROR" << endl;




	return 0;
}


