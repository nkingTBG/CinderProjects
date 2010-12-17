#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Circle.h"
#include <list>
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    void setup();
    void update();
    void draw();
    list<Circle> circles;
};

void p5drawingApp::setup()
{       
    circles.push_back( Circle(100.0f, 100.0f) );
}

void p5drawingApp::update()
{   
    for( list<Circle>::iterator i = circles.begin(); i != circles.end(); ++i ) {
        i->update();
    }
    circles.push_back( Circle(100.0f, 100.0f) );
}

void p5drawingApp::draw()
{
    gl::clear();
    for( list<Circle>::iterator i = circles.begin(); i != circles.end(); ++i ) {
        i->draw();
    }
}

CINDER_APP_BASIC( p5drawingApp, RendererGl )