#ifndef __DATA_H
#define __DATA_H
#include <vector>
#include <stdint.h>
#include <stdio.h>
using namespace std;
class data
{
    vector<uint8_t> *feature_vector;
    uint8_t label;
    int enum_label;
    double distance;

public:
    data() { this->feature_vector = new vector<uint8_t>; }
    ~data(){};
    void set_feature_vector(vector<uint8_t> *);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enumerated_label(int);

    int get_feature_vector_size();
    uint8_t get_label();
    uint8_t get_enumerated_label();
    vector<uint8_t> *get_feature_vector();
    void setDistance(double val);
    double getDistance() const;
};
#endif