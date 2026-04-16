#include <bits/stdc++.h>
using namespace std;

#define N 9

// Domain for each cell (81 cells)
vector<set<int>> domains(81);

// Row and column helpers
int row(int i) { return i / 9; }
int col(int i) { return i % 9; }

// Check if two cells are neighbors
bool isNeighbor(int i, int j) {
    if (i == j) return false;

    if (row(i) == row(j)) return true;
    if (col(i) == col(j)) return true;

    if ((row(i)/3 == row(j)/3) && (col(i)/3 == col(j)/3))
        return true;

    return false;
}

// Generate all arcs
queue<pair<int,int>> generateArcs() {
    queue<pair<int,int>> q;

    for (int i = 0; i < 81; i++) {
        for (int j = 0; j < 81; j++) {
            if (isNeighbor(i, j)) {
                q.push({i, j});
            }
        }
    }

    return q;
}

// Revise function
bool rev(int xi, int xj, int &removedCount) {
    bool revised = false;
    vector<int> toRemove;

    for (int val_i : domains[xi]) {
        bool satisfies = false;

        for (int val_j : domains[xj]) {
            if (val_i != val_j) {
                satisfies = true;
                break;
            }
        }

        if (!satisfies) {
            toRemove.push_back(val_i);
        }
    }

    for (int v : toRemove) {
        domains[xi].erase(v);
        removedCount++;
        revised = true;
    }

    return revised;
}

// AC-3 Algorithm
bool AC3(int &removedCount) {
    queue<pair<int,int>> q = generateArcs();

    while (!q.empty()) {
        auto arc = q.front();
        q.pop();

        int xi = arc.first;
        int xj = arc.second;

        if (rev(xi, xj, removedCount)) {

            if (domains[xi].empty())
                return false;

            // Add neighbors again
            for (int k = 0; k < 81; k++) {
                if (isNeighbor(k, xi) && k != xj) {
                    q.push({k, xi});
                }
            }
        }
    }
    return true;
}

// Print domain size grid
void printVisualization() {
    cout << "\nDomain Size Grid:\n";
    for (int i = 0; i < 81; i++) {
        cout << domains[i].size() << " ";
        if ((i + 1) % 9 == 0) cout << "\n";
    }
}

// Print partially solved Sudoku
void printSolution() {
    cout << "\nPartially Solved Grid:\n";
    for (int i = 0; i < 81; i++) {
        if (domains[i].size() == 1)
            cout << *domains[i].begin() << " ";
        else
            cout << "0 ";

        if ((i + 1) % 9 == 0) cout << "\n";
    }
}

int main() {

    // 2D ARRAY INPUT
    int grid[9][9] = {
        {0,0,0,0,0,6,0,0,0},
        {0,5,9,0,0,0,0,0,8},
        {2,0,0,0,8,0,0,0,0},

        {0,4,5,0,0,0,0,0,0},
        {0,0,3,0,0,0,0,0,0},
        {0,0,6,0,0,3,0,5,0},
        
        {0,0,0,0,7,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,5,0,0,0,2}
    };

    // Initialize domains
    for (int i = 0; i < 81; i++) {
        int r = i / 9;
        int c = i % 9;

        if (grid[r][c] == 0) {
            for (int v = 1; v <= 9; v++)
                domains[i].insert(v);
        } else {
            domains[i].insert(grid[r][c]);
        }
    }

    int removedCount = 0;

    bool result = AC3(removedCount);

    // Output results
    printVisualization();
    printSolution();

    cout << "\nTotal values removed: " << removedCount << endl;

    if (!result) {
        cout << "\nResult: Domain became EMPTY → UNSOLVABLE\n";
    } else {
        bool solved = true;

        for (auto &d : domains) {
            if (d.size() != 1) {
                solved = false;
                break;
            }
        }

        if (solved)
            cout << "\nResult: COMPLETELY solved by AC-3\n";
        else
            cout << "\nResult: AC-3 reduced domains but NOT fully solved\n";
    }

    return 0;
}