#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct Point3D {
    T x, y, z;
    Point3D operator+(Point3D & P) {return {x + P.x, y + P.y, z + P.z};}
    Point3D operator-(Point3D & P) {return {x - P.x, y - P.y, z - P.z};}
    Point3D operator*(T c) {return {x * c, y * c, z * c};}
    Point3D operator/(T c) {return {x / c, y / c, z / c};}
    bool operator<(const Point3D & P) const {return tie(x, y, z) < tie(P.x, P.y, P.z);}
    bool operator==(const Point3D & P) const {return tie(x, y, z) == tie(P.x, P.y, P.z);}
    bool operator!=(const Point3D & P) const {return tie(x, y, z) != tie(P.x, P.y, P.z);} 
    T inner(const Point3D & P) const {return x * P.x + y * P.y + z * P.z;}
    T norm() {return inner(*this);}
    long double abs() {return sqrt(inner(*this));}
    Point3D cross(const Point3D & P) {return {y * P.z - P.y * z, P.x * z - x * P.z, x * P.y - y * P.x};}
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Point3D P) {
        return out << "(" << P.x << ", " << P.y << ", " << P.z << ")";
    }
};

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    int n, m = 0;
    T_f f_inf = numeric_limits<T_f>::max();
    T_c c_inf = numeric_limits<T_c>::max();
    vector<pair<int, int>> path;
    vector<T_c> dist;
    vector<vector<pair<int, int>>> graph;
    vector<T_f> init_capacity, edge_capacity;
    vector<T_c> costs;
    CostFlowNetwork(int n): n(n), path(n), dist(n), graph(n) {};
    void add_edge(int ind1, int ind2, T_f capacity, T_c cost) {
        int front_edge = m++, back_edge = m++;
        graph[ind1].push_back({ind2, front_edge});
        graph[ind2].push_back({ind1, back_edge});
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
    }
    bool spfa(int source, int sink) {
        fill(dist.begin(), dist.end(), c_inf); dist[source] = 0;
        vector<bool> in_queue(n, false);
        queue<int> q; q.push(source); in_queue[source] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;
            for(pair<int, int> e: graph[u]) {
                if(edge_capacity[e.second] > 0 && dist[u] < c_inf && dist[u] + costs[e.second] < dist[e.first]) {
                    dist[e.first] = dist[u] + costs[e.second];
                    path[e.first] = {u, e.second};
                    if(!in_queue[e.first]) {
                        in_queue[e.first] = true;
                        q.push(e.first);
                    }
                }
            }
        }
        return dist[sink] < c_inf;
    }
    pair<T_f, T_c> min_cost_max_flow(int source, int sink) {
        T_f flow = 0; T_c cost = 0;
        for(int i = 0; i < m; i++) {
            edge_capacity[i] = init_capacity[i];
        }
        while(spfa(source, sink)) {
            T_f aug_path = f_inf;
            int cur_vertex = sink;
            while(cur_vertex != source) {
                aug_path = min(aug_path, edge_capacity[path[cur_vertex].second]);
                cur_vertex = path[cur_vertex].first;
            }
            cur_vertex = sink;
            while(cur_vertex != source) {
                edge_capacity[path[cur_vertex].second] -= aug_path;
                edge_capacity[path[cur_vertex].second ^ 1] += aug_path;
                cur_vertex = path[cur_vertex].first;
            }
            flow += aug_path, cost += dist[sink] * aug_path;
        }
        return {flow, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<Point3D<ll>> pl(n), dir(n);
    for(int i = 0; i < n; i++) {
        cin >> pl[i].x >> pl[i].y >> pl[i].z >> dir[i].x >> dir[i].y >> dir[i].z;
        int g = abs(__gcd(__gcd(dir[i].x, dir[i].y), dir[i].z));
        dir[i] = dir[i] / g;
    }
    bool collinear = true;
    Point3D<ll> zer = {0, 0, 0};
    for(int i = 2; i < n; i++) {
        if((pl[i] - pl[i - 1]).cross(pl[i - 1] - pl[i - 2]) != zer) {
            collinear = false;
        }
    }
    if(n == 1) {
        cout << "-1\n";
    } else if(n % 2 == 0 || !collinear) {
        CostFlowNetwork<int, int> cfn(2 * n + 2);
        for(int i = 0; i < n; i++) {
            map<Point3D<ll>, int> see;
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                auto dif = pl[j] - pl[i];
                int g = abs(__gcd(__gcd(dif.x, dif.y), dif.z));
                dif = dif / g;
                if(see.count(dif)) {
                    if((pl[see[dif]] - pl[i]).abs() > (pl[j] - pl[i]).abs()) {
                        see[dif] = j;
                    }
                } else {
                    see[dif] = j;
                }
            }
            for(auto [key, val]: see) {
                if(key == dir[i]) {
                    cfn.add_edge(i + 1, val + n + 1, 1, 0);
                } else {
                    cfn.add_edge(i + 1, val + n + 1, 1, 1);
                }
            }
        }
        for(int i = 0; i < n; i++) {
            cfn.add_edge(0, i + 1, 1, 0);
            cfn.add_edge(i + n + 1, 2 * n + 1, 1, 0);
        }
        auto [flow, cost] = cfn.min_cost_max_flow(0, 2 * n + 1);
        assert(flow == n);
        cout << cost << '\n';
    } else {
        vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x, int y) {
            return pl[x] < pl[y];
        });
        Point3D<ll> ray = pl[ord[n - 1]] - pl[ord[0]];
        int g = abs(__gcd(__gcd(ray.x, ray.y), ray.z));
        ray = ray / g;
        vector<int> ar(n, 0);
        for(int i = 0; i < n; i++) {
            if(dir[i] == ray) {
                ar[i] = 1;
            } else if(dir[i] == ray * -1) {
                ar[i] = -1;
            }
        }
        auto ray_line_intersect = [&zer](Point3D<ll> a1, Point3D<ll> b1, Point3D<ll> a2, Point3D<ll> b2) {
            auto v1 = b1.cross(b2);
            auto v2 = (a2 - a1).cross(b2);
            if(v1 == zer) {
                if(v2 != zer) return false;
                return (a2 - a1).inner(b1) >= 0 || (a1 - a2).inner(b2) >= 0;
            }
            if(v1.cross(v2) != zer) return false;
            return v1.inner(v2) >= 0;
        };
        auto ray_ray_intersect = [&](Point3D<ll> a1, Point3D<ll> b1, Point3D<ll> a2, Point3D<ll> b2) {
            return ray_line_intersect(a1, b1, a2, b2) && ray_line_intersect(a2, b2, a1, b1);
        };
        int res = 1e9;
        for(int i = 0; i < n; i++) {
            vector<int> pf(1, 0), sf(1, 0);
            auto ord_rem = ord[i]; ord.erase(ord.begin() + i);
            for(int j = 0; j < n - 1; j++) {
                int w1 = (j % 2 == 0 ? 1 : -1);
                int w2 = (j % 2 == 0 ? -1 : 1);
                pf.push_back(pf.back() + (ar[ord[j]] != w1));
                sf.push_back(sf.back() + (ar[ord[n - j - 2]] != w2));
            }
            reverse(sf.begin(), sf.end());
            for(int j = 0; j < n - 1; j++) {
                if(j % 2 == 0) {
                    int tot = 0;
                    for(int k = j; k < n - 1; k++) {
                        if(k % 2 != j % 2) {
                            int cycle_cost = pf[j] + sf[k + 1] + tot;
                            cycle_cost += (ar[ord_rem] != 0 || ar[ord[k]] != 0 || !ray_ray_intersect(pl[ord[j]], dir[ord_rem] * -1, pl[ord[k]], dir[ord[k]]));
                            cycle_cost += (ar[ord_rem] != 0 && ar[ord[k]] != 0);
                            res = min(res, cycle_cost);
                        }
                        tot += ar[ord[k]] != 1;
                    }
                } else {
                    int tot = 0;
                    for(int k = j; k >= 0; k--) {
                        if(k % 2 != j % 2) {
                            int cycle_cost = pf[k] + sf[j + 1] + tot;
                            cycle_cost += (ar[ord_rem] != 0 || ar[ord[k]] != 0 || !ray_ray_intersect(pl[ord[j]], dir[ord_rem] * -1, pl[ord[k]], dir[ord[k]]));
                            cycle_cost += (ar[ord_rem] != 0 && ar[ord[k]] != 0);
                            res = min(res, cycle_cost);
                        }
                        tot += ar[ord[k]] != -1;
                    }
                }
            }
            ord.insert(ord.begin() + i, ord_rem);
        }
        cout << 1000 + res << '\n';
    }
}