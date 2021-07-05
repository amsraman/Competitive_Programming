#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007

using namespace std;

int t, n, v[100000], nb[100000], ns[100000], fact[100001], ifact[100001];

int mul(int a, int b)
{
    return ((ll)a*b)%MOD;
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
    fact[0] = ifact[0] = 1;
    for(int i = 1; i<=1e5; i++)
        fact[i] = mul(fact[i-1],i), ifact[i] = exp(fact[i],MOD-2);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> v[i];
        stack<int> st;
        for(int i = n-1; i>=0; i--)
        {
            while(!st.empty() && v[st.top()]>v[i])
                st.pop();
            if(st.empty())
                nb[i] = n-i-1;
            else
                nb[i] = st.top()-i-1;
            st.push(i);
        }
        while(!st.empty())
            st.pop();
        for(int i = 0; i<n; i++)
        {
            while(!st.empty() && v[st.top()]>=v[i])
                st.pop();
            if(st.empty())
                ns[i] = i;
            else
                ns[i] = i-st.top()-1;
            st.push(i);
        }
        int ans = 1;
        for(int i = 0; i<n; i++)
        {
            //ns represents the number of j such that a[j] == a[i]
            //nb represents the number of things after i that are smaller than i 
            ans = mul(ans,mul(fact[ns[i]+nb[i]],mul(ifact[nb[i]],ifact[ns[i]])));
        }
        for(int i = 1; i<n; i++)
        {
            if(v[i-1]-v[i]+1<0)
                ans = 0;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}