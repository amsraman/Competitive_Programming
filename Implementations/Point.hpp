struct Point {
    int x_val, y_val;
    Point operator+(Point & P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point & P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    bool operator<(const Point & P) {
        return tie(x_val, y_val) < tie(P.x_val, P.y_val);
    }
    bool operator==(const Point & P) {
        return tie(x_val, y_val) == tie(P.x_val, P.y_val);
    }
    ll inner(const Point & P) {
        return 1LL * x_val * P.x_val + 1LL * y_val * P.y_val;
    }
    long double norm() {
        return sqrt((long double) inner(*this));
    }
    ll cross(const Point & P) {
        return 1LL * x_val * P.y_val - 1LL * y_val * P.x_val;
    }
    int turn(const Point & P) {
        if(1LL * x_val * P.y_val > 1LL * y_val * P.x_val) {
            return 1;
        } else if(1LL * x_val * P.y_val == 1LL * y_val * P.x_val) {
            return 0;
        }
        return -1;
    }
};