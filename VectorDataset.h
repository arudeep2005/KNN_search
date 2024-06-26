#include <bits/stdc++.h>
#include "DataVector.h"

using namespace std;

class VectorDataset{
    vector <DataVector> dset;
    public:
        VectorDataset(int dimension=0);
        ~VectorDataset();
        int getSize();
        int dimension();
        DataVector & operator[](int i);
        void setSize(int n);
        void print();
        void addDataVector(DataVector &v);
        void removeDataVector(DataVector &v, int idx);
        double max_distance(DataVector &query);
        void load(string filename);
};


