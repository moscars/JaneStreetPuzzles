#ifndef DICE_H
#define DICE_H
#include <bits/stdc++.h>
using namespace std;

#define EMPTY INT32_MAX
#define TOP 0
#define FRONT 1
#define BACK 2
#define LEFT 3
#define RIGHT 4
#define UNDER 5

enum Direction {
    ROLLUP,
    ROLLDOWN,
    ROLLRIGHT,
    ROLLLEFT,
    DUMMY,
};

struct Die{

    // Order: Top, front, back, left, right, under
    array<int, 6> sides;

    Die();
    void roll(Direction);
    void setSide(int, int);
    friend ostream & operator<<(ostream &, const Die &);
};

#endif