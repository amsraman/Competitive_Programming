template <typename T_c, typename T_w>
struct FenwickTree2D {
    // Offline version
    vector<T_c> x_coords;
    vector<vector<T_c>> y_coords;
    vector<vector<T_w>> bit;

    FenwickTree2D(vector<pair<int, int>> & points) {
        sort(points.begin(), points.end());
        for(pair<int, int> p: points) {
            x_coords.push_back(p.first);
        }
        x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());
        y_coords.resize(x_coords.size()), bit.resize(x_coords.size());
        for(int i = 0, j = 0; i < points.size(); i++) {
            for(int pos = j + 1; pos <= x_coords.size(); pos += pos & -pos) {
                y_coords[pos - 1].push_back(points[i].second);
            }
            if(i + 1 < points.size() && points[i].first != points[i + 1].first) {
                ++j;
            }
        }
        for(int i = 0; i < x_coords.size(); i++) {
            sort(y_coords[i].begin(), y_coords[i].end());
            y_coords[i].erase(unique(y_coords[i].begin(), y_coords[i].end()), y_coords[i].end());
            bit[i].resize(y_coords[i].size(), 0LL);
        }
    }

    int x_rank(T_c x) {
        return lower_bound(x_coords.begin(), x_coords.end(), x) - x_coords.begin();
    }

    int y_rank(int ind, T_c y) {
        return lower_bound(y_coords[ind].begin(), y_coords[ind].end(), y) - y_coords[ind].begin();
    }

    T_w qry(T_c x, T_c y) {
        T_w ret = 0;
        for(int x_pos = x_rank(x); x_pos > 0; x_pos -= x_pos & -x_pos) {
            for(int y_pos = y_rank(x_pos - 1, y); y_pos > 0; y_pos -= y_pos & -y_pos) {
                ret += bit[x_pos - 1][y_pos - 1];
            }
        }
        return ret;
    }

    T_w qry(T_c x_lo, T_c x_hi, T_c y_lo, T_c y_hi) {
        return qry(x_hi, y_hi) - qry(x_hi, y_lo) - qry(x_lo, y_hi) + qry(x_lo, y_lo);
    }

    void upd(T_c x, T_c y, T_w delta) {
        for(int x_pos = x_rank(x) + 1; x_pos <= x_coords.size(); x_pos += x_pos & -x_pos) {
            for(int y_pos = y_rank(x_pos - 1, y) + 1; y_pos <= y_coords[x_pos - 1].size(); y_pos += y_pos & -y_pos) {
                bit[x_pos - 1][y_pos - 1] += delta;
            }
        }
    }
};