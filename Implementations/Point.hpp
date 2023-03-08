template <typename T>
struct Point {
    T x, y;
    Point operator+(Point & P) {return {x + P.x, y + P.y};}
    Point operator-(Point & P) {return {x - P.x, y - P.y};}
    bool operator<(const Point & P) {return tie(x, y) < tie(P.x, P.y);}
    bool operator==(const Point & P) {return tie(x, y) == tie(P.x, P.y);} 
    T inner(const Point & P) {return x * P.x + y * P.y;}
    T norm() {return inner(*this);}
    long double abs() {return sqrt(inner(*this));}
    T cross(const Point & P) {return x * P.y - y * P.x;}
    int turn(const Point & P) { // 1 means ccw
        if(x * P.y > y * P.x) {
            return 1;
        } else if(x * P.y == y * P.x) {
            return 0;
        }
        return -1;
    }
};