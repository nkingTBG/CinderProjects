#include "cinder/app/AppBasic.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/ImageIo.h"
#include "Droplet.h"
#include "cinder/Rand.h"
#include <list> 

using namespace ci;
using namespace ci::app;
using namespace std;


class cairoApp : public AppBasic {
public:
	void setup();
	void update();
	void draw();
	void makeDroplet(); 
	void keyDown(KeyEvent event);
	int countCalculator();
	Colorf getColor(Surface32f surface, Vec2i pixel);
	
	cairo::Context ctx;
	Surface32f surface;
	
	int cellSize;
	list<Droplet> droplets;
};

int cairoApp::countCalculator()
{
	int width = getWindowWidth();
	int height = getWindowHeight(); 
	int dropletCount = floor(width * height / cellSize / cellSize * 12.0f);
	return dropletCount;
}

void cairoApp::keyDown(KeyEvent event)
{
	if( event.getChar() == '1' ) {
		cellSize -= 2;
	} else if (event.getChar()== '2') {
		cellSize += 2;
	}
	
	if (cellSize < 2){
		cellSize = 2;
	}
	if (cellSize > getWindowWidth()){
		cellSize = getWindowWidth();
	}
	
	droplets.clear();
	
	for(int i = 0; i < countCalculator(); i++){
		makeDroplet();  
	}
}

void cairoApp::makeDroplet()
{
	int x = Rand::randInt(getWindowWidth());
	int y = Rand::randInt(getWindowHeight());
	Vec2i pixel = Vec2i(x, y);
	Colorf average = getColor(surface, pixel);
	droplets.push_back(Droplet(pixel, ctx, average, cellSize));
}

Colorf cairoApp::getColor( Surface32f surface, Vec2i pixel){
	
	Vec2i UL = Vec2i(pixel.x - cellSize * 0.5f, pixel.y - cellSize * 0.5f);
	Vec2i LR = Vec2i(pixel.x + cellSize * 0.5f, pixel.y + cellSize * 0.5f);
	
	if(UL.x < 0){
		UL.x = 0;
	}
	if(UL.y < 0){
		UL.y = 0;
	}
	if(LR.x > getWindowWidth() ){
		LR.x = getWindowWidth();
	}
	if(LR.y > getWindowHeight() ){
		LR.y = getWindowHeight();
	}
	
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
	
	for(int i = 0; i < countCalculator(); i++){
		makeDroplet();  
	}
}

void cairoApp::update()
{
}

void cairoApp::draw()
{
	ctx.setSource(Colorf(0.5,0.5,0.5));
	ctx.paint();
	for( list<Droplet>::iterator i = droplets.begin(); i != droplets.end(); ++i ) {
        i->draw();
    }
}

CINDER_APP_BASIC( cairoApp, Renderer2d )