#include <bits/stdc++.h>
#include "twentyfourseven.h"
using namespace std;

TwentyFourSeven::TwentyFourSeven(vector<vector<int>> & preGrid, vector<int> firstOnRow_, vector<int> firstOnCol_){
    n = 7;
    m = 7;
    counts = vector<int>(8, 0);
    locked = vector<vector<bool>>(n, vector<bool>(m, false));
    countsRow = vector<int>(n, 0);
    countsCol = vector<int>(m, 0);
    firstOnRow = firstOnRow_;
    firstOnCol = firstOnCol_;
    firstPlacedOnRow = vector<int>(n, -1);
    firstPlacedOnCol = vector<int>(m, -1);
    sumRow = vector<int>(n, 0);
    sumCol = vector<int>(m, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(preGrid[i][j] != 0){
                locked[i][j] = true;
                counts[preGrid[i][j]]++;
                countsRow[i]++;
                countsCol[j]++;
                sumRow[i] += preGrid[i][j];
                sumCol[j] += preGrid[i][j];
            }
        }
    }
    grid = preGrid;
}

inline vector<pair<int, int>> TwentyFourSeven::twoByTwo(int i, int j){
    return {{i - 1, j - 1}, {i - 1, j}, {i, j - 1}, {i, j}};
}

inline vector<pair<int, int>> TwentyFourSeven::fourNeighbors(int i, int j){
    return {{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}};
}

bool TwentyFourSeven::goodTwoByTwo(int i, int j){
    if(i < 1 || j < 1) return true;
    int countFilled = 0;
    for(auto & p : twoByTwo(i, j)){
        if(grid[p.first][p.second] != 0) countFilled++;
    }
    return countFilled < 4;
}

inline bool TwentyFourSeven::valid(int i, int j){
    return i >= 0 && i < n && j >= 0 && j < m;
}

bool TwentyFourSeven::goodConnectivity(int i){
    for(int j = 0; j < 7; j++){
        if(grid[i][j] == 0) continue;
        vector<pair<int, int>> neighs = fourNeighbors(i, j);
        int countFilled = 0;
        for(auto & p : neighs){
            if(valid(p.first, p.second) && grid[p.first][p.second] != 0) countFilled++;
        }
        if(countFilled == 0) return false;
    }
    return true;
}

pair<int, int> TwentyFourSeven::nextState(int i, int j){
    int nextJ = j + 1;
    int nextI = i;
    if(nextJ == m){
        nextJ = 0;
        nextI++;
    }
    return {nextI, nextJ};
}

