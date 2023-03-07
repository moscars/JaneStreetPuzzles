#include <bits/stdc++.h>
#include "twentyfourseven.h"
using namespace std;

void solveHere(vector<vector<int>> & preGrid, vector<int> firstOnRow, vector<int> firstOnCol){
    TwentyFourSeven tfs(preGrid, firstOnRow, firstOnCol);
    tfs.solve(0, 0);
    for(auto & sol : tfs.solutions){
        for(auto & row : sol){
            for(auto & x : row){
                cout << x << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

inline bool valid(int i, int j, vector<vector<int>> & grid){
    return 0 <= i && i < 12 && 0 <= j && j < 12 && grid[i][j] == 0;
}

set<pair<int, int>> seen;
int dfs(int i, int j, vector<vector<int>> & grid){
    if(seen.count({i, j})) return 0;
    seen.insert({i, j});
    int ans = 0;
    if(valid(i-1, j, grid)) ans += dfs(i - 1, j, grid);
    if(valid(i+1, j, grid)) ans += dfs(i + 1, j, grid);
    if(valid(i, j-1, grid)) ans += dfs(i, j - 1, grid);
    if(valid(i, j+1, grid)) ans += dfs(i, j + 1, grid);
    return ans + 1;
}

int main(){
    // first get all possibilities for the upper left 7x7
    vector<int> firstOnRow = {5, 7, 7, -1, -1, 2, -1};
    vector<int> firstOnCol = {6, -1, -1, -1, -1, 3, -1};
    vector<vector<int>> preGridUpperLeft = 
    {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0},
        {0, 4, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0},
        {0, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
    };
    //solveHere(preGridUpperLeft, firstOnRow, firstOnCol);

    // then get all possibilities for the upper right 7x7
    firstOnRow = {4, -1, -1, 1, -1, -1, -1};
    firstOnCol = {-1, -1, -1, -1, -1, -1, -1};
    vector<vector<int>> preGridUpperRight = 
    {
        {0, 7, 0, 0, 0, 0, 0},
        {0, 5, 6, 0, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 3},
        {0, 0, 0, 7, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0},
        {0, 0, 7, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
    };
    //solveHere(preGridUpperRight, firstOnRow, firstOnCol);

    // Only one combination of the two upper 7x7s work
    // now get the lower left 7x7
    firstOnRow = {-1, -1, -1, -1, -1, -1, -1};
    firstOnCol = {-1, -1, -1, 4, -1, -1, 6};
    vector<vector<int>> preGridLowerLeft = 
    {
        {0, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 6, 0},
        {0, 7, 0, 0, 0, 5, 0},
        {0, 5, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 7, 0, 4, 4, 5},
        {0, 0, 6, 6, 6, 0, 2},
    };
    //solveHere(preGridLowerLeft, firstOnRow, firstOnCol);
    firstOnRow = {-1, -1, -1, -1, -1, -1, -1};
    firstOnCol = {-1, -1, -1, -1, -1, -1, -1};

    // Finaly get the lower right 7x7
    vector<vector<int>> preGridLowerRight = 
    {
        {0, 0, 6, 3, 7, 0, 4},
        {0, 0, 7, 0, 6, 2, 5},
        {5, 7, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0},
        {7, 2, 0, 0, 0, 0, 0},
        {0, 4, 0, 0, 0, 0, 0},
        {3, 7, 0, 0, 0, 0, 0},
    };
    //solveHere(preGridLowerRight, firstOnRow, firstOnCol);
    // And check the last two constraints to find the correct one

    // The final grid becomes
    vector<vector<int>> finalGrid = {
        {0, 5, 0, 6, 0, 3, 6, 0, 0, 0, 7, 4},
        {0, 7, 7, 1, 0, 0, 5, 0, 4, 6, 5, 0},
        {0, 0, 0, 7, 5, 3, 5, 0, 6, 0, 6, 0},
        {6, 4, 3, 0, 0, 7, 0, 5, 7, 1, 0, 0},
        {7, 0, 0, 0, 2, 7, 4, 2, 0, 0, 0, 7},
        {2, 0, 6, 6, 6, 0, 0, 6, 3, 7, 0, 4},
        {5, 4, 4, 0, 7, 0, 0, 7, 0, 6, 2, 5},
        {7, 0, 0, 0, 1, 5, 7, 1, 0, 0, 7, 0},
        {0, 5, 3, 7, 0, 5, 0, 0, 5, 0, 4, 6},
        {6, 5, 0, 0, 0, 7, 2, 0, 6, 0, 0, 5},
        {0, 6, 7, 3, 0, 0, 4, 6, 6, 4, 0, 0},
        {0, 0, 0, 4, 6, 3, 7, 0, 0, 3, 7, 0},
    };

    int ans = 1;
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            if(finalGrid[i][j] == 0 && !seen.count({i, j})){
                ans *= dfs(i, j, finalGrid);
            }
        }
    }
    cout << ans << endl;
    return 0;
}