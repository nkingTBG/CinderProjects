#pragma once
#include "cinder/app/AppBasic.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class Quad {
public:
    Quad();
    Quad(Vec3f, Vec3f, Vec3f, Vec3f);
    void update();
    void draw();
    Vec3f mVA, mVB, mVC, mVD;
    ColorAf mColor;
    bool mDie;
};