void TwentyFourSeven::solve(int i, int j){
    if(i == n){
        if(goodConnectivity(n - 1) 
            && goodConnectivity(n - 2) 
            && sumRow[n - 1] == 20
            && sumCol[m - 1] == 20
            && countsRow[n - 1] == 4
            && countsCol[m - 1] == 4
            && allConnected()
            && confirmEverything()){
            solutions.push_back(grid);
            cout << "Found " << solutions.size() << " solutions" << endl;
        }
        return;
    }
    auto [nextI, nextJ] = nextState(i, j);

    // if we are at the first cell of a row, check that the last row is valid
    if(j == 0 && i > 0 && countsRow[i - 1] != 4) return;
    // check that is has a valid sum
    if(j == 0 && i > 0 && sumRow[i - 1] != 20) return;
    // if we are at the first cell of a column, check that the last column is valid
    if(i == n - 1 && j > 0 && countsCol[j - 1] != 4) return;
    // check that is has a valid sum
    if(i == n - 1 && j > 0 && sumCol[j - 1] != 20) return;
    // if we are at the first cell of a row, check that the last two row is valid with cons
    if(j == 0 && i > 1 && !goodConnectivity(i - 2)) return;

    if(locked[i][j] && goodTwoByTwo(i, j)){
        int oldFirstPlacedOnRow = firstPlacedOnRow[i];
        int oldFirstPlacedOnCol = firstPlacedOnCol[j];
        if(firstPlacedOnRow[i] == -1) firstPlacedOnRow[i] = grid[i][j];
        if(firstPlacedOnCol[j] == -1) firstPlacedOnCol[j] = grid[i][j];

        bool good = true;
        if(firstOnRow[i] != -1 && firstOnRow[i] != firstPlacedOnRow[i]) good = false;
        if(firstOnCol[j] != -1 && firstOnCol[j] != firstPlacedOnCol[j]) good = false;
        if(good)
            solve(nextI, nextJ);
        firstPlacedOnRow[i] = oldFirstPlacedOnRow;
        firstPlacedOnCol[j] = oldFirstPlacedOnCol;
        return;
    } else if(locked[i][j]){
        return;
    }

    for(int num = 0; num <= 7; num++){
        if(num == 0){
            grid[i][j] = 0;
            solve(nextI, nextJ);
            continue;
        }
        grid[i][j] = num;
        counts[num]++;
        countsRow[i]++;
        countsCol[j]++;
        sumRow[i] += num;
        sumCol[j] += num;
        int oldFirstPlacedOnRow = firstPlacedOnRow[i];
        int oldFirstPlacedOnCol = firstPlacedOnCol[j];
        if(firstPlacedOnRow[i] == -1) firstPlacedOnRow[i] = num;
        if(firstPlacedOnCol[j] == -1) firstPlacedOnCol[j] = num;
        if(counts[num] <= num && 
            countsRow[i] <= 4 && 
            countsCol[j] <= 4 && 
            sumRow[i] <= 20   &&
            sumCol[j] <= 20   &&
            goodTwoByTwo(i, j)){
            
            bool good = true;
            if(firstOnRow[i] != -1 && firstOnRow[i] != firstPlacedOnRow[i]) good = false;
            if(firstOnCol[j] != -1 && firstOnCol[j] != firstPlacedOnCol[j]) good = false;

            if(good)
                solve(nextI, nextJ);
        }
        firstPlacedOnRow[i] = oldFirstPlacedOnRow;
        firstPlacedOnCol[j] = oldFirstPlacedOnCol;
        sumRow[i] -= num;
        sumCol[j] -= num;
        counts[num]--;
        countsRow[i]--;
        countsCol[j]--;
        grid[i][j] = 0;
    }
}

bool TwentyFourSeven::allConnected(){
    int startI, startJ;
    startI = 0;
    startJ = 0;
    queue<pair<int, int>> q;
    for(int j = 0; j < 7; j++){
        if(grid[startI][j] != 0){
            startJ = j;
            break;
        }
    }
    q.push({startI, startJ});
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[startI][startJ] = true;
    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        for(auto & p : fourNeighbors(i, j)){
            if(valid(p.first, p.second) && grid[p.first][p.second] != 0 && !visited[p.first][p.second]){
                visited[p.first][p.second] = true;
                q.push(p);
            }
        }
    }
    int countVisited = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] != 0 && visited[i][j]) countVisited++;
        }
    }
    return countVisited == 28;
}

bool TwentyFourSeven::confirmEverything(){
    map<int, int> localCounts;
    map<int, int> localCountsRow;
    map<int, int> localCountsCol;
    map<int, int> localSumRow;
    map<int, int> localSumCol;
    map<int, int> localFirstPlacedOnRow;
    map<int, int> localFirstPlacedOnCol;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] != 0){
                localCounts[grid[i][j]]++;
                localCountsRow[i]++;
                localCountsCol[j]++;
                localSumRow[i] += grid[i][j];
                localSumCol[j] += grid[i][j];
                if(!localFirstPlacedOnRow.count(i)) localFirstPlacedOnRow[i] = grid[i][j];
                if(!localFirstPlacedOnCol.count(j)) localFirstPlacedOnCol[j] = grid[i][j];
            }
        }
    }
    for(int i = 1; i <= 7; i++){
        if(localCounts[i] != i) return false;
    }
    for(int i = 0; i < n; i++){
        if(localCountsRow[i] != 4) return false;
        if(localSumRow[i] != 20) return false;
    }
    for(int j = 0; j < m; j++){
        if(localCountsCol[j] != 4) return false;
        if(localSumCol[j] != 20) return false;
    }
    for(int i = 0; i < n; i++){
        if(firstOnRow[i] != -1 && firstOnRow[i] != localFirstPlacedOnRow[i]) return false;
    }
    for(int j = 0; j < m; j++){
        if(firstOnCol[j] != -1 && firstOnCol[j] != localFirstPlacedOnCol[j]) return false;
    }
    return true;
}