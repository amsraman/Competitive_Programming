#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

pair<long long, long long> extended_euclidean(long long x, long long y) { // find {a, b} st ax + by = gcd(x, y)
    long long a0 = 1, b0 = 0, c0 = x, a1 = 0, b1 = 1, c1 = y;
    while(c1) {
        tie(a0, a1) = make_pair(a1, a0 - c0 / c1 * a1);
        tie(b0, b1) = make_pair(b1, b0 - c0 / c1 * b1);
        tie(c0, c1) = make_pair(c1, c0 % c1);
    }
    return make_pair(a0, b0);
}

long long inv_mod(long long x, long long m) {
	assert(__gcd(x, m) == 1);
	auto [a, b] = extended_euclidean(x, m);
	return (a % m + m) % m;
}

optional<pair<long long, long long>> chinese_remainder_theorem(vector<pair<long long, long long>> eq) {
	long long r1 = 0, r2 = 1;
	for(auto [k, m]: eq) {
		long long df = ((k - r1) % m + m) % m, g1 = __gcd(r2, m), g2 = __gcd(g1, df);
		if(g1 != g2) return nullopt;
		r1 += (inv_mod((r2 / g1) % (m / g1), m / g1) * (df / g1) % (m / g1)) * r2;
		r2 = r2 * m / g1;
	}
	return make_pair(r1, r2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int n, nx, ny, nz; cin >> n >> nx >> ny >> nz;
	using triple = tuple<ll, ll, ll>;
	vector<tuple<ll, triple, triple>> planets;
	vector<bool> dead(n, false);
    map<pair<ll, triple>, set<int>> events;
	ll cur_t = 0;
	for(int i = 0, m, x, y, z, vx, vy, vz; i < n; i++) {
		cin >> m >> x >> y >> z >> vx >> vy >> vz;
		planets.emplace_back(m, make_tuple(x, y, z), make_tuple(vx, vy, vz));
	}
    auto mv = [&](tuple<ll, ll, ll> pos, tuple<ll, ll, ll> vel, ll tm) -> triple {
        auto [x, y, z] = pos;
        auto [vx, vy, vz] = vel;
        x = (x + vx * tm) % nx;
        y = (y + vy * tm) % ny;
        z = (z + vz * tm) % nz;
        if(x < 0) x += nx;
        if(y < 0) y += ny;
        if(z < 0) z += nz;
        return make_tuple(x, y, z);
    };
	auto solve = [](ll x, ll y, ll m) -> optional<pair<ll, ll>> { // solves kx = y mod m
		x = (x % m + m) % m;
		y = (y % m + m) % m;
		ll g = abs(__gcd(__gcd(x, y), m));
		x /= g, y /= g, m /= g;
		if(__gcd(x, m) != 1) return nullopt;
		ll i = inv_mod(x, m);
		return make_pair((i * y) % m, m);
	};
	auto get_intersection = [&](int x, int y) -> optional<pair<ll, ll>> { // returns time at which planets x and y touch
		auto [m1, pos1, vel1] = planets[x];
		auto [x1, y1, z1] = pos1;
		auto [vx1, vy1, vz1] = vel1;
		auto [m2, pos2, vel2] = planets[y];
		auto [x2, y2, z2] = pos2;
		auto [vx2, vy2, vz2] = vel2;
		auto r1 = solve(vx1 - vx2, x2 - x1, nx);
		auto r2 = solve(vy1 - vy2, y2 - y1, ny);
		auto r3 = solve(vz1 - vz2, z2 - z1, nz);
		if(!r1 || !r2 || !r3) return nullopt;
		return chinese_remainder_theorem({r1.value(), r2.value(), r3.value()});
	};
	priority_queue<pair<ll, triple>, vector<pair<ll, triple>>, greater<pair<ll, triple>>> q; // time it happens, who's merging
	for(int i = 0; i < n; i++) {
        auto [pmass, ppos, pvel] = planets[i];
		for(int j = i + 1; j < n; j++) {
			auto res = get_intersection(i, j);
			if(res) {
				auto [k, m] = res.value();
                pair<ll, triple> entry = make_pair(k, mv(ppos, pvel, k));
                if(!events.count(entry)) {
                    q.push(entry);
                }
                events[entry].insert(i); events[entry].insert(j);
			}
		}
	}
	while(!q.empty()) {
		auto [tm, pos] = q.top(); q.pop();
        int ct = 0;
        for(int ind: events[{tm, pos}]) {
            ct += (int) !dead[ind];
        }
        if(ct <= 1) continue;
		// merge
        ll new_mass = 0, new_vx = 0, new_vy = 0, new_vz = 0;
        for(int ind: events[{tm, pos}]) {
            if(dead[ind]) continue;
            auto [pmass, ppos, pvel] = planets[ind];
            auto [vx, vy, vz] = pvel;
            new_vx += vx, new_vy += vy, new_vz += vz, new_mass += pmass;
            dead[ind] = true;
        }
		cur_t = tm;
		tuple<ll, ll, ll> new_v = make_tuple(new_vx / ct, new_vy / ct, new_vz / ct);
		planets.emplace_back(new_mass, mv(pos, new_v, -tm), new_v); dead.push_back(false);
        for(int i = 0; i < (int) planets.size() - 1; i++) {
            if(dead[i]) continue;
            auto res = get_intersection((int) planets.size() - 1, i);
            if(res) {
                auto [k, m] = res.value();
                ll tm = (cur_t - k + m - 1) / m * m + k;
                auto [pmass, ppos, pvel] = planets[i];
                pair<ll, triple> entry = make_pair(tm, mv(ppos, pvel, tm));
                if(!events.count(entry)) {
                    q.push(entry);
                }
                events[entry].insert(i); events[entry].insert((int) planets.size() - 1);
            }
        }
	}
	vector<tuple<ll, ll, ll, ll, ll, ll, ll>> res;
	for(int i = 0; i < (int) planets.size(); i++) {
		if(!dead[i]) {
			auto [m, pos, vel] = planets[i];
			auto [x, y, z] = mv(pos, vel, cur_t);
			auto [vx, vy, vz] = vel;
			res.emplace_back(-m, x, y, z, vx, vy, vz);
		}
	}
	sort(res.begin(), res.end());
	cout << res.size() << '\n';
	for(int i = 0; i < (int) res.size(); i++) {
        auto [m, x, y, z, vx, vy, vz] = res[i];
		cout << "P" << i << ": " << -m << " " << x << " " << y << " " << z << " " << vx << " " << vy << " " << vz << '\n';
	}
}