//
// Created by Darshan Kavathe on 3/27/2018.
//
#include <sstream>
#include <iomanip>
#include "building_one.h"
#include <memory>
BuildingOne::BuildingOne():rng_(SEED),vault_(),withdrawn_ids_(){
    vault_.clear();
    withdrawn_ids_.clear();
}

void BuildingOne::bull_market(double value){
     for (auto& entry : vault_){
        entry.second ->increase_value(value);
     }
}
void BuildingOne::bear_market(double value){
    for (auto& entry : vault_){
        entry.second->decrease_value(value);
    }
}
void BuildingOne::deposit(std::unique_ptr< DestlerDoubloon > dd){
    withdrawn_ids_.erase(dd->id());
    vault_.emplace(dd->id(),std::move(dd));
}
void BuildingOne::destroy(unsigned long long id){
        vault_.erase(doubloon(id).id());
}

const DestlerDoubloon& BuildingOne::doubloon(unsigned long long id) const{
    //check if id exist in vault
    auto it = vault_.find(id);
    if(it != vault_.end()){
            return *((*it).second);
    }
    else{
        std::stringstream sstream;
        sstream << "DD: 0x"<<std::uppercase<<std::hex<<std::setw(16)<<std::setfill('0')<<id<<std::setfill('0')<<" not in vault!"<<std::noshowbase<<std::nouppercase<<std::dec;
        throw DDException(sstream.str());
    }
}

void BuildingOne::mint(unsigned int num_doubloons) {
    unsigned long long new_id;
    for (unsigned int num = 0; num < num_doubloons;) {
        //get new random doubloon id
        new_id = rng_.rand();
        // check if id is unique
        auto it = vault_.find(new_id);
        auto it2 = withdrawn_ids_.find(new_id);
        if (it == vault_.end() and it2 == withdrawn_ids_.end()) {
            DestlerDoubloon* dx = new DestlerDoubloon (new_id,1);
            vault_.emplace(new_id,std::unique_ptr<DestlerDoubloon>(dx));
            num++;
        }
    }
}

size_t BuildingOne::num_doubloons() const{
    return vault_.size();
}

double BuildingOne::total_worth() const{
    double total_=0;
    //iterate over each doubloon to sum up
    for (const auto& entry : vault_){
        total_+=entry.second->value();
    }
    return total_;
}

std::unique_ptr< DestlerDoubloon > BuildingOne::withdraw(unsigned long long id){
    // check if doubloon is in vault
    auto it = vault_.find(id);
    if(it == vault_.end()){
        std::stringstream sstream;
        sstream << "DD: 0x"<<std::uppercase<<std::hex<<std::setw(16)<<std::setfill('0')<<id<<std::setfill('0')<<" not in vault!"<<std::noshowbase<<std::nouppercase<<std::dec;
        throw DDException(sstream.str());
    }
    auto p = std::move(((*it).second));
    withdrawn_ids_.insert(id);
    BuildingOne::vault_.erase(id);
    return p;
}
std::ostream& operator<<(std::ostream& os, const BuildingOne& b1){
    for (auto& entry : b1.vault_){
        // print doubloon in vault
       os<< *(entry.second)<<std::endl;
    }
    return os;
}
