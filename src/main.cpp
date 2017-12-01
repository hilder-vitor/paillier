#include"Paillier.h"
#include<iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	paillier::Paillier p(1024);

	mpz_class m1 = 501;
	mpz_class m2 = 112312313;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	paillier::Ciphertext c1 = p.enc(m1);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Encryption time for m1: " << duration << endl;
	
	t1 = high_resolution_clock::now();
	paillier::Ciphertext c2 = p.enc(m2);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Encryption time for m1: " << duration << endl;

	t1 = high_resolution_clock::now();
	paillier::Ciphertext c_add_1 = p.add(c1,c2);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Running time homomorphic m1 + m2: " << duration << endl;

	t1 = high_resolution_clock::now();
	paillier::Ciphertext c_add_2 = p.add(c2,c1);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Running time homomorphic m2 + m1: " << duration << endl;

	t1 = high_resolution_clock::now();
	paillier::Ciphertext c_prod_1 = p.mul(c1, m2);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Running time homomorphic c1*m2: " << duration << endl;

	t1 = high_resolution_clock::now();
	paillier::Ciphertext c_prod_2 = p.mul(c2, m1);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
	cout << "Running time homomorphic c21*m1: " << duration << endl;






	if (p.dec(c1) == m1)
		cout << "ENC(" << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << ") .....  ERROR" << endl;

	if (p.dec(c2) == m2)
		cout << "ENC(" << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << ") .....  ERROR" << endl;

	if (p.dec(c_add_1) == m1+m2)
		cout << "ENC(" << m1 << " + " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << " + " << m2 << ") .....  ERROR" << endl;

	if (p.dec(c_add_2) == m2+m1)
		cout << "ENC(" << m2 << " + " << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " + " << m1 << ") .....  ERROR" << endl;

	if (p.dec(c_prod_1) == m1*m2)
		cout << "ENC(" << m1 << " * " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 << " * " << m2 << ") .....  ERROR" << endl;
	if (p.dec(c_prod_2) == m1*m2)
		cout << "ENC(" << m2 << " * " << m1 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " * " << m1 << ") .....  ERROR" << endl;

	mpz_class val = p.dec(p.mul(c2, m2));
	if (val == m2*m2)
		cout << "ENC(" << m2 << " * " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m2 << " * " << m2 << ") .....  ERROR - " << val << endl;

	val = p.dec(p.add(c1, p.mul(c2, m2)));
	if (val == m1 + m2*m2)
		cout << "ENC(" << m1 <<" + " << m2 << " * " << m2 << ") .....  OK" << endl;
	else
		cout << "ENC(" << m1 <<" + " << m2 << " * " << m2 << ") .....  ERROR" << endl;


	vector<mpz_class> vec1(5, 2); // vector with five number two
	vector<mpz_class> vec2(5, 3); // vector with five number two

	vector<paillier::Ciphertext> enc_vec1 = p.enc(vec1);
	vector<paillier::Ciphertext> enc_vec2 = p.enc(vec2);

	
	vector<paillier::Ciphertext> sum_vec = p.add(enc_vec1, enc_vec2);

	if (p.dec(sum_vec) == vec1 + vec2)
		cout << "ENC( vector1 + vector2 ) .....  OK" << endl;
	else
		cout << "ENC( vector1 + vector2 ) .....  ERROR" << endl;


	vector<paillier::Ciphertext> prod_vec = p.mul(enc_vec1, vec2);

	if (p.dec(prod_vec) == mult_component_wise(vec1, vec2))
		cout << "ENC( vector1 *. vector2 ) .....  OK" << endl;
	else
		cout << "ENC( vector1 *. vector2 ) .....  ERROR" << endl;

	return 0;
}


