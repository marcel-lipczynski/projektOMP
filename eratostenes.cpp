#include <iostream>
#include <vector>
#include <math.h>
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
	int m, n, sqrt_bound;
	bool* primes;
	bool* tab;
	cout << "lower bound: ";
	cin >> m;
	cout << "upper bound: ";
	cin >> n;
	sqrt_bound = sqrt(n);
	primes = new bool[sqrt_bound + 1];

	if (m >= sqrt_bound) {
		for (int i = 2; i <= sqrt_bound; i++) {
			primes[i] = 0;
		}
		eratostenes(primes, sqrt_bound);
	}

	tab = new bool[n + 1];

	if (m >= sqrt_bound) {
		for (int i = 2; i <= n; i++) {
			tab[i] = 0;
		}
		for (int i = 0; i <= sqrt_bound; i++) {
			if (primes[i] == 0) {
				int start = m / i;
				start = start * i == m ? start * i : start * i + i;
				for (int j = start; j <= n; j += i) {
					tab[j] = 1;
				}
			}
		}
		for (int i = m; i <= n; i++) {
			if (tab[i] == 0) {
				cout << i << "\t";
			}
		}
	}
	else {
		for (int i = 2; i <= n; i++) {
			tab[i] = 0;
		}
		eratostenes(tab, n);
		for (int i = m; i <= n; i++) {
			if (tab[i] == 0) {
				cout << i << "\t";
			}
		}
	}
	return 0;
}