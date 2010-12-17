#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
    void setup();
    void update();
    void draw();
    
    Vec2f xyPosition; 
    float radius;
    
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
    
    void keyDown( KeyEvent event);
    
    bool click;
    
    Vec2f mouseVelocity;
    Vec2f mouseLast;
    
    Colorf color;
    Colorf colorArray[5];
    
};

void p5drawingApp::prepareSettings( Settings *settings )
{
    settings->setFrameRate( 100.0f );
}

void p5drawingApp::setup()
{
    xyPosition = Vec2f( 200.0f, 200.0f);
    radius = 2.0f;
    gl::clear();
    click = false;
    mouseLast = Vec2f (0.0f, 0.0f);
    
    Rand::randomize();
    
    for (int i = 0; i < 5; i++) {
        colorArray[i].r = Rand::randFloat(1.0);
        colorArray[i].g = Rand::randFloat(1.0);
        colorArray[i].b = Rand::randFloat(1.0);
    }
    
    color = colorArray[0];
}

void p5drawingApp::update()
{       
    mouseVelocity = xyPosition - mouseLast;
    radius = 2.0f + abs(mouseVelocity.x) + abs(mouseVelocity.y);
    if(radius > 50){
        radius = 50;
    }
    mouseLast = xyPosition;
}

void p5drawingApp::draw()
{   
    gl::color( color );
    if(click){
        gl::drawSolidCircle( xyPosition, radius );
    }
    float xCoord = getWindowWidth() - 10;
    float yCoord = getWindowHeight() - 10;
    gl::drawSolidCircle( Vec2f(xCoord, yCoord), 8.0f );
}

void p5drawingApp::mouseDrag( MouseEvent event )
{
    click = true;
    xyPosition = event.getPos() ;
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
    
    if( event.getChar() == '1' ){
        color = colorArray[0];
    }
    if( event.getChar() == '2' ){
        color = colorArray[1];
    }
    if( event.getChar() == '3' ){
        color = colorArray[2];
    }
    if( event.getChar() == '4' ){
        color = colorArray[3];
    }
    if( event.getChar() == '5' ){
        color = colorArray[4];
    }
    
}

CINDER_APP_BASIC( p5drawingApp, RendererGl )