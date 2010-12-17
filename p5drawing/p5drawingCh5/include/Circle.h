#pragma once
#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Circle {
public:
    Circle();
    Circle(float xPos, float yPos);
    
    void draw();
    void update();
    
    Vec2f mPosition, mVelocity, mGravity;
    float mRadius, mVariation;
};