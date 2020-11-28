#include <bits/stdc++.h>

using namespace std;

int t, n, m, k, ans;

int main()
{
    freopen("subtle_sabotage_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> m >> k;
        ans = 1e6;
        if((2*k+3<=n)&&(k+1<=m))
            ans = min(ans,(m+k-1)/k);
        if((2*k+3<=m)&&(k+1<=n))
            ans = min(ans,(n+k-1)/k);
        if(n>m)
            swap(n,m);
        if((2*k+1<=n)&&(2*k+3<=m))
            ans = min(ans,5-(k>1));
        cout << "Case #" << _ << ": " << (ans==1e6?-1:ans) << endl;
    }
}
