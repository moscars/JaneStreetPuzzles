#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <unordered_map>
#include <set>

void printBoard(const std::vector<std::vector<int>> & v){
    for(auto i : v){
        for(auto j : i){
            std::string s = std::to_string(j);
            if(j < 10){
                std::cout << "";
            } 
            if(j == -1){
                s = ".";
            }
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

const int GRIDSIZE = 9;
const int TOTALNEEDED = GRIDSIZE * (GRIDSIZE + 1) / 2;
std::vector<std::vector<int>> grid(GRIDSIZE, std::vector<int>(GRIDSIZE, -1));
std::vector<std::vector<std::vector<int>>> Ls;
std::vector<std::vector<int>> LGen(GRIDSIZE, std::vector<int>(GRIDSIZE, -1));
std::vector<std::pair<int, int>> order; // order to place the numbers (start by placing near helpers since those rule out the most)
std::vector<std::vector<int>> LCurr;
std::vector<int> currCount(GRIDSIZE + 1, 0);
std::vector<int> currL(GRIDSIZE + 1, 0);

std::vector<std::vector<int>> helpers = {
    {-1, 18, -1, -1, -1, -1,  7, -1, -1},
    {-1, -1, -1, -1, 12, -1, -1, -1, -1},
    {-1, -1,  9, -1, -1, -1, -1, 31, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1,  5, -1, 11, -1, 22, -1, 22, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1,  9, -1, -1, -1, -1, 19, -1, -1},
    {-1, -1, -1, -1, 14, -1, -1, -1, -1},
    {-1, -1, 22, -1, -1, -1, -1, 15, -1},
};

bool inGrid(int i, int j){
    return i >= 0 && i < GRIDSIZE && j >= 0 && j < GRIDSIZE;
}

std::vector<std::pair<int, int>> getOrder() {
    std::vector<std::pair<int, int>> order_;
    std::set<std::pair<int, int>> orderSet;
    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(helpers[i][j] != -1){
                std::vector<std::pair<int, int>> neighs = {
                    {i-1, j},
                    {i+1, j},
                    {i, j-1},
                    {i, j+1},
                };

                for(auto & [ii, jj] : neighs){
                    if(inGrid(ii, jj) && !orderSet.count({ii, jj})){
                        order_.push_back({ii, jj});
                        orderSet.insert({ii, jj});
                    }
                }
            }
        }
    }

    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(helpers[i][j] == -1 && !orderSet.count({i, j})){
                order_.push_back({i, j});
            }
        }
    }
    return order_;
}

std::vector<std::pair<int, int>> dirs = {
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
};

void generateLs(int size){
    if(size == 0){
        Ls.push_back(LGen);
        return;
    }

    for(size_t di = 0; di < dirs.size(); di++){
        std::pair<int, int> p1 = dirs[di];

        for(int i = 0; i < GRIDSIZE; i++){
            for(int j = 0; j < GRIDSIZE; j++){
                // check that all is clear
                bool clear = true;
                for(int k = 0; k < size; k++){
                    int ii = i + p1.first * k;
                    int jj = j + p1.second * k;
                    if(!inGrid(ii, jj) || LGen[ii][j] != -1 || LGen[i][jj] != -1){
                        clear = false;
                        break;
                    }
                }
                if(!clear){
                    continue;
                }

                // place the L
                for(int k = 0; k < size; k++){
                    int ii = i + p1.first * k;
                    int jj = j + p1.second * k;
                    LGen[ii][j] = size;
                    LGen[i][jj] = size;
                }

                generateLs(size - 1);

                // remove the L
                for(int k = 0; k < size; k++){
                    int ii = i + p1.first * k;
                    int jj = j + p1.second * k;
                    LGen[ii][j] = -1;
                    LGen[i][jj] = -1;
                }
            }
        }

        if(size == 1){
            break;
        }
    }
}

bool checkHelper(int i, int j){
    assert(inGrid(i, j));
    assert(helpers[i][j] != -1);

    int sum = 0;

    std::vector<std::pair<int, int>> neighs = {
        {i-1, j},
        {i, j-1},
        {i, j+1},
        {i+1, j},
    };

    for(auto & [ii, jj] : neighs){
        if(inGrid(ii, jj) && grid[ii][jj] != -1){
            sum += grid[ii][jj];
        }
    }
    return sum == helpers[i][j];
}

bool checkFinalGood(){
    for(int num = 1; num <= GRIDSIZE; num++){
        if(currCount[num] != num){
            return false;
        }
    }
    return true;
}

