//
//  Food.cpp
//  Universal
//
//  Created by Исаак Калинкин  on 19.03.16.
//  Copyright © 2016 HM. All rights reserved.
//
#include <cmath>

struct vect {
    double x, y;
    vect(double x_, double y_) {
        x = x_;
        y = y_;
    }
    vect operator+(vect &b) {
        return vect (x + b.x, y + b.y);
    }
    vect operator-(vect &b) {
        return vect(x - b.x, y - b.y);
    }
    double angle() {
        return atan2(x, y);
    }
};
#define GENOME_SZ
struct genome {
    double data[GENOME_SZ];
};

struct obj {
    vect pos;
    int weight;
    bool movable;
    obj(bool movable_ = 0, int weight_ = 10) {
        movable = movable_;
        weight = weight_;
    }
    
};