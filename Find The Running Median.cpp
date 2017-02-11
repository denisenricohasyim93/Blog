//Original problem: https://www.hackerrank.com/challenges/find-the-running-median
//Explanation of the algorithm: https://hansblanco.wordpress.com/2016/06/04/solving-find-median-hackerrank-challenge/

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

class FindMedian
{
	public:
		void insertHeap(int &);
		double getMedian();
	private:
		double median; //Stores current median
		priority_queue<int> max; //Max heap for lower values
		priority_queue<int, vector<int>, greater<int> > min; //Min heap for greater values
		
		void balanceHeaps(); //Method used by insertHeap
};

void FindMedian::insertHeap(int &x)
{
	if (max.empty())
		max.push(x);
	else if (x > max.top())
		min.push(x);
	else if(min.empty())
	{
		min.push(max.top());
		max.pop();
		max.push(x);
	}
	else
		max.push(x);
	balanceHeaps();
}

void FindMedian::balanceHeaps()
{
	if (abs(max.size() - min.size()) > 1) //Heaps are not balanced
	{
		if (max.size() > min.size())
		{
			min.push(max.top());
			max.pop();
		}
		
		else
		{
			max.push(min.top());
			min.pop();
		}
	}
}

double FindMedian::getMedian()
{
	if ((max.size() + min.size()) % 2 == 0)
	{
		median = (max.top() + min.top());
		median /= 2;
	}
	else
	{
		if (min.empty())
			median = max.top();
		else if (min.size() < max.size())
			median = max.top();
		else
			median = min.top();
	}
	
	return median;
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	int n, i;
	FindMedian Ans;
	cin >> n;
	forn1(i, n)
	{
		int x;
		cin >> x;
		Ans.insertHeap(x);
		cout.precision(1);
		cout << fixed << Ans.getMedian() << endl;
	}
	return 0;
}
