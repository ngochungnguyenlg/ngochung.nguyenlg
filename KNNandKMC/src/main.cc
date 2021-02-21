#include "../include/data_handler.hpp"
#include "../src/dataframe.cc"
#include <iostream>
int main()
{
    try
    {
        dataHandler *dh = new dataHandler();
        dh->readFeatureVector("../KMEANS/train-images-idx3-ubyte");
        dh->readFeatureLabel("../KMEANS/train-labels-idx1-ubyte");
        dh->splitData();
        vector<uint8_t>* dhtry=dh->getArrayData()->at(0)->get_feature_vector();
        dataframe<uint8_t> csv(*dhtry,dh->getRow(), dh->getCol());
        csv.to_csv("a.csv");
    }catch(const char * e){
        std::cout <<e<<std::endl;
    }
}