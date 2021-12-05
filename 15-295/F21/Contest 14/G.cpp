#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

int n, len[20], x, y;
pair<ld, ld> vec[20];

ld dist(pair<ld, ld> p1, pair<ld, ld> p2) {
    return sqrt((p1.f - p2.f) * (p1.f - p2.f) + (p1.s - p2.s) * (p1.s - p2.s));
}

pair<ld, ld> rot(pair<ld, ld> vec, ld ang_cos, ld ang_sin) {
    return {vec.f * ang_cos - vec.s * ang_sin, vec.f * ang_sin + vec.s * ang_cos};
}

int main() {
    cin >> n;
    ld tot_len = 0;
    for(int i = 0; i < n; i++) {
        cin >> len[i];
        tot_len += len[i];
    }
    cin >> x >> y;
    vector<pair<ld, int>> lens;
    for(int i = 0; i < n; i++) {
        lens.push_back({len[i], i});
    }
    sort(lens.begin(), lens.end());
    // Cycle Case
    int start_ind = 0;
    pair<ld, ld> starting_point = {0, 0};
    if(x == 0 && y == 0) {
        starting_point.s = lens[0].f;
        vec[lens[0].s] = starting_point;
        tot_len -= lens[0].f;
        ++start_ind;
    }
    ld tot_dist = dist(starting_point, {x, y});
    pair<ld, ld> cur = starting_point, unit_vec = {(ld) (x - starting_point.f) / tot_dist, (ld) (y - starting_point.s) / tot_dist};
    for(int i = start_ind; i < n; i++) {
        tot_len -= lens[i].f;
        if(tot_len == 0) {
            // Not much we can do, just move towards the point
            vec[lens[i].s] = {lens[i].f * unit_vec.f, lens[i].f * unit_vec.s};
            break;
        }
        ld dist_left = dist(cur, {x, y});
        if(tot_len + lens[i].f <= dist_left) {
            vec[lens[i].s] = {lens[i].f * unit_vec.f, lens[i].f * unit_vec.s};
        } else if(tot_len >= dist_left + lens[i].f) {
            vec[lens[i].s] = {-lens[i].f * unit_vec.f, -lens[i].f * unit_vec.s};
        } else {
            // Law of Cosines: a = lens[i].f, b = dist_left, c = tot_len
            ld cos_ang = ((ld) lens[i].f * lens[i].f + dist_left * dist_left - tot_len * tot_len) / (2.0 * lens[i].f * dist_left);
            pair<ld, ld> rot_vec = rot(unit_vec, cos_ang, sqrt(1.0 - cos_ang * cos_ang));
            vec[lens[i].s] = {rot_vec.f * lens[i].f, rot_vec.s * lens[i].f};
            cur = {cur.f + vec[lens[i].s].f, cur.s + vec[lens[i].s].s};
            // Line up the remaining points along the connecting vector
            pair<ld, ld> con_vec = {x - cur.f, y - cur.s};
            ld norm = dist(con_vec, {0, 0});
            con_vec = {con_vec.f / norm, con_vec.s / norm};
            for(int j = i + 1; j < n; j++) {
                vec[lens[j].s] = {con_vec.f * lens[j].f, con_vec.s * lens[j].f};
            }
            break;
        }
        cur = {cur.f + vec[lens[i].s].f, cur.s + vec[lens[i].s].s};
    }
    cur = {0, 0};
    for(int i = 0; i < n; i++) {
        cur.f += vec[i].f, cur.s += vec[i].s;
        cout << fixed << setprecision(8) << cur.f << " " << cur.s << endl;
    }
}