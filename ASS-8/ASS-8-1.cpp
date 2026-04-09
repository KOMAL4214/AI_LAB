#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const string cities = "ABCDEFGH";
const int dist[N][N] = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {12, 0, 35, 15, 20, 25, 30, 45},
    {25, 30, 0, 10, 40, 20, 15, 35},
    {18, 25, 12, 0, 15, 30, 20, 10},
    {22, 18, 28, 20, 0, 15, 25, 30},
    {35, 22, 18, 28, 12, 0, 40, 20},
    {30, 35, 22, 18, 28, 32, 0, 15},
    {40, 28, 35, 22, 18, 25, 12, 0}
};

int tourCost(vector<int>& tour) {
    int cost = 0;
    for (int i = 0; i < N - 1; i++)
        cost += dist[tour[i]][tour[i+1]];
    cost += dist[tour[N-1]][tour[0]];
    return cost;
}

vector<vector<int>> getNeighbors(vector<int> tour) {
    vector<vector<int>> neighbors;
    for (int i = 1; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            vector<int> newTour = tour;
            swap(newTour[i], newTour[j]);
            neighbors.push_back(newTour);
        }
    }
    return neighbors;
}

void localBeamSearch(int k) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<vector<int>> beam;

    for (int i = 0; i < k; i++) {
        vector<int> tour(N);
        iota(tour.begin(), tour.end(), 0);
        shuffle(tour.begin() + 1, tour.end(), rng);
        beam.push_back(tour);
    }

    int iterations = 0;
    vector<int> bestTour = beam[0];
    int bestCost = tourCost(bestTour);

    while (iterations < 1000) {
        vector<vector<int>> allNeighbors;

        for (auto& tour : beam) {
            auto neighbors = getNeighbors(tour);
            allNeighbors.insert(allNeighbors.end(), neighbors.begin(), neighbors.end());
        }

        sort(allNeighbors.begin(), allNeighbors.end(), [](auto& a, auto& b) {
            return tourCost(const_cast<vector<int>&>(a)) < tourCost(const_cast<vector<int>&>(b));
        });

        beam.clear();
        for (int i = 0; i < k && i < (int)allNeighbors.size(); i++) 
            beam.push_back(allNeighbors[i]);

        int currentBest = tourCost(beam[0]);
        if (currentBest < bestCost) {
            bestCost = currentBest;
            bestTour = beam[0]; 
        }

        iterations++;

        if (iterations > 50 && currentBest == bestCost) break;
    }

    cout << "Beam Width k=" << k << endl;
    cout << "Best Tour: ";
    for (int c : bestTour) cout << cities[c] << " ";
    cout << "-> " << cities[bestTour[0]] << endl;
    cout << "Best Cost: " << bestCost << endl;
    cout << "Iterations: " << iterations << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    cout << "===== Local Beam Search for TSP =====" << endl << endl;
    localBeamSearch(3);
    localBeamSearch(5);
    localBeamSearch(10);
    return 0;
}