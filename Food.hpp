//
//  Food.hpp
//  Universal
//
//  Created by Исаак Калинкин  on 19.03.16.
//  Copyright © 2016 HM. All rights reserved.
//

#ifndef Food_hpp
#define Food_hpp

#include <stdio.h>
//#include "BKTransform.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
#define FOOD_SPEED .5
#define EATING_DIST 4
#define POPULATION 100
using namespace std;

struct vect {
    double x, y;
    vect()
    {
        x = 0;
        y = 0;
    }
    vect(double x_, double y_) {
        x = x_;
        y = y_;
    }
    vect operator+(const vect &b) {
        return vect (x + b.x, y + b.y);
    }
    vect operator-(const vect &b) {
        return vect(x - b.x, y - b.y);
    }
    double angle() {
        return atan2(y, x)/(2 * M_PI) + 0.5;
    }
    double dist2(){
        return x*x + y*y;
    }
};
#define GENOME_SZ 2
struct genome {
    double data[GENOME_SZ];//N_EYES, -POW_of_DIST
    genome (){
        data[0] = 3 + rand()%100;
        data[1] = .1 + (rand() & 1023)/300;
    }
    genome operator+(genome &b){
        int a;
        genome res;
        for (int i = 0; i < GENOME_SZ; i++) {
            a = rand()&15;
            if (a == 0) {
                if (i == 0)
                    res.data[i] = 3 + rand() % 100;
            }else
                if (a < 8)
                    res.data[i] = b.data[i];
                else
                    res.data[i] = data[i];
        }
    }
};

int total_obj = 0;

struct obj {
    vect pos;
    int weight, id;
    bool movable;
    genome G;
    obj()
    {
        movable = 0;
        weight = 10;
        id = total_obj++;
    }
    obj(bool movable_, int weight_) {
        movable = movable_;
        weight = weight_;
        id = total_obj++;
    }
    void move(vector <obj> &A) {
        if (!movable)
            return;
        double eyes[int(G.data[0])], res_a;
        for (int i = 0; i < G.data[0]; i++)
            eyes[i] = 0;
        for (int i = 0; i < A.size(); i++) {
            if (id == A[i].id)
                continue;
            if ((A[i].pos - pos).dist2() < 4){///EATING DISTABCE
                if (A[i].movable) {//Eating
                    if (A[i].weight > weight) {
                        A[i].weight += weight;
                        weight = 10;
                        int best[3] = {0, 1, -1};
                        for (int i = 2; i < POPULATION; i++) {
                            best[2] = i;
                            if (A[best[1]].weight < A[best[2]].weight)
                                swap(best[1], best[2]);
                            if (A[best[0]].weight < A[best[1]].weight)
                                swap(best[0], best[1]);
                        }
                        G = A[best[0]].G + A[best[1]].G;
                        pos = vect (rand() % 100, rand() % 100);///SIZE OF FILD
                    } else {
                        weight += A[i].weight;
                        A[i].weight = 10;
                        int best[3] = {0, 1, -1};
                        for (int i = 2; i < POPULATION; i++) {
                            best[2] = i;
                            if (A[best[1]].weight < A[best[2]].weight)
                                swap(best[1], best[2]);
                            if (A[best[0]].weight < A[best[1]].weight)
                                swap(best[0], best[1]);
                        }
                        A[i].G = A[best[0]].G + A[best[1]].G;
                        A[i].pos = vect (rand() % 100, rand() % 100);///SIZE OF FILD
                    }
                } else {
                    weight += A[i].weight;
                    A[i].pos = vect (rand() % 100, rand() % 100);///SIZE OF FILD
                }
            }
            eyes[int((A[i].pos - pos).angle()*G.data[0])] +=
            pow((A[i].pos - pos).dist2(), G.data[1]) * (A[i].weight/weight);
        }
        int res = 0;
        for (int i = 1; i < G.data[0]; i++)
            if (eyes[i] > eyes[res])
                res = i;
        res_a = res / G.data[0] * 2 * M_PI;
        pos = pos + (vect(cos(res_a) * FOOD_SPEED, sin(res_a) * FOOD_SPEED));
    }
    void Render(sf::RenderWindow& window)
    {
        sf::CircleShape shape;
        shape.setRadius(pow(this->weight, 3));
        shape.setFillColor(sf::Color::White);
        shape.setPosition( 200, 200);
        window.draw(shape);
    }
};
#endif /* Food_hpp */
