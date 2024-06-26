#include <bits/stdc++.h>

using namespace std;
class DataVector{
    vector<double> v;
    public:
    DataVector(int dimension=0);
    DataVector(vector <double>& v);
    ~DataVector();
    void setDimension(int dimension=0);
    DataVector(const DataVector &other);
    DataVector & operator=(const DataVector &other);
    DataVector operator+(const DataVector &other);
    DataVector operator-(const DataVector &other);
    double operator[](int i);
    int getDimension() const;
    double operator*(const DataVector &other);
    double norm();
    double dist(const DataVector &other);
    void print();
    bool comparator(DataVector &other, DataVector &rule);
    void set(int pos);
    void rand_unit(int dim);
};