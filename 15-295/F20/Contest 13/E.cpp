#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;

bool isPrime(int x)
{
    for(int i = 2; i*i<=x; i++)
        if(x%i==0)
            return false;
    return true;
}

int mul(int a, int b)
{
    return ((ll)a*b)%n;
}

int exp(int a, int b)
{
    int ret = 1;
    while(b)
    {
        if(b&1)
            ret = mul(ret,a);
        a = mul(a,a), b>>=1;
    }
    return ret;
}

int main()
{
    cin >> n;
    if(!isPrime(n)&&n>4)
        cout << "NO" << endl;
    else if(n==4)
        cout << "YES\n1\n3\n2\n4" << endl;
    else
    {
        cout << "YES" << endl;
        cout << 1 << endl;
        for(int i = 1; i<n-1; i++)
            cout << mul(i+1,exp(i,n-2)) << endl;
        if(n>1)
            cout << n << endl;
    }
}