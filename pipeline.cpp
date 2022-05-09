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
        this->visited = 0;
        this->processed = false;
    }
};

unordered_map<int, Operation*> operations;
pair<int, Operation*> initialOperation;
pair<int, Operation*> lastOperation;
vector<int> processedOp;
vector<int> bottlenecks;
vector<int> nonProcessed;

vector<int> toProcess; //queue a ser usada na estatistica 2
vector<int> toProcessAux;
int t;

/*int findOp(Operation* op) {
    for (pair<int, Operation*> o : operations) {
        if (o.second == op) return o.first;
    }
    return 0;
}*/

bool hasCycle(Operation* op) {
    if (op->visited < op->D || op->D == 0) {
        op->visited++;
        for (int o : op->sons) {
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

void statistic1() {
    int time = 0;
    priority_queue<int, vector<int>, greater<int>>queue;
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
    priority_queue<int, vector<int>, greater<int>>queue;
    queue.push(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.top();
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

void isBottleneck(Operation* op) {
    for (int o : op->sons) {
        operations[o]->processed = true;
        isBottleneck(operations[o]);
    }
}

void isBottleneckAux(Operation* op) {
    for (int o : op->parents) {
        operations[o]->processed = true;
        isBottleneckAux(operations[o]);
    }
}

void statistic3() {
    queue<int> queue;
    queue.push(initialOperation.first);
    bottlenecks.push_back(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.front();
        Operation* o = operations[id];
        o->processed = true;
        processedOp.push_back(id);
        queue.pop();

        if (o->D != 0 && !o->sons.empty()) {
            isBottleneck(o);
            isBottleneckAux(o);
            int count = 0;
            for (pair<int, Operation*> i : operations) {
                if (i.second->processed == false)
                    break;
                count++;
            }
            if (count == (int)operations.size())
                bottlenecks.push_back(id);

            for (pair<int, Operation*> i : operations) {
                i.second->processed = false;
            }

        }

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (find(processedOp.begin(), processedOp.end(), parent) != processedOp.end()) j++;
            }

            if (j == operations[son]->D) queue.push(son);
        }
    }

    bottlenecks.push_back(lastOperation.first);

    for (int id : bottlenecks) cout << id << endl;
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

        if (initialNodes > 1) {
            cout << "INVALID" << endl;
            return 0;
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

    int stat; // statistic that should be computed if the data pipeline is valid
    cin >> stat;

    /*for (auto& i : operations) {
        cout << i.first << " -> ";
        for (auto& j : i.second->parents) cout << j << " ";
        cout << endl;
    }*/

    int nLeaves = 0;
    for (pair<int, Operation*> o : operations) {
        if (o.second->sons.size() == 0) {
            nLeaves++;
            lastOperation.first = o.first;
            lastOperation.second = o.second;
        }

        if (nLeaves > 1) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    /*----- FALTA DETECAO DE CICLOS -----*/

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
