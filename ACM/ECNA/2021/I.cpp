#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

const ld epsilon = 1e-4;

struct Point {
    ld x_val, y_val;
    bool operator==(const Point &P) const {
        return (x_val == P.x_val && y_val == P.y_val);
    }
    bool operator<(const Point &P) const {
        return (x_val < P.x_val || x_val == P.x_val && y_val < P.y_val);
    }
    Point operator+(Point &P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point &P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    double norm() {
        return sqrt(x_val * x_val + y_val * y_val);
    }
    ld inner(const Point &P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    ld cross(const Point &P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point &P) {
        if(abs(x_val * P.y_val - y_val * P.x_val) < epsilon) {
            return 0;
        } else if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        }
        return -1;
    }
} student;

struct LineSegment {
    Point P1, P2;
    bool intersects(LineSegment &L) {
        bool s1 = (L.P1 - P1).turn(P2 - L.P1) != (L.P2 - P1).turn(P2 - L.P2);
        bool s2 = (P1 - L.P1).turn(L.P2 - P1) != (P2 - L.P1).turn(L.P2 - P2);
        if((L.P1 - P1).turn(P2 - L.P1) == 0 && (P1 - L.P1).turn(L.P2 - P1) == 0) {
            int x11 = min(P1.x_val,P2.x_val), y11 = min(P1.y_val,P2.y_val);
            int x12 = max(P1.x_val,P2.x_val), y12 = max(P1.y_val,P2.y_val);
            int x21 = min(L.P1.x_val,L.P2.x_val), y21 = min(L.P1.y_val,L.P2.y_val);
            int x22 = max(L.P1.x_val,L.P2.x_val), y22 = max(L.P1.y_val,L.P2.y_val);
            s1 &= (x12 >= x21 && x22 >= x11 && y12 >= y21 && y22 >= y11);
        }
        return s1 && s2;
    }
    Point point_of_intersection(LineSegment &L) {
        if(P1 == L.P1 || P1 == L.P2) {
            return P1;
        } else if(P2 == L.P1 || P2 == L.P2) {
            return P2;
        }
        Point dir = P2 - P1, ortho = {-dir.y_val, dir.x_val};
        ld t = (L.P2 - L.P1).cross(P1 - L.P1) / (L.P2 - L.P1).inner(ortho);
        return {P1.x_val + t * dir.x_val, P1.y_val + t * dir.y_val};
    }
} walkways[500], fellow;

int n, node_count;
ld student_speed, fellow_speed, dist[250000], ans = 1e5;
map<Point,int> point_ind;
vector<pair<ld,int>> g[250000];
bool vis[250000];
set<pair<Point,int>> intermediate_points[500];
vector<LineSegment> edge_list;

void insert_point(Point p) {
    if(!point_ind.count(p)) {
        point_ind[p] = node_count++;
    }
}

int main() {
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> walkways[i].P1.x_val >> walkways[i].P1.y_val >> walkways[i].P2.x_val >> walkways[i].P2.y_val;
        insert_point(walkways[i].P1);
        insert_point(walkways[i].P2);
    }
    cin >> student.x_val >> student.y_val >> student_speed;
    cin >> fellow.P1.x_val >> fellow.P1.y_val >> fellow.P2.x_val >> fellow.P2.y_val >> fellow_speed;
    insert_point(student);
    for(int i = 0; i<n; i++) {
        intermediate_points[i].insert({walkways[i].P1,point_ind[walkways[i].P1]});
        intermediate_points[i].insert({walkways[i].P2,point_ind[walkways[i].P2]});
        if((student - walkways[i].P1).turn(walkways[i].P2 - student) == 0) {
            ld lb_x = min(walkways[i].P1.x_val,walkways[i].P2.x_val);
            ld lb_y = min(walkways[i].P1.y_val,walkways[i].P2.y_val);
            ld ub_x = max(walkways[i].P1.x_val,walkways[i].P2.x_val);
            ld ub_y = max(walkways[i].P1.y_val,walkways[i].P2.y_val);
            if(student.x_val >= lb_x && student.x_val <= ub_x && student.y_val >= lb_y && student.y_val <= ub_y) {
                intermediate_points[i].insert({student,point_ind[student]});
            }
        }
        for(int j = i+1; j<n; j++) {
            if(walkways[i].intersects(walkways[j])) {
                Point intersection = walkways[i].point_of_intersection(walkways[j]);
                insert_point(intersection);
                intermediate_points[i].insert({intersection,point_ind[intersection]});
                intermediate_points[j].insert({intersection,point_ind[intersection]});
            }
        }
    }
    for(int i = 0; i<n; i++) {
        auto it1 = intermediate_points[i].begin(), it2 = ++intermediate_points[i].begin();
        while(it2 != intermediate_points[i].end()) {
            Point P1 = it1->f, P2 = it2->f;
            g[it1->s].push_back({(P1 - P2).norm(),it2->s});
            g[it2->s].push_back({(P1 - P2).norm(),it1->s});
            edge_list.push_back({P1,P2});
            ++it1, ++it2;
        }
    }
    // Dijkstra
    priority_queue<pair<ld,int>> pq;
    fill(dist,dist+node_count,1e14);
    dist[point_ind[student]] = 0;
    pq.push({0,point_ind[student]});
    while(!pq.empty()) {
        int cur_node = pq.top().s;
        pq.pop();
        if(vis[cur_node]) {
            continue;
        }
        vis[cur_node] = true;
        for(pair<ld,int> i: g[cur_node]) {
            if(dist[cur_node] + i.f < dist[i.s]) {
                dist[i.s] = dist[cur_node] + i.f;
                pq.push({-dist[i.s],i.s});
            }
        }
    }
    for(LineSegment L: edge_list) {
        if(fellow.intersects(L)) {
            Point intersection = fellow.point_of_intersection(L);
            ld min_dist = min(dist[point_ind[L.P1]] + (intersection - L.P1).norm(),dist[point_ind[L.P2]] + (intersection - L.P2).norm());
            if(min_dist / student_speed <= (fellow.P1 - intersection).norm() / fellow_speed + epsilon) {
                ans = min(ans,(fellow.P1 - intersection).norm() / fellow_speed);
            } 
        }
    }
    if(ans == 1e5) {
        cout << "Impossible" << endl;
    } else {
        cout << fixed << setprecision(9) << ans << endl;
    }
}