#ifndef __KNN_H
#define __KNN_H

#include <vector>
// #include "../../KMEANS/include/data.hpp"
#include "data.hpp"

class knn{
    int k;
    std::vector<data *> *neighbors;
    std::vector<data*> *traningData;
    std::vector<data*> *testData;
    std::vector<data*> *validationData;
    public:
    knn(int);
    knn();
    ~knn(){}
    void findKnearest(data *queryPoint);
    void setTrainingData(std::vector<data*> *vect);
    void setTestData(std::vector<data*> *vect);
    void setValidationData(std::vector<data*>*vect);
    void setK(int val);
    int predict();
    double caculateDistance(data * queryPoint, data * input);
    double validatePerformance();
    double testPerformance();
    void getPredict();
};

#endif