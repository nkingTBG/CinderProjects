#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    void setup();
    void update();
    void draw();
    
    Vec2f xyPosition;
    float radius;
    
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
    
    void keyDown( KeyEvent event );
    
    bool click;
};

void p5drawingApp::setup()
{
    xyPosition = Vec2f( 200.0f, 200.0f );
    radius = 10.0f;
    gl::clear();
    click = false;
}

void p5drawingApp::update()
{       
}

void p5drawingApp::draw()
{    
    if(click){
        gl::drawSolidCircle( xyPosition, radius );
    }
}

void p5drawingApp::mouseDrag( MouseEvent event )
{
    xyPosition = event.getPos() ;
    click = true;
}

void p5drawingApp::mouseUp( MouseEvent event )
{
    if(event.isLeft()){
        click = false;
    }
}

void p5drawingApp::keyDown( KeyEvent event ) {
    if( event.getChar() == ' ' ){
        gl::clear();
    }
}

CINDER_APP_BASIC( p5drawingApp, RendererGl )