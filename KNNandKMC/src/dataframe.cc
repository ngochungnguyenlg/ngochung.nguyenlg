#include "../include/dataframe.hpp"
// using namespace cv;
template <class T>
void dataframe<T>::read_csv(string fileName)
{
    fstream f;
    data.clear();
    row=0; 
    col=0;
    numberCell->clear();
    f.open(fileName.c_str(), ios::in);
    if (f.fail())
    {
        throw "cannot open file";
    }
    string line;
    string word, temp;

    while (!f.eof())
    {
        row += 1;
        getline(f, line);
        stringstream ss(line);
        ss << line;
        int countMaxCol = 0;
        while (getline(ss, word, ','))
        {
            // if(word.find("\n")!=-1) continue;
            data.push_back((T)word);
            countMaxCol += 1;
        }
        this->numberCell->push_back(countMaxCol);
        if (col < countMaxCol)
        {
            col = countMaxCol;
        }
    }
    f.close();
}
template <class T>
dataframe<T>::dataframe(vector<T> data, int row, int col)
{
    this->data = data;
    this->col = col;
    this->row = row;
    this->numberCell = new vector<int>(row, col);
    // numberCell(col,row);
}
template <class T>
void dataframe<T>::to_csv(string outfilename)
{
    fstream f;
    f.open(outfilename, ios::out);
    if (f.fail())
    {
        throw "ERROR: cannot open file at to_csv";
    }
    int posWrite = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < numberCell->at(i); j++)
        {
            f << data.at(posWrite);
            if (j != numberCell->at(i) - 1)
            {
                f << ",";
            }
            posWrite += 1;
        }
        f << endl;
    }
    f.close();
}
// template <class T>
// void dataframe<T>::toImage(string outfilename) const
// {
//     cv::Mat image = cv::Mat(col, row, 1, CV8U, data);
//     cv::imwrite(outfilename.c_str(), image);
// }
// int main()
// {
//     dataframe<string> a;

//     a.read_csv("datatest.csv");
//     a.to_csv("hung.csv");
// }