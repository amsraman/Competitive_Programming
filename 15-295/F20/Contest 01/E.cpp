#include <bits/stdc++.h>

using namespace std;

int t, n, ctr, a[8], perm[8];
double ev1[40320], ev2[40320];
vector<int> vec;
map<vector<int>,int> mv;
bool done[40320];

void f(vector<int> vec)
{
    int bp1 = 0, bp2 = 0;
    double cur1 = 0, cur2 = 0;
    bool sorted = true;
    for(int i = 0; i<n-1; i++)
        if(vec[i]>vec[i+1])
            sorted = false;
    if(sorted)
    {
        ev1[mv[vec]] = ev2[mv[vec]] = 0;
        done[mv[vec]] = true;
        return;
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            if(vec[min(i,j)]>vec[max(i,j)])
            {
                swap(vec[min(i,j)],vec[max(i,j)]);
                if(!done[mv[vec]])
                    f(vec);
                cur1+=(ev1[mv[vec]])/double(n*n);
                swap(vec[min(i,j)],vec[max(i,j)]);
            }
            else
                bp1++;
        }
    for(int i = 0; i<n-1; i++)
    {
        if(vec[i]<=vec[i+1])
            bp2++;
        else
        {
            swap(vec[i],vec[i+1]);
            if(!done[mv[vec]])
                f(vec);
            cur2+=(ev2[mv[vec]])/double(n-1);
            swap(vec[i],vec[i+1]);
        }
    }
    ev1[mv[vec]] = (1+cur1)*(double(n*n)/double(n*n-bp1));
    ev2[mv[vec]] = (1+cur2)*(double(n-1)/double(n-1-bp2));
    done[mv[vec]] = true;
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<n; i++)
            vec.push_back(a[i]);
        sort(vec.begin(),vec.end());
        mv[vec] = 0, ctr = 1;
        while(next_permutation(vec.begin(),vec.end()))
            mv[vec] = ctr, ctr++;
        vec.clear();
        for(int i = 0; i<n; i++)
            vec.push_back(a[i]);
        memset(done,false,sizeof(done));
        f(vec);
        cout << fixed << setprecision(6) << "Monty " << ev1[mv[vec]] << " Carlos " << ev2[mv[vec]] << endl;
        vec.clear();
    }
}