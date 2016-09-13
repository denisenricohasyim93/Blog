//Includes all the standard C++ libraries
#include <bits/stdc++.h>

using namespace std;
//These are the macros i use
#define pb push_back
#define mp make_pair
#define forn1(i, n) for (i = 0; i < n; ++i)
#define forn2(i, n) for (i = 1; i <= n; ++i)
#define forr1(i, n) for (i = n; i > 0; --i)
#define forr2(i, n) for (i = n - 1; i >= 0; --i)
#define fori(i, s) for (i = s.begin(); i != s.end(); ++i)
#define ll long long

class Median
{
	public:
		double insertMSet(int &);
		double eraseMSet(int &);
		double getMedian();
	private:
		double median; //Stores current median
		multiset<ll> maxElements; //multiset for greater values
		multiset<ll> minElements; //multiset for lower values
		void balance();
};

//returns the median
double Median::insertMSet(int &x)
{
	if(minElements.empty())
		minElements.insert(x);
	else if(x >= *prev(minElements.end()))
		maxElements.insert(x);
	else if(maxElements.empty())
	{
		maxElements.insert(*prev(minElements.end()));
		minElements.erase(prev(minElements.end()));
		minElements.insert(x);
	}
	else
		minElements.insert(x);
	balance();
	return getMedian();
}

//returns the median
double Median::eraseMSet(int &x)
{
	auto it1 = maxElements.find(x);
	auto it2 = minElements.find(x);
	if(it1 == maxElements.end())
	{
		if(it2 == minElements.end())
			throw runtime_error("Empty");
		else
		{
			minElements.erase(it2);
			if(maxElements.empty() && minElements.empty())
				throw runtime_error("Empty");
		}
	}
	else
	{
		maxElements.erase(it1);
		if(maxElements.empty() && minElements.empty())
			throw runtime_error("Empty");
	}
	balance();
	return getMedian();
}

void Median::balance()
{
	if (abs(static_cast<int>(maxElements.size()) - static_cast<int>(minElements.size())) > 1) //not balanced
	{
		
		if(maxElements.size() > minElements.size())
		{
			minElements.insert(*maxElements.begin());
			maxElements.erase(maxElements.begin());
		}
		else
		{
			maxElements.insert(*prev(minElements.end()));
			minElements.erase(prev(minElements.end()));
		}
	}
}

double Median::getMedian()
{
	if(abs(static_cast<int>(maxElements.size()) - static_cast<int>(minElements.size())) % 2 == 0)
		median = (*maxElements.begin() + *prev(minElements.end()))/2.0;
	else
	{
		if (maxElements.empty())
			median =  *prev(minElements.end());
		else if (maxElements.size() < minElements.size())
			median = *prev(minElements.end());
		else
			median = *maxElements.begin();
	}
	return median;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int N;
	cin >> N;
	Median m;
	cout << fixed << showpoint;
    cout <<setprecision(1);
	for(int i = 0; i < N; i++)
	{
		char temp;
    	int tempint;
		cin >> temp >> tempint;
        if(temp == 'r')
        {
        	try
        	{
        		double x = m.eraseMSet(tempint);
        		string str = to_string (x);
				str.erase ( str.find_last_not_of('0') + 1, string::npos );
				if(str[str.size()-1] == '.')
					str.pop_back();
        		cout << str;
        	}
        	catch(runtime_error &e)
        	{
        		cout << "Wrong!";
			}
		}
		else
		{
			double x = m.insertMSet(tempint);
        	string str = to_string (x);
            str.erase ( str.find_last_not_of('0') + 1, string::npos );
			if(str[str.size()-1] == '.')
					str.pop_back();
			cout << str;
		}
		cout << endl;
   }
   return 0;
}
