/*
ID: adityasund1
TASK: packrec
LANG: C++
*/
#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int ans = 100000;
pair<int,int> rect[4];
vector<pair<int,int> > vec;

void ck(int a, int b, int c)
{
    if(a>b)
        swap(a,b);
    if(a*b<ans)
        ans = a*b, vec.clear(), vec.push_back({a,b});
    else if(a*b==ans)
        vec.push_back({a,b});
}

void process()
{
    ck(rect[0].f+rect[1].f+rect[2].f+rect[3].f,max(max(rect[0].s,rect[1].s),max(rect[2].s,rect[3].s)),0);
    ck(max(rect[0].f,rect[1].f+rect[2].f+rect[3].f),rect[0].s+max(max(rect[1].s,rect[2].s),rect[3].s),1);
    ck(rect[2].f+max(rect[0].f+rect[1].f,rect[3].f),max(rect[2].s,rect[3].s+max(rect[0].s,rect[1].s)),2);
    ck(rect[0].f+rect[3].f+max(rect[1].f,rect[2].f),max(max(rect[0].s,rect[1].s+rect[2].s),rect[3].s),3);
    if(rect[1].s>=rect[3].s)
    {
        int wd = rect[1].f+rect[3].f;
        wd = max(wd,rect[1].f+rect[2].f);
        if(rect[2].s+rect[3].s>rect[1].s)
            wd = max(wd,rect[0].f+rect[2].f);
        else
            wd = max(wd,rect[0].f);
        ck(wd,max(rect[0].s+rect[1].s,rect[2].s+rect[3].s),4);
    }
}

int main()
{
    freopen("packrec.in","r",stdin);
    freopen("packrec.out","w",stdout);
    for(int i = 0; i<4; i++)
        cin >> rect[i].f >> rect[i].s;
    for(int i = 0; i<16; i++)
    {
        for(int j = 0; j<4; j++)
            if((1<<j)&i)
                swap(rect[j].f,rect[j].s);
        for(int perm = 0; perm<24; perm++, next_permutation(rect,rect+4))
            process();
        for(int j = 0; j<4; j++)
            if((1<<j)&i)
                swap(rect[j].f,rect[j].s);
    }
    cout << ans << endl;
    sort(vec.begin(),vec.end());
    for(int i = 0; i<vec.size(); i++)
        if((i==vec.size()-1)||(vec[i]!=vec[i+1]))
            cout << vec[i].f << " " << vec[i].s << endl;
}