#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll w, n, x[100000], tot1, tot2, ans;

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> w >> n;
        for(int i = 0; i<w; i++)
            cin >> x[i];
        sort(x,x+w);
        tot1 = 0, tot2 = 0, ans = w*n;
        int extra = w%2;
        deque<ll> dq;
        for(int i = 0; i<w; i++)
            dq.push_back(x[i]);
        for(int i = 0; i<w/2; i++)
            tot1+=x[i];
        for(int i = w/2; i<w; i++)
            tot2+=x[i];
        for(int i = 0; i<w; i++)
        {
            ans = min(ans,tot2-tot1-extra*dq[w/2]);
            tot1-=dq.front(), tot2-=dq[w/2];
            tot1+=dq[w/2], tot2+=(n+dq.front());
            dq.push_back(n+dq.front());
            dq.pop_front();
        }
        cout << "Case #" << cs << ": " << ans << endl;
    }
}
