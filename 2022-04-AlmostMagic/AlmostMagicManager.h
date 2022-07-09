#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct AlmostMagic;

struct AlmostMagicManager {
    unordered_set<int> usedNums; // holds the numbers that we have filled for quick-lookup
    vector<int> vec; //holds the numbers that we have filled in order
    vector<int> possible; //holds the possible semi-magic numbers that we are currently constrained by
    unordered_set<int> checkLocations; // Locations where we are constrained by what has been placed before to keep the square almost magic
    unordered_map<int, vector<array<int, 3>>> checkProcedure; //Which indicies to sum with to check magicness
    unordered_map<int, array<int, 2>> above;
    vector<AlmostMagic> allFinds;
    unordered_map<int, vector<AlmostMagic>> hashList;
    void addCheckLocations();
    void addCheckProcedure();
    void initVec();
    void initAbove();
    void backtrack(int index);
    void initHashesForAllFound();
    void initAllHashLists();
};
