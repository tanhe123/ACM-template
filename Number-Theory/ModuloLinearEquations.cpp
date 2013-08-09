#define long long LL

//Euclid-extanded version for solving gcd(a,b)=ax+by
int ext_gcd(int a,int b,int& x,int& y)
{
  int t,ret;
	if (!b){
		x=1,y=0;
		return a;
	}
	ret=ext_gcd(b,a%b,x,y);
	t=x,x=y,y=t-a/b*y;
	return ret;
}

//find x, y that satisfied the equation ax+by=d, which minimize the {|x|+|y|}. ps:d = gcd(a,b).
void gcd(LL a, LL b, LL &d, LL &x, LL &y)
{
  if (!b)
	{
		d = a, x = 1, y = 0;
	}
	else
	{
		gcd(b, a %b, d, y, x);
		y -= x * (a / b);
	}
}

//for a single equation a = b(mod n);
LL modular_linear_equation(LL a, LL b, LL n)
{
	long long x, y, e, d;
	gcd(a, n,d, x, y);
	if (b % d)  return -1;
	e = b / d * x % n + n;
	return e % (n / d);
}

//another version, something goes wrong with it, i haven't varified it's rightness. the answer lies in sol.
int modular_linear(int a,int b,int n,int* sol)
{
  int d,e,x,y,i;
	d=ext_gcd(a,n,x,y);
	if (b%d)
		return 0;
	e=(x*(b/d)%n+n)%n;
	for (i=0;i<d;i++)
		sol[i]=(e+i*(n/d))%n;
	return d;
}

//calculate a^b mod n, O(log(b)). no restrictions of prime number "n"
int modular_exponent(int a,int b,int n)
{ //a^b mod n
  int ret=1;
	for (;b;b>>=1,a=(int)((i64)a)*a%n)
		if (b&1)
			ret=(int)((i64)ret)*a%n;
	return ret;
}

//China Remainder Theorem for solving groups of equations.
//  x = b[0] (mod w[0])
//  x = b[1] (mod w[1])
//  ...
//  x = b[k-1] (mod w[k-1])
//w[i]>0, for each i and j, w[i] relatively prime with w[j], the answers vary from 1 to n, and n=w[0]*w[1]*...*w[k-1]
int modular_linear_system(int b[],int w[],int k){
  int d,x,y,a=0,m,n=1,i;
	for (i=0;i<k;i++)
		n*=w[i];
	for (i=0;i<k;i++){
		m=n/w[i];
		d=ext_gcd(w[i],m,x,y);
		a=(a+y*m*b[i])%n;
	}
	return (a+n)%n;
}
