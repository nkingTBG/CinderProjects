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
};

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
}

CINDER_APP_BASIC( cairoApp, Renderer2d )