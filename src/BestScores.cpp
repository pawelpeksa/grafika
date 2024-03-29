#include "BestScores.h"


// score comparision function for sorting
bool BestScores::scoreCompare(const BestScores::score &lhs, const BestScores::score &rhs){ 
    if(std::get<TYPE>(lhs) == std::get<TYPE>(rhs)){
        if(std::get<TYPE>(lhs)>7){
            return std::get<MOVES>(lhs) < std::get<MOVES>(rhs); //sort on moves
        }else{
            return std::get<TIME>(lhs) < std::get<TIME>(rhs); // sort on time
        }
    }else{
        return std::get<TYPE>(lhs) < std::get<TYPE>(rhs); // sort on type
    }
}


// construction
BestScores::BestScores():
    _fileName("BestScores.txt"),
    _changed(false) // flag saying if BestScore list has been changed or not
{
    // load exisiting scores if exists
    _file.open(_fileName.c_str());

    std::string name;
    int time;
    int type;
    int moves;

    // alloc list for every type iterating through the enum
    for(int i=type1_3t; i!=guard; ++i){
        _allBestScores[static_cast<GameTypesEnum>(i)] = new std::list<score>();
    }

    // load from file
    while(_file>>name>>time>>moves>>type){
        GameTypesEnum enumType = static_cast<GameTypesEnum>(type);
        (_allBestScores[static_cast<GameTypesEnum>(type)]) -> push_back(make_tuple(name,time,moves,enumType));
    }
}

// print lists
void BestScores::print(){
    for(int i=type1_3t; i!=guard; ++i){
        std::list<score>* l = (_allBestScores[static_cast<GameTypesEnum>(i)]);
        std::list<score>::const_iterator it;
        for(it = l->cbegin(); it != l->cend(); ++it){
            std::cout<<std::get<NAME>(*it)<<" "<<std::get<TIME>(*it)<<" "<<std::get<MOVES>(*it)<<" "<<std::get<TYPE>(*it)<<std::endl;
        }
    }
}

BestScores::~BestScores(){
    // if antyhing changed in the highestScores
    if(_changed){
        // close file
        _file.close();
        //open file in truncate option in order to clear it
        _file.open(_fileName.c_str(),std::ofstream::trunc | std::ofstream::out);
        // iterate through enum, save best scores and delete lists
        for(int i=type1_3t; i!=guard; ++i){
            std::list<score>* l = (_allBestScores[static_cast<GameTypesEnum>(i)]);
            std::list<score>::const_iterator it;
            // iterate through list with best scores for particular type
            for(it = l->cbegin(); it != l->cend(); ++it){
                // save to file
                _file<<std::get<NAME>(*it)<<" "<<std::get<TIME>(*it)<<" "<<std::get<MOVES>(*it)<<" "<<std::get<TYPE>(*it)<<std::endl;
            }
            // deallock list
            delete l;
        }

    }
    _file.close();
}



void BestScores::addScore(const std::string& name,const int time,const int moves,const GameTypesEnum type){
    //check new high score for particular type
    std::list<BestScores::score>* scores = getScores(type);
    // if there's less then 5 result on the list just add the next one and sort list
    if(scores->size()<5){
        scores->push_back(make_tuple(name,time,moves,type));
        scores->sort(BestScores::scoreCompare);
        _changed=true;
    }else{
        // if there's more then 5 results on the list check the last one and replace with better one if needed, then sort
        BestScores::score score = scores->back();

        if(type<8){
            if(std::get<TIME>(score)>time){
                scores->pop_back();
                scores->push_back(make_tuple(name,time,moves,type));
                scores->sort(BestScores::scoreCompare);
                // swich flag change in order to save new scores in file
                _changed=true;
            }
        }else{
            if(std::get<MOVES>(score)>moves){
                scores->pop_back();
                scores->push_back(make_tuple(name,time,moves,type));
                scores->sort(BestScores::scoreCompare);
                // swich flag change in order to save new scores in file
                _changed=true;
            }
        }

    }
}

bool BestScores::isBestScore(const int time,const int moves,const GameTypesEnum type){
    //check new high score for particular type
    std::list<BestScores::score>* scores = getScores(type);
    // if there's less then 5 result on the list return true
    if(scores->size()<5){
        return true;
    }else{
        // if there's more then 5 results on the list check the last one and replace with better one if needed, then sort
        BestScores::score score = scores->back();

        if(type<8){
            if(std::get<TIME>(score)>time){
                return true;
            }else{
                return false;
            }
        }else{
            if(std::get<MOVES>(score)>moves){
                return true;
            }else{
                return false;
            }
        }

    }
}


// get result for particular type
std::list<BestScores::score>* BestScores::getScores(const GameTypesEnum type){
    return (_allBestScores[type]);
}


