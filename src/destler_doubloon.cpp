//
// Created by Darshan Kavathe on 3/27/2018.
//

#include <iomanip>
#include "destler_doubloon.h"

DestlerDoubloon::DestlerDoubloon(unsigned long long id, double value): id_{id},value{1}{
    //whats use of passing value parameter to constructor if we make only coin of value 1
    if(DestlerDoubloon::DEBUG){std::cout<<this<<" being created";}
}
DestlerDoubloon::~DestlerDoubloon(){
    if(DEBUG){std::cout<<this<<" being destroyed";}
}
DestlerDoubloon::DestlerDoubloon(DestlerDoubloon::DestlerDoubloon&& other): id_{other.id_},value_{other.value_}{
    other.id_ = 0; // NULL or 0??
    other.value_=0;
    if(DEBUG){std::cout<<this<<" moved from "<<other;}
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

std::ostream& operator<<(std::ostream& os, const DestlerDoubloon::DestlerDoubloon& dd){
    os <<"DD: "<<std::hex<<std::setw(16)<<std::setfill('0')<<dd.id()<<std::setfill('0');
    return os <<", value: "<<dd.value()<<std::endl;
}