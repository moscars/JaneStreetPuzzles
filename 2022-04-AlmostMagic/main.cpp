#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include "AlmostMagicManager.h"
#include "AlmostMagic.h"

using namespace std;
const char nl = '\n';
using ll = long long;
const int INF = (int) 1e9;
unordered_set<int> usedNums;
AlmostMagicManager m;
int bestScore;
AlmostMagic bestFirst;
AlmostMagic bestSecond;
AlmostMagic bestThird;
AlmostMagic bestForth;
vector<AlmostMagic *> previous;

bool check(const AlmostMagic & a){
    vector<int> sums(8, 0);
    sums[0] = a.vec[0] + a.vec[1] + a.vec[2]; // row 1
    sums[1] = a.vec[3] + a.vec[4] + a.vec[5]; // row 2
    sums[2] = a.vec[6] + a.vec[7] + a.vec[8]; // row 3
    sums[3] = a.vec[0] + a.vec[3] + a.vec[6]; // col 1
    sums[4] = a.vec[1] + a.vec[4] + a.vec[7]; // col 2
    sums[5] = a.vec[2] + a.vec[5] + a.vec[8]; // col 3
    sums[6] = a.vec[0] + a.vec[4] + a.vec[8]; // diag 1
    sums[7] = a.vec[2] + a.vec[4] + a.vec[6]; // diag 2
    int smallest = *min_element(sums.begin(), sums.end());
    int largest = *max_element(sums.begin(), sums.end());

    return smallest + 1 == largest || smallest == largest;
}

bool confirmMatchingEdges(const AlmostMagic & first, const AlmostMagic & second, const AlmostMagic & third, const AlmostMagic & forth){
    return first.vec[5] == second.vec[0] && first.vec[8] == second.vec[3] && 
    first.vec[6] == third.vec[1] && first.vec[7] == third.vec[2] && third.vec[5] == forth.vec[0] && 
    third.vec[8] == forth.vec[3] && second.vec[6] == forth.vec[1] && second.vec[7] == forth.vec[2];
}

int score(const AlmostMagic & forth){
    assert(previous.size() == 3);
    int score = 0;
    for(int i = 0; i < 9; i++){
        score += previous[0]->vec[i];
        score += forth.vec[i];
    }
    score += previous[1]->vec[1] + previous[1]->vec[2] + previous[1]->vec[4] + previous[1]->vec[5] + previous[1]->vec[8];
    score += previous[2]->vec[0] + previous[2]->vec[3] + previous[2]->vec[4] + previous[2]->vec[6] + previous[2]->vec[7];
    return score;
}

ll getGoal(int index){
    if (index == 2){
        assert(previous.size() == 1);
        return previous[0]->vec[5] * 1000 + previous[0]->vec[8];
    }
    if(index == 3){
        assert(previous.size() == 2);
        return previous[0]->vec[6] * 1000 + previous[0]->vec[7];
    }
    if(index == 4){
        assert(previous.size() == 3);
        return previous[2]->vec[5] * 10000000 + previous[1]->vec[6] * 100000 + previous[1]->vec[7] * 1000 + previous[2]->vec[8];
    }
    assert(false);
}

bool checkBad(AlmostMagic & a, int squareIndex){
    for(int i = 0; i < 9; i++){
        if(squareIndex == 2 && (i == 0 || i == 3)){
            continue;
        }
        else if(squareIndex == 3 && (i == 1 || i == 2)){
            continue;
        }
        else if(squareIndex == 4 && (i == 0 || i == 1 || i == 2 || i == 3)){
            continue;
        }
        if(usedNums.count(a.vec[i])){
            return true;
        }
    }
    return false;
}

void eraseCorrect(AlmostMagic & a, int squareIndex){
    for(int i = 0; i < 9; i++){
        if(squareIndex == 2 && (i == 0 || i == 3)){
            continue;
        }
        else if(squareIndex == 3 && (i == 1 || i == 2)){
            continue;
        }
        else if(squareIndex == 4 && (i == 0 || i == 1 || i == 2 || i == 3)){
            continue;
        }
        usedNums.erase(a.vec[i]);
    }
}

