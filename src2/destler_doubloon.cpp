//
// Created by Darshan Kavathe on 3/27/2018.
//

#include <iomanip>
#include "../src2/destler_doubloon.h"
bool DestlerDoubloon::DEBUG = false;
DestlerDoubloon::DestlerDoubloon(unsigned long long id, double value): id_{id},value_{1}{
    if(DEBUG){std::cout<<*this<<" being created!"<<std::endl;}
}
DestlerDoubloon::~DestlerDoubloon(){
    if(DEBUG){std::cout<<*this<<" being destroyed!"<<std::endl;}
}
bool DestlerDoubloon::operator==(const DestlerDoubloon& other) const{
    return this->id()==other.id();
}

unsigned long long DestlerDoubloon::id() const{
    return id_.to_ullong();
}
double DestlerDoubloon::value() const{
    return this->value_;
}
void DestlerDoubloon::increase_value(double value){
    this->value_+=value;
}
void DestlerDoubloon::decrease_value(double value){
    this->value_-=value;
}
std::ostream& operator<<(std::ostream& os, const DestlerDoubloon& dd){
    os <<"DD: 0x"<<std::hex<<std::uppercase;
    os <<std::setw(16)<<std::setfill('0')<<dd.id()<<std::setfill('0');
    os <<std::nouppercase<<std::dec;
    return os <<", value: "<<dd.value();
}