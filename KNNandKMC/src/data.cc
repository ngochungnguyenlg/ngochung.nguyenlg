#include "data.hpp"
void data::set_feature_vector(vector<uint8_t> *vect){
    feature_vector=vect;
}
void data::append_to_feature_vector(uint8_t val){
    feature_vector->push_back(val);
}
void data::set_label(uint8_t val){
    this->label=val;
}
void data::set_enumerated_label(int val){
    this->enum_label=val;
}

int data::get_feature_vector_size(){
    return this->feature_vector->size();
}
uint8_t data::get_label(){
    return this->label;
}
uint8_t data::get_enumerated_label(){
    return this->enum_label;
}
vector<uint8_t> *data::get_feature_vector(){
    return feature_vector;
}
void data::setDistance(double val){
    this->distance=val;
}
double data::getDistance() const{
    return distance;
}