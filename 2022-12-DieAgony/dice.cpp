#include <bits/stdc++.h>
#include "dice.h"
using namespace std;

Die::Die(){
    sides.fill(EMPTY);
}

void Die::roll(Direction dir){
    switch (dir){
        case ROLLUP:
            sides = {sides[BACK], sides[TOP], sides[UNDER], sides[LEFT], sides[RIGHT], sides[FRONT]};
            break;
        case ROLLDOWN:
            sides = {sides[FRONT], sides[UNDER], sides[TOP], sides[LEFT], sides[RIGHT], sides[BACK]};
            break;
        case ROLLRIGHT:
            sides = {sides[LEFT], sides[FRONT], sides[BACK], sides[UNDER], sides[TOP], sides[RIGHT]};
            break;
        case ROLLLEFT:
            sides = {sides[RIGHT], sides[FRONT], sides[BACK], sides[TOP], sides[UNDER], sides[LEFT]};
            break;
        default:
            assert(false);
    }
}

void Die::setSide(int side, int value){
    sides[side] = value;
}

ostream & operator<<(ostream & o, Die const & die) {
    o << "-------" << endl;
    o << "Top: " << die.sides[TOP] << endl;
    o << "Front: " << die.sides[FRONT] << endl;
    o << "Back: " << die.sides[BACK] << endl;
    o << "Left: " << die.sides[LEFT] << endl;
    o << "Right: " << die.sides[RIGHT] << endl;
    o << "Under: " << die.sides[UNDER] << endl;
    o << "-------";
    return o;
}