bool checkAllConnected(){
    std::vector<std::vector<bool>> visited(GRIDSIZE, std::vector<bool>(GRIDSIZE, false));
    // find first non -1
    std::pair<int, int> start = {-1, -1};
    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(grid[i][j] != -1){
                start = {i, j};
                break;
            }
        }
        if(start.first != -1){
            break;
        }
    }

    // do dfs from start
    std::vector<std::pair<int, int>> stack = {start};
    while(!stack.empty()){
        auto [i, j] = stack.back();
        stack.pop_back();
        if(visited[i][j]){
            continue;
        }
        visited[i][j] = true;

        std::vector<std::pair<int, int>> neighs = {
            {i-1, j},
            {i, j-1},
            {i, j+1},
            {i+1, j},
        };

        for(auto & [ii, jj] : neighs){
            if(inGrid(ii, jj) && grid[ii][jj] != -1){
                stack.push_back({ii, jj});
            }
        }
    }

    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(grid[i][j] != -1 && !visited[i][j]){
                return false;
            }
        }
    }
    return true;
}

int dfs(int i, int j, std::vector<std::vector<bool>> & seen){
    if(!inGrid(i, j) || grid[i][j] != -1 || seen[i][j]){
        return 0;
    }
    seen[i][j] = true;
    int size = dfs(i-1, j, seen) + dfs(i+1, j, seen) + dfs(i, j-1, seen) + dfs(i, j+1, seen) + 1;

    return size;
}

int getAnswer(){
    int ans = 1;
    std::vector<std::vector<bool>> seen(GRIDSIZE, std::vector<bool>(GRIDSIZE, false));
    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(grid[i][j] == -1 && !seen[i][j]){
                ans *= dfs(i, j, seen);
            }
        }
    }
    return ans;
}

void backtrack(int index){
    if(index >= static_cast<int>(order.size())){
        if (!checkFinalGood()){
            return;
        }
        if(!checkAllConnected()){
            return;
        }
        printBoard(grid);
        printBoard(LCurr);
        std::cout << "Answer: " << getAnswer() << std::endl;
        return;
    }

    int i = order[index].first;
    int j = order[index].second;
    int L = LCurr[i][j];

    // check if this should be empty (since it is a helper)
    assert(helpers[i][j] == -1);

    // check that the last 2x2 square has at least one empty square
    if(i > 0 && j > 0){
        if(grid[i-1][j] != -1 && grid[i][j-1] != -1 && grid[i-1][j-1] != -1){
            backtrack(index + 1);
            return;
        }
    }

    int currentLHolder = -1;
    for(int nn = 1; nn <= GRIDSIZE; nn++){
        if(currCount[nn] > 0 && currL[nn] == L){
            currentLHolder = nn;
            break;
        }
    }

    if(currentLHolder != -1){
        // we can only place this number here
        int num = currentLHolder;
        if(currCount[num] < num){
            grid[i][j] = num;
            currCount[num]++;

            // if the upper left is a helper, check if it is valid
            bool bad = false;
            if(j - 1 >= 0 && helpers[i][j-1] != -1){
                if(!checkHelper(i, j-1)){
                    grid[i][j] = -1;
                    currCount[num]--;
                    bad = true;
                }
            }

            if(!bad){
                backtrack(index + 1);

                currCount[num]--;
                grid[i][j] = -1;
            }
        }
    } else{
        // we can place any number here
        for(int num = 1; num <= GRIDSIZE; num++){
            if(currCount[num] == num){
                continue;
            }

            assert(currCount[num] < num);

            grid[i][j] = num;
            currCount[num]++;

            // if the upper left is a helper, check if it is valid
            if(j - 1 >= 0 && helpers[i][j-1] != -1){
                if(!checkHelper(i, j-1)){
                    grid[i][j] = -1;
                    currCount[num]--;
                    continue;
                }
            }

            if(currCount[num] == 1){
                currL[num] = L;
            } else{
                if(currL[num] != L){
                    grid[i][j] = -1;
                    currCount[num]--;
                    continue;
                }
            }

            backtrack(index + 1);

            currCount[num]--;
            grid[i][j] = -1;
        }
    }

    if(j - 1 >= 0 && helpers[i][j - 1] != -1){
        if(!checkHelper(i, j - 1)){
            return;
        }
    }
    backtrack(index + 1);
}

int main(){ 
    generateLs(GRIDSIZE); // gets all possible L permutations
    std::cout << "Found " << Ls.size() << " Ls" << std::endl;

    order = getOrder(); // gets the order to place the numbers
    for(size_t i = 0; i < Ls.size(); i++){
        if(i % 1000 == 0)
            std::cout << "At: " << i << std::endl;

        LCurr = Ls[i];
        backtrack(0);
    }

    return 0;
}