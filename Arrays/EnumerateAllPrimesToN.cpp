/*
* EnumerateAllPrimesToN.cpp
* -----------------
*
* Chapter 6 Question 9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> GeneratePrimes(int n) {
  vector<int> primes;
  vector<int> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (int p = 2; p < n + 1; ++p) {
    if (is_prime[p]) {
      primes.push_back(p);

      // can sieve from p^2 rather than p since all k*p for all k < p have already been sieved
      for (int j = p * p; j < n + 1; j += p) {
        is_prime[j] = false;
      }
    }
  }

  // for (int i = 0; i < n+1; i++) 
  //   cout << is_prime[i] << " ";

  return primes;
}

int main()
{ 
    
    vector<int> test = GeneratePrimes(10);
    
    cout << endl;
   
    for (int i = 0; i < test.size(); i++) 
        cout << test[i] << " ";
    
    return 0;
}