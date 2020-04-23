#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <omp.h>

#define M 800000000
#define N 1000000000

#define TYPE_OF_ALGORITHM 1

using namespace std;



void eratostenes(bool* tab, unsigned int n) {
	for (int i = 2; i * i <= n; i++) {
		if (!tab[i]) {
			for (int j = i * i; j <= n; j += i) {
				tab[j] = 1;
			}
		}
	}
}

int main() {
	int sqrt_bound;
	bool* primes;
	bool* tab;
	cout << "lower bound: " << M << "\n";
	cout << "upper bound: " << N << "\n";
	sqrt_bound = sqrt(N);
	primes = new bool[sqrt_bound + 1];
	tab = new bool[N + 1];

	clock_t start, stop;
	double omp_start = omp_get_wtime();

	start = clock();

	if (TYPE_OF_ALGORITHM == 1) {
		if (M >= sqrt_bound) {
			for (int i = 2; i <= sqrt_bound; i++) {
				primes[i] = 0;
			}
			eratostenes(primes, sqrt_bound);
		}

		if (M >= sqrt_bound) {
			for (int i = 2; i <= N; i++) {
				tab[i] = 0;
			}
			for (int i = 0; i <= sqrt_bound; i++) {
				if (primes[i] == 0) {
					int start = M / i;
					start = start * i == M ? start * i : start * i + i;
					for (int j = start; j <= N; j += i) {
						tab[j] = 1;
					}
				}
			}
			for (int i = M; i <= N; i++) {
				if (tab[i] == 0) {
					cout << i << "\t";
				}
			}
		}
		else {
			for (int i = 2; i <= N; i++) {
				tab[i] = 0;
			}
			eratostenes(tab, N);
			/*for (int i = M; i <= N; i++) {
				if (tab[i] == 0) {
					cout << i << "\t";
				}
			}*/
		}
	}
	else {
		for (int i = 2; i <= N; i++) 
			tab[i] = 0;

		eratostenes(tab, N);

		delete[]tab;
	}

	stop = clock();
	double omp_stop = omp_get_wtime();

	printf("Czas pracy procesorow wynosi %f sekund\n", ((double)(stop - start) / 1000.0));
	printf("Czas rzeczywisty wynosi %f sekund\n", ((double)(omp_stop - omp_start)));

	return 0;
}