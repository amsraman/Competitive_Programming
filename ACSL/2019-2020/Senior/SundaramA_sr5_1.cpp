#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

string n, ans;
int p, fact;
ll temp;

string tostring(int a)
{
    string ret = ((a)?(""):("0"));
    while(a>0) ret = char('0'+a%10)+ret, a/=10;
    return ret;
}

int main()
{
    freopen("srdata1.txt","r",stdin);
    for(int z = 0; z<5; z++)
    {
        cin >> n >> p;
        p = n.length()-p, temp = 0, fact = 0, ans = "";
        for(int i = 0; i<n.length(); i++) temp*=10, temp+=(n[i]-'0');
        for(ll i = 2; i*i<=temp; i++)
        {
            if(temp%i==0) fact++;
            while(temp%i==0) temp/=i;
        }
        if(temp!=1) fact++;
        for(int i = 0; i<n.length(); i++)
        {
            if(i<p) ans+=tostring((n[i]-'0')+(n[p]-'0'));
            else if(i==p) ans+=tostring(fact);
            else ans+=tostring(abs((n[i]-'0')-(n[p]-'0')));
        }
        cout << ans << endl;
    }
}
