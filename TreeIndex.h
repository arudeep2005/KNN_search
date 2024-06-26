#include "VectorDataset.h"
#define BASE 60005

struct node{
    vector<int> ref;
    int ind;
    DataVector rule;
    vector<double> del;
    double median;
};

typedef struct node node;

class Tree{
    Tree *left;
    Tree *right;

    node *con;
    int type; 
    friend class TreeIndex;
    public:
        Tree(int idx, int t, vector<int> ex);
        ~Tree();
        DataVector kdRule(int dim, int idx);
        DataVector rpRule(int dim);
        
        void MakeTree();
        VectorDataset search(DataVector *d, int k);                              
        void searchRecurse(DataVector *d, int k, priority_queue<pair<double, int> > &maxheap);
        VectorDataset knearestneighbor(DataVector &testVector, int k);
        void printTree();
};

class TreeIndex {
    Tree *root;
    protected:
        
        TreeIndex(int i, int t);
        ~TreeIndex();

    public:
        static int type;
        static TreeIndex & TGetInstance(int i, int t){
            static TreeIndex instance(i, t);
            return instance;
        }
        void print();
        VectorDataset knearest(DataVector *v, int k);
};

class KDTreeIndex : public TreeIndex{
    private:
        KDTreeIndex(int random);
        ~KDTreeIndex();
    public:
        static KDTreeIndex &GetInstance(int random){
            if (type == 1)
            {
                cout << "ERROR" << endl;
                exit(1);
            }
            static KDTreeIndex instance(0);
            type = 0;
            return instance;
        }
};

class RPTreeIndex : public TreeIndex {
    private:
        RPTreeIndex(int random);
        ~RPTreeIndex();
    public:
        static RPTreeIndex &GetInstance(int random){
            if (type == 0)
            {
                cout << "ERROR" << endl;
                exit(1);
            }
            static RPTreeIndex instance(0);
            type = 1;
            return instance;
        }
};
