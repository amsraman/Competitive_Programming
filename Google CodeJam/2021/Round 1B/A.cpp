#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll mxT = 360*12*(1e10), deg[3];
array<ll,4> ans;

ll sub(ll a, ll b)
{
    return (a+mxT-b)%mxT;
}

ll mul(ll a, ll b)
{
    return (a*b)%mxT;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        for(int i = 0; i<3; i++)
            cin >> deg[i];
        do {
            ll k = sub(sub(deg[2],mul(60,deg[1])),mul(5,sub(deg[1],mul(12,deg[0]))));
            if(k%4!=0)
                continue;
            k/=4;
            for(int i = 0; i<4; i++) {
                for(int j = 0; j<3; j++)
                    deg[j] = (deg[j]+k)%mxT;
                if(deg[1] == (12*deg[0])%mxT && deg[2] == (720*deg[0])%mxT)
                    ans = {deg[0]/(mxT/12),(deg[0]%(mxT/12))/(mxT/720),(deg[0]%(mxT/720))/(mxT/(12*60*60)),(deg[0]%(mxT/(12*60*60)))};
                for(int j = 0; j<3; j++)
                    deg[j] = sub(deg[j],k);
                k+=(mxT/4);
            }
        } while(next_permutation(deg,deg+3));
        cout << "Case #" << _ << ": ";
        for(int i = 0; i<4; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}