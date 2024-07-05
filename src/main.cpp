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
	paillier::Paillier p(3070);

    srand (time(NULL));

    double avg = 0.0;
    int NTESTS = 100;
    for(int i = 0; i <= NTESTS; i++){
    	mpz_class m1 = rand() % 10000;

    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    paillier::Ciphertext c1 = p.enc(m1);
    	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
        avg += duration;

    	if (p.dec(c1) != mpz_class(m1) % p.n){
	    	cout << "Enc   .....  ERROR" << endl;
            return 1;
        }

    }
    cout << "Encryption time with pk: " << avg/NTESTS << " milliseconds" << endl;

    avg = 0.0;
    for(int i = 0; i <= NTESTS; i++){
    	mpz_class m1 = rand() % 10000;

    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    paillier::Ciphertext c1 = p.enc_sk(m1);
    	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
        avg += duration;

    	if (p.dec(c1) != mpz_class(m1) % p.n){
	    	cout << "Enc   .....  ERROR" << endl;
            return 1;
        }

    }
    cout << "Encryption time with sk: " << avg/NTESTS << " milliseconds" << endl;



	avg = 0.0;
    for(int i = 0; i <= NTESTS; i++){
    	mpz_class m1 = rand() % 10000;
	    mpz_class m2 = rand() % 100000;

	    paillier::Ciphertext c1 = p.enc(m1);
	    paillier::Ciphertext c2 = p.enc(m2);

    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    paillier::Ciphertext c_add = p.add(c1,c2);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

	    auto duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
        avg += duration;
        
    	if (p.dec(c_add) != mpz_class(m1+m2) % p.n){
	    	cout << "Hom ADD   .....  ERROR" << endl;
            return 1;
        }

    }
    avg /= NTESTS;
    cout << "Running time homomorphic m1 + m2: " << avg << " milliseconds" << endl;


	avg = 0.0;
    for(int i = 0; i <= NTESTS; i++){
    	mpz_class m1 = rand() % 10000;
	    mpz_class m2 = rand() % 100000;

	    paillier::Ciphertext c1 = p.enc(m1);

    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    paillier::Ciphertext c_prod = p.mul(c1, m2);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

	    auto duration = duration_cast<microseconds>( t2 - t1 ).count() * 0.001;
        avg += duration;

    	if (p.dec(c_prod) != mpz_class(m1*m2) % p.n){
	    	cout << "Hom Prod   .....  ERROR" << endl;
            return 1;
        }

    }
    avg /= NTESTS;
	cout << "Running time homomorphic c1*m2: " << avg << " milliseconds" << endl;


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