string commaSeparated(const AlmostMagic & first, const AlmostMagic & second, const AlmostMagic & third, const AlmostMagic & forth){
    vector<string> fv; for(auto & num : first.vec) fv.push_back(to_string(num));
    vector<string> sv; for(auto & num : second.vec) sv.push_back(to_string(num));
    vector<string> tv; for(auto & num : third.vec) tv.push_back(to_string(num));
    vector<string> fov; for(auto & num : forth.vec) fov.push_back(to_string(num));
    string s;
    for(int i = 0; i <= 5; i++){
        s += fv[i] + ",";
    }
    s += sv[1] + ",";
    s += sv[2] + ",";
    for(int i = 0; i <= 2; i++){
        s += tv[i] + ",";
    }
    for(int i = 3; i <= 5; i++){
        s += sv[i] + ",";
    }
    for(int i = 3; i <= 5; i++){
        s += tv[i] + ",";
    }
    for(int i = 6; i <= 8; i++){
        s += sv[i] + ",";
    }
    for(int i = 6; i <= 8; i++){
        s += tv[i] + ",";
    }
    for(int i = 4; i < 9; i++){
        s += fov[i] + ",";
    }
    s.pop_back();
    return s;
}

// Backtracks to find all possible solutions given our found squares
// Able to binary search since the squares are sorted with respect the numbers that they have
// in the locations that depends on the previous squares
void binarySearchNext(int squareIndex){
    int l = 0;
    int r = m.hashList[squareIndex].size() - 1;
    ll goalSearch = getGoal(squareIndex);
    while(l <= r){
        int mid = (l + r) / 2;
        if (m.hashList[squareIndex][mid].hash[squareIndex] == goalSearch && (mid == 0 || m.hashList[squareIndex][mid-1].hash[squareIndex] != goalSearch)){
            for(int j = mid; j < m.hashList[squareIndex].size() && m.hashList[squareIndex][j].hash[squareIndex] == goalSearch; j++){
                AlmostMagic next = m.hashList[squareIndex][j];

                if(checkBad(next, squareIndex)) continue;
                
                if(squareIndex == 4){
                    if(check(*previous[0]) && check(*previous[1]) && check(*previous[2]) && check(next) && confirmMatchingEdges(*previous[0], *previous[1], *previous[2], next)){
                        int points = score(next);
                        if(points < bestScore){
                            bestFirst = *previous[0];
                            bestSecond = *previous[1];
                            bestThird = *previous[2];
                            bestForth = next;
                            bestScore = points;
                        }
                    }
                }
                for(int i = 0; i < 9; i++) usedNums.insert(next.vec[i]);
                if(squareIndex < 4){
                    previous.push_back(&next);
                    assert(previous.size() == squareIndex);
                    binarySearchNext(squareIndex + 1);
                    assert(previous.size() == squareIndex);
                    previous.pop_back();
                }
                eraseCorrect(next, squareIndex);
            }
            break;
        } else if(m.hashList[squareIndex][mid].hash[squareIndex] >= goalSearch){
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    cout << "Starting search for almost magic 3x3 squares" << endl;

    m.addCheckLocations();
    m.addCheckProcedure();
    m.initVec();
    m.initAbove();
    m.backtrack(0);
    m.initHashesForAllFound();
    m.initAllHashLists();

    cout << "Found " << m.allFinds.size() << " squares" << endl;

    cout << "Starting search for 4 matching squares" << endl;
    
    bestScore = INF;
    for(int i = 0; i < m.allFinds.size(); i++){
        AlmostMagic first = m.allFinds[i];
        for(int num : first.vec) usedNums.insert(num);
        previous.push_back(&first);
        binarySearchNext(2);
        previous.pop_back();
        for(int num : first.vec) usedNums.erase(num);
    }

    cout << "Best score: " << bestScore << endl;
    if(bestScore != INF){
        cout << bestFirst << endl;
        cout << bestSecond << endl;
        cout << bestThird << endl;
        cout << bestForth << endl;
        cout << "Code: " << commaSeparated(bestFirst, bestSecond, bestThird, bestForth) << endl; 
    }
    

	return 0;
}

