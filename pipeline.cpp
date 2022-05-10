#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

class Operation {
public:
    int T; // time needed to perform the operation
    int D; // number of parents
    int visited; // denotes if the variable has been visited, is used to find cycles
    bool processed;

    vector<int> sons; // operations that depend from this one
    vector<int> parents;

    Operation() {
        this->processed = false;
    }
};

unordered_map<int, Operation*> operations;
pair<int, Operation*> initialOperation;
pair<int, Operation*> lastOperation;
vector<int> processedOp;

bool hasCycle() {
    queue<int> queue;
    queue.push(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.front();
        Operation* o = operations[id];
        queue.pop();

        o->processed = true;

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (operations[parent]->processed) j++;
            }

            if (j == operations[son]->D) queue.push(son);
        }
    }

    for (pair<int, Operation*> i : operations) {
        if (!i.second->processed) return true;
        i.second->processed = false;
    }

    return false;
}

void statistic1() {
    int time = 0;
    priority_queue<int, vector<int>, greater<int>> queue;
    queue.push(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.top();
        Operation* o = operations[id];
        queue.pop();

        o->processed = true;
        processedOp.push_back(id);
        time += o->T;

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (operations[parent]->processed) j++;
            }

            if (j == operations[son]->D) queue.push(son);
        }
    }

    cout << time << endl;
    for (int id : processedOp) cout << id << endl;
}

void statistic2() {
    queue<int> queue;
    queue.push(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.front();
        Operation* o = operations[id];
        queue.pop();

        o->processed = true;

        for (int son : o->sons) {
            int j = 0;
            int max = 0;
            for (int parent : operations[son]->parents) {
                if (operations[parent]->processed) {
                    if (max < operations[parent]->T)
                        max = operations[parent]->T;
                    j++;
                }
            }

            if (j == operations[son]->D) {
                operations[son]->T += max;
                queue.push(son);
            }
        }
    }

    cout << lastOperation.second->T << endl;
}

void isBottleneck(int id) {
    for (int o : operations[id]->sons) {
        if (find(processedOp.begin(), processedOp.end(), o) == processedOp.end()) {
            processedOp.push_back(o);
            isBottleneck(o);
        }

    }
}

void isBottleneckAux(int id) {
    for (int o : operations[id]->parents) {
        if (find(processedOp.begin(), processedOp.end(), o) == processedOp.end()) {
            processedOp.push_back(o);
            isBottleneckAux(o);
        }

    }
}

void statistic3() {
    queue<int> queue;
    queue.push(initialOperation.first);
    cout << initialOperation.first << endl;

    while (!queue.empty()) {
        int id = queue.front();
        Operation* o = operations[id];
        o->processed = true;
        queue.pop();

        processedOp.push_back(id);
        if (o->D != 0 && !o->sons.empty()) {
            isBottleneck(id);
            isBottleneckAux(id);
            //cout << id << " -> " << processedOp.size() << " " << operations.size() << endl;
            if (processedOp.size() == operations.size())
                cout << id << endl;
        }
        processedOp.clear();

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (operations[parent]->processed) j++;
            }

            if (j == operations[son]->D) queue.push(son);
        }
    }

    cout << lastOperation.first << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

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
            initialOperation.first = i + 1;
            initialOperation.second = op;
        }

        for (int j = 0; j < op->D; j++) {
            int n;
            cin >> n;
            if (operations.find(n) != operations.end()) operations[n]->sons.push_back(i + 1);
            else {
                operations[n] = new Operation();
                operations[n]->sons.push_back(i + 1);
            }
            operations[i + 1]->parents.push_back(n);
        }
    }

    int nLeaves = 0;
    for (pair<int, Operation*> o : operations) {
        if (o.second->sons.size() == 0) {
            nLeaves++;
            lastOperation.first = o.first;
            lastOperation.second = o.second;
        }

        if (nLeaves > 1 || initialNodes != 1) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    if (hasCycle() == true) {
        cout << "INVALID\n";
        return 0;
    }

    int stat; // statistic that should be computed if the data pipeline is valid
    cin >> stat;

    switch (stat) {
    case 0:
        cout << "VALID" << endl;
        break;
    case 1:
        statistic1();
        break;
    case 2:
        statistic2();
        break;
    case 3:
        statistic3();
        break;
    }

    return 0;
}
