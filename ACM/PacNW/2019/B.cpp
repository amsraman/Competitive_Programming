#include <bits/stdc++.h>
#define f first
#define s second
#define INF 0x3f3f3f3f

using namespace std;

int n, k, x[200000], seg[(1<<19)];
vector<int> pos[200000], ans;
pair<int,int> cur;
priority_queue<pair<int,int>> lst;

int qry(int low, int high)
{
    low+=(1<<18), high+=(1<<18);
    int ret = INF;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret,seg[high]), high--;
        if(low%2==1) ret = min(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void upd(int k, int x)
{
    k+=(1<<18), seg[k] = x;
    while(k>1)
    {
        k/=2;
        seg[k] = min(seg[2*k],seg[2*k+1]);
    }
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> x[i];
    for(int i = 0; i<(1<<19); i++)
        seg[i] = INF;
    for(int i = 0; i<n; i++)
        pos[x[i]-1].push_back(i), upd(i,x[i]-1);
    for(int i = 0; i<k; i++)
        lst.push({-pos[i].back(),i});
    cur = {0,-lst.top().f}, lst.pop();
    for(int i = 0; i<k; i++)
    {
        int nxt = qry(cur.f,cur.s);
        for(int i: pos[nxt])
            upd(i,INF), x[i] = INF;
        for(int i: pos[nxt])
            if(i>=cur.f)
            {
                cur.f = i+1;
                break;
            }
        ans.push_back(nxt);
        while(!lst.empty()&&x[cur.s]==INF)
            cur.s = -lst.top().f, lst.pop();
    }
    for(int i: ans)
        cout << i+1 << " ";
    cout << endl;
}
