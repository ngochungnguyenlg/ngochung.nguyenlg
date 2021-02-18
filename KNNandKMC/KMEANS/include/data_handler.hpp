#ifndef __data_handler_h
#define __data_handler_h
#include <fstream>
#include <stdint.h>
#include "data.hpp"
#include <string>
#include <map>
#include <unordered_set>
using namespace std;

class dataHandler
{
    vector<data *> *dataArray;
    vector<data *> *traningData;
    vector<data *> *testData;
    vector<data *> *validateData;
    int numClasses;
    int featureVectorSize;
    map<uint8_t, int> classMap;
    const double trainSetPercent = 0.75;
    const double testSetPercent = 0.2;
    const double validateSetPercent = 0.05;

public:
    dataHandler();
    ~dataHandler();
    void readFeatureVector(string path);
    void readFeatureLabel(string path);
    void splitData();
    void countClasses();
    uint32_t convertToLittleEndian(const unsigned char * bytes);
    vector<data*> *getTrainingData();
    vector<data*> *getTestData();
    vector<data*> *getValidationData();
};

#endif