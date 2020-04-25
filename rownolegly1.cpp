#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <omp.h>

#define M 2
#define N 1000000000

using namespace std;

void erato(bool* tab, unsigned int n) {
	for (int i = 2; i * i <= n; i++) {
		if (!tab[i]) {
			for (int j = i * i; j <= n; j += i) {
				tab[j] = 1;
			}
		}
	}
}

void parallel_erato(long long lowerBound, long long upperBound) {
	//omp_set_num_threads(4);
	long long sqrtBound = sqrt(upperBound);
	bool* tab = new bool[upperBound + 1];

	//#pragma omp parallel for
	for (long long i = 0; i <= upperBound; i++) {
		tab[i] = 1;
	}

	//#pragma omp parallel for schedule(dynamic)
	for (long long i = 2; i <= sqrtBound; i++) {
		if (tab[i]) {
			for (long long j = i * i; j <= upperBound; j += i) {
				tab[j] = 0;
			}
		}
	}
}

long long parallel_erato_imp(long long lowerBound, long long upperBound) {
	omp_set_num_threads(4);
	long long sqrtBound = sqrt(upperBound);
	long long sqrtSqrtBound = sqrt(sqrtBound);
	bool* tab = new bool[upperBound + 1];
	bool* primes = new bool[sqrtBound + 1];
	vector<long long> primesNumbers;
	long long primesAm = 0;

#pragma omp parallel 
	{
#pragma omp for
		for (long long i = 0; i <= upperBound; i++) {
			tab[i] = 1;
		}

#pragma omp for
		for (long long i = 0; i <= sqrtBound; i++) {
			primes[i] = 1;
		}

#pragma omp for schedule(dynamic)
		for (long long i = 2; i <= sqrtSqrtBound; i++) {
			if (primes[i]) {
				for (long long j = i * i; j <= sqrtBound; j += i) {
					primes[j] = 0;
				}
			}
		}

#pragma omp single
		for (long long i = 2; i < sqrtBound; i++) {
			if (primes[i]) {
				primesNumbers.push_back(i);
			}
		}

#pragma omp for schedule(dynamic) 
		for (long long i = 0; i < primesNumbers.size(); i++) {
			long long start = lowerBound / primesNumbers[i];
			start = start * primesNumbers[i] == lowerBound ? start * primesNumbers[i] : start * primesNumbers[i] + primesNumbers[i];
			for (long long j = start; j <= upperBound; j += primesNumbers[i]) {
				tab[j] = 0;
			}
		}

#pragma omp for reduction(+:primesAm)
		for (long long i = lowerBound; i <= upperBound; i++) {
			primesAm += tab[i];
		}
	}

	return primesAm;
}

void sieve(long long from, long long to, bool* tab, vector<long long>& primes) {
	for (long long i = 0; i < primes.size(); i++) {
		long long start = from / primes[i];
		start = start * primes[i] == from ? start * primes[i] : start * primes[i] + primes[i];
		for (long long j = start; j <= to; j += primes[i]) {
			tab[j] = 0;
		}
	}
}

void parallel_erato_block(long long lowerBound, long long upperBound, long long slice) {
	omp_set_num_threads(4);
	long long sqrtBound = sqrt(upperBound);
	long long sqrtSqrtBound = sqrt(sqrtBound);
	bool* tab = new bool[upperBound + 1];
	bool* primes = new bool[sqrtBound + 1];
	vector<long long> primesNumbers;

#pragma omp parallel private(primesNumbers)
	{
#pragma omp for
		for (long long i = 0; i <= upperBound; i++) {
			tab[i] = 1;
		}

#pragma omp for
		for (long long i = 0; i <= sqrtBound; i++) {
			primes[i] = 1;
		}

#pragma omp for schedule(dynamic)
		for (long long i = 2; i <= sqrtSqrtBound; i++) {
			if (primes[i]) {
				for (long long j = i * i; j <= sqrtBound; j += i) {
					primes[j] = 0;
				}
			}
		}

#pragma omp single
		for (long long i = 2; i < sqrtBound; i++) {
			if (primes[i]) {
				primesNumbers.push_back(i);
			}
		}

#pragma omp for
		for (long long from = lowerBound; from < upperBound; from += slice) {
			long long to = from + slice;
			if (to > upperBound) {
				to = upperBound;
			}
			sieve(from, to, tab, primesNumbers);
		}
	}
}

int main() {
	double omp_start = omp_get_wtime();
	//parallel_erato_block(500000000, 1000000000, 125000000);
	parallel_erato_imp(500000000, 1000000000);
	double omp_stop = omp_get_wtime();
	printf("\nCzas rzeczywisty wynosi %f sekund\n", ((double)(omp_stop - omp_start)));
}