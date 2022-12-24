template <typename T>
vector<Point<T>> ConvexHull(vector<Point<T>> points) {
    if(points.size() <= 1) {
        return points;
    }
    sort(points.begin(), points.end());
    vector<Point<double>> hull(points.size() + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(points.begin(), points.end())) {
        for(Point p: points) {
            while(t >= s + 2 && (hull[t - 1] - hull[t - 2]).turn(p - hull[t - 2]) <= 0) {
                t--;
            }
            hull[t++] = p;
        }
    }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}