#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;


class Operation {
public:
    int T; // time needed to perform the operation
    int D; // number of dependencies

    vector<int> dependables; // operations that depend from this one

    Operation() {}
};

unordered_map<int, Operation*> operations;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int nOp; // number of operations
    cin >> nOp;

    int initialNodes = 0;
    for (int i = 0; i < nOp; i++) {
        Operation* op = new Operation();
        operations[i + 1] = op;

        cin >> op->T >> op->D;

        if (op->D == 0) initialNodes++;


        if (initialNodes > 1) {
            cout << "INVALID" << endl;
            return 0;
        }

        for (int j = 0; j < op->D; j++) {
            int n;
            cin >> n;
            if (operations.find(n) != operations.end()) operations[n]->dependables.push_back(i+1);


        }
    }

    int nLeaves = 0;
    for (auto& i : operations) {
        if (i.second->dependables.size() == 0) nLeaves++;

        if (nLeaves > 1) {
            cout << "INVALID" << endl;
            return 0;
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