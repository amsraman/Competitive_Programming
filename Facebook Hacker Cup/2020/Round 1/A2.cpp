#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007
typedef long long ll;

using namespace std;

int t, n, k, al, bl, cl, dl, aw, bw, cw, dw, ah, bh, ch, dh, l[1000000], w[1000000], h[1000000], perim, ans;
multiset<pair<int,int>> rect;

int add(int x, int y, int md = MOD)
{
    return (x+y)%md;
}

int sub(int x, int y, int md = MOD)
{
    return (x-y+md)%md;
}

int mul(int x, int y, int md = MOD)
{
    return (ll(x)*ll(y))%md;
}

int main()
{
    freopen("perimetric_chapter_2_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        for(int i = 0; i<k; i++)
            cin >> l[i];
        cin >> al >> bl >> cl >> dl;
        for(int i = 0; i<k; i++)
            cin >> w[i];
        cin >> aw >> bw >> cw >> dw;
        for(int i = 0; i<k; i++)
            cin >> h[i];
        cin >> ah >> bh >> ch >> dh;
        for(int i = k; i<n; i++)
        {
            l[i] = 1+add(add(mul(al,l[i-2],dl),mul(bl,l[i-1],dl),dl),cl,dl);
            w[i] = 1+add(add(mul(aw,w[i-2],dw),mul(bw,w[i-1],dw),dw),cw,dw);
            h[i] = 1+add(add(mul(ah,h[i-2],dh),mul(bh,h[i-1],dh),dh),ch,dh);
        }
        perim = 0, ans = 1;
        for(int i = 0; i<n; i++)
        {
            pair<int,int> x = {l[i],l[i]+w[i]}, y = {l[i],l[i]+w[i]};
            rect.insert(x);
            auto it = rect.find(x), it2 = (++rect.find(x));
            if(((it!=rect.begin())&&((--it)->second>=x.s))||((it2!=rect.end())&&(it2->first==l[i]))||(rect.count(x)>1))
                rect.erase(rect.find(x));
            else
            {
                it = (++rect.find(x));
                while((it!=rect.end())&&(it->second<l[i]+w[i]))
                {
                    pair<int,int> temp = *it;
                    it++;
                    rect.erase(rect.find(temp));
                    perim = sub(perim,mul(2,add(h[i],temp.s-temp.f)));
                }
                it = (++rect.find(y));
                if((it!=rect.end())&&(it->first<=l[i]+w[i]))
                    perim = sub(perim,mul(2,add(h[i],it->second-it->first))), x.s = it->second, rect.erase(it);
                it = rect.find(y);
                if((it!=rect.begin())&&((--it)->second>=l[i]))
                    perim = sub(perim,mul(2,add(h[i],it->second-it->first))), x.f = it->first, rect.erase(it);
                rect.erase(rect.find(y));
                rect.insert(x);
                perim = add(perim,mul(2,add(h[i],x.s-x.f)));
            }
            ans = mul(ans,perim);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        rect.clear();
    }
}
