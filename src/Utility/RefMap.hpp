#ifndef MAPREF_HH
#define MAPREF_HH
#include <map>
#include<iostream>

template<class A, class B>
class RefMap{
    std::map<A, B> mainMap_;
    RefMap<A, B>* refMap_ = nullptr;
    public:
        
        RefMap<A, B>() {}
        RefMap<A, B>(std::map<A, B>* m): refMap_(m)  {}
        
        void setMap(RefMap<A, B>* m){
            refMap_ = m;
        }
        
        B& operator[](A&& key){
            return mainMap_[key];
        }

         B& get(A&& key){
            if(mainMap_.count(key) == 0){
                if(refMap_ != nullptr || !(refMap_->contains(key))){
                    //
                }
                return (*refMap_).get(key);
            }
            return mainMap_[key];
        }

         B& get(A& key){
            if(mainMap_.count(key) == 0){
                if(refMap_ != nullptr || !(refMap_->contains(key))){
                    //
                }
                return (*refMap_).get(key);
            }
            return mainMap_[key];
        }

        bool contains(A&& key) const{
            return mainMap_.count(key) > 0 || (refMap_ != nullptr && refMap_->contains(key) > 0);
        }

        bool contains(A& key) const{
            return mainMap_.count(key) > 0 || (refMap_ != nullptr && refMap_->contains(key) > 0);
        }
    ~RefMap(){
        // delete refMap_;
    }
};

#endif