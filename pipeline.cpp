#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

class Operation
{
public:
    int T;       // time needed to perform the operation
    int D;       // number of parents
    bool processed;
    int totalT;

    vector<int> sons; // operations that depend from this one
    vector<int> parents;

    Operation()
    {
        this->processed = false;
    }
};

unordered_map<int, Operation*> operations;
pair<int, Operation*> initialOperation;
pair<int, Operation*> lastOperation;
vector<int> processedOp;
vector<bool> aux;
int nOp; // number of operations

int hasCycle()
{
    int time = 0;
    priority_queue<int, vector<int>, greater<int>> queue;
    queue.push(initialOperation.first);
    initialOperation.second->totalT = initialOperation.second->T;

    while (!queue.empty())
    {
        int id = queue.top();
        Operation* o = operations[id];
        queue.pop();

        o->processed = true;
        processedOp.push_back(id);
        time += o->T;

        for (int son : o->sons)
        {
            int j = 0;
            int max = 0;
            for (int parent : operations[son]->parents)
            {
                if (operations[parent]->processed)
                {
                    if (max < operations[parent]->totalT)
                        max = operations[parent]->totalT;
                    j++;
                }
            }

            if (j == operations[son]->D)
            {
                operations[son]->totalT = max + operations[son]->T;
                queue.push(son);
            }
        }
    }

    if (processedOp.size() != operations.size()) return -1;

    return time;
}

int isBottleneck(int id)
{
    aux[id] = true;
    int c = 1;

    for (int o : operations[id]->sons)
    {
        if (aux[o] == false) {
            aux[o] = true;
            c += isBottleneck(o);
        }
    }

    return c;
}

int isBottleneckAux(int id)
{
    aux[id] = true;
    int c = 1;

    for (int o : operations[id]->parents)
    {
        if (aux[o] == false) {
            aux[o] = true;
            c += isBottleneckAux(o);
        }
    }

    return c;
}

void statistic3()
{
    cout << initialOperation.first << endl;
    int sum1 = 0;
    int sum2 = 0;

    aux.resize(nOp + 1);

    for (int id : processedOp)
    {
        Operation* o = operations[id];
        if (o->D != 0 && !o->sons.empty())
        {
            fill(aux.begin(), aux.end(), false);
            sum1 = isBottleneck(id);
            sum2 = isBottleneckAux(id);
            if (sum1 + sum2 - 1 == (int)operations.size())
                cout << id << endl;
        }
    }

    cout << lastOperation.first << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> nOp;

    int initialNodes = 0;
    for (int i = 0; i < nOp; i++)
    {
        Operation* op = new Operation();

        if (operations.find(i + 1) == operations.end())
            operations[i + 1] = op;
        else
            op = operations[i + 1];

        cin >> op->T >> op->D;

        if (op->D == 0)
        {
            initialNodes++;
            initialOperation.first = i + 1;
            initialOperation.second = op;
        }

        for (int j = 0; j < op->D; j++)
        {
            int n;
            cin >> n;
            if (operations.find(n) != operations.end())
                operations[n]->sons.push_back(i + 1);
            else
            {
                operations[n] = new Operation();
                operations[n]->sons.push_back(i + 1);
            }
            operations[i + 1]->parents.push_back(n);
        }
    }

    int nLeaves = 0;
    for (pair<int, Operation*> o : operations)
    {
        if (o.second->sons.size() == 0)
        {
            nLeaves++;
            lastOperation.first = o.first;
            lastOperation.second = o.second;
        }

        if (nLeaves > 1 || initialNodes != 1)
        {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    int t = hasCycle();
    if (t == -1)
    {
        cout << "INVALID\n";
        return 0;
    }

    int stat; // statistic that should be computed if the data pipeline is valid
    cin >> stat;

    switch (stat)
    {
    case 0:
        cout << "VALID" << endl;
        break;
    case 1:
        cout << t << endl;
        for (int id : processedOp)
            cout << id << endl;
        break;
    case 2:
        cout << lastOperation.second->totalT << endl;
        break;
    case 3:
        statistic3();
        break;
    }

    return 0;
}
