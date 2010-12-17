#include "Circle.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

Circle::Circle(){
    
}

Circle::Circle(float x, float y){
    mVariation = Rand::randFloat(0.9f, 1.1f);
    mPosition = Vec2f(x,y);
    mRadius = 5.0f; 
    mVelocity = Vec2f(5.0f * mVariation, -5.0f * mVariation);
    mGravity = Vec2f(0.0f, 0.15f * mVariation);
}

void Circle::update(){
    
    if(mPosition.x > getWindowWidth() - mRadius || mPosition.x < mRadius){
        mVelocity.x *= -1;
        if (mPosition.x > getWindowWidth() - mRadius) {
            mPosition.x = getWindowWidth() - mRadius;
        }
        if (mPosition.x < mRadius) {
            mPosition.x = mRadius;
        }
        mVelocity *= 0.8f * mVariation;
    }   
    
    if(mPosition.y > getWindowHeight() - mRadius || mPosition.y < mRadius){
        mVelocity.y *= -1;
        if (mPosition.y > getWindowHeight() - mRadius) {
            mPosition.y = getWindowHeight() - mRadius;
        }
        if (mPosition.y < mRadius) {
            mPosition.y = mRadius;
        }
        mVelocity *= 0.8f * mVariation;
    }
    
    mVelocity += mGravity;
    mPosition += mVelocity;
    
}

void Circle::draw(){
    gl::drawSolidCircle( mPosition, mRadius);
}