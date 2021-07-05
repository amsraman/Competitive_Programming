#include <bits/stdc++.h>

using namespace std;

int s, n, sm[100000];
char type;
vector<int> vn, vy;

bool solve()
{
    int mn = 0x3f3f3f3f;
    for(int i = vy.size()-1; i>=0; i--)
        mn = min(mn,vy[i]-i-1), sm[i] = mn;
    if(mn<0)
        return false;
    for(int p1 = 0, p2 = 0, t = 1, psh = 0; (p1<vn.size()||p2<vy.size()); t++)
    {
        for(int i = 0; (i<s-1&&p1<vn.size()); i++, p1++)
            if(vn[p1]<t)
                return false;
        if(p1<vn.size()&&(p2==vy.size()||psh<sm[p2]))
        {
            psh++;
            if(vn[p1++]<t)
                return false;
        }
        else if(p2<vy.size()&&vy[p2++]<t)
            return false;
    }
    return true;
}

int main()
{
    cin >> s >> n;
    for(int i = 0, d; i<n; i++)
    {
        cin >> d >> type;
        if(type=='y')
            vy.push_back(d);
        else
            vn.push_back(d);
    }
    sort(vn.begin(),vn.end());
    sort(vy.begin(),vy.end());
    cout << (solve()?"Yes":"No") << endl;
}