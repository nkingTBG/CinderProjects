#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class p5drawingApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void p5drawingApp::setup()
{
}

void p5drawingApp::mouseDown( MouseEvent event )
{
}

void p5drawingApp::update()
{
}

void p5drawingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( p5drawingApp, RendererGl )
