#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

ll n;

int add(int a, int b)
{
    return (a+b)%MOD;
}

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

int pow(int a, ll b)
{
    int ret = 1;
    while(b>0)
    {
        if(b%2==1)
            ret = mul(ret,a);
        a = mul(a,a), b/=2;
    }
    return ret;
}

int main()
{
    cin >> n;
    cout << add(mul(12,pow(26,n-1)),mul(7,pow(13,n-1))) << endl;
}