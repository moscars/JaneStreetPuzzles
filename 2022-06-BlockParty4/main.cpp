#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int N = 10;
bool foundSolution = false;

vector<vector<int>> grid(N, vector<int>(N, 0));
set<pair<int, int>> unMovable;
map<pair<int, int>, int> locToRegion;
unordered_map<int, unordered_set<int>> usedInRegion;
unordered_map<int, set<pair<int, int>>> numLocations;
unordered_map<int, int> regionSize;

void initUnMovable() {
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(grid[i][j] != 0){
				unMovable.insert({i, j});
			}
		}
	}
}

void init(){
	
	grid[4][0] = 6;
	grid[0][1] = 3;
	grid[7][1] = 2;
	grid[4][2] = 1;
	grid[1][3] = 4;
	grid[3][3] = 1;
	grid[9][4] = 5;
	grid[0][5] = 7;
	grid[6][6] = 2;
	grid[8][6] = 6;
	grid[5][7] = 3;
	grid[2][8] = 2;
	grid[9][8] = 2;
	grid[5][9] = 6;

	//ones
	grid[5][1] = 1;
	grid[5][4] = 1;
	grid[4][6] = 1;
	grid[7][5] = 1;
	grid[5][6] = 1;
	grid[7][2] = 1;
	grid[6][2] = 2;
}

void initLocToRegion(){
	//First
	for(int i = 0; i < 7; i++){
		locToRegion[{i, 0}] = 1;
	}
	for(int i = 1; i < 4; i++){
		locToRegion[{i, 1}] = 1;
	}
	//Second
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			locToRegion[{i, j + i + 1}] = 2;
		}
	}
	//Third
	for(int j = 4; j < 10; j++){
		locToRegion[{0, j}] = 3;
	}
	locToRegion[{1, 5}] = 3;
	locToRegion[{1, 8}] = 3;
	locToRegion[{1, 9}] = 3;
	//Forth
	locToRegion[{2, 2}] = 4;
	locToRegion[{2, 3}] = 4;
	locToRegion[{3, 3}] = 4;
	//Fifth
	locToRegion[{2, 4}] = 5;
	locToRegion[{2, 5}] = 5;
	//Sixth
	locToRegion[{1, 6}] = 6;
	locToRegion[{1, 7}] = 6;
	locToRegion[{2, 7}] = 6;
	//Seventh
	for(int i = 3; i < 6; i++){
		locToRegion[{i, 2}] = 7;
	}
	locToRegion[{4, 1}] = 7;
	//Eighth
	locToRegion[{4, 3}] = 8;
	locToRegion[{4, 4}] = 8;
	locToRegion[{3, 4}] = 8;
	//Nineth
	for(int j = 5; j < 9; j++){
		locToRegion[{3, j}] = 9;
	}
	locToRegion[{2, 6}] = 9;
	locToRegion[{4, 7}] = 9;
	locToRegion[{4, 8}] = 9;
	//Tenth
	for(int i = 2; i < 6; i++){
		for(int j = 8; j < 10; j++){
			if(i == 4 && j == 8){
				continue;
			}
			locToRegion[{i, j}] = 10;
		}
	}
	//Eleventh
	for(int i = 7; i < 10; i++){
		for(int j = 0; j < 2; j++){
			locToRegion[{i, j}] = 11;
		}
	}
	locToRegion[{6, 1}] = 11;
	locToRegion[{8, 2}] = 11;
	locToRegion[{9, 2}] = 11;
	locToRegion[{9, 3}] = 11;
	//Twelfth
	for(int j = 3; j < 6; j++){
		locToRegion[{6, j}] = 12;
	}
	locToRegion[{5, 3}] = 12;
	locToRegion[{7, 4}] = 12;
	//Thirteenth
	locToRegion[{4, 5}] = 13;
	locToRegion[{5, 5}] = 13;
	//Fourteenth
	for(int j = 7; j < 10; j++){
		locToRegion[{6, j}] = 14;
	}
	//Fifteenth
	locToRegion[{7, 3}] = 15;
	locToRegion[{8, 3}] = 15;
	locToRegion[{8, 4}] = 15;
	locToRegion[{9, 4}] = 15;
	locToRegion[{9, 5}] = 15;
	//Sixteenth
	for(int i = 7; i < 10; i++){
		for(int j = 6; j < 10; j += 3){
			locToRegion[{i, j}] = 16;
		}
	}
	locToRegion[{8, 5}] = 16;
	locToRegion[{9, 7}] = 16;
	locToRegion[{9, 8}] = 16;
	//Seventeenth
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			locToRegion[{i + 7, j + 7}] = 17;
		}
	}
}

void print(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << grid[i][j] << (grid[i][j] >= 10 ? " " : "  ");
		}
		cout << endl;
	}
}

void initUsedInRegion(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(locToRegion.count({i, j})){
				if(unMovable.count({i, j})){
					usedInRegion[locToRegion[{i, j}]].insert(grid[i][j]);
				}
			}
		}
	}
}

void initNumLocations(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(grid[i][j] != 0){
				numLocations[grid[i][j]].insert({i, j});
			}
		}
	}
}

void initRegionSize(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(locToRegion.count({i, j})){
				regionSize[locToRegion[{i, j}]]++;
			}
		}
	}
}

int findClosest(int num, int ii, int jj){
	int closest = INT_MAX;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(i == ii && j == jj) continue;
			if(grid[i][j] == num){
				closest = min(closest, abs(i - ii) + abs(j - jj));
			}
		}
	}
	return closest;
}

bool checkSolution(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(findClosest(grid[i][j], i, j) != grid[i][j]){
				return false;
			}
		}
	}
	return true;
}

int getResult(vector<vector<int>> & res){
	int tot = 0;
	for(int i = 0; i < N; i++){
		int row = res[i][0];
		for(int j = 1; j < N; j++){
			row *= res[i][j];
		}
		tot += row;
	}
	return tot;
}

int bestThusFar = 0;
void backTrack(int index){
	if(foundSolution) return;
	if(index > bestThusFar){
		cout << "Best index found : " << index << endl;
		bestThusFar = index;
 	}

	if(index == N * N){
		if(checkSolution()){
			foundSolution = true;
			print();
			cout << "Result: " << getResult(grid) << endl;
		} 
		return;
	}

	int i = index / N;
	int j = index % N;
	if(unMovable.count({i, j})){
		backTrack(index + 1);
		return;
	}

	int region = locToRegion[{i, j}];
	int size = regionSize[region];

	for(int num = 1; num <= size; num++){
		if(usedInRegion[region].count(num)){
			continue;
		}
		bool possible = true;
		for(auto & otherLoc : numLocations[num]){
			int otherI = otherLoc.first;
			int otherJ = otherLoc.second;
			if(abs(i - otherI) + abs(j - otherJ) < num){
				possible = false;
				break;
			}
		}

		if(possible){
			grid[i][j] = num;
			usedInRegion[region].insert(num);
			numLocations[num].insert({i, j});
			backTrack(index + 1);
			grid[i][j] = 0;
			numLocations[num].erase({i, j});
			usedInRegion[region].erase(num);
		}
	}
}

int main(){
	init();
	initUnMovable();
	initLocToRegion();
	initUsedInRegion();
	initNumLocations();
	initRegionSize();
	backTrack(0);

	return 0;
}

