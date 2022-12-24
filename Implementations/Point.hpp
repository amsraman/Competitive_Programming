template <typename T>
struct Point {
    T x_val, y_val;
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
    T inner(const Point & P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    T norm() {
        return inner(*this);
    }
    long double abs() {
        return sqrt(inner(*this));
    }
    T cross(const Point & P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point & P) { // 1 means ccw
        if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        } else if(x_val * P.y_val == y_val * P.x_val) {
            return 0;
        }
        return -1;
    }
};