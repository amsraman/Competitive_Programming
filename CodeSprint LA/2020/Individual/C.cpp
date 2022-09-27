#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, themed[60];
ll pow2[62], d, ans = 1;
vector<int> bts;
bool v[60];

int main()
{
    pow2[0] = 1;
    for(int i = 1; i<62; i++)
        pow2[i] = 2*pow2[i-1];
    cin >> n >> k >> d;
    for(int i = 0; i<k; i++)
        cin >> themed[i];
    if(d>pow2[n+1])
        ans = 0;
    for(int i = 0; i<k; i++)
    {
        d-=pow2[themed[i]-1];
        v[themed[i]-1] = true;
    }
    if(d<0)
        ans = 0;
    if(d%2==1)
        ans = 0;
    for(int i = 0; d!=0; i++)
    {
        if(d%2==1)
            bts.push_back(i);
        d/=2;
    }
    for(int i = 0; i<bts.size(); i++)
        if((bts[i]>0)&&(v[bts[i]-1]))
            ans = 0;
    for(int i = 0; i<k; i++)
        ans*=2;
    cout << ans << endl;
}
