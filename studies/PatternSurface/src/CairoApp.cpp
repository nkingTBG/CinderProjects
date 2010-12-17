#include "cinder/app/AppBasic.h"
#include "cinder/cairo/Cairo.h"
using namespace ci;
using namespace ci::app;
using namespace std;


class cairoApp : public AppBasic {
public:
	void setup();
	void update();
	void draw();
	
	cairo::PatternSurface mPattern;
};

void cairoApp::setup()
{
	mPattern = cairo::PatternSurface( loadImage( loadResource("sunset.png")));
	mPattern.setExtendRepeat();
}

void cairoApp::update()
{
}

void cairoApp::draw()
{
	cairo::Context ctx( cairo::createWindowSurface() );     
	ctx.setSource(Colorf(0,0,0));
	ctx.paint();
	ctx.setSource( mPattern );
	ctx.circle(Vec2f(200,200), 100);
	ctx.fill();
}

CINDER_APP_BASIC( cairoApp, Renderer2d )