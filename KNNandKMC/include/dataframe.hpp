#ifndef __DATAFRAME_H
#define __DATAFRAME_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
// #include <opencv2/opencv.hpp>
using namespace std;

template <class T>
class dataframe
{
private:
    int row;
    int col;
    vector<int> *numberCell; //store the all of cell in row
    vector<T> data;
public:
    void read_csv(string fileName);
    dataframe()
    {
        row = col = 0;
        numberCell = new vector<int>;
    }
    dataframe(vector<T> data, int col, int row);
    void to_csv(string outfilename);
    // void toImage(string outfilename) const;
};

#endif