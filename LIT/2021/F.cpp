#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 998244353;

int n, q, t, in[100000], out[100000], sz[100000], poly[100000][501], fact[100001], ifact[100001];
vector<int> g[100000];

int mul(int a, int b) {
    return ((ll) a * b) % mod;
}

int exp(int a, int b) {
    int ret = 1;
    while(b) {
        if(b&1) {
            ret = mul(ret,a);
        }
        a = mul(a,a), b >>= 1;
    }
    return ret;
}

void poly_mul(int ind, int num) {
    for(int i = g[ind].size(); i>0; i--) {
        poly[ind][i] = (poly[ind][i] + mul(poly[ind][i-1],num)) % mod;
    }
}

void poly_div(int ind, int num) {
    for(int i = 0; i<g[ind].size(); i++) {
        poly[ind][i+1] = (poly[ind][i+1] - mul(poly[ind][i],num) + mod) % mod;
    }
}

void dfs(int x, int p) {
    sz[x] = 1, in[x] = ++t;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i,x);
            sz[x] += sz[i];
            poly_mul(x,sz[i]);
            poly_mul(i,n-sz[i]);
        }
    }
    out[x] = ++t;
}

bool isAnc(int u, int v) {
    return (in[u] <= in[v] && out[u] >= out[v]);
}

int main() {
    cin >> n >> q;
    for(int i = 0, u, v; i<n-1; i++) {
        cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    for(int i = 0; i<n; i++) {
        poly[i][0] = 1;
    }
    dfs(0,0);
    fact[0] = ifact[0] = 1;
    for(int i = 1; i<=n; i++) {
        fact[i] = mul(i,fact[i-1]), ifact[i] = exp(fact[i],mod-2);
    }
    for(int i = 0, u, v, k; i<q; i++) {
        cin >> u >> v >> k;
        --u, --v;
        int rem_u = n - sz[u], rem_v = n - sz[v];
        for(int i: g[u]) {
            if(isAnc(u,v) && isAnc(i,v)) {
                rem_u = sz[i];
            }
        }
        for(int i: g[v]) {
            if(isAnc(v,u) && isAnc(i,u)) {
                rem_v = sz[i];
            }
        }
        poly_div(u,rem_u);
        poly_div(v,rem_v);
        int tot1 = 0, tot2 = 0;
        for(int i = 0; i<=k; i++) {
            tot1 = (tot1 + mul(poly[u][i],ifact[k-i])) % mod;
            tot2 = (tot2 + mul(poly[v][i],ifact[k-i])) % mod;
        }
        cout << mul(mul(fact[k],tot1),mul(fact[k],tot2)) << endl;
        poly_mul(u,rem_u);
        poly_mul(v,rem_v);
    }
}