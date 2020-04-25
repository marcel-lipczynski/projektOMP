#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <omp.h>

#define M 2
#define N 1000000000

using namespace std;


void parallel_erato(long long lowerBound, long long upperBound) {
	omp_set_num_threads(4);
	long long sqrtBound = sqrt(upperBound);
	bool* tab = new bool[upperBound + 1];

#pragma omp parallel for
	for (long long i = 0; i <= upperBound; i++) {
		tab[i] = 1;
	}

#pragma omp parallel for schedule(dynamic)
	for (long long i = 2; i <= sqrtBound; i++) {
		if (tab[i]) {
			for (long long j = i * i; j <= upperBound; j += i) {
				tab[j] = 0;
			}
		}
	}
}

void parallel_erato_imp(long long lowerBound, long long upperBound) {
	omp_set_num_threads(4);
	long long sqrtBound = sqrt(upperBound);
	long long sqrtSqrtBound = sqrt(sqrtBound);
	bool* tab = new bool[upperBound + 1];
	bool* primes = new bool[sqrtBound + 1];
	vector<long long> primesNumbers;

#pragma omp parallel for
	for (long long i = 0; i <= upperBound; i++) {
		tab[i] = 1;
	}

#pragma omp parallel for
	for (long long i = 0; i <= sqrtBound; i++) {
		primes[i] = 1;
	}

#pragma omp parallel for schedule(dynamic)
	for (long long i = 2; i <= sqrtSqrtBound; i++) {
		if (primes[i]) {
			for (long long j = i * i; j <= sqrtBound; j += i) {
				primes[j] = 0;
			}
		}
	}

	for (long long i = 2; i < sqrtBound; i++) {
		if (primes[i]) {
			primesNumbers.push_back(i);
		}
	}

#pragma omp parallel for schedule(dynamic) 
	for (long long i = 0; i < primesNumbers.size(); i++) {
		long long start = lowerBound / primesNumbers[i];
		start = start * primesNumbers[i] == lowerBound ? start * primesNumbers[i] : start * primesNumbers[i] + primesNumbers[i];
		for (long long j = start; j <= upperBound; j += primesNumbers[i]) {
			tab[j] = 0;
		}
	}

	long long primesAm = 0;
#pragma omp parallel for reduction(+:primesAm)
	for (long long i = lowerBound; i <= upperBound; i++) {
		primesAm += tab[i];
	}

	cout << primesAm;
}

int main() {
	double omp_start = omp_get_wtime();
	parallel_erato_imp(800000000, 1000000000);
	double omp_stop = omp_get_wtime();
	printf("\nCzas rzeczywisty wynosi %f sekund\n", ((double)(omp_stop - omp_start)));
}