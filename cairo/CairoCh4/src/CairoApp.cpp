#include "cinder/app/AppBasic.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class cairoApp : public AppBasic {
public:
	void setup();
	void update();
	void draw();
	Colorf getColor(Surface32f surface, Vec2i pixel);
	void keyDown(KeyEvent event);
	
	cairo::Context ctx;
	Surface32f surface;
	
	int cellSize;
};

void cairoApp::keyDown(KeyEvent event)
{
	if( event.getChar() == '1' ) {
		cellSize *= 0.667f;
	} else if (event.getChar()== '2') {
		cellSize *= 1.5f;
	}
	
	if (cellSize < 2){
		cellSize = 2;
	}
	if (cellSize > getWindowWidth()){
		cellSize = getWindowWidth();
	}
}

Colorf cairoApp::getColor( Surface32f surface, Vec2i pixel){
	
	Vec2i UL = Vec2i(pixel.x, pixel.y);
	Vec2i LR = Vec2i(pixel.x + cellSize, pixel.y + cellSize );
	int totalPixels = 0;
	float rTotal = 0.0f;
	float gTotal = 0.0f;
	float bTotal = 0.0f;
	
	for(int x = int(UL.x); x <= int(LR.x); x++){
		
		for(int y = int(UL.y); y <= int(LR.y); y++){
			
			Vec2i currentPixel = Vec2i(x,y);
			float r = *surface.getDataRed(currentPixel);
			float g = *surface.getDataGreen(currentPixel);
			float b = *surface.getDataBlue(currentPixel);
			
			rTotal += r;
			gTotal += g;
			bTotal += b;
			totalPixels++;
		}
	}
	
	float r = rTotal / totalPixels;
	float g = gTotal / totalPixels;
	float b = bTotal / totalPixels;
	
	return Colorf( r, g, b );
}

void cairoApp::setup()
{
	ctx = cairo::Context(cairo::createWindowSurface());
	surface = Surface32f( loadImage( loadResource("sunset.png") ) );
	cellSize = 10;
}

void cairoApp::update()
{
}

void cairoApp::draw()
{
	for (int x = 0; x < getWindowWidth(); x+=cellSize) {
		for (int y = 0; y < getWindowHeight(); y+=cellSize) {
			Vec2i pixel = Vec2i(x,y);
			Colorf color = getColor(surface, pixel);
			ctx.rectangle(x,y,cellSize,cellSize);
			ctx.setSource(color);
			ctx.fill();
		}
	}
}

CINDER_APP_BASIC( cairoApp, Renderer2d )