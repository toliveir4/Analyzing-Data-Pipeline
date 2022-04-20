#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


class Operation {
public:
    int T; // time needed to perform the operation
    int D; // number of dependencies
    int visited; // denotes if the variable has been visited, is used to find cycles

    vector<int> dependables; // operations that depend from this one

    Operation() {
        this->visited = 0;
    }
};

map<int, Operation*> operations;


int findOp(Operation* op) {
    for (auto& o : operations) {
        if (o.second == op) return o.first;
    }
    return 0;
}

bool hasCycle(Operation* op) {
    if (op->visited < op->D || op->D == 0) {
        //cout << findOp(op) << " -> ";
        op->visited++;
        //cout << op->visited << endl;
        for (auto& o : op->dependables) {
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

        if (op->D == 0) initialNodes++;


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
        }
    }

    /*for (auto& i : operations) {
        cout << i.first << " -> ";
        for (auto& j : i.second->dependables) cout << j << " ";
        cout << endl;
    }*/

    int nLeaves = 0;
    for (auto& i : operations) {
        if (i.second->dependables.size() == 0) nLeaves++;

        if (nLeaves > 1) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    for (auto& i : operations) {
        if (i.second->D == 0) {
            if (hasCycle(i.second)) {
                cout << "INVALID" << endl;
                return 0;
            }
            break;
        }
    }

    int stat; // statistic that should be computed if the data pipeline is valid
    cin >> stat;

    switch (stat) {
    case 0:
        cout << "VALID" << endl;
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    }


    return 0;
}