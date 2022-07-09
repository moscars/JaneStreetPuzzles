#include "AlmostMagicManager.h"
#include "AlmostMagic.h"
#include <assert.h>
#include <algorithm>

void AlmostMagicManager::addCheckLocations(){
    checkLocations.insert(2);
    checkLocations.insert(5);
    checkLocations.insert(6);
    checkLocations.insert(7);
    checkLocations.insert(8);
}

void AlmostMagicManager::addCheckProcedure(){
    checkProcedure[2] = {{0, 1, 2}};
    checkProcedure[5] = {{3, 4, 5}};
    checkProcedure[6] = {{2, 4, 6}, {0, 3, 6}};
    checkProcedure[7] = {{1, 4, 7}};
    checkProcedure[8] = {{0, 4, 8}, {2, 5, 8}, {6, 7, 8}};
}

void AlmostMagicManager::initVec(){
    for(int i = 0; i < 9; i++){
        vec.push_back(0);
    }
}

void AlmostMagicManager::initAbove(){
    above[5] = {3, 4};
    above[6] = {3, 0};
    above[7] = {4, 1};
    above[8] = {5, 2};
}

// Finds all possible almost magic 3x3 squares constrained by start and finish
void AlmostMagicManager::backtrack(int index){
    int start = 1; // minimum number allowed in the square
    int finish = 40; // maximum number allowed in the square
    if(above.count(index)){
        assert(possible.size() > 0);
        int goal = possible[0];
        assert(goal > 0);
        int sumThusFar = vec[above[index][0]] + vec[above[index][1]];
        int left = goal - sumThusFar;
        if(left <= -1)
            return;
        start = max(left - 1, start);
        finish = min(left + 1, finish);
    }

    for(int i = start; i <= finish; i++){
        if(!usedNums.count(i)){
            vec[index] = i;
            usedNums.insert(i);
            bool bad = false;
            bool added = false;

            if(checkLocations.count(index)){
                auto procedures = checkProcedure[index];
                for(auto prod : procedures){
                    int sum = vec[prod[0]] + vec[prod[1]] + vec[prod[2]];
                    if(possible.size() == 0){
                        possible.push_back(sum);
                        added = true;
                    } else if (possible.size() == 1){
                        if(abs(possible[0] - sum) <= 1){
                            possible.push_back(sum);
                            added = true;
                        } else{
                            bad = true;
                            break;
                        }
                    } else{
                        if(sum != possible[0] && sum != possible[1]){
                            bad = true;
                            break;
                        }
                    }
                }   
            }
            if(!bad && index == 8){
                AlmostMagic m;
                for(int val : vec) m.vec.push_back(val);
                allFinds.push_back(m);
            }
            else if(!bad){
                backtrack(index + 1);
            }
            if(added && (index == 2 || index == 5)){
                possible.pop_back();
            }
            usedNums.erase(i);
            vec[index] = 0;
        }
    }
}

void AlmostMagicManager::initHashesForAllFound(){
    for(int i = 0; i < allFinds.size(); i++){
        allFinds[i].hash[2] = allFinds[i].vec[0] * 1000 + allFinds[i].vec[3];
        allFinds[i].hash[3] = allFinds[i].vec[1] * 1000 + allFinds[i].vec[2];
        allFinds[i].hash[4] = allFinds[i].vec[0] * 10000000 + allFinds[i].vec[1] * 100000 + allFinds[i].vec[2] * 1000 + allFinds[i].vec[3];
    }
}

// makes three lists of the squares that we have found and sorts them by the hash values
// in order to prepares the squares for binary search
void AlmostMagicManager::initAllHashLists(){
    for(int i = 0; i < allFinds.size(); i++){
        hashList[2].push_back(allFinds[i]);
        hashList[3].push_back(allFinds[i]);
        hashList[4].push_back(allFinds[i]);
    }

    for(int i = 2; i <= 4; i++){
        sort(hashList[i].begin(), hashList[i].end(), [i](const AlmostMagic & a, const AlmostMagic & b){
            return a.hash.at(i) < b.hash.at(i);
        });
    }
}

ostream & operator<<(ostream & os, const AlmostMagic & a){
    for(int i = 0; i < 9; i++){
        os << a.vec[i] << " ";
        if(i == 2 || i == 5) os << "\n";
    }
    cout << "\n";
    return os;
}