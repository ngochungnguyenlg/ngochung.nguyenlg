#include "../include/knn.hpp"
#include <math.h>
#include <algorithm>
#include <map>
#include <stdint.h>
#include "data_handler.hpp"
#include <iostream>
#include "../../src/dataframe.cc"
using namespace std;

knn::knn(int val)
{
    this->k = val;
}
knn::knn()
{
    //nothing to do
}
// knn::~knn() {}
void knn::findKnearest(data *queryPoint)
{
    /*
    @ý tưởng thuật toán:
    tìm toàn bộ trong tập traning size cho tới khi đủ 7 điểm gần nhất,
    ban đầu ta tìm điểm nhỏ nhất, sau đó tìm các điểm lơn hơn 1 chút.
    tuy nhiên ta cần khởi tạo 1 variable: distance trong class data để lưu vị trí của nó tới điểm đang truy vấn.
    như thế khi tìm điểm gần nhất thứ 2 trở đi, việc gọi giá trị của nó sẽ làm giảm thời gian tính toán lại khoảng cách đến điểm truy vấn.
    */
    this->neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double previousMin = min;
    int index = 0;
    for (int i = 0; i < k; ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < traningData->size(); ++j)
            {
                double distance = this->caculateDistance(queryPoint, traningData->at(j));
                traningData->at(j)->setDistance(distance);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbors->push_back(traningData->at(index));
            previousMin = min;
            min = std::numeric_limits<double>::max();
        }
        else
        {
            for (int j = 0; j < traningData->size(); ++j)
            {
                double distance = traningData->at(j)->getDistance();
                traningData->at(j)->setDistance(distance);
                if (distance > previousMin && distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbors->push_back(traningData->at(index));
            previousMin = min;
            min = std::numeric_limits<double>::max();
        }
    }
}
void knn::setTrainingData(std::vector<data *> *vect)
{
    this->traningData = vect;
}
void knn::setTestData(std::vector<data *> *vect)
{
    this->testData = vect;
}
void knn::setValidationData(std::vector<data *> *vect)
{
    this->validationData = vect;
}
void knn::setK(int val)
{
    this->k = val;
}
int knn::predict()
{
    /* ý tưởng thuật toán:/-7410 
        giả sử k=7:
        rõ ràng neighbors sẽ có size=7 và chưa những label khác nhau.
        ở đây tạm gọi như là kết quả định danh của 1 loại các data:
        ví dụ như: cánh vàng, nhụy trắng là data traning và có label là hoa cúc. 
        dùng map để định danh sống lượng label đang có:
        ví du: có 3 hoa cúc, 4 hoa hồng -> kết luận phải là hoa hồng
        như vậy ta khởi tạo 1 map rỗng mà bắt, đầu tìm kiếm label trên nó, nếu kết quả tìm kiếm ra end tức là nó chưa có trong map, 
        và ta phải tạo 1 index cho nó.
        nếu nó đã có r thì tăng nó lên: 
        classFreq.find["hoa hong"]==classFreq.end()
        classFreq["hoa hong"]=1;
        else
        classFreq["hoa hong"]+=1;
        sau đó truy vết, cái nào nhiều nhât và return nó.
    */
    std::map<uint8_t, int> classFreq;
    // cout << "neighbors size="<<neighbors->size()<<endl;
    // cout <<"dddddddd "<<neighbors->size() << endl;
    for (int i = 0; i < neighbors->size(); i++)
    {
        // cout <<"ket qua "<<(int)neighbors->at(i)->get_label()<<endl;
        if (classFreq.find(neighbors->at(i)->get_label()) == classFreq.end())
        {

            // cout << classFreq.find(neighbors->at(i)->get_label())->second<<endl;
            classFreq[neighbors->at(i)->get_label()] = 1;
        }
        else
        {
            classFreq[neighbors->at(i)->get_label()]++;
            // cout << "gia tri tai day ="<< classFreq[neighbors->at(i)->get_label()]<<endl;
        }
    }

    int best = 0;
    int max = 0;
    for (auto kv : classFreq)
    {
        // cout << classFreq.size() << endl;
        if (kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }
    return best;
}
double knn::caculateDistance(data *queryPoint, data *input)
{
    /*
    ý tưởng thuật toán:
    giả sử feature vectowr có n chiều, n chính là size của nó bao quanh điểm đang truy vấn,
    nếu, size của chúng k bằng nhau, ta có đó là 1 ngoại lệ.
    như vậy việc tính tổng distance = (Xtv-Xin)^2 +(Ytv-Yin)^2+(Xtv-Zin)^2....
    trong tv là truy vấn, in là input.
    và căng bậc hai của nó chính là khoảng cách thực tế từ điểm truy vấn đến điểm input
    */
    double distance = 0.0;
    // queryPoint->
    if (queryPoint->get_feature_vector_size() != input->get_feature_vector_size())
    {
        throw "mismatching the size of to point";
    }
#ifdef EUCLID
    for (unsigned i = 0; i < queryPoint->get_feature_vector_size(); i++)
    {
        
        distance += pow(queryPoint->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
    }
#elif defined MANHATTAN
// put ....
#endif
    return sqrt(distance);
}
double knn::validatePerformance()
{
    double currentPerformance = 0;
    int count = 0;
    int dataIndex = 0;
    for (data *itQueryPoint : *validationData)
    {
        findKnearest(itQueryPoint);
        int predict = this->predict();
        // printf("%d -> %d \n", predict, itQueryPoint->get_label());
        if (predict == itQueryPoint->get_label())
        {
            count++;
        }
        dataIndex += 1;
        // printf("current performace =%.3f\n", (double)count * 100 / (double)dataIndex);
    }
    currentPerformance = (double)count * 100.0 / (double)validationData->size();
    printf("validation performace for K= %d :=%.3f \n", k, currentPerformance);
    return currentPerformance;
}
double knn::testPerformance()
{
    double currentPerformance = 0;
    int count = 0;
    for (data *itQueryPoint : *testData)
    {
        findKnearest(itQueryPoint);
        int prediction = predict();
        if (prediction == itQueryPoint->get_label())
        {
            count += 1;
        }
    }
    currentPerformance = (double)count * 100.0 / (double)validationData->size();
    printf("validation performace %.3f\n", currentPerformance);
    return currentPerformance;
}
void knn::getPredict()
{
    size_t testSize = traningData->size();
    int indexRan = rand() % testSize;
    data *dataTest = traningData->at(indexRan);
    findKnearest(dataTest);
    int pred = predict();
    if (dataTest->get_label() != 0)
    {
        double vary = (float)100 * pred / (float)dataTest->get_label();

        printf("do chinh xac %.2f\n", vary);
        cout << "pred=" << pred << " thuc te= " << (int)dataTest->get_label() << endl;
    }
}
int main()
{
    try
    {
        dataHandler *dh = new dataHandler();
        dh->readFeatureVector("../KMEANS/train-images-idx3-ubyte");
        dh->readFeatureLabel("../KMEANS/train-labels-idx1-ubyte");
        dh->splitData();
        dh->countClasses();
        knn *knearest = new knn();
#ifndef NOTWRITE
        vector<int> label;
        for (int i = 0; i < dh->getArrayData()->size(); i++)
        {
            vector<int> tmp;
            label.push_back((int)dh->getArrayData()->at(i)->get_label());
            for (int j = 0; j < dh->getArrayData()->at(i)->get_feature_vector_size(); j++)
            {
                tmp.push_back(dh->getArrayData()->at(i)->get_feature_vector()->at(j));
            }
            dataframe<int> csv(tmp, dh->getRow(), dh->getCol());
            // cout << "_________" << tmp.size() << endl;
            csv.to_csv("./csv/data__" + to_string(i) + ".csv");
            // csv.toImage("./csv/data__" + to_string(i) + ".jpg");
        }
        dataframe<int> csv(label, dh->getArrayData()->size(), 1);
        csv.to_csv(".data_label.csv");
#endif

        knearest->setTrainingData(dh->getTrainingData());
        knearest->setTestData(dh->getTestData());
        knearest->setValidationData(dh->getValidationData());
        knearest->setK(1);
        double performance = 0;
        double bestPerformance = 0;
        int bestK = 1;
        knearest->setK(7);
        // performance = knearest->validatePerformance();
        while (1)
        {
            knearest->getPredict();
        }
    }
    catch (const char *e)
    {
        std::cout << e << std::endl;
    }
    catch (exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}