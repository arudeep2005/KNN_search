#include "DataVector.h"
#include <bits/stdc++.h>

DataVector::DataVector(int dimension) {
    v.resize(dimension,0);
}

DataVector::~DataVector() {
    v.clear();
}

DataVector::DataVector(const DataVector &other) {
    v.assign(other.v.begin(), other.v.end());
}

DataVector::DataVector(vector<double> &other) {
    v.assign(other.begin(), other.end());
}

DataVector & DataVector::operator=(const DataVector &other) {
    v.assign(other.v.begin(), other.v.end());
    return *this;
}

void DataVector::setDimension(int dimension) {
    v.resize(dimension);
}

DataVector DataVector::operator+(const DataVector &other) {
    DataVector result;
    result.v.resize(v.size());
    if (v.size() != other.v.size()) {
        cerr << "Error: Vectors must have the same dimension for addition." << endl;
        return result;
    }
    for (int i=0; i<v.size(); i++) {
        result.v[i] = v[i] + other.v[i];
    }
    return result;
}

DataVector DataVector::operator-(const DataVector &other) {
    DataVector result;
    result.v.resize(v.size());
    if (v.size() != other.v.size()) {
        cerr << "Error: Vectors must have the same dimension for subtraction." << endl;
        return result;
    }
    for (int i=0; i<v.size(); i++) {
        result.v[i] = v[i] - other.v[i];
    }
    return result;
}

double DataVector::operator*(const DataVector &other) {
    long double result = 0;
    if (v.size() != other.v.size()) {
        cerr << "Error: Vectors must have the same dimension for dot product." << endl;
        return result;
    }
    for (int i=0; i<v.size(); i++) {
        result += v[i] * other.v[i];
    }
    return result;
}

double DataVector::operator[](int i){
    return v[i];
};

int DataVector::getDimension() const{
    return v.size();
};

double DataVector::norm(){
    long double result = (*this) * (*this);
    long double temp =  sqrtl(result);
    return temp;
}

double DataVector::dist(const DataVector &other) {
    DataVector temp = (*this) - other;
    long double result = temp.norm();
    return result;
}

void DataVector::print() {
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

bool DataVector::comparator(DataVector &other, DataVector &rule){
    return (*this)*rule<other*rule;
}

void DataVector::set(int pos){
    v[pos] = 1;
    return;
}

void DataVector::rand_unit(int dim){
    srand (time(NULL));
    v.clear();
    v.resize(dim);
    double sum=0;
    for(int i=0;i<dim;i++){
        v[i]=(float)rand()/RAND_MAX;
        sum += v[i]*v[i];
    }
    sum = sqrt(sum);
    for(int i=0;i<dim;i++){
        v[i]/=sum*1.0;
    }
    return;
}
