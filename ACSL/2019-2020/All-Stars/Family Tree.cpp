#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, ct, sp[10000], m1, m2;
pair<int,int> par[10000];
string s1, s2, marker[10000];
map<string,int> m;
bool cousin[1000][1000];

bool isSib(int a, int b)
{
    if((a==0)||(b==0))
        return false;
    int paf = par[a].f, pbf = par[b].f, pas = par[a].s, pbs = par[b].s;
    if(paf==0)
        paf = 100;
    if(pas==0)
        pas = 101;
    if(pbf==0)
        pbf = 102;
    if(pbs==0)
        pbs = 103;
    if((paf==pbf)||(paf==pbs)||(pas==pbf))
        return true;
    return false;
}

bool isCousin(int a, int b)
{
    if((a==0)||(b==0))
        return false;
    return (isSib(par[a].f,par[b].f)||isSib(par[a].f,par[b].s)||isSib(par[a].s,par[b].f)||isSib(par[a].s,par[b].s));
}

int main()
{
    cin >> n;
    for(int i = 0; i<2*n; i++)
        par[i] = {0,0};
    for(int i = 0; i<n; i++)
    {
        cin >> s1 >> s2;
        if(!m[s1])
            m[s1] = ++ct, marker[ct] = s1;
        if(!m[s2])
            m[s2] = ++ct, marker[ct] = s2;
        if(par[m[s2]].f==0)
            par[m[s2]].f = m[s1];
        else
            par[m[s2]].s = m[s1];
    }
    cin >> s1 >> s2;
    m1 = m[s1], m2 = m[s2];
    for(int i = 0; i<ct; i++)
    {
        if(par[i+1].s!=0)
        {
            sp[par[i+1].s] = par[i+1].f;
            sp[par[i+1].f] = par[i+1].s;
        }
    }
    for(int i = 0; i<n; i++)
        if((par[i].s==0)&&(sp[par[i].f]!=0))
            par[i].s = sp[par[i].f];
    for(int i = 0; i<ct; i++)
        if(sp[i]!=0)
        {
            if((par[i].f!=par[sp[i]].f)&&(par[sp[i]].f!=0))
                par[i].s = par[sp[i]].f;
            int pc1, pc2;
            if(par[i].f==0)
                pc1 = 0;
            else if(par[i].s==0)
                pc1 = 1;
            else
                pc1 = 2;
            if(par[sp[i]].f==0)
                pc2 = 0;
            else if(par[sp[i]].f==0)
                pc2 = 1;
            else
                pc2 = 2;
            if(pc1<pc2)
                par[i] = par[sp[i]];
        }
    if(sp[m1]==m2)
        cout << "spouse" << endl;
    else if((par[m1].f==m2)||(par[m1].s==m2))
        cout << "parent" << endl;
    else if((par[par[m1].f].f==m2)||(par[par[m1].f].s==m2)||(par[par[m1].s].f==m2)||(par[par[m1].s].s==m2))
        cout << "grandparent" << endl;
    else if((par[par[par[m1].f].f].f==m2)||(par[par[par[m1].f].s].f==m2)||(par[par[par[m1].s].f].f==m2)||(par[par[par[m1].s].s].f==m2)||(par[par[par[m1].f].f].s==m2)||(par[par[par[m1].f].s].s==m2)||(par[par[par[m1].s].f].s==m2)||(par[par[par[m1].s].s].s==m2))
        cout << "great-grandparent" << endl;
    else if((par[m2].f==m1)||(par[m2].s==m1))
        cout << "child" << endl;
    else if((par[par[m2].f].f==m1)||(par[par[m2].f].s==m1)||(par[par[m2].s].f==m1)||(par[par[m2].s].s==m1))
        cout << "grandchild" << endl;
    else if((par[par[par[m2].f].f].f==m1)||(par[par[par[m2].f].s].f==m1)||(par[par[par[m2].s].f].f==m1)||(par[par[par[m2].s].s].f==m1)||(par[par[par[m2].f].f].s==m1)||(par[par[par[m2].f].s].s==m1)||(par[par[par[m2].s].f].s==m1)||(par[par[par[m2].s].s].s==m1))
        cout << "great-grandchild" << endl;
    else if(isSib(m1,m2))
        cout << "sibling" << endl;
    else if(isCousin(m1,m2))
        cout << "cousin" << endl;
    else if((isCousin(par[m1].f,par[m2].f))||(isCousin(par[m1].f,par[m2].s))||(isCousin(par[m1].s,par[m2].f))||(isCousin(par[m1].s,par[m2].s)))
        cout << "second cousin" << endl;
    else if(isSib(m2,par[m1].f)||isSib(m2,par[m1].s))
        cout << "pibling" << endl;
    else if(isSib(m2,par[par[m1].f].f)||isSib(m2,par[par[m1].f].s)||isSib(m2,par[par[m1].s].f)||isSib(m2,par[par[m1].s].s))
        cout << "grandpibling" << endl;
    else if(isSib(m1,par[m2].f)||isSib(m1,par[m2].s))
        cout << "nibling" << endl;
    else if(isSib(m1,par[par[m2].f].f)||isSib(m1,par[par[m2].f].s)||isSib(m1,par[par[m2].s].f)||isSib(m1,par[par[m2].s].s))
        cout << "grandnibling" << endl;
}
