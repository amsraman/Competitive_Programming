//Code by Ben Wu
#include<bits/stdc++.h>

using namespace std;

#define PB push_back
#define f first
#define s second
#define what_is(x) cerr << #x << " is " << x << endl;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

bool seen[201][201];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("capture.in", "r", stdin);
    freopen("capture.out", "w", stdout);
    int n, r, c, a, b;
    cin >> n >> r >> c >> a >> b;
    vector<pii> curr[500];
    for(int i=0; i<n; i++)
    {
        int x, y;
        cin >> x >> y;
        curr[0].PB({x, y});
        seen[x][y] = true;
    }

    for(int x=0; x<r+c; x++)
    {
//        for(int i=0; i<r; i++)
//        {
//            for(int j=0; j<c; j++)
//            {
//                cout << seen[i][j] << " ";
//            }
//            cout << "\n";
//        }
//        cout << "\n";
        int pref[r][c];
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                pref[i][j] = seen[i][j];
                if(j)
                    pref[i][j] += pref[i][j-1];
                if(i)
                    pref[i][j] += pref[i-1][j];
                if(i && j)
                    pref[i][j] -= pref[i-1][j-1];
            }
        }
        bool ok = false;
        for(int i=a-1; i<r; i++)
        {
            for(int j=b-1; j<c; j++)
            {
                int tot = pref[i][j];
                if(i>=a)
                {
                    tot -= pref[i-a][j];
                }
                if(j>=b)
                {
                    tot -= pref[i][j-b];
                }
                if(i>=a && j>=b)
                {
                    tot += pref[i-a][j-b];
                }
                ok |= (tot == 0);
            }
        }
        if(!ok)
        {
            cout << x;
            break;
        }
        for(pii p : curr[x])
        {
            int or_ = p.f, oc_ = p.s;
            for(int j=0; j<4; j++)
            {
                int nr = or_ + dr[j];
                int nc = oc_ + dc[j];
                if(nr >= r || nr < 0 || nc < 0 || nc >= c)
                {
                    continue;
                }
                if(seen[nr][nc])
                    continue;
                seen[nr][nc] = true;
                curr[x+1].PB({nr, nc});
            }
        }

    }
    return 0;
}
