#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include<list>
#include "cinder/CinderMath.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    void setup();
    void update();
    void draw();
    
    void mouseMove(MouseEvent event);
    
    Vec2f mousePos, mouseLast, mouseDir, mouseDirPlus, mouseDirMinus;
    Vec3f vStart, vEnd, vEndPlus, vEndMinus; 
    float vWidth, vRadius;
    list<Vec2f> vectorValues;
    list<float> lengthValues;
    int valAverageCount;
    
    float angleOrig, anglePlus, angleMinus, perpLength;
};

void p5drawingApp::mouseMove(MouseEvent event)
{
    mousePos = event.getPos();
}

void p5drawingApp::setup()
{       
    gl::clear( );
    valAverageCount = 5;
    vStart = Vec3f(0.0f, 0.0f, 0.0f);
    vWidth = 15.0f;
    vRadius = 5.0f;
    for(int i = 0; i < valAverageCount-1; i++){        
        vectorValues.push_back( Vec2f(0.0f, 0.0f) );   
    }
    for(int i = 0; i < valAverageCount-1; i++){ 
        lengthValues.push_back( 5.0f);
    }
}

void p5drawingApp::update()
{
    mouseDir = mousePos - mouseLast;
    if( abs(mouseDir.x) + abs(mouseDir.y) > 2.0f ){
        mouseDir.safeNormalize();
        
        vectorValues.push_back(mouseDir);
        
        for( list<Vec2f>::iterator listIterator = vectorValues.begin(); listIterator != vectorValues.end(); ++listIterator ) {
            Vec2f vec = Vec2f(listIterator->x, listIterator->y);
            mouseDir += vec;
        }
        
        mouseDir /= valAverageCount;
		
        angleOrig = math<float>::atan2(mouseDir.x, mouseDir.y);    
        anglePlus = angleOrig + M_PI/2;
        angleMinus = angleOrig - M_PI/2;
        
        Vec2f mouseVelocity = mousePos - mouseLast;
        perpLength = abs(mouseVelocity.x) + abs(mouseVelocity.y) + 5;
        
        lengthValues.push_back(perpLength);
        
        perpLength = 0.0f;
        
        for( list<float>::iterator listIterator = lengthValues.begin(); listIterator != lengthValues.end(); ++listIterator ) {
            float length = *listIterator;
            perpLength += length;
        }
        perpLength /= valAverageCount;
        
        
        mouseDirPlus = Vec2f( sin(anglePlus), cos(anglePlus) );
        mouseDirPlus.safeNormalize();
        mouseDirPlus *= perpLength;
        
        mouseDirMinus = Vec2f( sin(angleMinus), cos(angleMinus) );
        mouseDirMinus.safeNormalize();
        mouseDirMinus *= perpLength;
        
        mouseDir *= 35.0f;
        vStart = Vec3f(mousePos.x - mouseDir.x, mousePos.y - mouseDir.y, 0.0f);
        vEnd = Vec3f(mousePos.x, mousePos.y, 0.0f);
        
        vEndPlus = Vec3f(mousePos.x + mouseDirPlus.x, mousePos.y + mouseDirPlus.y, 0.0f);
        vEndMinus = Vec3f(mousePos.x + mouseDirMinus.x, mousePos.y + mouseDirMinus.y, 0.0f);
        
        mouseLast = mousePos;
        
        vectorValues.pop_front();
        lengthValues.pop_front();
    }
}

void p5drawingApp::draw()
{
    gl::clear( );
    gl::color( Colorf(1.0f, 1.0f, 1.0f) );
    gl::drawVector( vStart, vEnd, vWidth, vRadius);
    gl::color( Colorf(0.0f, 1.0f, 0.0f) );
    gl::drawVector( vEnd, vEndPlus, vWidth, vRadius);
    gl::color( Colorf(1.0f, 0.0f, 0.0f) );
    gl::drawVector( vEnd, vEndMinus, vWidth, vRadius);
}

CINDER_APP_BASIC( p5drawingApp, RendererGl )