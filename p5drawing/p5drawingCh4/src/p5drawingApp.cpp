#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include<list>
#include "cinder/CinderMath.h"
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
public:
    void setup();
    void update();
    void draw();
    
    void mouseDrag(MouseEvent event);
    void mouseUp(MouseEvent event);
    void keyDown(KeyEvent event);
    
    Vec2f mousePos, mouseLast, mouseDir, mouseDirPlus, mouseDirMinus;
    Vec3f vStart, vEnd, vEndPlus, vEndMinus; 
    float vWidth, vRadius;
    list<Vec2f> vectorValues;
    list<float> lengthValues;
    int valAverageCount;
    
    float angleOrig, anglePlus, angleMinus, perpLength;
    Colorf color;
};

void p5drawingApp::mouseUp(MouseEvent event)
{
    vectorValues.clear();
    lengthValues.clear();
    
}

void p5drawingApp::keyDown(KeyEvent event)
{
    if( event.getChar() == ' ' ){
        gl::clear();
    }
}

void p5drawingApp::mouseDrag(MouseEvent event)
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
}

void p5drawingApp::update()
{   
    color.r = Rand::randFloat();
    color.g = Rand::randFloat();
    color.b = Rand::randFloat();
    
    mouseDir = mousePos - mouseLast;
    if( abs(mouseDir.x) + abs(mouseDir.y) > 2.0f ){
        mouseDir.safeNormalize();
        
        vectorValues.push_back(mouseDir);
        
        if(vectorValues.size() == valAverageCount+1){
            
            vectorValues.pop_front();
            mouseDir = Vec2f(0.0f, 0.0f);
            for( list<Vec2f>::iterator listIterator = vectorValues.begin(); listIterator != vectorValues.end(); ++listIterator ) {
                Vec2f vec = Vec2f(listIterator->x, listIterator->y);
                mouseDir += vec;
            }
            
            mouseDir /= valAverageCount;
        }
        
        angleOrig = math<float>::atan2(mouseDir.x, mouseDir.y);    
        anglePlus = angleOrig + M_PI/2;
        angleMinus = angleOrig - M_PI/2;
        
        Vec2f mouseVelocity = mousePos - mouseLast;
        perpLength = abs(mouseVelocity.x) + abs(mouseVelocity.y) + 5;
        
        lengthValues.push_back(perpLength);
        
        if(lengthValues.size() == valAverageCount+1){
            lengthValues.pop_front();
            perpLength = 0.0f;
            for( list<float>::iterator listIterator = lengthValues.begin(); listIterator != lengthValues.end(); ++listIterator ) {
                float length = *listIterator;
                perpLength += length;
            }
            perpLength /= valAverageCount;
        }
        
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
    }
}

void p5drawingApp::draw()
{   
    glLineWidth(perpLength/5);
    gl::color( color );
    if(vectorValues.size() == valAverageCount){
        gl::drawLine(vEndPlus, vEndMinus);
    }
}

CINDER_APP_BASIC( p5drawingApp, RendererGl )