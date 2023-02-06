#include <bits/stdc++.h>
using namespace std;

struct Square{
	int x1, x2, y1, y2;
	// x1 = bottom left
	// x2 = bottom right
	// y1 = top left
	// y2 = top right
    Square(){x1 = x2 = y1 = y2 = 0;}
	Square(int x1_, int x2_, int y1_, int y2_) : x1(x1_), x2(x2_), y1(y1_), y2(y2_) {}

	void step(){
		int nextx1 = abs(x1 - y1);
		int nextx2 = abs(x1 - x2);
		int nexty1 = abs(y1 - y2);
		int nexty2 = abs(x2 - y2);

		x1 = nextx1;
		x2 = nextx2;
		y1 = nexty1;
		y2 = nexty2;
	}

	int simulate(){
		int ans = 1;
		while(!(x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)){
			step();
			ans++;
		}
		return ans;
	}

};

ostream& operator<<(ostream& os, const Square& sq){
    cout << sq.y1 << ";" << sq.y2 << ";" << sq.x2 << ";" << sq.x1;
	return os;
}

const int limit = 10000000;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    Square best;

	int ma = 0;
	for(int y2 = 0; y2 < 10000000; y2++){
		for(int y1 = int((double) y2 * 2.8392867); (double)y1/(double)y2 < 2.8392868 && y1 <= limit; y1++){
			for(int x1 = int((double) y1 * 2.191485); (double)x1/(double)y1 < 2.19149 && x1 <= limit; x1++){
				Square sq(x1, 0, y1, y2);
				Square original = sq;
				int ans = sq.simulate();
				if (ans > ma){
					cout << "New best: " << ans << endl;
                    ma = ans;
                    best = original;
				}
			}
		}
	}
    cout << "Answer:" << endl;
    cout << best << endl;

	return 0;
}

