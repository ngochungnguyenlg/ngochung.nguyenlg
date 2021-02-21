#include "data_handler.hpp"
#include <iostream>
dataHandler::dataHandler()
{
    dataArray = new vector<data *>;
    this->testData = new vector<data *>;
    this->validateData = new vector<data *>;
    this->traningData = new vector<data *>;
}
dataHandler::~dataHandler(){};
void dataHandler::readFeatureVector(string path)
{
    uint32_t header[4]; //[magic|numberimage|rowsize|colsize]
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if (f)
    {
        for (int i = 0; i < 4; i++)
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convertToLittleEndian(bytes);
            }
        }
        std::cout << "done getting header" << std::endl;
        int imageSize = header[2] * header[3];
        this->row=(int)header[2];
        this->col=(int)header[3];
        cout << header[1]<<endl;
        for (int i = 0; i < header[1]; i++)
        {
            data *d = new data();
            uint8_t element[1];
            for (int j = 0; j < imageSize; j++)
            {
                if (fread(element, sizeof(element), 1, f))
                {
                    d->append_to_feature_vector(element[0]);
                }
                else
                {
                    std::cout << "read file error" << endl;
                    exit(1);
                }
            }
            this->dataArray->push_back(d);
        }
        cout << "read finish" << endl;
    }
    else
    {
        cout << "could not file" << endl;
        exit(1);
    }
}
void dataHandler::readFeatureLabel(string path)
{
    uint32_t header[2]; //[magic|numberimage|rowsize|colsize]
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if (f)
    {
        for (int i = 0; i < 2; i++)
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convertToLittleEndian(bytes);
            }
        }
        std::cout << "done getting label header" << std::endl;
        // int imageSize = header[2] * header[3];
         printf("%d\n", header[1]);
        for (int i = 0; i < header[1]; i++)
        {
            uint8_t element[1];

            if (fread(element, sizeof(element), 1, f))
            {
                if(i>= dataArray->size()){
                    throw "error label and data training are not matching";
                }
                dataArray->at(i)->set_label(element[0]);
                // printf("%d\n",dataArray->size());
                
            }
            else
            {
                std::cout << "read file error" << endl;
                exit(1);
            }
        }
        cout << "read header finish" << endl;
    }
    else
    {
        cout << "could not file" << endl;
        exit(1);
    }
}
void dataHandler::splitData(){
    unordered_set<int> usedIndexes;
    int trainingSize=dataArray->size()*trainSetPercent;
    int testSize=dataArray->size()*testSetPercent;
    int validSize=dataArray->size()*validateSetPercent;
    int count=0;
    while(count <trainingSize){
        int randIndex=rand()%dataArray->size();
        if(usedIndexes.find(randIndex)==usedIndexes.end()){
            traningData->push_back(dataArray->at(randIndex));
            ++count;
        }
    }
    count=0;
    while(count <testSize){
        int randIndex=rand()%dataArray->size();
        if(usedIndexes.find(randIndex)==usedIndexes.end()){
            testData->push_back(dataArray->at(randIndex));
            ++count;
        }
    }
    count=0;
    while(count <validSize){
        int randIndex=rand()%dataArray->size();
        if(usedIndexes.find(randIndex)==usedIndexes.end()){
            validateData->push_back(dataArray->at(randIndex));
            ++count;
        }
    }
    cout <<"training data size="<<traningData->size()<<endl;
    cout <<"test data size="<<testData->size()<<endl;
    cout <<"validate data size="<<validateData->size()<<endl;

}
void dataHandler::countClasses(){
    int count =0; 
    for(int i=0; i< dataArray->size(); ++i){
        if(classMap.find(dataArray->at(i)->get_label())==classMap.end()){
            classMap[dataArray->at(i)->get_label()]=count;
            dataArray->at(i)->set_enumerated_label(count);
            count +=1;
        }
    }
    numClasses=count;
    cout << "successfully get numclass ="<<count<<endl;
}
uint32_t dataHandler::convertToLittleEndian(const unsigned char *bytes){
    return (uint32_t (bytes[0]<<24)|
                    (bytes[0]<<16)|
                    (bytes[2]<<8)|
                    (bytes[3]));
}
vector<data *> *dataHandler::getTrainingData(){
    return traningData;
}
vector<data *> *dataHandler::getTestData(){
    return testData;
}
vector<data *> *dataHandler::getValidationData(){
    return validateData;
}
vector<data *> *dataHandler::getArrayData(){
    return dataArray;
}
void dataHandler::convertToOneDim(){
    this->oneDim.clear();
    for(int i=0; i<this->dataArray->size(); i++){
        for (int j=0; j<this->dataArray->at(i)->get_feature_vector_size();j++){
            oneDim.push_back(this->dataArray->at(i)->get_feature_vector()->at(j));
        }
    }
}
vector<uint8_t> dataHandler::getOneDimVect() const{
    return oneDim;
}
int * dataHandler::getRowCol() const{
    int *ret=new int[2];
    ret[0]=this->dataArray->size();
    ret[1]=this->dataArray->at(0)->get_feature_vector_size();
    return ret;
}
