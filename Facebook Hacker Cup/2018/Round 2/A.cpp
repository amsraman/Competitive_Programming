#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, k;
vector<pair<pair<int,int>,int>> edges;

int main()
{
    freopen("ethan_finds_the_shortest_path_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        cout << "Case #" << _ << ": " << max(0,k*(k-1)/2-(max(0,k-n)+1)*max(0,k-n)/2-k) << endl;
        edges.push_back({{1,n},k});
        for(int i = 0; i<min(n,k)-2; i++)
            edges.push_back({{i+1,i+2},k-i-1});
        if((n>2)&&(k>2))
            edges.push_back({{min(n,k)-1,n},k-min(n,k)+1});
        cout << edges.size() << endl;
        for(auto x: edges)
            cout << x.f.f << " " << x.f.s << " " << x.s << endl;
        edges.clear();
    }
}
