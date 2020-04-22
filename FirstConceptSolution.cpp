#include <stdio.h>
#include <math.h>
#include <vector>

#define M 40
#define N 49

using namespace std;

int main() {

	vector<int> primeNumbers{2};
	if(M==2) printf("%d ", primeNumbers[0]);
	
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
			if(i >= M) printf("%d ", i);
		}
	}

	
}