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
#include "BKTransform.hpp"
#include <vector>
#include <iostream>
using namespace std;

const double elementary_radius = 5;
class Food
{
public:
    BKVector2d position;
    int radius;
    Food();
    Food(int radius);
    Food(BKVector2d position, int radius);
};
//void operator + (Food& lhs, Food& rhs);
class Player
{
private:
public:
    
};
class FoodManager
{
private:
    vector<Food> all_food;
    vector<Player> all_players;
public:
    void AddFood(Food food);
    void Update();
    void Render();
};
#endif /* Food_hpp */
