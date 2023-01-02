#include <bits/stdc++.h>
#include "dice.h"

using namespace std;

array<array<int, 6>, 6> grid = {{
	{57,  33,  132, 268, 492, 732},
	{81,  123, 240, 443, 353, 508},
	{186, 42,  195, 704, 452, 228},
	{-7,  2,   357, 452, 317, 395},
	{5,   23,   -4, 592, 445, 620},
	{0,   77,   32, 403, 337, 452},
}};

Die die;
int score = 0;
pair<int, int> loc = {5, 0};
pair<int, int> endLoc = {0, 5};
vector<Direction> moves = {ROLLUP, ROLLDOWN, ROLLLEFT, ROLLRIGHT};

map<Direction, Direction> reverseMove{
	{ROLLDOWN, ROLLUP},
	{ROLLUP, ROLLDOWN},
	{ROLLLEFT, ROLLRIGHT},
	{ROLLRIGHT, ROLLLEFT},
};

map<Direction, pair<int, int>> locationDiffByMove = {
	{ROLLUP, {-1, 0}},
	{ROLLDOWN, {1, 0}},
	{ROLLLEFT, {0, -1}},
	{ROLLRIGHT, {0, 1}},
};

bool valid(int k){
	return 0 <= k < 6;
}

bool valid(pair<int, int> & l){
	return valid(l.first) && valid(l.second);
}

void performRoll(Direction move){
	pair<int, int> delta = locationDiffByMove[move];
	pair<int, int> newLoc = {loc.first + delta.first, loc.second + delta.second};
	loc = newLoc;
	die.roll(move);
}

void performUnroll(Direction move){
	performRoll(reverseMove[move]);
}

vector<pair<int, int>> path;

bool foundEnd = false;
void backtrack(int turn){
	if(foundEnd) return;
	if(loc == endLoc){
		foundEnd = true;
		return;
	}
	
	for(Direction move : moves){

		performRoll(move);
		path.push_back(loc);
		int gridVal = grid[loc.first][loc.second];
		int topFace = die.sides[TOP];
		bool badMove = false;

		int addedScore = 0;
		if (topFace == EMPTY){
			int diff = gridVal - score;
			addedScore = diff;
			score += diff;
			if(diff % turn != 0){
				badMove = true;
			} else{
				die.setSide(TOP, diff / turn);
			}
		} else{
			addedScore = topFace * turn;
			score += addedScore;
			if(score != gridVal){
				badMove = true;
			}
		}


		if (!badMove && valid(loc)){

			backtrack(turn + 1);
			if(foundEnd) return;
			
		}
		
		path.pop_back();
		score -= addedScore;
		die.setSide(TOP, topFace);
		performUnroll(move);
	}
}

int main(){

	backtrack(1);

	int ans = 0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if(find(path.begin(), path.end(), make_pair(i, j)) == path.end()){
				ans += grid[i][j];
			}
		}
	}

	cout << "Answer: " << ans << endl; 

	return 0;
}

