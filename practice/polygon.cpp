#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

double calDistance(Point p1, Point p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void calPointByDistance(Point p1, Point p2, double needDistance, double lineDistance, Point& res) {
    res.x = needDistance / lineDistance * (p1.x - p2.x) + p2.x;
    res.y = needDistance / lineDistance * (p1.y - p2.y) + p2.y;
    return;
}

int main() {
    vector<Point> points = {{0,0}, {1,0}, {1,1}, {0,1}}; 
    double totalDistance = 0;
    vector<double> lineDistance;
    for (int i = 1; i < points.size(); i++) {
       double tmp = calDistance(points[i], points[i-1]);
       lineDistance.emplace_back(tmp);
       totalDistance += tmp;
    }
    double tmp = calDistance(points[points.size()-1], points[0]);
    lineDistance.emplace_back(tmp);
    totalDistance += tmp;
    
    int n = 3;
    double avgDistance = totalDistance / n;
    double needDistance = avgDistance;
    vector<Point> res;
    int i, j;
    for (i = 0, j = 0; i < n && j < lineDistance.size(); ) {
        if (needDistance > lineDistance[j]) {
            needDistance -= lineDistance[j];
            j++;
        }else {
            res.emplace_back(Point{0,0});
            if (j == lineDistance.size() - 1) {
                calPointByDistance(points[j], points[0], needDistance, lineDistance[j], res.back());
            }else {
                calPointByDistance(points[j+1], points[j], needDistance, lineDistance[j], res.back());
            }
            needDistance = avgDistance;
            i++;
        }
    }
    for (auto point : res) {
        cout << "(" << point.x << "," << point.y << ")" << endl;
    } 
    return 0;
}
