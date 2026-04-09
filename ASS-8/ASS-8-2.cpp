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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int tourCost(vector<int>& tour) {
    int cost = 0;
    for (int i = 0; i < N - 1; i++)
        cost += dist[tour[i]][tour[i+1]];
    cost += dist[tour[N-1]][tour[0]];
    return cost;
}

vector<int> crossoverOne(vector<int>& p1, vector<int>& p2) {
    int point = 1 + rng() % (N - 2);
    vector<int> child(N, -1);

    for (int i = 0; i <= point; i++)
        child[i] = p1[i];

    int pos = point + 1;
    for (int i = 0; i < N; i++) {
        int city = p2[i];
        if (find(child.begin(), child.end(), city) == child.end()) {
            child[pos % N] = city;
            pos++;
        }
    }
    return child;
}

vector<int> crossoverTwo(vector<int>& p1, vector<int>& p2) {
    int p1x = 1 + rng() % (N - 2);
    int p2x = 1 + rng() % (N - 2);
    if (p1x > p2x) swap(p1x, p2x);

    vector<int> child(N, -1);

    for (int i = p1x; i <= p2x; i++)
        child[i] = p1[i];

    int pos = (p2x + 1) % N;
    for (int i = 0; i < N; i++) {
        int city = p2[(p2x + 1 + i) % N];
        if (find(child.begin(), child.end(), city) == child.end()) {
            child[pos] = city;
            pos = (pos + 1) % N;
        }
    }
    return child;
}

void mutate(vector<int>& tour) {
    int i = 1 + rng() % (N - 1);
    int j = 1 + rng() % (N - 1);
    swap(tour[i], tour[j]);
}

vector<int> tournamentSelect(vector<vector<int>>& pop) {
    int a = rng() % pop.size();
    int b = rng() % pop.size();
    return tourCost(pop[a]) < tourCost(pop[b]) ? pop[a] : pop[b];
}

void geneticAlgorithm(int crossoverPoints) {
    const int POP_SIZE = 50;
    const int GENERATIONS = 500;
    const double MUTATION_RATE = 0.1;

    vector<vector<int>> population;
    for (int i = 0; i < POP_SIZE; i++) {
        vector<int> tour(N);
        iota(tour.begin(), tour.end(), 0);
        shuffle(tour.begin() + 1, tour.end(), rng);
        population.push_back(tour);
    }

    vector<int> bestTour = population[0];
    int bestCost = tourCost(bestTour);
    int convergenceGen = 0;

    for (int gen = 0; gen < GENERATIONS; gen++) {
        vector<vector<int>> newPop;

        while ((int)newPop.size() < POP_SIZE) {
            vector<int> parent1 = tournamentSelect(population);
            vector<int> parent2 = tournamentSelect(population);

            vector<int> child;
            if (crossoverPoints == 1)
                child = crossoverOne(parent1, parent2);
            else
                child = crossoverTwo(parent1, parent2);

            if ((double)(rng() % 100) / 100.0 < MUTATION_RATE)
                mutate(child);

            newPop.push_back(child);
        }

        population = newPop;

        for (auto& tour : population) {
            int cost = tourCost(tour);
            if (cost < bestCost) {
                bestCost = cost;
                bestTour = tour;
                convergenceGen = gen;
            }
        }
    }

    cout << "Crossover Points: " << crossoverPoints << endl;
    cout << "Best Tour: ";
    for (int c : bestTour) cout << cities[c] << " ";
    cout << "-> " << cities[bestTour[0]] << endl;
    cout << "Best Cost: " << bestCost << endl;
    cout << "Converged at Generation: " << convergenceGen << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    cout << "===== Genetic Algorithm for TSP =====" << endl << endl;
    geneticAlgorithm(1);
    geneticAlgorithm(2);
    return 0;
}