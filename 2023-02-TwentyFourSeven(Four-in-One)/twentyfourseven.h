#include <bits/stdc++.h>
using namespace std;

struct TwentyFourSeven{
    vector<vector<bool>> locked;
    vector<vector<int>> grid;
    vector<int> countsRow;
    vector<int> sumRow;
    vector<int> countsCol;
    vector<int> sumCol;
    vector<int> counts;
    vector<int> firstOnRow;
    vector<int> firstOnCol;
    vector<int> firstPlacedOnRow;
    vector<int> firstPlacedOnCol;
    vector<vector<vector<int>>> solutions;
    int n, m;

    TwentyFourSeven(vector<vector<int>> & preGrid, vector<int> firstOnRow_, vector<int> firstOnCol_);

    inline vector<pair<int, int>> twoByTwo(int i, int j);
    inline vector<pair<int, int>> fourNeighbors(int i, int j);
    bool goodTwoByTwo(int i, int j);
    inline bool valid(int i, int j);

    bool goodConnectivity(int i);
    pair<int, int> nextState(int i, int j);

    void solve(int i, int j);
    bool allConnected();
    bool confirmEverything();
};