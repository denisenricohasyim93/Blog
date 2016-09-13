#include <bits/stdc++.h>
#define ull unsigned long long
#define mp make_pair
#define MOD 1000000007

using namespace std;

template <typename T>
T exp(T p, unsigned q)
{
    T r(1);
    while (q != 0) {
        if (q % 2 == 1) {    // q is odd
            r = ((r%MOD)*(p%MOD))%MOD;
            q--;
        }
        p = ((p%MOD)*(p%MOD))%MOD;
        q /= 2;
    }
    return r;
}

ull modInverse(ull a, ull m)
{
	return exp(a, m-2);
}

map<ull, ull> factorials;
ull factorial(ull const &x)
{
	if(x == 0)
		return 1;
	if(factorials.find(x) != factorials.end())
		return factorials[x];
	ull fact = x;
	fact *= factorial(x-1) % MOD;
	if(factorials.find(x) == factorials.end())
		factorials.insert(mp(x, fact));
	return fact;
}

ull palindromeAnagrams(string &s)
{
	map<char, ull> m;
	for(auto x : s)
	{
		if(m.find(x) == m.end())
			m.insert(mp(x, 1));
		else
			m[x]++;
	}
	for(auto x : m)
		m[x.first] /= 2;	
	ull num = s.length() / 2;
	ull den = 1;
	num = factorial(num);
	for(auto x : m)
		num = ((num%MOD) * (modInverse(factorial(m[x.first]), MOD)%MOD));
	return num%MOD;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	string s;
	cin >> s;
	cout << palindromeAnagrams(s);
	return 0;
}
