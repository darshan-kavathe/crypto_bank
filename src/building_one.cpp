//
// Created by Darshan Kavathe on 3/27/2018.
//
#include <sstream>
#include <iomanip>
#include "building_one.h"

BuildingOne::BuildingOne():rng_(SEED){
}
void BuildingOne::bull_market(double value){
     for (auto& entry : vault_){
        entry.second.increase_value(value);
     }
}
void BuildingOne::bear_market(double value){
    for (auto& entry : vault_){ // TODO const auto or just auto??
        entry.second.decrease_value(value);
    }
}
void BuildingOne::deposit(DestlerDoubloon&& dd){
    vault_.insert(std::make_pair<unsigned long long, DestlerDoubloon::DestlerDoubloon>(dd.id(),std::move(dd)));
}
void BuildingOne::destroy(unsigned long long id){
        vault_.erase(doubloon(id).id());
}

const DestlerDoubloon& BuildingOne::doubloon(unsigned long long id) const{// TODO print in debug mode
    const std::unordered_map<unsigned long long, DestlerDoubloon>::iterator it = vault_.find(id);
    try {
        if(it != vault_.end()){
            return (*it).second;
        }
        else{
            std::stringstream sstream;
            sstream << "DD: "<<std::hex<<std::setw(16)<<std::setfill('0')<<id<<std::setfill('0')<<" not in vault!";
            throw DDException::DDException(sstream.str());
        }
    }catch(DDException& nd){
        std::cerr<<nd.what()<<std::endl;
    }
}

void BuildingOne::mint(unsigned int num_doubloons) {
    unsigned long long new_id;
    for (int num = 0; num < num_doubloons;) {
         new_id = rng_.rand();
        auto it = vault_.find(new_id);
        auto it2 = withdrawn_ids_.find(new_id);
        if (it == vault_.end() and it2 == withdrawn_ids_.end()) {
            vault_.insert(DestlerDoubloon(new_id, 1)); //TODO
            num++;
        }
    }
}
size_t BuildingOne::num_doubloons() const{
    return vault_.size(); //TODO
}
double BuildingOne::total_worth() const{
    double total_=0;
    for (const auto& entry : vault_){
        total_+=entry.second.value();
    }
    return total_;
}
DestlerDoubloon::DestlerDoubloon BuildingOne::withdraw(unsigned long long id){
    //DestlerDoubloon dd = (std::move(BuildingOne::doubloon(id)));
    //return *(dd);
    //withdrawn_ids_.insert(BuildingOne::doubloon(id).id()); //insert(BuildingOne::doubloon(id));
    const std::unordered_map<unsigned long long, DestlerDoubloon>::iterator it = vault_.find(id);
    try {
        if(it != vault_.end()){
            //std::cout<<"incomplete withdraw!;
            DestlerDoubloon dd = (std::move((*it).second));
            withdrawn_ids_.insert(dd.id());
            BuildingOne::vault_.erase(id);
            return dd;
        }
        else{
            std::stringstream sstream;
            sstream << "DD: "<<std::hex<<std::setw(16)<<std::setfill('0')<<id<<std::setfill('0')<<" not in vault!";
            throw DDException::DDException(sstream.str());
        }
    }catch(DDException& nd){
        std::cerr<<nd.what()<<std::endl;
    }
}
std::ostream& operator<<(std::ostream& os, const BuildingOne::BuildingOne& b1){
    for (auto& entry : b1.vault_){
       os<< entry.second<<std::endl;
    }
}
