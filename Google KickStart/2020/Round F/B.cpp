#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, k, sp, ans;
pair<int,int> in[100000];

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        for(int i = 0; i<n; i++)
            cin >> in[i].f >> in[i].s;
        sort(in,in+n);
        sp = ans = 0;
        for(int i = 0; i<n; i++)
        {
            sp = max(sp,in[i].f);
            int temp = (max(0,in[i].s-sp+k-1)/k);
            ans+=temp;
            sp+=temp*k;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}
