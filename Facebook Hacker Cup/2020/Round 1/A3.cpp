#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int t, n, k, al, bl, cl, dl, aw, bw, cw, dw, ah, bh, ch, dh, l[1000000], w[1000000], h[1000000], perim, ans;
set<array<int,5>> rect;

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
    freopen("perimetric_chapter_3_full_input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ofstream fout("output.txt");
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
            array<int,5> x = {l[i],l[i]+w[i],-h[i],h[i],h[i]}, y = {l[i],l[i]+w[i],-h[i],h[i],h[i]};
            rect.insert(x);
            auto it = rect.find(x);
            if((it!=rect.begin())&&((*(--it))[1]>x[1]))
            {
                array<int,5> temp1 = (*it), temp2 = (*it);
                rect.erase(it);
                perim = sub(perim,mul(2,x[1]-x[0]));
                x[3] = x[4] = h[i]+temp1[2], temp1[4] = temp2[3] = 0, temp1[1] = x[0], temp2[0] = x[1];
                rect.insert(temp1);
                rect.insert(temp2);
            }
            else
            {
                it = (++rect.find(y));
                while((it!=rect.end())&&((*it)[1]<=l[i]+w[i]))
                {
                    array<int,5> temp = *it;
                    it++;
                    rect.erase(rect.find(temp));
                    perim = sub(perim,add(mul(2,temp[1]-temp[0]),add(temp[3],temp[4])));
                }
                it = (rect.find(y));
                while((it!=rect.begin())&&((*(--it))[0]==l[i]))
                {
                    array<int,5> temp = *it;
                    it++;
                    rect.erase(rect.find(temp));
                    perim = sub(perim,add(mul(2,temp[1]-temp[0]),add(temp[3],temp[4])));
                }
                it = (++rect.find(y));
                if((it!=rect.end())&&((*it)[0]<=l[i]+w[i]))
                {
                    array<int,5> temp = *it;
                    rect.erase(it);
                    perim = sub(perim,add(temp[3],mul(2,x[1]-temp[0]))), temp[0] = x[1], temp[3] = 0, x[4]+=temp[2];
                    rect.insert(temp);
                }
                it = rect.find(y);
                if((it!=rect.begin())&&((*(--it))[1]>=l[i]))
                {
                    array<int,5> temp = *it;
                    rect.erase(it);
                    perim = sub(perim,add(temp[4],mul(2,temp[1]-x[0]))), temp[1] = x[0], temp[4] = 0, x[3]+=temp[2];
                    rect.insert(temp);
                }
            }
            rect.erase(rect.find(y));
            rect.insert(x);
            perim = add(perim,add(mul(2,x[1]-x[0]),add(x[3],x[4])));
            ans = mul(ans,perim);
        }
        fout << "Case #" << _ << ": " << ans << endl;
        cout << "Case #" << _ << ": " << ans << endl;
        rect.clear();
    }
}
