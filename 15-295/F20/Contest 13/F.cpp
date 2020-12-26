#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, in, block, lf[100001], num[100001];
ll ans = 1;
bool found;
vector<int> primes;
set<int> factors;

int q1(int x)
{
    int ret;
    cout << "A " << x << endl;
    cin >> ret;
    return ret;
}

int q2(int x)
{
    int ret;
    cout << "B " << x << endl;
    cin >> ret;
    return ret;
}

int main()
{
    cin >> n;
    in = n;
    for(int i = 2; i<=n; i++)
        lf[i] = i;
    for(int i = 2; i<=n; i++)
    {
        num[lf[i]]++;
        if(lf[i]==i)
            primes.push_back(i);
        for(int j = 2*i; j<=n; j+=i)
            if(lf[j]==j)
                lf[j] = i;
    }
    block = min(100,(int)primes.size());
    for(int i = 0; i<primes.size(); i++)
    {
        if(q2(primes[i])==num[primes[i]]+1)
            factors.insert(primes[i]);
        in-=num[primes[i]];
        if(!found&&(i==primes.size()-1||i%block==block-1)&&q1(1)==in+1)
        {
            found = true;
            for(int j = block-1; j>=0; j--)
                if(q1(primes[i-j])==1)
                    factors.insert(primes[i-j]);
        }
    }
    for(ll p: factors)
    {
        ll pw = p;
        while(pw<=n&&q1(pw)!=0)
            pw*=(ll)p;
        ans*=(pw/p);
    }
    cout << "C " << ans << endl;
}