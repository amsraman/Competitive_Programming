#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007
typedef long long ll;

using namespace std;

int t, n, k, w, al, bl, cl, dl, ah, bh, ch, dh, l[1000000], h[1000000], perim, prv, ans;

int add(int x, int y, int md)
{
    return (x+y)%md;
}

int mul(int x, int y, int md)
{
    return (ll(x)*ll(y))%md;
}

int main()
{
    freopen("perimetric_chapter_1_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        unordered_map<int,int> m;
        cin >> n >> k >> w;
        for(int i = 0; i<k; i++)
            cin >> l[i];
        cin >> al >> bl >> cl >> dl;
        for(int i = 0; i<k; i++)
            cin >> h[i];
        cin >> ah >> bh >> ch >> dh;
        for(int i = k; i<n; i++)
        {
            l[i] = add(add(add(mul(al,l[i-2],dl),mul(bl,l[i-1],dl),dl),cl,dl),1,dl);
            h[i] = add(add(add(mul(ah,h[i-2],dh),mul(bh,h[i-1],dh),dh),ch,dh),1,dh);
        }
        perim = 0, prv = l[0]-w, ans = 1;
        for(int i = 0; i<n; i++)
        {
            perim = add(perim,mul(2,min(w,l[i]-prv),MOD),MOD), prv = l[i];
            for(int j = 0; j<w; j++)
                perim = add(perim,MOD-abs(m[l[i]+j]-m[l[i]+j-1]),MOD);
            for(int j = 0; j<w; j++)
                m[l[i]+j] = max(m[l[i]+j],h[i]), perim = add(perim,abs(m[l[i]+j]-m[l[i]+j-1]),MOD);
            perim = add(perim,h[i],MOD);
            ans = mul(ans,perim,MOD);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}
