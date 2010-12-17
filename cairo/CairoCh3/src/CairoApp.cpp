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
	void drawGradient(Rectf rect);
	cairo::Context ctx;
	Rectf rect0;
	int count;
	float tileSize;
};

void cairoApp::setup()
{	
	ctx = cairo::Context( cairo::createWindowSurface() );
}

void cairoApp::update()
{
	tileSize = 32;
}

void cairoApp::draw()
{
	ctx.setSource( Colorf(0,0,0) );
	ctx.paint();
	
	int tileCountX = ceil(getWindowWidth()/tileSize);
	int tileCountY = ceil(getWindowHeight()/tileSize);
	
	for (int x = 0; x <= tileCountX; x++) {
		for(int y = 0; y <= tileCountY; y++){
			rect0 = Rectf(x*tileSize - tileSize/2, y*tileSize - tileSize/2, x*tileSize + tileSize/2, y*tileSize + tileSize/2);
			count = 0;
			drawGradient(rect0);
		}
	}
}

void cairoApp::drawGradient(Rectf rect)
{
	ctx.rectangle( rect.x1, rect.y1, rect.x2 - rect.x1, rect.y2 - rect.y1 );
	cairo::GradientLinear gradient( Vec2f( rect.x1, rect.y1 ), Vec2f( rect.x2, rect.y1 ) );
	if(count % 4 == 1){
		gradient = cairo::GradientLinear( Vec2f( rect.x2, rect.y1 ), Vec2f( rect.x2, rect.y2 ) );
	}
	if(count % 4 == 2){
		gradient = cairo::GradientLinear( Vec2f( rect.x2, rect.y2 ), Vec2f( rect.x1, rect.y2 ) );
	}
	if(count % 4 == 3){
		gradient = cairo::GradientLinear( Vec2f( rect.x1, rect.y2 ), Vec2f( rect.x1, rect.y1 ) );
	}
	gradient.addColorStop(0, Colorf(0.1, 0, 0.2) );
	gradient.addColorStop(1, Colorf(1, 0, 1) );
	ctx.setSource(gradient);
	ctx.fill();
	rect.x1 += 1;
	rect.y1 += 1;
	rect.x2 -= 1;
	rect.y2 -= 1;
	if(rect.x2 - rect.x1 > 1 && rect.y2 - rect.y1 > 1){
		count++;
		drawGradient(rect);
	}
}

CINDER_APP_BASIC( cairoApp, Renderer2d )
