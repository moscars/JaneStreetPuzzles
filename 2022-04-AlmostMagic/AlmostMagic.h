#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;

struct AlmostMagic {
    vector<int> vec;
    unordered_map<int, ll> hash; // holds three hash values for if it is considered the second, third or forth square
};

ostream & operator<<(std::ostream & os, const AlmostMagic & a);