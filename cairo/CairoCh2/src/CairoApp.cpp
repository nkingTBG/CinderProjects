#include "cinder/app/AppBasic.h"
#include "cinder/cairo/cairo.h"
using namespace ci;
using namespace ci::app;
using namespace std;


class cairoApp : public AppBasic {
public:
	void setup();
	void update();
	void draw();
	void mouseMove(MouseEvent event);
	void mouseDown(MouseEvent event);
	void mouseUp(MouseEvent event);
	Vec2f mouseLocation;
	bool mousePressed;
};

void cairoApp::mouseDown(MouseEvent event)
{
	mousePressed = true;
}

void cairoApp::mouseUp(MouseEvent event)
{
	mousePressed = false;
}

void cairoApp::mouseMove(MouseEvent event)
{
	mouseLocation = event.getPos();
}

void cairoApp::setup()
{
}

void cairoApp::update()
{
}

void cairoApp::draw()
{
	cairo::Context ctx( cairo::createWindowSurface() );     
	ctx.setSource( Colorf(0,0,0) );
	ctx.paint();
	
	Vec2f center = Vec2f( getWindowWidth()/2, getWindowHeight()/2 );
	Vec2f offset = mouseLocation - center;
	float length = offset.length();
	offset.safeNormalize();
	offset *= length/getWindowWidth() * 10;
	
	//Square
	ctx.rectangle(center.x - 100, center.y - 100, 200.0, 200.0 );
	ctx.setSource( Colorf(1,1,0) );
	ctx.fillPreserve();
	ctx.setSource( Colorf(1.0, 0.5, 0) );
	ctx.setLineWidth( 5.0 );
	ctx.stroke();
	
	//Circles
	ctx.circle( center + Vec2f(-30,-20), 20.0 );
	ctx.circle( center + Vec2f(30,-20), 20.0 );
	if (mousePressed) {
		ctx.setSource( Colorf(1,1,0) );
	} else {
		ctx.setSource( Colorf(1,1,1) );
	}
	ctx.fillPreserve();
	ctx.setSource( Colorf(1.0, 0.5, 0) );
	ctx.setLineWidth(1);
	ctx.stroke();
	
	//More Circles
	if (mousePressed) {
		ctx.arc(center.x - 30, center.y - 20, 20, M_PI / 6, M_PI / 6 * 5);
		ctx.setSource( Colorf(1.0,0.5,0) );
		ctx.setLineWidth(5);
		ctx.stroke();
		ctx.arc(center.x + 30, center.y - 20, 20, M_PI / 6, M_PI / 6 * 5);
		ctx.stroke();
	} else {
		ctx.circle( center + Vec2f(-30,-20) + offset, 7.0 );
		ctx.circle( center + Vec2f(30,-20) + offset, 7.0 );
		ctx.setSource( Colorf(0,0,1) );
		ctx.fill();
	}
	
	//Lines
	if(mousePressed){
		ctx.line( center + Vec2f(-55,-50), center + Vec2f(-20,-55) );
		ctx.line( center + Vec2f(55,-50), center + Vec2f(20,-55) );
	} else {
		ctx.line( center + Vec2f(-55,-55), center + Vec2f(-20,-70) );
		ctx.line( center + Vec2f(55,-55), center + Vec2f(20,-70) );
	}
	ctx.setLineWidth(3.0);
	ctx.setSource( Colorf(1.0,0.5,0) );
	ctx.stroke();
	
	//Arc
	ctx.arc(center.x, center.y - 20, 80.0, M_PI / 4, M_PI / 4 * 3);
	ctx.setLineWidth(8.0);
	ctx.setSource( Colorf(1,0,0) );
	ctx.stroke();
}

CINDER_APP_BASIC( cairoApp, Renderer2d )