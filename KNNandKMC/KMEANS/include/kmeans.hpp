#include <cstdlib>
#include <cmath>
#include <map>
#include "data_handler.hpp"
using namespace std;

typedef struct cluster{

vector<double> *centroid;
vector<data*> *cluster_point;
map<int, int> class_counts;
int mostFrequentClass;
cluster(data *initialPoint){
    centroid=new std::vector<double>;
    cluster_point=new std::vector<data*>;
    for(auto value: *(initialPoint->get_feature_vector())){
        centroid->push_back(value);
    }
    cluster_point->push_back(initialPoint);
    class_counts[initialPoint->get_label()]=1;
    mostFrequentClass=initialPoint->get_label();
}
void addToCluster(data *point){
    int previousSize=this->cluster_point->size();
    cluster_point->push_back(point);
    for(int i=0; i<centroid->size()-1; ++i){
        double value=centroid->at(i);
        value *=previousSize;
        value+=point->get_feature_vector()->at(i);
        double val=(double)cluster_point->size();
        centroid->at(i)=val;
    }
}

}cluster_t;