#include "TreeIndex.h"

VectorDataset *dataset = new VectorDataset;

DataVector Tree::kdRule(int dim, int idx) {
    DataVector result(dim);
    result.set(idx);
    return result;
}

DataVector Tree::rpRule(int dim){
    DataVector result(dim);
    srand(time(NULL));
    result.rand_unit(dim);
    return result;
}

Tree::Tree(int idx, int t, vector<int> ex) : type(t), left(NULL), right(NULL){
    con = new node;
    con->ref = ex;
    con->del.resize(con->ref.size(), 0);
    con->median = -1;
    con->ind = idx;
}

void Tree::MakeTree(){
    int dim = dataset->dimension();
    int size = con->ref.size();
    con->del.resize(con->ref.size(), 0);
    if (size <= BASE){
        return;
    }
    if (type == 0) con->rule = kdRule(dim, con->ind);
    else con->rule = rpRule(dim);

    sort(con->ref.begin(), con->ref.end(), [this](int i, int j)
         { return dataset->operator[](i).comparator(dataset->operator[](j), con->rule); });
    con->median = dataset->operator[](con->ref[size / 2]) * con->rule;
    vector<int> l;
    vector<int> r;

    for (int i = 0; i < size; ++i){
        srand(time(0));
        if (type == 1)
            con->del[i] = (((float)rand() / RAND_MAX) * 2 - 1) * 6 * dataset->max_distance(dataset->operator[](con->ref[i])) / sqrt(dim);
        if (dataset->operator[](con->ref[i]) * con->rule < con->median + con->del[i]){
            l.push_back(con->ref[i]);
        }
        else{
            r.push_back(con->ref[i]);
        }
    }
    left = new Tree((con->ind + 1) % dim, type, l);
    right = new Tree((con->ind + 1) % dim, type, r);
    left->MakeTree();
    right->MakeTree();
}

VectorDataset Tree::search(DataVector *d, int k){
    priority_queue <pair<double, int> > m;
    searchRecurse(d, k, m);
    VectorDataset result;
    while (!m.empty()){
        result.addDataVector(dataset->operator[](m.top().second));
        m.pop();
    }
    return result;
}

void Tree::searchRecurse(DataVector *d, int k, priority_queue<pair<double, int>> &m){
    if (left == NULL && right == NULL){
        knearestneighbor(*d, k);
        return;
    }
    double dis = (*d) * con->rule;
    double delt = (type == 1) ? (((float)rand() / RAND_MAX) * 2 - 1) * 6 * dataset->max_distance(*d) / sqrt(d->getDimension()) : 0;
    if ((*d) * con->rule < con->median + delt){
        left->searchRecurse(d, k, m);
        if (m.size() < k || dis < m.top().first){
            right->searchRecurse(d, k, m);
        }
    }
    else{
        right->searchRecurse(d, k, m);
        if (m.size() < k || dis <= m.top().first){
            left->searchRecurse(d, k, m);
        }
    }
}

VectorDataset Tree::knearestneighbor(DataVector &testVector, int k){
    auto start = chrono::high_resolution_clock::now();
    VectorDataset result;

    vector<pair<double, int> > distances; // Pair of distance and ind in the dataset
    int datasetSize = dataset->getSize();

    for (int i = 0; i < datasetSize; i++){
        double distance = testVector.dist(dataset->operator[](i));
        distances.push_back(make_pair(distance, i));
    }

    // Sort distances in ascending order
    sort(distances.begin(), distances.end());

    // Retrieve the top k closest vectors
    for (int i = 0; i < k; ++i){
        result.addDataVector(dataset->operator[](distances[i].second));
    }
    for (int i = 0; i < k; i++){
        cout << i + 1 << ". ";
        cout << "Index: " << distances[i].second << ", ";
        cout << "Distance: " << distances[i].first << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    double time = duration.count() / 1000000.0;

    cout << endl
         << endl
         << "Time taken for " << k << " nearest neighbor search: " << time << " seconds." << endl
         << endl;
    cout << endl;

    return result;
}

void Tree::printTree(){
    if (con == NULL) return;
    for (int i = 0; i < con->ref.size(); i++){
        cout << con->ref[i] << " ";
    }
    cout << endl;
    if (left != NULL){
        left->printTree();
    }
    if (right != NULL){
        right->printTree();
    }
    return;
}

Tree::~Tree(){
    delete left;
    delete right;
    delete con;
}

TreeIndex::TreeIndex(int i, int t) : root(new Tree(i, t, vector<int>(dataset->getSize(), 0))){
    for (int i = 0; i < dataset->getSize(); ++i) root->con->ref[i] = i;
    root->MakeTree();
};

TreeIndex::~TreeIndex() { delete root; }

void TreeIndex::print(){
    root->printTree();
}

VectorDataset TreeIndex::knearest(DataVector *v, int k){
    return root->search(v, k);
}

KDTreeIndex::KDTreeIndex(int random) : TreeIndex(57, 0) {}
KDTreeIndex::~KDTreeIndex() {}

RPTreeIndex::RPTreeIndex(int random) : TreeIndex(-1, 1) {}
RPTreeIndex::~RPTreeIndex() {}

int TreeIndex::type = -1;

int main(){
    dataset->load("fmnist-train.csv");
    cout << "Finding k nearest neighbour by RP or KD tree indexing\n" << endl;
    cout << "Enter 1 for RP tree indexing or 0 for KD tree indexing: ";
    int t,k;
    cin >> t;
    DataVector query = dataset->operator[](4);
    cout << "Enter the value of k: ";
    VectorDataset dataset2;
    dataset2.load("fmnist-test.csv");
    int cnt=0;
    cin>>k;
    if (t == 0) {
        for(int i=0;i<dataset2.getSize();i++){
            cout<<"The top "<<k<<" closest vectors to index "<<cnt<<" of testfile are:\n " << endl;
            KDTreeIndex::GetInstance(0).knearest(&dataset2.operator[](i),k).print();
            cout<<endl;
        }
    }
    else{
        for(int i=0;i<dataset2.getSize();i++){
            cout<<"The top "<<k<<" closest vectors to index "<<cnt<<" of testfile are:\n " << endl;
            RPTreeIndex::GetInstance(1).knearest(&dataset2.operator[](i),k).print();
            cout<<endl;
        }
    }
    return 0;
}
