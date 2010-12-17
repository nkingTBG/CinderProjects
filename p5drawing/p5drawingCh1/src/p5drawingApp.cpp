#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    //these are our 3 main functions
    void setup();
    void update();
    void draw();
    
    Vec2f xyPosition;   //this variable stores the x and y coordinates of the mouse
    float radius;       //this variable stores the radius of the circles we'll draw
    
    //these are the event listeners for the mouse
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
    
    //this is the event listener for the keyboard
    void keyDown( KeyEvent event );
    
    bool click;  //this variable stores whether the mouse is being held down or not
};

//this is the definition of our setup() function
void p5drawingApp::setup()
{
    xyPosition = Vec2f( 200.0f, 200.0f );   //initial value of the mouse position
    radius = 10.0f;             //value of the circle radius
    gl::clear();                //clear the screen
    click = false;              //set the initial state to false, or not-clicked
}

//this is the definition of our update() function
void p5drawingApp::update()
{       
}

//this is the definition of our draw() function
void p5drawingApp::draw()
{    
    //if the 'click' variable is set as true, draw a circle
    if(click){
        gl::drawSolidCircle( xyPosition, radius );
    }
}

//if the mouse gets dragged, record the mouses positions
void p5drawingApp::mouseDrag( MouseEvent event )
{
    xyPosition = event.getPos() ;
    click = true;
}

//if the mouse button is up, set 'click' to false
void p5drawingApp::mouseUp( MouseEvent event )
{
    if(event.isLeft()){
        click = false;
    }
}

//if the space bar is pressed, clear the screen
void p5drawingApp::keyDown( KeyEvent event ) {
    if( event.getChar() == ' ' ){
        gl::clear();
    }
}

//run our app, please!
CINDER_APP_BASIC( p5drawingApp, RendererGl )