#pragma once
#include "cinder/cairo/Cairo.h"

using namespace ci;
using namespace std;

class Droplet {
public:
    Droplet();
	Droplet(Vec2i pixel, cairo::Context &ctx, Colorf average, int cellSize);
	
    void draw();

    cairo::Context mCtx;
    Vec2f mPosition;
    float mRadius;
	Colorf mColor;	
};