#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>


using namespace std;


class Operation {
public:
    int T; // time needed to perform the operation
    int D; // number of dependencies
    int visited; // denotes if the variable has been visited, is used to find cycles

    vector<int> dependables; // operations that depend from this one
    vector<int> dependencies;

    Operation() {
        this->visited = 0;
    }
};

unordered_map<int, Operation*> operations;
pair<int, Operation*> startOp;


int findOp(Operation* op) {
    for (pair<int, Operation*> o : operations) {
        if (o.second == op) return o.first;
    }
    return 0;
}

bool hasCycle(Operation* op) {
    if (op->visited < op->D || op->D == 0) {
        //cout << findOp(op) << " -> ";
        op->visited++;
        //cout << op->visited << endl;
        for (int o : op->dependables) {
            if (hasCycle(operations[o]))
                return true;
            operations[o]->visited--;
        }
    }
    else
        return true;

    op->visited--;
    return false;
}

void stat1(int op) {
    priority_queue<int, vector<int>> queue;
    queue.push(op);

    while (!queue.empty()) {
        int id = queue.top();
        Operation* o = operations[id];
        queue.pop();


    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int nOp; // number of operations
    cin >> nOp;

    int initialNodes = 0;
    for (int i = 0; i < nOp; i++) {
        Operation* op = new Operation();

        if (operations.find(i + 1) == operations.end())
            operations[i + 1] = op;
        else op = operations[i + 1];

        cin >> op->T >> op->D;

        if (op->D == 0) {
            initialNodes++;
            startOp.first = i + 1;
            startOp.second = op;
        }

        if (initialNodes > 1) {
            cout << "INVALID" << endl;
            return 0;
        }

        for (int j = 0; j < op->D; j++) {
            int n;
            cin >> n;
            if (operations.find(n) != operations.end()) operations[n]->dependables.push_back(i + 1);
            else {
                operations[n] = new Operation();
                operations[n]->dependables.push_back(i + 1);
            }
            operations[i + 1]->dependencies.push_back(n);
        }
    }

    int stat; // statistic that should be computed if the data pipeline is valid
    cin >> stat;

    /*for (auto& i : operations) {
        cout << i.first << " -> ";
        for (auto& j : i.second->dependencies) cout << j << " ";
        cout << endl;
    }*/

    int nLeaves = 0;
    for (pair<int, Operation*> o : operations) {
        if (o.second->dependables.size() == 0) nLeaves++;

        if (nLeaves > 1) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    if (hasCycle(startOp.second)) {
        cout << "INVALID" << endl;
        return 0;
    }

    switch (stat) {
    case 0:
        cout << "VALID" << endl;
        break;
    case 1:
        stat1(startOp.first);
        break;
    case 2:

        break;
    case 3:

        break;
        }

        return 0;
    }