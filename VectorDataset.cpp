#include "VectorDataset.h"

VectorDataset::VectorDataset(int dimension){
    dset.resize(dimension);
}

VectorDataset::~VectorDataset(){}

int VectorDataset::getSize(){
    return dset.size();
}

int VectorDataset::dimension(){
    return dset[0].getDimension();
}

DataVector & VectorDataset::operator[](int i){
    return dset[i];
}

void VectorDataset::setSize(int n){
    dset.resize(n);
}

void VectorDataset::print(){
    for(int i=0;i<dset.size();i++){
        dset[i].print();
    }
}

void VectorDataset::addDataVector(DataVector &v){
    dset.push_back(v);
}

void VectorDataset::removeDataVector(DataVector &v , int idx){
    for(int i=idx; i<(dset.size())-1;i++) dset[i]=dset[i+1];
    dset.pop_back();
}

double VectorDataset::max_distance(DataVector &query){
    double result=0;
    for(int i=0;i<dset.size();i++){
        result=max(result, dset[i].dist(query));
    }
    return result;
}

void VectorDataset::load(string filename){
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<double> v;
        double x;

        while (iss >> x) {
            v.push_back(x);
            char comma;
            if (iss >> comma && comma != ',') {
                cerr << "Error: Expected a comma in the CSV file." << endl;
                return; // Exit with an error code
            }
        }
        DataVector dataVector(v);
        addDataVector(dataVector);
    }
    file.close();
}


