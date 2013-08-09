//as a example, poj2635
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define Max 1000000 + 100

bool prime[Max];
int p[100000];

int IsPrime()
{
  prime[0] = prime[1] = 0;
	prime[2] = 1;
	for (int i = 3; i < Max; i++)
	{
		prime[i] = i % 2 == 0 ? 0 : 1;
	}
	int t = (int) sqrt(Max*1.0);
	for (int i = 3; i <= t; i++)
	{
		if (prime[i])
		{
			for (int j = i * 2; j < Max; j += i)
			{
				prime[j] = 0;
			}
		}
	}

	int j = 1;
	for (int k = 0; k < Max; k++)
	{
		if (prime[k])
		{
			p[j++] = k;
		}
	}
	return j;
}

bool mod(const int* K, const int p, const int len)
{
	int sq = 0;
	for (int i = len - 1; i >= 0; i--)
		sq = (sq * 1000 + K[i])%p;  //同余模定理  

	if (!sq)   //K被整除  
		return false;
	return true;
}

int main()
{
	int num_of_prime = IsPrime();

	int num[100];
	string s;
	int l;
	while (cin >> s >> l && l)
	{
		memset(num, 0, sizeof(num));
		for (int i = 0; i < s.size(); i++)//局部顺序，全局倒序  
		{
			int pKt = (s.size() + 2 - i) / 3 - 1;
			num[pKt] = num[pKt] * 10 + (s[i] - '0');
		}

		int length_of_num = (s.size() + 2) / 3;

		bool flag = true;

		for (int i = 1; p[i] < l; ++i)
		{
			if (!mod(num, p[i], length_of_num))
			{
				flag = false;
				cout << "BAD " << p[i] << endl;
				break;
			}
		}
		if (flag)
			cout << "GOOD" << endl;

	}
	system("pause");
}
