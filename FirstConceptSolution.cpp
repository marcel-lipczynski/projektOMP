#include <stdio.h>
#include <math.h>
#include <vector>

#define M 2
#define N 2500000

using namespace std;

int main2() {

	vector<int> primeNumbers{ 2 };
	if (M == 2) printf("%d ", primeNumbers[0]);

	for (int i = 3; i <= N; i++) {
		bool isDivided = false;

		for (int j = 0; primeNumbers[j] <= sqrt(i) && j <= primeNumbers.size(); j++) {
			if (i % primeNumbers[j] == 0) {
				isDivided = true;
				break;
			}

		}
		if (!isDivided) {
			primeNumbers.push_back(i);
			if (i >= M) printf("%d ", i);
		}
	}
	return 0;
}