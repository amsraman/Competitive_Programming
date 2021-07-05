#include <bits/stdc++.h>

using namespace std;

int t, p, par[200], dep[200], nc, tot, root;
map<string,int> ind;
vector<int> g[200];
string pr, cd, name[200];

void dfs(int u, int v)
{
    for(int i: g[u])
        if(i!=v)
            dep[i] = dep[u]+1, dfs(i,u);
}

int lca(int u, int v)
{
    if(dep[u]<dep[v])
        swap(u,v);
    while(dep[u]>dep[v])
        u = par[u];
    while(u!=v)
        u = par[u], v = par[v];
    return v;
}

int main()
{
    cin >> t >> p;
    for(int i = 0; i<200; i++)
        par[i] = -1;
    for(int i = 0, d; i<t; i++)
    {
        cin >> pr >> d;
        if(!ind.count(pr))
            name[nc] = pr, ind[pr] = nc++;
        for(int j = 0; j<d; j++)
        {
            cin >> cd;
            if(!ind.count(cd))
                name[nc] = cd, ind[cd] = nc++;
            g[ind[pr]].push_back(ind[cd]);
            par[ind[cd]] = ind[pr];
        }
    }
    while(par[root]!=-1)
        root = par[root];
    dfs(root,root);
    for(int i = 0; i<p; i++)
    {
        cin >> pr >> cd;
        int ind1 = ind[pr], ind2 = ind[cd], anc = lca(ind1,ind2);
        //One is a direct descendent of the other
        if(anc==ind1||anc==ind2)
        {
            if(dep[ind1]<dep[ind2])
                swap(ind1,ind2);
            if(dep[ind1]-dep[ind2]==1)
                cout << name[ind1] << " is the child of " << name[ind2] << endl;
            else if(dep[ind1]-dep[ind2]==2)
                cout << name[ind1] << " is the grandchild of " << name[ind2] << endl;
            else
            {
                cout << name[ind1] << " is the ";
                for(int j = 0; j<dep[ind1]-dep[ind2]-2; j++)
                    cout << "great ";
                cout << "grandchild of " << name[ind2] << endl;
            }
        }
        else if(dep[ind1]==dep[anc]+1&&dep[ind2]==dep[anc]+1)
            cout << name[ind1] << " and " << name[ind2] << " are siblings" << endl;
        else
        {
            cout << name[ind1] << " and " << name[ind2] << " are " << min(dep[ind1],dep[ind2])-dep[anc]-1;
            if((min(dep[ind1],dep[ind2])-dep[anc]-1)%10==1&&(min(dep[ind1],dep[ind2])-dep[anc]-1)!=11)
                cout << "st";
            else if((min(dep[ind1],dep[ind2])-dep[anc]-1)%10==2&&(min(dep[ind1],dep[ind2])-dep[anc]-1)!=12)
                cout << "nd";
            else if((min(dep[ind1],dep[ind2])-dep[anc]-1)%10==3&&(min(dep[ind1],dep[ind2])-dep[anc]-1)!=13)
                cout << "rd";
            else
                cout << "th";            
            cout << " cousins";
            if(abs(dep[ind1]-dep[ind2])==1)
                cout << ", 1 time removed";
            else if(abs(dep[ind1]-dep[ind2])>1)
                cout << ", " << abs(dep[ind1]-dep[ind2]) << " times removed";
            cout << endl;
        }
    }
}