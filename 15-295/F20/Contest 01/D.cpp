#include <bits/stdc++.h>
 
using namespace std;

int n, a[100000], b[100000], pv1[100000], pv2[100000], ans1, ans2, mx;
string s;

int main()
{
    cin >> s;
    n = s.length();
    for(int i = 0; i<n; i++)
        a[i] = 2*int(s[i]=='R')-1, b[i] = 2*int(s[i]=='B')-1;
    pv1[0] = pv2[0] = 0, mx = 1;
    for(int i = 1; i<n; i++)
    {
        if(a[i-1]>=0)
            a[i]+=a[i-1], pv1[i] = pv1[i-1];
        else
            pv1[i] = i;
        if(a[i]>mx)
            ans1 = pv1[i], ans2 = i, mx = a[i];
    }
    for(int i = 1; i<n; i++)
    {
        if(b[i-1]>=0)
            b[i]+=b[i-1], pv2[i] = pv2[i-1];
        else
            pv2[i] = i;
        if((b[i]>mx)||((b[i]==mx)&&(pv2[i]<ans1))||((b[i]==mx)&&(pv2[i]==ans1)&&(i<ans2)))
            ans1 = pv2[i], ans2 = i, mx = b[i];
    }
    if(ans1==ans2)
        ans1 = ans2 = 0;
    cout << ans1+1 << " " << ans2+1 << endl;
}