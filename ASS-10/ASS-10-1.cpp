#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double dist2(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

vector<Point> readCSV(string filename) {
    vector<Point> cities;
    ifstream file(filename);
    string line;

    getline(file, line);

    while(getline(file, line)) {
        stringstream ss(line);
        string x, y;
        getline(ss, x, ',');
        getline(ss, y, ',');
        cities.push_back({stod(x), stod(y)});
    }
    return cities;
}

vector<vector<Point>> assignClusters(vector<Point>& cities, vector<Point>& centers) {
    vector<vector<Point>> clusters(3);

    for(auto &c : cities) {
        int best = 0;
        double bestDist = dist2(c, centers[0]);

        for(int i = 1; i < 3; i++) {
            double d = dist2(c, centers[i]);
            if(d < bestDist) {
                bestDist = d;
                best = i;
            }
        }
        clusters[best].push_back(c);
    }
    return clusters;
}

double computeCost(vector<vector<Point>>& clusters, vector<Point>& centers) {
    double cost = 0;
    for(int i = 0; i < 3; i++) {
        for(auto &c : clusters[i]) {
            cost += dist2(c, centers[i]);
        }
    }
    return cost;
}

void gradientDescent(vector<Point> cities) {
    cout << "\n--- Gradient Descent ---\n";

    vector<Point> centers = {cities[0], cities[1], cities[2]};
    double alpha = 0.01;

    for(int iter = 0; iter < 100; iter++) {
        auto clusters = assignClusters(cities, centers);

        for(int i = 0; i < 3; i++) {
            double dx = 0, dy = 0;

            for(auto &c : clusters[i]) {
                dx += (centers[i].x - c.x);
                dy += (centers[i].y - c.y);
            }

            centers[i].x -= alpha * 2 * dx;
            centers[i].y -= alpha * 2 * dy;
        }
    }

    auto clusters = assignClusters(cities, centers);
    double cost = computeCost(clusters, centers);

    cout << "Centers:\n";
    for(auto &c : centers)
        cout << c.x << " " << c.y << "\n";

    cout << "Total Cost: " << cost << "\n";
}

void newtonMethod(vector<Point> cities) {
    cout << "\n--- Newton Method ---\n";

    vector<Point> centers = {cities[0], cities[1], cities[2]};

    for(int iter = 0; iter < 20; iter++) {
        auto clusters = assignClusters(cities, centers);

        for(int i = 0; i < 3; i++) {
            if(clusters[i].empty()) continue;

            double sumx = 0, sumy = 0;

            for(auto &c : clusters[i]) {
                sumx += c.x;
                sumy += c.y;
            }

            centers[i].x = sumx / clusters[i].size();
            centers[i].y = sumy / clusters[i].size();
        }
    }

    auto clusters = assignClusters(cities, centers);
    double cost = computeCost(clusters, centers);

    cout << "Centers:\n";
    for(auto &c : centers)
        cout << c.x << " " << c.y << "\n";

    cout << "Total Cost: " << cost << "\n";
}

int main() {
    vector<Point> cities = readCSV("cities.csv");

    gradientDescent(cities);
    newtonMethod(cities);

    return 0;
}