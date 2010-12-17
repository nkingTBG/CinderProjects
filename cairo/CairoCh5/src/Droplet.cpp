#include "Droplet.h"
#include "cinder/cairo/Cairo.h"

Droplet::Droplet()
{
}

Droplet::Droplet(Vec2i pixel, cairo::Context &ctx, Colorf average, int cellSize)
{       
	mPosition = Vec2f(pixel.x, pixel.y);
	mCtx = ctx;
	mRadius = cellSize * 0.5f;
	mColor = average;
}

void Droplet::draw()
{
	Vec2f offset = Vec2f(mRadius * 0.05f, mRadius * 0.05f);
	cairo::GradientRadial gradient( mPosition + offset, mRadius, mPosition + offset, mRadius * 1.2f );
	gradient.addColorStop(0, ColorAf(mColor.r * 0.5f, mColor.g * 0.5f, mColor.b * 0.5f, 0.5f) );
	gradient.addColorStop(1, ColorAf(mColor.r * 0.5f, mColor.g * 0.5f, mColor.b * 0.5f, 0) );
	mCtx.setSource(gradient);
	mCtx.circle(mPosition + offset, mRadius * 1.2f);
	mCtx.fill();
	
	mCtx.circle(mPosition, mRadius);
	mCtx.setSource(mColor);
	mCtx.fill();
}