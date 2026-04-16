#include <bits/stdc++.h>
using namespace std;

// Domains of variables
map<string, set<string>> domain;

// Constraints (Adjacency list)
map<string, vector<string>> constraints;

// Function to print domains
void printDomains() {
    cout << "\nCurrent Domains:\n";
    for (auto &d : domain) {
        cout << d.first << " = { ";
        for (auto &val : d.second)
            cout << val << " ";
        cout << "}\n";
    }
    cout << endl;
}

// Revise function
bool revise(string Xi, string Xj) {
    bool revised = false;
    set<string> toRemove;

    for (auto x : domain[Xi]) {
        bool satisfies = false;

        for (auto y : domain[Xj]) {
            if (x != y) { // constraint: Xi != Xj
                satisfies = true;
                break;
            }
        }

        if (!satisfies) {
            toRemove.insert(x);
            revised = true;
        }
    }

    for (auto val : toRemove)
        domain[Xi].erase(val);

    if (revised) {
        cout << "Revised " << Xi << " after checking with " << Xj << endl;
    }

    return revised;
}

// AC-3 Algorithm
bool AC3() {
    queue<pair<string, string>> q;

    // Add all arcs
    for (auto &c : constraints) {
        for (auto &neighbor : c.second) {
            q.push({c.first, neighbor});
        }
    }

    int step = 1;

    while (!q.empty()) {
        auto arc = q.front();
        q.pop();

        cout << "Step " << step++ << ": Arc (" 
             << arc.first << ", " << arc.second << ") -> ";

        bool changed = revise(arc.first, arc.second);

        if (changed) {
            cout << "Revised\n";
            printDomains();

            if (domain[arc.first].empty()) {
                cout << "Failure: Domain wiped out!\n";
                return false;
            }

            // Add neighbors back
            for (auto &neighbor : constraints[arc.first]) {
                if (neighbor != arc.second) {
                    q.push({neighbor, arc.first});
                }
            }
        } else {
            cout << "No change\n";
        }
    }

    return true;
}

int main() {

    // Initialize domains
    vector<string> vars = {"P1","P2","P3","P4","P5","P6"};
    vector<string> rooms = {"R1","R2","R3"};

    for (auto v : vars)
        domain[v] = set<string>(rooms.begin(), rooms.end());

    // Define constraints (conflicts)
    constraints["P1"] = {"P2","P3","P6"};
    constraints["P2"] = {"P1","P3","P4"};
    constraints["P3"] = {"P1","P2","P5"};
    constraints["P4"] = {"P2","P6"};
    constraints["P5"] = {"P3","P6"};
    constraints["P6"] = {"P1","P4","P5"};

    cout << " Initial Domains ";
    printDomains();

    cout << "\n Running AC-3 \n";
    AC3();

    cout << "\n After AC-3 ";
    printDomains();

    // Assign P1 = R1
    cout << "\n Assign P1 = R1 and run AC-3 again\n";

    domain["P1"] = {"R1"};

    printDomains();

    bool result = AC3();

    if (result)
        cout << "\nNo failure detected.\n";
    else
        cout << "\nFailure detected.\n";

    printDomains();

    return 0;
}