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
vector<int> processed;
vector<int> bottlenecks;

vector<int> toProcess; //queue a ser usada na estatistica 2
vector<int> toProcessAux;

int findOp(Operation* op) {
    for (pair<int, Operation*> o : operations) {
        if (o.second == op) return o.first;
    }
    return 0;
}

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

bool isProcessed(int op) {
    for (int o : processed) {
        if (op == o) return true;
    }
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

        int i = 0;
        for (int parent : o->parents) {
            if (isProcessed(parent)) i++;
        }
        if (i == o->D) {
            processed.push_back(id);
            time += o->T;
        }

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (isProcessed(parent)) j++;
            }

            if (j == operations[son]->D) queue.push(son);
        }
    }

    cout << time << endl;
    for (int id : processed) cout << id << endl;
}

void statistic2aux(int index) {
    int count = 0; //num de pais processados

    for (auto& i: operations[index]->parents) {
        if (operations[i]->processed == false) {
            statistic2aux(i);
        } else {
            count++;
        }
    }

    if (count == operations[index]->D) {
        if (find(toProcessAux.begin(), toProcessAux.end(), index) == toProcessAux.end()) toProcessAux.push_back(index);
    }
    
    return;
}

void statistic2() {
    int time = 0;
    //vector<int> toProcess; //operacoes a serem processadas simultaneamente
    //vector<int> toProcessAux;

    toProcess.push_back(initialOperation.first);

    while(!toProcess.empty()) {
        toProcessAux.clear();

        //processa os nos do vector e avanca para os filhos
        for(auto& i: toProcess) {
            time += operations[i]->T;
            operations[i]->processed = true;
        }

        for(auto& i: toProcess) {
            for (auto& j: operations[i]->sons) {
                statistic2aux(j);
            }
        }
        
        toProcess = toProcessAux;
    }

    cout << time << endl;
}   

void statistic3() {
    cout << initialOperation.first << endl;

    priority_queue<int, vector<int>, greater<int>>queue;
    queue.push(initialOperation.first);

    while (!queue.empty()) {
        int id = queue.top();
        Operation* o = operations[id];
        queue.pop();

        int i = 0;
        for (int parent : o->parents) {
            if (isProcessed(parent)) i++;
        }
        if (i == o->D) {
            processed.push_back(id);
            if (o->D > 1 || o->sons.empty()) 
                cout << id << endl;
        }

        for (int son : o->sons) {
            int j = 0;
            for (int parent : operations[son]->parents) {
                if (isProcessed(parent)) j++;
            }
            if (j == operations[son]->D) queue.push(son);
        }
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
        if (o.second->sons.size() == 0) nLeaves++;

        if (nLeaves > 1) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    /*if (hasCycle(initialOperation.second)) {
        cout << "INVALID" << endl;
        return 0;
    }*/

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
